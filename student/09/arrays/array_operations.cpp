#include "array_operations.hh"
#include <memory>

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int size: number of elements to be examined
 * return value: the greatest element of the array
 */
int greatest_v1(int *itemptr, int size)
{
    int suurin = 0;
    for (int* iter = itemptr; iter < itemptr + size; ++iter)
    {
        if (*iter > suurin)
            suurin = *iter;
    }
    return suurin;
}

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int* endptr: pointer to the memory address after the last element of the array
 * return value: the greatest element of the array
 */
int greatest_v2(int *itemptr, int *endptr)
{
    int suurin = 0;         //katoaa olemasta???
    //int* osoitin = itemptr;
    for (int* iter = itemptr; iter < endptr; ++iter)
    {
        if (*iter > suurin)
        {

            suurin = *iter;

        }
    }
    return suurin;        //yritin palauttaa osoittimen osoittaman muistipaikan sisällön jossa suurin arvo on
}

/* Copies the content of the array to another array
 * int* itemptr: pointer to the first array element to be copied
 * int* endptr: pointer to the memory address after the last element of the array to be copied
 * int* targetptr: pointer to the head of the array, to which to copy
 */
void copy(int *itemptr, int *endptr, int *targetptr)
{
    //int laskuri = 0;
    for (int* iter = itemptr; iter < endptr; ++iter)
    {
        *targetptr  = *iter;    //targetpointterin osoittaman muistipaikan sisällöksi kopioidaan iterin osoittaman muistipaikan sisältö
        targetptr += 1;
    }

}

/* Reverses the elements of the array
 * int* leftptr: pointer to the first element of the reversable part
 * int* rightptr: pointer to the next memory address after the reversable part
 */
void reverse(int *leftptr, int *rightptr)
{
    int ero = rightptr - leftptr;
    int* pera = rightptr -1;
    int apu;
    for (int* iter = leftptr; iter < rightptr - ero/2; ++iter)
    {
        apu = *iter;
        *iter = *pera;
        *pera = apu;
        pera -= 1;
    }
}
