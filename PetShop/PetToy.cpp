//
//  PetToy.cpp
//  PetShop
//
//  Created by Marcin Badach on 15/12/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "PetToy.hpp"


PetToy::PetToy(int minAgeArg, double priceArg, double costArg, Species speciesArg, int stockNumberArg, std::string manufacturerArg) : Product(speciesArg, priceArg, costArg) {
    productType = zabawka;
    if (minAgeArg >=0)
        minAge = minAgeArg;
    else {
        minAge = 0;
        std::cout << "Błędny wiek minimalny. Wartość ustawiona na 0." << std::endl;
    }
    
    if (stockNumberArg >= 0)
        stockNumber = stockNumberArg;
    else {
        stockNumber = 1;
        std::cout << "Błędna ilość produktu. Wartość ustawiona na 1" << std::endl;
    }
    
    manufacturer = manufacturerArg;
    
#ifdef _DEBUG
    std::cout << "Konstuktor zabawki wywołany." << std::endl;
#endif
}

PetToy::~PetToy () {
#ifdef _DEBUG
    std::cout << "Dekonstuktor zabawki wywołany." << std::endl;
#endif
}



int PetToy::returnMinAge() {
    return minAge;
}



std::ostream& operator<< (std::ostream& os, PetToy& pf) {
    os << std::fixed;
    os << std::setprecision(2);
    pf.typeToOStream(os);
    pf.speciesToOStream(os);
    pf.minAgeToOStream(os);
    pf.manufacturerToOStream(os);
    pf.stockNumberToOStream(os);
    pf.priceToOStream(os);
    pf.costToOStream(os);
    os << std::endl;
    
    return os;
}


bool PetToy::decideIfDiscount() {
    if (stockNumber >= 20 && price > cost) {
        double newPr = cost + 0.5*(price-cost);
        price = newPr;
        return true;
    }
    return false;
}


std::ostream& PetToy::coutReceiptFormat(std::ostream& os){
    os << std::fixed;
    os << std::setprecision(2);
    coutReceiptFormat_TypeSpecies(os);
    os << std::string((50 - manufacturer.length()), ' ') << manufacturer << "|";
    coutReceiptFormat_Price(os);
    return os;
}

int PetToy::returnStockNumber() {
    return stockNumber;
}

void PetToy::changeStock(int n) {
    if (n >= 0)
        stockNumber = n;
    else {
        std::cout << "Podano niewłaściwą wartość. Zmiana nie została dokonana." << std::endl;
    }
}

std::ostream& PetToy::minAgeToOStream(std::ostream& os) {
    int minAgeArg = returnMinAge();
    os << "WIEK MINIMALNY: " << minAgeArg << std::string(complementIntegerToNCharacters(minAgeArg, 4), ' ');
    return os;
}

std::ostream& PetToy::manufacturerToOStream(std::ostream& os) {
    os << "PRODUCENT: " << manufacturer << std::string((49 - (manufacturer.length())), ' ');
    return os;
}

std::ostream& PetToy::stockNumberToOStream(std::ostream& os) {
    os << "LICZBA SZTUK: " << returnStockNumber() << std::string(complementIntegerToNCharacters(returnStockNumber(), 6), ' ');
    return os;
}

std::istream& PetToy::stockNumberFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 6);
    shortenString(temp, 0);
    stockNumber = std::stoi(temp);
    return is;
}
std::istream& PetToy::minAgeFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 4);
    shortenString(temp, 0);
    
    minAge = std::stoi(temp);
    return is;
}
std::istream& PetToy::manufacturerFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 49);
    shortenString(temp, 0);
    manufacturer = temp;
    return is;
}

std::istream& operator>>(std::istream& is, PetToy& pt) {
    //zjadanie "GATUNEK: "
    createNLengthString(is, 9);
    pt.speciesFromIStream(is);
    createNLengthString(is, 16);
    pt.minAgeFromIStream(is);
    createNLengthString(is, 11);
    pt.manufacturerFromIStream(is);
    createNLengthString(is, 14);
    pt.stockNumberFromIStream(is);
    createNLengthString(is, 6);
    pt.priceFromIStream(is);
    createNLengthString(is, 7);
    pt.costFromIStream(is);
    //zjadanie znaku nowej linii
    createNLengthString(is, 1);
    return is;
}

void PetToy::userUpdateMinAge() {
    std::cout << "Podaj minimalny wiek:" << std::endl;
    std::string newAge;
    std::getline(std::cin, newAge);
    if (is_number(newAge) && (newAge.length() <= 3)) {
        int nA = std::stoi(newAge);
        minAge = nA;
    }
    else {
        std::cout << "Podałeś błędny minimalny wiek." << std::endl;
        userUpdateMinAge();
    }
}

void PetToy::userUpdateStockNumber() {
    std::cout << "Podaj stan magazynowy:" << std::endl;
    std::string newStock;
    std::getline(std::cin, newStock);
    if (is_number(newStock) && (stoi(newStock) >= 0)) {
        int nA = std::stoi(newStock);
        stockNumber = nA;
    }
    else {
        std::cout << "Podałeś błędny stan magazynowy." << std::endl;
        userUpdateStockNumber();
    }
}

void PetToy::userUpdateManufacturer() {
    std::cout << "Podaj producenta:" << std::endl;
    std::string newManuf;
    std::getline(std::cin, newManuf);
    while (newManuf == "" || (newManuf.length() >= 1 && newManuf[0] == ' ')) {
        std::cout << "Podaj poprawnie nową nazwę sklepu:" << std::endl;
        getline(std::cin, newManuf);
    }
    manufacturer = newManuf;
}


std::ostream& PetToy::productToOstreamEncyclopedia (std::ostream & os) {
    os << std::fixed;
    os << std::setprecision(2);
    typeToOStream(os);
    speciesToOStream(os);
    minAgeToOStream(os);
    manufacturerToOStream(os);
    stockNumberToOStream(os);
    priceToOStream(os);
    costToOStream(os);
    os << std::endl;
    return os;
}
