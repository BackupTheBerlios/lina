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

namespace LINA {

/// LINA Range
/** This class provides a type of your choice
    with thoe possibility to define its range. */
template <class T=char,int min=0,int max=100>
class Range
{
    /// Operators << and >>.
    /** Makes `cout' and `cin' operations
        possible with Range. */
    friend std::ostream &operator<<<T,min,max>(std::ostream&, const Range<T,min,max>&);
    friend std::istream &operator>><T,min,max>(std::istream& is, Range&);

    // Operators for standard calculation.
    friend Range operator+<T,min,max>(const Range&, const Range&);
    friend Range operator-<T,min,max>(const Range&, const Range&);
    friend Range operator*<T,min,max>(const Range&, const Range&);
    friend Range operator/<T,min,max>(const Range&, const Range&);

    private:
      // The value itself - isn't it sweet?
      T value;

    public:
      /// Default constructor.
      Range();
      /// Constructor which takes a long int.
      Range(long);
      /// Constructor which takes an Range.
      Range(const Range &rv): value(rv.value) {};

      /// Destructor.
      ~Range();

      // Assignment operators.
      Range &operator= (const Range&);
      Range &operator+= (const Range&);
      Range &operator-= (const Range&);
      Range &operator*= (const Range&);
      Range &operator/= (const Range&);

      // Boolean operators.
      bool operator< (const Range&);
      bool operator> (const Range&);
      bool operator== (const Range&);
      bool operator!= (const Range&);
      bool operator<= (const Range&);
      bool operator>= (const Range&);

      /// Returns an integer value.
      /** Possibility to return an integer
          where no integer value is given. */
      operator T() { return value; }
};

typedef Range<char> RangeC;

#include "../lib/lrange.cpp"

} // end namespace LINA

#endif //LRANGE_H

