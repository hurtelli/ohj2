#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <map>
#include <list>


int counter(std::string s, std::vector<std::string> v){
    int count=0;
    for(unsigned int i=0; i<v.size();++i){
        if(s==v.at(i)){
            ++count;
        }
    }
    return count;
}

void vectorize(std::string s, std::vector<std::string> &v){

    std::string temp = "";
    for(int i=0;i<(int)s.length();++i){

        if(s[i]==' '){
            v.push_back(temp);
            temp = "";
        }
        else{
            temp.push_back(s[i]);
        }

    }
    v.push_back(temp);

}

void rowocc(std::string w, std::string filen, std::vector<int>& rovec){
    std::ifstream input(filen);
    int rowcounter=1;
    std::string rivi="";
    while (getline(input,rivi)){
        std::vector<std::string> riviwords ={};     //vektorisoidaan rivi
        vectorize(rivi, riviwords);
        for(unsigned int i=0; i<riviwords.size(); ++i){ //rivin alkioiden läpikäynti
            std::string wrd=riviwords.at(i);
            if(wrd==w){         //jos sana on listassa
                if(rovec.size()>0){
                    if(rovec.at(0) == rowcounter){
                    }
                    else{
                        rovec.push_back(rowcounter);
                    }
                }
                else if(rovec.size()>1){
                    if(rovec.at(1) == rowcounter){
                    }
                    else{
                        rovec.push_back(rowcounter);
                    }
                }
                else if(rovec.size()>=2){
                    if(rovec.at(2) == rowcounter){
                    }
                    else{
                        rovec.push_back(rowcounter);
                    }
                }

                else{
                    rovec.push_back(rowcounter);
                }
            }
        }
        ++rowcounter;
    }
}

void tostring(std::string& s, std::vector<int>rovec){
    for(unsigned int i=0;i<rovec.size();++i){
        int num = rovec.at(i);
        std::string charr = std::to_string(num);
        if(s.length()>=1){
            s+=", ";
            s+=charr;
        }
        else{
            s+=charr;
        }
    }

}

int main(){
    std::string file="";
    std::cout << "Input file: ";
    getline(std::cin, file);

    std::ifstream input(file);
    if(not input){
        std::cout<<"Error! The file "<<file<<" cannot be opened."<<std::endl;
        return EXIT_FAILURE;
    }
    else{

        std::map<std::string, int>used={};  //käytetyt sanat ja määrä
        std::map<std::string, int>used2={}; //käytetyt sanat ja rivi jolla käytetty
        std::string rivi="";
        int rowco =0;
        while(getline(input, rivi)){                        //uusi rivi joka kiekka

            std::vector<std::string> riviwords ={};     //vektorisoidaan rivi
            vectorize(rivi, riviwords);

            for(unsigned int i=0; i<riviwords.size(); ++i){ //rivin alkioiden läpikäynti
                std::string wrd=riviwords.at(i);            //sana on läpikäytävä alkio
                if(used.find(wrd)!=used.end()){         //jos sana on rivillä
                    if(used2[wrd]==rowco){
                    }
                    else{
                        int temp=0;
                        temp+=used[wrd];
                        temp+=counter(wrd,riviwords);
                        used.erase(wrd);
                        used.insert({wrd, temp});
                        used2.erase(wrd);
                        used2.insert({wrd,rowco});
                    }
                }
                else{                                   //jos sana ei ole listassa
                    used.insert({wrd, counter(wrd,riviwords)});
                    used2.insert({wrd,rowco});

                }
            }
            ++rowco;
        }
        input.close();

        for(const auto &wordinfo : used){
            std::string word = wordinfo.first;
            std::vector<int> rovec={};
            rowocc(word, file, rovec);
            std::string whatrows ="";
            tostring(whatrows, rovec);
            std::cout<<wordinfo.first<<" "<<wordinfo.second<<": "<<whatrows<<std::endl;
        }
    }
    return 0;
}
