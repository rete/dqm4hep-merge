/// \file DQMShmProxyApplication.h
/*
 *
 * DQMShmProxyApplication.h header template automatically generated by a class generator
 * Creation date : mer. avr. 13 2016
 *
 * This file is part of DQMEvb libraries.
 * 
 * DQMEvb is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * DQMEvb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DQMEvb.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef DQM4HEP_SHMPROXYAPPLICATION_H
#define DQM4HEP_SHMPROXYAPPLICATION_H

// -- dqm4hep headers
#include "dqm4hep/Application.h"
#include "dqm4hep/EventClient.h"
#include "dqm4hep/RunControlClient.h"
#include "dqm4hep/Run.h"
#include "dqm4hep/evb/DQMShmProcessor.h"

// -- levbdim headers
#include "fsm.hh"
#include "fsmmessage.hh"
#include "shmdriver.hh"
#include "datasocket.hh"

namespace dqm4hep {

  namespace core {

    class TiXmlElement;

    /** ShmProxyApplication class
     */
    class ShmProxyApplication : public Application, public levbdim::shmprocessor, public RunListener
    {
    public:
      /** Constructor
       */
      ShmProxyApplication();

      /** Destructor
       */
      ~ShmProxyApplication();

      /** Set the application name as it will be
       *  registered on DIM network
       */
      void setName(const std::string &name);

      // from Application
      StatusCode run();
      StatusCode readSettings(const std::string &settingsFile);
      StatusCode exit(int returnCode);
      bool shouldStopApplication() const;
      void setStopApplication(bool stop);
      const std::string & getType() const;
      const std::string & getName() const;

      // from run listener
      void onStartOfRun(Run *const pRun);
      void onEndOfRun(const Run *const pRun);

      void setReplacementParameters( const ParameterMap &parameters );

    private:
      /** Set the application as initialized.
       *  Set to true after calling readSettings()
       */
      void setInitialized(bool initialized);

      /** Whether the application is initialized
       */
      bool isInitialized() const;

      /** Configure application with global settings
       */
      StatusCode configureGlobal(TiXmlElement *pGlobalSettings);

      /** Configure application with user evb processor settings
       */
      StatusCode configureProcessors(TiXmlElement *pProcessorsSettings);

      /** Configure the shm driver
       */
      StatusCode configureShmDriver(TiXmlElement *pShmSettings);

      /** Configure the run control client interface
       */
      StatusCode configureRunControlClient(TiXmlElement *pRunControlSettings);

    private:
      // from shm processor
      void start(uint32_t run) {}
      void stop() {}

      /** Process a completed event.
       *
       * 	Do the following thing :
       * 	  - Create a dqm event
       * 	  - Call ShmProcessor::processEvent() for each registered processor to fill the event
       * 	  - Send the event using dqm event client
       */
      void processEvent(uint32_t key, std::vector<levbdim::buffer*> bufferList);

    private:
      typedef std::vector< std::pair<std::string, ShmProcessor *> > ProcessorList;

      ProcessorList                     m_processorList;

      EventStreamer                       *m_pEventStreamer;
      std::vector<EventClient *>           m_eventClientList;
      RunControlClient                    *m_pRunControlClient;
      levbdim::shmdriver                  *m_pShmDriver;          ///< The shm driver to read data source in shared memory

      ParameterMap                         m_replacementParameters;

      std::string                          m_type;
      std::string                          m_name;
      bool                                 m_isInitialized;
      bool                                 m_shouldStop;
      StatusCode                           m_returnCode;
    };

  }

} 

#endif  //  DQM4HEP_SHMPROXYAPPLICATION_H
