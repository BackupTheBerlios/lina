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

#include <zlib.h>
#include <ldatapool.h>
#include <lrand.h>

/* ===========================================================================
      Reads bytes from the compressed file until  an
   end-of-file condition is encountered.  The string is then terminated
   with a null character.
      gzgets returns buf, or Z_NULL in case of error.
*/
char * ZEXPORT gzgetsa(gzFile file) //FIXME: optimize it to death and try to make it an official zlib function @tobgle
{
  unsigned int buffer_chunk = 1024;
  unsigned int chunk_number = 1;
  char *b = (char*) malloc(sizeof(char)*buffer_chunk);
  char *pb = b;
  int eof = 0;
  while ((--buffer_chunk > 0 ||
  ((buffer_chunk = 1024) && ++chunk_number
   && (pb = (char*) realloc(pb,sizeof(char)*buffer_chunk*chunk_number)) && !(b = pb)))
   && (gzread(file, b, 1) == 1 || !(eof = 1)) && *b++ != '\0');
{}
  *b = '\0';
  return (eof && pb == b) ? Z_NULL : pb;
}

LINA::DataPool::DataPool(const std::string& datafile, bool allow_repetition)
{
  if(allow_repetition)
    used_indexs = NULL;
  else
    used_indexs = new std::set<int>();

  gzFile file = gzopen(datafile.c_str(),"rb");

  char* c = gzgetsa(file);
  if(c != Z_NULL)
  {
  name = c;
  delete c;
  }
  
  while((c = gzgetsa(file)) != Z_NULL)
  {
    data.insert(c);
    free(c);
  }

  gzclose(file);
}

LINA::DataPool::~DataPool()
{
  delete used_indexs;
}

const std::string LINA::DataPool::GetRandomData()
{
  LINA::Random rand;
  int index = rand.RandInt(data.size());
  std::set<std::string>::iterator it;
  for(it = data.begin(); index != 0; --index, ++it)
  {}
  if(used_indexs && used_indexs->size() < data.size())
  {
    std::pair<std::set<int>::iterator,bool> test = used_indexs->insert(index);
    if(test.second = false)
      return GetRandomData();
  }
  return (*it);
}




