//
//  PetShop.cpp
//  PetShop
//
//  Created by Marcin Badach on 31/10/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//
#include "PetShop.hpp"
#include <iostream>

int PetShop::howMany = 0;


PetShop::PetShop(std::string nameArg, std::string adressArg, std::string taxNumberArg) {
    name = nameArg;
    adress = adressArg;
    if (checkIfDigit(10, taxNumberArg))
        taxNumber = taxNumberArg;
    else {
        taxNumber = "0000000000";
        std::cout << "Błędny numer NIP. Wartość ustawiona na 0000000000." << std::endl;
    }
    cashRegister = CashRegister();
    howMany++;
    
#ifdef _DEBUG
    std::cout << "Konstuktor sklepu wywołany." << std::endl;
#endif
    
}


PetShop::~PetShop() {
    howMany--;
    int n1 = static_cast<int>(animalVector.size());
    int n2 = static_cast<int>(petFoodVector.size());
    int n3 = static_cast<int>(petToyVector.size());
    for (int i = 0; i < n1; i++)
        delete (animalVector[i]);
    for (int j = 0; j < n2; j++)
        delete petFoodVector[j];
    for (int k = 0; k < n3; k++)
        delete petToyVector[k];
    
#ifdef _DEBUG
    std::cout << "Dekonstuktor sklepu wywołany." << std::endl;
#endif
}

int PetShop::returnHowMany() {
    return howMany;
}

CashRegister& PetShop::returnCashRegister () {
    return cashRegister;
}



void PetShop::presentInfo() {
    std::cout << "Oto informacje o sklepie." << std::endl;
    std::cout << "Nazwa sklepu to: " << name << ", a jego adres: " << adress << ". Numer NIP: " << taxNumber << std::endl;
}


void PetShop::updateShopDetails() {
    presentInfo();
    
    std::cout << "Czy chciałbyć podać nową nazwę sklepu? Wpisz T lub N" << std::endl;
    if (checkInput())
        updateName(userUpdateName());
    std::cout << "Czy chciałbyś podać nowy adres sklepu? Wpisz T lub N" << std::endl;
    if (checkInput())
        updateAdress(userUpdateAdress());
    std::cout << "Czy chciałbyś podać nowy numer NIP sklepu? Wpisz T lub N" << std::endl;
    if (checkInput())
        updateTaxNumber(userUpdateTaxNumber());
}


std::string PetShop::userUpdateName() {
    std::cout << "Podaj nową nazwę sklepu:" << std::endl;
    std::string newName;
    getline(std::cin, newName);
    while (newName == "" || (newName.length() >= 1 && newName[0] == ' ')) {
        std::cout << "Podaj poprawnie nową nazwę sklepu:" << std::endl;
        getline(std::cin, newName);
    }
    return newName;
}


std::string PetShop::userUpdateAdress() {
    std::cout << "Podaj nowy adres sklepu:" << std::endl;
    std::string newAdress;
    getline(std::cin, newAdress);
    while (newAdress == "" || (newAdress.length() >= 1 && newAdress[0] == ' ')) {
        std::cout << "Podaj poprawnie nowy adres sklepu:" << std::endl;
        getline(std::cin, newAdress);
    }
    return newAdress;
}



std::string PetShop::userUpdateTaxNumber() {
    std::cout << "Podaj nowy numer NIP sklepu (10 cyfr):" << std::endl;
    std::string newTaxNumber = "";
    getline(std::cin, newTaxNumber);
    while (!checkIfDigit(10, newTaxNumber)) {
        std::cout << "Podaj poprawnie nowy numer NIP sklepu:" << std::endl;
        getline(std::cin, newTaxNumber);
    }
    return newTaxNumber;
}



void PetShop::updateName(std::string newName) {
    if (newName.length() == 0 || newName[0] == '\n' || newName[0] == ' ') {
        std::cout << "Nowa nazwa sklepu błędna." << std::endl;
    }
    else {
        name = newName;
        std::cout << "Nazwa sklepu została zmieniona." << std::endl;
    }
}

void PetShop::updateAdress(std::string newAdress) {
    if (newAdress.length() == 0 || newAdress[0] == '\n' || newAdress[0] == ' ') {
        std::cout << "Nowy adres sklepu błędny." << std::endl;
    }
    else {
        adress = newAdress;
        std::cout << "Adres sklepu został zmieniony." << std::endl;
    }
}


