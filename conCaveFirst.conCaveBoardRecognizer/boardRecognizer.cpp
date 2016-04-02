#include "boardRecognizer.h"
Board::Coordinate BoardRecognizer::whereToPut(vector<vector<Board::Status>>(&boardStatus), Board::Status color, Board::Coordinate size)
{
	vector<vector<BoardRecognizer::Point>> winningMap;
	winningMap.assign(size.x, vector<Point>(size.y));
	findMeaningful(boardStatus, winningMap);
	findEmergencePoint(boardStatus, color, winningMap);
	winnignMapComplete(boardStatus, color, winningMap);
	return returnWhichToChoose(winningMap, boardStatus);
}
/// <summary>
/// This function find the place in concaveBoard where is not blank and modify winningMap
/// </summary>
/// <param name="boardStatus">Act as concave board array</param>
/// <param name="winningMap">This array includes points'information about possibility to win</param>
/// <remarks>
/// This function is private. Do not try to call this function.
/// </remarks>
void BoardRecognizer::findMeaningful(vector<vector<Board::Status>>& boardStatus, vector<vector<BoardRecognizer::Point>>(&winningMap))
{
	//Iterates over every points
	for (int i = 0; i < winningMap.size(); i++)
		for (int j = 0; j < winningMap[i].size(); j++)
			if (boardStatus[i][j] == Board::Status::none)//find place where is blank
				winningMap[i][j].isMeaningful = true;
}
/// <summary>
/// This function find the place in concaveBoard where is important because if not put here, the opponent will win
/// </summary>
/// <param name="boardStatus">Act as concave board array</param>
/// <param name="myColor">This paramater determine my color</param>
/// <param name="winningMap">This array includes points'information about possibility to win</param>
/// <remarks>
/// This function is private. Do not try to call this function.
/// </remarks>
void BoardRecognizer::findEmergencePoint(vector<vector<Board::Status>>& boardStatus, Board::Status myColor, vector<vector<BoardRecognizer::Point>>(&winningMap))

