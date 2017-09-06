/// \file DQMCycle.cc
/*
 *
 * DQMCycle.cc source template automatically generated by a class generator
 * Creation date : ven. sept. 5 2014
 *
 * This file is part of DQM4HEP libraries.
 * 
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */

// -- dqm4hep headers
#include "dqm4hep/Cycle.h"
#include "dqm4hep/CoreTool.h"

namespace dqm4hep {

  namespace core {

    Cycle::Cycle() :
		    m_processingRate(0.f),
		    m_cycleValue(0.f),
		    m_cycleTimeout(10), // 10 seconds is the default value
		    m_nProcessedEvents(0)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    Cycle::~Cycle()
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    float Cycle::getCycleValue() const
    {
      return m_cycleValue;
    }

    //-------------------------------------------------------------------------------------------------

    void Cycle::setCycleValue(float value)
    {
      m_cycleValue = value;
    }

    //-------------------------------------------------------------------------------------------------

    unsigned int Cycle::getTimeout() const
    {
      return m_cycleTimeout;
    }

    //-------------------------------------------------------------------------------------------------

    void Cycle::setTimeout(unsigned int timeout)
    {
      m_cycleTimeout = timeout;
    }

    //-------------------------------------------------------------------------------------------------

    float Cycle::getProcessingRate() const
    {
      return m_processingRate;
    }

    //-------------------------------------------------------------------------------------------------

    unsigned int Cycle::getNProcessedEvents() const
    {
      return m_nProcessedEvents;
    }

    //-------------------------------------------------------------------------------------------------

    TimeDuration Cycle::getTotalCycleTime() const
    {
      return (m_endTime - m_startTime);
    }

    //-------------------------------------------------------------------------------------------------

    void Cycle::eventProcessed(const Event *const pEvent)
    {
      if(this->getState() != RUNNING_STATE)
        return;

      if(NULL == pEvent)
        return;

      m_nProcessedEvents++;
      m_lastEventProcessedTime = CoreTool::now();

      // call back for daughter class
      this->onEventProcessed(pEvent);

      // call back from listeners
      for(std::set<CycleListener*>::iterator iter = m_listeners.begin(), endIter = m_listeners.end() ;
          endIter != iter ; ++iter)
        (*iter)->onEventProcessed(this, pEvent);
    }

    //-------------------------------------------------------------------------------------------------

    const TimePoint &Cycle::getStartTime() const
    {
      return m_startTime;
    }

    //-------------------------------------------------------------------------------------------------

    const TimePoint &Cycle::getEndTime() const
    {
      return m_endTime;
    }

    //-------------------------------------------------------------------------------------------------

    void Cycle::startCycle()
    {
      m_startTime = CoreTool::now();
      m_lastEventProcessedTime = m_startTime;
      m_endTime = TimePoint();

      m_nProcessedEvents = 0;
      m_processingRate = 0.f;
      m_state = RUNNING_STATE;

      // call back for daughter class
      this->onCycleStarted();

      // call back from listeners
      for(std::set<CycleListener*>::iterator iter = m_listeners.begin(), endIter = m_listeners.end() ;
          endIter != iter ; ++iter)
        (*iter)->onCycleStarted(this);
    }

    //-------------------------------------------------------------------------------------------------

    void Cycle::stopCycle()
    {
      m_endTime = CoreTool::now();
      m_state = STOPPED_STATE;

      TimeDuration timeDifference = this->getTotalCycleTime();

      m_processingRate = (static_cast<float>(m_nProcessedEvents) / timeDifference.count());

      // call back for daughter class
      this->onCycleStopped();

      // call back from listeners
      for(std::set<CycleListener*>::iterator iter = m_listeners.begin(), endIter = m_listeners.end() ;
          endIter != iter ; ++iter)
        (*iter)->onCycleStopped(this);
    }

    //-------------------------------------------------------------------------------------------------

    State Cycle::getState() const
    {
      return m_state;
    }

    //-------------------------------------------------------------------------------------------------

    bool Cycle::isTimeoutReached() const
    {
      if( CoreTool::now() > m_lastEventProcessedTime + std::chrono::seconds(this->getTimeout()) )
        return true;

      return false;
    }

    //-------------------------------------------------------------------------------------------------

    void Cycle::addListener(CycleListener *pListener)
    {
      if(NULL != pListener)
        m_listeners.insert(pListener);
    }

    //-------------------------------------------------------------------------------------------------

    void Cycle::removeListener(CycleListener *pListener)
    {
      m_listeners.erase(pListener);
    }

  }

}

