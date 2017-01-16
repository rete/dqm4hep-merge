/// \file RequestHandler.cc
/*
 *
 * RequestHandler.cc source template automatically generated by a class generator
 * Creation date : sam. d�c. 3 2016
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


#include "dqm4hep/RequestHandler.h"

namespace dqm4hep {

  namespace net {

    BaseRequestHandler::BaseRequestHandler(Server *pServer, const std::string &type, const std::string &name) :
        m_type(type),
        m_name(name),
        m_fullName(getFullRequestHandlerName(m_type, m_name)),
        m_pServer(pServer)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    BaseRequestHandler::~BaseRequestHandler()
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    const std::string &BaseRequestHandler::getType() const
    {
      return m_type;
    }

    //-------------------------------------------------------------------------------------------------

    const std::string &BaseRequestHandler::getName() const
    {
      return m_name;
    }

    //-------------------------------------------------------------------------------------------------

    const std::string &BaseRequestHandler::getFullName() const
    {
      return m_fullName;
    }

    //-------------------------------------------------------------------------------------------------

    Server *BaseRequestHandler::getServer() const
    {
      return m_pServer;
    }

    //-------------------------------------------------------------------------------------------------

    std::string BaseRequestHandler::getFullRequestHandlerName(const std::string &type, const std::string &name)
    {
      return ("/dqm4hep/" + type + "/" + name);
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

  }

}
