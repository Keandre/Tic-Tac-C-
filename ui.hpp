#ifndef UI_HPP
#define UI_HPP
#include <windows.h>

class ui{
	private:
	std::vector<char> playSymbols={'X','O','@','$','%','&'};
	bool containsSymbol(const char str); //if board contains any of the play symbols
	void colorPrint();
	
	public:
	void displayBoard();
	
};

#endif