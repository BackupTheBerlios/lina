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

#include <lutility.h>
#include <lmetrics.h>

using namespace std;

int main(int argc, char *argv[])
{

  LPoint test(2,0);
  LDebug("2 0",test);
  test += LPoint(3,5);
  LDebug("5 5",test);
  test *= 2;
  LDebug("10 10",test);
  test /= 2;
  LDebug("5 5",test);
  test -= LPoint(3,2);
  LDebug("2 3",test);
  float d = Distance(LPoint(2,9.4),test);
  LDebug("6.4",d);
  LPoint m = Middle(LPoint(5,5),test);
  LDebug("3.5 4",m);
  bool near = test.IsNear(LPoint(0,5),3);
  if(near)
  LDebug("OK");
  else
  LDebug("ERR");

  return EXIT_SUCCESS;
}
