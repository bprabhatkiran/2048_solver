/*
 * Board.h
 *
 *  Created on: Mar 29, 2014
 *      Author: prabhatkiran
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>

enum monotonicity { Increasing, Decreasing, Equal, Undefined };

using namespace std;

class Board {
	// -1 has a special significance in the board
	signed short matrix[4][4];

	void moveTileToTheRight(int i,int j);
	void moveTileToTheLeft(int i,int j);
	void moveTileToTheTop(int i,int j);
	void moveTileToTheBottom(int i,int j);
	int smoothness_count(int i, int j);
	int possible_merges(int i, int j);
public:
	Board(const Board& board);
	Board(const unsigned short input[4][4]);

	monotonicity rowMonotonicity(int i);
	monotonicity colMonotonicity(int j);

	void moveToRight();
	void moveToLeft();
	void moveToTop();
	void moveToBottom();

	vector<int> availableCells();
	bool canMakeMove();

	void addRandomTile();
	void insertTile(int posi, int posj, int value);

	long long evaluate();

	void printBoard();

	bool isEqual(const Board& board);

	bool is_monotonous();
};

#endif /* BOARD_H_ */
