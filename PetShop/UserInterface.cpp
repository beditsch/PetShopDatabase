//
//  UserInterface.cpp
//  PetShop
//
//  Created by Marcin Badach on 17/12/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "UserInterface.hpp"



void printMENU () {
    std::cout << "\nWybierz czynność, którą chcesz przeprowadzić. Naciśnij odpowiedni klawisz:" << std::endl;
    std::cout << "a - modyfikuj dane sklepu              b - nowa transakcja               c - sprzedaj produkt" << std::endl;
    std::cout << "d - nakarm zwierzaka                   e - uzupełnij zapas pokarmu       f - uzupełnij zapas zabawki" << std::endl;
    std::cout << "g - dokup produkt                      h - przeceń produkty" << std::endl;
    std::cout << "k - koniec" << std::endl;
}

void printAddMENU () {
    std::cout << "\nWybierz produkt, który chcesz dodać. Naciśnij odpowiedni klawisz:" << std::endl;
    std::cout << "a - zwierzę              b - zabawkę               c - pokarm" << std::endl;
    std::cout << "k - koniec" << std::endl;
}

void printSellMENU() {
    std::cout << "\nWybierz produkt, który chcesz sprzedać. Naciśnij odpowiedni klawisz:" << std::endl;
    std::cout << "a - zwierzę              b - zabawkę               c - pokarm" << std::endl;
    std::cout << "k - koniec" << std::endl;
}



int decideWhatToDoSellMENU (PetShop& ps){
    printSellMENU();
    std::string waste;
    char c = std::cin.get();
    std::getline(std::cin, waste);
    
    if (c == 'a') {
        ps += ps.returnAnimal(ps.userChooseAnimal() - 1);
        return 1;
    }
    else if (c == 'b') {
        ps += ps.returnPetToy(ps.userChoosePetToy() - 1);
        return 1;
    }
    else if (c == 'c') {
        ps += ps.returnPetFood(ps.userChoosePetFood() - 1);
        return 1;
    }
    else if (c == 'k') {
        return 0;
    }
    else {
        std::cout << "Wprowadziłeś błędne dane, wprowadź poprawne." << std::endl;
        return 2;
    }
    return 2;
}

int decideWhatToDoAddMENU (PetShop& ps){
    printAddMENU();
    std::string waste;
    char c = std::cin.get();
    std::getline(std::cin, waste);

    if (c == 'a') {
        ps.userAddAnimal();
        return 1;
    }
    else if (c == 'b') {
        ps.userAddPetToy();
        return 1;
    }
    else if (c == 'c') {
        ps.userAddPetFood();
        return 1;
    }
    else if (c == 'k') {
        return 0;
    }
    else {
        std::cout << "Wprowadziłeś błędne dane, wprowadź poprawne." << std::endl;
            return 2;
    }
    return 2;
}

int decideWhatToDoMENU (std::ofstream& destinationFile, PetShop& ps){
    printMENU();
    std::string waste;
    char c = std::cin.get();
    std::getline(std::cin, waste);
    int status1 = 0;
    switch (c) {
        case 'a':
            ps.updateShopDetails();
            return 1;
            break;
        case 'b':
            ++(ps.returnCashRegister());
            return 1;
            break;
        case 'c':
            while ((status1 = decideWhatToDoSellMENU(ps))) {
                if (status1 == 1) {
                    std::cout << "Procedura zakończona!" << std::endl;
                    std::cout << ps;
                }
                continue;
            }
            return 1;
            break;
        case 'd':
            ps.userFeedAnimal();
            return 1;
            break;
        case 'e':
            std::cout << "Wybierz pokarm, którego stan magazynowy chcesz uzupełnić." << std::endl;
            ps + *(ps.returnPetFood(ps.userChoosePetFood() - 1));
            return 1;
            break;
        case 'f':
            std::cout << "Wybierz zabawkę, której stan magazynowy chcesz uzupełnić." << std::endl;
            ps + *(ps.returnPetToy(ps.userChoosePetToy() - 1));
            return 1;
            break;
        case 'g':
            while ((status1 = decideWhatToDoAddMENU(ps))) {
                if (status1 == 1) {
                    std::cout << "Procedura zakończona!" << std::endl;
                    std::cout << ps;
                }
                continue;
            }
        case 'h':
            ps.decideIfDiscount();
            return 1;
            break;
            
        case 'k':
            return 0;
            break;
            
        default:
            std::cout << "Wprowadziłeś błędne dane, wprowadź poprawne." << std::endl;
            return 2;
            break;
    }
    
    return 2;
}











//*******************************
///       ENCYKLOPEDIA
//*******************************
void printEncyclopediaMENU() {
        std::cout << "\nWybierz czynność, którą chcesz przeprowadzić. Naciśnij odpowiedni klawisz:" << std::endl;
        std::cout << "a - dodaj zwierzę              b - dodaj zabawkę              c - dodaj pokarm" << std::endl;
        std::cout << "d - usuń produkt                                              k - koniec" << std::endl;
}


int decideWhatToDoEncyclopediaMENU (ListMB<Product *>& list) {
    printEncyclopediaMENU();
    std::string waste;
    char c = std::cin.get();
    std::getline(std::cin, waste);
    
    if (c == 'a') {
        int num = userNumberInput();
        Animal * anim = new Animal();
        anim -> userUpdateSpecies();
        anim -> userUpdateSex();
        anim -> userUpdateAge();
        anim -> userUpdatePrice();
        anim -> userUpdateCost();
        Product * pr = anim;
        list.pushData(pr, num - 1);
        return 1;
    }
    else if (c == 'b') {
        int num = userNumberInput();
        PetToy * pt = new PetToy();
        pt -> userUpdateSpecies();
        pt -> userUpdateMinAge();
        pt -> userUpdateStockNumber();
        pt -> userUpdatePrice();
        pt -> userUpdateCost();
        pt -> userUpdateManufacturer();
        Product * pr = pt;
        list.pushData(pr, num - 1);
        return 1;
    }
    else if (c == 'c') {
        int num = userNumberInput();
        PetFood * pf = new PetFood();
        pf -> userUpdateSpecies();
        pf -> userUpdateMinAge();
        pf -> userUpdateMaxAge();
        pf -> userUpdateStockNumber();
        pf -> userUpdatePrice();
        pf -> userUpdateCost();
        pf -> userUpdateManufacturer();
        Product * pr = pf;
        list.pushData(pr, num - 1);
        return 1;
    }
    else if (c == 'd') {
        int num = userNumberInput();
        list.popData(num - 1);
        return 1;
    }
    else if (c == 'k') {
        return 0;
    }
    else {
        std::cout << "Wprowadziłeś błędne dane, wprowadź poprawne." << std::endl;
        return 2;
    }
    return 2;
}


int userNumberInput() {
        std::cout << "Podaj numer na liście:" << std::endl;
        std::string uIndex;
        std::getline(std::cin, uIndex);
        if (is_number(uIndex)) {
            int uI = std::stoi(uIndex);
            return uI;
        }
        else {
            std::cout << "Podałeś błędny numer." << std::endl;
            return userNumberInput();
        }
}
