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

enum direction_t { Down, Up, Right, Left, NotDefined };

struct result_t {
	long long eval;
	direction_t direction;
};

struct result_t minmax(Board board, int playerIndex, int depth);

#define MAX_DEPTH 7

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

	int playerIndex = 1;

	while(1) {
		if(!board.canMakeMove()) {
			cout<<"Thats the end of it"<<endl;
			break;
		}

		struct result_t result = minmax(board, playerIndex, 0);

		// int pause;
		// cin>>pause;

		switch(result.direction) {
			case Down:
				board.moveToBottom();
				break;
			case Up:
				board.moveToTop();
				break;
			case Right:
				board.moveToRight();
				break;
			case Left:
				board.moveToLeft();
				break;
			case NotDefined:
				cout<<"Nothing left to do"<<endl;
				board.printBoard();
				return 0;
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

struct result_t minmax(Board board, int playerIndex, int depth) {
	
	if(depth == MAX_DEPTH) {
		struct result_t result;
		result.direction = NotDefined;
		result.eval = board.evaluate();
		return result;
	}

	/*
	 * Player index = 1, meaning out turn to play the game
	 * Player index = -1, meaning computer is going to randomly insert a tile
	 */

	 if(playerIndex == 1) {
	 	struct result_t results[4];

	 	for(int i=0;i<4;i++) {
	 		Board newBoard(board);
	 		switch((direction_t)i) {
	 		case Down:
		 		newBoard.moveToBottom();
		 		break;
	 		case Up:
	 			newBoard.moveToTop();
	 			break;
	 		case Right:
	 			newBoard.moveToRight();
	 			break;
	 		case Left:
	 			newBoard.moveToLeft();
	 			break;
	 		case NotDefined:
	 			cout<<"Not defined in the evaluation of player 1 index"<<endl;
	 			break;
		 	}
		 	results[i] = minmax(newBoard, (playerIndex * -1), (depth + 1));
		 }
		 long long maxValue = -1;
		 int index = -1;
		 for(int i=0;i<4;i++) {
		 	if(results[i].eval > maxValue) {
		 		index = i;
		 		maxValue = results[i].eval;
		 	}
		 }
		 struct result_t result;
		 result.eval = maxValue;
		 result.direction = (direction_t)index;
		 return result;
	}

	// This is the case where the computer puts a random tile and we are going to do an exhaustive search
	vector<int> availableCells = board.availableCells();

	if(availableCells.size() == 0) {
		struct result_t result;
		result.eval = board.evaluate();
		result.direction = NotDefined;
		return result;
	}

	vector<struct result_t> results;

	for(std::vector<int>::size_type i = 0; i != availableCells.size(); i++) {
    		Board newBoard(board);
    		int pos = availableCells[i];
    		int posi = pos/4;
    		int posj = pos%4;
    		newBoard.insertTile(posi, posj, 2);
    		struct result_t newResult = minmax(newBoard, (playerIndex * -1), (depth + 1));
    		results.push_back(newResult);
	}

	long long minValue = LONG_LONG_MAX;
	int index = -1;

	for(std::vector<int>::size_type i = 0; i != results.size(); i++) {
		if(results[i].eval < minValue) {
			minValue = results[i].eval;
			index = i;
		}
	}

	return results[index];

}