{
	int opponentCount;
	int blankCount;
	Board::Coordinate blankPoint;
	list<Board::Coordinate> listEmergenceLines;
	// Vertical searching
	for (int i = 0; i < 3; i++)
	{
		opponentCount = 0;
		blankCount = 0;
		for (int j = 0; j < 3; j++)
		{
			//search point data

			//Position where i putted
			if (boardStatus[i][j] == myColor)
			{
				continue;
			}
			//Position where is blank. this is candidate emmergence point.
			else if (boardStatus[i][j] == Board::Status::none)
			{
				blankPoint.x = i;
				blankPoint.y = j;
				blankCount++;
			}
			//Position where enemy putted.
			else
			{
				opponentCount++;
			}
		}
		// If this line seem to be completed
		if (opponentCount == 2 && blankCount == 1)
		{
			// Push this line's blank place to returning list
			listEmergenceLines.push_back(blankPoint);
		}
	}
	// Horizontal searching
	for (int i = 0; i < 3; i++)
	{
		opponentCount = 0;
		blankCount = 0;
		for (int j = 0; j < 3; j++)
		{
			//search point data

			//Position where i putted
			if (boardStatus[j][i] == myColor)
			{
				continue;
			}

			//Position where is blank. this is candidate emmergence point.
			else if (boardStatus[j][i] == Board::Status::none)
			{
				blankPoint.x = j;
				blankPoint.y = i;
				blankCount++;
			}
			//Position where enemy putted.
			else
			{
				opponentCount++;
			}
		}
		// If this line seem to be completed
		if (opponentCount == 2 && blankCount == 1)
		{
			// Push this line's blank place to returning list
			listEmergenceLines.push_back(blankPoint);
		}
	}
	// Diagonal searching
	for (int i = 0; i < 3; i++)
	{
		opponentCount = 0;
		blankCount = 0;
		//Position where i putted
		if (boardStatus[i][i] == myColor)
		{
			continue;
		}
		//Position where is blank. this is candidate emmergence point.
		else if (boardStatus[i][i] == Board::Status::none)
		{
			blankPoint.x = i;
			blankPoint.y = i;
			blankCount++;
		}
		//Position where enemy putted.
		else
		{
			opponentCount++;
		}
	}
	// If this line seem to be completed
	if (opponentCount == 2 && blankCount == 1)
	{
		// Push this line's blank place to returning list
		listEmergenceLines.push_back(blankPoint);
	}
	// Antidiagonal searching
	for (int i = 0; i < 3; i++)
	{
		opponentCount = 0;
		blankCount = 0;
		//Position where i putted
		if (boardStatus[i][2 - i] == myColor)
		{
			continue;
		}
		//Position where is blank. this is candidate emmergence point.
		else if (boardStatus[i][2 - i] == Board::Status::none)
		{
			blankPoint.x = i;
			blankPoint.y = 2 - i;
			blankCount++;
		}
		//Position where enemy putted.
		else
		{
			opponentCount++;
		}
	}
	// If this line seem to be completed
	if (opponentCount == 2 && blankCount == 1)
	{
		// Push this line's blank place to returning list
		listEmergenceLines.push_back(blankPoint);
	}
	// Process every list element's emergence information to winningmap
	for (list<Board::Coordinate>::iterator iterator = listEmergenceLines.begin(); iterator != listEmergenceLines.end(); iterator++)
	{
		winningMap[iterator->x][iterator->y].isEmergence = true;
	}
}
/// <summary>
/// This Function completes winningmap based on the result contributed from functions like findNoneBlank, findEmergencePoint.
/// <see cref="findNoneBlank"/>
/// </summary>
/// <param name="boardStatus">Act as concave board array</param>
/// <param name="myColor">This paramater determine my color</param>
/// <param name="winningMap">This array includes points'information about possibility to win</param>
/// <remarks>
/// This function is private. Do not try to call this function.
/// </remarks>
void BoardRecognizer::winnignMapComplete(vector<vector<Board::Status>>& boardStatus, Board::Status myColor, vector<vector<BoardRecognizer::Point>>(&winningMap))
{
	bool isThereBlack;
	bool isThereWhite;
	list<Board::Coordinate> addedCoordinate;
	// Calculate each position's number of lines where it can contribute to.
	// Vertical
	for (int i = 0; i < 3; i++)
	{
		isThereBlack = false;
		isThereWhite = false;

		// Search lines' stones
		for (int j = 0; j < 3; j++)
		{
			switch (boardStatus[i][j])
			{
			case Board::Status::black:
				isThereBlack = true; break;
			case Board::Status::white:
				isThereWhite = true; break;
			case Board::Status::none:
				addedCoordinate.push_back(Board::Coordinate{ i, j });
			default:
				continue;
			}
		}
		
		if (isThereBlack == false || isThereWhite == false)// If line is filled with different colr, it is meaningless line
		{
			// Else, add number
			for (list<Board::Coordinate>::iterator iterator = addedCoordinate.begin(); iterator != addedCoordinate.end(); iterator++)
			{
				winningMap[iterator->x][iterator->y].linesCanContribute += 1;
			}
		}
		addedCoordinate.clear();
	}
	// Horizontal
	for (int i = 0; i < 3; i++)
	{
		isThereBlack = false;
		isThereWhite = false;

		// Search lines' stones
		for (int j = 0; j < 3; j++)
		{
			switch (boardStatus[j][i])
			{
			case Board::Status::black:
				isThereBlack = true; break;
			case Board::Status::white:
				isThereWhite = true; break;
			case Board::Status::none:
				addedCoordinate.push_back(Board::Coordinate{ j, i });
			default:
				continue;
			}
		}
		if (isThereBlack == false || isThereWhite == false)// If line is filled with different colr, it is meaningless line
		{
			// Else, add number
			for (list<Board::Coordinate>::iterator iterator = addedCoordinate.begin(); iterator != addedCoordinate.end(); iterator++)
			{
				winningMap[iterator->x][iterator->y].linesCanContribute += 1;
			}
		}
		addedCoordinate.clear();
	}
	// Diagonal
	isThereBlack = false;
	isThereWhite = false;
	// Search lines' stones
	for (int i = 0; i < 3; i++)
	{
		switch (boardStatus[i][i])
		{
		case Board::Status::black:
			isThereBlack = true; break;
		case Board::Status::white:
			isThereWhite = true; break;
		case Board::Status::none:
			addedCoordinate.push_back(Board::Coordinate{ i, i });
		default:
			continue;
		}
	}
	if (isThereBlack == false || isThereWhite == false)// If line is filled with different colr, it is meaningless line
	{
		// Else, add number
		for (list<Board::Coordinate>::iterator iterator = addedCoordinate.begin(); iterator != addedCoordinate.end(); iterator++)
		{
			winningMap[iterator->x][iterator->y].linesCanContribute += 1;
		}
	}
	addedCoordinate.clear();
	// Antidiagonal
	isThereBlack = false;
	isThereWhite = false;
	// Search lines' stones
	for (int i = 0; i < 3; i++)
	{
		switch (boardStatus[i][2-i])
		{
		case Board::Status::black:
			isThereBlack = true; break;
		case Board::Status::white:
			isThereWhite = true; break;
		case Board::Status::none:
			addedCoordinate.push_back(Board::Coordinate{ i, 2-i });
		default:
			continue;
		}
	}
	if (isThereBlack == false || isThereWhite == false)// If line is filled with different colr, it is meaningless line
	{
		// Else, add number
		for (list<Board::Coordinate>::iterator iterator = addedCoordinate.begin(); iterator != addedCoordinate.end(); iterator++)
		{
			winningMap[iterator->x][iterator->y].linesCanContribute += 1;
		}
	}
	addedCoordinate.clear();
	// Upper operations never eliminate positions which are not blank, but still can be linked. We don't need this information. So eliminate them.
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (boardStatus[i][j] != Board::Status::none)
				winningMap[i][j].linesCanContribute = 0;
}
/// <summary>
/// This Function returns which point to return as a putting location.
/// <see cref="findNoneBlank"/>
/// <see cref="findEmergencePoint"/>
/// </summary>
/// <param name="Point">Researched point' informations about winning tactic</param>
/// <remarks>
/// This function is private. Do not try to call this function.
/// </remarks>
Board::Coordinate BoardRecognizer::returnWhichToChoose(vector<vector<BoardRecognizer::Point>>(&winningMap), vector<vector<Board::Status>>& boardStatus)

