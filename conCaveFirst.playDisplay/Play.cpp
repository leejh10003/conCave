#include "Play.h"

Play::Play()
{
	Board boardForThisGame(3); //At now, we only implement AI for 3-concave
	Board::Status userColor = Board::Status::white;
	Board::Status computerColor = (Board::Status)(-(int)userColor);
	//Variables for user color selection. Later, color choice will be implemented
	while (true)
	{
		if (boardForThisGame.isFull()) {
			cout << "No winner" << endl;
			break;
		}
		Board::Status result = step(boardForThisGame, userColor);//If not ended, game goes on
		if (result != Board::Status::none)
			if (result == Board::Status::black) {
				cout << "winner is black" << endl;
				break;
			}
			else if (result == Board::Status::white) {
				cout << "winner is white" << endl;
				break;
			}
	}
}
/// <summary>
/// This function every lines on board and check the game is ended. This function returns side which is winner.
/// </summary>
/// <param name ="boardToPlay">
/// Board used to this round
/// </param>
/// <remarks>
/// This function is private. Do not call it from outside instance
///</remarks>
Board::Status Play::winCheck(Board& boardToPlay)
{
	bool whiteWin = false;
	bool blackWin = false;
	int firstCount = 0;
	int secondCount = 0;
	vector<vector<Board::Status>> checkBoard = boardToPlay.getBoard();
	// Linear searching for vertical and horizontal
	for (int i = 0; i < 3; i++)
	{
		firstCount = 0;
		secondCount = 0;
		for (int j = 0; j < 3; j++)
		{
			firstCount += (int)checkBoard[i][j];
			secondCount += (int)checkBoard[j][i];
		}
		switch (firstCount)
		{
		case 3:
			whiteWin = true; break;
		case -3:
			blackWin = true; break;
		default:
			break;
		}
		switch (secondCount)
		{
		case 3:
			whiteWin = true; break;
		case -3:
			blackWin = true; break;
		default:
			break;
		}
	}
	firstCount = 0;
	secondCount = 0;
	// Linear searching for diagonal and antidiagonal
	for (int i = 0; i < 3; i++)
	{
		firstCount += (int)checkBoard[i][i];
		secondCount += (int)checkBoard[i][2 - i];
	}
	switch (firstCount)
	{
	case 3:
		whiteWin = true; break;
	case -3:
		blackWin = true; break;
	default:
		break;
	}
	switch (secondCount)
	{
	case 3:
		whiteWin = true; break;
	case -3:
		blackWin = true; break;
	default:
		break;
	}
	if (!(whiteWin ^ blackWin))
	{
		return Board::Status::none;
	}
	else if (whiteWin)
	{
		return Board::Status::white;
	}
	else
	{
		return Board::Status::black;
	}
}
/// <summary>
/// This function query user's color side and returns it. Later, it will be used.
/// </summary>
/// <remarks>
/// This function is private. Do not call it from outside instance
///</remarks>
Board::Status Play::queryUserToSelectColor()
{
	string inputFromUser;
	cout << "You should choose the side which you want to play. Black or White?. (input is case \"insensitive\")" << endl;
	while (true) {
		cout << "{black, b} for black side"
			<< endl << "{white, w} for white side"
			<< endl << "Your selection: ";
		getline(cin, inputFromUser);
		transform(inputFromUser.begin(),
			inputFromUser.end(),
			inputFromUser.begin(),
			::tolower);
		if (inputFromUser == "black" || inputFromUser == "b")
			return Board::Status::black;
		else if (inputFromUser == "white" || inputFromUser == "w")
			return Board::Status::white;
		else
		{
			cout << "Wrong input" << endl;
		}
	}
}
/// <summary>
/// This function query user's coordination selection and returns it.
/// </summary>
/// <remarks>
/// This function is private. Do not call it from outside instance
///</remarks>
Board::Coordinate Play::queryCoordinateToPutStone()
{
	string inputFromUser;
	regex inputPattern("[\\s]*[(][\\s]*[0-9]{1,}[\\s]*[,][\\s]*[0-9]{1,}[\\s]*[)][\\s]*");// Right form input
	bool isMatched = false;
	while (isMatched == false) {
		cout << "input coordinate to put stone in (x, y) form: ";
		cin.clear();
		getline(cin, inputFromUser);
		cin.clear();
		isMatched = regex_match(inputFromUser, inputPattern);
		if (isMatched == false)
			cout << "Wrong form. ";
	}
	inputFromUser = regex_replace(inputFromUser, regex("[\\s]*"), string(""));
	inputFromUser = regex_replace(inputFromUser, regex("[(]"), string(""));
	inputFromUser = regex_replace(inputFromUser, regex("[)]"), string(""));// input normalization
	int x = stoi(inputFromUser);
	int y = stoi(inputFromUser.substr(inputFromUser.find(",") + 1));
	return Board::Coordinate{ x, y };
}
/// <summary>
/// This function continue game on each step. It gets users input and gets AI's decision.
/// </summary>
/// <param name ="boardToPlay">
/// Board used to this round
/// </param>
/// <param name = "playerColor">
/// Playerside color
/// </param>
/// <remarks>
/// This function is private. Do not call it from outside instance
///</remarks>
Board::Status Play::step(Board& boardToPlay, Board::Status playerColor)
{
	Board::Status computerColor;
	Board::Coordinate userInput;
	Board::Coordinate computerPutdown;
	switch (playerColor)// Each step of calling is different because of playerside's color
	{
	case Board::Status::black:
		userInput = this->queryCoordinateToPutStone();
		while (boardToPlay.putConcaveStone(userInput, Board::Status::black) == false) {};
		boardToPlay.printBoard();
		if (winCheck(boardToPlay) != Board::Status::none) return winCheck(boardToPlay);
		if (boardToPlay.isFull())
			return Board::Status::none;
		computerPutdown = BoardRecognizer::whereToPut(boardToPlay.getBoard(), Board::Status::white);
		boardToPlay.putConcaveStone(computerPutdown, Board::Status::white);
		boardToPlay.printBoard();
		if (winCheck(boardToPlay) != Board::Status::none) return winCheck(boardToPlay);
		if (boardToPlay.isFull())
			return Board::Status::none;
		break;
	case Board::Status::white:
		computerPutdown = BoardRecognizer::whereToPut(boardToPlay.getBoard(), Board::Status::black);
		boardToPlay.putConcaveStone(computerPutdown, Board::Status::black);
		boardToPlay.printBoard();
		if (winCheck(boardToPlay) != Board::Status::none) return winCheck(boardToPlay);
		if (boardToPlay.isFull())
			return Board::Status::none;
		do {
			userInput = this->queryCoordinateToPutStone();
		} while (boardToPlay.putConcaveStone(userInput, Board::Status::white) == false);
		if (winCheck(boardToPlay) != Board::Status::none) return winCheck(boardToPlay);
		if (boardToPlay.isFull())
			return Board::Status::none;
		break;
	}
	return Board::Status::none;
}