void PetShop::updateTaxNumber(std::string newTaxNumber) {
    if (newTaxNumber.length() != 10 || !checkIfDigit(10, newTaxNumber)) {
        std::cout << "Nowy numer NIP sklepu błędny." << std::endl;
    }
    else {
        taxNumber = newTaxNumber;
        std::cout << "Numer NIP sklepu został zmieniony." << std::endl;
    }
}


template <typename T>
void PetShop::restockProduct(T& prod) {
    int num = prod.returnStockNumber();
    double cost = prod.returnCost();
    if (num >= 25) {
        std::cout << "Produktu jest pod dostatkiem. Uzupełnienie zapasu niepotrzebne." << std::endl;
        return;
    }
    else if (cost * (25-num) <= cashRegister.returnCash()) {
        double totalC = (cost * (25-num));
        std::cout << "Zapasy uzupełnione." << std::endl;
        cashRegister.spendCash(totalC);
        prod.changeStock(25);
        return;
    }
    else {
        int howMany = static_cast<int>(cashRegister.returnCash() / cost);
        double totalC2 = howMany * cost;
        cashRegister.spendCash(totalC2);
        prod.changeStock(prod.returnStockNumber() + howMany);
        std::cout << "Nie starczyło pieniędzy. Zakupiono " << howMany << " sztuk/i produktu. Na stanie: " << prod.returnStockNumber() << "sztuk/i produktu." << std::endl;
        return;
    }
}



void PetShop::operator+(PetFood& pf) {
    if (petFoodVector.size() == 0) {
        std::cout << "Brak danych żadnego pokarmu w magazynie. Nie można uzupełnić zapasów." << std::endl;
        return;
    }
    else
        restockProduct(pf);
}

void PetShop::operator+(PetToy& pt) {
    if (petToyVector.size() == 0) {
        std::cout << "Brak danych żadnej zabawki w magazynie. Nie można uzupełnić zapasów." << std::endl;
        return;
    }
    else
        restockProduct(pt);
}


PetShop::operator double() {
    double sum = 0.0;
    for (int i = 0; i < animalVector.size(); i++) {
        if (animalVector[i] != nullptr)
            sum += (animalVector[i] -> returnPrice());
    }
    for (int j = 0; j < petFoodVector.size(); j++) {
        if (petFoodVector[j] != nullptr)
            sum += ((petFoodVector[j] -> returnPrice()) * static_cast<double>(petFoodVector[j] -> returnStockNumber()));
    }
    for (int k = 0; k < petToyVector.size(); k++) {
        if (petToyVector[k] != nullptr)
            sum += ((petToyVector[k] -> returnPrice()) * static_cast<double>(petToyVector[k] -> returnStockNumber()));
            }
    sum += cashRegister.returnCash();
    return sum;
}


void PetShop::operator+= (Animal * anim) {
    //sprawdzenie, czy jest paragon w kasie
    if (cashRegister.returnLength() == 0) {
        std::cout << "Brak paragonu. Sprzedaż niemożliwa." << std::endl;
        return;
    }
    //sprawdzenie, czy wskaźnik jest dostępny w sklepie zoo
    bool check = false;
    int animIndex = 0;
    int num = static_cast<int>(animalVector.size());
    for (int i = 0; i < num; i++) {
        if (anim == animalVector[i]) {
            check = true;
            animIndex = i;
        }
    }
    if (!check) {
        std::cout << "Zwierzę nie pochodzi ze sklepu. Sprzedaż niemożliwa." << std::endl;
        return;
    }
    cashRegister.collectCash(anim -> returnPrice());
    cashRegister.productPushBack(anim);
    animalVector.erase(animalVector.begin() + animIndex);
    std::cout << "Zwierzę dodane do paragonu" << std::endl;
}



template <typename T>
void PetShop::addToyOrFoodToReceipt(T * prod) {
    if (prod -> returnStockNumber() <= 0) {
        std::cout << "Brak produktu na magazynie. Sprzedaż niemożliwa." << std::endl;
        return;
    }
    //zmniejszam stan magazynowy
    prod -> changeStock((prod -> returnStockNumber()) - 1);
    //dodaje pieniądze ze sprzedaży do kasy
    cashRegister.collectCash(prod -> returnPrice());
    //alokuje pamiec dla pokarmu na paragonie
    T * temp = new T;
    *temp = *prod;
    temp -> changeStock(1);
    //dodaje pokarm do paragonu
    cashRegister.productPushBack(temp);
    std::cout << "Produkt dodany do paragonu" << std::endl;
}

