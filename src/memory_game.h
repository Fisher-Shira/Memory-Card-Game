/**************
 * Shira Fisher
 * Computer Science Student
 **************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BOARD_DIM 4
#define MAX_NUM_PLAYERS 10
#define MAX_BOARD_LENGTH 25
#define MAX_CARD_LENGTH 11
#define INITIAL_POINTS 0
#define ROW_POS_CALC(pos) (pos / BOARD_DIM)
#define COL_POS_CALC(pos) (pos % BOARD_DIM)
#define NUM_OF_CARDS (int) (pow(BOARD_DIM, 2))
#define NUM_OF_OBJECTS (int) (NUM_OF_CARDS/2)
#define NUM_LEFT_PADDING(currentLen) (int) ((MAX_CARD_LENGTH - currentLen) / 2 + currentLen)
#define NUM_RIGHT_PADDING(currentLen) (int) ((MAX_CARD_LENGTH - currentLen) % 2 ? (MAX_CARD_LENGTH - currentLen) / 2 + 1 : \
                                        (MAX_CARD_LENGTH - currentLen) / 2)
#define NUM_ROW_DIVISION ((MAX_CARD_LENGTH+1) * BOARD_DIM + 3)
#define EXPLANATION_ROW_DIVISION (3 + (8 * BOARD_DIM))

typedef enum
{
    False,
    True
} Bool;
typedef struct
{
    char * name;
    int points;
} Player;
typedef struct
{
    char * type;
    Bool isMatched;
} Card;

Player createPlayer(const char *playerName);
void initializeAndExplainGame(Card (*board)[MAX_BOARD_LENGTH+1], Player arrPlayers[], int *numOfPlayers);
void printPlayersScores(Player arrPlayers[], int numOfPlayers);
void printGameBoard(Card (*board)[MAX_BOARD_LENGTH+1]);
Bool playerTurn(Player *currentPlayer, Card (*board)[MAX_BOARD_LENGTH+1]);
Bool isValidMove(int row, int col, Card (*board)[MAX_BOARD_LENGTH+1]);
Bool isCardsMatch(int firstRow, int firstCol, int secondRow, int secondCol, Card (*board)[MAX_BOARD_LENGTH+1]);
void CheckGameScores(int numOfPlayers, Player arrPlayers[]);