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

LINA::Database& LINA::DatabaseInterface::DB = LINA::Database::Get();

bool LINA::operator<(const LINA::DBPair& lhs, const LINA::DBPair& rhs) { return ( lhs.second > rhs.second); };
bool LINA::operator>(const LINA::DBPair& lhs, const LINA::DBPair& rhs) { return ( lhs.second < rhs.second); };

bool LINA::operator<(const LINA::ID& lhs, const LINA::ID& rhs) { return ( lhs.catalog + lhs.token < rhs.catalog + rhs.token); };
bool LINA::operator>(const LINA::ID& lhs, const LINA::ID& rhs) { return ( lhs.catalog + lhs.token > rhs.catalog + rhs.token); };

bool LINA::operator<(const LINA::DatabaseInterface& lhs, const LINA::DatabaseInterface& rhs) { return ( lhs.my_LID  < rhs.my_LID ); };
bool LINA::operator>(const LINA::DatabaseInterface& lhs, const LINA::DatabaseInterface& rhs) { return ( lhs.my_LID  > rhs.my_LID ); };

bool operator==(const LINA::ID& lhs, const LINA::ID& rhs)
{
  return (lhs.Catalog() == rhs.Catalog() && lhs.Token() == rhs.Token() );
}

std::ostream& LINA::operator<<(std::ostream& os, const LINA::ID& rv)
{
  return os << rv.catalog << " " << rv.token;
}

std::istream& LINA::operator>>(std::istream& is, LINA::ID& rv)
{
  return is >> rv.catalog >> rv.token;
}

LINA::ID::ID(const string& lid_catalog, const string& lid_token) : catalog(lid_catalog),token(lid_token)
{}

LINA::ID::ID(const LINA::ID& lid) : catalog(lid.catalog),token(lid.token)
{}

LINA::Database& LINA::Database::Get()
{
  static LINA::Database instance;
  return instance;
}

bool LINA::Database::AddRoot(const string& db_root)
{
  ifstream file;
  //open the root-prio file
  file.open(((db_root+"/prio").c_str()));
  //to have "/" as database root would not be a good idea
  if(db_root != "/" && file.is_open() )
  {
    //get the priority of this root
    char tmp[10];
    file.getline(tmp,10);
    LINA::DBPrio db_prio;
    LINA::StringToDigit(db_prio,tmp);
    if ( db_prio < 0 )
      db_prio = 0;
    //finaly add this root to the database
    root_prio_set.insert(LINA::DBPair(db_root,db_prio));
    return true;
  }
  else
    return false;
}

void LINA::Database::RemoveRoot(const string& db_root)
{
  for(LINA::DBPairSet::iterator it = root_prio_set.begin(); it != root_prio_set.end(); ++it)
  {
    if( (*it).first == db_root )
    {
      //Remove the database root
      root_prio_set.erase(it);
    }
  }
}

void LINA::Database::RemoveRoot(LINA::DBPrio prio)
{
  for(LINA::DBPairSet::iterator it = root_prio_set.begin(); it != root_prio_set.end(); ++it)
  {
    if( (*it).second == prio )
    {
      //Remove the database root
      root_prio_set.erase(it);
    }
  }
}

void LINA::Database::Clear()
{
  //erase all data of root_prio_set
  root_prio_set.erase(root_prio_set.begin(),root_prio_set.end());
}

bool LINA::Database::CreateRoot(const string& db_root, LINA::DBPrio db_prio)
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

