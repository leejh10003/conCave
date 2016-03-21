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
	Board::Coordinate findOptimisticPostion(Board& inputBoard)
	{
		Board::Coordinate boardSize = inputBoard.getBoardSize();
		vector<vector<Point>> boardWinningMap(boardSize.x, vector<Point>(boardSize.y));
		vector<vector<Board::Status>> boardMatrix = inputBoard.getBoard();
	}
private:
	struct Point {
		bool isMeaningless = false;
		int linesCanSupport;
		int linesCanHinder;
	};
	enum meaninglessFindingState {
		normal,
		alert
	};
	void findDownsideMeaninglessPlace(Board::Coordinate boardSize, Board::Status opponentColor, vector<vector<Point>>& boardWinningMap, vector<vector<Board::Status>> boardMatrix, const int objectLineLength)
	{
		int yCoordinateStack = 0;
		BoardRecognizer::meaninglessFindingState stateMachine = BoardRecognizer::meaninglessFindingState::normal;
		for (int i = 0; i < boardSize.x; i++)
		{
			for (int j = 0; j < boardSize.y; j++)
			{
				switch (stateMachine)
				{
				case BoardRecognizer::meaninglessFindingState::normal:
					if (boardMatrix[i][j] == opponentColor)
					{
						if (j - yCoordinateStack < objectLineLength)
						{
							for (int k = yCoordinateStack; k < j; k++)
							{
								boardWinningMap[i][k].isMeaningless = true;
							}
						}
						stateMachine = BoardRecognizer::meaninglessFindingState::alert;
						yCoordinateStack = j;
					}
				case BoardRecognizer::meaninglessFindingState::alert:
					if (boardMatrix[i][j] != opponentColor)
					{
						stateMachine = BoardRecognizer::meaninglessFindingState::normal;
						yCoordinateStack = j;
					}
				}
			}
		}
	}
};