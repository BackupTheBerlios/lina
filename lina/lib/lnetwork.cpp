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
#include <lnetwork.h>

const Netxx::port_type LINA::lina_port = 1368;

LINA::Buffer& LINA::Buffer::operator+= (const LINA::Buffer &rv)
{
  if(rv.buffer.empty())
    return *this;

  buffer.resize(buffer.size()+rv.buffer.size());
  std::copy(rv.buffer.begin(),rv.buffer.end()-1,buffer.end()-rv.buffer.size());
  return *this;
}

int LINA::Network::ReceivePackage(Netxx::Stream& net_stream, LINA::NetPackage& net_package)
{
  /* The first bytes of a datapackage are expected to be one int,
     that tells us about the overall length of the package. */
  Netxx::SockOpt sockopt(net_stream.get_socketfd());
  sockopt.set_non_blocking();
  if (!((byte_count = net_stream.read(&Buffer::NetxxSize(), sizeof(int))) == sizeof(int)))
  {

    /* Not enough bytes received! */
    return -1;
  }

  if (!((byte_count = net_stream.read(&net_package.type, sizeof(LINA::NetPT))) /*== sizeof(LINA::NetPT)*/ != 0))
  {
    /* Not enough bytes received! */
    return -1;
  }

  net_package.buffer.Resize(Buffer::NetxxSize());
  unsigned int bytes;
  for( bytes = 0; /*() > -1 &&*/  bytes < net_package.buffer.Size(); )
  {
    byte_count = net_stream.read(net_package.buffer.Get() + bytes, net_package.buffer.Size()-bytes);
    if(byte_count > 0)
      bytes += byte_count;

    /*unsigned int old = bytes;
    bytes += bytes_read;
    buffer2 = (char*) realloc(buffer2,bytes+1);
    memcpy(buffer2+old,buffer,bytes_read);
    std::cout<<bytes<<std::endl;*/
  }

  /*char* buffe = new char[1024];
  for( bytes = 0; byte_count = net_stream.read(buffe, 1024) > 0; )
  { /* Emptying. (Maybe not neccessary) * /
  }*/
}

void LINA::Network::SendPackage(Netxx::Stream& net_stream, const LINA::NetPackage& net_package)
{
  /*
  char* tmp = new char[sizeof(int)+sizeof(LINA::NetPT)+net_package.buffer.Size()];
  std::memcpy(tmp,(net_package.buffer.Size()),sizeof(int));
  std::memcpy(tmp+sizeof(int),&net_package.type,sizeof(LINA::NetPT));
  std::memcpy(tmp+sizeof(int)+sizeof(LINA::NetPT),net_package.buffer.Get(),net_package.buffer.Size());
    /*if ( (byte_count = net_stream.write(&net_package.size, sizeof(int))) != sizeof(int))
      return;
    if ( (byte_count = net_stream.write(&net_package.type, sizeof(LINA::NetPT))) != sizeof(LINA::NetPT))
      return;* /
    if ( (byte_count = net_stream.write(tmp, sizeof(int)+sizeof(LINA::NetPT)+net_package.buffer.Size())) <= 0)
      return;
      
  delete tmp;
  */
  Buffer tmp(net_package.buffer.SizePointer(),sizeof(Netxx::size_type));
  tmp += Buffer(&net_package.type, sizeof(LINA::NetPT));
  tmp += net_package.buffer;

  if ( (byte_count = net_stream.write(tmp.Get(), sizeof(int)+sizeof(LINA::NetPT)+net_package.buffer.Size())) <= 0)
    return;
}

void LINA::Network::SendClientInfo(Netxx::Stream& net_stream, const LINA::ClientInfo& client_info, bool remove)
{
  int client_id_tmp = client_info.ClientID();
  LINA::NetPackage client_info_package( remove ? LINA::NetRemoveClientInfo : LINA::NetClientInfo, Buffer( &client_id_tmp  , sizeof(int) ) );
  client_info_package.buffer += Buffer(client_info.Nickname());
  SendPackage(net_stream,client_info_package);
}




