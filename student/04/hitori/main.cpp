#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>

/*THE HITORI GAME
 *
 * The game works as follows:
 *  The gameboard is a 5x5 grid that is filled with values that range from 1 to 5.
 *  One by one you remove a value from the grid.
 *
 *  How to set up the board:
 *
 *      When running the game, the user will be asked for input (R or I). The input
 *      determines the game set up style. There is two options for this. Either you
 *      choose R (==random) that decides the boards values at random with a seed that
 *      you decide. Or you choose I (==input) and input the values to put on the board
 *      yourself. You must input the values in one go without pressing enter, separating
 *      the values with a space.
 *
 *  How to play the game:
 *
 *      The player is asked every round to enter coordinates of a value that they want to
 *      remove from the grid. The coordinates are separated from the gameboard to be clear.
 *      The values that go from left to right at the top of the board are x-coordinates.
 *      The values that go from up to down on the far left of the board are y-coordinates.
 *
 *  Winning:
 *
 *      The goal is to have every horizontal row and vertical line
 *      to have no repeating values (in example; number 2 can't be twice the second row).
 *
 *      A row or line does NOT have to have specific values across it. The values on the
 *      row or line can be anything as long as there is no REPEATING values.
 *
 *  Losing:
 *
 *      You'll lose the game if you delete a value that has an empty square next to it.
 *      So if you remove number at 1,3 and then try to remove 2,3 the game is lost.
 *      This works both vertically and horizontally but not diagonally.
 *
 *      The second losing condition is having a square with a value be alone. If a value
 *      doesn't have a valueful square adjacent to it the game is lost. So the values that
 *      remain on the board must be "touching".
 *
 *
 *  Ohjelman kirjoittaja
 *      Nimi: Otto Palmgren
 *      Opiskelijanumero: 50327953
 *      Käyttäjätunnus: protpa
 *      E-mail: otto.palmgren@tuni.fi
 *
 *  Huomioita ohjelmasta ja sen toteutuksesta:
 *
 *      Ensinnäkin ohjelma on tehty vaikeimman kautta suurimmassa osassa, mutta se
 *      toimii. Tällä c++ kokemuksella tulos jopa yllättää. Laudan täytössä jos antaa
 *      tietyn väärän arvon saattaa ohjelma hajota (ainakin aiemmassa versiossa), mutta
 *      sitä ei ehtinyt lähteä tutkimaan. Koitin silmäillä opetusmateriaalista try,except
 *      kaltaista toimintoa, mutten löytänyt. Tilanteden tarkastelu olisi ollut helppoa
 *      ellei olisi tarvinnut vältellä erroreja. Ohjelma täytyi saada valmiiksi ja
 *      tällaisena täyttää myös kriteerit.
 *
 * */

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';


//Returns the input string as the same string but without empty characters
std::string removeSpaces(std::string input)
{
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
}


// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const std::string& str){

    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i){
        if(not isdigit(str.at(i))){
            is_numeric = false;
            break;
        }
    }
    if(is_numeric){
        return stoi(str);
    }
    else{
        return 0;
    }
}


//Gives values to every coordinate on the platform.
//Has choice of inputting values manually or generating randomly.
//Randomizing works with default random engine and seed is timeNULL.
//Manual takes one value at a time and adds them to xVal vector,
//and after row getting completed pushes yRow back by the created vector.
void createBoard(std::vector< std::vector<int> >& yRow){
    std::default_random_engine rand;

    //the randoms range is what a singular value at the board can get 1-5
    std::uniform_int_distribution<> dist(1,5);

    //Loop verifies that the input given is r or i (not case sensitive)
    //and does not end until the input is r or i
    while(true){
        std::string seed = "";
        std::cout << "Select start (R for random, I for input): ";
        std::getline(std::cin,seed);
        if (seed == "R" or seed == "r"){

            //asks for the seed value "seedput" as for seed input
            //sets the seed to given value or if input is letters; to 0 with stoi_
            std::cout <<"Enter seed value: ";
            std::string seedput = "";
            std::getline(std::cin, seedput);
            rand.seed(stoi_with_check(seedput));

            //generates 5 random values to vector xVal, which represents a row
            //after 5 iterations the vector is added to yRow
            for (unsigned int y=0; y<BOARD_SIDE; ++y){
                std::vector<int> xVal = {};
                for (unsigned int x=0; x<BOARD_SIDE; ++x){
                    xVal.push_back(dist(rand));
                }
            yRow.push_back(xVal);
            }
            break;
        }

        //gets the input manually and the user has to either copy paste the values in or
        //give one value at a time.
        //if the input goes through removeSpaces() to be more easily usable by the loop
        else if(seed=="i" or seed=="I"){

            while(true){
                std::string input="";
                std::cout << "Input: ";
                std::getline(std::cin,input);
                std::string intPut = removeSpaces(input);

                if(intPut.size()==25){
                    for (unsigned int y=0; y < BOARD_SIDE; ++y){
                        std::vector<int> xVal;
                        for (unsigned int x=0; x<BOARD_SIDE; ++x){
                            //as the loop goes on the first character gets deleted so index is always
                            //the correct one
                            char newChar = intPut.at(0);
                            //changes the intPut char to int which is then added to the vector and
                            //removed from the string
                            int newNumb = newChar-'0';
                            if(newNumb > 5 or newNumb < 0){
                                std::cout<<"You must input 25 numbers between 1-5"<<std::endl;
                            }
                            else{
                                xVal.push_back(newNumb);
                                intPut.erase(0,1);
                            }
                        }
                    yRow.push_back(xVal);
                    }
                    break;
                }
                else{
                    std::cout<<"You must input 25 numbers between 1-5"<<std::endl;
                }
            }
            break;
        }
    }
}


// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
//
// Prints the game board with row and column numbers.
void print(const std::vector< std::vector<int> >& gameboard){
    std::cout << "=================" << std::endl;
    std::cout << "|   | 1 2 3 4 5 |" << std::endl;
    std::cout << "-----------------" << std::endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i){
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j){
            if(gameboard.at(i).at(j) == 0){
                std::cout << EMPTY << " ";
            }
            else{
                std::cout << gameboard.at(i).at(j) << " ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "=================" << std::endl;
}


//"Deletes" the value after checking wether it has been already removed
//Changes the vectors vectors value at the coordinates to zero and returns true
//If it has been removed already nothing is changed and this returns true
bool deleteVal(std::vector< std::vector<int> >& yRow, const std::vector<int> coords) {
        //the grid starts from 1 but indexes at 0 so -1 to
        //coordinates is a must
        unsigned int y = (coords.at(0))-1;
        unsigned int x = (coords.at(1))-1;

        if(yRow.at(y).at(x) == 0){
            std::cout << "Already removed" <<std::endl;
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
void askValue(std::vector<int>& coords){
    while(true){
        //coordinates are str to allow the quit input of 'q'
        //and to use them with stoi_with_check
        std::string x = "";
        std::string y = "";
        std::cout << "Enter removable element (x, y): ";
        std::cin >> x;

        if (x == "q" or x == "Q"){
            std::cout << "Quitting"<<std::endl;
            break;
        }

        //asks for the second value only after determining earlier whether user wants to quit or not
        else{
            std::cin >> y;
            if (stoi_with_check(x) == 0 or stoi_with_check(y) == 0 or stoi(x) > 5 or stoi(y) > 5){
                std::cout << "Out of board"<<std::endl;
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
bool isEndEmpties(const std::vector< std::vector<int> > yRow){

    //Loop starts from 0 and goes to 4 because of the index values
    //starting at 0 when coordinates start at 1
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
//if a value doesn't have neighbours with value returns true
//if a value has a neighbour value at any side return value is false
bool isAlone(const std::vector< std::vector<int> > yRow){

    //Loop starts from 0 and goes to 4 because of the index values
    //starting at 0 when coordinates start at 1
    for(int y=0; y<=4; ++y){
        for(int x=0; x<=4;++x){

            //binding all cases y==0
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
bool isLost(std::vector< std::vector<int> >& yRow){
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
bool isWon(std::vector< std::vector<int> >& yRow){

    //this loop checks the horizontal lines for double values
    for(unsigned int y=0; y<BOARD_SIDE; ++y){
        //if the same value appears twice it returns false as the game has not been won
        for(unsigned int x=0; x<BOARD_SIDE;++x){
            //loop for the comparison value
            for(unsigned int l=0; l<BOARD_SIDE; ++l){
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
    std::vector< std::vector<int> > yRow={};

    createBoard(yRow);
    print(yRow);

    //Starts the actual game that goes on in a loop until isLost or isWon
    while(true){

        //vector coords is emptied every time to get new values in
        std::vector<int> coords = {};
        askValue(coords);

        //doesn't loop if the coordinates are unusable == if user quits
        if(coords.size()>1){
            //checks that the value given is removable or doesn't go to check for wins or losses
            if(deleteVal(yRow, coords)){
                //checks for losses
                if (isLost(yRow)){
                    print(yRow);
                    std::cout << "You lost"<<std::endl;
                    break;
                }
                //if the game hasn't been lost checks for wins
                else if(isWon(yRow)){
                    print(yRow);
                    std::cout << "You won"<<std::endl;
                    break;
                }
                //and if the game goes on prints the board and starts loop again
                else{
                    print(yRow);
                }
            }
        }
        //this only gets triggered if the player quits and coords has one value
        //coords.size()==1
        else{
            break;
        }

    }
    return 0;
}
