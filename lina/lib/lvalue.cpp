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


#include <lvalue.h>

LValue::LValue()
{
    value=0;
}

LValue::LValue(int x)
{
    if (x > 100)
        x=100;
    else if (x < 0)
        x=0;
    value=x;
}

LValue::~LValue() {}

LValue& LValue::operator= (const LValue &rv)
{
    if (rv.value > 100)
        value = 100;
    else
        value = rv.value;
    return *this;
}

LValue& LValue::operator+= (const LValue &rv)
{
    if ((value + rv.value) > 100)
        value = 100;
    else
        value += rv.value;
    return *this;
}

LValue& LValue::operator-= (const LValue &rv)
{
    if ((value - rv.value) < 0)
        value = 0;
    else
        value -= rv.value;
    return *this;
}

LValue& LValue::operator*= (const LValue &rv)
{
    if ((value * rv.value) > 100)
        value = 100;
    else if ((value * rv.value) < 0)
        value = 0;
    else
        value *= rv.value;
    return *this;
}

LValue& LValue::operator/= (const LValue &rv)
{
    if ((value / rv.value) > 100)
        value = 100;
    else
        value /= rv.value;
    return *this;
}

bool LValue::operator> (const LValue &rv)
{
    return value > rv.value;
}

bool LValue::operator< (const LValue &rv)
{
    return value < rv.value;
}

bool LValue::operator== (const LValue &rv)
{
    return value == rv.value;
}

bool LValue::operator!= (const LValue &rv)
{
    return value != rv.value;
}

bool LValue::operator<= (const LValue &rv)
{
    return value <= rv.value;
}

bool LValue::operator>= (const LValue &rv)
{
    return value >= rv.value;
}

ostream &operator<<(ostream &ostr, const LValue &rv)
{
    ostr << rv.value;
    return ostr;
}

LValue operator+(const LValue &rv1, const LValue &rv2)
{
    return rv1.value + rv2.value;
}

LValue operator-(const LValue &rv1, const LValue &rv2)
{
    return rv1.value - rv2.value;
}

LValue operator*(const LValue &rv1, const LValue &rv2)
{
    return rv1.value * rv2.value;
}

LValue operator/(const LValue &rv1, const LValue &rv2)
{
    return rv1.value / rv2.value;
}
