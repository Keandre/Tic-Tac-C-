#include "tictactoe.hpp"	
	
void tictactoe::changeBoard(const char symbol){
	unsigned int playerMove=0;
	while(true){
		std::cin>>playerMove;
		if(playerMove >= 1 || playerMove<=9){	
			if(std::isdigit(board.at(playerMove-1))){
				board[playerMove-1] = symbol;
				break;
			}
			else{
				std::cout<<"That space is not vacant. Please try again.\n";
			}
		}
		else{
			std::cout<<"That space does not exist. Please try again.\n";
		}
	}
}	
	
bool tictactoe::containsSymbol(const char str){
	return std::find(playSymbols.begin(), playSymbols.end(), str) != playSymbols.end();
}
	
void tictactoe::chooseSymbol(){	
	playSymbols = {'X','O','@','$','%','&'};				
	char choice=' ';
	std::cout<<"Player One, type in the symbol you would like out of these:\n";	
	for(char symbol : playSymbols){	
		std::cout<<symbol<<" ";
	}
	std::cout<<"\n";
	while(true){
		std::cin>>choice;
		if(!containsSymbol(choice)){
			std::cout<<"That isn't a valid choice. Please try again.\n";
		}
		else{
			playerOne = choice;
			playSymbols.erase(std::remove(playSymbols.begin(),playSymbols.end(),playerOne),playSymbols.end());
			break;
		}
	}
	std::cout<<"And you, player two? Feel free to pick from the remaining:\n";
	for(char symbol:playSymbols){
		std::cout<<symbol<<" ";
	}
	std::cout<<"\n";
	while(true){
		std::cin>>choice;
		if(!containsSymbol(choice)){
			std::cout<<"That isn't a valid choice. Please try again.\n";
		}		
		else{
			playerTwo = choice;
			playSymbols.erase(std::remove(playSymbols.begin(),playSymbols.end(),playerTwo),playSymbols.end());
			break;
		}
	}
}
	
void tictactoe::chooseSymbolOnePlayer(){		
	char choice=' ';
	std::cout<<"Player One, type in the symbol you would like out of these:\n";
	for(char symbol : playSymbols){
		std::cout<<symbol<<" ";
	}
	std::cout<<"\n";
	while(true){
		std::cin>>choice;
		if(!containsSymbol(choice)){
			std::cout<<"That isn't a valid choice. Please try again.\n";
		}
		else{
			playerOne = choice;
			playSymbols.erase(std::remove(playSymbols.begin(),playSymbols.end(),playerOne),playSymbols.end());
			std::uniform_int_distribution<int> choiceAI(0, 5);
			playerTwo = playSymbols[choiceAI(generator)]; //AI will be player 2
			playSymbols = {'X','O','@','$','%','&'};			
			break;
		}
	}
}
	
unsigned int tictactoe::coords(const unsigned int x, const unsigned int y){
	return y+x*3;
}

bool tictactoe::checkFull(){
	for(int i = 0; i < 9;i++){
		if(board[i]>=49 && board[i]<=57) return false;
	}
	return true;
}

unsigned int tictactoe::checkSideWays(){
	for(unsigned int x = 0; x < 3; x++){
		if(board.at(coords(0,x)) == board.at(coords(1,x)) && board.at(coords(0,x)) == board.at(coords(2,x)) && board.at(coords(0,x)) != ' '){
			return board.at(coords(0,x)) == playerOne? 1:2;
		}
	}
	return 0;
}
unsigned int tictactoe::checkDownwards(){
	for(unsigned int x = 0; x < 3; x++){
		if(board.at(coords(x,0)) == board.at(coords(x,1)) && board.at(coords(x,0)) == board.at(coords(x,2)) && board.at(coords(x,0)) != ' '){
			return board.at(coords(x,0)) == playerOne? 1:2;
		}
	}
	return 0;
}


unsigned int tictactoe::checkDiagonals(){
	//diagonal (top left to bottom right)
	if(board.at(coords(0,0)) == board.at(coords(1,1)) && board.at(coords(0,0)) == board.at(coords(2,2)) && board.at(coords(0,0)) != ' '){
		return board.at(coords(0,0)) == playerOne? 1:2;	
	}
	
	//diagonal (top right to bottom left)
	if(board.at(coords(0,2)) == board.at(coords(1,1)) && board.at(coords(0,2)) == board.at(coords(2,0)) && board.at(coords(0,2)) != ' '){
		return board.at(coords(0,2)) == playerOne? 1:2;	
	}
	return 0;
}
unsigned int tictactoe::checkWin(){
	if(checkDownwards()){
		return checkDownwards();
	}
	if(checkSideWays()){
		return checkSideWays();
	}
	if(checkDiagonals()){
		return checkDiagonals();
	}
	return 0;
}
	
void tictactoe::AI(){
	m_x = std::uniform_int_distribution<int>(0, 2);
	m_y = std::uniform_int_distribution<int>(0, 2);

	unsigned int xMove = m_x(generator);
	unsigned int yMove = m_y(generator);

	while(!std::isdigit(board.at(coords(xMove,yMove)))){
		xMove = m_x(generator);
		yMove = m_y(generator);
	}
	board[coords(xMove,yMove)] = playerTwo;
}
	
void tictactoe::colorPrint(const char chr){
	unsigned int color;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		
	//if it's a number
	if(std::isdigit(chr)) color = 8;
	if(chr==playerOne) color = 1;
	if(chr==playerTwo) color = 4;
	SetConsoleTextAttribute(hConsole,color);
	std::cout<<chr;
	//change the color back to white
	SetConsoleTextAttribute(hConsole,7);
}

void tictactoe::displayBoard(){
	for(unsigned int a = 0; a < 3; a++){
		for(unsigned int b = 0; b < 3; b++){
			std::cout<<"| ";
			colorPrint(board.at(coords(a,b)));
			std::cout<<" |";
		}
		std::cout<<"\n";
	}
}

tictactoe::tictactoe(){}	
	
void tictactoe::twoPlayerMode(){
	chooseSymbol();
	while(true){
		displayBoard();
		if(checkFull() || checkWin()) break;
		std::cout << "Player One, Your Move: ";
		changeBoard(playerOne);
		displayBoard();
		if(checkFull() || checkWin()) break;
		std::cout << "Player Two, Your Move: ";
		changeBoard(playerTwo);
	}
	if(checkWin()){
		std::cout<<"The winner is Player "<<checkWin();
	}
	else{
		std::cout<<"It is a draw!";
	}
}
	
void tictactoe::onePlayerMode(){
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());		
	chooseSymbolOnePlayer();
	while(true){
		displayBoard();
		if(checkFull() || checkWin()) break;
		std::cout<<"Your Move: ";
		changeBoard(playerOne);
		if(checkFull()||checkWin()) break;
		AI();
	}
	if(checkWin()){
		std::cout<<"\n";		
		displayBoard();
		if(checkWin()==1){
			std::cout<<"You win!";
		}
		else{
			std::cout<<"You've lost!";
		}
	}
	else{
		std::cout<<"It is a draw!";
	}
}
	
void tictactoe::run(){
	unsigned int gameDecision = 0;
	while(true){
		std::cout<<"Type in the amount of players you'd like to play with.\n";
		while(gameDecision < 1 || gameDecision > 2){
			std::cin>>gameDecision;
		}
		if(gameDecision==1) onePlayerMode();
		if(gameDecision==2) twoPlayerMode();
		board={'1','2','3','4','5','6','7','8','9'}; //reset board
		std::cout<<"\nEnter 1 if you'd like to play again.\n";
		std::cin>>gameDecision;
		if(gameDecision!=1) break;
	}
}