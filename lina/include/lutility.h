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

#include <iostream>
#include <string>

using namespace std;

 ///LDebug helps debugging
 /**The first parameter is the debug-message and
   with the second one you can set wether the program
   should be hold or not.*/
template<class T>
void LDebug(const T& msg,bool hold=false)
{
cout<<"LDebug: "<<msg<<endl;
if(hold)
getc(stdin);
}

 ///LDebug helps debugging
 /**The first parameter is the expected output, the second
   one is the output and with the third one you can set wether the program
   should be hold or not.*/
template<class T,class C>
void LDebug(const T& expected,const C& output,bool hold=false)
{
cout<<"LDebug - Expected output:"<<endl;
cout<<expected<<endl;
cout<<"LDebug - Output:"<<endl;
cout<<output<<endl;
if(hold)
getc(stdin);
}

///LPtr is LINA's smart pointer
template <class T>
class LPtr {
public:
///constructor
LPtr(T* realPtr = 0) : pointee(realPtr) {};
///constructor
LPtr(T value)
{
pointee = new T;
*pointee = value;
};
///copy-constructor
LPtr(const LPtr& rhs) : pointee(rhs) {};
///destructor
~LPtr() { delete pointee; };
///operator=
LPtr& operator=(const LPtr& rhs)
{
if ( this != &rhs )
{
delete pointee;
pointee = &*rhs;
}
return *this;
};

///-> operator
T* operator-> () const { return pointee; };
///dereferencing operator
T& operator*() const { return *pointee; };

///Is it NULL?
bool isNULL() const
{
if (pointee)
return false;
else
return true;
};

///converts to a reference of a real pointer
operator T*&() { return pointee; };

private:
//the real pointer
T* pointee;
};

#endif //LUTILITY_H
