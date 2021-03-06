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

LINA::Server::Server()
{
  try
  {
    timeout.set_usec(10000);
    /*context.load_private_key("lina.pem");
    context.load_cert_chain("lina.pem");*/
    stream_server = new StreamServer(lina_port,timeout);
    buffer = new char[1024];
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

LINA::Server::~Server()
{
  delete stream_server;
  delete buffer;
}

void LINA::Server::Run()
{
  HandleConnections();
}

void LINA::Server::HandleConnections()
{
  try
  {
    for(;;)
    {
      /* Accept connection with peer. */
      Netxx::Peer client = stream_server->accept_connection();
      /*Set the socket to non blocking. */
      Netxx::SockOpt sockopt(client.get_socketfd());
      sockopt.set_non_blocking();

      /* Check for timeouts. */
      if (!client)
      {
        /*std::cout<< "timeout" << std::endl;*/
      }
      else
      {
        Netxx::Stream* client_stream = new Netxx::Stream(client.get_socketfd());
        for(ClientMap::iterator it = clients.begin(); it != clients.end(); ++it)
        {
          LINA::Network::SendClientInfo(*client_stream,(*it).second.second);
        }
        clients.insert( ClientMap::value_type( client, std::pair<Netxx::Stream*, ClientInfo>(client_stream , ClientInfo()) ) );
        /* Who connected? IP:PORT */

        std::cout << " connection from " << client << std::endl;
      }
      /* Set up stream with the client. */
      /*      Netxx::TLS::Stream* client_stream = new Netxx::TLS::Stream(context, client.get_socketfd(),
                                             Netxx::TLS::Stream::mode_server, timeout);*/
      /* Counts the incoming bytes. */
      Netxx::signed_size_type bytes_read;
      for(ClientMap::iterator it = clients.begin(); it != clients.end(); ++it)
      {
        Netxx::Stream* client_stream = (*it).second.first;
        for(bool break_loop = false; !break_loop;)
        {

          LINA::NetPackage net_package;
          if(ReceivePackage(*client_stream, net_package) == -1)
            break;
	    
	  LINA::Buffer tmp;
          switch(net_package.type)
          {
          case LINA::NetDisconnect: /* Disconnect client. */
            for(ClientMap::iterator sit = clients.begin(); sit != clients.end(); ++sit)
            {
              if(sit == it)
                continue;

              Netxx::Stream* other_client_stream = (*sit).second.first;
              LINA::Network::SendClientInfo(*other_client_stream,(*it).second.second,true);
            }
            delete (*it).second.first;
            clients.erase(it);
            std::cout << " client disconnected from server" << std::endl;
            break_loop = true;
            break;
          case LINA::NetChatMessage:
            std::cout<<"Message Received:"<<net_package.buffer.Get()<< std::endl;
	    
	    tmp += LINA::Buffer("&lt;"+ (*it).second.second.Nickname() +"&gt; ");
	    tmp.Resize(tmp.Size()-1); 
	    tmp += net_package.buffer;
	    net_package.buffer = tmp;
	    
            for(ClientMap::iterator sit = clients.begin(); sit != clients.end(); ++sit)
            {
              Netxx::Stream* other_client_stream = (*sit).second.first;
              SendPackage(*other_client_stream, net_package);
            }
            break;
          case LINA::NetClientInfo:

            std::cout << (*it).second.second.Nickname();
	    //Make sure we don't share the same nick as someone else
	    for(ClientMap::iterator sit = clients.begin(); sit != clients.end(); ++sit)
            {
              if((*sit).second.second.Nickname() == std::string(net_package.buffer.Get()+sizeof(int)))
	      {
	      net_package.buffer.Resize(net_package.buffer.Size()-1);
	      net_package.buffer += LINA::Buffer("_");
	      sit = clients.begin();
	      }  
            }
            (*it).second.second.SetID(*(static_cast<int*>(net_package.buffer.Void())));
            (*it).second.second.SetNickname(net_package.buffer.Get()+sizeof(int));
            std::cout << " is now known as " << (*it).second.second.Nickname() << std::endl;

            for(ClientMap::iterator sit = clients.begin(); sit != clients.end(); ++sit)
            {
              Netxx::Stream* other_client_stream = (*sit).second.first;
              SendPackage(*other_client_stream, net_package);      
            }
            break;
          default:
            break;
          }

          /* For testing only! */
          /*std::cout<< type << "-" << message << std::endl;*/

        }
      }

      //client_stream.write(buffer, bytes_read);



      //std::cout << " client disconnected from server" << std::endl;
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

}
