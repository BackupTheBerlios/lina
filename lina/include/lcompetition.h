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

#ifndef LCOMPETITION_H
#define LCOMPETITION_H

#include <ldatabase.h>

namespace LINA {

/// Base class for competitions
class Competition : public DatabaseInterface
{
public:
  Competition(const ID& lid) : DatabaseInterface(lid) {}
  virtual void Save() const {};
  unsigned int Participants() const
  {
    return participants.size();
  };
  virtual void AddParticipant(const ID& lid)
  {
    participants.insert(lid);
  };

private:
  std::set
    <ID> participants;
};

class CompetitionManager : public DatabaseInterface
{
public:
  CompetitionManager(const ID& lid) : DatabaseInterface(lid) {}

private:
  std::set
    <ID> competitions;
};

class League : public Competition
{
public:
  League(const ID& lid) : Competition(lid) {};
};

class Cup : public Competition
{
public:
  Cup(const ID& lid) : Competition(lid) {};
};

} // end LINA namespace

#endif //LCOMPETITION_H

