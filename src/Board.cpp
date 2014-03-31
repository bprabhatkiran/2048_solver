/*
 * Board.cpp
 *
 *  Created on: Mar 29, 2014
 *      Author: prabhatkiran
 */

#include "Board.h"

#include <iostream>
#include <vector>

using namespace std;

Board::Board(const Board& board) {
	for (int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			matrix[i][j] = board.matrix[i][j];
		}
	}
}

Board::Board(const unsigned short input[4][4]) {
	for (int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			matrix[i][j] = input[i][j];
		}
	}
}

void Board::printBoard() {
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			cout<<"\t\t"<<matrix[i][j]<<"\t\t";
		}
		cout<<endl;
	}
}

void Board::insertTile(int posi, int posj, int value) {
	this->matrix[posi][posj] = value;
}

vector<int> Board::availableCells() {
	vector<int> availableCells;

	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			if(matrix[i][j] == 0) {
				int pos = i*4 + j;
				availableCells.push_back(pos);
			}
		}
	}
	return availableCells;
}

bool Board::isEqual(const Board& board) {
	bool result = true;
	for(int i = 0;i<4;i++) {
		for (int j=0;j<4;j++) {
			if (matrix[i][j] != board.matrix[i][j]) {
				return false;
			}
		}
	}
	return result;
}

bool Board::canMakeMove() {

	Board board1(*this);
	Board board2(*this);
	Board board3(*this);
	Board board4(*this);

	board1.moveToBottom();
	board2.moveToRight();
	board3.moveToTop();
	board4.moveToLeft();

	if(this->isEqual(board1) && this->isEqual(board2) && this->isEqual(board3) && this->isEqual(board4)) {
		return false;
	}
	return true;
}

void Board::addRandomTile() {
	vector<int> availableCells = this->availableCells();
	int index = rand()%availableCells.size();
	int pos = availableCells.at(index);

	int i = pos/4;
	int j = pos%4;
	int val = 2;

	int random = rand()%90;
	if(random > 90) {
		val = 4;
	}
	insertTile(i, j, val);
}

void Board::moveToRight() {
	int i = 0,j = 0;
	for (i=0;i<4; i++) {
		// For each row, move the units to the right starting from the right
		for(j=2;j>=0;j--) {
			if(matrix[i][j] <= 0)
	 			continue;
			moveTileToTheRight(i,j);
		}
	}
	for (i=0;i<4; i++) {
		for(j=0;j<4;j++) {
			if(matrix[i][j] < 0)
	 			matrix[i][j] = 0;
		}
	}
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
	} else if(matrix[i][j+1] < 0) {
		matrix[i][j+1] = matrix[i][j];
		matrix[i][j] = 0;
	} else if(matrix[i][j+1] == matrix[i][j]) {
		// Merge it and make way for the next tile
		matrix[i][j+1] = matrix[i][j+1] << 1;
		// Mark it as -1, so that we dont merge anything after that
		matrix[i][j] = -1;
	}
	// Oh good, you can do nothing, just return
	return;
}

void Board::moveToLeft() {
	int i = 0,j = 0;
	for (i=0;i<4; i++) {
		// For each row, move the units to the left starting from the left
		for(j=1;j<=3;j++) {
			if(matrix[i][j] <= 0)
	 			continue;
			moveTileToTheLeft(i,j);
		}
	}

	for (i=0;i<4; i++) {
		for(j=0;j<4;j++) {
			if(matrix[i][j] < 0)
	 			matrix[i][j] = 0;
		}
	}
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
	} else if(matrix[i][j-1] < 0) {
		matrix[i][j-1] = matrix[i][j];
		matrix[i][j] = 0;
	} else if(matrix[i][j-1] == matrix[i][j]) {
		// Merge it and make way for the next tile
		matrix[i][j-1] = matrix[i][j-1] << 1;
		matrix[i][j] = -1;
	}
	// Oh good, you can do nothing, just return
	return;
}

void Board::moveToTop() {
	int i = 0,j = 0;
	for (j=0;j<4; j++) {
		// For each column, move the units to the top starting from the top
		for(i=1;i<4;i++) {
			if(matrix[i][j] <= 0)
	 			continue;
			moveTileToTheTop(i,j);
		}
	}

	for (i=0;i<4; i++) {
		for(j=0;j<4;j++) {
			if(matrix[i][j] < 0)
	 			matrix[i][j] = 0;
		}
	}
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
	} else if(matrix[i-1][j] < 0) {
		matrix[i-1][j] = matrix[i][j];
		matrix[i][j] = 0;
	} else if(matrix[i-1][j] == matrix[i][j]) {
		// Merge it and make way for the next tile
		matrix[i-1][j] = matrix[i-1][j] << 1;
		matrix[i][j] = -1;
	}
	// Oh good, you can do nothing, just return
	return;
}

void Board::moveToBottom() {
	int i = 0,j = 0;
	for (j=0;j<4; j++) {
		// For each column, move the units to the bottom starting from the bottom
		for(i=2;i>=0;i--) {
			if(matrix[i][j] <= 0)
	 			continue;
			moveTileToTheBottom(i,j);
		}
	}

	for (i=0;i<4; i++) {
		for(j=0;j<4;j++) {
			if(matrix[i][j] < 0)
	 			matrix[i][j] = 0;
		}
	}
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
	} else if(matrix[i+1][j] < 0) {
		matrix[i+1][j] = matrix[i][j];
		matrix[i][j] = 0;
	} else if(matrix[i+1][j] == matrix[i][j]) {
		// Merge it and make way for the next tile
		matrix[i+1][j] = matrix[i+1][j] << 1;
		matrix[i][j] = -1;
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

	int emptySpaces = 0;

	int maxValue = -1;
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			if(matrix[i][j] == 0) {
				emptySpaces++;
			} else if(maxValue < matrix[i][j]) {
				maxValue = matrix[i][j];
				posi = i;
				posj = j;
			} else if(maxValue == matrix[i][j]) {
				// Lets keep it in the corners
				if (((i == 0) || (i == 3)) && ((j == 0) || (j == 3))) {
					posi = i;
					posj = j;
				}
			}
		}
	}

	eval += (emptySpaces * 2000);

	if(!canMakeMove()) {
		return ((8192/maxValue) * 100);
	} else {
		if((posi == 0 || posi == 3) && (posj == 0 || posj == 3)) {
			eval += ((8192/maxValue) * 10000);
		} else {
			eval += ((8192/maxValue) * 2500);
		}
	}

	int maxRow = -1;
	int row = -1;

	int maxCol = -1;
	int col = -1;

	for(int j=0;j<4;j++) {
		for(int i=0;i<4;i++) {
			if(matrix[i][j] > maxCol) {
				maxCol = matrix[i][j];
				col = j;
			}
		}
		if(col == 0 || col == 3) {
			eval += 1000;
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
		}
		// End of the row, decide the heuristic value
		if(row==0 || row==3) {
			eval += 1000;
		}
	}

	return eval;
}

