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

/// LPoint represents a 2d coordinate.
/** LPoint can be used to represent and
    manipulate a coordinate.*/
class LPoint
{
/// Operators << and >>.
/** Makes `cout' and `cin' operations
    possible with LRange. */
friend std::ostream &operator<<(std::ostream&, const LPoint&);
friend std::istream &operator>>(std::istream& is, LPoint&);

/// Operators for standard calculations.
friend LPoint operator+(const LPoint&, const LPoint&);
friend LPoint operator-(const LPoint&, const LPoint&);

/// Returns the coordinate of the middle between two coordinates.
friend LPoint Middle(const LPoint&, const LPoint&);
/// Returns the distance between two coordinates.
friend float Distance(const LPoint&, const LPoint&);

public:
/// Constructor.
LPoint(float coord_x, float coord_y) : x(coord_x),y(coord_y) {};
/// Copy-constructor.
LPoint(const LPoint& rhs) : x(rhs.x), y(rhs.y) {};
/// Set the X coordinate.
void SetX(float coord_x) { x = coord_x; };
/// Set the Y coordinate.
void SetY(float coord_y) { x = coord_y; };
/// Get the X coordinate.
float X() { return x; };
/// Get the Y coordinate.
float Y() { return y; };
/// Is it near to a certain coordinate?
bool IsNear(const LPoint& n,float d);

// Assignment operators.
LPoint &operator= (const LPoint&);
LPoint &operator+= (const LPoint&);
LPoint &operator-= (const LPoint&);
LPoint &operator*= (float s);
LPoint &operator/= (float s);

// Calculation operators.
LPoint &operator*(float s);
LPoint &operator/(float s);

// Boolean operators.
bool operator< (const LPoint&);
bool operator> (const LPoint&);
bool operator== (const LPoint&);
bool operator!= (const LPoint&);
bool operator<= (const LPoint&);
bool operator>= (const LPoint&);

private:
//coordinates
float x;
float y;
};

#endif //LMETRICS_H
