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
using namespace LINA;

int main(int argc, char *argv[])
{

  ID eins("eins","one");
  ID eeeins("zwei","two");
  stringstream ss;
  ss << eins;
  ss >> eeeins;
  Debug(eeeins.Catalog());
  Debug(eeeins);

  Time a(2000,12,1,0,40,33);
  Time w(2000,12,1,0,30,33);   
  Time b(2000,12,2);
  Time c(2000,12,3);
  Time d(2000,12,4);
  Time k(2000,12,4,11,34,11);  
  Time z(2000,12,4,12,44,22);  
  Time e(2000,12,5);
  Time f(2000,12,6);
  
  set<Time> h;
  h.insert(k);  
  h.insert(z);
  h.insert(w);  
  h.insert(b);
  h.insert(d);
  h.insert(c);  
  h.insert(e);
  h.insert(a);
  h.insert(f);
  
  for(std::set<Time>::iterator it = h.begin(); it != h.end(); ++it)
  {
  Debug((*it));
  }
        
  Time test_time(2000,12,30);
  int mon;
  //cin>>mon;
  mon = Random().RandInt(1000);
  test_time.AddMonths(mon);
  Debug(test_time.Year());
  Debug(test_time.Month());
  Debug(test_time.Day());
  if(test_time.LeapYear(test_time.Year()))
  {
    Debug("true");
  }
 
  Stadium sta(ID("stadium","FCB"));
  Event tz(Time(2003,12,8),Time(2003,12,15),LEventID(ID("foo","bar"),3));
  
  sta.HandleEvent(tz);

    
  Debug(tz);
  
  DB.AddRoot("../../data/database/test/root1");
  DB.SetWriteFlag(1);
  
 Calendar cal(ID("special","aid"),Time(2003,12,10));
      
  cal.InsertEvent(tz);
    
  Event* leventptr;
  leventptr = cal.NextEvent();
  
  if(leventptr->EventLID().Catalog() == "foo")
  {
  sta.HandleEvent(*leventptr);
  }
  
  Debug(*leventptr);
  
  
  
  cal.Save();
    
  return 0;
}
