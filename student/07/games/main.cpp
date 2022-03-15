/*  COMP.CS.100 Project 2: GAME STATISTICS
 *
 *   A program to monitor data from multiple games
 *
 *   The data includes game names, players and their points in specific games
 *   Has seemingly endless storage to go through.
 *   Works with STL storages.
 *
 *   The program works as follows:
 *   1. the program asks for an input file
 *      *the file should be a readable text document
 *      *the data should be formatted as follows:
 *          gamename;playername;points
 *      *where point should be represented in numbers
 *      *when the input is in order and read and saved to the program memory, it closes the file and start the mainloop
 *
 *   1.b. if the input file isn't in the correct format program ends with correct error message
 *      -doesn't have 3 data pieces separated by semicolons
 *      -is the wrong filetype
 *
 *   2.  in the main input loop program asks for a command and depending on the command does following things:
 *
 *      *QUIT
 *          -self explanatory, quits the program
 *
 *      *ALL_GAMES
 *          -prints all the game names saved in the storage, in alphabetical order
 *
 *      *GAME x
 *          -requires a game name in the x spot, if the name has two words separated by a space, the name should be inside ""
 *          -prints the x games players and their points in form of a scoreboard
 *
 *      *ALL_GAMES
 *          -prints all games stored in the database in alphabetical order
 *
 *      *PLAYER x
 *          -requires a player name in the x spot, if the name has two words separated by a space, the name should be inside ""
 *          -prints all the games that player x has scores in
 *
 *      *ADD_GAME x
 *          -requires a game name in the x spot, if the name has two words separated by a space, the name should be inside ""
 *          -adds a game to the programs database
 *
 *      *ADD_PLAYER x y z
 *          -requires three inputs for the player addition
 *              -x == the game name that the player plays
 *              -y == the players name
 *              -z == the players score in the game x
 *          -if player has a score already in the game, this updates it
 *
 *      *REMOVE x
 *          -requires a player name in the x spot, if the name has two words separated by a space, the name should be inside ""
 *          -removes a player from the whole database
 *          -can NOT be used to remove player from a single game
 *
 *
 *
 *      Ohjelman kirjoittaja
 *      Nimi: Otto Palmgren
 *      Opiskelijanumero:
 *      Käyttäjätunnus: protpa
 *      E-mail: otto.palmgren@tuni.fi
 *
 *      Huomiota ohjelmasta ja sen toteutuksesta:
 *
 *      Olisin ehkä halunnut tehdä tietorakenteen olio-ohjelmoinnilla, mutta ei valmiudet riittänyt suorittaa sitä c++
 *      Muutamassa kohdassa joutui tekemään lukuisia väliaikaissäiliöitä datan käsittelyyn, olisi mukava tietää miten dataa kannattaisi
 *      käsitellä vastaavassa tilanteessa, ilman lukuisia väliaikaissäiliöitä, ohjelman optimoinniksi.
 *
 * */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>

