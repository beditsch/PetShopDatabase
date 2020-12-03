//
//  Animal.cpp
//  PetShop
//
//  Created by Marcin Badach on 31/10/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "Animal.hpp"


int Animal::howMany = 0;


Animal::Animal(Animal::Species speciesArg, Animal::Sex sexArg, int ageArg, double priceArg, double costArg) : Product(speciesArg, priceArg, costArg) {
    productType = zwierze;
    
    if (sexArg == male)
        sex = male;
    else if (sexArg == female)
        sex = female;
    else {
        sex = male;
        std::cout << "Błędna płeć. Wartość ustawiona na \"osobnik męski\"." << std::endl;
    }
    
    if (ageArg >= 0)
        age = ageArg;
    else {
        age = 1;
        std::cout << "Błędny wiek. Wartość ustawiona na 1." << std::endl;
    }
    
    lastFeedDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    
    howMany++;
#ifdef _DEBUG
    std::cout << "Konstuktor zwierzęcia wywołany." << std::endl;
#endif
}


Animal::~Animal() {
    howMany--;
#ifdef _DEBUG
    std::cout << "Dekonstuktor zwierzęcia wywołany." << std::endl;
#endif
}

int Animal::returnHowMany () {
    return howMany;
}

int Animal::returnAge() {
    return age;
}



void Animal::operator=(PetFood & pf) {
    if (pf.returnStockNumber() <= 0) {
        std::cout << "Brak pokarmu na stanie." << std::endl;
        return;
    }
    if (static_cast<int>(species) !=  pf.returnSpecies()) {
        std::cout << "Pokarm przeznaczony dla innego gatunku." << std::endl;
        return;
    }
    if (pf.returnMinAge() > age) {
        std::cout << "Zwierze za młode na ten pokarm." << std::endl;
        return;
    }
    if (pf.returnMaxAge() < age) {
        std::cout << "Zwierze za stare na ten pokarm." << std::endl;
        return;
    }
    
    lastFeedDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    pf.changeStock(pf.returnStockNumber() - 1);
    std::cout << "Zwierze nakarmiono." << std::endl;
}

std::string Animal::returnSexString() {
    std::string sexString;
    switch (sex) {
        case 0:
            sexString = "samiec";
            break;
        case 1:
            sexString = "samica";
            break;
        default:
            sexString = "";
            break;
    }
    return sexString;
}


std::ostream& operator<< (std::ostream& os, Animal& anim) {
    os << std::fixed;
    os << std::setprecision(2);
    anim.typeToOStream(os);
    anim.speciesToOStream(os);
    anim.sexToOStream(os);
    anim.ageToOStream(os);
    anim.priceToOStream(os);
    anim.costToOStream(os);
    os << "DATA KARMIENIA: " << std::ctime(&(anim.lastFeedDate));
    return os;
}

bool Animal::decideIfDiscount() {
    if (age >= 5 && price > cost) {
        price = cost + 0.5*(price - cost);
        return true;
    }
    return false;
}

std::ostream& Animal::animalToOStream(std::ostream& os) {
    os << std::fixed;
    os << std::setprecision(2);
    typeToOStream(os);
    speciesToOStream(os);
    sexToOStream(os);
    ageToOStream(os);
    priceToOStream(os);
    costToOStream(os);
    os << "DATA KARMIENIA: " << lastFeedDate;
    os << std::endl;
    return os;
}





std::ostream& Animal::coutReceiptFormat(std::ostream& os) {
    os << std::fixed;
    os << std::setprecision(2);
    coutReceiptFormat_TypeSpecies(os);
    os << std::string(20, ' ') << std::string(10, '-') << std::string(20, ' ') << "|";
    coutReceiptFormat_Price(os);
    return os;
}

std::ostream& Animal::ageToOStream(std::ostream& os) {
    os << "WIEK: " << age << std::string(complementIntegerToNCharacters(age, 4), ' ');
    return os;
}

std::ostream& Animal::sexToOStream(std::ostream& os) {
    os << "PLEC: " << returnSexString() << std::string(15 - returnSexString().length(), ' ');
    return os;
}

std::istream& Animal::sexFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 15);
    shortenString(temp, 0);
    if (temp == "samiec") {
        sex = Animal::male;
    }
    else if (temp == "samica") {
        sex = Animal::female;
    }
    return is;
}
std::istream& Animal::ageFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 4);
    shortenString(temp, 0);
    age = std::stoi(temp);
    return is;
}
std::istream& Animal::lastFeedDateFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 10);
    shortenString(temp, 0);
    lastFeedDate = static_cast<time_t>((std::stoi(temp)));
    return is;
}
std::istream& operator>>(std::istream& is, Animal& pt) {
    //zjadanie "GATUNEK: "
    createNLengthString(is, 9);
    pt.speciesFromIStream(is);
    createNLengthString(is, 6);
    pt.sexFromIStream(is);
    createNLengthString(is, 6);
    pt.ageFromIStream(is);
    createNLengthString(is, 6);
    pt.priceFromIStream(is);
    createNLengthString(is, 7);
    pt.costFromIStream(is);
    createNLengthString(is, 16);
    pt.lastFeedDateFromIStream(is);
    //zjadanie znaku nowej linii
    createNLengthString(is, 1);
    return is;
}



void Animal::userUpdateSex() {
    std::cout << "Podaj płeć:" << std::endl;
    std::string newSex;
    std::getline(std::cin, newSex);
    if (newSex == "samiec") {
        sex = Animal::male;
    }
    else if (newSex == "samica") {
        sex = Animal::female;
    }
    else {
        std::cout << "Podałeś błędną płeć." << std::endl;
        userUpdateSex();
    }
}

void Animal::userUpdateAge() {
    std::cout << "Podaj wiek:" << std::endl;
    std::string newAge;
    std::getline(std::cin, newAge);
    if (is_number(newAge) && (newAge.length() <= 3)) {
        int nA = std::stoi(newAge);
        age = nA;
    }
    else {
        std::cout << "Podałeś błędny wiek." << std::endl;
        userUpdateAge();
    }
}





std::ostream& Animal::productToOstreamEncyclopedia (std::ostream & os) {
    os << std::fixed;
    os << std::setprecision(2);
    typeToOStream(os);
    speciesToOStream(os);
    sexToOStream(os);
    ageToOStream(os);
    priceToOStream(os);
    costToOStream(os);
    os << "DATA KARMIENIA: " << std::ctime(&(lastFeedDate));
    return os;
}
