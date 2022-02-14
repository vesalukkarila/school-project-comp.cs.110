#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC


          if (s.length() == 1)
                  return true;
          else
          {
              char& eka = s.at(0);
              char& vika = s.at(s.length()-1);
              if (eka == vika)
              {
                  s.erase(0, 1);
                  s.erase(s.length()-1, 1);
                  return palindrome_recursive(s);
              }
              else
                  return false;

          }


}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
