#include "gtest.h"
#include "GameRunner.h"
#include "HumanPlayer.h"

Board createBoard1ForExample();
Board createBoard2ForExample();
Board createBoard3ForExample();

TEST(GameRunnerTests, CanContinue) {
	Board b1 = createBoard1ForExample();
	Board b2 = createBoard2ForExample();
	Board b3 = createBoard3ForExample();
	HumanPlayer p1('X');
	HumanPlayer p2('O');
	GameRunner gr1(b1, p1, p2, 'X');
	GameRunner gr2(b2, p1, p2, 'X');
	GameRunner gr3(b3, p1, p2, 'X');

	EXPECT_TRUE(gr1.canToContinue());
	EXPECT_TRUE(gr2.canToContinue());
	EXPECT_FALSE(gr3.canToContinue());

}


