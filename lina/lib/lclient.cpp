/***************************************************************************
 *   Copyright (C) 2003 by Tobias Glaesser                                 *
 *   tobi.web@gmx.de                                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <string.h>
#include <iostream>
#include <lclient.h>

using namespace Netxx;

LINA::Client::Client(const std::string& uri)
{
  connected = false;
  try
  {
    timeout.set_sec(500000);
    stream_client = new Stream(uri.c_str(),lina_port);
    Netxx::SockOpt sockopt(stream_client->get_socketfd());
    sockopt.set_non_blocking();
    connected = true;
    client_info = new ClientInfo();
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void LINA::Client::Reconnect()
{
  delete stream_client;
  stream_client = new Stream("localhost",lina_port);
}

void LINA::Client::Disconnect()
{
  if(connected)
  {
    SendPackage(LINA::NetPackage(LINA::NetDisconnect));
    delete stream_client;
    connected = false;
  }
}

void LINA::Client::ConnectTo(const std::string &uri)
{
  try
  {
  Disconnect();

  stream_client = new Stream(uri.c_str(),lina_port);
  Netxx::SockOpt sockopt(stream_client->get_socketfd());
  sockopt.set_non_blocking();
  connected = true;
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

LINA::Client::~ Client()
{
  Disconnect();
}

int LINA::Client::ReceivePackage(LINA::NetPackage& net_package)
{
if(connected)
  LINA::Network::ReceivePackage(*stream_client,net_package);
}

void LINA::Client::SendPackage(const LINA::NetPackage& net_package)
{
if(connected)
  LINA::Network::SendPackage(*stream_client,net_package);
}


