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

#include <ldatagenerator.h>
#include <lrand.h>

LINA::DataGenerator::DataGenerator(const std::string& datafile, bool allow_repetition_)
{
allow_repetition = allow_repetition_;

 /*   gzFile file = gzopen(datafile,"rb");

    const short int MAXLINESIZE = 1024;

    char c;
    while((c = gzgetc(file)) != -1)
    
    for (char tmpline[MAXLINESIZE]; gzgets(file,tmpline,MAXLINESIZE) != Z_NULL ; )
    {
      text += tmpline;
    }
    gzclose(file);*/
}

const std::string LINA::DataGenerator::GetRandomData()
{
LINA::Random rand;
int index = rand.RandInt(data.size());
std::set<std::string>::iterator it;
for(it = data.begin(); index != 0; --index)
{}
return (*it);
}


