#include "doctest.h"
#include "Board.hpp"
#include "DemoGame.hpp"
#include "FootSoldier.hpp"
#include "FootCommander.hpp"
#include "Sniper.hpp"
#include "SniperCommander.hpp"
#include "Paramedic.hpp"
#include "ParamedicCommander.hpp"

using namespace std;
using namespace WarGame;


TEST_CASE ("Test Soldier(not Commanders) ") {
    Board board(4, 4);

            CHECK_FALSE(board.has_soldiers(1));   //No players yet
            CHECK_FALSE(board.has_soldiers(2));
    board[{0, 1}] = new FootSoldier(1);
    board[{3, 2}] = new FootSoldier(2);
            CHECK_FALSE(!board.has_soldiers(1));
            CHECK_FALSE(!board.has_soldiers(2));

    //start game
    board.move(1, {0, 1}, Board::MoveDIR::Up);//-10 to FootSoldier
            CHECK_FALSE(!board.has_soldiers(2));
    board.move(1, {1, 1}, Board::MoveDIR::Down);
            CHECK_FALSE(!board.has_soldiers(2));
    board.move(1, {0, 1}, Board::MoveDIR::Up);
            CHECK_FALSE(!board.has_soldiers(2));
    board.move(1, {1, 1}, Board::MoveDIR::Down);
            CHECK_FALSE(!board.has_soldiers(2));
    board.move(1, {0, 1}, Board::MoveDIR::Up);
            CHECK_FALSE(!board.has_soldiers(2));
    board.move(1, {1, 1}, Board::MoveDIR::Down);
            CHECK_FALSE(!board.has_soldiers(2));
    board.move(1, {0, 1}, Board::MoveDIR::Up);
            CHECK_FALSE(!board.has_soldiers(2));
    board.move(1, {1, 1}, Board::MoveDIR::Down);
            CHECK_FALSE(!board.has_soldiers(2));
    board.move(1, {0, 1}, Board::MoveDIR::Up);
            CHECK_FALSE(!board.has_soldiers(2));
    board.move(1, {1, 1}, Board::MoveDIR::Down);
            CHECK_FALSE(board.has_soldiers(2)); //Player 2 is dead

    //add sniper to player 2
    board[{3, 2}] = new Sniper(2);
            CHECK_FALSE(!board.has_soldiers(2));
    board.move(2, {3, 2}, Board::MoveDIR::Down); //-50 to FootSoldier
            CHECK_FALSE(!board.has_soldiers(1));
    board.move(2, {2, 2}, Board::MoveDIR::Up); //-50 to FootSoldier
            CHECK_FALSE(board.has_soldiers(1)); // Player 1 is dead

    //Paramedic and sniper to player 1
    board[{0, 2}] = new Sniper(1);
    board[{0, 1}] = new Paramedic(1);
            CHECK_FALSE(!board.has_soldiers(1));
    board.move(2, {3, 2}, Board::MoveDIR::Down); //-50 to Sniper or Paramedic
            CHECK_FALSE(!board.has_soldiers(1));
    board.move(2, {2, 2}, Board::MoveDIR::Up); //-50 to strong(Sniper or Paramedic)
            CHECK_FALSE(!board.has_soldiers(1));
    board.move(1, {0, 1}, Board::MoveDIR::Up); //Sniper up to 100
            CHECK_FALSE(!board.has_soldiers(1));
    board.move(2, {3, 2}, Board::MoveDIR::Down); //-50 to Sniper
            CHECK_FALSE(!board.has_soldiers(1));
    board.move(1, {0, 2}, Board::MoveDIR::Up); //Sniper -50
    board.move(1, {1, 2}, Board::MoveDIR::Down); //Sniper -50
            CHECK_FALSE(board.has_soldiers(2));

}


