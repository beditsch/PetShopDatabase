//
//  GlobalFunctions.cpp
//  PetShop
//
//  Created by Marcin Badach on 01/11/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "GlobalFunctions.hpp"


bool checkInput () {
    std::string c;
    std::getline(std::cin, c);
    
    while (c.length() != 1 || (c[0] != 'T' && c[0] != 'N')) {
        std::cout << "Podałeś błędny znak. Spróbuj ponownie." << std::endl;
        std::getline(std::cin, c);
    }
    if (c[0] == 'T')
        return true;
    return false;
}

bool checkIfDigit(int numOfDigits, std::string str) {
    if (str.length() != numOfDigits)
        return false;
    for (int i=0; i < numOfDigits; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

bool checkIntLength (int num, int length) {
    int l;
    l = log10(num) + 1;
    if (l == length)
        return true;
    else return false;
}


int complementDoubleToNCharacters (double num, int n) {
    if (num < 1.0)
        return n - 4;
    
    int x = (floor(log10(num)) + 1); //liczba miejsc, którą zajmuje część calkowita
    x += 3; // dodaje kropkę i dwa miejsca po przecinku;
    return n - x;
}

int complementIntegerToNCharacters (int num, int n) {
    if (num == 0)
        return n - 1;
    int x = (floor(log10(num)) + 1);
    return n - x;
}

void shortenString (std::string& str, int n) {
    int length = static_cast<int>(str.length());
    int i = length - 1;
    while (str[i] == ' ' || str[i] == '\n')
        i--;
    //po powyższej pętli i wskazuje indeks ostatniego pola, które nie jest spacją
    str = str.substr(n, i + 1);
}

std::string createNLengthString (std::istream& is, int n) {
    std::string str = "";
    for (int i = 0; i < n; i++)
        str += is.get();
    return str;
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool is_double(const std::string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}




