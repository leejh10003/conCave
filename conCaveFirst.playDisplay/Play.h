#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>
#include <regex>
#include "../conCaveFirst/board.h"
#include "../conCaveFirst.conCaveBoardRecognizer/boardRecognizer.h"
#include "Display.h"
using namespace std;
class Play {
public:
	Play();
private:
	Board::Status winCheck(Board& boardToPlay);
	Board::Status queryUserToSelectColor();
	Board::Coordinate queryCoordinateToPutStone();
	Board::Status step(Board& boardToPlay, Board::Status playerColor);
};