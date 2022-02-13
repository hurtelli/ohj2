#include <iostream>
#include <vector>
#include <random>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';


vector< vector<int> > yRow;

//Gives values to every coordinate on the platform.
//Has choice of inputting values manually or generating randomly.
//Randomizing works with default random engine and seed is timeNULL.
//Manual takes one value at a time and adds them to xVal vector,
//and after row getting completed pushes yRow back by the created vector.

void createBoard(){
    default_random_engine rand;
    uniform_int_distribution<> dist(1,5);
    string  seed="";
    cout << "Select start (R for random, I for input): ";
    cin >> seed;

    if (seed == "R" or seed == "r"){
        rand.seed(time(NULL));
        for (unsigned int y=0; y<BOARD_SIDE; ++y){
            vector<int> xVal;
            for (unsigned int x=0; x<BOARD_SIDE; ++x){
                xVal.push_back(dist(rand));
            }
        yRow.push_back(xVal);
        }
    }
    //maybe change method to make the input also accept all the numbers at once
    //###########MAKE THIS CHECK THE INPUT USER GIVES!!!!!!!!!!!!##########
    else{
        int input;
        cout << "Input: ";
        for (unsigned int y=0; y<BOARD_SIDE; ++y){
            vector<int> xVal;
            for (unsigned int x=0; x<BOARD_SIDE; ++x){
                cin >> input;
                xVal.push_back(input);
            }
        yRow.push_back(xVal);
        }
    }
}






// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
//
// Prints the game board with row and column numbers.
void print(const vector< vector<int> >& gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

bool deleteVal(){
    string input="";
    string input2="";
    cout << "Enter removable element (x, y): ";
    cin >> input >> input2;

    if (input == "q" or input == "Q"){
        cout << "Quitting"<<endl;
        return false;
    }
    else{

        if (stoi_with_check(input)==0 or stoi_with_check(input2) == 0){
            cout << "Out of board"<<endl;
            return false;
        }
        else{
            return true;
        }
    }
}

int hasWon(){
    return true;
}


int main()
{
    createBoard();
    print(yRow);

    //Starts the actual game that goes on in a loop until the function gets value false
    while(true){
        if(deleteVal()){
        }
        else{

            break;
        }

    //prints the winning or losing or nothing message depending on the value of hasWon
    if (hasWon){

    }
    }
    cout << "toimi";
    return 0;
}
