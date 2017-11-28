#include "Board.h"
#include "gtest.h"

Board createBoard1ForExample();
Board createBoard2ForExample();

Board createBoard3ForExample() {
	Board board;
	int t;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			t = i*i + j*i;
			t = t%2;
			if (t == 0) {
				board.enterToBoard('O', i, j);
			} else {
				board.enterToBoard('X', i, j);
			}
		}
	}
	return board;
}

TEST(BoardTest, FullTest) {
	Board b1 = createBoard1ForExample();
	Board b2 = createBoard2ForExample();
	Board b3 = createBoard3ForExample();
	EXPECT_TRUE(b3.isBoardFull());
	EXPECT_FALSE(b1.isBoardFull());
	EXPECT_FALSE(b2.isBoardFull());
}

TEST(BoardTest, HowMuchTest) {
	Board b1 = createBoard1ForExample();
	Board b2 = createBoard2ForExample();
	Board b3 = createBoard3ForExample();

	EXPECT_EQ(b1.howMuchCells('X'), 5);
	EXPECT_EQ(b1.howMuchCells('O'), 4);
	EXPECT_EQ(b2.howMuchCells('X'), 7);
	EXPECT_EQ(b2.howMuchCells('O'), 4);
	EXPECT_EQ(b3.howMuchCells('X'), 16);
	EXPECT_EQ(b3.howMuchCells('O'), 48);

}


