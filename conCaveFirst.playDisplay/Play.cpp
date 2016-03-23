#include "Play.h"

Play::Play()
{
	Board boardForThisGame(3);
	Board::Status userColor = Board::Status::white;//queryUserToSelectColor();
	Board::Status computerColor = (Board::Status)(-(int)userColor);
	while (true)
	{
		if (boardForThisGame.isFull()) {
			cout << "No winner" << endl;
			break;
		}
		Board::Status result = step(boardForThisGame, userColor);
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
Board::Status Play::winCheck(Board& boardToPlay)
{
	bool whiteWin = false;
	bool blackWin = false;
	int firstCount = 0;
	int secondCount = 0;
	vector<vector<Board::Status>> checkBoard = boardToPlay.getBoard();
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
Board::Coordinate Play::queryCoordinateToPutStone()
{
	string inputFromUser;
	regex inputPattern("[\\s]*[(][\\s]*[0-9]{1,}[\\s]*[,][\\s]*[0-9]{1,}[\\s]*[)][\\s]*");
	bool isMatched = false;
	while (isMatched == false) {
		cout << "input coordinate to put stone in (x, y) form: ";
		fflush(stdout);
		fflush(stdin);
		cin >> inputFromUser;
		fflush(stdout);
		fflush(stdin);
		isMatched = regex_match(inputFromUser, inputPattern);
		switch (isMatched)
		{
		case true:
			cout << "true" << endl;
			break;
		case false:
			cout << "false" << endl;
			continue;
		default:
			break;
		}
	}
	inputFromUser = regex_replace(inputFromUser, regex("[\\s]*"), string(""));
	inputFromUser = regex_replace(inputFromUser, regex("[(]"), string(""));
	inputFromUser = regex_replace(inputFromUser, regex("[)]"), string(""));
	int x = stoi(inputFromUser);
	int y = stoi(inputFromUser.substr(inputFromUser.find(",") + 1));
	return Board::Coordinate{ x, y };
}
Board::Status Play::step(Board& boardToPlay, Board::Status playerColor)
{
	Board::Status computerColor;
	Board::Coordinate userInput;
	Board::Coordinate computerPutdown;
	switch (playerColor)
	{
	case Board::Status::black:
		boardToPlay.printBoard();
		fflush(stdin);
		userInput = this->queryCoordinateToPutStone();
		while (boardToPlay.putConcaveStone(userInput, Board::Status::black) == false) {};
		if (winCheck(boardToPlay) != Board::Status::none) return winCheck(boardToPlay);
		if (boardToPlay.isFull())
			return Board::Status::none;
		computerPutdown = BoardRecognizer::whereToPut(boardToPlay.getBoard(), Board::Status::white);
		boardToPlay.putConcaveStone(computerPutdown, Board::Status::white);
		if (winCheck(boardToPlay) != Board::Status::none) return winCheck(boardToPlay);
		if (boardToPlay.isFull())
			return Board::Status::none;
		break;
	case Board::Status::white:
		computerPutdown = BoardRecognizer::whereToPut(boardToPlay.getBoard(), Board::Status::black);
		boardToPlay.putConcaveStone(computerPutdown, Board::Status::black);
		if (winCheck(boardToPlay) != Board::Status::none) return winCheck(boardToPlay);
		if (boardToPlay.isFull())
			return Board::Status::none;
		boardToPlay.printBoard();
		fflush(stdin);
		userInput = this->queryCoordinateToPutStone();
		while (boardToPlay.putConcaveStone(userInput, Board::Status::white) == false) {};
		if (winCheck(boardToPlay) != Board::Status::none) return winCheck(boardToPlay);
		if (boardToPlay.isFull())
			return Board::Status::none;
		break;
	}
	return Board::Status::none;
}