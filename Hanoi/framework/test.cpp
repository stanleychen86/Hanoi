#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "game.h"
using namespace std;

//List of friend functions
bool checkConfigsTest(Game& g, int n, int diff, std::string nString, std::string diffString) {
    return g.checkConfigs(n, diff, nString, diffString);
}

bool checkSeqTest(Game& g, std::string seq, int n) {
    return g.checkSeq(seq, n);
}

std::vector<int> createSeqTest(Game& g, std::string seq, int n) {
    return g.createSeq(seq, n);
}

bool checkInitialsTest(Game& g, std::string initials) {
    return g.checkInitials(initials);
}

void calculateScoreTest(GameEngine &e) {
    e.calculateScore();
}

void setWinnerAndScore(GameEngine &e, int winner, int score) {
    e.winner = winner;
    e.score = score;
}
void setNAndDiff(GameEngine &e, int n, int diff) {
    e.n = n;
    e.diff = diff;
}

//List of Test Cases
TEST_CASE( "configs \"n\" and \"diff\" should be checked for errors", "[Game]" ) {

   Game g1;
   SECTION("invalid inputs for \"n\"")
   {
       REQUIRE(checkConfigsTest(g1, 0, 9, "0", "9") == false);
       REQUIRE(checkConfigsTest(g1, 9, 9, "awoooo", "9") == false);
   }
   SECTION("invalid inputs for \"diff\"")
   {
       REQUIRE(checkConfigsTest(g1, 9, 99, "9", "99") == false);
       REQUIRE(checkConfigsTest(g1, 9, 9, "9", "2b") == false);
   }
   SECTION("valid inputs for \"n\"")
   {
       REQUIRE(checkConfigsTest(g1, 4, 9, "4", "9") == true);
       REQUIRE(checkConfigsTest(g1, 2, 9, "2", "9") == true);
   }
   SECTION("valid inputs for \"diff\"")
   {
       REQUIRE(checkConfigsTest(g1, 9, 6, "9", "6") == true);
       REQUIRE(checkConfigsTest(g1, 9, 9, "9", "9") == true);
   }
}

//Test case for checkSeq()
TEST_CASE( "user-specified pancake sequences should be checked for errors", "[Game]" ) {

   Game g1;
   SECTION("invalid sequence inputs")
   {
       REQUIRE(checkSeqTest(g1, "1239", 4) == false);
       REQUIRE(checkSeqTest(g1, "1", 9) == false);
       REQUIRE(checkSeqTest(g1, "hunter2", 7) == false);
       REQUIRE(checkSeqTest(g1, "666666", 6) == false);
   }
   SECTION("valid sequence inputs")
   {
       REQUIRE(checkSeqTest(g1, "352146", 6) == true);
       REQUIRE(checkSeqTest(g1, "r", 3) == true);
       REQUIRE(checkSeqTest(g1, "12345", 5) == true);
       REQUIRE(checkSeqTest(g1, "21", 2) == true);
   }

}

//Test case for createSeq()
TEST_CASE( "user-specified pancake sequences can be generated", "[Game]" ) {

   Game g1;
   std::vector<int> result = {5,4,3,2,1};
   REQUIRE(createSeqTest(g1, "54321", 5) == result);

   result = {8,3,5,9,6,2,7,1,4};
   REQUIRE(createSeqTest(g1, "835962714", 9) == result);

   result = {1,2};
   REQUIRE(createSeqTest(g1, "21", 2) != result);

   REQUIRE(createSeqTest(g1, "r", 7).size() == 7);

}

//Test case for checkInitials()
TEST_CASE( "initials should be checked for errors", "[Game]" ) {

   Game g1;
   SECTION("invalid initials inputs")
   {
       REQUIRE(checkInitialsTest(g1, "aaaa") == false);
       REQUIRE(checkInitialsTest(g1, "a2") == false);
       REQUIRE(checkInitialsTest(g1, "A ") == false);
       REQUIRE(checkInitialsTest(g1, "") == false);
   }
   SECTION("valid initials inputs")
   {
       REQUIRE(checkInitialsTest(g1, "LO") == true);
       REQUIRE(checkInitialsTest(g1, "Wa") == true);
       REQUIRE(checkInitialsTest(g1, "qq") == true);
       REQUIRE(checkInitialsTest(g1, "iI") == true);
   }

}

