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

#include <cstdlib>
#include <lclient.h>
#include <qapplication.h>
#include "lchat.h"
#include "linachat.h"

using namespace std;


int main(int argc, char *argv[])
{
  QApplication myapp( argc, argv );
  LINAChat* mylinachat = new LINAChat();

  myapp.setMainWidget( mylinachat );
  mylinachat->show();

  std::string nick;
  std::string server;
  
  char* tmp;
  if((tmp = getenv("USER")) != NULL)
  nick = tmp;
  else
  nick = "unnamed";

  for(int i = 0; i < argc; ++i)
  {
    if(argv[i][0] == '-' && argv[i][1] == 'n')
      nick = &argv[i][2];
    else if(argv[i][0] == '-' && argv[i][1] == 's')
      nick = &argv[i][2];
  }
  
  cout << "Your nickname is: "<< nick << endl;
  mylinachat->set_nick(nick);
  if(!server.empty())
  mylinachat->set_server(server);
  
  return myapp.exec();
  

  /*
  
  for(;;)
  {
    string input;
    cin >> input;

    
    LNetPackage tmp;
    
    cout << "SendITTT" << endl;
    
    client.ReceivePackage(tmp);
    
    cout<< tmp.buffer << endl;
        
    cout << endl;
  }

  return EXIT_SUCCESS;*/
}

