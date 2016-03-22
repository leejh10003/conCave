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
		this->boardMatrix[inputCoordinate.x][inputCoordinate.y] = statusValue;
		return true;
	}
	else
	{
		return false;
	}
}


vector< vector< Board::Status > > Board::getBoard()
{
	return this->boardMatrix;
}


Board::Coordinate Board::getBoardSize()
{
	return Board::Coordinate{ xDimSize, yDimSize };
}

void Board::printBoard()
{
	displayStringMake();
	cout << stringForDisplay << endl;
	stringForDisplay.clear();
}




void Board::assignBoard(int x, int y)
{
	this->boardMatrix.assign(x, vector< Board::Status >(y, Board::Status::none));
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
	if (this->boardMatrix[inputCoordinate.x][inputCoordinate.y] != Board::Status::none)
	{
		return false;
	}
	else
	{
		return true;
	}
}


void Board::displayStringMake()
{
	for (int i = 0; i < xDimSize; i++) {
		for (int j = 0; j < xDimSize; j++)
			stringForDisplay += statusToChar(Board::Coordinate{xDimSize, yDimSize}, Board::Coordinate{ i, j }, boardMatrix[i][j]);
		stringForDisplay.append(1, '\n');
	}
}
char Board::statusToChar(Board::Coordinate boardSize, Board::Coordinate pointCoordinate, Board::Status color)
{
	int maxX = boardSize.x - 1;
	int maxY = boardSize.y - 1;
	int currentX = pointCoordinate.x;
	int currentY = pointCoordinate.y;
	switch (color)
	{
	case Board::black:
		return '¡Ü';
		break;
	case Board::white:
		return '¡Û';
		break;
	default:
		if (currentX == 0)
			if (currentY == 0)
				return '¦¦';
			else if (currentY == maxY)
				return '¦£';
			else
				return '¦§';
		else if (currentX == maxX)
			if (currentY == 0)
				return '¦¥';
			else if (currentY == maxY)
				return '¦¤';
			else
				return '¦©';
		else
			if (currentY == 0)
				return '¦ª';
			else if (currentY == maxY)
				return '¦¨';
			else
				return '¦«';
			break;
	}
}