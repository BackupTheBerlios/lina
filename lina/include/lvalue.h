/***************************************************************************
 *   Copyright (C) 2003 by Johannes Laudenberg                             *
 *   zwerg@berlios.de                                                      *
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

#ifndef LVALUE_H
#define LVALUE_H

#include <iostream>

using namespace std;

class LValue
{
    friend ostream &operator<<(ostream&, const LValue&);
    friend LValue operator+(const LValue&, const LValue&);
    friend LValue operator-(const LValue&, const LValue&);
    friend LValue operator*(const LValue&, const LValue&);
    friend LValue operator/(const LValue&, const LValue&);

    private:
      unsigned char value;

    public:
      LValue();
      LValue(int);
      LValue(const LValue &rv): value(rv.value) {};
      ~LValue();
      LValue &operator= (const LValue&);
      LValue &operator+= (const LValue&);
      LValue &operator-= (const LValue&);
      LValue &operator*= (const LValue&);
      LValue &operator/= (const LValue&);
      bool operator< (const LValue&);
      bool operator> (const LValue&);
      bool operator== (const LValue&);
      bool operator!= (const LValue&);
      bool operator<= (const LValue&);
      bool operator>= (const LValue&);
      operator int() { return value; }
};
#endif //LVALUE_H
