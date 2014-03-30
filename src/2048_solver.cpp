//============================================================================
// Name        : 2048_solver.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#define MAX_DEPTH 8

int main() {
	Board board;

	while(1) {
		solve(board);
	}

	return 0;
}

void solve(Board board) {
	// Assume we have the board for now.
	int val1, val2, val3, val4;

	Board board1 = board.boardAfterMoveToBottom();
	board1.addRandomTile();

	Board board2 = board.boardAfterMoveToTop();
	board2.addRandomTile();

	Board board3 = board.boardAfterMoveToRight();
	board3.addRandomTile();

	Board board4 = board.boardAfterMoveToLeft();
	board4.addRandomTile();

	val1 = evaluate(board1, 1);
	val2 = evaluate(board2, 1);
	val3 = evaluate(board3, 1);
	val4 = evaluate(board4, 1);

	int direction = moveToMake(val1, val2, val3, val4);

	switch(direction) {
	case 0:
		cout<<"Move down"<<endl;
		board1.printBoard();
		break;
	case 1:
		cout<<"Move Top"<<endl;
		board2.printBoard();
		break;
	case 2:
		cout<<"Move Right"<<endl;
		board3.printBoard();
		break;
	case 3:
		cout<<"Move Left"<<endl;
		board4.printBoard();
		break;
	}
}

long long evaluate(Board board, int depth) {
	if(depth == MAX_DEPTH) {
		return board.evaluate();
	}

	int val1, val2, val3, val4;

	Board board1 = board.boardAfterMoveToBottom();
	board1.addRandomTile();

	Board board2 = board.boardAfterMoveToTop();
	board2.addRandomTile();

	Board board3 = board.boardAfterMoveToRight();
	board3.addRandomTile();

	Board board4 = board.boardAfterMoveToLeft();
	board4.addRandomTile();

	val1 = evaluate(board1, depth+1);
	val2 = evaluate(board2, depth+1);
	val3 = evaluate(board3, depth+1);
	val4 = evaluate(board4, depth+1);

	return maxFourLong(val1, val2, val3, val4);
}

long long maxFourLong(long long a, long long b, long long c, long long d) {
	if(a > b) {
		if(a > c) {
			if(a > d) {
				return a;
			} else {
				return d;
			}
		} else if(c > d) {
			return c;
		}
	} else {
		if (b > c) {
			if (b > d) {
				return b;
			} else {
				return d;
			}
		}
		else {
			if (c > d) {
				return c;
			} else {
				return d;
			}
		}
	}
	return a;
}

int moveToMake(long long a, long long b, long long c, long long d) {
	if(a > b) {
		if(a > c) {
			if(a > d) {
				return 0;
			} else {
				return 3;
			}
		} else if(c > d) {
			return 2;
		}
	} else {
		if (b > c) {
			if (b > d) {
				return 1;
			} else {
				return 3;
			}
		}
		else {
			if (c > d) {
				return 2;
			} else {
				return 3;
			}
		}
	}
	return 0;
}
