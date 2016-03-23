#pragma once
#include <vector>
#include <iostream>
#include <string>

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
	struct GoStone {
		Board::Status color;
		Board::Coordinate position;
	};

	Board(unsigned int size);
	Board(Board::Coordinate inputCoordinate);
	Board(unsigned int xDimInput, unsigned int yDimInput);
	bool putConcaveStone(Coordinate inputCoordinate, Board::Status statusValue);
	bool isFull();
	vector< vector< Board::Status > > getBoard();
	Board::Coordinate getBoardSize();
	void printBoard();














private:
	int xDimSize = 0;
	int yDimSize = 0;
	int maxStoneNum;
	int currentStoneNum = 0;
	string stringForDisplay;
	vector< vector< Board::Status > > boardMatrix;

	void assignBoard(int x, int y);
	bool checkBoundry(Board::Coordinate inputCoordinate);
	bool checkIsStatusNone(Board::Coordinate inputCoordinate);
	void displayStringMake();
	char statusToChar(Board::Coordinate boardSize, Board::Coordinate pointCoordinate, Board::Status color);
};