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

#ifndef LUTILITY_H
#define LUTILITY_H

#include <stdio.h>
#include <iostream>
#include <string>

/// LDebug helps debugging
/** The first parameter is the debug-message and
    with the second one you can set wether the program
    should be hold or not.*/
template<class T>
void LDebug(const T& msg,bool hold=false)
{
  std::cout<<"LDebug: "<<msg<<std::endl;
  if(hold)
    getc(stdin);
}

/// LDebug helps debugging
/** The first parameter is the expected output, the second
    one is the output and with the third one you can set wether the program
    should be hold or not.*/
template<class T,class C>
void LDebug(const T& expected,const C& output,bool hold=false)
{
  std::cout<<"LDebug - Expected output:"<<std::endl;
  std::cout<<expected<<std::endl;
  std::cout<<"LDebug - Output:"<<std::endl;
  std::cout<<output<<std::endl;
  if(hold)
    getc(stdin);
}

/// LPtr is LINA's smart pointer
template <class T>
class LPtr
{
public:
  /// Constructor
  LPtr(T* realPtr = 0) : pointee(realPtr) {};
  /// Constructor
  LPtr(T value)
  {
    pointee = new T(value);
  };
  /// Copy-constructor
  LPtr(LPtr& rhs) : pointee(rhs.pointee) { rhs.pointee = 0; };
  /// Destructor
  ~LPtr() { delete pointee; };
  /// Operator=
  LPtr& operator=(const LPtr& rhs)
  {
    if ( this != &rhs )
    {
      delete pointee;
      pointee = &*rhs;
    }
    return *this;
  };

  /// Operator=
  LPtr& operator=(T* realPtr)
  {
    if ( realPtr != pointee )
    {
      delete pointee;
      pointee = realPtr;
    }
    return *this;
  };

  /// -> operator
  T* operator-> () const { return pointee; };
  /// Dereferencing operator
  T& operator*() const { return *pointee; };

  /// Is it NULL?
  bool IsNULL() const
  {
    if (pointee)
      return false;
    else
      return true;
  };

  /// Converts to a reference of a real pointer
  operator T*&() { return pointee; };

  /// Converts to a reference of a real pointer
  operator T* const&() const { return pointee; };

private:
  // The real pointer
  T* pointee;
};

#endif //LUTILITY_H
