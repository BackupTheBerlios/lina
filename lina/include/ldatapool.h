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

#ifndef LDATAPOOL_H
#define LDATAPOOL_H

#include <set>
#include <string>

namespace LINA
{

  class DataPool
  {

  public:
    DataPool(const std::string& datafile, bool allow_repetition = true);
    ~DataPool();
    const std::string GetRandomData();
    const std::set<std::string>* GetData() { return &data; };
    int Size() { return data.size(); };
    const std::string& Name() { return name; }

  private:
    std::set<std::string> data;
    std::set<int>* used_indexs;
    std::string name;

  };

} // end LINA namespace

#endif //LDATAPOOL_H

