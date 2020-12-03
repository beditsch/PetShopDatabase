//
//  Product.cpp
//  PetShop
//
//  Created by Marcin Badach on 09/12/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "Product.hpp"

int Product::howMany = 0;


Product::Product(Product::Species speciesArg, double priceArg, double costArg) {
    if (speciesArg <= 7 && speciesArg >= 0)
        species = speciesArg;
    else {
        species = chomik;
        std::cout << "Błędny gatunek zwierzęcia. Wartość ustawiona na \"chomik\"." << std::endl;
    }
    
    if (priceArg >= 0.0)
        price = priceArg;
    else {
        std::cout << "Błędna cena. Wartość ustawiona na 10.0." << std::endl;
    }
    
    if (costArg >= 0.0)
        cost = costArg;
    else {
        std::cout << "Błędny koszt. Wartość ustawiona na 10.0." << std::endl;
        cost = 10.0;
    }
    howMany++;
#ifdef _DEBUG
    std::cout << "Konstuktor zwierzęcia wywołany." << std::endl;
#endif
}


Product::~Product() {
    howMany--;
}


int Product::returnHowMany () {
    return howMany;
}


double Product::returnPrice() {
    return price;
}

double Product::returnCost() {
    return cost;
}

int Product::returnSpecies() {
    return static_cast<int>(species);
}

std::string Product::returnSpeciesString() {
    std::string sp;
    switch (species) {
        case 0:
            sp = "chomik";
            break;
        case 1:
            sp = "kanarek";
            break;
        case 2:
            sp = "krolik";
            break;
        case 3:
            sp = "mysz";
            break;
        case 4:
            sp = "pajak";
            break;
        case 5:
            sp = "papuga";
            break;
        case 6:
            sp = "rybka";
            break;
        case 7:
            sp = "snake";
            break;
        default:
            sp = "";
            break;
    }
    return sp;
}


std::ostream& operator<< (std::ostream& os, Product& pr) {
    os << std::fixed;
    os << std::setprecision(2);
    os << "CENA: " << pr.price << "   ";
    os << "KOSZT: " << pr.cost << std::endl;
    return os;
}



int Product::returnProductType() {
    return static_cast<int>(productType);
}

std::string Product::returnProductTypeString() {
    std::string pt;
    switch (productType) {
        case 0:
            pt = "zwierze";
            break;
        case 1:
            pt = "zabawka";
            break;
        case 2:
            pt = "pokarm";
            break;
        default:
            pt = "zwierze";
            break;
    }
    return pt;
}


std::ostream& Product::coutReceiptFormat_TypeSpecies(std::ostream& os) {
    os << std::fixed;
    os << std::setprecision(2);
    //wyświetlanie typu produktu
    os << std::string((15 - (returnProductTypeString().length())), ' ') << returnProductTypeString() << "|";
    //wyświetlanie gatunku
    os << std::string((20 - (returnSpeciesString().length())), ' ') << returnSpeciesString() << "|";
    return os;
}

std::ostream& Product::coutReceiptFormat_Price(std::ostream& os) {
    os <<  std::string(7 - 2 - (floor(log10(price)) + 1), ' ') << price << std::endl;
    return os;
}


std::ostream& Product::speciesToOStream(std::ostream& os) {
    os << "GATUNEK: " << returnSpeciesString() << std::string((16 - (returnSpeciesString().length())), ' ');
    return os;
}
std::ostream& Product::costToOStream(std::ostream& os) {
    os << std::fixed;
    os << std::setprecision(2);
    os << "KOSZT: " << cost << std::string(complementDoubleToNCharacters(cost, 8), ' ');
    return os;
}
std::ostream& Product::priceToOStream(std::ostream& os) {
    os << std::fixed;
    os << std::setprecision(2);
    os << "CENA: " << price << std::string(complementDoubleToNCharacters(price, 9), ' ');
    return os;
}
std::ostream& Product::typeToOStream(std::ostream& os) {
    os << "TYP: " << returnProductTypeString() << std::string(15 - returnProductTypeString().length(), ' ');
    return os;
}

std::istream& Product::speciesFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 16);
    shortenString(temp, 0);
    if (temp == "chomik") {
        species = Product::chomik;
    }
    else if (temp == "kanarek") {
        species = Product::kanarek;
    }
    else if (temp == "krolik") {
        species = Product::krolik;
    }
    else if (temp == "mysz") {
        species = Product::mysz;
    }
    else if (temp == "pajak") {
        species = Product::pajak;
    }
    else if (temp == "papuga") {
        species = Product::papuga;
    }
    else if (temp == "rybka") {
        species = Product::rybka;
    }
    else if (temp == "snake") {
        species = Product::snake;
    }
    return is;
}

std::istream& Product::priceFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 9);
    shortenString(temp, 0);
    price = std::stod(temp);
    return is;
}
std::istream& Product::costFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 8);
    shortenString(temp, 0);
    cost = std::stod(temp);
    return is;
}

void Product::userUpdateSpecies() {
    std::cout << "Podaj gatunek:" << std::endl;
    std::string newSpecies;
    std::getline(std::cin, newSpecies);
    if (newSpecies == "chomik") {
        species = Product::chomik;
    }
    else if (newSpecies == "kanarek") {
        species = Product::kanarek;
    }
    else if (newSpecies == "krolik") {
        species = Product::krolik;
    }
    else if (newSpecies == "mysz") {
        species = Product::mysz;
    }
    else if (newSpecies == "pajak") {
        species = Product::pajak;
    }
    else if (newSpecies == "papuga") {
        species = Product::papuga;
    }
    else if (newSpecies == "rybka") {
        species = Product::rybka;
    }
    else if (newSpecies == "snake") {
        species = Product::snake;
    }
    else {
        std::cout << "Podałeś błędny gatunek." << std::endl;
        userUpdateSpecies();
    }
}

void Product::userUpdatePrice() {
    std::cout << "Podaj cenę:" << std::endl;
    std::string newPrice;
    std::getline(std::cin, newPrice);
    if (is_double(newPrice)) {
        if (std::stod(newPrice) < 0 || std::stod(newPrice) >= 10000) {
            std::cout << "Podałeś błędną cenę." << std::endl;
            userUpdatePrice();
        }
        else {
            double nP = std::stod(newPrice);
            price = nP;
        }
    }
    else {
        std::cout << "Podałeś błędną cenę." << std::endl;
        userUpdatePrice();
    }
}

void Product::userUpdateCost() {
    std::cout << "Podaj koszt:" << std::endl;
    std::string newCost;
    std::getline(std::cin, newCost);
    if (is_double(newCost)) {
        if (std::stod(newCost) < 0) {
            std::cout << "Podałeś błędny koszt." << std::endl;
            userUpdateCost();
        }
        else {
            double nC = std::stod(newCost);
            cost = nC;
        }
    }
    else {
        std::cout << "Podałeś błędny koszt." << std::endl;
        userUpdateCost();
    }
}
