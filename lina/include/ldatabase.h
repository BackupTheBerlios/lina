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
#include <lconvert.h>
#include <lutility.h>

/// LINA ID
/** This class stores a unique ID,
    wich can't be changed during the runtime. */
class LID
{
  friend std::ostream &operator<<(std::ostream&, const LID&);
  friend std::istream &operator>>(std::istream& is, LID&);

  friend bool operator<(const LID& lhs, const LID& rhs);
  friend bool operator>(const LID& lhs, const LID& rhs);
  
public:
  /// Constructor
  LID(const std::string& lid_catalog, const std::string& lid_token);
  /// Copy constructor
  LID(const LID& lid);  
  /// Destructor
  ~LID() {  };

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
typedef int LDBPrio;

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
  void Read(const LID& lid, const std::string& key, std::string& value) const;

  /// Read value from LID of the database.
  /** Read the key's value from the database.*/
  void Read(const LID& lid, const std::string& key, std::stringstream& value) const;

  /// Read value from LID of the database.
  /** Read the key's value from the database.*/
  template<class T> void Read(const LID& lid, const std::string& key, T& value) const;

  /// Read array from LID of the database.
  /** Read the key's array from the database.*/
  void ReadArray(const LID& lid, const std::string& key, std::vector<std::string>& value_vector) const;

  /// Read array from LID of the database.
  /** Read the key's array from the database.*/
  template<class T,class Cont> void ReadArray(const LID& lid, const std::string& key, Cont& cont) const;

  /// Read size of array from LID of the database.
  /** Read the key's array size from the database.*/
  int ReadArraySize(const LID& lid, const std::string& key) const;

  /// Read the plain text of all database-files related to this LID
  /** This method is thought for debugging issues.*/
  void ReadPlainText(const LID& lid, std::string& text) const;
  
  /// Erase a key from a LID.
  /** Erases a key completly in a certain LID.*/
  void Erase(const LID& lid, const std::string& key) const;

  /// Write values to a LID of the database.
  /** Write the key and value to the database.*/
  void Write(const LID& lid, const std::string& key, const std::string& value) const;

  /// Write values to a LID of the database.
  /** Write the key and value to the database.*/
  void Write(const LID& lid, const std::string& key, const std::stringstream& value) const;

  /// Write array to a LID of the database.
  /** Write the key and array to the database.*/
  template<class T> void Write(const LID& lid, const std::string& key, const T& value) const;

  /// Write array to a LID of the database.
  /** Write the key and array to the database.*/
  template<class IT>
  void WriteArray(const LID& lid, const std::string& key, IT begin, const IT end) const;

  /// Write array to a LID of the database.
  /** Write the key and array to the database.*/
  template<class Cont>
  void WriteArray(const LID& lid, const std::string& key, const Cont& cont) const { WriteArray(lid,key,cont.begin(),cont.end()); }

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
  
  /// Remove a database root.
  void RemoveRoot(LDBPrio prio);

  /// Create a new database root.
  /** Returns false if it failes. */
  bool CreateRoot(const std::string& db_root, LDBPrio=0);

  /// Clear the database roots
  void Clear();

  /// Set write_flag
  /** The write_flag defines to which database priority
      data may be written currently.*/
void SetWriteFlag(LDBPrio prio) { write_flag=prio; };

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

private:
  /// Default constructor.
  LDatabase() : write_flag(2) {};
  // Clean a lid from unparseable data TODO
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
  LDatabaseInterface(const LID& lid,const std::string& section="") : my_LID(lid) , my_section(section)
  { if(!my_section.empty()){ my_section+="."; } }
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
  std::set<void*> lazy_members;

  ///Marks a member as lazy. This means that the LazyGet methods won't try
  ///to read its value from the database.
  void MakeLazy(void* address);

  ///Reads data of the database, if ref isn't marked as lazy.
  template<class T>
  void LazyGet(const std::string& key, std::string& ref);

  ///Reads data of the database, if ref isn't marked as lazy.
  template<class T>
  void LazyGet(const std::string& key, std::string*& ref);

  ///Reads data of the database, if ref isn't marked as lazy.
  template<class T>
  void LazyGet(const std::string& key, T& ref);

  ///Reads data of the database, if ref isn't marked as lazy.
  template<class T>
  void LazyGet(const std::string& key, T*& ref);

  ///Writes data to the database, if ref is marked as lazy.
  template<class T>
  void LazySave(const std::string& key, const T& ref) const;

  ///Writes data to the database, if ref is marked as lazy.
  template<class T>
  void LazySave(const std::string& key, const T*& ref) const;

  ///Writes data to the database, if ref is marked as lazy.
  template<class T>
  void LazySave(const std::string& key, const std::string& ref) const;

  ///Writes data to the database, if ref is marked as lazy.
  template<class T>
  void LazySave(const std::string& key, const std::string*& ref) const;
  
  ///Writes data to the database, if ref is marked as lazy.
  template<class IT>
  void LazySaveArray(const std::string& key, const void* ref, IT begin, IT end) const;

  ///Writes data to the database, if ref is marked as lazy.
  template<class Cont>
  void LazySaveArray(const std::string& key, const Cont& ref) const;

/*  ///Writes data to the database, if ref is marked as lazy.
  template<class T>
  void LazyGetArray(const std::string& key, const std::string& ref) const;

  ///Writes data to the database, if ref is marked as lazy.
  template<class T>
  void LazySaveArray(const std::string*& ref, const std::string& key) const;*/

  /// Static reference to LDatabase object.
  static LDatabase& LDB;

  /// My LID.
  LID my_LID;

  /// Section
  std::string my_section;
};

#include "../lib/ldatabase_tpl.cpp"

#endif //LDATABASE_H
