//
//  PetFood.cpp
//  PetShop
//
//  Created by Marcin Badach on 31/10/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "PetFood.hpp"


PetFood::PetFood(int minAgeArg, int maxAgeArg, double priceArg, double costArg, int stockNumberArg, Species speciesArg, std::string manufacturerArg) : PetToy(minAgeArg, priceArg, costArg, speciesArg, stockNumberArg, manufacturerArg) {
    productType = pokarm;
    
    if (maxAgeArg >= 0 && maxAgeArg >= minAgeArg)
        maxAge = maxAgeArg;
    else {
        maxAge = minAge;
        std::cout << "Błędny wiek maksymalny karmionego zwierzęcia. Wartość ustawiona na równą wiekowi minimalnemu." << std::endl;
    }
    

    
#ifdef _DEBUG
    std::cout << "Konstuktor pokarmu wywołany." << std::endl;
#endif
}

PetFood::~PetFood () {
#ifdef _DEBUG
    std::cout << "Dekonstuktor pokarmu wywołany." << std::endl;
#endif
}



int PetFood::returnMaxAge() {
    return maxAge;
}





std::ostream& operator<< (std::ostream& os, PetFood& pf) {
    os << std::fixed;
    os << std::setprecision(2);
    pf.typeToOStream(os);
    pf.speciesToOStream(os);
    pf.minAgeToOStream(os);
    pf.maxAgeToOStream(os);
    pf.manufacturerToOStream(os);
    pf.stockNumberToOStream(os);
    pf.priceToOStream(os);
    pf.costToOStream(os);
    os << std::endl;
    return os;
}


bool PetFood::decideIfDiscount() {
    if ((maxAge - minAge) <=2) {
        return PetToy::decideIfDiscount();
    }
    return false;
}

std::ostream& PetFood::maxAgeToOStream(std::ostream& os) {
    os << "WIEK MAKSYMALNY: " << maxAge << std::string(complementIntegerToNCharacters(maxAge, 4), ' ');
    return os;
}
std::istream& PetFood::maxAgeFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 4);
    shortenString(temp, 0);
    maxAge = std::stoi(temp);
    return is;
}
std::istream& operator>>(std::istream& is, PetFood& pf) {
    //zjadanie "GATUNEK: "
    createNLengthString(is, 9);
    pf.speciesFromIStream(is);
    createNLengthString(is, 16);
    pf.minAgeFromIStream(is);
    createNLengthString(is, 17);
    pf.maxAgeFromIStream(is);
    createNLengthString(is, 11);
    pf.manufacturerFromIStream(is);
    createNLengthString(is, 14);
    pf.stockNumberFromIStream(is);
    createNLengthString(is, 6);
    pf.priceFromIStream(is);
    createNLengthString(is, 7);
    pf.costFromIStream(is);
    //zjadanie znaku nowej linii
    createNLengthString(is, 1);
    return is;
}


void PetFood::userUpdateMaxAge() {
    std::cout << "Podaj maksymalny wiek:" << std::endl;
    std::string newAge;
    std::getline(std::cin, newAge);
    if (is_number(newAge) && (newAge.length() <= 3)) {
        int nA = std::stoi(newAge);
        if (nA >= minAge) {
        maxAge = nA;
        }
        else {
            std::cout << "Podałeś błędny maksymalny wiek." << std::endl;
            userUpdateMaxAge();
        }
    }
    else {
        std::cout << "Podałeś błędny maksymalny wiek." << std::endl;
        userUpdateMaxAge();
    }
}



std::ostream& PetFood::productToOstreamEncyclopedia (std::ostream & os) {
    os << std::fixed;
    os << std::setprecision(2);
    typeToOStream(os);
    speciesToOStream(os);
    minAgeToOStream(os);
    maxAgeToOStream(os);
    manufacturerToOStream(os);
    stockNumberToOStream(os);
    priceToOStream(os);
    costToOStream(os);
    os << std::endl;
    return os;
}
