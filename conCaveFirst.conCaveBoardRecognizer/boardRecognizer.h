#pragma once
#include <list>
#include "..\conCaveFirst\board.h"

using namespace std;
class BoardRecognizer
{
public:
	struct Line {
		Board::Coordinate startCoordinate;
		Board::Coordinate endCoordinate;
	};
private:
	list<BoardRecognizer::Line> whiteLines;
	list<BoardRecognizer::Line> blackLines;
};