/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014-2015,  Regents of the University of California,
 *                           Arizona Board of Regents,
 *                           Colorado State University,
 *                           University Pierre & Marie Curie, Sorbonne University,
 *                           Washington University in St. Louis,
 *                           Beijing Institute of Technology,
 *                           The University of Memphis.
 *
 * This file is part of NFD (Named Data Networking Forwarding Daemon).
 * See AUTHORS.md for complete list of NFD authors and contributors.
 *
 * NFD is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * NFD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * NFD, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ndn-net-device-link-service.hpp"
#include "ndn-l3-protocol.hpp"

#include "ndn-ns3.hpp"

#include "ns3/net-device.h"
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/node.h"
#include "ns3/pointer.h"

#include "ns3/address.h"
#include "ns3/point-to-point-net-device.h"
#include "ns3/channel.h"

#include "../utils/ndn-fw-hop-count-tag.hpp"

#include "ns3/ndnSIM/NFD/common.hpp"
#include "ns3/ndnSIM/NFD/core/logger.hpp" 
#include <ndn-cxx/lp/packet.hpp>

namespace ns3 {
namespace ndn {

void
NetDeviceLinkService::NetDeviceLinkService()
{

}


void
NetDeviceLinkService::doSendInterest(const ::ndn::Interest& interest)
{
  NS_LOG_FUNCTION(this << &interest);

  //this->emitSignal(onSendInterest, interest);
  ::ndn::lp::Packet lpPacket(interest.wireEncode());
  nfd::face::Transport::Packet tp(lpPacket.wireEncode());
  //Ptr<Packet> packet = Convert::ToPacket(interest);
  sendPacket(std::move(tp));
}

void
NetDeviceLinkService::doSendData(const Data& data)
{
  NS_LOG_FUNCTION(this << &data);

  ::ndn::lp::Packet lpPacket(data.wireEncode());
  nfd::face::Transport::Packet tp(lpPacket.wireEncode());
  sendPacket(std::move(tp));
}

void
NetDeviceLinkService::doSendNack(const lp::Nack& nack)
{
  ::ndn::lp::Packet lpPacket(nack.getInterest().wireEncode());
  nfd::face::Transport::Packet tp(lpPacket.wireEncode());
  sendPacket(std::move(tp));
}

void
NetDeviceLinkService::doReceivePacket(Transport::Packet&& packet)
{
  try {
    lp::Packet pkt(packet.packet);

    bool isReassembled = false;
    Block netPkt;
    lp::Packet firstPkt;
    std::tie(isReassembled, netPkt, firstPkt) = m_reassembler.receiveFragment(packet.remoteEndpoint,
                                                                              pkt);
    if (isReassembled) {
      this->decodeNetPacket(netPkt, firstPkt);
    }
  }
  catch (const tlv::Error& e) {
    ++this->nInLpInvalid;
    NFD_LOG_FACE_WARN("packet parse error (" << e.what() << "): DROP");
  }
}

} // namespace face
} // namespace nfd
