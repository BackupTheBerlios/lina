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

#ifndef LNETWORK_H
#define LNETWORK_H

#include <iostream>
#include <netxx/tls/netxx.h>

extern const Netxx::port_type lina_port;

/* This is NOT final and only for testing purposes right now.*/

/* LINA Network Package Type. */
enum LNetPT {

  LNetConnect = 0,
  LNetDisconnect = 1,
  LNetMessage = 2,
  LNetUndefined = -1

};

/* LINA Network Package. */
class LNetPackage
{
public:
  LNetPackage(LNetPT type_ = LNetUndefined) : type(type_), buffer(NULL), size(0) {};
  LNetPackage(LNetPT type_, std::string buffer_) : type(type_) { size = buffer_.size()+1; buffer = new char[size]; std::memcpy(buffer,buffer_.c_str(),size); std::cout<<"BUFFER:"<<buffer<<std::endl;};
  ~LNetPackage() { delete buffer; };

public:
  char* buffer;
  unsigned int size;
  LNetPT type;
};

/* Base class for LServer and LClient. */
class LNetwork
{
public:
  LNetwork() {};
  int ReceivePackage(Netxx::Stream& net_stream, LNetPackage& net_package);
  void SendPackage(Netxx::Stream& net_stream, const LNetPackage& net_package);

protected:
  char* buffer;
  Netxx::signed_size_type byte_count;
};

#endif //LNETWORK_H
