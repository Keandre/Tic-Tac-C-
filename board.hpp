#ifndef BOARD_HPP
#define BOARD_HPP
#include <array>

class board{
	public:
	enum Win{Ongoing=0,PlayerOne=1,PlayerTwo=2,Tie=3};
	void changeBoard(unsigned int pos, char symbol);
	Win checkWin() const;
	
	private:
	std::array<char,9> board={' ',' ',' ',' ',' ',' ',' ',' ',' '};
	
	Win checkSideWays() const;
	Win checkDownwards() const;
	Win checkDiagonals() const;
	Win checkFull() const;
	unsigned int coords(const unsigned int x, const unsigned int y) const;
	
};

#endif