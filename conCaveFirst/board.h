#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Board {
public:
	enum Status {
		black = -1,
		none = 0,
		white = 1
	};
	struct Coordinate {
		int x;
		int y;
	};

	Board(unsigned int size);
	Board(Board::Coordinate inputCoordinate);
	Board(unsigned int xDimInput, unsigned int yDimInput);
	bool putConcaveStone(Coordinate inputCoordinate, Board::Status statusValue);
	vector< vector< Board::Status > > getBoard();
	Board::Coordinate getBoardSize();
	void printBoard();














private:
	int xDimSize = 0;
	int yDimSize = 0;
	vector< vector< Board::Status > > instanceBoard;

	void assignBoard(int x, int y);
	bool checkBoundry(Coordinate inputCoordinate);
	bool checkIsStatusNone(Coordinate inputCoordinate);
};