#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>
#include <regex>
#include "../conCaveFirst/board.h"
#include "Display.h"
using namespace std;
class Play {
public:
	Play()
	{

	}
private:
	Board boardForThisGame;
	Board::Status queryUserToSelectColor()
	{
		string inputFromUser;
		cout << "You should choose the side which you want to play. Black or White?. (input is case \"insensitive\")";
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
	Board::Coordinate queryCoordinateToPutStone()
	{
		string inputFromUser;
		regex inputPattern("[\\s]*[(][\\s]*[0-9]{1,}[\\s]*[,][\\s]*[0-9]{1,}[\\s]*[)][\\s]*");
		bool isMatched = false;
		while (isMatched) {
			cout << "input coordinate to put stone in (x, y) form: ";
			getline(cin, inputFromUser);
			isMatched = regex_match(inputFromUser, inputPattern);
			switch (isMatched == false)
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
	void step(Board& boardToPlay, Board::Status playerColor)
	{
		boardToPlay.printBoard();
		Board::Coordinate userInput = this->queryCoordinateToPutStone();
		boardToPlay.putConcaveStone(userInput, playerColor);
	}
};