TEST_CASE ("Test Soldier with Commanders") {

    // Check FootCommander
    Board board(8, 8);
            CHECK_FALSE(board.has_soldiers(1));   //No players yet
            CHECK_FALSE(board.has_soldiers(2));

    board[{0, 0}] = new FootSoldier(1);
    board[{0, 1}] = new FootSoldier(1);
    board[{0, 2}] = new FootSoldier(1);
    board[{0, 3}] = new FootCommander(1);

    board[{7, 0}] = new FootSoldier(2);

            CHECK_FALSE(!board.has_soldiers(1));
            CHECK_FALSE(!board.has_soldiers(2));

            CHECK(board[{0, 0}] != nullptr);
            CHECK(board[{0, 1}] != nullptr);
            CHECK(board[{0, 2}] != nullptr);
            CHECK(board[{0, 3}] != nullptr);
            CHECK(board[{7, 0}] != nullptr);


    board.move(1, {0, 3}, Board::MoveDIR::Up);  //-50 to FootSoldier
            CHECK_FALSE(!board.has_soldiers(2));
    board.move(1, {1, 3}, Board::MoveDIR::Down);  //-50 to FootSoldier
            CHECK_FALSE(board.has_soldiers(2));  //FootSoldier =0

    //add soldier to player 2
    board[{7, 0}] = new FootSoldier(2);
    board[{7, 1}] = new FootSoldier(2);
    board[{7, 2}] = new FootSoldier(2);
    board[{7, 3}] = new FootSoldier(2);
            CHECK_FALSE(!board.has_soldiers(2));

            CHECK(board[{7, 0}] != nullptr);
            CHECK(board[{7, 1}] != nullptr);
            CHECK(board[{7, 2}] != nullptr);
            CHECK(board[{7, 3}] != nullptr);


    board.move(1, {0, 3}, Board::MoveDIR::Up); //all soldiers also attack
    board.move(1, {1, 3}, Board::MoveDIR::Down);
    board.move(1, {0, 3}, Board::MoveDIR::Up);
    board.move(1, {1, 3}, Board::MoveDIR::Down);
    board.move(1, {0, 3}, Board::MoveDIR::Up);
            CHECK(board[{7, 3}] == nullptr);
    board.move(1, {1, 3}, Board::MoveDIR::Down);
            CHECK(board[{7, 0}] != nullptr);
            CHECK(board[{7, 1}] != nullptr);
            CHECK(board[{7, 2}] != nullptr);
    board.move(1, {0, 3}, Board::MoveDIR::Up);
            CHECK(board[{7, 2}] == nullptr);
            CHECK(board[{7, 1}] != nullptr);
            CHECK(board[{7, 0}] != nullptr);
    board.move(1, {1, 3}, Board::MoveDIR::Down);
            CHECK(board[{7, 1}] == nullptr);
            CHECK(board[{7, 0}] == nullptr);
            CHECK_FALSE(board.has_soldiers(2));


    // Check SniperCommander
    board[{7, 0}] = new Sniper(2);
    board[{7, 1}] = new Sniper(2);
    board[{7, 2}] = new Sniper(2);
    board[{7, 3}] = new SniperCommander(2);
            CHECK_FALSE(!board.has_soldiers(2));

            CHECK(board[{7, 0}] != nullptr);
            CHECK(board[{7, 1}] != nullptr);
            CHECK(board[{7, 2}] != nullptr);
            CHECK(board[{7, 3}] != nullptr);

    board.move(2, {7, 3}, Board::MoveDIR::Down); //all sniper also attack
    board.move(2, {6, 3}, Board::MoveDIR::Up);
            CHECK(board[{0, 0}] == nullptr);
            CHECK(board[{0, 1}] == nullptr);
            CHECK(board[{0, 2}] == nullptr);
            CHECK(board[{0, 3}] == nullptr);

            CHECK_FALSE(board.has_soldiers(1));

    // Check ParamedicCommander
    board[{0, 0}] = new Sniper(1);
    board[{0, 1}] = new Sniper(1);
    board[{0, 2}] = new Sniper(1);
    board[{0, 3}] = new SniperCommander(1);

            CHECK(board[{0, 0}] != nullptr);
            CHECK(board[{0, 1}] != nullptr);
            CHECK(board[{0, 2}] != nullptr);
            CHECK(board[{0, 3}] != nullptr);

    board[{1, 0}] = new Paramedic(1);
    board[{1, 1}] = new Paramedic(1);
    board[{1, 2}] = new Paramedic(1);
    board[{2, 3}] = new ParamedicCommander(1);

            CHECK(board[{1, 0}] != nullptr);
            CHECK(board[{1, 1}] != nullptr);
            CHECK(board[{1, 2}] != nullptr);
            CHECK(board[{2, 3}] != nullptr);

    board.move(2, {7, 3}, Board::MoveDIR::Down); //all sniper also attack
            CHECK(board[{0, 0}] != nullptr);
            CHECK(board[{0, 1}] != nullptr);
            CHECK(board[{0, 2}] != nullptr);
            CHECK(board[{0, 3}] != nullptr);

            CHECK(board[{1, 0}] != nullptr);
            CHECK(board[{1, 1}] != nullptr);
            CHECK(board[{1, 2}] != nullptr);
            CHECK(board[{2, 3}] != nullptr);

    board.move(1, {2, 3}, Board::MoveDIR::Down); //all Paramedic also activate

    board.move(2, {6, 3}, Board::MoveDIR::Up); //all sniper also attack
            CHECK(board[{0, 0}] != nullptr);
            CHECK(board[{0, 1}] != nullptr);
            CHECK(board[{0, 2}] != nullptr);
            CHECK(board[{0, 3}] != nullptr);

            CHECK(board[{1, 0}] != nullptr);
            CHECK(board[{1, 1}] != nullptr);
            CHECK(board[{1, 2}] != nullptr);
            CHECK(board[{1, 3}] != nullptr);

    board.move(2, {7, 3}, Board::MoveDIR::Down); //all sniper also attack
    board.move(2, {6, 3}, Board::MoveDIR::Up); //all sniper also attack
    board.move(2, {7, 3}, Board::MoveDIR::Down); //all sniper also attack
            CHECK(board[{0, 0}] == nullptr);
            CHECK(board[{0, 1}] == nullptr);
            CHECK(board[{0, 2}] == nullptr);
            CHECK(board[{0, 3}] == nullptr);

            CHECK(board[{1, 0}] == nullptr);
            CHECK(board[{1, 1}] == nullptr);
            CHECK(board[{1, 2}] == nullptr);
            CHECK(board[{1, 3}] == nullptr);

            CHECK_FALSE(board.has_soldiers(1));
}

TEST_CASE ("Test check throws") {
    Board board(4, 4);

            CHECK_FALSE(board.has_soldiers(1));
            CHECK_FALSE(board.has_soldiers(2));
    board[{0, 0}] = new FootSoldier(1);
    board[{1, 0}] = new FootSoldier(2);
            CHECK_FALSE(!board.has_soldiers(1));
            CHECK_FALSE(!board.has_soldiers(2));

            CHECK_THROWS(board.move(1, {0, 0}, Board::MoveDIR::Up)); //There is already another soldier
            CHECK_THROWS(board.move(1, {0, 0}, Board::MoveDIR::Down)); //There is already another soldier
            CHECK_THROWS(board.move(2, {1, 0}, Board::MoveDIR::Down)); //exit from the board

            CHECK_THROWS( board.move(1, {1, 0}, Board::MoveDIR::Up));  // The soldier in the source location belongs to the other player.

            CHECK_THROWS( board.move(1, {2, 2}, Board::MoveDIR::Up));  //There is no soldier in the source location
}