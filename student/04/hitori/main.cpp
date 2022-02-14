#include <iostream>
#include <vector>
#include <random>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';




//Gives values to every coordinate on the platform.
//Has choice of inputting values manually or generating randomly.
//Randomizing works with default random engine and seed is timeNULL.
//Manual takes one value at a time and adds them to xVal vector,
//and after row getting completed pushes yRow back by the created vector.

void createBoard(vector< vector<int> >& yRow){
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

void deleteVal(vector< vector<int> >& yRow, const vector<int> coords) {

    unsigned int y = (coords.at(0))-1;
    unsigned int x = (coords.at(1))-1;
    if(yRow.at(y).at(x) == 0){
        cout << "Already removed"<<endl;
    }
    else{
        cout << coords.at(1)-1<<"  "<<coords.at(0)-1<<endl;
        cout <<"pete"<< yRow.at(y).at(x) <<endl;
        yRow.at(y).at(x) = 0;
    }
}

void askValue(vector<int>& coords){
    string x="";
    string y="";
    cout << "Enter removable element (x, y): ";
    cin >> x;
    if (x == "q" or x == "Q"){
        cout << "Quitting"<<endl;
    }
    else{
        cin >> y;
        if (stoi_with_check(x) == 0 or stoi_with_check(y) == 0 or stoi(x) > 5 or stoi(y) > 5){
            cout << "Out of board"<<endl;
        }
        else{
            coords.push_back(stoi_with_check(y));
            coords.push_back(stoi_with_check(x));
        }
    }
}

//the function goes to check every single point on the board and checks wether it has values on its sides or not
//it also sees when the number has no connecting numbers and it is isolated
bool isEnd(const vector< vector<int> > yRow){
    cout << "alku"<<endl;
    //creating the loop
    for(int y=0; y <= 4; ++y){
        for(int x=0; x <= 4; ++x){
            //If the value at the point is zero then the function will check the right value and lower value
            //If there is no possible right value only lower is checked
            if(yRow.at(y).at(x)==0){
                if(y <= 3){
                    if(x < 4 and (yRow.at(y).at(x+1)==0 or yRow.at(y+1).at(x)==0)){
                        cout << "toimivanegro"<<endl;
                        return true;
                    }
                    else if(x==4 and yRow.at(y+1).at(x)==0){
                        cout << "toimivanegro"<<endl;
                        return true;
                    }

                }
                else if(y==4 and x < 4){
                    if(yRow.at(y).at(x+1)==0){
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

int main()
{
    vector< vector<int> > yRow;
    createBoard(yRow);
    print(yRow);

    //Starts the actual game that goes on in a loop until the function gets value false

    while(true){
        vector<int> coords = {};
        askValue(coords);
        deleteVal(yRow, coords);
        if (isEnd(yRow)){
            print(yRow);
            cout << "You lost"<<endl;
            break;
        }
        else{
            print(yRow);

        }
    }
    return 0;
}
