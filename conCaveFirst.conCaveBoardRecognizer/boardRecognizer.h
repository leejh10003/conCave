#pragma once
#include <list>
#include "..\conCaveFirst\board.h"

using namespace std;
class BoardRecognizer
{
public:
	struct Line {
		Board::Coordinate start;
		Board::Coordinate end;
	};
	void addLines(Board inputBoard, Board::Coordinate inputStoneCoordinate)
	{
		
	}
private:
	list<BoardRecognizer::Line> lines;
	class checkSideExist {
		bool up(Board inputBoard, Board::Coordinate inputStoneCoordinate)
		{
			if (inputStoneCoordinate.y > 0)
				return true;
			else
				return false;
		}
		bool down(Board inputBoard, Board::Coordinate inputStoneCoordinate)
		{
			if (inputStoneCoordinate.y < inputBoard.getBoardSize().y)
				return true;
			else
				return false;
		}
		bool left(Board inputBoard, Board::Coordinate inputStoneCoordinate)
		{
			if (inputStoneCoordinate.x > 0)
				return true;
			else
				return false;
		}
		bool right(Board inputBoard, Board::Coordinate inputStoneCoordinate)
		{
			if (inputStoneCoordinate.x < inputBoard.getBoardSize().x)
				return true;
			else
				return false;
		}
	};
};