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
#include <vector>
#include <set>
#include <cstdio>
#include <cerrno>

using namespace std;

/// LINA ID
/** This class stores a unique ID,
    wich can't be changed during the runtime. */
class LID
{
public:
  /// Constructor
  LID(const string& lid_catalog, const string& lid_token);

  const string ID() const { return catalog+token; };
  const string Catalog() const { return catalog; };
  const string Token() const { return token; };

  struct LIDComp
  {
   bool operator()(const LID& lhs, const LID& rhs)
   {
   return (lhs.Catalog()+lhs.Token() > rhs.Catalog()+rhs.Token());
   }
  };

private:
  // Constructor without arguments
  // Is declared private, because every LID has to be identified,
  // when it is declared.
  LID();

  string catalog;
  string token;
};



/// Global operator== for LID.
bool operator==(const LID& lhs, const LID& rhs);

/// Enum representing priorities.
enum LDBPrio{low,mid,high};

/// Pair for a database root and its priority.
struct LDBPair
{
LDBPair(const string& p_first, const LDBPrio& p_second) : first(p_first),second(p_second) {};
string first;
LDBPrio second;
friend bool operator<(const LDBPair& lhs, const LDBPair& rhs);
friend bool operator>(const LDBPair& lhs, const LDBPair& rhs);
};

/// Set of LDBPair.
typedef set<LDBPair> LDBPairSet;

/// LINA Database
/** This object can do several actions with a database,
    like reading and writing data.*/
class LDatabase
{
public:
  /// Default constructor.
  LDatabase() {};
  /// Constructor with initialization.
  /** This constructor is initialized with a LDBPairSet,
  which contains the roots and priorities.*/
  LDatabase(const LDBPairSet& init_root_prio_set):root_prio_set(init_root_prio_set) {};

  /// Read value from LID of the database.
  /** Read the key's value from the database.*/
  const string Read(const LID& lid, const string& key) const;

  /// Read value from LID of the database.
  /** Read the key's value from the database.*/
  int ReadArray(const LID& lid, const string& key, vector<string>& value_vector) const;

  /// Erase a key from a LID.
  /** Erases a key completly in a certain LID.*/
  bool Erase(const LID& lid, const string& key) const;

  /// Write values to a LID of the database.
  /** Write the key and value to the database.
      Returns true if success.*/
  bool Write(const LID& lid, const string& key, const string& value) const;

  /// Write values to a LID of the database.
  /** Write the key and value to the database.
      Returns true if success.*/
  bool WriteArray(const LID& lid, const string& key, const vector<string>& value_vector) const;

//  forkLID(const LID& lid, LDBPrio from, LDBPrio to=high) const;

  /// Get all keys in a LID
  /** Gets all keys and pushes them into key_vector.
      Returns the number of keys.*/
  int GetKeys(const LID& lid, vector<string>& key_vector) const;

  /// Iterates through the LIDs.
  /** Fills a vector<LID> with all LIDs in a catalog*/
  int IterateLIDs(const string& lid_catalog, vector<LID>& lid_vector);

  /// Find LIDs.
  /** Fills a vector<LID> with all LIDs,
      that have the right key and value.*/
  int FindLIDs(const string& lid_catalog,const string& key,const string& value, vector<LID>& lid_vector);

  /// Add a database root.
  /** Returns false if the database root is invalid. */
  bool AddRoot(const string& db_root);

  /// Create a new database root.
  /** Returns false if it failes. */
  bool CreateRoot(const string& db_root,enum LDBPrio=low);

  /// Information about a LID.
  /** Contains information about a LID.*/
  struct LID_info
  {
  /// This LDBPairSet contains the roots and priorities,
  /// where a LID is found in the database.
  LDBPairSet root_prio_set;
  };

  LID_info GetLIDInfo(const LID& lid);

private:
  // Clean a lid from unparsed data TODO
  void Clean(const LID& lid) const;
  // Test if a file exists.
  bool Fexists(const string& filename) const;
  // Finds the highest DBRoot with the LID lid.
  string FindTopPriorityRoot(const LID& lid) const;

  // Contains the database roots.
  // Only one per priority!
  LDBPairSet root_prio_set;
};

#endif //LDATABASE_H
