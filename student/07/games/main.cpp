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
#include <sstream>

//Alphabetize the vector and print it
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

//Casual split func for useful purposes, splits str with ' '
std::vector<std::string> ssplit( const std::string& str, char delim = ' ' ){
      std::vector<std::string> output={};
      std::stringstream ss(str);
      std::string s;
      while (std::getline(ss, s, delim)) {
          output.push_back(s);
      }
      return output;
}

bool readfile(std::string filename, std::set<std::string>& xgames,std::map<std::string,std::map<std::string, int>>& gdata, std::string& failname){
    std::ifstream file(filename);
    if(!file){
        failname = "unread";
        return false;
    }
    else{
        std::string row="";
        while(getline(file,row)){
            std::vector<std::string> vecrow = split(row);
            //If input row doesn't meet the required 3 data pieces
            if(vecrow.size()!=3){
                failname = "badformat";
                return false;
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
    for(const auto &a : xgames){
        tvec.push_back(a);
    }
    Aprint(tvec);
}

void allplayers(std::map<std::string,std::map<std::string, int>> gdata){
    std::set<std::string> stnames={};
    std::vector<std::string> vtnames={};
    for (const auto &item : gdata) {
        for(const auto &item2 : item.second){
            if(stnames.find(item2.first)!=stnames.end()){
            }
            else{
                stnames.insert(item2.first);
                vtnames.push_back(item2.first);
            }
        }
    }
    Aprint(vtnames);
}

void player(std::map<std::string,std::map<std::string, int>> gdata, std::string pname){
    std::set<std::string> spgames={};
    std::vector<std::string> vpgames={};
    for(const auto &a : gdata){
        for(const auto &b : a.second){
            if(b.first==pname){
                if(spgames.find(pname)==spgames.end()){
                    spgames.insert(a.first);
                    vpgames.push_back(a.first);
                }
            }
        }
    }
    //Prints the players name and the list of games
    if(vpgames.size()==0){
        std::cout<<"Error: Player could not be found."<<std::endl;
    }else{
    std::cout<<"Player "<<pname<<" plays the following games:"<<std::endl;
    Aprint(vpgames);
    }

}

void prntgame(std::map<std::string,std::map<std::string, int>> gdata, std::string gname){

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
                //if the name is already in the list in the key points
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
    else{
    std::cout<<"Error: Invalid input"<<std::endl;
    }


}


bool inputloop(std::set<std::string>& xgames, std::map<std::string,std::map<std::string, int>>& gdata){
    //ask for input and use split on it to get the command as a single entity
    std::string cmnd ="";
    std::cout<<"games> ";
    getline(std::cin,cmnd);
    std::vector<std::string> cmndv = ssplit(cmnd);
    cmnd = cmndv.at(0);
    std::transform(cmnd.begin(), cmnd.end(), cmnd.begin(), ::toupper);
    //command quit ends the loop and program
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
    else if(cmnd=="PLAYER"){
        player(gdata,cmndv.at(1));
    }
    else{
        std::cout<<"Error: Invalid input"<<std::endl;
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
