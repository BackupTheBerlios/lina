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

#include <ldatabase.h>

using namespace std;

LDatabase dbtest;

int main(int argc, char *argv[])
{

cout<<"Test LDBPair:"<<endl;
    LDBPairSet ldbpairset;
    ldbpairset.insert(LDBPair("A",low));
    ldbpairset.insert(LDBPair("B",high));
    ldbpairset.insert(LDBPair("C",mid));
    ldbpairset.insert(LDBPair("D",high));

    for(LDBPairSet::iterator it = ldbpairset.begin(); it != ldbpairset.end(); ++it)
   {
   cout<<(*it).first<<endl;
   }
cout<<"Expected output is:\nB\nC\nA"<<endl;

dbtest.AddRoot("../../data/database/test/root1");
dbtest.AddRoot("../../data/database/test/root2");
dbtest.AddRoot("../../data/database/test/root3");

cout<<"\nTest database creation:"<<endl;
if(dbtest.CreateRoot("/var/tmp/testdatabase"))
cout<<"PASSED!"<<endl;
else
cout<<"FAILED!"<<endl;

LID lidtest("player","ANDRZIEG");

cout<<"Test database iteration:"<<endl;
vector<LID> testvec;
dbtest.IterateLIDs(lidtest.Catalog(),testvec);
for(vector<LID>::iterator it = testvec.begin(); it != testvec.end(); ++it)
{
cout<<(*it).Token()<<endl;
}

cout<<"Test LID finding:"<<endl;
testvec.clear();
dbtest.FindLIDs(lidtest.Catalog(),"testdata","hallo wie gehts",testvec);
for(vector<LID>::iterator it = testvec.begin(); it != testvec.end(); ++it)
{
cout<<(*it).Token()<<endl;
}

string res = dbtest.Read(LID("player","ANDRZIEG"),"mehrtestdata");
  cout <<"\n"<< res << endl;
res = dbtest.Read(LID("player","ANDRZIEG"),"testdata");
  cout <<"\n"<< res << endl;

dbtest.Erase(LID("player","ANDRZIEG"),"testdata");
dbtest.Write(LID("player","ANDRZIEG"),"testdata","crazy\\\ntest");

LDatabase::LID_info info = dbtest.GetLIDInfo(LID("player","ANDRZIEG"));

  for(LDBPairSet::iterator it = info.root_prio_set.begin(); it != info.root_prio_set.end(); ++it)
  {
      cout<<"Root: "<<(*it).first<<endl<<"With prio: "<<(*it).second<<endl;
  }

LDBPairSet::iterator it = info.root_prio_set.find(LDBPair("",mid));
cout<<"Mid: "<<(*it).first;


  return EXIT_SUCCESS;
}
