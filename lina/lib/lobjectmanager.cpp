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

#include <lobjectmanager.h>

LINA::ObjectManager::~ObjectManager()
{
  for(std::map<std::string, LINA::DatabaseInterfaceSet >::iterator it = object_map.begin(); it != object_map.end(); ++it)
    {
      for(DatabaseInterfaceSet::iterator sit = (*it).second.begin(); sit != (*it).second.end(); ++sit)
        {
	delete (*sit);
        }

    }
}

LINA::ObjectManager& LINA::ObjectManager::Get()
{
  static LINA::ObjectManager instance;
  return instance;
}

LINA::DatabaseInterface* LINA::ObjectManager::GetObject(const LINA::ID& id)
{
  LINA::DatabaseInterface* pid = new LINA::DatabaseInterfaceProxyImpl(id);
  return (*object_map[id.Catalog()].find(pid));
}

void LINA::ObjectManager::InsertObject(LINA::DatabaseInterface* object)
{
  object_map[object->GetID().Catalog()].insert(object);
}

std::set<std::string> LINA::ObjectManager::GetCatalogs()
{
std::set<std::string> catalogs;
  for(std::map<std::string, LINA::DatabaseInterfaceSet >::iterator it = object_map.begin(); it != object_map.end(); ++it)
    {
     catalogs.insert((*it).first);
    }
}

LINA::DatabaseInterfaceSet* LINA::ObjectManager::GetCatalog(std::string catalog)
{
return &object_map[catalog];
}


    
