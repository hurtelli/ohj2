#include <iostream>
#include <string>
#include <fstream>


int main()
{
    //input file
    std::string infilename = "";
    std::cout<<"Input file: ";
    getline(std::cin,infilename);

    //output file
    std::string outfilename="";
    std::cout<<"Output file: ";
    getline(std::cin,outfilename);

    std::ifstream infile(infilename);
    if(infile){
        std::ofstream outfile(outfilename);
        std::string outext="";
        std::string row="";
        int counter=1;
        while(getline(infile, row)){
            std::cout<<row<<std::endl;
            std::string outrow = "";
            outrow+=std::to_string(counter);
            outrow+=" ";
            outrow+=row;
            outext+=outrow;
            outext+="\n";
            counter+=1;
        }
        infile.close();
        outfile<<outext;
        std::cout<<outext;
        outfile.close();
    }
    else{
        std::cout<<"Error! The file "<<infilename<<" cannot be opened."<<std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
