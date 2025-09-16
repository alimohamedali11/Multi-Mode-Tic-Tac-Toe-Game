#include <iostream>
#include <cstdlib> // for system()

#define RESET   "\033[0m" // used to reset the color into default
#define RED     "\033[31m" 
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"

using namespace std;

void tic_tac_toe() {
	cout << "========================================\n";
	cout << "            TIC-TAC-TOE GAME\n";
	cout << "========================================\n";
}

void clear_screen() { // clear the screen and scrollback buffer
	// we haven't relied only on system("cls") because it works only with windows.
   // so we used system("clear") for other OS as linux, macOS,..
#ifdef _WIN32 //a preprocessor directive checks if you are compiling your program on Windows 32-bit or 64-bit.
	system("cls");
#else // If you are NOT compiling on Windows (meaning you are on Linux, macOS, or other Unix-like OS), this branch runs.
	system("clear");
#endif
}

void enter_player_names(string& player1, string& player2) {
	tic_tac_toe();
	cout << "           ENTER PLAYER NAMES\n";
	cout << "========================================\n";
	cout << "Enter name for Player 1 : ";
	cin >> player1;
	cout << "Enter name for Player 2 : ";
	cin >> player2;
	clear_screen();
}

void display_board(char board[3][3]) {

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[row][col] == 'X') {
				cout << RED; // to make X have a RED colour
			}
			else if (board[row][col] == 'O') {
				cout << GREEN; // to make O have a GREEN colour
			}
			cout << "  " << board[row][col] << RESET;
			if (col == 0 || col == 1) {
				cout << MAGENTA << "   | " << RESET; // to make the board have a MAGENTA colour
			}
			else { // (col == 2)
				cout << '\n';
				if (row == 0 || row == 1) {
					cout << MAGENTA << "  -----------------\n" << RESET; // to make the board have a MAGENTA colour
				}
			}
		}
	}
}

void score_board(string player1, string player2, int& player1_score, int& player2_score, int games_played) {
	cout << '\n' << "<< " << player1 << ": " << player1_score << "  |  " << player2 << ": " << player2_score << " >>";
	cout << "   Games Played : " << games_played << "\n";
	cout << "---------------------------------------\n";
}

void final_result_UI(string player1, string player2, int& player1_score, int& player2_score, int games_played) {
	clear_screen();

	if (player1_score > player2_score) {
		cout << " OVERALL WINNER: " << player1;
	}
	else if (player1_score < player2_score) {
		cout << " OVERALL WINNER: " << player2;
	}
	else { // draw
		cout << " OVERALL RESULT: DRAW";
	}
	cout << "\n---------------------------------------";
	score_board(player1, player2, player1_score, player2_score, games_played);
	cout << "Thanks for playing!\n";
}

void player_move_validation(char& player_move, char board[3][3], char current_symbol) {

	for (;;) {
		for (; !(player_move >= '1' && player_move <= '9');) {
			cout << "\nenter a Valid Number from 1 To 9 : ";
			cin >> player_move;
		}
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (board[row][col] == player_move) {
					board[row][col] = current_symbol;
					return;
				}
			}
		}
		// this means that player_move not found in the numbers from 1 to 9 , so it is taken , so we must enter a new valid non-chosen number
		cout << "\nenter a valid non-chosen number from 1 to 9 : ";
		cin >> player_move;
	}
}

char win_checker(char board[3][3]) {

	for (int row = 0, col = 0; row < 3; row++) { // rows win checker
		if ((board[row][col] == board[row][col + 1]) && (board[row][col] == board[row][col + 2]) && (board[row][col] != '\0')) {
			return board[row][col];
		}
	}

	for (int col = 0, row = 0; col < 3; col++) { // columns win checker
		if ((board[row][col] == board[row + 1][col]) && (board[row][col] == board[row + 2][col]) && (board[row][col] != '\0')) {
			return board[row][col];
		}
	}

	if ((board[0][0] == board[1][1]) && (board[0][0] == board[2][2]) && (board[0][0] != '\0')) { // diagonals win checker
		return board[0][0];
	}
	else if ((board[0][2] == board[1][1]) && (board[0][2] == board[2][0]) && (board[0][2] != '\0')) {
		return board[0][2];
	}
	return '\0'; // in case it still draw
}

