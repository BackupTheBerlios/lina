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


#include <lrange.h>

template<class T,int min,int max> LINA::Range<T,min,max>::Range()
{
    value=min;
}

template<class T,int min,int max> LINA::Range<T,min,max>::Range(long x)
{
    if (x > max)
        x=max;
    else if (x < min)
        x=min;
    value=x;
}

template<class T,int min,int max> LINA::Range<T,min,max>::~Range() {}

template<class T,int min,int max> LINA::Range<T,min,max>& LINA::Range<T,min,max>::operator=(const LINA::Range<T,min,max> &rv)
{
    value = rv.value;
    return *this;
}

template<class T,int min,int max> LINA::Range<T,min,max>& LINA::Range<T,min,max>::operator+= (const LINA::Range<T,min,max> &rv)
{
    if ((value + rv.value) > max)
        value = max;
    else if ((value + rv.value) < min)
        value = min;
    else
        value += rv.value;
    return *this;
}

template<class T,int min,int max> LINA::Range<T,min,max>& LINA::Range<T,min,max>::operator-= (const LINA::Range<T,min,max> &rv)
{
    if ((value - rv.value) > max)
        value = max;
    else if ((value - rv.value) < min)
        value = min;
    else
        value -= rv.value;
    return *this;
}

template<class T,int min,int max> LINA::Range<T,min,max>& LINA::Range<T,min,max>::operator*= (const LINA::Range<T,min,max> &rv)
{
    if ((value * rv.value) > max)
        value = max;
    else if ((value * rv.value) < min)
        value = min;
    else
        value *= rv.value;
    return *this;
}

template<class T,int min,int max> LINA::Range<T,min,max>& LINA::Range<T,min,max>::operator/= (const LINA::Range<T,min,max> &rv)
{
    if ((value / rv.value) > max)
        value = max;
    else if ((value / rv.value) < min)
        value = min;
    else
        value /= rv.value;
    return *this;
}

template<class T,int min,int max> bool LINA::Range<T,min,max>::operator> (const LINA::Range<T,min,max> &rv)
{
    return value > rv.value;
}

template<class T,int min,int max> bool LINA::Range<T,min,max>::operator< (const LINA::Range<T,min,max> &rv)
{
    return value < rv.value;
}

template<class T,int min,int max> bool LINA::Range<T,min,max>::operator== (const LINA::Range<T,min,max> &rv)
{
    return value == rv.value;
}

template<class T,int min,int max> bool LINA::Range<T,min,max>::operator!= (const LINA::Range<T,min,max> &rv)
{
    return value != rv.value;
}

template<class T,int min,int max> bool LINA::Range<T,min,max>::operator<= (const LINA::Range<T,min,max> &rv)
{
    return value <= rv.value;
}

template<class T,int min,int max> bool LINA::Range<T,min,max>::operator>= (const LINA::Range<T,min,max> &rv)
{
    return value >= rv.value;
}

template<class T,int min,int max> std::ostream& operator<<(std::ostream& ostr, const LINA::Range<T,min,max> &rv)
{
    ostr << static_cast<int>(rv.value);
    return ostr;
}

template<class T,int min,int max> std::istream& operator>>(std::istream& is, LINA::Range<T,min,max>& rv)
{
  is >> rv.value;
  return is;
}

template<class T,int min,int max> LINA::Range<T,min,max> operator+(const LINA::Range<T,min,max> &rv1, const LINA::Range<T,min,max> &rv2)
{
    return rv1.value + rv2.value;
}

template<class T,int min,int max> LINA::Range<T,min,max> operator-(const LINA::Range<T,min,max> &rv1, const LINA::Range<T,min,max> &rv2)
{
    return rv1.value - rv2.value;
}

template<class T,int min,int max> LINA::Range<T,min,max> operator*(const LINA::Range<T,min,max> &rv1, const LINA::Range<T,min,max> &rv2)
{
    return rv1.value * rv2.value;
}

template<class T,int min,int max> LINA::Range<T,min,max> operator/(const LINA::Range<T,min,max> &rv1, const LINA::Range<T,min,max> &rv2)
{
    return rv1.value / rv2.value;
}
