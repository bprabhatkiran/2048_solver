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

struct result_t alpha_beta(Board board, int playerIndex, int depth, struct result_t alpha, struct result_t beta);
struct result_t maximum(struct result_t a, struct result_t b);
struct result_t minimum(struct result_t a, struct result_t b);

#define MAX_DEPTH 4

int main() {

	unsigned short input[4][4] = {0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0};
	// unsigned short input[4][4] = {0,0,0,2,0,0,8,128,128,2,64,2,2,32,128,8};

	Board board(input);

	unsigned short position[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

	Board positionBoard(position);

	struct result_t alpha;
	alpha.eval = LONG_LONG_MIN;
	alpha.direction = NotDefined;

	struct result_t beta;
	beta.eval = LONG_LONG_MAX;
	beta.direction = NotDefined;

	while(1) {
		if(!board.canMakeMove()) {
			cout<<"Thats the end of it"<<endl;
			board.printBoard();
			break;
		}

		cout<<"Solving this board"<<endl;
		board.printBoard();

		struct result_t result = alpha_beta(board, 1, 0, alpha, beta);


		switch(result.direction) {
			case Down:
				cout<<"Moved down"<<endl;
				board.moveToBottom();
				break;
			case Up:
				cout<<"Moved up"<<endl;
				board.moveToTop();
				break;
			case Right:
				cout<<"Moved right"<<endl;
				board.moveToRight();
				break;
			case Left:
				cout<<"Moved left"<<endl;
				board.moveToLeft();
				break;
			case NotDefined:
				cout<<"How did the control get here"<<endl;
				board.printBoard();
				return 0;
		}
		// Instead get the state from the user
		board.addRandomTile();
	}

	return 0;
}

struct result_t alpha_beta(Board board, int playerIndex, int depth, struct result_t alpha, struct result_t beta) {
	
	if(depth == MAX_DEPTH || (playerIndex == 1 && !board.canMakeMove()) || (playerIndex == -1 && board.availableCells().size() == 0)) {
		struct result_t result;
		result.direction = NotDefined;
		result.eval = board.evaluate();
		return result;
	}

	/*
	 * Player index = 1, meaning our turn to play the game
	 * Player index = -1, meaning computer is going to randomly insert a tile
	 */

	 if(playerIndex == 1) {
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
	 		default:
	 			break;
		 	}

		 	if(newBoard.isEqual(board)) {
		 		continue;
		 	}

	 		struct result_t child_result = alpha_beta(newBoard, (playerIndex * -1), (depth + 1), alpha, beta);
	 		child_result.direction = (direction_t)i;

	 		// if(depth == 0) {
	 		// 	if(newBoard.is_monotonous()) {
	 		// 		cout<<"Child is monotonous"<<endl;
	 		// 	} else {
	 		// 		cout<<"Child is not monotonous"<<endl;
	 		// 	}
	 		// 	newBoard.printBoard();
	 		// 	cout<<endl;
	 		// 	cout<<"Direction:\t"<<child_result.direction<<endl;
	 		// 	cout<<"Result:\t"<<child_result.eval<<endl;
	 		// 	cout<<endl;
	 		// }

	 		alpha = maximum(alpha, child_result);

	 		if(beta.eval <= alpha.eval)
	 			break;
		 }
		 return alpha;
	}

	vector<int> availableCells = board.availableCells();
	for(std::vector<int>::size_type i = 0; i != availableCells.size(); i++) {
    		Board newBoard(board);
    		int pos = availableCells[i];
    		int posi = pos/4;
    		int posj = pos%4;
    		newBoard.insertTile(posi, posj, 2);
    		struct result_t child_result = alpha_beta(newBoard, (playerIndex * -1), (depth + 1), alpha, beta);
    		beta = minimum(beta, child_result);
    		if(beta.eval <= alpha.eval)
    			break;
	}
	return beta;
}

struct result_t maximum(struct result_t a, struct result_t b) {
	return (a.eval>b.eval) ? a: b;
}

struct result_t minimum(struct result_t a, struct result_t b) {
	return (a.eval<b.eval) ? a: b;
}
