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

#include <ldefault.h>
#include <lrand.h>

using namespace std;
using namespace LINA;

struct test
{
int integer;
long longer;
};

int main(int argc, char *argv[])
{

Ptr<ID> test_lid(ID("bla","blub"));
Ptr<ID> test_ptr_lid(test_lid);

Ptr<int> int_test_test(123);
Debug("123",*int_test_test);

int* real_pointer = new int;
*real_pointer = 23;
Ptr<int> int_test(real_pointer);
Debug("23",*int_test);

Ptr<long> long_test;
Debug("Is NULL",long_test.IsNULL() ? "IS NULL" : "" );

Ptr<char> char_test('a');
Debug("a",*char_test);

Ptr<int> int_test2(new int);
*int_test2 = 400;
Debug("400",*int_test2);

Ptr<test> struct_test(new test);
struct_test->integer = 33;
struct_test->longer = 0;
Debug("33",struct_test->integer);
Debug("0",struct_test->longer);

Ptr<float> floating_test;
floating_test = new float;
*floating_test = 99;
Debug(99,*floating_test);

return 0;
}
