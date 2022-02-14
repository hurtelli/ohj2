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


//"Deletes" the value after checking wether it has been already removed
//Changes the vectors vector at the place to zero
void deleteVal(vector< vector<int> >& yRow, const vector<int> coords) {
    unsigned int y = (coords.at(0))-1;
    unsigned int x = (coords.at(1))-1;
    if(yRow.at(y).at(x) == 0){
        cout << "Already removed"<<endl;
    }
    else{
        yRow.at(y).at(x) = 0;
    }
}


//Asks for 2 inputs for x and y coordinate to be removed
//Has faulty value check with stoi_with_check function
//Has also the quitting command input
//Adds the coordinates to a vector to use with other functions
void askValue(vector<int>& coords){
    string x="";
    string y="";
    cout << "Enter removable element (x, y): ";
    cin >> x;
    if (x == "q" or x == "Q"){
        cout << "Quitting"<<endl;
    }
    //asks for the second value after determining whether user wants to quit or not
    else{
        cin >> y;
        if (stoi_with_check(x) == 0 or stoi_with_check(y) == 0 or stoi(x) > 5 or stoi(y) > 5){
            cout << "Out of board"<<endl;
        }
        else{
            //transforms the string to int with stoi
            coords.push_back(stoi_with_check(y));
            coords.push_back(stoi_with_check(x));
        }
    }
}


//the function goes to check every single point on the board and checks wether it has values on its sides or not
//it also sees when the number has no connecting numbers and it is isolated
bool isEndEmpties(const vector< vector<int> > yRow){
    //creating the loop
    for(int y=0; y <= 4; ++y){
        for(int x=0; x <= 4; ++x){
            //If the value at the point is zero then the function will check the right value and lower value
            //If there is no possible right value only lower is checked and vice versa(elseif)
            if(yRow.at(y).at(x)==0){
                if(y <= 3){
                    if(x < 4 and (yRow.at(y).at(x+1)==0 or yRow.at(y+1).at(x)==0)){
                        return true;
                    }
                    else if(x==4 and yRow.at(y+1).at(x)==0){
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


//isAlone checks every square and the neighbors to see wether they have values or not
//
bool isAlone(const vector< vector<int> > yRow){

    for(int y=0; y<=4; ++y){
        for(int x=0; x<=4;++x){

            //binding all y==0 to same
            if(y==0){
                //top left
                if(x==0){
                    if(yRow.at(y).at(x+1)==0 and yRow.at(y+1).at(x)==0){
                        return true;
                    }
                }
                //top right
                else if(x==4){
                    if(yRow.at(y).at(x-1)==0 and yRow.at(y+1).at(x)==0){
                        return true;
                    }
                }
                //top row
                else if(0 < x and x < 4){
                    if(yRow.at(y).at(x+1)==0 and yRow.at(y+1).at(x)==0 and yRow.at(y).at(x-1)==0){
                        return true;
                    }
                }
            }
            //binding all y=4
            else if(y==4){
                //bottom right
                if(x==4){
                    if(yRow.at(y).at(x-1)==0 and yRow.at(y-1).at(x)==0){
                        return true;
                    }
                }
                //bottom left
                else if(x==0){
                    if(yRow.at(y).at(x+1)==0 and yRow.at(y-1).at(x)==0){
                        return true;
                    }
                }
                //bottom row
                else if(0 < x and x < 4){
                    if(yRow.at(y).at(x+1)==0 and yRow.at(y-1).at(x)==0 and yRow.at(y).at(x-1)==0){
                        return true;
                    }
                }
            }

            //left column
            else if(0<y and y < 4 and x==0){
                if(yRow.at(y).at(x+1)==0 and yRow.at(y-1).at(x)==0 and yRow.at(y+1).at(x)==0){
                    return true;
                }
            }

            //right column
            else if(0 < y and y < 4 and x==4){
                if(yRow.at(y).at(x-1)==0 and yRow.at(y-1).at(x)==0 and yRow.at(y+1).at(x)==0){
                    return true;
                }
            }

            //In the center of the grid
            else{
                if(y < 4 and 0 < y and x < 4 and 0 < x){
                    if(yRow.at(y).at(x-1)==0 and yRow.at(y).at(x+1)==0 and yRow.at(y-1).at(x)==0 and yRow.at(y+1).at(x)==0){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


//binds the two functions of losing the game together
//and returns bool whether game has been lost or not
bool isGameOver(vector< vector<int> >& yRow){
    if(isEndEmpties(yRow) or isAlone(yRow)){
        return true;
    }
    else{
        return false;
    }
}


int main()
{
    //The vector yRow is the data storage that includes a vector for every row
    //Naming is a reminder that the first value that you input is the y-value
    //and the second value is the x in the correct y level
    vector< vector<int> > yRow;

    createBoard(yRow);
    print(yRow);

    //Starts the actual game that goes on in a loop until the function gets value false

    while(true){
        vector<int> coords = {};
        askValue(coords);
        if(coords.size() > 1){
            deleteVal(yRow, coords);
            if (isGameOver(yRow)){
                print(yRow);
                cout << "You lost"<<endl;
                break;
            }
            else{
                print(yRow);

            }
        }
        else{
            break;
        }
    }
    return 0;
}
