// ECE 114 Project with Options 1 and 2
// March 9, 2016
// This program is an interactive game of tic-tac-toe where the user (Player X) plays against a computer (Player O)

#include <iostream>
using namespace std;

const int g_cRows = 5;	// Number of rows in the 2D tic-tac-toe board
const int g_cCols = 5;	// Number of columns in the 2D tic-tac-toe board

/** Initializes the 2D array tic-tac-toe board to be an empty board
 *	@param[in]		aachBoard		2D array tic-tac-toe board
 *	@param[in]		nRow			Number of rows in the 2D array
 *	@param[in]		nCol			Number of columns in the 2D array
 */
void InitializeBoard(char aachBoard[][g_cCols], const int g_cRows, const int g_cCols) {
	int iRow;	// Current row index of array
	int iCol;	// Current column index of array

	for (iRow = 0; iRow < g_cRows; iRow++) {
		for (iCol = 0; iCol < g_cCols; iCol++) {
			aachBoard[iRow][iCol] = '-';
		}
	}
}

/** Prints the current status of the game board
 *	@param[in]		aachBoard		2D array tic-tac-toe board
 *	@param[in]		g_cRows			Number of rows in the 2D array
 *	@param[in]		g_cCols			Number of columns in the 2D array
 */
void PrintBoard(const char aachBoard[][g_cCols], const int g_cRows, const int g_cCols) {
	int iRow;	// Current row index of array
	int iCol;	// Current column index of array

	for (iRow = 0; iRow < g_cRows; iRow++) {
		for (iCol = 0; iCol < g_cCols; iCol++) {
			cout << aachBoard[iRow][iCol] << " ";
		}
		cout << "\n";
	}

	cout << "\n";
}

/** Checks if the selected square is not yet taken
 *	@param[in]	aachBoard	2D array tic-tac-toe board
 *	@param[in]	nRow		Row of selected square
 *	@param[in]	nCol		Column of selected square
 *	@return					True if square available, false if not
 */
bool CheckValidSquare(const char aachBoard[][g_cCols], const int nRow, const int nCol) {
	if (aachBoard[nRow][nCol] == '-') {
		// Selected square has not yet been chosen, therefore valid
		return true;
	} else {
		// Selected square is already taken, square not valid
		return false;
	}
}

/** Updates the player's winning combination progress arrays
 *	@param[in]			nPlayer		Current player
 *	@param[in]			nRow		Row of selected square
 *	@param[in]			nCol		Column of selected square
 *	@param[in,out]		anXProg		Player X's winning combination progress
 *	@param[in,out]		anOProg		Player O's winning combination progress
 */
void UpdateProgress(const int nPlayer, const int nRow, const int nCol, int anXProg[], int anOProg[]) {
	// Updates player's progress on the winning combinations that are all rows or all columns
	switch (nPlayer) {
		// Updates Player X's progress
		case 1:
			anXProg[nRow]++;
			anXProg[nCol + g_cCols]++;
			break;
		
		// Updates Player O's progress
		case 2:
			anOProg[nRow]++;
			anOProg[nCol + g_cCols]++;
			break;
	}

	// Updates progress on the diagonal winning combination from top left to bottom right
	if (nRow == nCol) {
		switch (nPlayer) {
			case 1:
				anXProg[g_cRows + g_cCols]++;
				break;
			case 2:
				anOProg[g_cRows + g_cCols]++;
				break;
		}
	}

	// Updates progress on the diagonal winning combination from bottom left to top right
	if (nRow + nCol == g_cRows-1) {
		switch (nPlayer) {
			case 1:
				anXProg[g_cRows + g_cCols + 1]++;
				break;
			case 2:
				anOProg[g_cRows + g_cCols + 1]++;
				break;
		}
	}
}

/** Generates a random valid row and column pair for Player O (computer)
 *	@param[in,out]		aachBoard		2D array tic-tac-toe board
 *	@param[in]			anXProg			Player X's winning combination progress
 *	@param[in,out]		anOProg			Player O's winning combination progress
 */
void ComputerTurn(char aachBoard[][g_cCols], int anXProg[], int anOProg[]) {
	int nMin = 0;					// Minimum value chosen
	int nMax = g_cRows-1;			// Maximum value chosen
	int nWidth = nMax - nMin + 1;	// Width of interval for random number
	int nRandNum;					// Current random number in full range
	int nRow;						// Randomly chosen row
	int nCol;						// Raandomly chosen column

	// Generates a random row
	nRandNum = rand();
	nRow = nRandNum % nWidth + nMin;

	// Generates a random column
	nRandNum = rand();
	nCol = nRandNum % nWidth + nMin;

	// Checks if randomly generated pair is a valid square, if not, generate a new random pair
	if (CheckValidSquare(aachBoard, nRow, nCol) == false) {
		ComputerTurn(aachBoard, anXProg, anOProg);
	} else {
		UpdateProgress(2, nRow, nCol, anXProg, anOProg);
		cout << "Player O randomly chooses row " << nRow << " and col " << nCol << "\n";
		aachBoard[nRow][nCol] = 'O';
	}
}

/** Prompts the appropriate player to select a square via row and column coordinate
 *	@param[in]		nPlayer		Current player
 *	@param[in]		aachBoard	2D array tic-tac-toe board
 *	@param[in]		anXProg		Player X's winning combination progress
 *	@param[in]		anOProg		Player O's winning combination progress
 */
