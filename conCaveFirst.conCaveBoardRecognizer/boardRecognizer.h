#pragma once
#include <list>
#include "..\conCaveFirst\board.h"

using namespace std;
class BoardRecognizer
{
public:
	/// <summary>
	/// This function determines where to computer put concave stone.
	/// </summary>
	/// <param name="boardStatus">Act as concave board array</param>
	/// <param name="color">Act as concave board array</param>
	static Board::Coordinate whereToPut(vector<vector<Board::Status>>& boardStatus, Board::Status color);
private:
	struct Point {
		bool isEmergence = false;
		bool isMeaningful = false;
		int linesCanContribute = 0;
	};
	static void findProhibittedPlace(vector<vector<Board::Status>>& boardStatus, vector<vector<BoardRecognizer::Point>>(&winningMap));
	static void findNoneBlank(vector<vector<Board::Status>>& boardStatus, BoardRecognizer::Point(&winningMap)[3][3]);
	static void findEmergencePoint(vector<vector<Board::Status>>& boardStatus, Board::Status myColor, BoardRecognizer::Point(&winningMap)[3][3]);
	static void winnignMapComplete(vector<vector<Board::Status>>& boardStatus, Board::Status myColor, BoardRecognizer::Point(&winningMap)[3][3]);
	static Board::Coordinate returnWhichToChoose(BoardRecognizer::Point(&point)[3][3]);
	static Board::Coordinate chooseBaseonPosition(list<Board::Coordinate>& input);
	static list<Board::Coordinate> returnBlankList(BoardRecognizer::Point(&points)[3][3]);
};