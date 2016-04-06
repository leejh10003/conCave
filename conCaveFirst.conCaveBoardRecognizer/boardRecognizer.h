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
	static Board::Coordinate whereToPut(vector<vector<Board::Status>>(&boardStatus), Board::Status color, Board::Coordinate size);
private:
	enum PointImportanceEnum {
		normal,
		attention,
		emergence
	};
	struct Point {
		bool isEmergence = false;
		bool isMeaningful = true;
		bool opponentCanPut = true;
		BoardRecognizer::PointImportanceEnum computerImportance;
		BoardRecognizer::PointImportanceEnum userImportance;
		int chunkCompletionSum = 0;
	};
	struct WinningSubstringResult {
		BoardRecognizer::PointImportanceEnum pointImportanceKind;
		int posInString;
	};
	enum direction
	{
		hori,
		verti,
		diag,
		antidiag
	};
	enum boundaryCheck
	{
		lower,
		higher
	};
	enum Dim
	{
		x,
		y
	};
	static void findMeaningful(vector<vector<Board::Status>>& boardStatus, vector<vector<BoardRecognizer::Point>>(&winningMap), Board::Status mySide);
	static void determineAllPointImportance(vector<vector<Board::Status>>& boardStatus, Board::Status myColor, vector<vector<BoardRecognizer::Point>>(&winningMap));
	static void getChunkCompleteSum(vector<vector<Board::Status>>& boardStatus, Board::Status myColor, vector<vector<BoardRecognizer::Point>>(&winningMap));
	static Board::Coordinate BoardRecognizer::returnWhichToChoose(vector<vector<BoardRecognizer::Point>>(&winningMap), vector<vector<Board::Status>>& boardStatus);
	static Board::Coordinate chooseBaseonPosition(list<Board::Coordinate>& input);
	static list<Board::Coordinate> returnBlankList(vector<vector<BoardRecognizer::Point>>(&winningMap));
	static bool prohibitted(vector<vector<Board::Status>>& boardStatus, int dimSize, int x, int y, Board::Status side);
	static BoardRecognizer::direction sideCollect(int i, int j);
	static bool boundaryCheck(int i, int j, Board::Coordinate positionToCalculate, int lower, int higher, int dimSize);
	static list<BoardRecognizer::WinningSubstringResult> fiveWinningpoint(string subString, int index);
	static list<BoardRecognizer::WinningSubstringResult> sixWinningpoint(string subString, int index);
	static BoardRecognizer::PointImportanceEnum BoardRecognizer::stateHandler(BoardRecognizer::PointImportanceEnum current, BoardRecognizer::PointImportanceEnum dst);
};