{
	int best = 0;
	list<Board::Coordinate> emergencePoint;
	list<Board::Coordinate> winningPoint;
	list<Board::Coordinate> both;
	list<Board::Coordinate> blankCandidates;
	// Find the points which are most win-promising
	for (int i = 0; i < winningMap.size(); i++)
	{
		for (int j = 0; j < winningMap[i].size(); j++)
		{
			int thisPointLines = winningMap[i][j].linesCanContribute;
			if (best < thisPointLines)
			{
				winningPoint.clear();
				winningPoint.push_back(Board::Coordinate{ i, j });
				best = thisPointLines;
			}
			else if (best == thisPointLines)
			{
				winningPoint.push_back(Board::Coordinate{ i, j });
			}
			if (winningMap[i][j].isEmergence)
			{
				emergencePoint.push_back(Board::Coordinate{ i, j });
			}
		}
	}
	// Find the best place where can effectively minimize possibility to lose, and maximize possibility to win
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
	// Determine which information to base on.
	switch (both.size())
	{
	case 1:
		return *both.begin();
	case 0:
		switch (emergencePoint.size())
		{
		case 1:
			return *emergencePoint.begin();
		case 0:
			switch (winningPoint.size())
			{
			case 1:
				return *winningPoint.begin();
			case 0:
				blankCandidates = returnBlankList(winningMap);
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
/// <summary>
/// This Function returns where to put if two or more point has same number of lines can complete and both emergence.
/// </summary>
/// <param name="input">Recieve candidate coordinates</param>
/// <remarks>
/// This function is private. Do not try to call this function.
/// </remarks>
Board::Coordinate BoardRecognizer::chooseBaseonPosition(list<Board::Coordinate>& input)
{
	Board::Coordinate forReturn = {-1,-1};
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
/// <summary>
/// This Function returns blank points.
/// </summary>
/// <param name="input">Recieve winningmap</param>
/// <remarks>
/// This function is private. Do not try to call this function.
/// </remarks>
list<Board::Coordinate> BoardRecognizer::returnBlankList(vector<vector<BoardRecognizer::Point>>(&winningMap))
{
	list<Board::Coordinate> listToReturn;
	for (int i = 0; i < winningMap.size(); i++)
		for (int j = 0; j < winningMap[i].size(); j++)
			if (winningMap[i][j].isMeaningful)
				listToReturn.push_back(Board::Coordinate{ i, j });
	return listToReturn;
}