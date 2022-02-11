#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);
    }
}

bool same_values(std::vector<int>&integs)
{
    int muisti = integs.at(0);
    for(int alkio : integs)
    {

        if (alkio == muisti)
        {
            muisti = alkio;
        }
        else
        {
            return false;
        }
    }
    return true;
}


bool is_ordered_non_strict_ascending(std::vector<int>&ints)
{
    int muisti;
    for (int alkio : ints)

        if (alkio >= muisti)
        {
            muisti = alkio;
        }
        else
        {
            return false;
        }
   return true;
}


bool is_arithmetic_series(std::vector<int>&intes)
{
    if (intes.size() > 1)
    {
        int muisti = intes.at(0);

        int erotus = (intes.at(1) - intes.at(0));
        for (int arvo : intes)
        {
            if(arvo - muisti == erotus)
            {
                muisti = arvo;
            }
            else
            {
                if (muisti == intes.at(0))
                {
                    muisti = arvo;
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
     }
    else
    {
        return false;
    }
}


bool is_geometric_series(std::vector<int>&ints)
{
    if(ints.size()> 1)
    {
        int muisti = ints.at(0);
        int kerroin = (ints.at(1) / ints.at(0));

        for(int arvo : ints)
        {
            if( (arvo / muisti) == kerroin)
            {
                muisti = arvo;
            }
            else
            {
                if (muisti == ints.at(0))
                {
                    muisti = arvo;
                }
                else
                {
                    return false;
                }

            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