//GameEngine
//Test case for getScore()
//Test case for getWinner()
TEST_CASE( "score and winner data can be accessed", "[GameEngine]" ) {

   GameEngine e1({1,2}, 2, 2);
   setWinnerAndScore(e1, 0, 6);
   REQUIRE(e1.getWinner() == 0);
   REQUIRE(e1.getScore() == 6);

   setWinnerAndScore(e1, 1, 100);
   REQUIRE(e1.getWinner() == 1);
   REQUIRE(e1.getScore() == 100);

}
//Test case for calculateScore()
TEST_CASE( "scores can be calculated", "[GameEngine]" ) {

   GameEngine e1({1,2}, 2, 2);
   SECTION("calculating the score with varying winners")
   {
       setNAndDiff(e1, 9, 9);
       setWinnerAndScore(e1, 1, 0);
       calculateScoreTest(e1);
       REQUIRE(e1.getScore() == 180);

       setWinnerAndScore(e1, -1, 0);
       calculateScoreTest(e1);
       REQUIRE(e1.getScore() == 9);

       setWinnerAndScore(e1, 0, 0);
       calculateScoreTest(e1);
       REQUIRE(e1.getScore() == 90);
   }
   SECTION("calculating the score with varying \"n\" and \"diff\"")
   {
       setWinnerAndScore(e1, 0, 0);
       setNAndDiff(e1, 2, 9);
       calculateScoreTest(e1);
       REQUIRE(e1.getScore() == 20);

       setNAndDiff(e1, 5, 9);
       calculateScoreTest(e1);
       REQUIRE(e1.getScore() == 50);

       setNAndDiff(e1, 9, 4);
       calculateScoreTest(e1);
       REQUIRE(e1.getScore() == 45);

       setNAndDiff(e1, 9, 7);
       calculateScoreTest(e1);
       REQUIRE(e1.getScore() == 72);
   }
}

//AI
//Test case for select()
TEST_CASE( "pancake stack indices can be selected", "[AI]" ) {
	SECTION("AI for size 5"){
	   AI a1({1,2,3,4,5}, NULL, 9);
	   int index = a1.select();
	   REQUIRE(index == 0);
	}
	SECTION("AI for size 6"){
	   AI a1({5,4,3,2,1,6}, NULL, 9);
	   int index = a1.select();
	   REQUIRE(index == 5);	
	}
		SECTION("AI for size 7"){
	   AI a1({5,4,3,2,1,6,7}, NULL, 9);
	   int index = a1.select();
	   REQUIRE(index == 5);	
	}
		SECTION("AI for size 8"){
	   AI a1({2,1,3,4,5,6,7,8}, NULL, 9);
	   int index = a1.select();
	   REQUIRE(index == 2);	
	}
		SECTION("AI for size 9"){
	   AI a1({5,4,3,1,2,6,7,8,9}, NULL, 9);
	   int index = a1.select();
	   REQUIRE(index == 5);	
	}
}

//PancakeStack
//Test case for flip()
TEST_CASE( "pancake stacks can be flipped", "[PancakeStack]" ) {

   PancakeStack p({2,1,3,4,5},NULL);
   p.flip(2);
   vector<int> result = {1,2,3,4,5};
   REQUIRE(p.getOrder() == result);

   p.flip(5);
   result = {5,4,3,2,1};
   REQUIRE(p.getOrder() == result);

}

//Test case for isSorted()
TEST_CASE( "sorted pancake stacks can be determined for isSorted", "[PancakeStack]" ) {
   PancakeStack p({1,2,3,4,5},NULL);
   REQUIRE(p.isSorted() == true);

   PancakeStack p1({1,2,3,4,5,6,7,8,9},NULL);
   REQUIRE(p1.isSorted() == true);
}

//Test case for getOrder()
TEST_CASE( "pancake stack orders can be accessed", "[PancakeStack]" ) {
    PancakeStack p({1,2,3,4,5},NULL);
    vector<int> result = {1,2,3,4,5};
    REQUIRE(p.getOrder() == result);

    PancakeStack p1({1,3,2,5,4,7,6,9,8},NULL);
    result = {1,3,2,5,4,7,6,9,8};
    REQUIRE(p1.getOrder() == result);
}

//Test case for requestHint()
TEST_CASE( "pancake hint indices can be obtained", "[PancakeStack]" ) {
	SECTION("for size 4"){
    	PancakeStack p({4,1,2,3},NULL);
    	REQUIRE(p.requestHint() == 4);
	}
	SECTION("for size 5"){
    	PancakeStack p({2,1,3,4,5},NULL);
   		REQUIRE(p.requestHint() == 2);
	}
	SECTION("for size 6"){
    	PancakeStack p({5,4,3,2,1,6},NULL);
    	REQUIRE(p.requestHint() == 5);
	}
	SECTION("for size 7"){
    	PancakeStack p({5,4,3,2,1,6,7},NULL);
    	REQUIRE(p.requestHint() == 5);
	}
	SECTION("for size 8"){
    	PancakeStack p({2,1,3,4,5,6,7,8},NULL);
    	REQUIRE(p.requestHint() == 2);
	}	
	SECTION("for size 9"){
    	PancakeStack p({5,4,3,1,2,6,7,8,9},NULL);
    	REQUIRE(p.requestHint() == 5);
	}
}


