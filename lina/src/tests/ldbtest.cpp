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
#include <iterator>
#include <deque>

#include <ldefault.h>
#include <lmetrics.h>

using namespace std;


int main(int argc, char *argv[])
{

LID* bla = new LID("bla","foo");


cout<<"Test LDBPair:"<<endl;
    LDBPairSet ldbpairset;
    ldbpairset.insert(LDBPair("A",0));
    ldbpairset.insert(LDBPair("B",2));
    ldbpairset.insert(LDBPair("C",1));
    ldbpairset.insert(LDBPair("D",2));

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
  cout <<"\n"<< res << "MTD" << endl;
res = LDB.Read(LID("player","ANDRZIEG"),"testdata");
  cout <<"\n"<< res << endl;


LDB.Erase(LID("player","ANDRZIEG"),"testdata");
LDB.Write(LID("player","ANDRZIEG"),"testdata","crazy\\\ntest");


LDatabase::LIDInfo info = LDB.GetLIDInfo(LID("player","ANDRZIEG"));

  for(LDBPairSet::iterator it = info.root_prio_set.begin(); it != info.root_prio_set.end(); ++it)
  {
      cout<<"Root: "<<(*it).first<<endl<<"With prio: "<<(*it).second<<endl;
  }

LDBPairSet::iterator it = info.root_prio_set.find(LDBPair("",1));
if(it != info.root_prio_set.end())
{
cout<<"Mid: "<<(*it).first;
}

vector<int> int_v;
int_v.push_back(123);
int_v.push_back(321);
int_v.push_back(456);
LDB.WriteArray(LID("player","extrem"),"cool",int_v);

int sizes = LDB.ReadArraySize(LID("player","extrem"),"cool");
LDebug("3",sizes);

int woa = 1232;
LDB.Write(LID("player","extrem"),"uncool",woa);

int int_vr;
LDB.Read(LID("player","extrem"),"uncool",int_vr);
LDebug(woa,int_vr);


vector<float> isset;
LDB.ReadArray<float>(LID("player","extrem"),"cool",isset);

   for(vector<float>::iterator it = isset.begin(); it != isset.end(); ++it)
   {
   cout<<(*it)<<endl;
   }
   
   
LPoint anti_plan;
LDB.Read(LID("player","extrem"),"fly",anti_plan);
LDebug(anti_plan);
LPoint advanced(4, 1. / 2. );
LDB.Write(LID("player","extrem"),"fly",advanced);
   
 /*while (!isset.empty() )
 {
   cout <<"the last element is: "<< isset.front() << endl; //front() returns 
                                                        //the top-most element
  isset.pop(); //remove the top-most element
 }*/
   
float suppa[3];

/*LDB.ReadArray<float>(LID("player","extrem"),"cool",suppa);

   cout<<suppa[0]<<endl;
   cout<<suppa[1]<<endl;
   cout<<suppa[2]<<endl;   */
   
delete bla;

  return EXIT_SUCCESS;
}
