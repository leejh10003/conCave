#pragma once
#include <vector>
#include <iostream>

using namespace std;

class board {
public:
	enum status {
		black = -1,
		none = 0,
		white = 1
	};

	board(unsigned int size);
	board(unsigned int xDimInput, unsigned int yDimInput);
	bool putConcaveStone(int xCoordinate, int yCoordinate, board::status statusValue);
	vector< vector< board::status > > getBoard();
	int getXdimSize();
	int getYdimSize();














private:
	int xDimSize = 0;
	int yDimSize = 0;
	vector< vector< board::status > > instanceBoard;

	void assignBoard(int x, int y);
	bool checkBoundry(int xCoordinate, int yCoordinate);
	bool checkIsStatusNone(int xCoordinate, int yCoordinate);
};