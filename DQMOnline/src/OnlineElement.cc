  /// \file OnlineElement.cc
/*
 *
 * OnlineElement.cc source template automatically generated by a class generator
 * Creation date : lun. avr. 30 2018
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
 * @copyright 
 */

// -- dqm4hep header
#include <dqm4hep/OnlineElement.h>
#include <dqm4hep/Logging.h>
#include <dqm4hep/QualityTest.h>

// -- xdrstream header
#include <xdrstream/xdrstream.h>

namespace dqm4hep {
  
  namespace online {

    OnlineElementPtr OnlineElement::make_shared() {
      return std::shared_ptr<OnlineElement>(new OnlineElement());
    }
    
    //-------------------------------------------------------------------------------------------------

    OnlineElementPtr OnlineElement::make_shared(TObject *pMonitorObject) {
      return std::shared_ptr<OnlineElement>(new OnlineElement(pMonitorObject));
    }
    
    //-------------------------------------------------------------------------------------------------

    OnlineElementPtr OnlineElement::make_shared(TObject *pMonitorObject, TObject *pReferenceObject) {
      return std::shared_ptr<OnlineElement>(new OnlineElement(pMonitorObject, pReferenceObject));
    }
    
    //-------------------------------------------------------------------------------------------------

    OnlineElementPtr OnlineElement::make_shared(const core::PtrHandler<TObject> &monitorObject) {
      return std::shared_ptr<OnlineElement>(new OnlineElement(monitorObject));
    }
    
    //-------------------------------------------------------------------------------------------------

    OnlineElementPtr OnlineElement::make_shared(const core::PtrHandler<TObject> &monitorObject,
                                   const core::PtrHandler<TObject> &referenceObject) {
      return std::shared_ptr<OnlineElement>(new OnlineElement(monitorObject, referenceObject));
    }
    
    //-------------------------------------------------------------------------------------------------
    
    OnlineElement::OnlineElement() :
      core::MonitorElement() {
      /* nop */
    }
    
    //-------------------------------------------------------------------------------------------------
    
    OnlineElement::OnlineElement(TObject *pMonitorObject) :
      core::MonitorElement(pMonitorObject) {
      /* nop */
    }
    
    //-------------------------------------------------------------------------------------------------
    
    OnlineElement::OnlineElement(TObject *pMonitorObject, TObject *pReferenceObject) :
      core::MonitorElement(pMonitorObject, pReferenceObject) {
      /* nop */
    }
    
    //-------------------------------------------------------------------------------------------------
    
    OnlineElement::OnlineElement(const core::PtrHandler<TObject> &monitorObject) :
      core::MonitorElement(monitorObject) {
      /* nop */
    }
    
    //-------------------------------------------------------------------------------------------------
    
    OnlineElement::OnlineElement(const core::PtrHandler<TObject> &monitorObject, const core::PtrHandler<TObject> &referenceObject) :
      core::MonitorElement(monitorObject, referenceObject) {
      /* nop */
    }
    
    //-------------------------------------------------------------------------------------------------

