#include <iostream>


int main()
{
    int montako = 0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> montako;

    for (int luku = 1; luku <=montako; ++luku)
    {
        if (luku % 3 == 0)
        {
            std::cout << "zip" << std::endl;
        }

        else
        {
        std::cout << luku << std::endl;
        }
    }


    return 0;
}
