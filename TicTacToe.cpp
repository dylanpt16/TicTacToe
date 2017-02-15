#include <iostream>
using namespace std;

bool hasWin(char board[][3], char c)
{
    if ((board [0][0] == board[1][1]) && (board[1][1] == board[2][2])
            && (board[2][2] == c))
        return true;
    if ((board [0][2] == board[1][1]) && (board[1][1] == board[2][0])
            && (board[0][2] == c))
        return true;
    for (int i = 0; i < 3; i++)
    {
        if ((board [i][0] == board[i][1]) && (board[i][1] == board[i][2])
                && (board[i][2] == c))
            return true;
        if ((board [0][i] == board[1][i]) && (board[1][i] == board[2][i])
                && (board[2][i] == c))
            return true;
    }
    return false;
}

bool availPlaces(char board[][3])
{
    for (int i = 0;  i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
                return true;
        }
    }
    return false;
}

void printBoard(char board[][3])
{
    cout << "  1 2 3" << endl;
    for(int i = 0; i < 3; i++)
    {
        cout << "  ------" << endl;
        cout << (i+1);
        for(int j = 0; j < 3; j++)
        {
            cout << "|" << board[i][j];
        }
        cout << "|" << endl;
    }
    cout << "  ------" << endl;

}

int scores(char board[][3],int depth, bool comp )
{
    int bestScore;
    if(hasWin(board, 'O'))
    {
        return 10-depth;
    }
    if(hasWin(board, 'X'))
    {
        return depth-10;
    }
    if(!availPlaces(board))
    {
        return 0;
    }
    if(comp)
    {
        bestScore = -1000;
    }
    else
    {
        bestScore = 1000;
    }
    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(board[i][j] == '-')
            {
                if(comp)
                {
                    board[i][j] = 'O';
                    bestScore = max(bestScore,scores(board,depth+1, false));
                    board[i][j] = '-';
                }
                else
                {
                    board[i][j] = 'X';
                    bestScore = min(bestScore,scores(board,depth+1, true));
                    board[i][j] = '-';
                }
            }
        }
    }
    return bestScore;
}


void compMove(char board[][3])
{
    int r,c, score;
    int bestScore = -1000;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == '-')
            {
                board[i][j] = 'O';
                score = scores(board,1,false);
                if(score >= bestScore)
                {
                    bestScore = score;
                    r = i;
                    c = j;
                }
                board[i][j] = '-';
            }
        }
    }
    board[r][c] = 'O';
    printBoard(board);
}

void playerMove(char board[][3], char player)
{
    int r, c;
    cout << player << " turn:\n";
    cout << "Please choose row: ";
    cin >> r;
    cout << "Please choose column: ";
    cin >> c;
    while( r < 1 || r > 3 || c < 1 || c > 3 || board[r-1][c-1] != '-')
    {
        cout << "Not Available! Please choose another place!" << endl;
        cout << "Please choose row: ";
        cin >> r;
        cout << "Please choose column: ";
        cin >> c;
    }
    board[r-1][c-1] = player;
    printBoard(board);
}

void play(char board[][3], bool comp)
{
    printBoard(board);
    while (availPlaces(board))
    {
        playerMove(board,'X');
        if(hasWin(board,'X'))
        {
            cout << "X wins!" << endl;
            return;
        }
        if(comp && availPlaces(board))
        {
            compMove(board);
        }
        else if (availPlaces(board))
        {
            playerMove(board,'O');
        }
        if(hasWin(board,'O'))
        {
            cout << "O wins!" << endl;
            return;
        }
        if(!availPlaces(board))
        {
            cout << "It's a Tie!" << endl;
        }
    }
}

void initialize(char board[][3])
{
    for (int i = 0;  i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '-';
        }
    }
}

int main(int argc, char*argv[])
{
    if ( argc !=1 )
    {
        cout << "Wrong number of argument, please check and enter it" << endl;
        return -1;
    }
    char board [3][3];
    int ans;
    bool computer = false;
    cout << "How many players? (1/2) ";
    cin >> ans;
    if (ans == 2)
    {
        computer = false;
    }
    else
    {
        computer = true;
    }
    initialize(board);
    play(board, computer);
    return 0;
}
