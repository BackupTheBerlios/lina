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

template <class T,int min=0,int max=100>
class LRange
{
    friend std::ostream &operator<<<T,min,max>(std::ostream&, const LRange<T,min,max>&);
    friend LRange operator+<T,min,max>(const LRange&, const LRange&);
    friend LRange operator-<T,min,max>(const LRange&, const LRange&);
    friend LRange operator*<T,min,max>(const LRange&, const LRange&);
    friend LRange operator/<T,min,max>(const LRange&, const LRange&);

    private:
      T value;

    public:
      LRange();
      LRange(long);
      LRange(const LRange &rv): value(rv.value) {};
      ~LRange();
      LRange &operator= (const LRange&);
      LRange &operator+= (const LRange&);
      LRange &operator-= (const LRange&);
      LRange &operator*= (const LRange&);
      LRange &operator/= (const LRange&);
      bool operator< (const LRange&);
      bool operator> (const LRange&);
      bool operator== (const LRange&);
      bool operator!= (const LRange&);
      bool operator<= (const LRange&);
      bool operator>= (const LRange&);
      operator int() { return value; }
};

#include "../lib/lrange.cpp"

#endif //LVALUE_H