//Alphabetize the given vector and print it
void Aprint(std::vector<std::string> v){
    sort(v.begin(),v.end());
    for(unsigned int i=0;i<v.size();++i){
        std::cout<<v.at(i)<<std::endl;
    }
}

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split( const std::string& str, char delim = ';' )
{
    std::vector<std::string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = not inside_quatation;
        }
        else if ( current_char == delim and not inside_quatation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

//Function to open the file, add the data in the file to gamedata map
//also has implemented function failure recognisition in failname
bool readfile(std::string filename, std::set<std::string>& xgames,
              std::map<std::string,std::map<std::string, int>>& gdata, std::string& failname){

    //if opening the file the maininterface gets
    //info that failure was because of "unread" unreadability
    std::ifstream file(filename);
    if(!file){
        failname = "unread";
        return false;
    }
    //loop for getting the data
    else{
        std::string row="";
        while(getline(file,row)){
            std::vector<std::string> vecrow = split(row);

            //If input row doesn't meet the required 3 data pieces
            //returns failname of bad format in file
            if(vecrow.size()!=3){
                failname = "badformat";
                return false;
            }
            //if the game is already in the existing games set
            if(xgames.find(vecrow[0])!=xgames.end()){

                //if the player has played the game before
                if(gdata[vecrow[0]].find(vecrow[1])!=gdata[vecrow[0]].end()){
                    gdata[vecrow[0]][vecrow[1]]=stoi(vecrow[2]);
                }

                //if the player isn't in the map
                else{
                    //adds the player data
                    gdata[vecrow[0]].insert({vecrow[1],stoi(vecrow[2])});
                }
            }
            //if the game hasn't been inserted to xgames
            else{
                xgames.insert(vecrow[0]);
                gdata[vecrow[0]][vecrow[1]] = stoi(vecrow.at(2));;
            }
        }

    }
    file.close();
    return true;
}

void allgames(std::set<std::string>& xgames){
    //temporary vector to get the games sorted
    std::vector<std::string> tvec={};
    for(const auto &a : xgames){
        tvec.push_back(a);
    }
    std::cout<<"All games in alphabetical order:"<<std::endl;
    Aprint(tvec);
}

//Creates temporary data storages to analyze and print all the players names
void allplayers(std::map<std::string,std::map<std::string, int>> gdata){

    //temporary set for fast search of existing players
    std::set<std::string> stnames={};
    //temporary vector for sorting and printing the players
    std::vector<std::string> vtnames={};

    //goes through the main game data and adds the names to temporary set and vec
    for (const auto &item : gdata) {
        for(const auto &item2 : item.second){
            //if the namee is already in the temp set it doesn't get added again
            if(stnames.find(item2.first)!=stnames.end()){
            }
            else{
                stnames.insert(item2.first);
                vtnames.push_back(item2.first);
            }
        }
    }
    std::cout<<"All players in alphabetical order:"<<std::endl;
    Aprint(vtnames);
}

//Goes through the main gamedata and searches for instances of the wanted player pname
//If player exists prints the player name and the games played by pname
void player(std::map<std::string,std::map<std::string, int>> gdata, std::string pname){

    //temporary set for games that the player pname plays
    std::set<std::string> spgames={};
    //temporary vector of the games that the player plays
    //used for easy sorting
    std::vector<std::string> vpgames={};

    //goes through the main data to get the players played games
    //a.first is the game name a.second is the player name
    for(const auto &a : gdata){
        //b.first is the player name and b.second is the points amount
        for(const auto &b : a.second){
            //if the wanted name is found in the game being searched through
            if(b.first==pname){
                //gets added if the name isn't in the temp set and vec already
                if(spgames.find(pname)==spgames.end()){
                    spgames.insert(a.first);
                    vpgames.push_back(a.first);
                }
            }
        }
    }

    //if the player isn't found in any of the games.
    if(vpgames.size()==0){
        std::cout<<"Error: Player could not be found."<<std::endl;
    }
    //Prints the players name and the list of games
    else{
    std::cout<<"Player "<<pname<<" playes the following games:"<<std::endl;
    Aprint(vpgames);
    }

}

//Goes thtough the main gamedata and creates a new temporary data storage for the wanted game
//Prints the game and the points and players, all in order
void prntgame(std::map<std::string,std::map<std::string, int>> gdata, std::string gname){

    //if the game exists starts the search
    if(gdata.find(gname)!=gdata.end()){

        //vector for the points to print them in order
        std::vector<int> usednumbers = {};
        //temp map to hold the gname games data with search capability for the points amount
        std::map<int, std::vector<std::string> > thegamedata = {};

        //1. Adding the data from gdata to the wanted game == thegamedata vector
        //
        for(const auto& b : gdata.at(gname)){

            //if the points amount is an entry in the games data
            if(thegamedata.find(b.second)!=thegamedata.end()){
                //if the name is already in the list in the key "points"
                bool isinthelist = false;
                for(unsigned int i=0;i<thegamedata[b.second].size();++i){
                    if(thegamedata[b.second].at(i)==b.first){
                        isinthelist = true;
                    }
                }
                if(not isinthelist){
                    thegamedata[b.second].push_back(b.first);
                }
            }
            //else add the point amount to used and insert the points amount to thgamedata
            //and add the name to vector going with it
            else{
                usednumbers.push_back(b.second);
                thegamedata.insert({b.second,{b.first}});
            }
        }

        //sorting the points values in usednumbers
        std::sort(usednumbers.begin(),usednumbers.end());


        //2. Sorting the names in the vector inside thegamedata map
        //
        //b.first is the points amount and b.second is the names VECTOR
        for(const auto& b : thegamedata){
            std::sort(thegamedata.at(b.first).begin(),thegamedata.at(b.first).end());
        }

        //2.b. Changing the names vector to a single string with commas
        //
        for(const auto& c : thegamedata){
            std::string namestr="";
            for( size_t i = 0; i < thegamedata.at(c.first).size(); ++i ) {
                namestr += thegamedata[c.first].at(i);
                namestr += ", ";
            }
            namestr.pop_back();namestr.pop_back();
            //deleting the old key and value to enter the new one with single string
            thegamedata.erase(c.first);
            thegamedata.insert({c.first,{namestr}});
            //now the data can be accesed by data.at(points) and the output is the
            //player names in one string
        }

        //3. Printing the output
        //
        std::cout<<"Game "<<gname<<" has these scores and players, listed in ascending order:"<<std::endl;
        for(unsigned int j=0;j<usednumbers.size();++j){
                    std::cout<<usednumbers.at(j)<<" : "<< thegamedata[usednumbers.at(j)].at(0) <<std::endl;
                }
    }

    //if the game isn't found
    else{
    std::cout<<"Error: Game could not be found."<<std::endl;
    }


}

//adds the wanted game to the database
void addgame(std::map<std::string,std::map<std::string, int>>& gdata,std::set<std::string>& xgames, std::string gname){
    //checks whether the game is already in the list, if not adds it
    if(gdata.find(gname)==gdata.end()){
        gdata.insert({gname,{}});
        xgames.insert(gname);
        std::cout<<"Game was added."<<std::endl;
    }
    else{
        std::cout<<"Error: Already exists."<<std::endl;
    }
}

//adds the wanted player and score to the wanted games database,
//if the player has a score, updates it
void addplayer(std::map<std::string,std::map<std::string, int>>& gdata, std::string gname, std::string pname, int points){

    //if the game exists in the database
    if(gdata.find(gname)!=gdata.end()){
        //adds the data if the player hasn't a score in the game already
        if(gdata[gname].find(pname)==gdata[gname].end()){
            gdata[gname].insert({pname,points});
        }
        //adds only the points if the player has a score already
        else{
            gdata[gname][pname] = points;
        }
        std::cout<<"Player was added."<<std::endl;
    }
}

//goes through the data given and if finds instance of player pname existing and having scores in a game
//erases them.
void removeplayer(std::map<std::string,std::map<std::string, int>>& gdata,std::string pname){
    //bool for finding the pname
    bool found = false;

    //loop goes through the data and if finds instance of pname deletes its data
    //a.first is game name a.second is map of players and scores
    for(const auto& a: gdata){
        //if the player name is found in the game being searched
        if(gdata[a.first].find(pname)!=gdata[a.first].end()){
            gdata[a.first].erase(pname);
            found=true;
        }
    }

    //if the player got removed prints that
    //else prints error message of not found
    if(found){
        std::cout<<"Player was removed from all games."<<std::endl;
    }
    else{
        std::cout<<"Error: Player could not be found."<<std::endl;
    }
}

//the main loop for inputting the commands and returning if somtehing doesn't go as expected
//bool type to make while input loop in main
bool inputloop(std::set<std::string>& xgames, std::map<std::string,std::map<std::string, int>>& gdata){

    //ask for input and use split on it to get the command as a single entity
    std::string cmnd ="";
    std::cout<<"games> ";
    getline(std::cin,cmnd);

    //split into vector using split() and ' ' as delimiter
    std::vector<std::string> cmndv = split(cmnd,' ');

    //transforms the command part to uppercase
    cmnd = cmndv.at(0);
    std::transform(cmnd.begin(), cmnd.end(), cmnd.begin(), ::toupper);

    //checks what the command in question does and does it
    //if it is a bad command error is printed and new command needed
    //
    if(cmnd=="QUIT"){
        return false;
    }
    else if(cmnd=="ALL_GAMES" and cmndv.size()==1){
        allgames(xgames);
    }
    else if(cmnd=="GAME" and cmndv.size()==2){
        prntgame(gdata,cmndv.at(1));
    }
    else if(cmnd=="ALL_PLAYERS" and cmndv.size()==1){
        allplayers(gdata);
    }
    else if(cmnd=="PLAYER" and cmndv.size()==2){
        player(gdata,cmndv.at(1));
    }
    else if(cmnd=="ADD_GAME" and cmndv.size()==2){
        addgame(gdata,xgames,cmndv.at(1));
    }
    else if(cmnd=="ADD_PLAYER" and cmndv.size()==4){
        addplayer(gdata,cmndv.at(1),cmndv.at(2),stoi(cmndv.at(3)));
    }
    else if(cmnd=="REMOVE" and cmndv.size()==2){
        removeplayer(gdata,cmndv.at(1));
    }
    else{
        std::cout<<"Error: Invalid input."<<std::endl;
    }

    return true;
}


int main()
{
    //set of existing games
    std::set<std::string> xgames = {};
    //map for players points in a game
    std::map<std::string,std::map<std::string, int>> gdata={};

    //setting the name of input file
    std::cout<< "Give a name for input file: ";
    std::string filename = "";
    getline(std::cin,filename);
    
    //opening and writing the file data
    std::string failname = "";
    if(!readfile(filename,xgames,gdata,failname)){
        //if the file couldn't be read prints the correct failure reason according to failname
        //if file errors, the program ends with exit failure
        if(failname=="unread"){
            std::cout<<"Error: File could not be read."<<std::endl;
            return EXIT_FAILURE;
        }
        if(failname=="badformat"){
            std::cout<<"Error: Invalid format in file."<<std::endl;
            return EXIT_FAILURE;
        }
    }

    //the main input loop
    while(inputloop(xgames,gdata)){
    }
    return EXIT_SUCCESS;
}
