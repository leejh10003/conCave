#include "board.h"





board::board(unsigned int size) : xDimSize(size), yDimSize(size)
{
	assignBoard(size, size);
};


board::board(unsigned int xDimInput, unsigned int yDimInput) : xDimSize(xDimInput), yDimSize(yDimInput)
{
	assignBoard(xDimInput, yDimInput);
}


bool board::putConcaveStone(int xCoordinate, int yCoordinate, board::status statusValue)
{
	if (checkBoundry(xCoordinate, yCoordinate) == true &&
		checkIsStatusNone(xCoordinate, yCoordinate) == true)
	{
		this->instanceBoard[xCoordinate][yCoordinate] = statusValue;
		return true;
	}
	else
	{
		return false;
	}
}


vector< vector< board::status > > board::getBoard()
{
	return this->instanceBoard;
}


int board::getXdimSize()
{
	return xDimSize;
}


int board::getYdimSize()
{
	return yDimSize;
}





void board::assignBoard(int x, int y)
{
	vector< board::status > temp;
	temp.assign(yDimSize, none);
	this->instanceBoard.assign(xDimSize, temp);
}


bool board::checkBoundry(int xCoordinate, int yCoordinate)
{
	if (xCoordinate >= this->xDimSize || yCoordinate >= this->yDimSize ||
		xCoordinate < 0 || yCoordinate < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool board::checkIsStatusNone(int xCoordinate, int yCoordinate)
{
	if (this->instanceBoard[xCoordinate][yCoordinate] != status::none)
	{
		return false;
	}
	else
	{
		return true;
	}
}

