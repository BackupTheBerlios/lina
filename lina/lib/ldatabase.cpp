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

#include <ldatabase.h>

using namespace std;

LDatabase& LDatabaseInterface::LDB = LDatabase::Get();

bool operator<(const LDBPair& lhs, const LDBPair& rhs) { return ( lhs.second > rhs.second); };
bool operator>(const LDBPair& lhs, const LDBPair& rhs) { return ( lhs.second < rhs.second); };

bool operator<(const LID& lhs, const LID& rhs) { return ( lhs.Catalog()+lhs.Token() > rhs.Catalog()+rhs.Token()); };
bool operator>(const LID& lhs, const LID& rhs) { return ( lhs.Catalog()+lhs.Token() < rhs.Catalog()+rhs.Token()); };

bool operator==(const LID& lhs, const LID& rhs)
{
  return (lhs.Catalog() == rhs.Catalog() && lhs.Token() == rhs.Token() );
}

LID::LID(const string& lid_catalog, const string& lid_token) : catalog(lid_catalog),token(lid_token)
{}

LDatabase& LDatabase::Get()
{
  static LDatabase instance;
  return instance;
}

bool LDatabase::AddRoot(const string& db_root)
{
  ifstream file;
  //open the root-prio file
  file.open(((db_root+"/prio").c_str()));
  //to have "/" as database root would not be a good idea
  if(db_root != "/" && file.is_open() )
  {
    //get the priority of this root
    LDBPrio db_prio = static_cast<LDBPrio>(file.get() - 48);
    if ( db_prio < low || db_prio > high)
      db_prio = low;
    //finaly add this root to the database
    root_prio_set.insert(LDBPair(db_root,db_prio));
    return true;
  }
  else
    return false;
}

void LDatabase::RemoveRoot(const string& db_root)
{
  for(LDBPairSet::iterator it = root_prio_set.begin(); it != root_prio_set.end(); ++it)
  {
    if( (*it).first == db_root )
    {
      //Remove the database root
      root_prio_set.erase(it);
    }
  }
}

void LDatabase::Clear()
{
  //erase all data of root_prio_set
  root_prio_set.erase(root_prio_set.begin(),root_prio_set.end());
}

bool LDatabase::CreateRoot(const string& db_root, LDBPrio db_prio)
{
  //"/" as database root is no good idea
  if(db_root == "/")
    return false;
  //create directory for the new root
  if (mkdir(db_root.c_str(), 0755) == 0)
  {
    //create the priority file
    ofstream file;
    file.open(((db_root+"/prio").c_str()),ios::out);
    if(file.is_open())
    {
      file.put(db_prio+48);
      return true;
    }
    else
      return false;
  }
  else
  {
    printf("mkdir returned errno: %#s\n", strerror(errno));
    return false;
  }
}

const string LDatabase::Read(const LID& lid,const string& key) const
{

  LIDInfo lid_info = GetLIDInfo(lid);
  for( LDBPairSet::iterator it = lid_info.root_prio_set.begin(); it != lid_info.root_prio_set.end(); ++it )
  {
    gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");

    const short int MAXLINESIZE = 1024;

    string line;
    string data;
    bool multiline = false;
    for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != '\0' ; )
    {
      line=tmpline;
      line.erase(line.length()-1);
      if((line.find(key+":") == 0 || multiline) && line[0] != '#' )
      {

        if(!multiline)
        {
          data.insert(0,line,key.length()+1,line.length()-key.length());
        }
        else
        {
          data[data.length()-1]='\n';
          data.insert(data.length(),line,0,line.length());
        }

        if(data[data.length()-1] != '\\' || data[data.length()-2] == '\\' )
          break;
        else
          multiline = true;
      }

    }

    gzclose(file);

    return data;
  }
  return "";
}

int LDatabase::ReadArray(const LID& lid,const string& key,vector<string>& value_vector) const
{
  //get the plain value
  string value = Read(lid,key);

  int lastpos=0;
  int pos=0;
  //split it with '|' and push the parts to value_vector
  while((pos = value.find('|',lastpos)) != string::npos)
  {
    value_vector.push_back(value.substr(lastpos,pos-lastpos));
    lastpos=pos+1;
  }
  //the last value has to be handled seperate
  if(value.substr(lastpos,value.length()).length())
  {
    value_vector.push_back(value.substr(lastpos,value.length()-lastpos));
  }
}

int LDatabase::GetKeys(const LID& lid, set<string>& key_set) const
  {
    int keys=0;
    LIDInfo lid_info = GetLIDInfo(lid);
    for( LDBPairSet::iterator it = lid_info.root_prio_set.begin(); it != lid_info.root_prio_set.end(); ++it )
    {
      gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");

      const short int MAXLINESIZE = 1024;

      string line;
      string data;
      bool multiline = false;
      for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != '\0' ; )
      {
        line=tmpline;
        string::size_type pos = line.find(":",0);
        if(line[0] != '#' && (multiline || (pos != string::npos && (line[pos-1] != '\\' || line[pos-2] == '\\'))))
        {
          if(multiline == false)
          {
            key_set.insert(line.substr(0,pos));
            ++keys;
          }
          if(line[line.length()-3] != '\\' && line[line.length()-2] == '\\')
            multiline = true;
          else
            multiline = false;
        }
      }

      gzclose(file);
    }
    return keys;
  }

