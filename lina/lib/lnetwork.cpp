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

const Netxx::port_type lina_port = 1368;

int LNetwork::ReceivePackage(Netxx::Stream& net_stream, LNetPackage& net_package)
{
      /* The first bytes of a datapackage are expected to be one int,
         that tells us about the overall length of the package. */
	 Netxx::SockOpt sockopt(net_stream.get_socketfd());
	 sockopt.set_non_blocking();
          if (!((byte_count = net_stream.read(&net_package.size, sizeof(int))) == sizeof(int)))
          {
	  
	    /* Not enough bytes received! */
            return -1;
         }
	 
	 if (!((byte_count = net_stream.read(&net_package.type, sizeof(LNetPT))) /*== sizeof(LNetPT)*/ != 0))
          {
            /* Not enough bytes received! */
            return -1;
          }
	  	  
	  net_package.buffer = new char[net_package.size];
	  unsigned int bytes;
          for( bytes = 0; /*() > -1 &&*/  bytes < net_package.size; )
          {
	  byte_count = net_stream.read(net_package.buffer + bytes, net_package.size-bytes);
	  if(byte_count > 0)
	  bytes += byte_count;

            /*unsigned int old = bytes;
            bytes += bytes_read;
            buffer2 = (char*) realloc(buffer2,bytes+1);
            memcpy(buffer2+old,buffer,bytes_read);
            std::cout<<bytes<<std::endl;*/
          }
	  
	  char* buffe = new char[1024];
	  for( bytes = 0; byte_count = net_stream.read(buffe, 1024) > 0; )
          { /* Emptying. (Maybe not neccessary) */
	  }
}

void LNetwork::SendPackage(Netxx::Stream& net_stream, const LNetPackage& net_package)
{
char* tmp = new char[sizeof(int)+sizeof(LNetPT)+net_package.size];
std::memcpy(tmp,&net_package.size,sizeof(int));
std::memcpy(tmp+sizeof(int),&net_package.type,sizeof(LNetPT));
std::memcpy(tmp+sizeof(int)+sizeof(LNetPT),net_package.buffer,net_package.size);
  /*if ( (byte_count = net_stream.write(&net_package.size, sizeof(int))) != sizeof(int))
    return;
  if ( (byte_count = net_stream.write(&net_package.type, sizeof(LNetPT))) != sizeof(LNetPT))
    return;*/
  if ( (byte_count = net_stream.write(tmp, sizeof(int)+sizeof(LNetPT)+net_package.size)) <= 0)
    return;
    
delete tmp;

}

