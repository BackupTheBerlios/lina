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

#ifndef LDATABASE_H
#define LDATABASE_H

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <zlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <cstdio>
#include <cerrno>

/// LINA ID
/** This class stores a unique ID,
    wich can't be changed during the runtime. */
class LID
{
public:
  /// Constructor
  LID(const std::string& lid_catalog, const std::string& lid_token);

  const std::string ID() const { return catalog+token; };
  const std::string Catalog() const { return catalog; };
  const std::string Token() const { return token; };

private:
  // Constructor without arguments
  // Is declared private, because every LID has to be identified,
  // when it is declared.
  LID();

  std::string catalog;
  std::string token;
};



/// Global operator== for LID.
bool operator==(const LID& lhs, const LID& rhs);

/// Enum representing priorities.
enum LDBPrio{low,mid,high};

/// Pair for a database root and its priority.
struct LDBPair
{
  LDBPair(const std::string& p_first, const LDBPrio& p_second) : first(p_first),second(p_second) {};
  std::string first;
  LDBPrio second;
  friend bool operator<(const LDBPair& lhs, const LDBPair& rhs);
  friend bool operator>(const LDBPair& lhs, const LDBPair& rhs);
};

/// Set of LDBPair.
typedef std::set<LDBPair> LDBPairSet;

/// LINA Database
/** This object can do several actions with a database,
    like reading and writing data.*/
class LDatabase
{
public:
  static LDatabase& Get();

  /// Read value from LID of the database.
  /** Read the key's value from the database.*/
  const std::string Read(const LID& lid, const std::string& key) const;

  /// Read value from LID of the database.
  /** Read the key's value from the database.*/
  int ReadArray(const LID& lid, const std::string& key, std::vector<std::string>& value_vector) const;

  /// Erase a key from a LID.
  /** Erases a key completly in a certain LID.*/
  void Erase(const LID& lid, const std::string& key) const;

  /// Write values to a LID of the database.
  /** Write the key and value to the database.*/
  void Write(const LID& lid, const std::string& key, const std::string& value) const;

  /// Write values to a LID of the database.
  /** Write the key and value to the database.*/
  template<class IT>
  void WriteArray(const LID& lid, const std::string& key, IT begin, const IT end) const
  {
    std::string value;
    while(begin!=end)
    {
      value += (*begin) + '|';
      begin++;
    }
    Write(lid,key,value);
  }

  /// Write values to a LID of the database.
  /** Write the key and value to the database.*/
  template<class Cont>
  void WriteArray(const LID& lid, const std::string& key, const Cont& cont) const { WriteArray(lid,key,cont.begin(),cont.end()); }

  //  forkLID(const LID& lid, LDBPrio from, LDBPrio to=high) const;

  /// Get all keys in a LID
  /** Gets all keys and pushs them into key_set.
      Returns the number of keys.*/
  int GetKeys(const LID& lid, std::set<std::string>& key_set) const;

  /// Iterates through the LIDs.
  /** Fills a set<LID> with all LIDs in a catalog*/
  int IterateLIDs(const std::string& lid_catalog, std::set<LID>& lid_set);

  /// Find LIDs.
  /** Fills a set<LID> with all LIDs,
      that have the right key and value.*/
  int FindLIDs(const std::string& lid_catalog,const std::string& key,const std::string& value, std::set<LID>& lid_set);

  /// Add a database root.
  /** Returns false if the database root is invalid. */
  bool AddRoot(const std::string& db_root);

  /// Remove a database root.
  void RemoveRoot(const std::string& db_root);

  /// Create a new database root.
  /** Returns false if it failes. */
  bool CreateRoot(const std::string& db_root,enum LDBPrio=low);

  /// Clear the database roots
  void Clear();

  /// Set write_flag
  /** The write_flag defines to which database priority
      data may be written currently.*/
  void SetWriteFlag(enum LDBPrio prio=high) { write_flag=prio; };

  /// Information about a LID.
  /** Contains information about a LID.*/
  struct LIDInfo
  {
    /// This LDBPairSet contains the roots and priorities,
    /// where a LID is found in the database.
    LDBPairSet root_prio_set;
  };

  /// Get LIDInfo
  /** Return a LIDInfo about a certain LID.*/
  LIDInfo GetLIDInfo(const LID& lid) const;

  /// Special get digit method for pointers.
  /** It is thought for lazy fetching.*/
  template<class T>
  void PtrGetDigit(const LID& lid,const std::string& key, T*& ptr , T def=-1)
  {
    if(!ptr)
    {
      ptr = new T;
      std::string tmp = Read(lid, key);
      if(!tmp.empty())
        *ptr = T(atof(tmp.c_str()));
      else
        *ptr = def;
    }
  }
  /// Special get string method for pointers.
  /** It is thought for lazy fetching.*/
  void PtrGetString(const LID& lid , const std::string& key , std::string*& ptr )
  {
    if(!ptr)
    {
      ptr = new std::string;
      *ptr = Read(lid, key);
    }
  }
  /// Special save digit method for pointers.
  /** Could be used in conjunction with PtrGetDigit.*/
  template<class T>
  void PtrSaveDigit(const LID& lid , const std::string& key , T* const& ptr) const
  {
    if(ptr)
    {
      std::stringstream tmp;
      tmp << *ptr;
      Write(lid, key, tmp.str());
    }
  }
  /// Special save string method for pointers.
  /** Could be used in conjunction with PtrGetString.*/
  void PtrSaveString(const LID& lid,const std::string& key,std::string* const& ptr) const
  {
    if(ptr)
    {
      Write(lid, key, *ptr);
    }
  }

private:
  /// Default constructor.
  LDatabase() : write_flag(high) {};
  // Clean a lid from unparsed data TODO
  void Clean(const LID& lid) const;
  // Test if a file exists.
  bool Fexists(const std::string& filename) const;
  // Finds the highest DBRoot with the LID lid.
  std::string FindTopPriorityRoot(const LID& lid) const;

  // Contains the database roots.
  // Only one per priority!
  LDBPairSet root_prio_set;

  // This is the write_flag.
  // It defines to which priority
  // writing is currently allowed.
  LDBPrio write_flag;
};

/// Interface class to the database
class LDatabaseInterface
{
public:
  /// Constructor.
  LDatabaseInterface(const LID& lid) : my_LID(lid) {};
  /// Destructor.
  virtual ~LDatabaseInterface() {};
  /// Save method.
  /** This method has to be implemented by all derived classes.
      It is supposed to save the current data of the object to
      the database.*/
  virtual void Save() const = 0;
  /// Returns the LID of the object.
  LID GetLID() const { return my_LID; }

protected:
  /// Wrapper for LDatabase::PtrGetDigit
  template<class T>
  void PtrGetDigit(const std::string& key, T*& ptr, T def=-1)
  {  LDB.PtrGetDigit(my_LID, key, ptr, def);  }
  /// Wrapper for LDatabase::PtrGetString
  void PtrGetString(const std::string& key, std::string*& ptr)
  {  LDB.PtrGetString(my_LID, key, ptr); }
  /// Wrapper for LDatabase::PtrSaveDigit
  template<class T>
  void PtrSaveDigit(const std::string& key,T* const& ptr) const
    {  LDB.PtrSaveDigit(my_LID,key,ptr); };
  /// Wrapper for LDatabase::PtrSaveString
  void PtrSaveString(const std::string& key,std::string* const& ptr) const
    {  LDB.PtrSaveString(my_LID, key, ptr);  };

  /// Static reference to LDatabase object.
  static LDatabase& LDB;

  /// My LID.
  LID my_LID;
};

#endif //LDATABASE_H
