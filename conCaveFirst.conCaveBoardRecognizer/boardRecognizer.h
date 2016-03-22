#pragma once
#include <list>
#include "..\conCaveFirst\board.h"

using namespace std;
class BoardRecognizer
{
public:
	struct Point {
		bool isEmergence = false;
		bool isNone = false;
		int linesCanContribute = 0;
	};
private:
	Board::Coordinate whereToPut(vector<vector<Board::Status>>& boardStatus, Board::Status color)
	{
		BoardRecognizer::Point winningMap[3][3];
		findNoneBlank(boardStatus, winningMap);
		findEmergencePoint(boardStatus, color, winningMap);
		winnignMapComplete(boardStatus, color, winningMap);

	}
	void findNoneBlank(vector<vector<Board::Status>>& boardStatus, BoardRecognizer::Point (&winningMap)[3][3])
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (boardStatus[i][j] == Board::Status::none)
					winningMap[i][j].isNone == true;
	}
	void findEmergencePoint(vector<vector<Board::Status>>& boardStatus, Board::Status myColor, BoardRecognizer::Point (&winningMap)[3][3])
	{
		int opponentCount;
		int blankCount;
		Board::Coordinate blankPoint;
		list<Board::Coordinate> listEmergenceLines;
		for (int i = 0; i < 3; i++)
		{
			opponentCount = 0;
			blankCount = 0;
			for (int j = 0; j < 3; j++)
			{
				if (boardStatus[i][j] == myColor)
				{
					continue;
				}
				else if (boardStatus[i][j] == Board::Status::none)
				{
					blankPoint.x = i;
					blankPoint.y = j;
					blankCount++;
				}
				else
				{
					opponentCount++;
				}
				if (opponentCount == 2)
				{
					listEmergenceLines.push_back(blankPoint);
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			opponentCount = 0;
			blankCount = 0;
			for (int j = 0; j < 3; j++)
			{
				if (boardStatus[j][i] == myColor)
				{
					continue;
				}
				else if (boardStatus[j][i] == Board::Status::none)
				{
					blankPoint.x = j;
					blankPoint.y = i;
					blankCount++;
				}
				else
				{
					opponentCount++;
				}
				if (opponentCount == 2)
				{
					listEmergenceLines.push_back(blankPoint);
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			opponentCount = 0;
			blankCount = 0;
			if (boardStatus[i][i] == myColor)
			{
				continue;
			}
			else if (boardStatus[i][i] == Board::Status::none)
			{
				blankPoint.x = i;
				blankPoint.y = i;
				blankCount++;
			}
			else
			{
				opponentCount++;
			}
			if (opponentCount == 2)
			{
				listEmergenceLines.push_back(blankPoint);
			}
		}
		for (int i = 0; i < 3; i++)
		{
			opponentCount = 0;
			blankCount = 0;
			if (boardStatus[i][2 - i] == myColor)
			{
				continue;
			}
			else if (boardStatus[i][2 - i] == Board::Status::none)
			{
				blankPoint.x = i;
				blankPoint.y = 2 - i;
				blankCount++;
			}
			else
			{
				opponentCount++;
			}
			if (opponentCount == 2)
			{
				listEmergenceLines.push_back(blankPoint);
			}
		}
	}
	void winnignMapComplete(vector<vector<Board::Status>>& boardStatus, Board::Status myColor, BoardRecognizer::Point (&winningMap)[3][3])
	{
		bool isThereBlack;
		bool isThereWhite;
		list<Board::Coordinate> addedCoordinate;
		for (int i = 0; i < 3; i++)
		{
			isThereBlack = false;
			isThereWhite = false;

			for (int j = 0; j < 3; j++)
			{
				switch (boardStatus[i][j])
				{
				case Board::Status::black:
					isThereBlack = true; break;
				case Board::Status::white:
					isThereWhite = true; break;
				case Board::Status::none:
					addedCoordinate.push_back(Board::Coordinate{i, j});
				default:
					continue;
				}
			}
			if (isThereBlack == false || isThereWhite == false)
			{
				for (list<Board::Coordinate>::iterator iterator = addedCoordinate.begin(); iterator != addedCoordinate.end(); iterator++)
				{
					winningMap[iterator->x][iterator->y].linesCanContribute += 1;
				}
				addedCoordinate.clear();
			}
		}
	}
	Board::Coordinate returnWhichToChoose(BoardRecognizer::Point (&point)[3][3])
	{
		int best = 0;
		list<Board::Coordinate> emergencePoint;
		list<Board::Coordinate> winningPoint;
		list<Board::Coordinate> both;
		list<Board::Coordinate> blankCandidates;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int thisPointLines = point[i][j].linesCanContribute;
				if (best < thisPointLines)
				{
					winningPoint.clear();
					winningPoint.push_back(Board::Coordinate{i, j});
				}
				else if (best == thisPointLines)
				{
					winningPoint.push_back(Board::Coordinate{i, j});
				}
				if (point[i][j].isEmergence)
				{
					emergencePoint.push_back(Board::Coordinate{ i, j });
				}
			}
		}
		for (list<Board::Coordinate>::iterator iteratorForEmergencePoint = emergencePoint.begin(); iteratorForEmergencePoint != emergencePoint.end(); iteratorForEmergencePoint++)
		{
			for (list<Board::Coordinate>::iterator iteratorForWinningPoint = winningPoint.begin(); iteratorForWinningPoint != winningPoint.end(); iteratorForWinningPoint++)
			{
				if (iteratorForEmergencePoint->x == iteratorForWinningPoint->x &&
					iteratorForEmergencePoint->y == iteratorForWinningPoint->y)
				{
					both.push_back(*iteratorForEmergencePoint);
				}
			}
		}
		switch (both.size)
		{
		case 1:
			return *both.begin();
		case 0:
			switch (emergencePoint.size)
			{
			case 1:
				return *emergencePoint.begin();
			case 0:
				switch (winningPoint.size)
				{
				case 1:
					return *winningPoint.begin();
				case 0: 
					blankCandidates = returnBlankList(point);
					return chooseBaseonPosition(blankCandidates);
				default:
					return BoardRecognizer::chooseBaseonPosition(winningPoint);
				}
			default:
				return BoardRecognizer::chooseBaseonPosition(emergencePoint);
			}
		default:
			return BoardRecognizer::chooseBaseonPosition(both);
		}
	}
	Board::Coordinate chooseBaseonPosition(list<Board::Coordinate>& input)
	{
		Board::Coordinate forReturn;
		for (list<Board::Coordinate>::iterator iterator = input.begin(); iterator != input.end(); iterator++)
		{
			int x = iterator->x;
			int y = iterator->y;
			if (x == 1 && y == 1)
			{
				return Board::Coordinate{ 1,1 };
			}
			else if (x == 1 && y == 0 ||
				x == 1 && y == 2 ||
				x == 0 && y == 1 ||
				x == 2 && y == 1)
			{
				forReturn = *iterator;
			}
			else
			{
				if (!(forReturn.x == 1 && forReturn.y == 0 ||
					forReturn.x == 1 && forReturn.y == 2 ||
					forReturn.x == 0 && forReturn.y == 1 ||
					forReturn.x == 2 && forReturn.y == 1))
				{
					forReturn = *iterator;
				}
			}
		}
		return forReturn;
	}
	list<Board::Coordinate> returnBlankList(BoardRecognizer::Point(&points)[3][3])
	{
		list<Board::Coordinate> listToReturn;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (points[i][j].isNone)
					listToReturn.push_back(Board::Coordinate{i, j});
		return listToReturn;
	}
};