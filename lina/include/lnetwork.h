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

namespace LINA {

extern const Netxx::port_type lina_port;

/* This is NOT final and only for testing purposes right now.*/

/* LINA Network Package Type. */
enum NetPT {

  /* Connection types. */
  NetConnect,
  NetDisconnect,
  
  /* Client information types. */
  NetClientInfo,
  
  /* Database requests. */
  NetDbRequest,
  
  /*Chat types. */
  NetChatMessage,
  
  /* Undefined type. */
  NetUndefined = -1

};

struct Buffer
{
Buffer() : buffer(NULL) , size(0) {};
Buffer(std::string str) : size(str.size()+1) , buffer(new char[size]) { std::memcpy(buffer,str.c_str(),size); }
Buffer(char* buf, unsigned int size_) : size(size_) ,buffer(new char[size]) { std::memcpy(buffer,buf,size); };
~Buffer() { delete buffer; };

void Allocate(unsigned size) { buffer = new char[size]; };
char* Copy() { return (new char[size]); };
char* Get() { return buffer; };
const char* GetConst() const { return buffer; };
unsigned Size() const { return size; };

const unsigned* PSize() const { return &size; };

private:
char* buffer;
unsigned size;
};

/* LINA Network Package. */
class NetPackage
{
public:
  /* Constructor */
  NetPackage(NetPT type_ = NetUndefined) : type(type_), buffer() {};
  /* Constructor */
  NetPackage(NetPT type_, std::string buffer_) : type(type_) , buffer(buffer_) {};
  /* Constructor */
  NetPackage(NetPT type_, char* buffer_, unsigned int size) : type(type_), buffer(buffer_,size) {};
  ~NetPackage() {};

public:
  Buffer buffer;
  NetPT type;
};

/* Base class for Server and Client. */
class Network
{
public:
  Network() {};
  int ReceivePackage(Netxx::Stream& net_stream, NetPackage& net_package);
  void SendPackage(Netxx::Stream& net_stream, const NetPackage& net_package);

protected:
  char* buffer;
  Netxx::signed_size_type byte_count;
};

} // end LINA namespace

#endif //LNETWORK_H
