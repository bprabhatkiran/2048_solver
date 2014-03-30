/*
 * Board.cpp
 *
 *  Created on: Mar 29, 2014
 *      Author: prabhatkiran
 */

#include "Board.h"

#include <iostream>

using namespace std;

Board::Board(const Board& board) {
	int i = 0,j = 0;

	for (;i<4;i++) {
		for(;j<4;j++) {
			this->matrix[i][j] = board.matrix[i][j];
		}
	}
}

void Board::printBoard() {
	cout<<"Printing the matrix"<<endl<<endl;

	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			cout<<"\t\t"<<matrix[i][j]<<"\t\t";
		}
		cout<<endl;
	}
}

Board Board::boardAfterMoveToRight() {
	Board nextBoard = *this;

	int i = 0,j = 0;
	for (;i<4; i++) {
		// For each row, move the units to the right starting from the right
		for(j=2;j>=0;j--) {
			moveTileToTheRight(i,j);
		}
	}
	return nextBoard;
}

void Board::moveTileToTheRight(int i, int j) {
	if(j>=3 || j<0) {
		return;
	}

	/*
	 * There are three possiblities for this
	 * 1. The immediate tile on the right is empty
	 * 2. The tile on the right has the same value as the current one
	 * 3. The tile on the right has a different value
	 */

	if(matrix[i][j+1] == 0) {
		// Just fucking move the tile the right and re-iterate it
		matrix[i][j+1] = matrix[i][j];
		matrix[i][j] = 0;
		moveTileToTheRight(i,j+1);
	} else if(matrix[i][j+1] == matrix[i][j]) {
		// Merge it and make way for the next tile
		matrix[i][j+1] = matrix[i][j+1] << 1;
		matrix[i][j] = 0;
	}
	// Oh good, you can do nothing, just return
	return;
}

Board Board::boardAfterMoveToLeft() {
	Board nextBoard = *this;

	int i = 0,j = 0;
	for (;i<4; i++) {
		// For each row, move the units to the left starting from the left
		for(j=1;j<=3;j++) {
			moveTileToTheLeft(i,j);
		}
	}
	return nextBoard;
}

void Board::moveTileToTheLeft(int i, int j) {
	if(j>3 || j<=0) {
		return;
	}

	/*
	 * There are three possiblities for this
	 * 1. The immediate tile on the left is empty
	 * 2. The tile on the left has the same value as the current one
	 * 3. The tile on the left has a different value
	 */

	if(matrix[i][j-1] == 0) {
		matrix[i][j-1] = matrix[i][j];
		matrix[i][j] = 0;
		moveTileToTheLeft(i,j-1);
	} else if(matrix[i][j-1] == matrix[i][j]) {
		// Merge it and make way for the next tile
		matrix[i][j-1] = matrix[i][j-1] << 1;
		matrix[i][j] = 0;
	}
	// Oh good, you can do nothing, just return
	return;
}

Board Board::boardAfterMoveToTop() {
	Board nextBoard = *this;

	int i = 0,j = 0;
	for (;j<4; j++) {
		// For each column, move the units to the top starting from the top
		for(i=1;i<4;i++) {
			moveTileToTheTop(i,j);
		}
	}

	return nextBoard;
}

void Board::moveTileToTheTop(int i, int j) {
	if(i>3 || i<=0) {
		return;
	}

	/*
	 * There are three possiblities for this
	 * 1. The immediate tile on the top is empty
	 * 2. The tile on the top has the same value as the current one
	 * 3. The tile on the top has a different value
	 */

	if(matrix[i-1][j] == 0) {
		matrix[i-1][j] = matrix[i][j];
		matrix[i][j] = 0;
		moveTileToTheTop(i,j-1);
	} else if(matrix[i-1][j] == matrix[i][j]) {
		// Merge it and make way for the next tile
		matrix[i-1][j] = matrix[i-1][j] << 1;
		matrix[i][j] = 0;
	}
	// Oh good, you can do nothing, just return
	return;
}

Board Board::boardAfterMoveToBottom() {
	Board nextBoard = *this;

	int i = 0,j = 0;
	for (;j<4; j++) {
		// For each column, move the units to the bottom starting from the bottom
		for(i=2;i>=0;i--) {
			moveTileToTheBottom(i,j);
		}
	}

	return nextBoard;
}

void Board::moveTileToTheBottom(int i, int j) {
	if(i>=3 || i<0) {
		return;
	}

	/*
	 * There are three possiblities for this
	 * 1. The immediate tile on the bottom is empty
	 * 2. The tile on the bottom has the same value as the current one
	 * 3. The tile on the bottom has a different value
	 */

	if(matrix[i+1][j] == 0) {
		matrix[i+1][j] = matrix[i][j];
		matrix[i][j] = 0;
		moveTileToTheBottom(i+1,j);
	} else if(matrix[i+1][j] == matrix[i][j]) {
		// Merge it and make way for the next tile
		matrix[i+1][j] = matrix[i+1][j] << 1;
		matrix[i][j] = 0;
	}
	// Oh good, you can do nothing, just return
	return;
}

long long Board::evaluate() {
	/*
	 * Lets keep it simple.
	 * 1. We want the highest valued tile in the corners. (500)
	 * 2. For each row and column, keep the highest tile on the edge. (100)
	 * 3. We want more space to make more moves. So count the number of empty spaces. (10)
	 */

	long long eval = 0;

	int posi = -1;
	int posj = -1;
	int maxValue = -1;

	int maxRow = -1;
	int row = -1;

	int maxCol = -1;
	int col = -1;

	int numEmptySpaces = 0;

	for(int j=0;j<4;j++) {
		for(int i=0;i<4;i++) {
			if(matrix[i][j] > maxCol) {
				maxCol = matrix[i][j];
				col = j;
			}
		}
		if(col == 0 || col == 3) {
			eval += 100;
		}
		maxCol = -1;
		col = -1;
	}

	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			if(matrix[i][j] > maxRow) {
				maxRow = matrix[i][j];
				row = j;
			}
			if(matrix[i][j] > maxValue) {
				maxValue = matrix[i][j];
				posi = i;
				posj = j;
			}
			if(matrix[i][j] == 0) {
				numEmptySpaces++;
			}
		}
		// End of the row, decide the heuristic value
		if(row==0 || row==3) {
			eval += 100;
		}
		maxValue = -1;
		row = -1;
	}
	if((posi == 0 || posi == 3) && (posj == 0 || posj == 3)) {
		eval += 500;
	}

	eval += (numEmptySpaces * 10);

	return eval;
}

