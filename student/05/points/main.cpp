#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

int p(std::string str){
    int am = 0;
    for(int i =0; i<(int)str.length();++i){
        if(isdigit(str[i])){
            int num = str[i] -'0';
            am +=num;
        }
    }
    return am;
}

void s(std::string str, std::map<std::string, int>& mp){
    std::string temp = "";

    for(int i=0; i<(int)str.size(); i++){
       if(str[i] != ':'){
          temp += str[i];
      }
        else{
            if(mp.find(temp)!=mp.end()){
                mp.at(temp) += p(str);
            }
            else{
                mp.insert(std::pair<std::string,int>(temp,p(str)));
            }
      }
  }
}

int main()
{
    std::string tiedoston_nimi = "";
        std::cout << "Input file: ";
        getline(std::cin, tiedoston_nimi);

        std::ifstream tied(tiedoston_nimi);
        if (not tied) {
            std::cout << "Error! The file " << tiedoston_nimi << " cannot be opened."<< std::endl;
            return EXIT_FAILURE;
        }
        else{
            std::map<std::string, int> pisteet = {};
            std::cout<<"Final scores:"<<std::endl;
            std::string rivi ="";

            while(getline(tied, rivi)){
                s(rivi, pisteet);
            }
        for ( auto pair : pisteet ) {
            std::cout << pair.first << " "
                 << pair.second << std::endl;
        }
        }


    return 0;
}
