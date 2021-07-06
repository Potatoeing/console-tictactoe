#include <iostream>
#include <cmath>
#include <string>

using namespace std;

#define endl '\n'
#define DEBUG(x) cout << ">DEBUG: " << #x << ": " << (x) << endl;
#define print(s) cout << (s) << endl;

static bool ended = false;

static char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

static int currTurn = 1; //odd is 'O', even is 'X'
static string winner = "";

bool hasEnded(char board[], int n, int currTurn, int pos, string &winner)
{
    int cnt = 0;
    char tmp;
    //horizontal case:
    for(int i=0; i<n; i+=3)
    {
        tmp = board[i];
        cnt = 0;
        for(int j=0; j<3; j++)
        {
            if(board[i+j] == tmp)
                cnt++;
            
        }
        if(cnt == 3)
        {
            (currTurn%2 == 0) ? winner = 'X' : winner = 'O';
            return true;
        }
    }

    //vertical case:
    cnt = 0;
    for(int i=0; i<n/3; i++)
    {
        tmp = board[i];
        cnt = 0;
        for(int j=0; j<=i+6; j+=3)
        {
            if(board[i+j] == tmp)
                cnt++;
        }
        if(cnt == 3)
        {
            (currTurn%2 == 0) ? winner = 'X' : winner = 'O';
            return true;
        }
    }

    //l to r diagonal case:
    cnt = 0;
    tmp = board[0];
    for(int i=0; i<n; i+=4)
    {
        if(board[i] == tmp)
            cnt++;
        if(cnt == 3)
        {
            (currTurn%2 == 0) ? winner = 'X' : winner = 'O';
            return true;
        }
    }

    //r to l diagonal case:
    cnt = 0;
    tmp = board[n/3-1];
    for(int i=n/3-1; i<n/3+4; i+=2)
    {
        if(board[i] == tmp)
            cnt++;
        if(cnt == 3)
        {
            (currTurn%2 == 0) ? winner = 'X' : winner = 'O';
            return true;
        }
    }
    
    //tie case: if there isn't a digit in the board, all the spaces are filled
    for(int i=0; i<n; i++)
        if(isdigit(board[i]))
            return false;
    
    winner = "tie";
    return true;
}

string repeatString(string substring, int n)
{
    string r = "";
    while(n--) { r += substring; }
    return r;
}

void printBoard(char board[], int n, int size)
{
    int add;
    (size == 1) ? add = 0 : add = 1;
    
    for(int i=0; i<n; i+=n/3)
    {
        for(int j=0; j<size; j++)
        {
            string s1 = board[i]+string(add, ' ');
            string s2 = board[i+1]+string(add, ' ');
            string s3 = board[i+2]+string(add, ' ');
            cout << repeatString(s1, size) << string(size, ' ') << repeatString(s2, size) << string(size, ' ') << repeatString(s3, size) << endl;
        }
        cout << string(size/2, endl);
    }
}

void clearConsole() //"clears" console by printing a bunch of new lines
{
    cout << string(10, endl); 
}

bool isNumber(string s)
{
    return s.find_first_not_of("0123456789") == string::npos;
}

int main() 
{
    string pieceSizeStr; //piece size as string
    bool hasInit = false; 
    cout << "What do you want the size of the board pieces to be? Enter a positive integer." << endl;
    cin >> pieceSizeStr;
    while(!isNumber(pieceSizeStr) && stoi(pieceSizeStr) <= INT32_MAX)
    {
        cout << "Invalid input. What do you want the size of the board pieces to be? Enter a positive integer." << endl;
        cin >> pieceSizeStr;
    }   

    int pieceSize = stoi(pieceSizeStr);

    while(!ended)
    {
        bool validIn = false; 

        clearConsole();

        if(currTurn%2 == 1)
            cout << "It is O's Turn.\n" << endl; 
        else
            cout << "It is X's Turn.\n" << endl;

        cout << "Note: E means empty. Enter a number on the board to play a turn!\n" << endl;

        printBoard(board, 9, pieceSize);
        
        int t; //representing spot on board
        while(!validIn)
        {
            cin >> t;
            if(t == 69)
            {
                ended = true;
                break;
            }
            if(t < 1 || t > 9 || !isdigit(board[t-1]))
                cout << "Not a valid turn!" << endl;
            else
                validIn = true;
        }

        if(currTurn%2 == 0)
            board[t-1] = 'X';
        else    
            board[t-1] = 'O';

        ended = hasEnded(board, 9, currTurn, t, winner);
        currTurn++;
    }

    clearConsole();
    printBoard(board, 9, pieceSize);

    if(winner == "tie")
        cout << "The game ends in a tie!";
    else
        cout << '\n' << winner << " wins!";
    
    return 0;
}