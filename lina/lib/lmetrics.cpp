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

#include <math.h>
#include <lmetrics.h>

std::ostream& operator<<(std::ostream& os, const LPoint& rv)
{
return os << rv.x << " " << rv.y;
}

std::istream& operator>>(std::istream& is, LPoint& rv)
{
return is >> rv.x >> rv.y;
}

LPoint operator+(const LPoint &rv1, const LPoint &rv2)
{
    return LPoint(rv1.x + rv2.x, rv1.y + rv2.y);
}

LPoint operator-(const LPoint &rv1, const LPoint &rv2)
{
    return LPoint(rv1.x - rv2.x, rv1.y - rv2.y);
}

LPoint& LPoint::operator*(float s)
{
    x *= s;
    y *= s;
    return *this;
}

LPoint& LPoint::operator/(float s)
{
    x /= s;
    y /= s;
    return *this;
}

LPoint Middle(const LPoint &rv1, const LPoint &rv2)
{

    return LPoint((rv1.x + rv2.x) / 2, (rv1.y + rv2.y) / 2);
}

float Distance(const LPoint &rv1, const LPoint &rv2)
{

    return sqrt((rv1.x - rv2.x)*(rv1.x - rv2.x) + (rv1.y - rv2.y)*(rv1.y - rv2.y));
}

bool LPoint::IsNear(const LPoint& n,float d)
{
return (n.x-x)*(n.x-x)+(n.y-y)*(n.y-y) <= d*d;
}

LPoint& LPoint::operator=(const LPoint &rv)
{
    x = rv.x;
    y = rv.y;
    return *this;
}

LPoint& LPoint::operator+= (const LPoint &rv)
{
    x += rv.x;
    y += rv.y;
    return *this;
}

LPoint& LPoint::operator-= (const LPoint &rv)
{
    x -= rv.x;
    y -= rv.y;
    return *this;
}

LPoint& LPoint::operator*= (float s)
{
    x *= s;
    y *= s;
    return *this;
}

LPoint& LPoint::operator/= (float s)
{
    x /= s;
    y /= s;
    return *this;
}

bool LPoint::operator> (const LPoint &rv)
{
    return x > rv.x && y > rv.y;
}

bool LPoint::operator< (const LPoint &rv)
{
    return x < rv.x && y < rv.y;
}

bool LPoint::operator== (const LPoint &rv)
{
    return x == rv.x && y == rv.y;
}

bool LPoint::operator!= (const LPoint &rv)
{
    return x != rv.x || y != rv.y;
}

bool LPoint::operator<= (const LPoint &rv)
{
    return x <= rv.x && y <= rv.y;
}

bool LPoint::operator>= (const LPoint &rv)
{
    return x >= rv.x && y >= rv.y;
}