void PetShop::operator+= (PetFood * pf) {
    //sprawdzenie, czy jest paragon w kasie
    if (cashRegister.returnLength() == 0) {
        std::cout << "Brak paragonu. Sprzedaż niemożliwa." << std::endl;
        return;
    }
    //sprawdzenie, czy wskaźnik jest dostępny w sklepie zoo
    bool check = false;
    int pfIndex = 0;
    int num = static_cast<int>(petFoodVector.size());
    for (int i = 0; i < num; i++) {
        if (pf == petFoodVector[i]) {
            check = true;
            pfIndex = i;
        }
    }
    addToyOrFoodToReceipt(pf);
}

void PetShop::operator+= (PetToy * pt) {
    //sprawdzenie, czy jest paragon w kasie
    if (cashRegister.returnLength() == 0) {
        std::cout << "Brak paragonu. Sprzedaż niemożliwa." << std::endl;
        return;
    }
    //sprawdzenie, czy wskaźnik jest dostępny w sklepie zoo
    bool check = false;
    int ptIndex = 0;
    int num = static_cast<int>(petToyVector.size());
    for (int i = 0; i < num; i++) {
        if (pt == petToyVector[i]) {
            check = true;
            ptIndex = i;
        }
    }
    if (!check) {
        std::cout << "Zabawka nie pochodzi ze sklepu. Sprzedaż niemożliwa." << std::endl;
        return;
    }
    addToyOrFoodToReceipt(pt);
}



std::ostream& operator<< (std::ostream & os, PetShop& ps) {
    os << "Oto informacje o sklepie:" << std::endl;
    ps.nameToOStream(os);
    ps.adressToOStream(os);
    ps.taxNumberToOStream(os);
    os << std::endl;
    
    int n1 = static_cast<int>(ps.animalVector.size());
    int n2 = static_cast<int>(ps.petFoodVector.size());
    int n3 = static_cast<int>(ps.petToyVector.size());
    
    os << "Oto zwierzęta w magazynie sklepu:" << std::endl;
    for (int i = 0; i < n1; i++) {
        os << i+1 << ")" << std::string(complementIntegerToNCharacters(i+1, 3), ' ') << *(ps.animalVector[i]);
    }
    
    os << "Oto pokarm w magazynie sklepu:" << std::endl;
    for (int i = 0; i < n2; i++) {
        os << i+1 << ")" << std::string(complementIntegerToNCharacters(i+1, 3), ' ') << *(ps.petFoodVector[i]);
    }
    
    os << "Oto zabawki w magazynie sklepu:" << std::endl;
    for (int i = 0; i < n3; i++) {
        os << i+1 << ")" << std::string(complementIntegerToNCharacters(i+1, 3), ' ') << *(ps.petToyVector[i]);
    }
    os << ps.cashRegister;
    
    
    return os;
}


void PetShop::addAnimal (Animal::Species spArg, Animal::Sex sexArg, int ageArg, double priceArg, double costArg) {
    if (costArg > cashRegister.returnCash()) {
        std::cout << "Za mało pieniędzy w kasie." << std::endl;
        return;
    }
    Animal * anim = new Animal;
    *anim = Animal(spArg, sexArg, ageArg, priceArg, costArg);
    
    animalVector.push_back(anim);
    cashRegister.spendCash(costArg);
    std::cout << "Zwierzę zakupione do sklepu." << std::endl;
}

void PetShop::addPetFood (int minAgeArg, int maxAgeArg, double priceArg, double costArg, int stockNumberArg, PetFood::Species animalsTypeArg, std::string manufacturerArg) {
    if (costArg * stockNumberArg > cashRegister.returnCash()) {
        std::cout << "Za mało pieniędzy w kasie." << std::endl;
        return;
    }
    PetFood * pf = new PetFood;
    *pf = PetFood(minAgeArg, maxAgeArg, priceArg, costArg, stockNumberArg, animalsTypeArg, manufacturerArg);
    petFoodVector.push_back(pf);
    cashRegister.spendCash(stockNumberArg * costArg);
    std::cout << "Pokarm zakupiony do sklepu." << std::endl;
}

