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
private:
	list<BoardRecognizer::Line> lines;
	bool isThereUpsideLine(Board::Coordinate inputPosition)
	{
		for (list<BoardRecognizer::Line>::reverse_iterator searchIterator = this->lines.rbegin(); searchIterator != lines.rend(); searchIterator++)
		{
			if( searchIterator->end.x == inputPosition.x && searchIterator->end.y == inputPosition.y )
		}
	}
};