#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

bool isValidDouble(const string& s) { // checks if a given string is a valid double
    if (s.empty()) return false; // if the string contains nothing
    size_t i = 0; // initialize index i to 0
    if (s[i] == '+' || s[i] == '-') ++i; // check if the first charcter of string is + or - if so increment the index
    bool hasDigitsBeforeDecimal = false; // initialize variable for tracking if digits appear before the decimal
    bool hasDecimal = false; // initializes variable for tracking if there is a decimal in the string
    bool hasDigitsAfterDecimal = false; // initialize variable for tracking if digits appear after the decimal
    for (; i < s.size(); ++i) { // iterate through string using index i 
        if (isdigit(s[i])) { // checks if current character is a digit
            if (!hasDecimal) hasDigitsBeforeDecimal = true; // if decimal hasn't been encountered yet set hasDigitsBeforeDecimal to true
            else hasDigitsAfterDecimal = true; // decimal has been encountered so set hasDigitsAfterDecimal to true
        } else if (s[i] == '.') { // check if current character is a decimal point
            if (hasDecimal) return false;  // check if this isn't the first decimal point and if so return false
            hasDecimal = true; // decimal has been encountered so set hasDecimal to true
        } else { // character isn't a digit or decimal
            return false; // return false
        } // closes else statement
    } // closes for loop
    if (hasDecimal && !hasDigitsAfterDecimal) return false; // if there aren't any digits after the decimal point return false
    return hasDigitsBeforeDecimal; // return whether or not there were digits before the decimal point
} // closes isValidDouble function


void split(const string& s, string& intPart, string& fracPart) { //split a string at its decimal point
    size_t decimal = s.find('.'); // finds the index of the decimal point
    if (decimal == string::npos) { // checks if a decimal point was found
        intPart = s; // no deciimal was found so there is only and integer part
        fracPart = ""; // set the fraction part to an empty string
    } else { // a decimal was found
        intPart = s.substr(0, decimal); // assign the integer part as the string before the decimal point
        fracPart = s.substr(decimal + 1); // assign the fraction part as the string after the decimal point
    } // closes else statement
} // closes split function


size_t padStrings(string& a, string& b) { // pads doubles with zeros so they are the same length
    string aInt, aFrac, bInt, bFrac; // initialize strings for storing the integer and fraction parts
    split(a, aInt, aFrac); // split string a
    split(b, bInt, bFrac); // split string b
    if (aInt.size() < bInt.size()) // check if a has a shorter integer part
        aInt = string(bInt.size() - aInt.size(), '0') + aInt; // a has a shorter integer part so pad it with zeros
    if (bInt.size() < aInt.size()) // check if b has a shorter integer part
        bInt = string(aInt.size() - bInt.size(), '0') + bInt; // b has a shorter integer part so pad it with zeros
    if (aFrac.size() < bFrac.size()) // check if a has a shorter fraction part
        aFrac += string(bFrac.size() - aFrac.size(), '0'); // a has a shorter fraction part so pad it with zeros
    if (bFrac.size() < aFrac.size()) // check if b has a shorter fraction part
        bFrac += string(aFrac.size() - bFrac.size(), '0'); // b has a shorter fraction part so pad it with zeros
    a = aInt + aFrac; // combine the integer and fraction parts of a
    b = bInt + bFrac; // combine the integer and fraction parts of b
    return max(aFrac.size(), bFrac.size()); // the lenth of the larger fraction part of a and b
} // closes the padStrings function


bool isSmaller(const string& a, const string& b) { // takes two strings that have been padded and returns the larger one
    return a.size() < b.size() || (a.size() == b.size() && a < b); // return true if string a is smaller than string b
} // closes isSmaller function


string addSameSign(const string& a, const string& b) { // adds two strings that have the same sign
    string result; // initialize a result string
    int carry = 0; // initialize a carry value
    for (int i = (int)a.size() - 1; i >= 0; --i) { // iterate through strings a and b
        int sum = (a[i] - '0') + (b[i] - '0') + carry; // calculate the sum of current digits and the previuous carry
        carry = sum / 10; // calculate the carry from the sum
        result += (sum % 10) + '0'; // add the part of the sum that isn't the carry to the result
    } // closes for loop
    if (carry) result += (carry + '0'); // if there is a final carry it is added
    reverse(result.begin(), result.end()); //reverses order of the result because it was built in reverse
    return result; // return the result
} // closes addSameSign function


