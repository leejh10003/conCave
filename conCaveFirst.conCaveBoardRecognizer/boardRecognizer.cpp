#include "boardRecognizer.h"
#include <string>
Board::Coordinate BoardRecognizer::whereToPut(vector<vector<Board::Status>>(&boardStatus), Board::Status color, Board::Coordinate size)
{
	vector<vector<BoardRecognizer::Point>> winningMap;
	winningMap.assign(size.x, vector<Point>(size.y));
	findMeaningful(boardStatus, winningMap, color);
	determineAllPointImportance(boardStatus, color, winningMap);
	getChunkCompleteSum(boardStatus, color, winningMap);
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
void BoardRecognizer::findMeaningful(vector<vector<Board::Status>>& boardStatus, vector<vector<BoardRecognizer::Point>>(&winningMap), Board::Status computerSide)
{
	//Iterates over every points
	for (int i = 0; i < winningMap.size(); i++)
		for (int j = 0; j < winningMap[i].size(); j++) {
			if (boardStatus[i][j] == (Board::Status)(-(int)computerSide))//find place where is blank
				winningMap[i][j].isMeaningful = false;
			if (BoardRecognizer::prohibitted(boardStatus, boardStatus.size(), i, j, (Board::Status)(-(int)computerSide)))
				winningMap[i][j].opponentCanPut = false;
			if (BoardRecognizer::prohibitted(boardStatus, winningMap.size(), i, j, computerSide)) {
				winningMap[i][j].isMeaningful = false;
			}
		}
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
void BoardRecognizer::determineAllPointImportance(vector<vector<Board::Status>>& boardStatus, Board::Status computerSide, vector<vector<BoardRecognizer::Point>>(&winningMap))
{
	string eachRow = "";
	list<BoardRecognizer::WinningSubstringResult> returned;
	const int boardSize = boardStatus.size();
	for (int i = 0; i < boardSize; i++) {
		eachRow.append("s");
		for (int j = 0; j < boardSize; j++)
			if (boardStatus[i][j] == computerSide)
				eachRow.append("s");
			else if (boardStatus[i][j] == (Board::Status)(-(int)computerSide))
				eachRow.append("o");
			else
				eachRow.append("n");
		eachRow.append("c");
		for (int j = 0; j < eachRow.length() - 5; j++) {
			returned = fiveWinningpoint(eachRow.substr(j, j+5), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[i][j + iterator->posInString - 1].computerImportance = stateHandler(winningMap[i][j + iterator->posInString - 1].computerImportance, iterator->pointImportanceKind);
			}
		}
		for (int j = 0; j < eachRow.length() - 6; j++) {
			returned = sixWinningpoint(eachRow.substr(j, j +6), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[i][j + iterator->posInString - 1].computerImportance = stateHandler(winningMap[i][j + iterator->posInString - 1].computerImportance, iterator->pointImportanceKind);
			}
		}
		eachRow.clear();
	}
	for (int i = 0; i < boardSize; i++) {
		eachRow.append("s");
		for (int j = 0; j < boardSize; j++)
			if (boardStatus[j][i] == computerSide)
				eachRow.append("s");
			else if (boardStatus[j][i] == (Board::Status)(-(int)computerSide))
				eachRow.append("o");
			else
				eachRow.append("n");
		eachRow.append("s");
		for (int j = 0; j < eachRow.length() - 5; j++) {
			returned = fiveWinningpoint(eachRow.substr(j, j + 5), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[j + iterator->posInString - 1][i].computerImportance = stateHandler(winningMap[j + iterator->posInString - 1][i].computerImportance, iterator->pointImportanceKind);
			}
		}
		for (int j = 0; j < eachRow.length() - 6; j++) {
			returned = sixWinningpoint(eachRow.substr(j, j + 6), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[j + iterator->posInString - 1][i].computerImportance = stateHandler(winningMap[j + iterator->posInString - 1][i].computerImportance, iterator->pointImportanceKind);
			}
		}
		eachRow.clear();
	}
	for (int i = 0; i < boardSize - 2; i++) {
		eachRow.append("s");
		for (int j = 0; j < boardSize - i; j++)
			if (boardStatus[j][j + i] == computerSide)
				eachRow.append("s");
			else if (boardStatus[j][j + i] == (Board::Status)(-(int)computerSide))
				eachRow.append("o");
			else
				eachRow.append("n");
		eachRow.append("s");
		for (int j = 0; j < eachRow.length() - 5; j++) {
			returned = fiveWinningpoint(eachRow.substr(j, j + 5), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[j + iterator->posInString - 1][j + i + iterator->posInString - 1].computerImportance = stateHandler(winningMap[j + iterator->posInString - 1][j + i + iterator->posInString - 1].computerImportance, iterator->pointImportanceKind);
			}
		}
		eachRow.clear();
	}
	for (int i = 1; i < boardSize - 2; i++) {
		eachRow.append("s");
		for (int j = 0; j < boardSize - i; j++)
			if (boardStatus[j + i][j] == computerSide)
				eachRow.append("s");
			else if (boardStatus[j + i][j] == (Board::Status)(-(int)computerSide))
				eachRow.append("o");
			else
				eachRow.append("n");
		eachRow.append("s");
		for (int j = 0; j < eachRow.length() - 5; j++) {
			returned = fiveWinningpoint(eachRow.substr(j, j + 5), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[j + i + iterator->posInString - 1][j + iterator->posInString - 1].computerImportance = stateHandler(winningMap[j + i + iterator->posInString - 1][j + iterator->posInString - 1].computerImportance, iterator->pointImportanceKind);
			}
		}
		eachRow.clear();
	}
	for (int i = 0; i < boardSize - 3; i++) {
		eachRow.append("s");
		for (int j = 0; j < boardSize - i; j++)
			if (boardStatus[j][j + i] == computerSide)
				eachRow.append("s");
			else if (boardStatus[j][j + i] == (Board::Status)(-(int)computerSide))
				eachRow.append("o");
			else
				eachRow.append("n");
		eachRow.append("s");
		for (int j = 0; j < eachRow.length() - 6; j++) {
			returned = sixWinningpoint(eachRow.substr(j, j + 6), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[j + iterator->posInString - 1][j + i + iterator->posInString - 1].computerImportance = stateHandler(winningMap[j + iterator->posInString - 1][j + i + iterator->posInString - 1].computerImportance, iterator->pointImportanceKind);
			}
		}
		eachRow.clear();
	}
	for (int i = 1; i < boardSize - 3; i++) {
		eachRow.append("s");
		for (int j = 0; j < boardSize - i; j++)
			if (boardStatus[j + i][j] == computerSide)
				eachRow.append("s");
			else if (boardStatus[j + i][j] == (Board::Status)(-(int)computerSide))
				eachRow.append("o");
			else
				eachRow.append("n");
		eachRow.append("s");
		for (int j = 0; j < eachRow.length() - 6; j++) {
			returned = sixWinningpoint(eachRow.substr(j, j + 6), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[j + i + iterator->posInString - 1][j + iterator->posInString - 1].computerImportance = stateHandler(winningMap[j + i + iterator->posInString - 1][j + iterator->posInString - 1].computerImportance, iterator->pointImportanceKind);
			}
		}
		eachRow.clear();
	}

	for (int i = 0; i < boardSize - 2; i++) {
		eachRow.append("s");
		for (int j = 0; j < boardSize - i; j++)
			if (boardStatus[j][boardSize - 1 - j - i] == computerSide)
				eachRow.append("s");
			else if (boardStatus[j][boardSize - 1 - j - i] == (Board::Status)(-(int)computerSide))
				eachRow.append("o");
			else
				eachRow.append("n");
		eachRow.append("s");
		for (int j = 0; j < eachRow.length() - 5; j++) {
			returned = fiveWinningpoint(eachRow.substr(j, j + 5), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[j + iterator->posInString - 1][boardSize - j - i - iterator->posInString].computerImportance = stateHandler(winningMap[j + iterator->posInString - 1][boardSize - j - i - iterator->posInString].computerImportance, iterator->pointImportanceKind);
			}
		}
		eachRow.clear();
	}
	for (int i = 1; i < boardSize - 2; i++) {
		eachRow.append("s");
		for (int j = 0; j < boardSize - i; j++)
			if (boardStatus[i + j][boardSize + i - j] == computerSide)
				eachRow.append("s");
			else if (boardStatus[i + j][boardSize + i - j] == (Board::Status)(-(int)computerSide))
				eachRow.append("o");
			else
				eachRow.append("n");
		eachRow.append("s");
		for (int j = 0; j < eachRow.length() - 5; j++) {
			returned = fiveWinningpoint(eachRow.substr(j, j + 5), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[j + i + iterator->posInString - 1][boardSize - j - iterator->posInString].computerImportance = stateHandler(winningMap[j + i + iterator->posInString - 1][boardSize - j - iterator->posInString].computerImportance, iterator->pointImportanceKind);
			}
		}
		eachRow.clear();
	}
	for (int i = 0; i < boardSize - 3; i++) {
		eachRow.append("s");
		for (int j = 0; j < boardSize - i; j++)
			if (boardStatus[j][boardSize - 1 - j - i] == computerSide)
				eachRow.append("s");
			else if (boardStatus[j][boardSize - 1 - j - i] == (Board::Status)(-(int)computerSide))
				eachRow.append("o");
			else
				eachRow.append("n");
		eachRow.append("s");
		for (int j = 0; j < eachRow.length() - 6; j++) {
			returned = sixWinningpoint(eachRow.substr(j, j + 6), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[j + iterator->posInString - 1][boardSize - j - i - iterator->posInString].computerImportance = stateHandler(winningMap[j + iterator->posInString - 1][boardSize - j - i - iterator->posInString].computerImportance, iterator->pointImportanceKind);
			}
		}
		eachRow.clear();
	}
	for (int i = 1; i < boardSize - 3; i++) {
		eachRow.append("s");
		for (int j = 0; j < boardSize - i; j++)
			if (boardStatus[i + j][boardSize + i - j] == computerSide)
				eachRow.append("s");
			else if (boardStatus[i + j][boardSize + i - j] == (Board::Status)(-(int)computerSide))
				eachRow.append("o");
			else
				eachRow.append("n");
		eachRow.append("s");
		for (int j = 0; j < eachRow.length() - 6; j++) {
			returned = sixWinningpoint(eachRow.substr(j, j + 6), j);
			for (list<BoardRecognizer::WinningSubstringResult>::iterator iterator = returned.begin(); iterator != returned.end(); iterator++) {
				winningMap[j + i + iterator->posInString - 1][boardSize - j - iterator->posInString].computerImportance = stateHandler(winningMap[j + i + iterator->posInString - 1][boardSize - j - iterator->posInString].computerImportance, iterator->pointImportanceKind);
			}
		}
		eachRow.clear();
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
void BoardRecognizer::getChunkCompleteSum(vector<vector<Board::Status>>& boardStatus, Board::Status myColor, vector<vector<BoardRecognizer::Point>>(&winningMap))
{
	int boardSize = boardStatus.size();
	string str;
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			if (winningMap[i][j].isMeaningful == true) {
				for (int k = i - 5; k < i + 6; k++)
					if (k < 0 || k >= boardSize || boardStatus[k][j] == (Board::Status)(-(int)myColor))
						str.append("o");
					else if (boardStatus[k][j] == myColor)
						str.append("s");
					else
						str.append("n");
				for (int k = 0; k < 5; k++) {
					string temp = str.substr(k, k + 7);
					if (temp[0] == myColor || temp[6] == myColor)
						continue;
					if (temp.substr(1, 6).find("o") > 0)
						continue;
					else
						winningMap[i][j].chunkCompletionSum += temp.substr(1, 6).find("s");
				}
			}
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			if (winningMap[j][i].isMeaningful == true) {
				for (int k = i - 5; k < i + 6; k++)
					if (k < 0 || k >= boardSize || boardStatus[j][k] == (Board::Status)(-(int)myColor))
						str.append("o");
					else if (boardStatus[j][k] == myColor)
						str.append("s");
					else
						str.append("n");
				for (int k = 0; k < 5; k++) {
					string temp = str.substr(k, k + 7);
					if (temp[0] == myColor || temp[6] == myColor)
						continue;
					if (temp.substr(1, 6).find("o") > 0)
						continue;
					else
						winningMap[j][i].chunkCompletionSum += temp.substr(1, 6).find("s");
				}
			}
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			if (winningMap[i][j].isMeaningful == true) {
				for (int k = - 5; k < 6; k++)
					if (k + i < 0 || k + i >= boardSize || k + j < 0 || k + j >= boardSize || boardStatus[i + k][j + k] == (Board::Status)(-(int)myColor))
						str.append("o");
					else if (boardStatus[i + k][j + k] == myColor)
						str.append("s");
					else
						str.append("n");
				for (int k = 0; k < 5; k++) {
					string temp = str.substr(k, k + 7);
					if (temp[0] == myColor || temp[6] == myColor)
						continue;
					if (temp.substr(1, 6).find("o") > 0)
						continue;
					else
						winningMap[j][i].chunkCompletionSum += temp.substr(1, 6).find("s");
				}
			}
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			if (winningMap[i][j].isMeaningful == true) {
				for (int k = - 5; k < 6; k++)
					if (k + i < 0 || k + i >= boardSize || j - k < 0 || j - k >= boardSize || boardStatus[i + k][j - k] == (Board::Status)(-(int)myColor))
						str.append("o");
					else if (boardStatus[i + k][j - k] == myColor)
						str.append("s");
					else
						str.append("n");
				for (int k = 0; k < 5; k++) {
					string temp = str.substr(k, k + 7);
					if (temp[0] == myColor || temp[6] == myColor)
						continue;
					if (temp.substr(1, 6).find("o") > 0)
						continue;
					else
						winningMap[j][i].chunkCompletionSum += temp.substr(1, 6).find("s");
				}
			}
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
			int thisPointLines = winningMap[i][j].chunkCompletionSum;
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

bool BoardRecognizer::prohibitted(vector<vector<Board::Status>>& boardStatus, int dimSize, int x, int y, Board::Status side)
{
	int* lineNumMap;
	int i, j;
	int sum[4] = { 0, };
	int tes = 0;
	int toWhere;
	for (i = -1; i < 2; i++)
		for (j = -1; j < 2; j++)
			if (i != 0 || j != 0) {
				toWhere = (int)BoardRecognizer::sideCollect(i, j);
				if (boundaryCheck(i, j, {x, y}, -2, 3, dimSize) &&
					boardStatus[x - 2 * i][y - 2 * j] == Board::Status::none &&
					boardStatus[x - 1 * i][y - 1 * j] == Board::Status::none &&
					boardStatus[x + 1 * i][y + 1 * j] == side &&
					boardStatus[x + 2 * i][y + 2 * j] == side &&
					boardStatus[x + 3 * i][y + 3 * j] == Board::Status::none)
					sum[toWhere] = 1;
				if (boundaryCheck(i, j, {x, y}, -1, 4, dimSize) &&
					boardStatus[x - 1 * i][y - 1 * j] == Board::Status::none &&
					boardStatus[x + 1 * i][y + 1 * j] == Board::Status::none &&
					boardStatus[x + 2 * i][y + 2 * j] == side &&
					boardStatus[x + 3 * i][y + 3 * j] == side &&
					boardStatus[x + 4 * i][y + 4 * j] == Board::Status::none)
					sum[toWhere] = 1;
				if (boundaryCheck(i, j, {x, y}, -1, 4, dimSize) &&
					boardStatus[x - 1 * i][y - 1 * j] == Board::Status::none &&
					boardStatus[x + 1 * i][y + 1 * j] == side &&
					boardStatus[x + 2 * i][y + 2 * j] == Board::Status::none &&
					boardStatus[x + 3 * i][y + 3 * j] == side &&
					boardStatus[x + 4 * i][y + 4 * j] == Board::Status::none)
					sum[toWhere] = 1;
				if (boundaryCheck(i, j, {x, y}, -2, 3, dimSize) &&
					boardStatus[x - 2 * i][y - 2 * j] == Board::Status::none &&
					boardStatus[x - 1 * i][y - 1 * j] == side &&
					boardStatus[x + 1 * i][y + 1 * j] == Board::Status::none &&
					boardStatus[x + 2 * i][y + 2 * j] == side &&
					boardStatus[x + 3 * i][y + 3 * j] == Board::Status::none)
					sum[toWhere] = 1;
				if (boundaryCheck(i, j, {x, y}, -2, 2, dimSize) &&
					boardStatus[x - 2 * i][y - 2 * j] == Board::Status::none &&
					boardStatus[x - 1 * i][y - 1 * j] == side &&
					boardStatus[x + 1 * i][y + 1 * j] == side &&
					boardStatus[x + 2 * i][y + 2 * j] == Board::Status::none)
					sum[toWhere] = 1;
			}
	for (i = 0; i < 4; ++i)
		tes += sum[i];
	if (tes > 1)
		return true;
	else
		return false;
}
BoardRecognizer::direction BoardRecognizer::sideCollect(int i, int j)
{
	if (i * j == 1)
		return diag;
	else if (i * j == -1)
		return antidiag;
	else
		if (i != 0)
			return hori;
		else
			return verti;
}
bool BoardRecognizer::boundaryCheck(int i, int j, Board::Coordinate positionToCalculate, int lower, int higher, int dimSize)
{
	int boundary[2][2] = { 0, };
	switch (i)
	{
	case 0:
		boundary[(int)BoardRecognizer::Dim::x][(int)BoardRecognizer::boundaryCheck::lower] = 0;
		boundary[(int)BoardRecognizer::Dim::x][(int)BoardRecognizer::boundaryCheck::higher] = 0;
		switch (j)
		{
		case 0:
			return false;
		case -1:
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::lower] = -higher;
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::higher] = -lower;
			break;
		case 1:
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::lower] = lower;
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::higher] = higher;
			break;
		}
		break;
	case -1:
		boundary[(int)BoardRecognizer::Dim::x][(int)BoardRecognizer::boundaryCheck::lower] = -higher;
		boundary[(int)BoardRecognizer::Dim::x][(int)BoardRecognizer::boundaryCheck::higher] = -lower;
		switch (j)
		{
		case 0:
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::lower] = 0;
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::higher] = 0;
			break;
		case -1:
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::lower] = -higher;
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::higher] = -lower;
			break;
		case 1:
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::lower] = lower;
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::higher] = higher;
			break;
		}
		break;
	case 1:
		boundary[(int)BoardRecognizer::Dim::x][(int)BoardRecognizer::boundaryCheck::lower] = lower;
		boundary[(int)BoardRecognizer::Dim::x][(int)BoardRecognizer::boundaryCheck::higher] = higher;
		switch (j)
		{
		case 0:
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::lower] = 0;
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::higher] = 0;
			break;
		case -1:
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::lower] = -higher;
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::higher] = -lower;
			break;
		case 1:
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::lower] = lower;
			boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::higher] = higher;
			break;
		}
		break;
	}
	if (x + boundary[(int)BoardRecognizer::Dim::x][(int)BoardRecognizer::boundaryCheck::lower] >= 0 &&
		x + boundary[(int)BoardRecognizer::Dim::x][(int)BoardRecognizer::boundaryCheck::higher] < dimSize &&
		y + boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::lower] >= 0 &&
		y + boundary[(int)BoardRecognizer::Dim::y][(int)BoardRecognizer::boundaryCheck::higher] < dimSize)
		return true;
	else
		return false;
}
list<BoardRecognizer::WinningSubstringResult> BoardRecognizer::fiveWinningpoint(string subString, int index)
{
	list<BoardRecognizer::WinningSubstringResult> returnList;
	returnList.clear();
	if (subString == "nooon") {
		returnList.push_back({ BoardRecognizer::PointImportanceEnum::emergence, 0 + index});
		returnList.push_back({ BoardRecognizer::PointImportanceEnum::emergence, 4 + index});
	}
	else if (subString == "oonoo") {
		returnList.push_back({ BoardRecognizer::PointImportanceEnum::emergence, 2 + index});
	}
	return returnList;
}
list<BoardRecognizer::WinningSubstringResult> BoardRecognizer::sixWinningpoint(string subString, int index)
{
	list<BoardRecognizer::WinningSubstringResult> returnList;
	returnList.clear();
	if (subString == "nonoon") {
		returnList.push_back({ BoardRecognizer::PointImportanceEnum::attention, 0 + index });
		returnList.push_back({ BoardRecognizer::PointImportanceEnum::emergence, 2 + index });
		returnList.push_back({ BoardRecognizer::PointImportanceEnum::emergence, 5 + index });
	}
	else if (subString == "noonon") {
		returnList.push_back({ BoardRecognizer::PointImportanceEnum::attention, 0 + index });
		returnList.push_back({ BoardRecognizer::PointImportanceEnum::emergence, 3 + index });
		returnList.push_back({ BoardRecognizer::PointImportanceEnum::emergence, 5 + index });
	}
	else if (subString == "soooon") {
		returnList.push_back({ BoardRecognizer::PointImportanceEnum::emergence, 5 + index });
	}
	else if (subString == "noooos") {
		returnList.push_back({ BoardRecognizer::PointImportanceEnum::attention, 0 + index });
	}
	return returnList;
}
BoardRecognizer::PointImportanceEnum BoardRecognizer::stateHandler(BoardRecognizer::PointImportanceEnum current, BoardRecognizer::PointImportanceEnum dst)
{
	if ((int)current < (int)dst)
		return dst;
	else
		return current;
}