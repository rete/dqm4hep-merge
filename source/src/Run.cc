/// \file DQMRun.cc
/*
 *
 * DQMRun.cc source template automatically generated by a class generator
 * Creation date : dim. mars 29 2015
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


#include "dqm4hep/Run.h"
#include "dqm4hep/StreamingHelper.h"

namespace dqm4hep {

  namespace core {

    Run::Run(int runNumber, const std::string &description, const std::string &detectorName) :
        m_runNumber(runNumber),
        m_startTime(dqm4hep::core::now()),
        m_endTime(),
        m_detectorName(detectorName),
        m_description(description),
        m_parametersMap()
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    Run::~Run()
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    StringVector Run::getParameterKeys() const
    {
      StringVector keys;

      for(auto iter = m_parametersMap.begin(), endIter = m_parametersMap.end() ;
          endIter != iter ; ++iter)
        keys.push_back( iter->first );

      return keys;
    }

    //-------------------------------------------------------------------------------------------------

    xdrstream::Status Run::stream(xdrstream::StreamingMode mode, xdrstream::IODevice *pDevice,
        xdrstream::xdr_version_t version)
    {
      if( xdrstream::XDR_READ_STREAM == mode )
      {
        XDR_STREAM( pDevice->read<int32_t>( & m_runNumber ) )

		    int64_t startTime;// = std::chrono::system_clock::to_time_t(m_startTime);
        int64_t endTime; //= std::chrono::system_clock::to_time_t(m_endTime);
        XDR_STREAM( pDevice->read<int64_t>( & startTime ) )
        XDR_STREAM( pDevice->read<int64_t>( & endTime ) )
        m_startTime = std::chrono::system_clock::from_time_t(startTime);
        m_endTime = std::chrono::system_clock::from_time_t(endTime);

        XDR_STREAM( pDevice->read( & m_detectorName ) )
        XDR_STREAM( pDevice->read( & m_description ) )
        XDR_STREAM( StreamingHelper::read( pDevice , m_parametersMap ))
      }
      else
      {
        XDR_STREAM( pDevice->write<int32_t>( & m_runNumber ) )

		    int64_t startTime = std::chrono::system_clock::to_time_t(m_startTime);
        int64_t endTime = std::chrono::system_clock::to_time_t(m_endTime);
        XDR_STREAM( pDevice->write<int64_t>( & startTime ) )
        XDR_STREAM( pDevice->write<int64_t>( & endTime ) )

        XDR_STREAM( pDevice->write( & m_detectorName ) )
        XDR_STREAM( pDevice->write( & m_description ) )
        XDR_STREAM( StreamingHelper::write( pDevice , m_parametersMap ))
      }

      return xdrstream::XDR_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    void Run::toJson(Json::Value &value) const
    {
      Json::Value::Int64 startTime = std::chrono::system_clock::to_time_t(m_startTime);
      Json::Value::Int64 endTime = std::chrono::system_clock::to_time_t(m_endTime);

      value["runNumber"] = m_runNumber;
      value["startTime"] = startTime;
      value["endTime"] = endTime;
      value["detector"] = m_detectorName;
      value["description"] = m_description;

      Json::Value parametersValue;

      for(const auto &parameter : m_parametersMap)
        parametersValue[parameter.first] = parameter.second;

      value["parameters"] = parametersValue;
    }

    //-------------------------------------------------------------------------------------------------

    void Run::fromJson(const Json::Value &value)
    {
      m_runNumber = value.get("runNumber", 0).asInt();
      int64_t startTime = value.get("startTime", 0).asInt64();
      int64_t endTime = value.get("endTime", 0).asInt64();
      m_startTime = std::chrono::system_clock::from_time_t(startTime);
      m_endTime = std::chrono::system_clock::from_time_t(endTime);
      m_detectorName = value.get("detector", "").asString();
      m_description = value.get("description", "").asString();

      m_parametersMap.clear();
      Json::Value parametersValue(value.get("parameters", Json::Value(Json::objectValue)));
      auto members = parametersValue.getMemberNames();

      for( const auto &parameter : members )
        m_parametersMap[parameter] = parametersValue[parameter].asString();
    }

  }

}
