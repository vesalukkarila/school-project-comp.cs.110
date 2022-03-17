#include "orienteeringmap.hh"
#include "parser.hh"
#include "cli.hh"
#include "rasti.hh"
#include <iostream>

int main()
{
    //uusi dynaaminen osoittaja nimeltä routes, osoitinkohde OrienteringMap-olio jonka luo dynaamisesi
    std::shared_ptr<OrienteeringMap> routes(new OrienteeringMap);
    std::cout << "Input> ";
    std::string input;
    getline(std::cin, input);
    if( not read_input_from_file(input, routes) )   //dynaaminen osoitin orienteeringmap-olioon
    {
        return EXIT_FAILURE;
    }
    Cli cli(routes);
    while( cli.exec_prompt() ){ }
    return EXIT_SUCCESS;
}


