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

std::ostream& LINA::operator<<(std::ostream& os, const LINA::Point& rv)
{
return os << rv.x << " " << rv.y;
}

std::istream& LINA::operator>>(std::istream& is, LINA::Point& rv)
{
return is >> rv.x >> rv.y;
}

LINA::Point LINA::operator+(const LINA::Point &rv1, const LINA::Point &rv2)
{
    return LINA::Point(rv1.x + rv2.x, rv1.y + rv2.y);
}

LINA::Point LINA::operator-(const LINA::Point &rv1, const LINA::Point &rv2)
{
    return LINA::Point(rv1.x - rv2.x, rv1.y - rv2.y);
}

LINA::Point& LINA::Point::operator*(float s)
{
    x *= s;
    y *= s;
    return *this;
}

LINA::Point& LINA::Point::operator/(float s)
{
    x /= s;
    y /= s;
    return *this;
}

LINA::Point LINA::Middle(const LINA::Point &rv1, const LINA::Point &rv2)
{

    return LINA::Point((rv1.x + rv2.x) / 2, (rv1.y + rv2.y) / 2);
}

float LINA::Distance(const LINA::Point &rv1, const LINA::Point &rv2)
{

    return sqrt((rv1.x - rv2.x)*(rv1.x - rv2.x) + (rv1.y - rv2.y)*(rv1.y - rv2.y));
}

bool LINA::Point::IsNear(const LINA::Point& n,float d)
{
return (n.x-x)*(n.x-x)+(n.y-y)*(n.y-y) <= d*d;
}

LINA::Point& LINA::Point::operator=(const LINA::Point &rv)
{
    x = rv.x;
    y = rv.y;
    return *this;
}

LINA::Point& LINA::Point::operator+= (const LINA::Point &rv)
{
    x += rv.x;
    y += rv.y;
    return *this;
}

LINA::Point& LINA::Point::operator-= (const LINA::Point &rv)
{
    x -= rv.x;
    y -= rv.y;
    return *this;
}

LINA::Point& LINA::Point::operator*= (float s)
{
    x *= s;
    y *= s;
    return *this;
}

LINA::Point& LINA::Point::operator/= (float s)
{
    x /= s;
    y /= s;
    return *this;
}

bool LINA::Point::operator> (const LINA::Point &rv)
{
    return x > rv.x && y > rv.y;
}

bool LINA::Point::operator< (const LINA::Point &rv)
{
    return x < rv.x && y < rv.y;
}

bool LINA::Point::operator== (const LINA::Point &rv)
{
    return x == rv.x && y == rv.y;
}

bool LINA::Point::operator!= (const LINA::Point &rv)
{
    return x != rv.x || y != rv.y;
}

bool LINA::Point::operator<= (const LINA::Point &rv)
{
    return x <= rv.x && y <= rv.y;
}

bool LINA::Point::operator>= (const LINA::Point &rv)
{
    return x >= rv.x && y >= rv.y;
}
