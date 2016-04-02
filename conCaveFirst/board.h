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
	/// <summary>
	/// This constructor allocates concaveBoard matrix and dimensions size for square board
	/// </summary>
	/// <param name="size">
	/// One dimension's size for square board
	/// </param>
	Board(unsigned int size);
	bool putConcaveStone(Board::Coordinate inputCoordinate, Board::Status statusValue);
	/// <summary>
	/// This function query weather the board is full
	/// </summary>
	bool isFull();
	/// <summary>
	/// This function return matrix of stone color
	/// </summary>
	vector< vector< Board::Status > > getBoard();
	/// <summary>
	/// This function return board's each dimension's size in euclidian coordination
	/// </summary>
	Board::Coordinate getBoardSize();
	/// <summary>
	/// This function prints board on console screen
	/// </summary>
	void printBoard();
private:
	int dimSize = 0; //Board's X dimension's size
	int maxStoneNum; //Board's maximum number of resolvable stone. This member is used by isFull() function.
	int currentStoneNum = 0; //Board's current number of stone. This member is used by isFull() function.
	string stringForDisplay; //String to display on screen. Initialized by displayStringMake() function in each iteration.
	vector< vector< Board::Status > > boardMatrix; //Matrix of color of stones

	void assignBoard(int x, int y);
	bool checkBoundry(Board::Coordinate inputCoordinate);
	bool checkIsStatusNone(Board::Coordinate inputCoordinate);
	void displayStringMake();
	string statusToString(Board::Coordinate boardSize, Board::Coordinate pointCoordinate, Board::Status color);
};