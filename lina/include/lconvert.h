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

#ifndef LCONVERT_H
#define LCONVERT_H

#include <string>
#include <sstream>

///Converts a string into a digit(int ...).
template<class T>
inline bool LStringToDigit(T &t,
                           const std::string &s,
                           std::ios & (*f)(std::ios&)=std::dec)
{
  std::istringstream iss(s);
  return !(iss>>f>>t).fail();
}

///Converts a digit(int...) into a string.
template<class T>
inline bool LDigitToString(const T &t, std::string &s)
{
  std::stringstream tmp; tmp << t;
  s = tmp.str();
}

#endif //LCONVERT_H
