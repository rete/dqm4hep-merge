/// \file Client.cc
/*
 *
 * Client.cc source template automatically generated by a class generator
 * Creation date : dim. d�c. 4 2016
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
#include "dqm4hep/Client.h"
#include "dqm4hep/RequestHandler.h"

namespace dqm4hep {

  namespace net {

    Client::Client()
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    Client::~Client()
    {
      for(auto iter = m_serviceHandlerMap.begin(), endIter = m_serviceHandlerMap.end() ; endIter != iter ; ++iter)
        delete iter->second;

      m_serviceHandlerMap.clear();
    }

    //-------------------------------------------------------------------------------------------------

    void Client::queryServerInfo(const std::string &serverName, Json::Value &serverInfo) const
    {
      this->sendRequest(serverName, "info", Json::Value(), serverInfo);
    }

    //-------------------------------------------------------------------------------------------------

    void Client::sendRequest(const std::string &type, const std::string &name, const Json::Value &request) const
    {
      std::string rpcName(BaseRequestHandler::getFullRequestHandlerName(type, name));
      std::string emptyJson("{}");
      DimRpcInfo rpcInfo(const_cast<char*>(rpcName.c_str()), const_cast<char*>(emptyJson.c_str()));

      // Json::Value message;
      Json::Value message;
      message["response"] = false;
      message["request"] = request;
      Json::FastWriter writer;
      std::string messageStr(writer.write(message));

      rpcInfo.setData(const_cast<char*>(messageStr.c_str()));
    }

    //-------------------------------------------------------------------------------------------------

    bool Client::hasSubscribed(const std::string &type, const std::string &name) const
    {
      const std::string fullName(BaseService::getFullServiceName(type, name));
      return (m_serviceHandlerMap.end() != m_serviceHandlerMap.find(fullName));
    }

  }

}
