/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <vector>
#include <ldefault.h>

using namespace std;
using namespace LINA;

League stadium_legue(ID("league","stadiumtest"));
Stadium my_stadium(ID("stadium","test0"));
std::vector<Stadium*> opponents;

void StadiumTest::play_round()
{
LINA::Random random;
int i;
for(std::vector<Stadium*>::iterator it = opponents.begin(); it != opponents.end(); ++it)
{
//i = random.Rand((*it)->max_spectators);

}

}


void StadiumTest::start_game()
{
//Generate 5 opponents

opponents.push_back(new Stadium(ID("stadium","test1")));
opponents.push_back(new Stadium(ID("stadium","test2")));
opponents.push_back(new Stadium(ID("stadium","test3")));
opponents.push_back(new Stadium(ID("stadium","test4")));
opponents.push_back(new Stadium(ID("stadium","test5")));

}
