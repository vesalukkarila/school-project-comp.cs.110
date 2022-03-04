#include "queue.hh"
#include <iostream>

using namespace std;

int main()
{
    const unsigned int VEHICLES_PER_GREEN_PERIOD = 3;
    Queue q(VEHICLES_PER_GREEN_PERIOD);             //luokan queue rakentaja luo olion q, parametrilla 3
    cout << "Current cycle is " << VEHICLES_PER_GREEN_PERIOD
         << ", i.e. at most "
         << VEHICLES_PER_GREEN_PERIOD <<
         " vehicles can pass during the same green period" << endl;

    while(true) {
        cout << "(a)dd, (p)rint, (s)witch light, (r)eset cycle, (q)uit: ";
        string choice = "";
        cin >> choice;
        if ( choice == "a" ) {                  //valinta a, kysytään regnumero parametriksi ja q-olio kutsuu enqueue-metodia
            cout << "  Input a register number: ";
            string reg = "";
            cin >> reg;
            q.enqueue(reg);
        } else if ( choice == "p" ) {           //valinta p, q-olio kutsuu print-metodia, ilman parametria
            q.print();
        } else if ( choice == "s" ) {           //valinta s, q-olio kutsuu switch_light-metodia, ilman parametria
            q.switch_light();
        } else if ( choice == "r" ) {           //valinta r, kysyy uutta lukua sykliksi (min.1), q-olio kutsuu reset_cycle tällä param.
            cout << "  Input a new amount for cycle: ";
            unsigned int cycle = 0;
            cin >> cycle;
            // Ensuring that the cycle is not too small
            if(cycle < 1) {
                cout << "Too small value, using 1 instead" << endl;
                cycle = 1;
            }
            q.reset_cycle(cycle);
        } else if ( choice == "q" ) {
            break;
        } else {
            cout << "An unknown command" << endl;
        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}
