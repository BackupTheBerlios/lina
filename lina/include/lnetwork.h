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
#include <vector>

#include <netxx/netxx.h>
#include <lrand.h>

namespace LINA
{

  extern const Netxx::port_type lina_port;

  /* This is NOT final and only for testing purposes right now.*/

  /* LINA Network Package Type. */
  enum NetPT {

    /* Connection types. */
    NetConnect,
    NetDisconnect,

    /* Client information types. */
    NetClientInfo,
    NetRemoveClientInfo,

    /* Database requests. */
    NetDbRequest,

    /*Chat types. */
    NetChatMessage,

    /* Undefined type. */
    NetUndefined = -1

  };

  struct Buffer
  {  
    Buffer() {};
    //Copy constructor
    Buffer(const Buffer& buffer_) { buffer.assign(buffer_.buffer.begin(),buffer_.buffer.end()); };
    Buffer(std::string str) { buffer.resize(str.size() + 1); std::copy(str.c_str(),str.c_str()+str.size()+1,buffer.begin()); }
    Buffer(const char* buf, unsigned int size_) { buffer.resize(size_); std::copy(buf,buf+size_,buffer.begin());};
    Buffer(const void* buf, unsigned int size_) { buffer.resize(size_); std::copy(static_cast<const char*>(buf),static_cast<const char*>(buf)+size_,buffer.begin());};
    
    char* Get() { return &(*buffer.begin()); };
    const char* Get() const { return &(*buffer.begin()); };    
    void* Void() { return &(*buffer.begin()); };
    const void* Void() const { return &(*buffer.begin()); };
        
    Netxx::size_type Size() const { return buffer.size(); }
    Netxx::size_type* SizePointer() const {  NetxxSize() = buffer.size(); return &NetxxSize(); };
    void Resize(const Netxx::size_type& new_size) { buffer.resize(new_size);};
    
    Buffer &operator+= (const Buffer&);
    Buffer &operator= (const Buffer&);
      
    static Netxx::size_type& NetxxSize() {  static Netxx::size_type instance; return instance;};
    
  private:
    std::vector<char> buffer;
  };

  /* LINA Network Package. */
  class NetPackage
  {
  public:
    /* Constructor */
    NetPackage(NetPT type_ = NetUndefined) : type(type_) {};
    /* Constructor */
    NetPackage(NetPT type_, const Buffer& buffer_) : type(type_) , buffer(buffer_) {};
    ~NetPackage() {};

  public:
    Buffer buffer;
    NetPT type;
  };

  class ClientInfo
  {

  friend bool operator<(const ClientInfo& lhs, const ClientInfo& rhs) { return lhs.client_id < rhs.client_id; }
  friend bool operator>(const ClientInfo& lhs, const ClientInfo& rhs) { return lhs.client_id > rhs.client_id; }
  
  public:
    ClientInfo(std::string nick = "unknown") {nickname = nick; LINA::Random rand; client_id = rand.RandInt(); }
    //returns true, if the nickname changed
    bool SetNickname(const std::string& nick) { if(nick != nickname ) {nickname = nick; return true;} else { return false; } }
    bool SetID(int id) { client_id = id; }
    const std::string Nickname() const {return nickname; }
    int ClientID() const { return client_id; }
  private:
    std::string nickname;
    int client_id;
  };
  
  /* Base class for Server and Client. */
  class Network
  {
  public:
    Network() {};
    int ReceivePackage(Netxx::Stream& net_stream, NetPackage& net_package);
    void SendPackage(Netxx::Stream& net_stream, const NetPackage& net_package);
    void SendClientInfo(Netxx::Stream& net_stream, const ClientInfo& client_info, bool remove = false);

  protected:
    char* buffer;
    Netxx::signed_size_type byte_count;
  };

} // end LINA namespace

#endif //LNETWORK_H
