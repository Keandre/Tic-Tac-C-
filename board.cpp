#include "board.hpp"
#define RET_IF_KNOWN(f) { \
Win t=f(); \
if(t!=Win::Ongoing) return t; \
}

unsigned int board::coords(const unsigned int x, const unsigned int y) const{
	return y+x*3;
}

Win board::checkSideWays() const{
	for(unsigned int x = 0; x < 3; x++){
		if(board.at(coords(0,x)) == board.at(coords(1,x)) && board.at(coords(0,x)) == board.at(coords(2,x)) && board.at(coords(0,x)) != ' '){
			return board.at(coords(0,x)) == 'X'? Win::PlayerOne:Win::PlayerTwo;
		}
	}
	return Win::Ongoing;
}
Win board::checkDownwards() const{
	for(unsigned int x = 0; x < 3; x++){
		if(board.at(coords(x,0)) == board.at(coords(x,1)) && board.at(coords(x,0)) == board.at(coords(x,2)) && board.at(coords(x,0)) != ' '){
			return board.at(coords(x,0)) == 'X'? Win::PlayerOne : Win::PlayerTwo;
		}
	}
	return Win::Ongoing;
}

Win board::checkDiagonals() const{
	//diagonal (top left to bottom right)
	if(board.at(coords(0,0)) == board.at(coords(1,1)) && board.at(coords(0,0)) == board.at(coords(2,2)) && board.at(coords(0,0)) != ' '){
		return board.at(coords(0,0)) == 'X'? Win::PlayerOne : Win::PlayerTwo;
	}
	
	//diagonal (top right to bottom left)
	if(board.at(coords(0,2)) == board.at(coords(1,1)) && board.at(coords(0,2)) == board.at(coords(2,0)) && board.at(coords(0,2)) != ' '){
		return board.at(coords(0,2)) == 'X'? Win::PlayerOne : Win::PlayerTwo;	
	}
	return Win::Ongoing;
}

Win board::checkFull() const{
	for(unsigned int x = 0; x < 9; x++){
		if(board.at(x) == ' ') return Win::Ongoing;
	}
	return Win::Tie;
}

Win board::checkWin() const {
	RET_IF_KNOWN(checkSideWays());
	RET_IF_KNOWN(checkDownwards());
	RET_IF_KNOWN(checkDiagonals());
	RET_IF_KNOWN(checkFull());
	return Win::Ongoing;
}

void board::changeBoard(unsigned int pos, char symbol){
	board[pos] = symbol;
}