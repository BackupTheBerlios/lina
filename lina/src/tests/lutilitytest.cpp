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

struct test
{
int integer;
long longer;
};

int main(int argc, char *argv[])
{

LPtr<LID> test_lid(LID("bla","blub"));
LPtr<LID> test_ptr_lid(test_lid);

LPtr<int> int_test_test(123);
LDebug("123",*int_test_test);

int* real_pointer = new int;
*real_pointer = 23;
LPtr<int> int_test(real_pointer);
LDebug("23",*int_test);

LPtr<long> long_test;
LDebug("Is NULL",long_test.IsNULL() ? "IS NULL" : "" );

LPtr<char> char_test('a');
LDebug("a",*char_test);

LPtr<int> int_test2(new int);
*int_test2 = 400;
LDebug("400",*int_test2);

LPtr<test> struct_test(new test);
struct_test->integer = 33;
struct_test->longer = 0;
LDebug("33",struct_test->integer);
LDebug("0",struct_test->longer);

LPtr<float> floating_test;
floating_test = new float;
*floating_test = 99;
LDebug(99,*floating_test);

return 0;
}