void PetShop::addPetToy (int minAgeArg, double priceArg, double costArg, int stockNumberArg, PetFood::Species animalsTypeArg, std::string manufacturerArg) {
    if (costArg * stockNumberArg > cashRegister.returnCash()) {
        std::cout << "Za mało pieniędzy w kasie." << std::endl;
        return;
    }
    PetToy * pt = new PetToy;
    *pt = PetToy(minAgeArg, priceArg, costArg, animalsTypeArg, stockNumberArg, manufacturerArg);
    petToyVector.push_back(pt);
    cashRegister.spendCash(stockNumberArg * costArg);
    std::cout << "Zabawka zakupiona do sklepu." << std::endl;
}

PetFood * PetShop::returnPetFood (int n) {
    if (petFoodVector.size() == 0) {
        std::cout << "Brak zdefiniowanego pokarmu. Stworzono domyślny." << std::endl;
        PetFood * ptr = new PetFood;
        *ptr = PetFood();
        petFoodVector.push_back(ptr);
        return ptr;
    }
    if ((static_cast<int>(petFoodVector.size()) - 1) < n) {
        std::cout << "Brak pokarmu o takim dużym indeksie. Zwrócono ostatni pokarm." << std::endl;
        return petFoodVector[petFoodVector.size() - 1];
    }
    if (n < 0) {
        std::cout << "Za mały indeks pokarmu. Zwrócono pokarm nr. 0." << std::endl;
        return petFoodVector[0];
    }
    return petFoodVector[n];
}

Animal * PetShop::returnAnimal (int n) {
    if (animalVector.size() == 0) {
        std::cout << "Brak zdefiniowanego zwierzęcia. Stworzono domyślny." << std::endl;
        Animal * ptr = new Animal;
        *ptr = Animal();
        animalVector.push_back(ptr);
        return ptr;
    }
    if ((static_cast<int>(animalVector.size()) - 1) < n) {
        std::cout << "Brak zwierzęcia o takim dużym indeksie. Zwrócono ostatnie zwierzę." << std::endl;
        return animalVector[animalVector.size() - 1];
    }
    if (n < 0) {
        std::cout << "Za mały indeks zwierzęcia. Zwrócono zwierzę nr. 0." << std::endl;
        return animalVector[0];
    }
    return animalVector[n];
}

PetToy * PetShop::returnPetToy (int n) {
    if (petToyVector.size() == 0) {
        std::cout << "Brak zdefiniowanej zabawki. Stworzono domyślną." << std::endl;
        PetToy * ptr = new PetToy;
        *ptr = PetToy();
        petToyVector.push_back(ptr);
        return ptr;
    }
    if ((static_cast<int>(petToyVector.size()) - 1) < n) {
        std::cout << "Brak zabawki o takim dużym indeksie. Zwrócono ostatnią zabawkę." << std::endl;
        return petToyVector[petToyVector.size() - 1];
    }
    if (n < 0) {
        std::cout << "Za mały indeks zabawki. Zwrócono zabawkę nr. 0." << std::endl;
        return petToyVector[0];
    }
    return petToyVector[n];
}


std::ostream& PetShop::nameToOStream(std::ostream& os) {
    os << "NAZWA: " << name << std::string(53 - (name.length()), ' ');
    return os;
}
///metoda przekazująca adres sklepu do obiektu klasy ostream (60 pól)
std::ostream& PetShop::adressToOStream(std::ostream& os) {
    os << "ADRES: " << adress << std::string(53 - (adress.length()), ' ');
    return os;
}
std::ostream& PetShop::taxNumberToOStream(std::ostream& os) {
    os << "NUMER NIP: " << taxNumber << std::string(14 - (taxNumber.length()), ' ');
    return os;
}


std::ostream& PetShop::petShopToOStream(std::ostream& os) {
    os << "Oto informacje o sklepie:" << std::endl;
    nameToOStream(os);
    adressToOStream(os);
    taxNumberToOStream(os);
    os << std::endl;
    
    int n1 = static_cast<int>(animalVector.size());
    int n2 = static_cast<int>(petFoodVector.size());
    int n3 = static_cast<int>(petToyVector.size());
    
    os << "Oto zwierzęta w magazynie sklepu:" << std::endl;
    for (int i = 0; i < n1; i++) {
        animalVector[i] -> animalToOStream(os);
    }
    
    os << "Oto pokarm w magazynie sklepu:" << std::endl;
    for (int i = 0; i < n2; i++) {
        os << *(petFoodVector[i]);
    }
    
    os << "Oto zabawki w magazynie sklepu:" << std::endl;
    for (int i = 0; i < n3; i++) {
        os << *(petToyVector[i]);
    }
    cashRegister.cashRegisterToOStream(os);
    return os;
}

