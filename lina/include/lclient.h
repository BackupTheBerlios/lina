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

#ifndef LCLIENT_H
#define LCLIENT_H

#include <set>
#include <iostream>
#include <lnetwork.h>
#include <lrand.h>

namespace LINA
{

  class Client : public Network
  {
  public:
    Client(const std::string &uri = "localhost");
    ~Client();
    void Reconnect();
    void Disconnect();
    void ConnectTo(const std::string &uri = "localhost");
    int ReceivePackage(NetPackage& net_package);
    void SendPackage(const NetPackage& net_package);
    bool IsConnected() { return connected; };
    void SetClientInfo(std::string nick);
    void HandleClientInfo(const NetPackage& netpackage);
    const ClientInfo* GetClientInfo() const { return client_info;};
    const std::set<ClientInfo>* GetClientsInformation() const { return &clients; };

  private:
    void SendClientInfo();
    Netxx::Timeout timeout;
    Netxx::Stream* stream_client;
    ClientInfo* client_info;
    std::set<ClientInfo> clients;
    bool connected;
  };
} // end LINA namespace

#endif //LCLIENT_H