void LDatabase::Erase(const LID& lid,const string& key) const
{

  LDBPairSet::iterator it = root_prio_set.find(LDBPair("",write_flag));
  if ( it != root_prio_set.end() )
  {

    gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");

    const short int MAXLINESIZE = 1024;

    string line;
    string data;
    bool multiline = false;
    for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != '\0' ; )
    {
      line=tmpline;
      if(((line.find(key+":") == 0 || multiline) && line[0] != '#' ))
      {
        if(line[line.length()-3] != '\\' && line[line.length()-2] == '\\')
          multiline = true;
        else
          multiline = false;
      }
      else
      {
        data+=line;
      }
    }
    gzclose(file);

    if(data.length())
    {
      file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"w");
      gzwrite(file, const_cast<char*>(data.c_str()), data.length()-1);
      gzclose(file);
    }

  }
}

void LDatabase::Write(const LID& lid, const string& key, const string& value) const
{
  //erase the current appearances of key
  Erase(lid,key);

  LDBPairSet::iterator it = root_prio_set.find(LDBPair("",write_flag));
  if ( it != root_prio_set.end() )
  {
    //open the file for appending
    gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"ab");
    //create data and write it to the filestream
    string data = '\n' + key + ':' + value + '\n';
    gzwrite(file, const_cast<char*>(data.c_str()), data.length());
    //close
    gzclose(file);
  }
}

int LDatabase::IterateLIDs(const string& lid_catalog, set<LID>& lid_set)
{
  DIR   *dirStructP;
  dirent   *direntp;

  int lids=0;
  for(LDBPairSet::iterator it = root_prio_set.begin(); it != root_prio_set.end(); ++it)
  {
    if((dirStructP = opendir(((*it).first+"/"+lid_catalog).c_str())) != NULL)
    {
      while((direntp = readdir(dirStructP)) != NULL)
      {
        if ( direntp->d_type == DT_REG )
        {
          lid_set.insert(LID(lid_catalog,direntp->d_name));
          ++lids;
        }
      }
      closedir(dirStructP);
    }
    else
    {
      printf("opendir returned errno: %#x\n", errno);
    }
  }
  return lids;
}

int LDatabase::FindLIDs(const string& lid_catalog,const string& key,const string& value, set<LID>& lid_set)
{
  DIR   *dirStructP;
  dirent   *direntp;

  int lids=0;
  for(LDBPairSet::iterator it = root_prio_set.begin(); it != root_prio_set.end(); ++it)
  {
    if((dirStructP = opendir(((*it).first+"/"+lid_catalog).c_str())) != NULL)
    {
      while((direntp = readdir(dirStructP)) != NULL)
      {
        if ( direntp->d_type == DT_REG )
        {
          if ( Read(LID(lid_catalog,direntp->d_name),key) == value )
          {
            lid_set.insert(LID(lid_catalog,direntp->d_name));
            ++lids;
          }
        }
      }
      closedir(dirStructP);
    }
    else
    {
      printf("opendir returned errno: %#x\n", errno);
    }
  }

  return lids;
}

bool LDatabase::Fexists(const string& filename) const
{
  ifstream file;
  file.open(filename.c_str(), ios::in);
  if(!file)
  {
    file.close();
    return false;
  }
  else
  {
    file.close();
    return true;
  }
}

string LDatabase::FindTopPriorityRoot(const LID& lid) const
{
  for(LDBPairSet::iterator it = root_prio_set.begin(); it != root_prio_set.end(); ++it)
  {
    if( Fexists((*it).first+"/"+lid.Catalog()+"/"+lid.Token()) )
    {
      return (*it).first;
    }
  }
  return "";
}

//TODO - I'm pretty sure it doesnt work, but someone has to test this ;)
void LDatabase::Clean(const LID& lid) const
{
  LDBPairSet::iterator it = root_prio_set.begin();
  gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");

  // write file contents to cout
  const short int MAXLINESIZE = 1024;
  string line;
  string data;
  bool multiline = false;
  vector<string> keys;
  vector<string> values;
  int cnt=0;
  for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != '\0' ; )
  {
    line=tmpline;
    string::size_type pos = line.find(":",0);
    if(pos != string::npos && (line[pos-1] != '\\' || line[pos-2] == '\\'))
    {
      keys.push_back(line.substr(0,pos-1));
      gzclose(file);
      values.push_back(Read(lid,keys[cnt]));
      Erase(lid,keys[cnt]);
      file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");
      ++cnt;
    }
  }
  // close file
  gzclose(file);

  file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");
  for (int i=0; i != cnt ; ++i)
  {
    Write(lid,keys[i],values[i]);
  }

  gzclose(file);

}

LDatabase::LIDInfo LDatabase::GetLIDInfo(const LID& lid) const
{
  LIDInfo lid_info;
  for(LDBPairSet::iterator it = root_prio_set.begin(); it != root_prio_set.end(); ++it)
  {
    if( Fexists((*it).first+"/"+lid.Catalog()+"/"+lid.Token()) )
    {
      lid_info.root_prio_set.insert(LDBPair((*it).first,(*it).second));
    }
  }
  return lid_info;
}

void LDatabaseInterface::MakeLazy(void* address)
{
if(lazy_members.find(address) == lazy_members.end())
{
lazy_members.insert(address);
}
}
