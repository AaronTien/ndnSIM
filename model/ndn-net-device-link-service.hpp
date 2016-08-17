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

#ifndef NDN_NET_DEVICE_LINK_SERVICE_HPP
#define NDN_NET_DEVICE_LINK_SERVICE_HPP

#include "ns3/ndnSIM/NFD/daemon/face/link-service.hpp"
#include "ns3/ndnSIM/model/ndn-common.hpp"
#include "ns3/ndnSIM/model/ndn-face.hpp"

#include "ns3/net-device.h"

namespace ns3 {
namespace ndn {

//class Face;

/** \brief the upper part of a Face
 *  \sa Face
 */
class NetDeviceLinkService : public virtual nfd::face::LinkService
{

public:
  NetDeviceLinkService();

  virtual
  ~NetDeviceLinkService();

private: // upper interface to be overridden in subclass (send path entrypoint)
  /** \brief performs LinkService specific operations to send an Interest
   */
  void
  doSendInterest(const ::ndn::Interest& interest);

  /** \brief performs LinkService specific operations to send a Data
   */
  void
  doSendData(const ::ndn::Data& data);

  /** \brief performs LinkService specific operations to send a Nack
   */
  void
  doSendNack(const ::ndn::lp::Nack& nack);

private: // lower interface to be overridden in subclass
  void
  doReceivePacket(nfd::face::Transport::Packet&& packet);

private:
  Ptr<Node> m_node;
  Ptr<NetDevice> m_netDevice; ///< \brief Smart pointer to NetDevice
};

} // namespace ndn
} // namespace ns3

#endif // NDN_NET_DEVICE_LINK_SERVICE_HPP
