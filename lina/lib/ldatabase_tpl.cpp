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

template<class T>
void LDatabaseInterface::LazyGet(std::string& ref, const std::string& key)
{
  if(lazy_members.find(&ref) == lazy_members.end())
  {
    ref = LDB.Read(my_LID,my_section+key);

    lazy_members.insert(&ref);
  }
}

template<class T>
void LDatabaseInterface::LazyGet(std::string*& ref, const std::string& key)
{
  if(lazy_members.find(&ref) == lazy_members.end())
  {
    delete ref;
    ref = new T;
    *ref = LDB.Read(my_LID,my_section+key);
    lazy_members.insert(&ref);
  }
}

template<class T>
void LDatabaseInterface::LazyGet(T& ref, const std::string& key)
{
  if(lazy_members.find(&ref) == lazy_members.end())
  {
    LStringToDigit(ref,LDB.Read(my_LID,my_section+key),std::dec);

    lazy_members.insert(&ref);
  }
}

template<class T>
void LDatabaseInterface::LazyGet(T*& ref, const std::string& key)
{
  if(lazy_members.find(&ref) == lazy_members.end())
  {
    delete ref;
    ref = new T;
    *ref = LDB.Read(my_LID,my_section+key);
    lazy_members.insert(&ref);
  }
}

template<class T>
void LDatabaseInterface::LazySave(const T& ref, const std::string& key) const
{
  if(lazy_members.find(const_cast<T*>(&ref)) != lazy_members.end())
  {
    std::stringstream tmp;
    tmp << ref;
    LDB.Write(my_LID, my_section+key, tmp.str());
  }
}

template<class T>
void LDatabaseInterface::LazySave(const T*& ref, const std::string& key) const
{
  if(lazy_members.find(const_cast<T*>(&ref)) != lazy_members.end())
  {
    std::stringstream tmp;
    tmp << *ref;
    LDB.Write(my_LID, my_section+key, tmp.str());
  }
}

template<class T>
void LDatabaseInterface::LazySave(const std::string& ref, const std::string& key) const
{
  if(lazy_members.find(const_cast<T*>(&ref)) != lazy_members.end())
  {
    LDB.Write(my_LID, my_section+key, ref);
  }
}

template<class T>
void LDatabaseInterface::LazySave(const std::string*& ref, const std::string& key) const
{
  if(lazy_members.find(const_cast<T*>(&ref)) != lazy_members.end())
  {
    LDB.Write(my_LID, my_section+key, ref);
  }
}
