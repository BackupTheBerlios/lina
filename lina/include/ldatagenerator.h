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

#ifndef LDATAGENERATOR_H
#define LDATAGENERATOR_H

#include <set>
#include <string>

namespace LINA
{

  class DataGenerator
  {

  public:
    DataGenerator(const std::string& datafile, bool allow_repetition = true);
    ~DataGenerator();
    const std::string GetRandomData();
    const std::set<std::string>* GetData() { return &data; };
    int Size() { return data.size(); };

  private:
    std::set<std::string> data;
    std::set<int>* used_indexs;

  };

} // end LINA namespace

#endif //LDATAGENERATOR_H

