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

template<class T> inline void Database::Write(const ID& lid, const std::string& key, const T& value) const
{
  std::stringstream ss;
  ss<<value;
  Write(lid,key,ss);
}

template<class IT>
void Database::WriteArray(const ID& lid, const std::string& key, IT begin, const IT end) const
{
  std::stringstream value;
  if(begin!=end)
  {
    value << (*begin);
    ++begin;
  }
  while(begin!=end)
  {
    value << '|' << (*begin);
    ++begin;
  }
  Write(lid,key,value);
}

template<class T> inline void Database::Read(const ID& lid, const std::string& key, T& value) const
{
  std::stringstream ss;
  Read(lid,key,ss);
  ss>>value;
}

template<class T,class Cont> void Database::ReadArray(const ID& lid, const std::string& key, Cont& cont) const
{
  //get the plain value
  std::string value = Read(lid,key);
  Debug(value);

  std::insert_iterator<Cont> it(cont,cont.end());
  int lastpos=0;
  int pos=0;
  T tmp;
  //split it with '|' and push the parts to value_vector
  while((pos = value.find('|',lastpos)) != std::string::npos)
  {
    std::stringstream ss;
    ss << value.substr(lastpos,pos-lastpos);
    ss >> tmp;
    it = tmp;
    lastpos=pos+1;
  }
  //the last value has to be handled seperate
  if(value.substr(lastpos,value.length()).length())
  {
    //value_vector.push_back(value.substr(lastpos,value.length()-lastpos));
    std::stringstream ss;
    ss << value.substr(lastpos,value.length()-lastpos);
    ss >> tmp;
    it = tmp;
  }
}

template<class T>
void DatabaseInterface::LazyGet(const std::string& key, std::string& ref)
{
  if(lazy_members.find(&ref) == lazy_members.end())
  {
    DB.Read(my_LID,my_section+key,ref);

    lazy_members.insert(&ref);
  }
}

template<class T>
void DatabaseInterface::LazyGet(const std::string& key, std::string*& ref)
{
  if(lazy_members.find(&ref) == lazy_members.end())
  {
    delete ref;
    ref = new T;
    DB.Read(my_LID,my_section+key,*ref);
    lazy_members.insert(&ref);
  }
}

template<class T>
void DatabaseInterface::LazyGet(const std::string& key, T& ref)
{
  if(lazy_members.find(&ref) == lazy_members.end())
  {
    DB.Read(my_LID,my_section+key,ref);

    lazy_members.insert(&ref);
  }
}

template<class T>
void DatabaseInterface::LazyGet(const std::string& key, T*& ref)
{
  if(lazy_members.find(&ref) == lazy_members.end())
  {
    delete ref;
    ref = new T;
    DB.Read(my_LID,my_section+key,*ref);
    lazy_members.insert(&ref);
  }
}

template<class T>
void DatabaseInterface::LazySave(const std::string& key, const T& ref) const
{
  if(lazy_members.find(const_cast<T*>(&ref)) != lazy_members.end())
  {
    DB.Write(my_LID, my_section+key, ref);
  }
}

template<class T>
void DatabaseInterface::LazySave(const std::string& key, const T*& ref) const
{
  if(lazy_members.find(const_cast<T*>(&ref)) != lazy_members.end())
  {
    DB.Write(my_LID, my_section+key, *ref);
  }
}

template<class T>
void DatabaseInterface::LazySave(const std::string& key, const std::string& ref) const
{
  if(lazy_members.find(const_cast<T*>(&ref)) != lazy_members.end())
  {
    DB.Write(my_LID, my_section+key, ref);
  }
}

template<class T>
void DatabaseInterface::LazySave(const std::string& key, const std::string*& ref) const
{
  if(lazy_members.find(const_cast<T*>(&ref)) != lazy_members.end())
  {
    DB.Write(my_LID, my_section+key, *ref);
  }
}

template<class IT>
void DatabaseInterface::LazySaveArray(const std::string& key,const void* ref, IT begin, IT end) const
{
  if(lazy_members.find(ref) != lazy_members.end())
  {
    DB.WriteArray(my_LID, my_section+key, begin, end);
  }
}

template<class Cont>
void DatabaseInterface::LazySaveArray(const std::string& key, const Cont& ref) const
{
  if(lazy_members.find(const_cast<Cont*>(&ref)) != lazy_members.end())
  {
    DB.WriteArray(my_LID, my_section+key, ref.begin(), ref.end());
  }
}

