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
    static bool isDouble(string str) { //Check whether the input is a double.
        //[0-9] represents match from 0-9, + represents contains 1 or more (digits 0-9)
        //[.] represents the literal dot
        //()? - () represents capture group, which is captured by ?, 
        //which indicates 0 or 1 that specific capture group.
        //Overall, it represents that number has many digits, 
        //and may or may not have a decimal point.
        //(Negative values are not counted).
        return regex_match(str, regex("[0-9]+([.][0-9]+)?"));
    }


};