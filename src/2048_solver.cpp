//============================================================================
// Name        : 2048_solver.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Board.h"

using namespace std;

int solve(Board board);
long long evaluate(Board board, int depth);
long long maxFourLong(long long a, long long b, long long c, long long d);
int moveToMake(long long a, long long b, long long c, long long d);

#define MAX_DEPTH 8

int main() {

	// unsigned short input[4][4] = {0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0};
	unsigned short input[4][4] = {2,4,16,8,16,8,4,0,4,0,0,0,2,0,0,0};

	unsigned short position[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

	Board positionBoard(position);

	// cout <<"Enter the numbers in this order:"<<endl<<endl;
	// positionBoard.printBoard();

	// for(int i=0;i<4;i++) {
	// 	for(int j=0;j<4;j++) {
	// 		cin>>input[i][j];
	// 	}
	// }

	Board board(input);
	board.printBoard();

	while(1) {
		if(!board.canMakeMove()) {
			cout<<"Thats the end of it"<<endl;
			break;
		}

		int result = solve(board);

		// int pause;
		// cin>>pause;

		switch(result) {
			case 0:
				board.moveToBottom();
				break;
			case 1:
				board.moveToTop();
				break;
			case 2:
				board.moveToRight();
				break;
			case 3:
				board.moveToLeft();
				break;
		}
		board.printBoard();
		
		// Get the next board
		// cout<<endl<<endl;
		// int i, j, pos;
		// int val;
		// cin>>pos;
		// i = pos/4;
		// j = pos%4;
		// cin>>val;
		// board.insertTile(i, j, val);
		board.addRandomTile();
	}

	return 0;
}

int solve(Board board) {
	// Assume we have the board for now.
	int val1, val2, val3, val4;

	Board board1 = board;
	board1.moveToBottom();
	// cout<<"Bottom move"<<endl;
	// board1.printBoard();
	if(board1.canMakeMove())
		board1.addRandomTile();

	Board board2 = board;
	board2.moveToTop();
	// cout<<"Top move"<<endl;
	// board2.printBoard();
	if(board2.canMakeMove())
		board2.addRandomTile();

	Board board3 = board;
	board3.moveToRight();
	// cout<<"Right move"<<endl;
	// board3.printBoard();
	if(board3.canMakeMove())
		board3.addRandomTile();

	Board board4 = board;
	board4.moveToLeft();
	// cout<<"Left move"<<endl;
	// board4.printBoard();
	if(board4.canMakeMove())
		board4.addRandomTile();

	val1 = evaluate(board1, 1);
	val2 = evaluate(board2, 1);
	val3 = evaluate(board3, 1);
	val4 = evaluate(board4, 1);

	int direction = moveToMake(val1, val2, val3, val4);

	return direction;
}

long long evaluate(Board board, int depth) {
	if(depth == MAX_DEPTH) {
		return board.evaluate();
	}

	int val1, val2, val3, val4;

	Board board1 = board;
	board1.moveToBottom();
	if(board1.canMakeMove())
		board1.addRandomTile();

	Board board2 = board;
	board2.moveToTop();
	if(board2.canMakeMove())
		board2.addRandomTile();

	Board board3 = board;
	board3.moveToRight();
	if(board3.canMakeMove())
		board3.addRandomTile();

	Board board4 = board;
	board4.moveToLeft();
	if(board4.canMakeMove())
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
