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

LLeague stadium_legue(LID("league","stadiumtest"));
LStadium my_stadium(LID("stadium","test0"));
std::vector<LStadium*> opponents;

void StadiumTest::play_round()
{
LRand random;
int i;
for(std::vector<LStadium*>::iterator it = opponents.begin(); it != opponents.end(); ++it)
{
//i = random.Rand((*it)->max_spectators);

}

}


void StadiumTest::start_game()
{
//Generate 5 opponents

opponents.push_back(new LStadium(LID("stadium","test1")));
opponents.push_back(new LStadium(LID("stadium","test2")));
opponents.push_back(new LStadium(LID("stadium","test3")));
opponents.push_back(new LStadium(LID("stadium","test4")));
opponents.push_back(new LStadium(LID("stadium","test5")));

}
