#include "stdafx.h"
#include "TicTacToe.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <iterator>
using namespace std;

void main()
{
	gameController();
}

void gameController() {
	//Welcome prompt
	cout << "Welcome to Tic Tac Toe!, player uses \"X\", computer uses \"O\"\n";
	cout << "When selecting move, enter number inside box you'd like to choose\n";
	//Initialize board
	char currBoard[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	int move;
	vector<int> playersPicks;
	vector<int> computersPicks;
	//Get beginning board
	getBoard(currBoard);
	//Begin game
	while (true) {
		//Get player's move
		int pMove = getPlayerMove(currBoard, move);
		playersPicks.push_back(pMove);
		sort(playersPicks.begin(), playersPicks.end());
		//Check for player win
		if (checkWin('p', playersPicks)) {
			//Update Board to show winner's move
			getBoard(currBoard);
			false;
			break;
		}
		// If no win, update Board and check for draw
		if (getBoard(currBoard)) {
			drawGame();
			false;
			break;
		}
		//Get computer's move
		int cMove = getCompMove(currBoard, playersPicks, computersPicks, move);
		computersPicks.push_back(cMove);
		sort(computersPicks.begin(), computersPicks.end());
		//Check for computer win
		if (checkWin('c', computersPicks)) {
			//Update Board to show computer's move
			getBoard(currBoard);
			false;
			break;
		}
		cout << "Computer player chose spot " << cMove << "\n";
		//If no win, update Board and check for draw
		if (getBoard(currBoard)) {
			drawGame();
			false;
			break;
		}
	}
}

bool getBoard(char board[]) {
	bool fullBoard = true;
	//Create current board
	int z = 0;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (board[z] != 'X' && board[z] != 'O') {
				fullBoard = false;
			}
			cout << "|";
			cout << board[z];
			z++;
		}
		cout << "|\n";
	}
	return fullBoard;
}

int(&getPlayerMove(char(&currBoard)[9], int(&move))) {
	//Prompt player's move and check move is valid
	do {
		cout << "Enter move: ";
		cin >> move;
		//If move entered isnt an integer, ask for integer
		while (!cin) {
			cout << "Please enter an integer: ";
			cin.clear();
			cin.ignore();
			cin >> move;
		}
	} while (move < 1 || move > 9 || currBoard[move - 1] == 'X' || currBoard[move - 1] == 'O');
	//Fill player's move into currBoard
	currBoard[move - 1] = 'X';
	return move;
}

bool checkWin(char user, vector<int> picks) {
	//Check for win
	set<int> winCombos[8];
	//Get possible winning combos
	getWinCombos(winCombos);
	int picksS = picks.size();
	set<int> diff;
	//Ensure player has a least 3 picks before checking
	if (picksS > 2) {
		for (int x = 0; x < 8; x++) {
			diff.clear();
			//Get difference between picks and winning combos to see if all picks are chosen by player being checked
			set_difference(winCombos[x].begin(), winCombos[x].end(), picks.begin(), picks.end(), inserter(diff, diff.end()));
			//If player has chosen all of a combo, difference is empty
			if (diff.empty()) {
				switch (user) {
				case 'p':
					cout << "Player Wins!!!!\n";
					break;
				case 'c':
					cout << "Computer Won!!!!\n";
					break;
				}
				return true;
			}
		}
	}
	return false;
}

void drawGame() {
	cout << "Draw Game!!\n";
}

int(&getCompMove(char(&currBoard)[9], vector<int> playersPicks, vector<int> computersPicks, int(&move))) {
	set<int> winCombos[8];
	//Create vector of corner spots for ideal placement
	vector<int> corner = { 1, 3, 7, 9 };
	//Get possible winning combos
	getWinCombos(winCombos);
	set<int> playerProg;
	set<int> computerProg;
	//Find if comp can get win in next turn
	for (int x = 0; x < 8; x++) {
		computerProg.clear();
		set_difference(winCombos[x].begin(), winCombos[x].end(), computersPicks.begin(), computersPicks.end(), inserter(computerProg, computerProg.end()));
		if (computerProg.size() == 1) {
			move = *computerProg.begin();
			if (currBoard[move - 1] != 'X' && currBoard[move - 1] != 'O') {
				currBoard[move - 1] = 'O';
				return move;
			}
			else {
				move = 0;
			}
		}
	}
	//If not, check player's move to see if win in next turn
	for (int x = 0; x < 8; x++) {
		playerProg.clear();
		set_difference(winCombos[x].begin(), winCombos[x].end(), playersPicks.begin(), playersPicks.end(), inserter(playerProg, playerProg.end()));
		if (playerProg.size() == 1) {
			move = *playerProg.begin();
			if (currBoard[move - 1] != 'X' && currBoard[move - 1] != 'O') {
				currBoard[move - 1] = 'O';
				return move;
			}
			else {
				move = 0;
			}
		}
	}
	//If not, check player's move to see if they can get two in same row/col using a corner spot
	if (currBoard[4] != 'X' && currBoard[4] != 'O') {
		currBoard[4] = 'O';
		move = 5;
		return move;
	}
	for (int x = 7; x > -1; x--) {
		playerProg.clear();
		set_difference(winCombos[x].begin(), winCombos[x].end(), playersPicks.begin(), playersPicks.end(), inserter(playerProg, playerProg.end()));
		if (playerProg.size() == 2) {
			set<int>::iterator iter = playerProg.begin();
			int tempBegin = *iter;
			advance(iter, 1);
			int tempEnd = *iter;
			if (currBoard[tempBegin - 1] != 'X' && currBoard[tempBegin - 1] != 'O' && find(corner.begin(), corner.end(), tempBegin) != corner.end()) {
				move = tempBegin;
				currBoard[move - 1] = 'O';
				return move;
			}
			else if (currBoard[tempEnd - 1] != 'X' && currBoard[tempEnd - 1] != 'O' && find(corner.begin(), corner.end(), tempEnd) != corner.end()) {
				move = tempEnd;
				currBoard[move - 1] = 'O';
				return move;
			}
			else {
				move = 0;
			}
		}
	}
	//If not, pick move
	if (currBoard[4] != 'X' && currBoard[4] != 'O') {
		currBoard[4] = 'O';
		move = 5;
		return move;
	}
	for (char m : currBoard) {
		if (m != 'X' && m != 'O') {
			move = m - '0';
			currBoard[move] = 'O';
			return move;
		}
	}
	return move;
}

set<int>(&getWinCombos(set<int>(&winCombos)[8])) {
	winCombos[0] = { 1, 2, 3 };
	winCombos[1] = { 4, 5, 6 };
	winCombos[2] = { 7, 8, 9 };
	winCombos[3] = { 1, 4, 7 };
	winCombos[4] = { 2, 5, 8 };
	winCombos[5] = { 3, 6, 9 };
	winCombos[6] = { 1, 5, 9 };
	winCombos[7] = { 3, 5, 7 };
	return winCombos[0];
}