std::istream& PetShop::nameFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 53);
    shortenString(temp, 0);
    name = temp;
    return is;
}
std::istream& PetShop::adressFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 53);
    shortenString(temp, 0);
    adress = temp;
    return is;
}
std::istream& PetShop::taxNumberFromIStream(std::istream& is) {
    std::string temp = createNLengthString(is, 14);
    shortenString(temp, 0);
    taxNumber = temp;
    return is;
}

void PetShop::addAnimalPointer(Animal * ptr) {
    animalVector.push_back(ptr);
}
void PetShop::addPetToyPointer(PetToy * ptr) {
    petToyVector.push_back(ptr);
}
void PetShop::addPetFoodPointer(PetFood * ptr) {
    petFoodVector.push_back(ptr);
}


std::istream& operator>>(std::istream& is, PetShop& ps) {
    std::string waste;
    //zjadam pierwsza linijke
    std::getline(is, waste);
    
    ps.shopInfoFromIStream(is);
    
    //jedzenie entera po linijce z info o sklepi
    createNLengthString(is, 1);
    std::getline(is, waste);
    
    ps.animalsFromIStream(is);
    
    //zjadam linijke opisową
    std::getline(is, waste);
    
    ps.petFoodFromIStream(is);

    std::getline(is, waste);
    
    ps.petToyFromIStream(is);

    //jem input, aby natrafić na gotowke w kasie
    createNLengthString(is, 26);
    is >> ps.cashRegister;
    return is;
}


int PetShop::returnAnimalVectorLength () {
    return static_cast<int>(animalVector.size());
}


int PetShop::returnPetToyVectorLength () {
    return static_cast<int>(petToyVector.size());
}

int PetShop::returnPetFoodVectorLength () {
    return static_cast<int>(petFoodVector.size());
}

std::istream& PetShop::shopInfoFromIStream(std::istream& is) {
    createNLengthString(is, 7);
    this -> nameFromIStream(is);
    createNLengthString(is, 7);
    this -> adressFromIStream(is);
    createNLengthString(is, 11);
    this -> taxNumberFromIStream(is);
    return is;
}

std::istream& PetShop::animalsFromIStream(std::istream& is) {
    while(createNLengthString(is, 1) != "O") {
        createNLengthString(is, 19);
        Animal * ptr = new Animal;
        is >> *ptr;
        this -> addAnimalPointer(ptr);
    }
    return is;
}

std::istream& PetShop::petFoodFromIStream(std::istream& is) {
    while(createNLengthString(is, 1) != "O") {
        createNLengthString(is, 19);
        PetFood * ptr = new PetFood;
        is >> *ptr;
        this -> addPetFoodPointer(ptr);
    }
    return is;
}

std::istream& PetShop::petToyFromIStream(std::istream& is) {
    while(createNLengthString(is, 1) != "G") {
        createNLengthString(is, 19);
        PetToy * ptr = new PetToy;
        is >> *ptr;
        this -> addPetToyPointer(ptr);
    }
    return is;
}

void PetShop::decideIfDiscount() {
    for (int i = 0; i < (this -> returnAnimalVectorLength()); i++) {
        animalVector[i] -> decideIfDiscount();
    }
    for (int i = 0; i < this -> returnPetToyVectorLength(); i++) {
        petToyVector[i] -> decideIfDiscount();
    }
    for (int i = 0; i < this -> returnPetFoodVectorLength(); i++) {
        petFoodVector[i] -> decideIfDiscount();
    }
}



void PetShop::userAddAnimal() {
    addAnimal(Animal::chomik, Animal::male, 1, 10.0, 0.0);
    Animal * anim = returnAnimal((returnAnimalVectorLength() - 1));
    anim -> userUpdateSpecies();
    anim -> userUpdateSex();
    anim -> userUpdateAge();
    anim -> userUpdatePrice();
    anim -> userUpdateCost();
    if ((anim -> returnCost()) > returnCashRegister().returnCash()) {
        std::cout << "Za mało pieniędzy na zakup produktu." << std::endl;
        delete anim;
        animalVector.erase(animalVector.begin() + returnAnimalVectorLength() - 1);
    }
    else {
    returnCashRegister().spendCash(anim -> returnCost());
        std::cout << "Produkt poprawnie dokupiony do sklepu." << std:: endl;
    }
}

