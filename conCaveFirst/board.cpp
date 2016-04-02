#include "board.h"





Board::Board(unsigned int size) : dimSize(size)
{
	assignBoard(size, size);
	maxStoneNum = dimSize * dimSize;
};


bool Board::putConcaveStone(Board::Coordinate inputCoordinate, Board::Status statusValue)
{
	//Check lower and higher bound
	if (checkBoundry(inputCoordinate) == true &&
		checkIsStatusNone(inputCoordinate) == true)
	{
		this->boardMatrix[inputCoordinate.x][inputCoordinate.y] = statusValue;
		currentStoneNum += 1;
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::isFull()
{
	return currentStoneNum < maxStoneNum ? false : true;
}

vector< vector< Board::Status > > Board::getBoard()
{
	return this->boardMatrix;
}


Board::Coordinate Board::getBoardSize()
{
	return Board::Coordinate{ dimSize, dimSize };
}

void Board::printBoard()
{
	system("cls");
	displayStringMake();
	cout << stringForDisplay << endl;
	stringForDisplay.clear();
}




/// <summary>
/// This function assign board's stone matrix
/// </summary>
/// <param name="x">
/// X dimension size of board
/// </param>
/// <param name="y">
/// y dimension size of board
/// </param>
/// <remarks>
/// This function is private. Do not call it from other class or instance.
/// </remarks>
void Board::assignBoard(int x, int y)
{
	this->boardMatrix.assign(x, vector< Board::Status >(y, Board::Status::none));
}


/// <summary>
/// This function check boundry for function putConcaveStone(Board::Coordinate inputCoordinate, Board::Status statusValue).
/// <see cref="putConcaveStone"/>
/// </summary>
/// <param name="inputCoordinate">
/// Coordinate input from user.
/// </param>
/// <remarks>
/// This function is private. Do not call it from other class or instance.
bool Board::checkBoundry(Board::Coordinate inputCoordinate)
{
	if (inputCoordinate.x >= this->dimSize || inputCoordinate.y >= this->dimSize ||
		inputCoordinate.x  < 0 || inputCoordinate.y < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
/// <summary>
/// This function check one position wether it is empty or not.
/// </summary>
/// <param name="inputCoordinate">
/// Coordinate input from caller.
/// </param>
/// <remarks>
/// This function is private. Do not call it from other class or instance.
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

/// <summary>
/// This function make string which is dynamic-size and printed to console later
/// </summary>
/// <remarks>
/// This function is private. Do not call it from other class or instance.
void Board::displayStringMake()
{
	for (int i = 0; i < dimSize; i++) {
		for (int j = 0; j < dimSize; j++)
			stringForDisplay += statusToString(Board::Coordinate{dimSize, dimSize}, Board::Coordinate{ i, j }, boardMatrix[j][i]);
		if (i < dimSize -1 )
			stringForDisplay.append(1, '\n');
	}
}

/// <summary>
/// This function return character which is suit for position and color
/// </summary>
/// <remarks>
/// This function is private. Do not call it from other class or instance.
string Board::statusToString(Board::Coordinate boardSize, Board::Coordinate pointCoordinate, Board::Status color)
{
	int maxX = boardSize.x - 1;
	int maxY = boardSize.y - 1;
	int currentX = pointCoordinate.x;
	int currentY = pointCoordinate.y;
	switch (color)
	{
	case Board::black:
		return "¡Ü";
		break;
	case Board::white:
		return "¡Û";
		break;
	default:
		if (currentX == 0)
			if (currentY == 0)
				return "¦£";
			else if (currentY == maxY)
				return "¦¤";
			else
				return "¦¨";
		else if (currentX == maxX)
			if (currentY == 0)
				return "¦¦";
			else if (currentY == maxY)
				return "¦¥";
			else
				return "¦ª";
		else
			if (currentY == 0)
				return "¦§";
			else if (currentY == maxY)
				return "¦©";
			else
				return "¦«";
			break;
	}
}