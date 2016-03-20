#pragma once
#include <list>
#include "..\conCaveFirst\board.h"

using namespace std;
class BoardRecognizer
{
public:
	struct Line {
		Board::GoStone start;
		Board::GoStone end;
		Board::Status color;
	};
private:
	list<BoardRecognizer::Line> lines;
	void searchDownsideLines(Board inputBoard)
	{

	}
	void searchRighesideLines(Board inputBoard)
	{

	}
	void searchDiagonalLines(Board inputBoard)
	{

	}
	void searchAntiDiagonalLines(Board inputBoard)
	{

	}
};