#ifndef TicTacToe
#define TicTacToe
#include <vector>
#include <set>
using namespace std;
void gameController();
bool getBoard(char[]);
int(&getPlayerMove(char(&currBoard)[9], int(&move)));
int(&getCompMove(char(&currBoard)[9], vector<int> playersPicks, vector<int> computersPicks, int(&move)));
bool checkWin(char user, vector<int>);
void drawGame();
set<int>(&getWinCombos(set<int>(&winCombos)[8]));

#endif