#include <iostream>
#include <string>
#include <vector>


int split(std::string text, char sep, bool no_empty=false)
{
    std::vector<std::string> parts = {};


    char muisti;
    std::string muistix = "";
    for (char x : text)
    {
        if(x == sep)
        {
            if(muisti==sep)
            {

                parts.push_back(muistix);
            }
            else
            {
                muistix += muisti;
                muisti = x;
            }

        }
        else
        {
            muistix += muisti;
            muisti = x;
        }


    }
    return std::vector<std::string>(parts)
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
