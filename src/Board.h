/*
 * Board.h
 *
 *  Created on: Mar 29, 2014
 *      Author: prabhatkiran
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>

using namespace std;

class Board {
	unsigned short matrix[4][4];

	void moveTileToTheRight(int i,int j);
	void moveTileToTheLeft(int i,int j);
	void moveTileToTheTop(int i,int j);
	void moveTileToTheBottom(int i,int j);
public:
	Board(const Board& board);
	Board(const unsigned short input[4][4]);

	Board boardAfterMoveToRight();
	Board boardAfterMoveToLeft();
	Board boardAfterMoveToTop();
	Board boardAfterMoveToBottom();

	vector<int> availableCells();
	bool canMakeMove();

	void addRandomTile();
	void insertTile(int posi, int posj, int value);

	long long evaluate();

	void printBoard();
};

#endif /* BOARD_H_ */
