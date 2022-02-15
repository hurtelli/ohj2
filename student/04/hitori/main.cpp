#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';

string removeSpaces(string input)
{
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
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


//Gives values to every coordinate on the platform.
//Has choice of inputting values manually or generating randomly.
//Randomizing works with default random engine and seed is timeNULL.
//Manual takes one value at a time and adds them to xVal vector,
//and after row getting completed3 5 3 4 5 2 4 2 1 3 3 3 1 5 3 5 1 2 3 5 5 3 3 2 5 pushes yRow back by the created vector.

void createBoard(vector< vector<int> >& yRow){
    default_random_engine rand;
    uniform_int_distribution<> dist(1,5);

    //Loop verifies that the input given is r or i (not case sensitive)
    while(true){
        string  seed="";
        cout << "Select start (R for random, I for input): ";
        getline(cin,seed);
        if (seed == "R" or seed == "r"){
            rand.seed(time(NULL));
            for (unsigned int y=0; y<BOARD_SIDE; ++y){
                vector<int> xVal;
                for (unsigned int x=0; x<BOARD_SIDE; ++x){
                    xVal.push_back(dist(rand));
                }
            yRow.push_back(xVal);
            }
            break;
        }

        //gets the input manually
        else if(seed=="i" or seed=="I"){
            string input;
            cout << "Input: ";
            std::getline(std::cin,input);
            string intPut = removeSpaces(input);
            for (unsigned int y=0; y < BOARD_SIDE; ++y){
                vector<int> xVal;
                for (unsigned int x=0; x<BOARD_SIDE; ++x){
                    char newChar = intPut.at(0);
                    int newNumb = newChar-'0';
                    xVal.push_back(newNumb);
                    intPut.erase(0,1);
                }
            yRow.push_back(xVal);
            }
            break;
            }

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
bool deleteVal(vector< vector<int> >& yRow, const vector<int> coords) {
        unsigned int y = (coords.at(0))-1;
        unsigned int x = (coords.at(1))-1;
        if(yRow.at(y).at(x) == 0){
            cout << "Already removed" <<endl;
            return false;
        }
        else{
            yRow.at(y).at(x) = 0;
            return true;
        }
}


//Asks for 2 inputs for x and y coordinate to be removed
//Has faulty value check with stoi_with_check function
//Has also the quitting command input
//Adds the coordinates to a vector to use with other functions
void askValue(vector<int>& coords){
    while(true){
        string x="";
        string y="";
        cout << "Enter removable element (x, y): ";
        cin >> x;
        if (x == "q" or x == "Q"){
            cout << "Quitting"<<endl;
            break;
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
                break;
            }
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
bool isLost(vector< vector<int> >& yRow){
    if(isEndEmpties(yRow) or isAlone(yRow)){
        return true;
    }
    else{
        return false;
    }
}


//goes through all rows and vertical lines on the board and checks for double values
//returns false in case there is
    //1. a row that has the same value twice
    //2. a horizontal line that has the same value twice
//after it has checked every line it returns true and game has been won
bool isWon(vector< vector<int> >& yRow){

    //this loop checks the horizontal lines for double values
    for(unsigned int y=0; y<BOARD_SIDE; ++y){
        //if the same value appears twice it returns false as the game has not been won
        for(unsigned int x=0; x<BOARD_SIDE;++x){
            //loop for the comparison value
            for(unsigned int l=0; l<BOARD_SIDE; ++l){
                cout <<"rivit"<< x <<"  is compared to    " << l<<endl;
                if(yRow.at(y).at(x)!=0){
                    if(l != x){
                        if(yRow.at(y).at(x)==yRow.at(y).at(l)){
                            return false;
                        }

                    }
                }
            }
        }

    }
    //this loop checks the vertical lines for repeating values by ++x every round
    for(unsigned int x=0; x<BOARD_SIDE; ++x){
        //original value
        for(unsigned int y=0; y<BOARD_SIDE; ++y){
            //value that is being compared
            for(unsigned int p=0; p<BOARD_SIDE; ++p){
                cout <<"sarakkeet"<< y <<"  is compared to    " << p<<endl;
                if(yRow.at(y).at(x)!=0){
                    if(y != p){
                        if(yRow.at(y).at(x)==yRow.at(p).at(x)){
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
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
        //vector coords is emptied every time to get new values in
        vector<int> coords = {};
        askValue(coords);

        if(coords.size()>1){
            //checks that the value given is removable or doesn't go to check for wins or losses
            if(deleteVal(yRow, coords)){
                if (isLost(yRow)){
                    print(yRow);
                    cout << "You lost"<<endl;
                    break;
                }
                else if(isWon(yRow)){
                    print(yRow);
                    cout << "You won"<<endl;
                    break;
                }
                else{
                    print(yRow);
                }
            }
        }
        else{
            break;
        }

    }
    return 0;
}