void single_game_display(string player1, string player2, int& player1_score, int& player2_score, int games_played) {

	char board[3][3] = { {'1','2','3'},
						 {'4','5','6'},
						 {'7','8','9'}
	};
	// we make an Array only contains X and O instead of 1D array of strings to make the logic easier

	display_board(board);
	score_board(player1, player2, player1_score, player2_score, games_played);

	for (int turn = 1; turn <= 9; turn++) {
		char current_symbol; // X or O
		if (turn % 2 == 1) { // exchanging players after each turn
			cout << player1 << " Enter a Number [1-9] : ";
			current_symbol = 'X';  // X always starts
		}
		else {
			cout << player2 << " Enter a Number [1-9] : ";
			current_symbol = 'O'; // O always plays the second one
		}

		char player_move; // must be from [1-9]
		cin >> player_move;
		player_move_validation(player_move, board, current_symbol); // to validate player_move (to be from 1 to 9 and non-chosen number) 
		// input validation + replacing player_move from the board[] with the current_symbol (X or O)

		clear_screen();
		display_board(board);
		score_board(player1, player2, player1_score, player2_score, games_played);

		char winner = win_checker(board); // we assigned the returned value from the function in the variable winner to avoid calling the function twice
		if (winner == 'X') {
			player1_score++;
			clear_screen();
			display_board(board);
			score_board(player1, player2, player1_score, player2_score, games_played + 1);
			cout << "*** " << player1 << " Wins! ***\n"; // X always plays first
			return;
		}
		else if (winner == 'O') {
			player2_score++;
			clear_screen();
			display_board(board);
			score_board(player1, player2, player1_score, player2_score, games_played + 1);
			cout << "*** " << player2 << " Wins! ***\n"; // O always plays second
			return;
		}
	}
	// Nobody wins , game is draw
	score_board(player1, player2, player1_score, player2_score, games_played + 1);
	cout << "*** It's a Draw! ***\n";
}

void Play_Until_Exit_Mode(string player1, string player2, int& player1_score, int& player2_score) { // you will be asked after each game to continue or end

	for (int games_played = 0;; games_played++) {  // we have make a variable Games_played to use it in the logic of change player starting
		clear_screen();
		if (games_played % 2 == 0) { // changing who starts first
			single_game_display(player1, player2, player1_score, player2_score, games_played);
		}
		else {
			single_game_display(player2, player1, player2_score, player1_score, games_played);
		}

		cout << "---------------------------------------\n";
		cout << "What do you want to do?\n";
		cout << "[0] End\n";
		cout << "[1] Continue Playing\n";
		cout << "Enter a Number [0-1] : ";
		char choice; // declare it as a charachter not integer to handle char input also not only integers
		cin >> choice;
		for (; choice != '0' && choice != '1';) {
			cout << "\nEnter a Valid Number [0-1] : ";
			cin >> choice;
		}
		if (choice == '0') {
			final_result_UI(player1, player2, player1_score, player2_score, games_played + 1);
			return;
		}
	}
}

void Match_Selection_Mode(string player1, string player2, int& player1_score, int& player2_score) { // play a specific number of matches
	int no_of_matches;
	cout << "Enter The Number of Matches : ";
	cin >> no_of_matches;
	for (int games_played = 0; games_played < no_of_matches; games_played++) {
		clear_screen();
		if (games_played % 2 == 0) { // changing who starts first
			single_game_display(player1, player2, player1_score, player2_score, games_played);
		}
		else {
			single_game_display(player2, player1, player2_score, player1_score, games_played);
		}

		if (games_played != no_of_matches - 1) { // this will not execute only in the last turn
			cout << "---------------------------------------\n";
			cout << "Press Enter or anything to continue . . . . : ";
			cin.ignore(1000, '\n'); // remove the newline and 1000 charachters from the buffer.
			cin.get(); // Reads 1 character even if newline (pressing enter), and waits if buffer is empty.
			// used to stop the system("cls") to show the board status (is it a win or a draw) by asking the user to enter any charachter
		}
	}
	final_result_UI(player1, player2, player1_score, player2_score, no_of_matches);
}

void choose_game_mode(string player1, string player2) {
	tic_tac_toe();
	cout << "Players:  " << player1 << "      vs      " << player2 << '\n';
	cout << "========================================\n";
	cout << "            CHOOSE GAME MODE\n";
	cout << "========================================\n";
	cout << "choose Game Mode :\n";
	cout << "[0] Play Until Exit     (you will be asked after each game to continue or end)\n";
	cout << "[1] Match Selection     (play a specific number of matches)\n";
	cout << "Enter 0 or 1 to continue : ";
	char mode; // declare it as a charachter not integer to handle char input also not only integers
	cin >> mode;
	for (; mode != '0' && mode != '1';) { // runs untill the user enters 0 or 1
		cout << "\nEnter a Valid Number : ";
		cin >> mode;
	}

	int player1_score = 0, player2_score = 0; // count the players scores
	if (mode == '0') {
		Play_Until_Exit_Mode(player1, player2, player1_score, player2_score);
	}
	else { // (mode == '1')
		Match_Selection_Mode(player1, player2, player1_score, player2_score);
	}
}

int main() {

	string player1, player2;
	enter_player_names(player1, player2);
	choose_game_mode(player1, player2);
}