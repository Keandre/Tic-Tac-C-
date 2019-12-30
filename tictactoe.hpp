#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP
#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <chrono>
#include <algorithm>
extern "C"{
	#include <windows.h>
}

class tictactoe{
	private:
	std::array<char,9> board={'1','2','3','4','5','6','7','8','9'};
	std::vector<char> playSymbols={'X','O','@','$','%','&'}; //@, $, % and &			
	char playerOne;
	char playerTwo;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> m_x,m_y;


	void changeBoard(const char symbol);
	bool containsSymbol(const char str);
	void chooseSymbol();
	void chooseSymbolOnePlayer();
	unsigned int coords(const unsigned int x, const unsigned int y);
	bool checkFull();
	unsigned int checkWin();
	unsigned int checkSideWays();
	unsigned int checkDownwards();
	unsigned int checkDiagonals();
	void AI();
	void colorPrint(const char chr);
	void displayBoard();

	public:
	tictactoe();	
	void twoPlayerMode();
	void onePlayerMode();
	void run();
	
};
#endif