const string LINA::Database::Read(const LINA::ID& lid,const string& key) const
{

  IDInfo lid_info = GetIDInfo(lid);
  for( LINA::DBPairSet::iterator it = lid_info.root_prio_set.begin(); it != lid_info.root_prio_set.end(); ++it )
  {
    gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");

    const short int MAXLINESIZE = 1024;

    string line;
    string data;
    bool multiline = false;
    for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != Z_NULL ; )
    {
      line=tmpline;
      line.erase(line.length()-1);
      if(line.find(key+":") == 0 || multiline)
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

void LINA::Database::Read(const LINA::ID& lid,const string& key, string& value) const
{

  IDInfo lid_info = GetIDInfo(lid);
  for( LINA::DBPairSet::iterator it = lid_info.root_prio_set.begin(); it != lid_info.root_prio_set.end(); ++it )
  {
    gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");

    const short int MAXLINESIZE = 1024;

    string line;
    bool multiline = false;
    for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != Z_NULL ; )
    {
      line=tmpline;
      line.erase(line.length()-1);
      if(line.find(key+":") == 0 || multiline)
      {

        if(!multiline)
        {
          value.insert(0,line,key.length()+1,line.length()-key.length());
        }
        else
        {
          value[value.length()-1]='\n';
          value.insert(value.length(),line,0,line.length());
        }

        if(value[value.length()-1] != '\\' || value[value.length()-2] == '\\' )
          break;
        else
          multiline = true;
      }

    }

    gzclose(file);
  }
}

void LINA::Database::Read(const LINA::ID& lid,const string& key, stringstream& value) const
{

  IDInfo lid_info = GetIDInfo(lid);
  for( LINA::DBPairSet::iterator it = lid_info.root_prio_set.begin(); it != lid_info.root_prio_set.end(); ++it )
  {
    gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");

    const short int MAXLINESIZE = 1024;

    string tmp;
    string line;
    bool multiline = false;
    for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != Z_NULL ; )
    {
      line=tmpline;
      line.erase(line.length()-1);
      if(line.find(key+":") == 0 || multiline)
      {

        if(!multiline)
        {
          tmp.insert(0,line,key.length()+1,line.length()-key.length());
        }
        else
        {
          tmp[tmp.length()-1]='\n';
          tmp.insert(tmp.length(),line,0,line.length());
        }

        if(tmp[tmp.length()-1] != '\\' || tmp[tmp.length()-2] == '\\' )
          break;
        else
          multiline = true;
      }

    }

    value<<tmp;
    gzclose(file);
  }
}

void LINA::Database::ReadArray(const LINA::ID& lid,const string& key,vector<string>& value_vector) const
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

int LINA::Database::ReadArraySize(const LINA::ID& lid,const string& key) const
{
  //get the plain value
  string value = Read(lid,key);

  int i=0;
  int pos=0;
  //split it with '|'
  while((pos = value.find('|',pos)) != string::npos)
  {
    pos+=1;
    ++i;
  }
  return i;
}

int LINA::Database::GetKeys(const LINA::ID& lid, set<string>& key_set) const
  {
    int keys=0;
    IDInfo lid_info = GetIDInfo(lid);
    for( LINA::DBPairSet::iterator it = lid_info.root_prio_set.begin(); it != lid_info.root_prio_set.end(); ++it )
    {
      gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");

      const short int MAXLINESIZE = 1024;

      string line;
      string data;
      bool multiline = false;
      for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != Z_NULL ; )
      {
        line=tmpline;
        string::size_type pos = line.find(":",0);
        if(multiline || (pos != string::npos && (line[pos-1] != '\\' || line[pos-2] == '\\')))
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

void LINA::Database::ReadPlainText(const LINA::ID& lid, std::string& text) const
{
  IDInfo lid_info = GetIDInfo(lid);
  for( LINA::DBPairSet::iterator it = lid_info.root_prio_set.begin(); it != lid_info.root_prio_set.end(); ++it )
  {
    gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");

    const short int MAXLINESIZE = 1024;

    for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != Z_NULL ; )
    {
      text += tmpline;
    }
    gzclose(file);
  }
}

void LINA::Database::Erase(const LINA::ID& lid,const string& key) const
{

  LINA::DBPairSet::iterator it = root_prio_set.find(LINA::DBPair("",write_flag));
  if ( it != root_prio_set.end() )
  {

    gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");

    const short int MAXLINESIZE = 1024;

    string line;
    string data;
    bool multiline = false;
    bool clean = false;
    for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != Z_NULL ; )
    {
      line=tmpline;
      if(!clean)
      {
        if(line.find(":") == string::npos)
          continue;
        else
          clean = true;
      }
      if(line.find(key+":") == 0 || multiline)
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
      gzwrite(file, const_cast<char*>(data.c_str()), data.length());
      gzclose(file);
    }

  }
}


