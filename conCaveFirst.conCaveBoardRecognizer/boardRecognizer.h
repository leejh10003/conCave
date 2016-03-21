#pragma once
#include <list>
#include "..\conCaveFirst\board.h"

using namespace std;
class BoardRecognizer
{
public:
	struct Point {
		bool isEmergence = false;
		int linesCanContribute = 0;
	};
private:
	Board::Coordinate whereToPut(vector<vector<Board::Status>>& boardStatus, Board::Status color)
	{
		BoardRecognizer::Point winningMap[3][3];
		
		findEmergencePoint(boardStatus, color, winningMap);
		addLinesCanContribute(boardStatus, color, winningMap);
	}
	void findEmergencePoint(vector<vector<Board::Status>>& boardStatus, Board::Status myColor, BoardRecognizer::Point winningMap[3][3])
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
	void addLinesCanContribute(vector<vector<Board::Status>>& boardStatus, Board::Status myColor, BoardRecognizer::Point winningMap[3][3])
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
	
};