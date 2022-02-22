#include <iostream>
#include <string>
#include <fstream>

int frequency(std::string s, std::string file_name){

    std::ifstream file;
    std::string word;
    int count = 0;

    try{
        file.open(file_name.c_str());

        while(file>>word){
           if(s.compare(word) == 0) ++count;
        }

        file.close();
    }catch(std::ifstream::failure e){
        //std::cout<<e<<std::endl;
    }
    return count;
}

//===============================================
int main() {

    std::string file_name, word;

    std::cout << "Enter file name.." << '\n';
    std::cout << "Enter word.. " << '\n';

    std::cin >> file_name >> word;

    int count = frequency(word, file_name);

    std::cout << "Occurrences of " << word << ": " << count << std::endl;

    return 0;
}
