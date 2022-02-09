#include <iostream>
#include <fstream>
using namespace std;
const int gridsize = 3;
char board[gridsize][gridsize] = {{'-', '-', '-'},
                                  {'-', '-', '-'},
                                  {'-', '-', '-'}};
void save();
void load();
void menu();
void header();
void start_new();
void printBoard();
bool checkRows(char);
bool checkColumns(char);
bool checkDiagnols(char);
int retrieveRow(string);
int retrieveColumn(string);
bool isWinner(char);
string key;
int count = 0;
int option = 0;
char turn;
int main()
{
    string move;
    turn = 'X';
    char status = 'D';
    while (option != 3)
    {
        menu();
        if (option > 0 && option < 3)
        {
            if(option == 1){
                system("CLS");
                start_new();
            }
            if (option == 2)
            {
                load();
            }
            for (int z = 0; z < 9; z++)
            {
                header();
                printBoard();
                cout << "It is turn for " << turn << endl;
                cout << "Enter your move::";
                cin >> move;
                system("cls");
                if (retrieveRow(move) == -1 || retrieveColumn(move) == -1 || board[retrieveRow(move)][retrieveColumn(move)] != '-')
                {
                    while (retrieveRow(move) == -1 || retrieveColumn(move) == -1 || board[retrieveRow(move)][retrieveColumn(move)] != '-')
                    {
                        printBoard();
                        cout << "Enter Valid Move::" << endl;
                        cin >> move;
                        system("cls");
                    }
                }
                board[retrieveRow(move)][retrieveColumn(move)] = turn;
                save();
                if (isWinner(turn))
                {
                    status = 'W';
                    printBoard();
                    cout << "********** GAME OVER! *********** " << endl;
                    cout<<"***********  ";
                    cout << "The Winner is " << turn <<" ************" <<endl;
                    break;
                }
                if (turn == 'X')
                {
                    turn = 'O';
                    // cout << "The turn is = " << turn<<endl;
                }
                else if (turn == 'O')
                {
                    turn = 'X';
                    // cout << "The turn is 1 = " << turn<<endl;
                }

                // cout << "Press any key to continue:";
                // cin >> key;
            }
            if (status == 'D')
            {
                cout << "This Match is Draw..";
            }
        }
    }

    return 0;
}
void menu()
{
    cout << "1_Start New Game" << endl;
    cout << "2_Load Game." << endl;
    cout << "3_Exit" << endl;
    cout << "Enter your Option..";
    cin >> option;
}
void header(){
    cout <<endl<<endl;
    cout << "\t\t\t*******************************************************************"<<endl;
    cout << "\t\t\t*******************************************************************"<<endl;
    cout << "\t\t\t********************* Tic  Tac Toe Game **************************"<<endl;
    cout << "\t\t\t*******************************************************************"<<endl;
    cout << "\t\t\t*******************************************************************"<<endl;
    cout << "\t\t\t*******************************************************************"<<endl;
    cout << endl<<endl;
}
void printBoard()
{
    string temp_string = "ABC";
    cout << "\t\t\t\t\t       0       1       2"<<endl;  
    cout << "\t\t\t\t\t    ------- ------- -------" << endl;
    for(int i = 0;i<gridsize;i++){
        cout << "\t\t\t\t\t" <<temp_string[i]<<"   |  ";
        for(int a = 0;a<gridsize;a++){
            cout <<board[i][a]<<"   |   ";
        }
        cout << endl;
        cout << "\t\t\t\t\t    ------- ------- -------" << endl;
    }
    
}
int retrieveRow(string move)
{
    int row = -1;
    if (move[0] == 'A' || move[0] == 'a')
    {
        row = 0;
    }
    else if (move[0] == 'B' || move[0] == 'b')
    {
        row = 1;
    }
    else if (move[0] == 'C' || move[0] == 'c')
    {
        row = 2;
    }
    return row;
}
int retrieveColumn(string move)
{
    int column = 0;
    int temp = 0;
    string t = " ";
    for (int a = 0; a < gridsize; a++)
    {
        t = move[1];
        temp = stoi(t);
        if (temp == a)
        {
            column = temp;
            return column;
        }
    }
    return -1;
}
bool checkRows(char t)
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (board[x][y] == t)
            {
                count++;
            }
            if (count == 3)
            {
                return true;
            }
        }
        count = 0;
    }

    return false;
}
bool checkColumns(char t)
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (board[y][x] == t)
            {
                count++;
            }
            if (count == 3)
            {

                return true;
            }
        }
        count = 0;
    }

    return false;
}
bool checkDiagnols(char t)
{
    count = 0;
    for (int i = 0; i < 3; i++)
    {
        if (board[i][i] == t)
        {
            count++;
        }
    }
    if (count == 3)
    {
        return true;
    }
    count = 0;
    for (int row = 0, column = 2; row < 3; row++, column--)
    {
        if (board[row][column] == t)
        {
            count++;
        }
    }
    if (count == 3)
    {
        return true;
    }
    count = 0;
    return false;
}
bool isWinner(char turn)
{
    if (checkColumns(turn) || checkRows(turn) || checkDiagnols(turn))
    {
        return true;
    }
    return false;
}
void save()
{
    fstream file;
    file.open("tic_tac.txt", ios::out);
    for (int ridx = 0; ridx < gridsize; ridx++)
    {
        for (int cidx = 0; cidx < gridsize; cidx++)
        {
            file << board[ridx][cidx];
        }
        file << '\n';
    }
    if(turn == 'X') file<<'O';
    else if(turn == 'O') file << 'X';
    
    file.close();
}
void load()
{
    string line;
    int idx = 0;
    fstream file;
    file.open("tic_tac.txt", ios::in);

    while (!file.eof())
    {

        file >> line;
        for (int col = 0; col < gridsize; col++)
        {
            board[idx][col] = line[col];
        }
        idx++;
        if(idx == 3){
            file >> turn;
        }
    }
    file.close();
}
void start_new(){
    string line;
    int idx = 0;
    fstream file;
    file.open("empty.txt", ios::in);

    while (!file.eof())
    {

        file >> line;
        for (int col = 0; col < gridsize; col++)
        {
            board[idx][col] = line[col];
        }
        idx++;
    }
}