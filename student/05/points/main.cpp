#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

void s(std::string str, std::map<std::string, int>& mp){
    std::string temp = "";

    for(int i=0; i<(int)str.size(); i++){
      // If cur char is not del, then append it to the cur "word", otherwise
        // you have completed the word, print it, and start a new word.
       if(str[i] != ':'){
          temp += str[i];
      }
        else{
            if(mp.find(temp)!=mp.end()){
                mp.at(temp) += str.at(str.length()-1);
                std::cout<< str.at(str.length()-1)<<"pistettä inee"<<std::endl;
            }
            else{
                mp.insert(std::pair<std::string,int>(temp,str[-1]));
            }
      }
  }
}

int main()
{
    std::string tiedoston_nimi = "";
        std::cout << "Syota tiedoston nimi: ";
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
