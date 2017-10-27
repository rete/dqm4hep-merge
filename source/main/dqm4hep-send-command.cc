  /// \file dqm4hep-send-command.cc
/*
 *
 * dqm4hep-send-command.cc source template automatically generated by a class generator
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


#include "dqm4hep/Client.h"

#include "json/json.h"

using namespace dqm4hep::net;

template <typename T>
void sendCommand(const Client &client, const std::string &name, const std::string &value);

// template <>
// inline void sendCommand<std::string>(const Client &client, const std::string &name, const std::string &value)
// {
//   client.sendCommand(name, Buffer(value.c_str(), value.size()), true);
// }

template <typename T>
inline void sendCommand(const Client &client, const std::string &name, const std::string &value)
{
  T tValue;
  std::stringstream ss;
  ss.str(value);

  if(!(ss >> tValue))
    throw;

  client.sendCommand(name, tValue, true);
}

int main(int argc, char **argv)
{
  if(argc < 4)
  {
    std::cout << "Usage : dqm4hep-send-command command type data" << std::endl;
    return 1;
  }

  std::string name(argv[1]);
  std::string type(argv[2]);

  Client client;

  std::string str;

  for(int i=3 ; i<argc ; i++)
    str += argv[i] + std::string(" ");

  str.pop_back();

  if(type == "float") sendCommand<float>(client, name, str);
  else if(type == "int")   sendCommand<int>(client, name, str);
  else if(type == "uint") sendCommand<unsigned int>(client, name, str);
  else if(type == "double") sendCommand<double>(client, name, str);
  else if(type == "short") sendCommand<short>(client, name, str);
  else if(type == "long") sendCommand<long>(client, name, str);
  else if(type == "ulong") sendCommand<unsigned long>(client, name, str);
  else if(type == "ullong") sendCommand<unsigned long long>(client, name, str);
  else if(type == "json") sendCommand<std::string>(client, name, str);
  else if(type == "string") sendCommand<std::string>(client, name, str);
  else throw "Command type error";

  return 0;
}
