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

#ifndef LOBJECTMANAGER_H
#define LOBJECTMANAGER_H

#include <ldatabase.h>

#include <map>
#include <set>

namespace LINA
{

  class DatabaseInterfaceProxyImpl : public DatabaseInterface
  {
  public:
    DatabaseInterfaceProxyImpl(const ID& lid,const std::string& section="") : DatabaseInterface(lid,section) {};
    virtual void Save() const {};
  };

  typedef std::set<DatabaseInterface*,DatabaseInterface::Less> DatabaseInterfaceSet;
  
  class ObjectManager
  {
  public:
    ~ObjectManager();
  
    static ObjectManager& Get();
    DatabaseInterface* GetObject(const ID& id);
    void InsertObject(DatabaseInterface* object);
    std::set<std::string> GetCatalogs();
    DatabaseInterfaceSet* GetCatalog(std::string catalog);


  private:
    /// Default constructor is private, so you can't generate objects.
  ObjectManager() {};

    std::map<std::string, DatabaseInterfaceSet > object_map;
  };

} //End of namespace LINA

#endif //LOBJECTMANAGER_H



