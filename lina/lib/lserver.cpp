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

#include <iostream>
#include <lserver.h>

using namespace Netxx;

LServer::LServer()
{
  try
  {
    timeout.set_sec(1);
    context.load_private_key("lina.pem");
    context.load_cert_chain("lina.pem");
    stream_server = new StreamServer(lina_port,timeout);
    buffer = new char[1024];
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

LServer::~LServer()
{
  delete stream_server;
  delete buffer;
}

void LServer::Run()
{
  HandleConnections();
}

void LServer::HandleConnections()
{
  try
  {
    for(;;)
    {
      Netxx::Peer client = stream_server->accept_connection();
      Netxx::SockOpt sockopt(client.get_socketfd());
      sockopt.set_non_blocking();
      clients.insert(client);

      if (!client)
      {
        std::cout << "timeout waiting for connection" << std::endl;
        continue;
      }

      Netxx::TLS::Stream client_stream(context, client.get_socketfd(),
                                       Netxx::TLS::Stream::mode_server, timeout);
      Netxx::signed_size_type bytes_read;

      std::cout << " connection from " << client << std::endl;

      char* buffer2 = NULL;
      unsigned int bytes = 0;
      while ( (bytes_read = client_stream.read(buffer, sizeof(buffer))) > 0)
      {
        unsigned int old = bytes;
        bytes += bytes_read;
        buffer2 = (char*) realloc(buffer2,bytes+1);
        memcpy(buffer2+old,buffer,bytes_read);
        std::cout<<bytes<<std::endl;
      }
      buffer2[bytes] = '\0';

      LNetMsg type = static_cast<LNetMsg>(buffer2[0]);
      std::string message = &buffer2[1];

      /* For testing only! */
      std::cout<< type << "-" << message << std::endl;

      delete buffer2;

      //client_stream.write(buffer, bytes_read);



      //std::cout << " client disconnected from server" << std::endl;

    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

}
