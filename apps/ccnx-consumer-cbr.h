/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Ilya Moiseenko <iliamo@cs.ucla.edu>
 *         Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 */

#ifndef CCNX_CONSUMER_CBR_H
#define CCNX_CONSUMER_CBR_H

#include "ccnx-consumer.h"

namespace ns3 
{

/**
 * @ingroup ccnx
 * \brief CCNx application for sending out Interest packets at a "constant" rate (Poisson process)
 */
class CcnxConsumerCbr: public CcnxConsumer
{
public: 
  static TypeId GetTypeId ();
        
  /**
   * \brief Default constructor 
   * Sets up randomizer function and packet sequence number
   */
  CcnxConsumerCbr ();
  virtual ~CcnxConsumerCbr ();

  // From CcnxApp
  // virtual void
  // OnInterest (const Ptr<const CcnxInterestHeader> &interest);

  // virtual void
  // OnNack (const Ptr<const CcnxInterestHeader> &interest);

  // virtual void
  // OnContentObject (const Ptr<const CcnxContentObjectHeader> &contentObject,
  //                  const Ptr<const Packet> &payload);

protected:
  /**
   * \brief Constructs the Interest packet and sends it using a callback to the underlying CCNx protocol
   */
  virtual void
  ScheduleNextPacket ();

  void
  SetRandomize (const std::string &value);

  std::string
  GetRandomize () const;
  
private:
  // void
  // UpdateMean ();

  // virtual void
  // SetPayloadSize (uint32_t payload);

  // void
  // SetDesiredRate (DataRate rate);

  // DataRate
  // GetDesiredRate () const;
  
protected:
  double              m_frequency; // Frequency of interest packets (in hertz)
  bool                m_firstTime;
  RandomVariable      *m_random;
  std::string         m_randomType;
};

} // namespace ns3

#endif
