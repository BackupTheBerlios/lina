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

#ifndef LSERVER_H
#define LSERVER_H

#include <map>
#include <lnetwork.h>
#include <lclient.h>

namespace LINA
{

  class Server : public Network
  {
  public:
    Server();
    ~Server();
    void Run();

  private:
    void HandleConnections();

    Netxx::StreamServer* stream_server;
    Netxx::Timeout timeout;
    
    typedef std::map<Netxx::Peer,std::pair<Netxx::Stream*, ClientInfo> > ClientMap;
    ClientMap clients;
  };

} // end LINA namespace

#endif //LSERVER_H


