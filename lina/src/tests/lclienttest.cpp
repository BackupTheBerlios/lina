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
#include <lclient.h>

using namespace std;
using namespace LINA;

int main(int argc, char *argv[])
{
  Client client;
  for(;;)
  {
  client.SendPackage(NetPackage(NetConnect, Buffer("\nHere I am! With Boost!\n")));
  
  client.SendPackage(NetPackage(NetDisconnect,Buffer("\nAgain and Again!\n")));
  sleep(2);
  }

  return EXIT_SUCCESS;
}

