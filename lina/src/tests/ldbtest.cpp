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
using namespace LINA;

int main(int argc, char *argv[])
{

ID* bla = new ID("bla","foo");


cout<<"Test DBPair:"<<endl;
    DBPairSet ldbpairset;
    ldbpairset.insert(DBPair("A",0));
    ldbpairset.insert(DBPair("B",2));
    ldbpairset.insert(DBPair("C",1));
    ldbpairset.insert(DBPair("D",2));

Debug("B\nC\nA","");
    for(DBPairSet::iterator it = ldbpairset.begin(); it != ldbpairset.end(); ++it)
   {
   cout<<(*it).first<<endl;
   }



DB.AddRoot("../../data/database/test/root1");
DB.AddRoot("../../data/database/test/root2");
DB.AddRoot("../../data/database/test/root3");

cout<<"\nTest database creation:"<<endl;
if(DB.CreateRoot("/var/tmp/testdatabase"))
cout<<"PASSED!"<<endl;
else
cout<<"FAILED!"<<endl;

ID lidtest("player","ANDRZIEG");

cout<<"Test database iteration:"<<endl;
set<ID> testvec;
DB.IterateIDs(lidtest.Catalog(),testvec);
for(set<ID>::iterator it = testvec.begin(); it != testvec.end(); ++it)
{
cout<<(*it).Token()<<endl;
}

cout<<"Test ID finding:"<<endl;
testvec.clear();
DB.FindIDs(lidtest.Catalog(),"testdata","hallo wie gehts",testvec);
for(set<ID>::iterator it = testvec.begin(); it != testvec.end(); ++it)
{
cout<<(*it).Token()<<endl;
}

string res = DB.Read(ID("player","ANDRZIEG"),"mehrtestdata");
  cout <<"\n"<< res << "MTD" << endl;
res = DB.Read(ID("player","ANDRZIEG"),"testdata");
  cout <<"\n"<< res << endl;


DB.Erase(ID("player","ANDRZIEG"),"testdata");
DB.Write(ID("player","ANDRZIEG"),"testdata","crazy\\\ntest");


Database::IDInfo info = DB.GetIDInfo(ID("player","ANDRZIEG"));

  for(DBPairSet::iterator it = info.root_prio_set.begin(); it != info.root_prio_set.end(); ++it)
  {
      cout<<"Root: "<<(*it).first<<endl<<"With prio: "<<(*it).second<<endl;
  }

DBPairSet::iterator it = info.root_prio_set.find(DBPair("",1));
if(it != info.root_prio_set.end())
{
cout<<"Mid: "<<(*it).first;
}

vector<int> int_v;
int_v.push_back(123);
int_v.push_back(321);
int_v.push_back(456);
DB.WriteArray(ID("player","extrem"),"cool",int_v);

int sizes = DB.ReadArraySize(ID("player","extrem"),"cool");
Debug("3",sizes);

int woa = 1232;
DB.Write(ID("player","extrem"),"uncool",woa);

int int_vr;
DB.Read(ID("player","extrem"),"uncool",int_vr);
Debug(woa,int_vr);


vector<float> isset;
DB.ReadArray<float>(ID("player","extrem"),"cool",isset);

   for(vector<float>::iterator it = isset.begin(); it != isset.end(); ++it)
   {
   cout<<(*it)<<endl;
   }
   
   
Point anti_plan;
DB.Read(ID("player","extrem"),"fly",anti_plan);
Debug(anti_plan);
Point advanced(4, 1. / 2. );
DB.Write(ID("player","extrem"),"fly",advanced);
   
 /*while (!isset.empty() )
 {
   cout <<"the last element is: "<< isset.front() << endl; //front() returns 
                                                        //the top-most element
  isset.pop(); //remove the top-most element
 }*/
   
float suppa[3];

/*DB.ReadArray<float>(ID("player","extrem"),"cool",suppa);

   cout<<suppa[0]<<endl;
   cout<<suppa[1]<<endl;
   cout<<suppa[2]<<endl;   */
   
delete bla;

  return EXIT_SUCCESS;
}