void PlayerTurn(int nPlayer, char aachBoard[][g_cCols], int anXProg[], int anOProg[]) {
	int nRow;	// Row index chosen
	int nCol;	// Column index chosen

	switch (nPlayer) {
		// Player X (user) turn
		case 1:
			// Prompts player for a valid row until given
			do
			{
				cout << "Player X please enter row (0 to " << g_cRows-1 << "): ";
				cin >> nRow;
				
				if (nRow < 0 || nRow > g_cRows-1) {
					cout << "Invalid entry\n";
				}
			} while (nRow < 0 || nRow > g_cRows-1);

			// Prompts player for a valid column until given
			do
			{
				cout << "Player X please enter col (0 to " << g_cCols-1 << "): ";
				cin >> nCol;

				if (nCol < 0 || nCol > g_cCols-1) {
					cout << "Invalid entry\n";
				}
			} while (nCol < 0 || nCol > g_cCols-1);

			// Checks if the chosen square is taken
			if (CheckValidSquare(aachBoard, nRow, nCol) == true) {
				UpdateProgress(1, nRow, nCol, anXProg, anOProg);
				aachBoard[nRow][nCol] = 'X';
			} else {
				cout << "That square is taken. Lose a turn.\n";
			}

			break;
		// Player O (computer) turn
		case 2:
			ComputerTurn(aachBoard, anXProg, anOProg);
			break;
	}
}

/** Checks the current status of the game
 *	@param[in,out]		bGameOver		Boolean true if game over, false if not
 *	@param[in,out]		nPlayer			Current player
 *	@param[in]			anXProg			Player X's winning combination progress
 *	@param[in]			anOProg			Player O's winning combination progress
 *	@param[in]			nWinCombo		Number of winning combinations
 *	@param[in]			aachBoard		2D array tic-tac-toe board
 *	@param[in]			g_cRows			Number of rows in the 2D array
 *	@param[in]			g_cCols			Number of columns in the 2D array
 */
void CheckStatus(bool & bGameOver, int & nPlayer, const int anXProg[], const int anOProg[], const int nWinCombo, const char aachBoard[][g_cCols], const int g_cRows, const int g_cCols) {
	int iArr; // Current index of array
	
	switch (nPlayer) {
		case 1:
			// Checks if Player X has won by completing a winning combination
			for (iArr = 0; iArr < nWinCombo; iArr++) {
				if (anXProg[iArr] == g_cRows) {
					PrintBoard(aachBoard, g_cRows, g_cCols);
					cout << "Player X wins\n";
					bGameOver = true;
					return;
				} else {
					bGameOver = false;
				}
			}

			if (bGameOver == false) {
				nPlayer = 2;
			}
			break;
		
		case 2:
			// Checks if Player O has won by completing a winning combination
			for (iArr = 0; iArr < nWinCombo; iArr++) {
				if (anOProg[iArr] == g_cRows) {
					PrintBoard(aachBoard, g_cRows, g_cCols);
					cout << "Player O wins\n";
					bGameOver = true;
					return;
				} else {
					bGameOver = false;
				}
			} 
			
			if (bGameOver == false) {
				nPlayer = 1;
			}
			break;
	} 
}

/** Checks if the board is full with no winner, resulting in a tie
 *	@param[in,out]		bGameOver		Boolean true if game over, false if not
 *	@param[in]			aachBoard		2D array tic-tac-toe board
 *	@param[in]			g_cRows			Number of rows in the 2D array
 *	@param[in]			g_cCols			Number of columns in the 2D arrays
 */
void CheckTieStatus (bool & bGameOver, const char aachBoard[][g_cCols], const int g_cRows, const int g_cCols) {
	int iRow;	// Current row index
	int iCol;	// Current column index

	// Checks if the game has been declared over yet
	if (bGameOver != false) {
		// If game is already over, return
		return;
	} else {
		// Checks if there is an available square to choose
		for (iRow = 0; iRow < g_cRows; iRow++) {
			for (iCol = 0; iCol < g_cCols; iCol++) {
				// If a square is available, continue the game
				if (aachBoard[iRow][iCol] == '-') {
					bGameOver = false;
					return;
				} else {
					// Since there are no more available squares, game is over
					bGameOver = true;
				}
			}
		}

		// Prints the status of the board and declares the game a tie
		if (bGameOver == true) {
			PrintBoard(aachBoard, g_cRows, g_cCols);
			cout << "Game ended in a tie\n";
		}
	}
}

int main() {
	char aachBoard[g_cRows][g_cCols];					// 2D array tic-tac-toe board
	int nPlayer = 1;									// Current player turn (1 = Player X, 2 = Player O)
	bool bGameOver = false;								// Boolean true if game is over, false if not
	const int nWinCombo = g_cRows + g_cCols + 2;		// Number of winning combininations
	int anXProg[nWinCombo] = { };						// Player X's winning combination progress
	int anOProg[nWinCombo] = { };						// Player O's winning combination progress

	InitializeBoard(aachBoard, g_cRows, g_cCols);

	while (bGameOver == false) {
		PrintBoard(aachBoard, g_cRows, g_cCols);
		PlayerTurn(nPlayer, aachBoard, anXProg, anOProg);
		CheckStatus(bGameOver, nPlayer, anXProg, anOProg, nWinCombo, aachBoard, g_cRows, g_cCols);
		CheckTieStatus(bGameOver, aachBoard, g_cRows, g_cCols);
	}

	system("pause");
	return (0);
}