void LINA::Database::Write(const LINA::ID& lid, const string& key, const string& value) const
{
  //erase the current appearances of key
  Erase(lid,key);

  LINA::DBPairSet::iterator it = root_prio_set.find(LINA::DBPair("",write_flag));
  if ( it != root_prio_set.end() )
  {
    //open the file for appending
    gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"ab");
    //create data and write it to the filestream
    string data = key + ':' + value + '\n';
    gzwrite(file, const_cast<char*>(data.c_str()), data.length());
    //close
    gzclose(file);
  }
}


void LINA::Database::Write(const LINA::ID& lid, const string& key, const stringstream& value) const
{
  //erase the current appearances of key
  Erase(lid,key);

  LINA::DBPairSet::iterator it = root_prio_set.find(LINA::DBPair("",write_flag));
  if ( it != root_prio_set.end() )
  {
    //open the file for appending
    gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"ab");
    //create data and write it to the filestream
    string data = key + ':' + value.str() + '\n';
    gzwrite(file, const_cast<char*>(data.c_str()), data.length());
    //close
    gzclose(file);
  }
}

int LINA::Database::IterateIDs(const string& lid_catalog, set<LINA::ID>& lid_set)
{
  DIR   *dirStructP;
  dirent   *direntp;

  int lids=0;
  for(LINA::DBPairSet::iterator it = root_prio_set.begin(); it != root_prio_set.end(); ++it)
  {
    if((dirStructP = opendir(((*it).first+"/"+lid_catalog).c_str())) != NULL)
    {
      while((direntp = readdir(dirStructP)) != NULL)
      {
        if ( direntp->d_type == DT_REG )
        {
          lid_set.insert(LINA::ID(lid_catalog,direntp->d_name));
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

int LINA::Database::FindIDs(const string& lid_catalog,const string& key,const string& value, set<LINA::ID>& lid_set)
{
  DIR   *dirStructP;
  dirent   *direntp;

  int lids=0;
  for(LINA::DBPairSet::iterator it = root_prio_set.begin(); it != root_prio_set.end(); ++it)
  {
    if((dirStructP = opendir(((*it).first+"/"+lid_catalog).c_str())) != NULL)
    {
      while((direntp = readdir(dirStructP)) != NULL)
      {
        if ( direntp->d_type == DT_REG )
        {
          if ( Read(LINA::ID(lid_catalog,direntp->d_name),key) == value )
          {
            lid_set.insert(LINA::ID(lid_catalog,direntp->d_name));
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

bool LINA::Database::Fexists(const string& filename) const
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

string LINA::Database::FindTopPriorityRoot(const LINA::ID& lid) const
{
  for(LINA::DBPairSet::iterator it = root_prio_set.begin(); it != root_prio_set.end(); ++it)
  {
    if( Fexists((*it).first+"/"+lid.Catalog()+"/"+lid.Token()) )
    {
      return (*it).first;
    }
  }
  return "";
}

//TODO - I'm pretty sure it doesnt work, but someone has to test this ;)
void LINA::Database::Clean(const LINA::ID& lid) const
{
  LINA::DBPairSet::iterator it = root_prio_set.begin();
  gzFile file = gzopen((((*it).first+"/"+lid.Catalog()+"/"+lid.Token()).c_str()),"rb");

  // write file contents to cout
  const short int MAXLINESIZE = 1024;
  string line;
  string data;
  bool multiline = false;
  vector<string> keys;
  vector<string> values;
  int cnt=0;
  for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != Z_NULL ; )
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

LINA::Database::IDInfo LINA::Database::GetIDInfo(const LINA::ID& lid) const
{
  IDInfo lid_info;
  for(LINA::DBPairSet::iterator it = root_prio_set.begin(); it != root_prio_set.end(); ++it)
  {
    if( Fexists((*it).first+"/"+lid.Catalog()+"/"+lid.Token()) )
    {
      lid_info.root_prio_set.insert(LINA::DBPair((*it).first,(*it).second));
    }
  }
  return lid_info;
}

void LINA::DatabaseInterface::MakeLazy(void* address)
{
  if(lazy_members.find(address) == lazy_members.end())
  {
    lazy_members.insert(address);
  }
}
