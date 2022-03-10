#include "array_operations.hh"
#include <iostream>
#include <algorithm>

using namespace std;

const int ITEM_NUMBER = 30;

int main() {

    // Declaring an array with 30 elements, which begins with 4 non-zero values,
    // and the rest of the values are zero.
    int array[ITEM_NUMBER] = { 1, 3, 6, 9 };

    // Example on how to apply algorithm library to a C array
    sort(array, array + ITEM_NUMBER);       //sortin lukuvälinä muistipaikka - muistipaikka + 30

    for(int* position = array; position < array + ITEM_NUMBER; ++position){
        cout << *position << " ";   //tässä tulostaa 0 0 0 ...  1 3 6 9
    }
    cout << endl;

    // point a
   // cout << "hui" << endl;
    cout << greatest_v1(array, ITEM_NUMBER) << endl;            //tulostuu 9
   // cout << "jälkeen" << endl;
    cout << greatest_v2(array, array + ITEM_NUMBER) << endl;    //tulostuu 9


    // point b
    int target_array[ITEM_NUMBER];
    copy(array, array + ITEM_NUMBER, target_array);

    for(int* position = target_array; position < target_array + ITEM_NUMBER; ++position){
        cout << *position << " ";           //tulostaa 000001369
    }
    cout << endl;



    // point c
    reverse(array, array + ITEM_NUMBER);

    for(int* position = array; position < array + ITEM_NUMBER; ++position){
        cout << *position << " ";
    }
    cout << endl;


}
