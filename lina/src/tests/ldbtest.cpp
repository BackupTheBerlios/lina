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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>

#include <ldefault.h>

using namespace std;

int main(int argc, char *argv[])
{

LID* bla = new LID("bla","foo");


cout<<"Test LDBPair:"<<endl;
    LDBPairSet ldbpairset;
    ldbpairset.insert(LDBPair("A",low));
    ldbpairset.insert(LDBPair("B",high));
    ldbpairset.insert(LDBPair("C",mid));
    ldbpairset.insert(LDBPair("D",high));

LDebug("B\nC\nA","");
    for(LDBPairSet::iterator it = ldbpairset.begin(); it != ldbpairset.end(); ++it)
   {
   cout<<(*it).first<<endl;
   }



LDB.AddRoot("../../data/database/test/root1");
LDB.AddRoot("../../data/database/test/root2");
LDB.AddRoot("../../data/database/test/root3");

cout<<"\nTest database creation:"<<endl;
if(LDB.CreateRoot("/var/tmp/testdatabase"))
cout<<"PASSED!"<<endl;
else
cout<<"FAILED!"<<endl;

LID lidtest("player","ANDRZIEG");

cout<<"Test database iteration:"<<endl;
set<LID> testvec;
LDB.IterateLIDs(lidtest.Catalog(),testvec);
for(set<LID>::iterator it = testvec.begin(); it != testvec.end(); ++it)
{
cout<<(*it).Token()<<endl;
}

cout<<"Test LID finding:"<<endl;
testvec.clear();
LDB.FindLIDs(lidtest.Catalog(),"testdata","hallo wie gehts",testvec);
for(set<LID>::iterator it = testvec.begin(); it != testvec.end(); ++it)
{
cout<<(*it).Token()<<endl;
}

string res = LDB.Read(LID("player","ANDRZIEG"),"mehrtestdata");
  cout <<"\n"<< res << endl;
res = LDB.Read(LID("player","ANDRZIEG"),"testdata");
  cout <<"\n"<< res << endl;


LDB.Erase(LID("player","ANDRZIEG"),"testdata");
LDB.Write(LID("player","ANDRZIEG"),"testdata","crazy\\\ntest");


LDatabase::LIDInfo info = LDB.GetLIDInfo(LID("player","ANDRZIEG"));

  for(LDBPairSet::iterator it = info.root_prio_set.begin(); it != info.root_prio_set.end(); ++it)
  {
      cout<<"Root: "<<(*it).first<<endl<<"With prio: "<<(*it).second<<endl;
  }

LDBPairSet::iterator it = info.root_prio_set.find(LDBPair("",mid));
if(it != info.root_prio_set.end())
{
cout<<"Mid: "<<(*it).first;
}

  return EXIT_SUCCESS;
}