void PetShop::userAddPetToy() {
    addPetToy(0, 10.0, 0.0, 1, Product::chomik, "Producent");
    PetToy * pt = returnPetToy((returnPetToyVectorLength() - 1));
    pt -> userUpdateSpecies();
    pt -> userUpdateMinAge();
    pt -> userUpdateStockNumber();
    pt -> userUpdatePrice();
    pt -> userUpdateCost();
    pt -> userUpdateManufacturer();
    if (((pt -> returnCost()) * (pt -> returnStockNumber())) > returnCashRegister().returnCash()) {
        std::cout << "Za mało pieniędzy na zakup produktu." << std::endl;
        delete pt;
        petToyVector.erase(petToyVector.begin() + returnPetToyVectorLength() - 1);
    }
    else {
        returnCashRegister().spendCash((pt -> returnCost()) * (pt -> returnStockNumber()));
        std::cout << "Produkt poprawnie dokupiony do sklepu." << std:: endl;
    }
}


void PetShop::userAddPetFood() {
    addPetFood(0, 10, 10.0, 0.0, 1, Product::chomik, "Producent");
    PetFood * pf = returnPetFood((returnPetFoodVectorLength() - 1));
    pf -> userUpdateSpecies();
    pf -> userUpdateMinAge();
    pf -> userUpdateMaxAge();
    pf -> userUpdateStockNumber();
    pf -> userUpdatePrice();
    pf -> userUpdateCost();
    pf -> userUpdateManufacturer();
    if (((pf -> returnCost()) * (pf -> returnStockNumber())) > returnCashRegister().returnCash()) {
        std::cout << "Za mało pieniędzy na zakup produktu." << std::endl;
        delete pf;
        petFoodVector.erase(petFoodVector.begin() + returnPetFoodVectorLength() - 1);
    }
    else {
        returnCashRegister().spendCash((pf -> returnCost()) * (pf -> returnStockNumber()));
        std::cout << "Produkt poprawnie dokupiony do sklepu." << std:: endl;
    }
}


int PetShop::userChooseAnimal() {
    std::cout << "Podaj numer wybranego zwierzęcia:" << std::endl;
    std::string num;
    std::getline(std::cin, num);
    int nA = 0;
    if (is_number(num)) {
        nA = std::stoi(num);
        if (nA <= 0 || nA > returnAnimalVectorLength()){
            std::cout << "Podałeś błędny numer." << std::endl;
            nA = userChooseAnimal();
        }
            
    }
    else {
        std::cout << "Podałeś błędny numer." << std::endl;
        nA = userChooseAnimal();
    }
    return nA;
}

int PetShop::userChoosePetToy() {
    std::cout << "Podaj numer wybranej zabawki:" << std::endl;
    std::string num;
    std::getline(std::cin, num);
    int nA = 0;
    if (is_number(num)) {
        nA = std::stoi(num);
        if (nA <= 0 || nA > returnPetToyVectorLength()){
            std::cout << "Podałeś błędny numer." << std::endl;
            nA = userChoosePetToy();
        }
        
    }
    else {
        std::cout << "Podałeś błędny numer." << std::endl;
        nA = userChoosePetToy();
    }
    return nA;
}

int PetShop::userChoosePetFood() {
    std::cout << "Podaj numer wybranego pokarmu:" << std::endl;
    std::string num;
    std::getline(std::cin, num);
    int nA = 0;
    if (is_number(num)) {
        nA = std::stoi(num);
        if (nA <= 0 || nA > returnPetFoodVectorLength()){
            std::cout << "Podałeś błędny numer." << std::endl;
            nA = userChoosePetFood();
        }
        
    }
    else {
        std::cout << "Podałeś błędny numer." << std::endl;
        nA = userChoosePetFood();
    }
    return nA;
}


void PetShop::userFeedAnimal() {
    std::cout << "Wybierz zwierzę, które chcesz nakarmić." << std::endl;
    int n1 = userChooseAnimal();
    std::cout << "Wybierz pokarm, którym chcesz nakarmić." << std::endl;
    int n2 = userChoosePetFood();
    
    (*returnAnimal(n1 - 1)) = (*returnPetFood(n2 - 1));
}
