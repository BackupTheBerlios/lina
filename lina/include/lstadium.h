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

#ifndef LSTADIUM_H
#define LSTADIUM_H

#include <ldatabase.h>
#include <lrange.h>
#include <lcalendar.h>

namespace LINA {

class Tribune : public DatabaseInterface
{
public:
  Tribune(const ID& lid,const std::string& section="") : DatabaseInterface(lid,section) {};
  virtual void Save() const;
  void SetCondition(const int set_condition) { MakeLazy(&condition); condition = set_condition; };
  int Condition() {  LazyGet("condition",condition); return condition; };
  void IncreaseCapacity(const int inc_capacity) { MakeLazy(&condition); capacity += inc_capacity; };
  int Capacity() { LazyGet("capacity",capacity); return capacity; };

private:
  RangeC condition;
  int capacity;
  int capacity_limit;
  bool roofed;
  bool seats;
};

///Represents a sport stadium
class Stadium : public DatabaseInterface , EventInterface
{
public:
  Stadium(const ID& lid);
  virtual ~Stadium() {};
  virtual void Save() const;
  void SetName(const std::string& set_name) { MakeLazy(&name); name = set_name; };
  std::string Name() { LazyGet("name",name); return name; };
  Event& TESTMakeDuper()
  {
    Event ev(Time(2003,12,8),Time(2003,12,10),LEventID(my_LID,2));
  }
  virtual void HandleEvent(const Event& levent)
  {
    switch(levent.EventID())
    {
    case 2: Debug("Stadion -2- Action!"); break;
    case 3: Debug("Stadion -3- ction!"); break;
    case 4: Debug("Stadion -4- Action!"); break;
    default: Debug("Stadion -default- NETT!"); break;
    }

  }

private:
  struct AdmissionCharge
  {
  }
  admission_charge;
  std::string name;
  RangeC popularity;
  int max_spectators;
};

} // end LINA namespace

#endif //LSTADIUM_H
