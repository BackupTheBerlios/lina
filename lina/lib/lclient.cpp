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

LClient::LClient()
{
  try
  {
    stream_client = new TLS::Stream(context,"localhost",lina_port);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

LClient::~ LClient()
{
  delete stream_client;
}

void LClient::SendMsg(const LNetMsg type, const std::string& message)
{
char* buffer = new char[message.size()+1];
buffer[0] = type;
strcpy(&buffer[1],message.c_str());
std::cout<<type<< "-" << message <<std::endl;
if ( (byte_count = stream_client->write(buffer, message.size()+1)) <= 0)
std::cout<<"byte_count <= 0"<<std::endl;

/*byte_count = stream_client->read(buffer, sizeof(buffer));*/
delete buffer;
}


