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

#ifndef LRANGE_H
#define LRANGE_H

#include <iostream>

/// LINA Range
/** This class provides a type of your choice
    with the possibility to define its range. */
template <class T=char,int min=0,int max=100>
class LRange
{
    /// Operators << and >>.
    /** Makes `cout' and `cin' operations
        possible with LRange. */
    friend std::ostream &operator<<<T,min,max>(std::ostream&, const LRange<T,min,max>&);
    friend std::istream &operator>><T,min,max>(std::istream& is, LRange&);

    // Operators for standard calculation.
    friend LRange operator+<T,min,max>(const LRange&, const LRange&);
    friend LRange operator-<T,min,max>(const LRange&, const LRange&);
    friend LRange operator*<T,min,max>(const LRange&, const LRange&);
    friend LRange operator/<T,min,max>(const LRange&, const LRange&);

    private:
      // The value itself - isn't it sweet?
      T value;

    public:
      /// Default constructor.
      LRange();
      /// Constructor which takes a long int.
      LRange(long);
      /// Constructor which takes an LRange.
      LRange(const LRange &rv): value(rv.value) {};

      /// Destructor.
      ~LRange();

      // Assignment operators.
      LRange &operator= (const LRange&);
      LRange &operator+= (const LRange&);
      LRange &operator-= (const LRange&);
      LRange &operator*= (const LRange&);
      LRange &operator/= (const LRange&);

      // Boolean operators.
      bool operator< (const LRange&);
      bool operator> (const LRange&);
      bool operator== (const LRange&);
      bool operator!= (const LRange&);
      bool operator<= (const LRange&);
      bool operator>= (const LRange&);

      /// Returns an integer value.
      /** Possibility to return an integer
          where no integer value is given. */
      operator T() { return value; }
};

typedef LRange<char> LRangeC;

#include "../lib/lrange.cpp"

#endif //LRANGE_H

