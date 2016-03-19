#include "board.h"





Board::Board(unsigned int size) : xDimSize(size), yDimSize(size)
{
	assignBoard(size, size);
};

Board::Board(Board::Coordinate inputCoordinate)
{
	assignBoard(inputCoordinate.x, inputCoordinate.y);
}

Board::Board(unsigned int xDimInput, unsigned int yDimInput) : xDimSize(xDimInput), yDimSize(yDimInput)
{
	assignBoard(xDimInput, yDimInput);
}


bool Board::putConcaveStone(Board::Coordinate inputCoordinate, Board::Status statusValue)
{
	if (checkBoundry(inputCoordinate) == true &&
		checkIsStatusNone(inputCoordinate) == true)
	{
		this->instanceBoard[inputCoordinate.x][inputCoordinate.y] = statusValue;
		return true;
	}
	else
	{
		return false;
	}
}


vector< vector< Board::Status > > Board::getBoard()
{
	return this->instanceBoard;
}


Board::Coordinate Board::getBoardSize()
{
	return Board::Coordinate{ xDimSize, yDimSize };
}

void Board::printBoard()
{

}




void Board::assignBoard(int x, int y)
{
	vector< Board::Status > temp;
	temp.assign(yDimSize, none);
	this->instanceBoard.assign(xDimSize, temp);
}


bool Board::checkBoundry(Board::Coordinate inputCoordinate)
{
	if (inputCoordinate.x >= this->xDimSize || inputCoordinate.y >= this->yDimSize ||
		inputCoordinate.x  < 0 || inputCoordinate.y < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool Board::checkIsStatusNone(Board::Coordinate inputCoordinate)
{
	if (this->instanceBoard[inputCoordinate.x][inputCoordinate.y] != Board::Status::none)
	{
		return false;
	}
	else
	{
		return true;
	}
}

