#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void save(std::string id1, std::string id2, std::map<std::string,std::vector<std::string>>& names){
    if(names.find(id1)!=names.end()){
        names[id1].push_back(id2);
    }
    else{
        names.insert(std::pair<std::string,std::vector<std::string> >(id1,std::vector<std::string>()));
        names[id1].push_back(id2);
    }
}

//arvoina lista, id ja num
//tarkistaa onko idllä alaideitä jos on niin tulostaa nimen
//rekursioi ja tarkastaa uudestaan alaidtä jnejne..
//mikäli ei ole alaid:tä tulostaa vain id nimen
//ja palaa takaisin ylempään kerrokseen
void print(std::map<std::string,std::vector<std::string>> names, std::string id,int& num){
    std::string merkit(num*2,'.');

    //jos id:llä on alaideitä
    if(names.find(id)!=names.end()){
        //tulostetaan nimi
        std::cout<<merkit<<id<<std::endl;
        //suoritetaan print tutkiminen alaid:lle
        ++num;
        for(unsigned int i=0; i<names.at(id).size();++i){
            print(names, names.at(id).at(i),num);
        }
    }
    //jos id on umpikuja
    else{
        //tulostetaan nimi ja palataan
        std::cout<<merkit<<id<<std::endl;
        --num;
        return;
    }
}

int main()
{
    int nm = 0;
    //vector contains all people that participate
    //used to check their existence
    std::map<std::string,std::vector<std::string>> names ={};


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);
            save(id1,id2,names);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print(names, id, nm);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
