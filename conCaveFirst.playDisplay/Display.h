#include <vector>
#include <string>
#include <iostream>
#include "../conCaveFirst/board.h"
using namespace std;
class Display {
public:
private: 
	static string stringForDisplay;
	static void displayString(Board& boardToDisplay)
	{
		vector<vector<Board::Status>> boardStoneColor= boardToDisplay.getBoard();
		Board::Coordinate dimSize = boardToDisplay.getBoardSize();
		for (int i = 0; i < dimSize.x; i++) {
			for (int j = 0; j < dimSize.y; j++)
				stringForDisplay.append(1, statusToChar(dimSize, Board::Coordinate{ i, j }, boardStoneColor[i][j]));
			stringForDisplay.append(1, '\n');
		}
	}
	static char statusToChar(Board::Coordinate boardSize, Board::Coordinate pointCoordinate, Board::Status color)
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
};