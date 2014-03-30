/*
 * Board.h
 *
 *  Created on: Mar 29, 2014
 *      Author: prabhatkiran
 */

#ifndef BOARD_H_
#define BOARD_H_

class Board {
	unsigned short matrix[4][4];

	void moveTileToTheRight(int i,int j);
	void moveTileToTheLeft(int i,int j);
	void moveTileToTheTop(int i,int j);
	void moveTileToTheBottom(int i,int j);
public:
	Board(const Board& board);
	Board boardAfterMoveToRight();
	Board boardAfterMoveToLeft();
	Board boardAfterMoveToTop();
	Board boardAfterMoveToBottom();
	void addRandomTile();
	long long evaluate();

	void printBoard();
};

#endif /* BOARD_H_ */
