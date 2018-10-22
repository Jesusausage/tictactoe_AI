#include <iostream>

using namespace std;


struct Move {
    int score;
    int row, col;
};


void print_board(const char board[3][3]);
void make_move(char board[3][3], char &player);
char check_winner(const char board[3][3]);
void swap_player(char &player);
bool check_legal_move(const char board[3][3], int row, int col);
char opponent(char player);
Move minimax(char board[3][3], char player);
void AI_move(char board[3][3], char&player);


int main()
{
    char board[3][3] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    char player = 'X';
    char winner = ' ';
    char human;
    
    cout << "Choose noughts or crosses (input 'O' or 'X'): ";
    cin >> human;
    while (human!='O' && human!='X') {
	cout << "Invalid choice, please enter 'O' or 'X': ";
	cin >> human;
    }

    cout << "\nThe board is: \n";
    print_board(board);

    while(winner == ' ') {
	if (player == human)
	    make_move(board, player);
	else
	    AI_move(board, player);

	cout << "\nThe board is now: \n";
	print_board(board);
	winner = check_winner(board);
    }

    if (winner != 'D') {
	cout << "The winner is " << winner << ".\n";
	if (winner == player)
	    cout << "You win.\n\n";
	else
	    cout << "You lose.\n\n";
    }
    else
	cout << "Draw. \n\n";

    return 0;
}


void print_board(const char board[3][3]) {
    cout << "\n     1   2   3";
    cout << "\n   +===+===+===+\n";
    for (int rows=0; rows<3; rows++) {
	char letter = rows+'A';
	cout << " " << letter << " |";
	for (int cols=0; cols<3; cols++) {
	    cout << " " << board[rows][cols] << " |";
	}
	cout << "\n   +===+===+===+\n";
    }
    cout << endl;
}


void AI_move(char board[3][3], char&player) {
    cout << "Computer's turn to make a move...\n";
    
    Move bestResponse = minimax(board, player);
    char row = bestResponse.row + 'A';
    char col = bestResponse.col + '1';

    cout << "Computer chooses " << row << col << ".\n";
    board[bestResponse.row][bestResponse.col] = player;

    swap_player(player);
}


void make_move(char board[3][3], char &player) {
    char tile[2];

    cout << "Player's turn to make a move (enter coordinates for " << player << "): ";
    cin >> tile;
    int row = tile[0]-'A';
    int col = tile[1]-'1';

    while (!check_legal_move(board, row, col)) {
	cout << "Invalid move. Enter another location: ";
	cin >> tile;
	row = tile[0]-'A';
	col = tile[1]-'1';
    }
    
    board[row][col] = player;

    swap_player(player);
}


char check_winner(const char board[3][3]) {
    for (int rows=0; rows<3; rows++) {
	if (board[rows][0]==board[rows][1] && board[rows][1]==board[rows][2])
	    return board[rows][0];
    }
    
    for (int cols=0; cols<3; cols++) {
	if (board[0][cols]==board[1][cols] && board[1][cols]==board[2][cols])
	    return board[0][cols];
    }

    if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
	return board[0][0];

    if (board[2][0]==board[1][1] && board[1][1]==board[0][2])
	return board[2][0];

    for (int rows=0; rows<3; rows++) {
	for (int cols=0; cols<3; cols++)
	    if (board[rows][cols] == ' ') return ' ';
    }
    
    return 'D';
}


void swap_player(char &player) {
    if (player=='X') player='O';
    else if (player=='O') player='X';
}


bool check_legal_move(const char board[3][3], int row, int col) {
    if (board[row][col]!=' ' || row<0 || row>2 || col<0 || col>2)
	return 0;
    return 1;
}


char opponent(char player) {
    if (player == 'O') return 'X';
    if (player == 'X') return 'O';
}


Move minimax(char board[3][3], char player) {
    Move bestMove;
    bestMove.score = -99;
    char winner;

    for (int rows=0; rows<3; rows++) {
	for (int cols=0; cols<3; cols++) {
	    if (board[rows][cols] == ' ') {

		board[rows][cols] = player;
		winner = check_winner(board);

		int score = -99;
		if (winner == opponent(player))
		    score = -1;
		if (winner == 'D')
		    score = 0;
		if (winner == player)
		    score = 1;

		if (score > bestMove.score) {
		    bestMove.row = rows;
		    bestMove.col = cols;
		    bestMove.score = score;
		}

		board[rows][cols] = ' ';

	    }
	}
    }

    if (winner != ' ') return bestMove;

    for (int rows=0; rows<3; rows++) {
	for (int cols=0; cols<3; cols++) {
	    if (board[rows][cols] == ' ') {

		board[rows][cols] = player;
		swap_player(player);

		Move bestResponse = minimax(board, player);

		int score = -1 * bestResponse.score;
		if (score > bestMove.score) {
		    bestMove.row = rows;
		    bestMove.col = cols;
		    bestMove.score = score;
		}

		board[rows][cols]= ' ';
		swap_player(player);

	    }
	}
    }

    return bestMove;
}