string addOppositeSign(const string& a, const string& b) { // adds two string that are opposite signs (a - b)
    string result; // initialize a result string
    int borrow = 0; // initialize a borrow value 
    for (int i = (int)a.size() - 1; i >= 0; --i) {
        int digitA = a[i] - '0' - borrow; // initialize digitA and subtract the borrow value
        int digitB = b[i] - '0'; // initialize digitB
        if (digitA < digitB) { // check if digitA is a smaller number
            digitA += 10; // digitA is smaller so borrow ten from next number
            borrow = 1; // add one to borrow
        } else { // digitA is bigger than digitB
            borrow = 0; // no borrow needed
        } // close else statement
        result += (digitA - digitB) + '0'; // subtract the digits and add them to result
    } // closes else statement
    reverse(result.begin(), result.end()); // reverses order of the result because it was built in reverse
    return result; // return the result
} // closes addOppositeSign function


string formatResult(string raw, size_t decimalDigits, bool negative) { //reformats the result by removing the padding and replacing the decimal
    if (decimalDigits > 0 && raw.size() > decimalDigits) // checks if there was a decimal previously
        raw.insert(raw.size() - decimalDigits, "."); // inserts decimal in correct spot
    else if (decimalDigits > 0) // result isn't as long as it needs to be to insert the decimal point
        raw = "0." + string(decimalDigits - raw.size(), '0') + raw; // reformats results that lost leading zeros and inserts decimal point
    else  // result didn't have a decimal at the start
        raw += ".0"; // add decimal point
    while (raw.size() > 1 && raw[0] == '0' && raw[1] != '.') raw.erase(0, 1); // delete leading zeros
    if (raw.find('.') != string::npos) { // check that there is a decimal point
        while (raw.back() == '0') raw.pop_back(); // deletes trailing zeros
        if (raw.back() == '.') raw.pop_back(); // adds a zero after the decimal point
    } // closes if statement
    if (raw.empty() || raw == ".") raw = "0.0"; // default result for no string or only a decimal point
    if (raw[0] == '.') raw = "0" + raw; // adds a zero if only decimal numbers exist
    if (raw == "0") raw = "0.0"; // adds a decimal point and zero if the result is just zero
    return negative ? "-" + raw : raw; // returns the formatted result
} // closes formatResult function


string addWithFixedOperand(string input) { // adds in the input number with -123.456
    bool negInput = false; // initialize variable to track if the input is negative
    if (input[0] == '-') { // check if the input string is negative
        negInput = true; // set negInput to true
        input = input.substr(1); // remove the negative sign
    } else if (input[0] == '+') { // check if the input string has a positive sign
        input = input.substr(1); // remove the positive sign
    } // closes else it statement
    string fixed = "123.456"; // initialize the fixed number to add
    size_t decimalDigits = padStrings(input, fixed); // pad the input number and fixed number
    string result; // initialize a result string
    bool resultNegative; // initialize a varialbe to track if the result is negative
    if (!negInput) { // check if input was negative
        if (isSmaller(input, fixed)) { // input was negative so check which one is smaller
            result = addOppositeSign(fixed, input); // subtract in the right order
            resultNegative = true; // set resultNegative to true
        } else { // fixed is smaller so change order
            result = addOppositeSign(input, fixed); // subtract in the right order
            resultNegative = false; // set resultNegative to true
        } // closes else statement
    } else { // input wass negative
        result = addSameSign(input, fixed); // perform addition and store the result in result
        resultNegative = true; // set resultNegative to true because same sign addition with -123.456 gives a negative
    } // closes else statement
    return formatResult(result, decimalDigits, resultNegative); // return a formatted string as the result
} // closes addWithFixedOperand


void processFile(const string& filename) { // takes an input file and calculates double sums using it
    ifstream file(filename); // open input file
    if (!file) { // check if input file could be opened
        cout << "Error: could not open file.\n"; // input file couldn't be opened
        return; // return
    } // closes if statement
    string inputDouble; // initialize a string for storing the input double
    while (file >> inputDouble) { // iterate through the files doubles 
        if (!isValidDouble(inputDouble)) { // check if the current double is a valid double
            cout << "Invalid number: " << inputDouble << endl; // it wasn't a valid double
            continue; // move to the next loop
        } // closes if statement
        string result = addWithFixedOperand(inputDouble); // perform addition with -123.456
        cout << inputDouble << " + (-123.456) = " << result << endl; // print the result of the addition
    } // closes while loop
} // closes processFile function


int main() { // main function
    string filename; //initialize a string to hold the file name
    cout << "Enter input filename: "; // print statement asking for filename
    getline(cin, filename); // get file name from user
    processFile(filename); // pass file name to processFile
    return 0; // return 0
} // closes main function