    void OnlineElement::setRunNumber(int runNum) {
      m_runNumber = runNum;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    int OnlineElement::runNumber() const {
      return m_runNumber;
    }
    
    //-------------------------------------------------------------------------------------------------
      
    const std::string &OnlineElement::collectorName() const {
      return m_collectorName;
    }
    
    //-------------------------------------------------------------------------------------------------

    const std::string &OnlineElement::moduleName() const {
      return m_moduleName;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    void OnlineElement::setDescription(const std::string &desc) {
      m_description = desc;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    const std::string &OnlineElement::description() const {
      return m_description;
    }
    
    //-------------------------------------------------------------------------------------------------
   
    void OnlineElement::setCollectorName(const std::string &colName) {
      m_collectorName = colName;
    }
    
    //-------------------------------------------------------------------------------------------------

    void OnlineElement::setModuleName(const std::string &modName) {
      m_moduleName = modName;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    void OnlineElement::setPublish(bool pub) {
      m_publish = pub;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    bool OnlineElement::publish() const {
      return m_publish;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    bool OnlineElement::subscribed() const {
      return m_subscribed;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    void OnlineElement::setSubscribed(bool sub) {
      m_subscribed = sub;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    core::StatusCode OnlineElement::runQualityTests(core::QReportMap &reports) {
      RETURN_RESULT_IF(core::STATUS_CODE_SUCCESS, !=, core::MonitorElement::runQualityTests(reports));
      m_reports.clear();
      m_reports = reports;
      return core::STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    core::StatusCode OnlineElement::runQualityTest(const std::string &qname, core::QReport &report) {
      RETURN_RESULT_IF(core::STATUS_CODE_SUCCESS, !=, core::MonitorElement::runQualityTest(qname, report));
      m_reports[report.m_qualityTestName] = report;
      return core::STATUS_CODE_SUCCESS;
    }
    
    //-------------------------------------------------------------------------------------------------
    
    void OnlineElement::reset(bool resetQtests) {
      core::MonitorElement::reset(resetQtests);
      m_runNumber = 0;
      m_collectorName.clear();
      m_moduleName.clear();
      m_description.clear();
      m_reports.clear();
    }
    
    //-------------------------------------------------------------------------------------------------
    
    void OnlineElement::toJson(core::json &obj) const {
      core::MonitorElement::toJson(obj);
      obj["run"] = m_runNumber;
      obj["collector"] = m_collectorName;
      obj["module"] = m_moduleName;
      obj["description"] = m_description;
      core::json reports = {};
      for(auto report : m_reports) {
        core::json jreport;
        report.second.toJson(jreport);
        reports[report.first] = jreport;
      }
      obj["reports"] = reports;
    }
    
    //-------------------------------------------------------------------------------------------------
// #if ROOT_VERSION_CODE >= ROOT_VERSION(6, 14, 0)
//     void OnlineElement::fromJson(const core::json &value) {
//       clear();
//       core::MonitorElement::fromJson(value);
//       m_runNumber = object.value<std::string>("run", 0);
//       m_collectorName = object.value<std::string>("collector", "");
//       m_moduleName = object.value<std::string>("module", "");
//       m_description = object.value<std::string>("description", "");
//       auto reports = object.value("reports", core::json(nullptr));
//       for(auto it = reports.begin() ; it != reports.end() ; it++) {
//         core::QReport report; report.fromJson(it.value());
//         m_reports[it.key()] = report;
//       }
//     }
// #endif
    //-------------------------------------------------------------------------------------------------

    core::StatusCode OnlineElement::toDevice(xdrstream::IODevice *device) const {
      // get initial device state
      auto pos = device->getPosition();
      // write base
      RETURN_RESULT_IF(core::STATUS_CODE_SUCCESS, !=, core::MonitorElement::toDevice(device));
      // write properties
      XDRSTREAM_SUCCESS_RESTORE(device->write(&m_runNumber), pos);
      XDRSTREAM_SUCCESS_RESTORE(device->write(&m_collectorName), pos);
      XDRSTREAM_SUCCESS_RESTORE(device->write(&m_moduleName), pos);
      XDRSTREAM_SUCCESS_RESTORE(device->write(&m_description), pos);
      core::json reports = {};
      for(auto report : m_reports) {
        core::json jreport;
        report.second.toJson(jreport);
        reports[report.first] = jreport;
      }
      const std::string qreportStr = reports.dump();
      XDRSTREAM_SUCCESS_RESTORE(device->write(&qreportStr), pos);
      return core::STATUS_CODE_SUCCESS;
    }
    
    //-------------------------------------------------------------------------------------------------

    core::StatusCode OnlineElement::fromDevice(xdrstream::IODevice *device) {
      reset(false);
      // get initial device state
      auto pos = device->getPosition();
      // read base
      RETURN_RESULT_IF(core::STATUS_CODE_SUCCESS, !=, core::MonitorElement::fromDevice(device));
      // read properties
      XDRSTREAM_SUCCESS_RESTORE(device->read(&m_runNumber), pos);
      XDRSTREAM_SUCCESS_RESTORE(device->read(&m_collectorName), pos);
      XDRSTREAM_SUCCESS_RESTORE(device->read(&m_moduleName), pos);
      XDRSTREAM_SUCCESS_RESTORE(device->read(&m_description), pos);
      std::string qreportStr;
      XDRSTREAM_SUCCESS_RESTORE(device->read(&qreportStr), pos);
      auto reports = core::json::parse(qreportStr);
      for(auto it = reports.begin() ; it != reports.end() ; it++) {
        core::QReport report; report.fromJson(it.value());
        m_reports[it.key()] = report;
      }
      return core::STATUS_CODE_SUCCESS;
    }

  }

} 

