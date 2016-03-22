#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>
#include "../conCaveFirst/board.h"
using namespace std;
class Play {
public:
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
	void Step()
	{

	}
};