/// \file DQMStandaloneModuleApplication.cc
/*
 *
 * DQMStandaloneModuleApplication.cc source template automatically generated by a class generator
 * Creation date : mer. ao�t 26 2015
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
#include "dqm4hep/StandaloneModuleApplication.h"
#include "dqm4hep/PluginManager.h"
#include "dqm4hep/FileHandler.h"
#include "dqm4hep/FileHandlerFactory.h"
#include "dqm4hep/MonitorElementManager.h"
#include "dqm4hep/StandaloneModule.h"
#include "dqm4hep/MonitorElementSender.h"
#include "dqm4hep/TimerCycle.h"
#include "dqm4hep/Archiver.h"
#include "dqm4hep/XmlHelper.h"
#include "dqm4hep/CoreTool.h"
#include "dqm4hep/tinyxml.h"

// -- std headers
#include <fstream>
#include <stdexcept>

// -- dim headers
#include "dis.hxx"
#include "dic.hxx"

namespace dqm4hep {

  namespace core {

    StandaloneModuleApplication::StandaloneModuleApplication() :
        ModuleApplication(),
        m_pTimerCycle(NULL),
        m_type("StandaloneModule"),
        m_name("Unknown"),
        m_moduleLogStr("[Standalone Module]"),
        m_returnStatusCode(STATUS_CODE_SUCCESS)
    {
      m_pArchiver = new Archiver();
    }

    //-------------------------------------------------------------------------------------------------

    StandaloneModuleApplication::~StandaloneModuleApplication()
    {
      if(m_pTimerCycle)
        delete m_pTimerCycle;

      delete m_pArchiver;
    }

    //-------------------------------------------------------------------------------------------------

    const std::string &StandaloneModuleApplication::getType() const
    {
      return m_type;
    }

    //-------------------------------------------------------------------------------------------------

    const std::string &StandaloneModuleApplication::getName() const
    {
      return m_name;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode StandaloneModuleApplication::readSettings( const std::string &settingsFileName )
    {
      if(this->isInitialized())
        return STATUS_CODE_ALREADY_INITIALIZED;

      size_t splitterPosition = settingsFileName.find(":");

      std::string fileHandlerType;
      std::string filePattern;

      if(splitterPosition != std::string::npos)
      {
        fileHandlerType = settingsFileName.substr(0, splitterPosition);
        filePattern = settingsFileName.substr(splitterPosition+1);
      }
      else
      {
        fileHandlerType = "";
        filePattern = settingsFileName;
      }

      LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << ", Starting standalone module application with file handler type " << fileHandlerType );

      FileHandlerFactory fileHandlerFactory;
      FileHandler *pFileHandler = fileHandlerFactory.createFileHandler(fileHandlerType);

      if(!pFileHandler)
        return STATUS_CODE_FAILURE;

      StatusCode statusCode = pFileHandler->download(filePattern);

      if(statusCode != STATUS_CODE_SUCCESS)
      {
        delete pFileHandler;
        return statusCode;
      }

      m_settings.m_settingsFileName = pFileHandler->getLocalFileName();
      delete pFileHandler;

      TiXmlDocument xmlDocument(m_settings.m_settingsFileName);

      if (!xmlDocument.LoadFile())
      {
        LOG4CXX_FATAL( dqmMainLogger , m_moduleLogStr << ", AnalysisModuleApplication::readSettings - Invalid xml file." );
        return STATUS_CODE_FAILURE;
      }

      const TiXmlHandle xmlDocumentHandle(&xmlDocument);

      if( ! m_replacementParameters.empty() )
      {
        TiXmlElement *pXmlElement = xmlDocumentHandle.FirstChildElement().Element();
        RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::replaceAllXmlAttributes(pXmlElement, m_replacementParameters));
      }

      const TiXmlHandle xmlHandle = TiXmlHandle(xmlDocumentHandle.FirstChildElement().Element());

      // monitor element sender
      TiXmlElement *const pMeCollectorElement = xmlHandle.FirstChildElement("monitorelementcollector").Element();

      if(NULL == pMeCollectorElement)
      {
        LOG4CXX_FATAL( dqmMainLogger , m_moduleLogStr << ", <monitorelementcollector> element not found !" );
        return STATUS_CODE_NOT_FOUND;
      }

      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::getAttribute(pMeCollectorElement, "name", m_settings.m_monitorElementCollector));

      this->getMonitorElementSender()->setCollectorName(m_settings.m_monitorElementCollector);
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->getMonitorElementSender()->connectToService());


      // cycle
      TiXmlElement *const pCycleElement = xmlHandle.FirstChildElement("cycle").Element();

      if(pCycleElement)
      {
        RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::getAttribute(pCycleElement, "sleep", m_settings.m_sleepTime));
        RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::getAttribute(pCycleElement, "period", m_settings.m_cyclePeriod));
      }

      m_pTimerCycle = new TimerCycle();
      m_pTimerCycle->setCycleValue(m_settings.m_cyclePeriod);
      m_pTimerCycle->setTimeout(0);
      m_pTimerCycle->addListener(this);




      // module
      TiXmlElement *const pXmlElement = xmlHandle.FirstChildElement("module").Element();

      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::getAttribute(pXmlElement, "type", m_settings.m_moduleType));
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::getAttribute(pXmlElement, "name", m_settings.m_moduleName));

      if(this->getModuleType().empty())
        this->setModuleType(m_settings.m_moduleType);

      if(this->getModuleName().empty())
        this->setModuleName(m_settings.m_moduleName);

      LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << ", Query standalone module to PluginManager ... " );

      StandaloneModule *pStandaloneModule = PluginManager::instance()->createPluginClass<StandaloneModule>(this->getModuleType());

      if(!pStandaloneModule)
        return STATUS_CODE_FAILURE;

      this->setModule(pStandaloneModule);
      m_moduleLogStr = "[" + pStandaloneModule->getName() + "]";

      LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << ", Query standalone module to PluginManager ... OK" );

      TiXmlHandle moduleHandle(pXmlElement);

      LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << ", Reading settings of active module '" << this->getModule()->getName() << "' ..." );
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->getModule()->readSettings(moduleHandle));
      LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << ", Reading settings of active module '" << this->getModule()->getName() << "' ... OK" );

      LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << ", Initializing active module '" << this->getModule()->getName() << "' ..." );
      RETURN_RESULT_IF( STATUS_CODE_SUCCESS, !=, this->getModule()->initModule() );
      LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << ", Initializing active module '" << this->getModule()->getName() << "' ... OK" );



      try
      {
        LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << ", Configuring archiver ..." );

        const TiXmlElement *const pXmlElement = xmlHandle.FirstChildElement("archiver").Element();

        THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::getAttribute(pXmlElement, "open", m_settings.m_openArchive));
        THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, XmlHelper::getAttribute(pXmlElement, "directory", m_settings.m_archiveDirectory));

        LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << ", Configuring archiver ... OK" );
      }
      catch(const StatusCodeException &exception)
      {
        return exception.getStatusCode();
      }



      m_name = this->getModule()->getName();

      DimBrowser browser;
      int nServers = browser.getServers();

      std::string moduleServerName = "DQM4HEP/Module/" + this->getModule()->getName();

      if(nServers)
      {
        char *serverName;
        char *node;

        while(browser.getNextServer(serverName, node))
        {
          if(moduleServerName == serverName)
          {
            LOG4CXX_ERROR( dqmMainLogger , m_moduleLogStr << ", Module already registered over the network.\n"
                << "Please, change the module name or stop the other module application with the same name !" );
            return STATUS_CODE_ALREADY_PRESENT;
          }
        }
      }

      DimServer::start( moduleServerName.c_str() );

      RETURN_RESULT_IF( STATUS_CODE_SUCCESS, !=, this->getMonitorElementSender()->connectToService() );

      this->setInitialized(true);
      m_settings.print(m_moduleLogStr);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    void StandaloneModuleApplication::setReplacementParameters(const ParameterMap &parametersMap)
    {
      m_replacementParameters = parametersMap;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode StandaloneModuleApplication::run()
    {
      if(!this->isInitialized())
        return STATUS_CODE_NOT_INITIALIZED;

      bool callStartOfCycle = true;

      // get casted module for easier manipulation
      StandaloneModule *pStandaloneModule = dynamic_cast<StandaloneModule *>(this->getModule());


      // open an archive
      if(m_settings.m_openArchive)
      {
        std::stringstream archiveFileName;
        std::string directory =
            m_settings.m_archiveDirectory.at(m_settings.m_archiveDirectory.size() - 1) == '/' ?
                m_settings.m_archiveDirectory : m_settings.m_archiveDirectory + "/";

        archiveFileName << directory
            << "DQMArchive"
            << "_M" << m_settings.m_moduleName;

        RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, m_pArchiver->open(archiveFileName.str(), "RECREATE"));
        LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << " , Archive '" << m_pArchiver->getFileName() << "' opened" );
      }


      while(!this->shouldStopApplication())
      {
        // process a cycle
        LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << " , Start of cycle");
        m_pTimerCycle->startCycle();

        while(1)
        {
          if( m_pTimerCycle->isEndOfCycleReached() )
            break;

          if( this->shouldStopApplication() )
            break;

          RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pStandaloneModule->process());

          CoreTool::sleep(std::chrono::microseconds(m_settings.m_sleepTime));
        }

        m_pTimerCycle->stopCycle();

        LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << " , End of cycle reached");
        LOG4CXX_INFO( dqmMainLogger , m_moduleLogStr << " , Sending monitor elements to collector" );

        RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->getMonitorElementSender()->sendMonitorElements());

        // archive publication if user asked for
        if(m_settings.m_openArchive)
          RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, m_pArchiver->archive(pStandaloneModule));
      }

      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pStandaloneModule->endModule());

      // archive the monitor element if archive is opened
      if(m_settings.m_openArchive)
        RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, m_pArchiver->close());

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    void StandaloneModuleApplication::onCycleStarted(const Cycle *const /*pCycle*/)
    {
      THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->getModule()->startOfCycle());
    }

    //-------------------------------------------------------------------------------------------------

    void StandaloneModuleApplication::onCycleStopped(const Cycle *const /*pCycle*/)
    {
      THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->getModule()->endOfCycle());
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    StandaloneModuleApplication::Settings::Settings() :
		    m_sleepTime(10),   // in ms
		    m_cyclePeriod(5.f),
		    m_monitorElementCollector("DEFAULT"),
		    m_archiveDirectory("/tmp"),
		    m_openArchive(false)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    void StandaloneModuleApplication::Settings::print(const std::string &moduleLogStr)
    {
      std::string openArchive = m_openArchive ? "yes" : "no";
      LOG4CXX_INFO( dqmMainLogger , moduleLogStr << " Settings file name : " << m_settingsFileName );
      LOG4CXX_INFO( dqmMainLogger , moduleLogStr << " Module type : " << m_moduleType );
      LOG4CXX_INFO( dqmMainLogger , moduleLogStr << " Module name : " << m_moduleName );
      LOG4CXX_INFO( dqmMainLogger , moduleLogStr << " Cycle period : " << m_cyclePeriod );
      LOG4CXX_INFO( dqmMainLogger , moduleLogStr << " Open archive : " << openArchive );
      LOG4CXX_INFO( dqmMainLogger , moduleLogStr << " Archive directory : " << m_archiveDirectory );
    }

  }

}

