/*  COMP.CS.100 Project 2: GAME STATISTICS
 * ===============================
 * EXAMPLE SOLUTION
 * ===============================
 *
 *  Acts as a game statistics with n commands:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 *
 *  The data file's lines should be in format game_name;player_name;score
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>

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

bool readfile(std::string filename, std::set<std::string>& xgames,std::map<std::string,std::map<std::string, int>>& gdata){
    std::cout<<"beenis:DD"<<std::endl;
    std::ifstream file(filename);
    if(!file){
        return false;
    }
    else{
        std::string row="";
        while(getline(file,row)){
            std::vector<std::string> vecrow = split(row);
            //If input row doesn't meet the required 3 data pieces
            if(vecrow.size()!=3){
                std::cout<<"Error: Invalid format in file."<<std::endl;
                return EXIT_FAILURE;
            }
            //if the game is already in the xgames
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
    std::cout<<"benis"<<std::endl;
    for(const auto &a : xgames){
        tvec.push_back(a);
    }
    sort(tvec.begin(),tvec.end());
    for(unsigned int i=0;i<tvec.size();++i){
        std::cout<<tvec.at(i)<<std::endl;
    }
}

bool inputloop(std::set<std::string>& xgames, std::map<std::string,std::map<std::string, int>>& gdata){
    //ask for input and use split on it to get the command as a single entity
    std::string cmnd ="";
    std::cout<<"games>";
    std::cin>>cmnd;
    std::vector<std::string> cmndv = split(cmnd);
    cmnd = cmndv.at(0);
    std::transform(cmnd.begin(), cmnd.end(), cmnd.begin(), ::toupper);
    //command quit ends the loop and program
    if(cmnd=="QUIT"){
        return false;
    }
    else if(cmnd=="ALL_GAMES" and cmndv.size()<2){
        allgames(xgames);
    }
    else if(cmnd=="GAME"){
        //rakenna tää#######################
    }
    else if(cmnd=="ALL_PLAYERS"){
        //rakenna tää#######################
    }
    else if(cmnd=="PLAYER"){
        //rakenna tää#######################
    }
    else{
        std::cout<<"Invalid input"<<std::endl;
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
    std::cout<< "Give a name for an input file: ";
    std::string filename = "";
    getline(std::cin,filename);
    
    if(!readfile(filename,xgames,gdata)){
        std::cout<<"Error: File could not be read."<<std::endl;
        return EXIT_FAILURE;
    }
    while(inputloop(xgames,gdata)){

    }
    return EXIT_SUCCESS;
}
