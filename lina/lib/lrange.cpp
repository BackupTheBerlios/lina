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

template<class T,int min,int max> LRange<T,min,max>::LRange()
{
    value=0;
}

template<class T,int min,int max> LRange<T,min,max>::LRange(long x)
{
    if (x > 100)
        x=100;
    else if (x < 0)
        x=0;
    value=x;
}

template<class T,int min,int max> LRange<T,min,max>::~LRange() {}

template<class T,int min,int max> LRange<T,min,max>& LRange<T,min,max>::operator=(const LRange<T,min,max> &rv)
{
    value = rv.value;
    return *this;
}

template<class T,int min,int max> LRange<T,min,max>& LRange<T,min,max>::operator+= (const LRange<T,min,max> &rv)
{
    if ((value + rv.value) > 100)
        value = 100;
    else
        value += rv.value;
    return *this;
}

template<class T,int min,int max> LRange<T,min,max>& LRange<T,min,max>::operator-= (const LRange<T,min,max> &rv)
{
    if ((value - rv.value) < 0)
        value = 0;
    else
        value -= rv.value;
    return *this;
}

template<class T,int min,int max> LRange<T,min,max>& LRange<T,min,max>::operator*= (const LRange<T,min,max> &rv)
{
    if ((value * rv.value) > 100)
        value = 100;
    else if ((value * rv.value) < 0)
        value = 0;
    else
        value *= rv.value;
    return *this;
}

template<class T,int min,int max> LRange<T,min,max>& LRange<T,min,max>::operator/= (const LRange<T,min,max> &rv)
{
    if ((value / rv.value) > 100)
        value = 100;
    else
        value /= rv.value;
    return *this;
}

template<class T,int min,int max> bool LRange<T,min,max>::operator> (const LRange<T,min,max> &rv)
{
    return value > rv.value;
}

template<class T,int min,int max> bool LRange<T,min,max>::operator< (const LRange<T,min,max> &rv)
{
    return value < rv.value;
}

template<class T,int min,int max> bool LRange<T,min,max>::operator== (const LRange<T,min,max> &rv)
{
    return value == rv.value;
}

template<class T,int min,int max> bool LRange<T,min,max>::operator!= (const LRange<T,min,max> &rv)
{
    return value != rv.value;
}

template<class T,int min,int max> bool LRange<T,min,max>::operator<= (const LRange<T,min,max> &rv)
{
    return value <= rv.value;
}

template<class T,int min,int max> bool LRange<T,min,max>::operator>= (const LRange<T,min,max> &rv)
{
    return value >= rv.value;
}

template<class T,int min,int max> std::ostream& operator<<(std::ostream& ostr, const LRange<T,min,max> &rv)
{
    ostr << static_cast<int>(rv.value);
    return ostr;
}

template<class T,int min,int max> LRange<T,min,max> operator+(const LRange<T,min,max> &rv1, const LRange<T,min,max> &rv2)
{
    return rv1.value + rv2.value;
}

template<class T,int min,int max> LRange<T,min,max> operator-(const LRange<T,min,max> &rv1, const LRange<T,min,max> &rv2)
{
    return rv1.value - rv2.value;
}

template<class T,int min,int max> LRange<T,min,max> operator*(const LRange<T,min,max> &rv1, const LRange<T,min,max> &rv2)
{
    return rv1.value * rv2.value;
}

template<class T,int min,int max> LRange<T,min,max> operator/(const LRange<T,min,max> &rv1, const LRange<T,min,max> &rv2)
{
    return rv1.value / rv2.value;
}
