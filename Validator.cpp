#include <iostream>
#include <string>
#include <regex>

using namespace std;

class Validator {

public:
    static bool isBetween(char lower, char upper, char input) {
        //Self explainatory. Returns true if input char is between lower and upper.
        lower = toupper(lower);
        upper = toupper(upper);
        input = toupper(input);

        if (lower <= input && input <= upper)
            return true;
        else
            return false;
    }
    static bool isValidDate(string str) {
        return regex_match(str, regex("([0-9]{1,2})[.]([0-9]{1,2})"));
    }

    static bool isInteger(string str) { //Check whether the input is a int.
        return regex_match(str, regex("[0-9]+"));
    }


};