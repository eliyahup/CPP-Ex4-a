#include "doctest.h"
#include "Board.hpp"
#include "DemoGame.hpp"
#include "FootSoldier.hpp"
#include "FootCommander.hpp"


using namespace std;
using namespace WarGame;


TEST_CASE("play game") {
  Board board(8,8);
  CHECK_FALSE(board.has_soldiers(1));
    board[{0,1}] = new FootSoldier(1);
    board[{0,3}] = new FootCommander(1);
    board[{0,5}] = new FootSoldier(1);
for(int i=0;i<100 ; i++){
            CHECK_FALSE(!board.has_soldiers(1));
    //CHECK(0==0);
}


}