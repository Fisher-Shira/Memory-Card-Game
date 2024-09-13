/**************
 * Shira Fisher
 * Computer Science Student
 **************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "memory_game.h"

int main(int argc, char *argv[])
{
    // Run the game until someone win
    Card board[MAX_BOARD_LENGTH][MAX_BOARD_LENGTH+1];
    Player arrPlayers[MAX_NUM_PLAYERS + 1];
    int numPlayerTurn = 0, numOfMatches = 0, numOfPlayers;
    initializeAndExplainGame(board, arrPlayers, &numOfPlayers);
    printGameBoard(board);
    while(numOfMatches != NUM_OF_OBJECTS)
    {
        // Match
        if(playerTurn(&arrPlayers[numPlayerTurn%numOfPlayers], board))
        {
            numOfMatches += 1;
            printPlayersScores(arrPlayers, numOfPlayers);
            printGameBoard(board);
        }
        else
            numPlayerTurn += 1;
    }
    CheckGameScores(numOfPlayers, arrPlayers);
}

Player createPlayer(const char *playerName)
{
    // Create new Player
    Player newPlayer;
    newPlayer.name = malloc(strlen(playerName) + 1);
    if (newPlayer.name != NULL)
        strcpy(newPlayer.name, playerName);
    newPlayer.points = INITIAL_POINTS;
    return newPlayer;
}

void initializeAndExplainGame(Card (*board)[MAX_BOARD_LENGTH+1], Player arrPlayers[], int *numOfPlayers)
{
    // Initialize the game args + Print game explanation
    int playersCounter = 0, currentPos, rowPos, colPos;
    char *currentName;
    char playerNames[100];
    char *objects[] = {"Cat", "Dog", "Fish", "Giraffe", "Bird", "Turtle", "Kangaroo", "Dolphin"};
    printf("Welcome to the Memory Card Game!\n\n");
    // Board numbers positions
    char rowDivStr[EXPLANATION_ROW_DIVISION];
    memset(rowDivStr, '-', EXPLANATION_ROW_DIVISION);
    rowDivStr[EXPLANATION_ROW_DIVISION] = '\0';
    printf("The game will be played on the following board:\n  ");
    for (int i = 0; i < BOARD_DIM; i++)
        printf("|   %d   ", i);
    for (int i = 0; i < BOARD_DIM; i++)
    {
        printf("|\n%s\n%d ", rowDivStr, i);
        for (int j = 0; j < BOARD_DIM; j++)
            printf("| (%d,%d) ", i, j);
    }
    // Game objects
    printf("|\n%s\n\nAnd the following objects:\n", rowDivStr);
    for (int i = 0; i < NUM_OF_OBJECTS; i++)
        printf("%d. %s\n", i + 1, objects[i]);
    // Notice message
    printf("\nNotice: for your guessed cards you need to enter row space column (between 0 and 3)\n");
    printf("For example: '0 0' is the top left card in the (0,0) position\n\n");
    // Add players to the game
    printf("Enter the names of the players seperated by # (max %d): ", MAX_NUM_PLAYERS);
    scanf("%99s", playerNames);
    currentName = strtok(playerNames, "#");
    while(currentName != NULL && playersCounter < MAX_NUM_PLAYERS)
    {
        arrPlayers[playersCounter] = createPlayer(currentName);
        currentName = strtok(NULL, "#");
        playersCounter++;
    }
    *numOfPlayers = playersCounter;
    printf("There will be %d players in the game\n\n", playersCounter);
    // Add cards in arrange order
    for(int i=0; i< NUM_OF_CARDS; i++)
    {
        rowPos = ROW_POS_CALC(i);
        colPos = COL_POS_CALC(i);
        board[rowPos][colPos] = (Card) {objects[(int)i/2], 0};
    }
    // Shuffle the cards
    srand(time(0));
    for(int i=0; i< NUM_OF_CARDS; i++)
    {
        int j = rand() % NUM_OF_CARDS;
        Card temp = board[ROW_POS_CALC(i)][COL_POS_CALC(i)];
        board[ROW_POS_CALC(i)][COL_POS_CALC(i)] = board[ROW_POS_CALC(j)][COL_POS_CALC(j)];
        board[ROW_POS_CALC(j)][COL_POS_CALC(j)] = temp;
    }
    printf("Let the game begin!\n\n");
}

void printPlayersScores(Player arrPlayers[], int numOfPlayers)
{
    // Print the players scores
    printf("The scores are:\n");
    for(int i = 0; i < numOfPlayers; i++)
    {
        printf("%s: %d", arrPlayers[i].name, arrPlayers[i].points);
        if(i < numOfPlayers - 1)
            printf(", ");
    }
    printf("\n\n");
}

void printGameBoard(Card (*board)[MAX_BOARD_LENGTH+1])
{
    // Print board grids
    int numChars = NUM_ROW_DIVISION, currentLen;
    char rowDivStr[numChars];
    // Calculate number of row division chars
    memset(rowDivStr, '-', numChars);
    rowDivStr[numChars] = '\0';
    printf("Current board state:\n  ");
    // Board headers
    for (int i = 0; i < BOARD_DIM; i++)
        printf("|%*d%-*c", NUM_LEFT_PADDING(1), i, NUM_RIGHT_PADDING(1), ' ');
    // Board cards
    for (int i = 0; i < BOARD_DIM; i++)
    {
        printf("|\n%s\n%d ", rowDivStr, i);
        for (int j = 0; j < BOARD_DIM; j++)
        {
            currentLen = board[i][j].isMatched ? (int) strlen(board[i][j].type) : 1;
            printf("|%*s%-*c", NUM_LEFT_PADDING(currentLen), board[i][j].isMatched ? board[i][j].type : "X",
                   NUM_RIGHT_PADDING(currentLen), ' ');
        }
    }
    printf("|\n%s\n\n", rowDivStr);
}

Bool playerTurn(Player *currentPlayer, Card (*board)[MAX_BOARD_LENGTH+1])
{
    // Get 2 position and return answer (match/unmatch)
    int firstRow, firstCol, secondRow, secondCol;
    Bool isMatch = False;
    printf("It is %s's turn.\n", currentPlayer->name);
    // Get player 2 cards selection
    printf(" Enter the coordinates of the first card (row col):");
    scanf("%d %d", &firstRow, &firstCol);
    while(!isValidMove(firstRow, firstCol, board)) 
    {
        printf(" Invalid move. Try again.\n");
        printf(" Enter the coordinates of the first card (row col):");
        scanf("%d %d", &firstRow, &firstCol);
    }
    printf(" The card is a %s\n", board[firstRow][firstCol].type);
    printf(" Enter the coordinates of the second card (row col):");
    scanf("%d %d", &secondRow, &secondCol);
    while(!isValidMove(secondRow, secondCol, board) || (firstRow == secondRow && firstCol == secondCol)) 
    {
        printf(" Invalid move. Try again.\n");
        printf(" Enter the coordinates of the second card (row col):");
        scanf("%d %d", &secondRow, &secondCol);
    }
    printf(" The card is a %s\n", board[secondRow][secondCol].type);
    // Check match
    if(isCardsMatch(firstRow, firstCol, secondRow, secondCol, board))
    {
        printf(" Match!\n\n");
        currentPlayer->points += 1;
        isMatch = True;
    }
    else
        printf(" No match.\n\n");
    return isMatch;
}

Bool isValidMove(int row, int col, Card (*board)[MAX_BOARD_LENGTH+1])
{
    // Check if the card is valid - unmatched and the in valid positions
    Bool validUnmatchedCard, validPos;
    validUnmatchedCard = board[row][col].isMatched ? False : True;
    validPos = row >= BOARD_DIM || col >= BOARD_DIM || row < 0 || col < 0 ? False : True;
    return validUnmatchedCard && validPos;
}

Bool isCardsMatch(int firstRow, int firstCol, int secondRow, int secondCol, Card (*board)[MAX_BOARD_LENGTH+1])
{
    // Check if the 2 selected cards match
    if (!strcmp(board[firstRow][firstCol].type, board[secondRow][secondCol].type))
    {
        board[firstRow][firstCol].isMatched = True;
        board[secondRow][secondCol].isMatched = True;
        return True;
    }
    return False;
}

void CheckGameScores(int numOfPlayers, Player arrPlayers[])
{
    // Calculate the player with the greatest score
    int maxPoints = 0, nextMaxPoints = 0;
    char * playerMaxPointName;
    for(int i = 0; i < numOfPlayers; i++)
    {
        // Better score then the current max score
        if (arrPlayers[i].points > maxPoints)
        {
            nextMaxPoints = maxPoints;
            maxPoints = arrPlayers[i].points;
            playerMaxPointName = arrPlayers[i].name;
        }
        // Better score then the current second max score
        else if (arrPlayers[i].points > nextMaxPoints)
            nextMaxPoints = arrPlayers[i].points;
    }
    if(maxPoints == nextMaxPoints)
        printf("It's a tie! with %d points", maxPoints);
    else
        printf("Congratulations %s! You won with %d points!", playerMaxPointName, maxPoints);
}
