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

#include <iostream>
#include <cstdlib>

#include <ldefault.h>

using namespace std;

int main(int argc, char *argv[])
{

  LID eins("eins","one");
  LID eeeins("zwei","two");
  stringstream ss;
  ss << eins;
  ss >> eeeins;
  LDebug(eeeins.Catalog());
  LDebug(eeeins);

  LTime a(2000,12,1,0,40,33);
  LTime w(2000,12,1,0,30,33);   
  LTime b(2000,12,2);
  LTime c(2000,12,3);
  LTime d(2000,12,4);
  LTime k(2000,12,4,11,34,11);  
  LTime z(2000,12,4,12,44,22);  
  LTime e(2000,12,5);
  LTime f(2000,12,6);
  
  set<LTime> h;
  h.insert(k);  
  h.insert(z);
  h.insert(w);  
  h.insert(b);
  h.insert(d);
  h.insert(c);  
  h.insert(e);
  h.insert(a);
  h.insert(f);
  
  for(std::set<LTime>::iterator it = h.begin(); it != h.end(); ++it)
  {
  LDebug((*it));
  }
        
  LTime test_time(2000,12,30);
  int mon;
  //cin>>mon;
  mon = LRand().RandInt(1000);
  test_time.AddMonths(mon);
  LDebug(test_time.Year());
  LDebug(test_time.Month());
  LDebug(test_time.Day());
  if(test_time.LeapYear(test_time.Year()))
  {
    LDebug("true");
  }
 
  LStadium sta(LID("stadium","FCB"));
  LEvent tz(LTime(2003,12,8),LTime(2003,12,15),LEventID(LID("foo","bar"),3));
  
  sta.HandleEvent(tz);

    
  LDebug(tz);
  
  LDB.AddRoot("../../data/database/test/root1");
  LDB.SetWriteFlag(1);
  
 LCalendar cal(LID("special","aid"),LTime(2003,12,10));
      
  cal.InsertEvent(tz);
    
  LEvent* leventptr;
  leventptr = cal.NextEvent();
  
  if(leventptr->EventLID().Catalog() == "foo")
  {
  sta.HandleEvent(*leventptr);
  }
  
  LDebug(*leventptr);
  
  
  
  cal.Save();
    
  return 0;
}
