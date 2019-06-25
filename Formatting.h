//
// Created by Vishal Singh on 20/06/19.
//
//The below functions have been used to input and format data
#ifndef GOJAK_FORMATTING_H
#define GOJAK_FORMATTING_H
#include <string>
#include <iostream>
#include <algorithm>
using namespace::std;
typedef long long int ll;
std::string trim_left(const std::string& str)
{
    const std::string pattern = " \f\n\r\t\v";
    return str.substr(str.find_first_not_of(pattern));
}

std::string trim_right(const std::string& str)
{
    const std::string pattern = " \f\n\r\t\v";
    return str.substr(0,str.find_last_not_of(pattern) + 1);
}

std::string trim(const std::string& str)
{
    return trim_left(trim_right(str));
}
string input_string()
{
    string source;
    cin>>source;
    //transform(source.begin(), source.end(), source.begin(), ::tolower);
    return trim(source);
}

string format_string(string source)
{
    //transform(source.begin(), source.end(), source.begin(), ::tolower);
    return trim(source);
}

ll convert_to_number(string str)
{
    ll num;
    try{
        num = stoull(str);
    }
        // catch invalid_argument exception.
    catch(const std::invalid_argument){
        num=-1;
        cout<< "Invalid argument" << "\n";
    }
    return num;
}


#endif //GOJAK_FORMATTING_H
