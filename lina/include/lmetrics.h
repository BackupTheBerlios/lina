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

#ifndef LMETRICS_H
#define LMETRICS_H

#include <iostream>

namespace LINA {

/// Point represents a 2d coordinate.
/** Point can be used to represent and
    manipulate a coordinate.*/
class Point
{
/// Operators << and >>.
/** Makes `cout' and `cin' operations
    possible with Range. */
friend std::ostream &operator<<(std::ostream&, const Point&);
friend std::istream &operator>>(std::istream& is, Point&);

/// Operators for standard calculations.
friend Point operator+(const Point&, const Point&);
friend Point operator-(const Point&, const Point&);

/// Returns the coordinate of the middle between two coordinates.
friend Point Middle(const Point&, const Point&);
/// Returns the distance between two coordinates.
friend float Distance(const Point&, const Point&);

public:
Point() : x(0),y(0) {};
/// Constructor.
Point(float coord_x, float coord_y) : x(coord_x),y(coord_y) {};
/// Copy-constructor.
Point(const Point& rhs) : x(rhs.x), y(rhs.y) {};
/// Set the X coordinate.
void SetX(float coord_x) { x = coord_x; };
/// Set the Y coordinate.
void SetY(float coord_y) { x = coord_y; };
/// Get the X coordinate.
float X() { return x; };
/// Get the Y coordinate.
float Y() { return y; };
/// Is it near to a certain coordinate?
bool IsNear(const Point& n,float d);

// Assignment operators.
Point &operator= (const Point&);
Point &operator+= (const Point&);
Point &operator-= (const Point&);
Point &operator*= (float s);
Point &operator/= (float s);

// Calculation operators.
Point &operator*(float s);
Point &operator/(float s);

// Boolean operators.
bool operator< (const Point&);
bool operator> (const Point&);
bool operator== (const Point&);
bool operator!= (const Point&);
bool operator<= (const Point&);
bool operator>= (const Point&);

private:
//coordinates
float x;
float y;
};

} // end LINA namespace

#endif //LMETRICS_H
