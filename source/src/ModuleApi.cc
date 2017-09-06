/// \file DQMModuleApi.cc
/*
 *
 * DQMModuleApi.cc source template automatically generated by a class generator
 * Creation date : ven. oct. 31 2014
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
#include "dqm4hep/ModuleApi.h"
#include "dqm4hep/ModuleApplication.h"
#include "dqm4hep/AnalysisModuleApplication.h"
#include "dqm4hep/Logging.h"
#include "dqm4hep/MonitorElement.h"
#include "dqm4hep/MonitorElementManager.h"
#include "dqm4hep/Storage.h"
#include "dqm4hep/Directory.h"
#include "dqm4hep/Module.h"
#include "dqm4hep/Archiver.h"
#include "dqm4hep/AlertSystem.h"
#include "dqm4hep/Run.h"
#include "dqm4hep/Cycle.h"
#include "dqm4hep/tinyxml.h"

namespace dqm4hep {

  namespace core {

    void ModuleApi::cd(const Module *const pModule)
    {
      pModule->getModuleApplication()->getMonitorElementManager()->cd();
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::cd(const Module *const pModule, const std::string &dirName)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->cd(dirName);
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::mkdir(const Module *const pModule, const std::string &dirName)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->mkdir(dirName);
    }

    //-------------------------------------------------------------------------------------------------

    void ModuleApi::ls(const Module *const pModule, bool recursive)
    {
      pModule->getModuleApplication()->getMonitorElementManager()->ls(recursive);
    }

    //-------------------------------------------------------------------------------------------------

    const std::string &ModuleApi::pwd(const Module *const pModule)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->pwd();
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::goUp(const Module *const pModule)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->goUp();
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::rmdir(const Module *const pModule, const std::string &dirName)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->rmdir(dirName);
    }

    //-------------------------------------------------------------------------------------------------

    bool ModuleApi::dirExists(const Module *const pModule, const std::string &dirName)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->dirExists(dirName);
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookRealHistogram1D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title, int nBins, float minimum, float maximum)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          REAL_HISTOGRAM_1D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TH1FAllocator(), nBins, minimum, maximum));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookIntHistogram1D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title, int nBins, float minimum, float maximum)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          INT_HISTOGRAM_1D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TH1IAllocator(), nBins, minimum, maximum));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookCharHistogram1D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title, int nBins, float minimum, float maximum)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          CHAR_HISTOGRAM_1D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TH1CAllocator(), nBins, minimum, maximum));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookShortHistogram1D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title, int nBins, float minimum, float maximum)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          SHORT_HISTOGRAM_1D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TH1SAllocator(), nBins, minimum, maximum));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookRealHistogram2D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          REAL_HISTOGRAM_2D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TH2FAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookIntHistogram2D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          INT_HISTOGRAM_2D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TH2IAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookCharHistogram2D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          CHAR_HISTOGRAM_2D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TH2CAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookShortHistogram2D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          SHORT_HISTOGRAM_2D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TH2SAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookRealHistogram3D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax,
        int nZBins, float zMin, float zMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          REAL_HISTOGRAM_3D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TH3FAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax, nZBins, zMin, zMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookIntHistogram3D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax,
        int nZBins, float zMin, float zMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          INT_HISTOGRAM_3D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TH3IAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax, nZBins, zMin, zMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookProfile1D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax, float yMin, float yMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          PROFILE_1D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TProfileAllocator(), nXBins, xMin, xMax, yMin, yMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookProfile2D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax,
        float zMin, float zMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          PROFILE_2D_ELEMENT_TYPE, ".", name, title, pModule->getName(), TProfile2DAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax, zMin, zMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookInt(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title, const int &value)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookObject(monitorElement,
          INT_ELEMENT_TYPE, ".", name, title, pModule->getName(), TScalarIntAllocator(), value));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookFloat(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title, const float &value)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookObject(monitorElement,
          REAL_ELEMENT_TYPE, ".", name, title, pModule->getName(), TScalarFloatAllocator(), value));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookShort(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title, const short &value)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookObject(monitorElement,
          SHORT_ELEMENT_TYPE, ".", name, title, pModule->getName(), TScalarShortAllocator(), value));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookString(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &name, const std::string &title, const std::string &value)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookObject(monitorElement,
          STRING_ELEMENT_TYPE, ".", name, title, pModule->getName(), TScalarStringAllocator(), value));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookRealHistogram1D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title, int nBins, float minimum, float maximum)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          REAL_HISTOGRAM_1D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TH1FAllocator(), nBins, minimum, maximum));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookIntHistogram1D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title, int nBins, float minimum, float maximum)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          INT_HISTOGRAM_1D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TH1IAllocator(), nBins, minimum, maximum));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookCharHistogram1D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title, int nBins, float minimum, float maximum)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          CHAR_HISTOGRAM_1D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TH1CAllocator(), nBins, minimum, maximum));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookShortHistogram1D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title, int nBins, float minimum, float maximum)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          SHORT_HISTOGRAM_1D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TH1SAllocator(), nBins, minimum, maximum));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookRealHistogram2D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          REAL_HISTOGRAM_2D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TH2FAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookIntHistogram2D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          INT_HISTOGRAM_2D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TH2IAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookCharHistogram2D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          CHAR_HISTOGRAM_2D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TH2CAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookShortHistogram2D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          SHORT_HISTOGRAM_2D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TH2SAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookRealHistogram3D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax,
        int nZBins, float zMin, float zMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          REAL_HISTOGRAM_3D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TH3FAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax, nZBins, zMin, zMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookIntHistogram3D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax,
        int nZBins, float zMin, float zMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          INT_HISTOGRAM_3D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TH3IAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax, nZBins, zMin, zMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookProfile1D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax, float yMin, float yMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          PROFILE_1D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TProfileAllocator(), nXBins, xMin, xMax, yMin, yMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookProfile2D(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title,
        int nXBins, float xMin, float xMax,
        int nYBins, float yMin, float yMax,
        float zMin, float zMax)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookHistogram(monitorElement,
          PROFILE_2D_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TProfile2DAllocator(), nXBins, xMin, xMax, nYBins, yMin, yMax, zMin, zMax));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookInt(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title, const int &value)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookObject(monitorElement,
          INT_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TScalarIntAllocator(), value));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookFloat(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title, const float &value)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookObject(monitorElement,
          REAL_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TScalarFloatAllocator(), value));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookShort(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title, const short &value)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookObject(monitorElement,
          SHORT_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TScalarShortAllocator(), value));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookString(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title, const std::string &value)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookObject(monitorElement,
          STRING_ELEMENT_TYPE, dirName, name, title, pModule->getName(), TScalarStringAllocator(), value));

      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::getAllMonitorElements(const Module *const pModule, MonitorElementPtrList &monitorElementList)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->getAllMonitorElements(monitorElementList);
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::getMonitorElement(const Module *const pModule, const std::string &monitorElementName, MonitorElementPtr &monitorElement)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->getMonitorElement(monitorElementName, monitorElement);
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::getMonitorElement(const Module *const pModule, const std::string &dirName, const std::string &monitorElementName, MonitorElementPtr &monitorElement)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->getMonitorElement(dirName, monitorElementName, monitorElement);
    }

    //-------------------------------------------------------------------------------------------------

    MonitorElementPtr ModuleApi::getMonitorElement(const Module *const pModule, const std::string &monitorElementName)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->getMonitorElement(monitorElementName);
    }

    //-------------------------------------------------------------------------------------------------

    MonitorElementPtr ModuleApi::getMonitorElement(const Module *const pModule, const std::string &dirName, const std::string &monitorElementName)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->getMonitorElement(dirName, monitorElementName);
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::deleteMonitorElement(const Module *const pModule, MonitorElementPtr &monitorElement)
    {
      std::string fullName = (monitorElement->getPath() + monitorElement->getName()).getPath();
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->deleteMonitorElement(monitorElement));
      pModule->getModuleApplication()->getMonitorElementSender()->removeAvailableMonitorElement(fullName);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::sendAlert(const Module *const pModule, AlertType type, const std::string &message)
    {
      return pModule->getModuleApplication()->getAlertNotifier()->notify(type, message);
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::sendAlert(const Module *const pModule, AlertType type, const std::string &message, const MonitorElementPtr &monitorElement)
    {
      return pModule->getModuleApplication()->getAlertNotifier()->notify(type, message, monitorElement);
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::resetMonitorElements(const Module *const pModule, ResetPolicy policy)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->resetMonitorElements(policy);
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::resetMonitorElements(const Module *const pModule)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->resetMonitorElements();
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::registerQualityTestFactory(const Module *const pModule, const std::string &qualityTestFactoryName, const QualityTestFactory *const pQualityTestFactory)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->registerQualityTestFactory(qualityTestFactoryName, pQualityTestFactory);
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::createQualityTest(const Module *const pModule, TiXmlElement *const pXmlElement)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->createQualityTest(pXmlElement);
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::addQualityTest(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &qualityTestName)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->addQualityTest(monitorElement, qualityTestName);
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::runQualityTests(const Module *const pModule, MonitorElementPtr &monitorElement)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->runQualityTests(monitorElement);
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::runQualityTest(const Module *const pModule, MonitorElementPtr &monitorElement, const std::string &qualityTestName)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->runQualityTest(monitorElement, qualityTestName);
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::runQualityTests(const Module *const pModule)
    {
      return pModule->getModuleApplication()->getMonitorElementManager()->runQualityTests();
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::getTimeSinceStartOfRun(const AnalysisModule *const pModule, TimeDuration &duration)
    {
      AnalysisModuleApplication *pApplication = dynamic_cast<AnalysisModuleApplication *>(pModule->getModuleApplication());

      if( ! pApplication )
        return STATUS_CODE_INVALID_PARAMETER;

      Run *pRun = pApplication->getCurrentRun();

      if( ! pRun )
        return STATUS_CODE_FAILURE;

      duration = pRun->getStartTime() - CoreTool::now();

      return STATUS_CODE_FAILURE;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::getTimeSinceStartOfCycle(const AnalysisModule *const pModule, TimeDuration &duration)
    {
      AnalysisModuleApplication *pApplication = dynamic_cast<AnalysisModuleApplication *>(pModule->getModuleApplication());

      if( ! pApplication )
        return STATUS_CODE_INVALID_PARAMETER;

      Cycle *pCycle = pApplication->getCycle();

      if( ! pCycle )
        return STATUS_CODE_FAILURE;

      duration = pCycle->getStartTime() - CoreTool::now();

      return STATUS_CODE_FAILURE;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookMonitorElement(const Module *const pModule, const TiXmlElement *const pXmlElement,
        const std::string &meName, MonitorElementPtr &monitorElement)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookMonitorElement(pXmlElement, pModule->getName(), meName, monitorElement));
      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode ModuleApi::bookMonitorElement(const Module *const pModule, const TiXmlElement *const pXmlElement,
        MonitorElementPtr &monitorElement, const ParameterMap &parameters)
    {
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookMonitorElement(pXmlElement, pModule->getName(), monitorElement, parameters));
      pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

      return STATUS_CODE_SUCCESS;
    }

  }

}

