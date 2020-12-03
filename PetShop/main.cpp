//
//  main.cpp
//  PetShop
//
//  Created by Marcin Badach on 31/10/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//



#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include "PetShop.hpp"
#include "PetFood.hpp"
#include "Animal.hpp"
#include "Receipt.hpp"
#include "CashRegister.hpp"
#include "PetToy.hpp"
#include <fstream>
#include "UserInterface.hpp"
#include "ListMB.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>



void test1 ();
void test2();

int main(int argc, const char * argv[]) {
//    ListMB<int> l1;
//    l1.pushBack(2);
//    l1.pushBack(5);
//    sleep(3);
//    l1.pushBack(6);
//    l1.pushData(3, 1);

//    std::cout << std::endl << l1.length;
//    std::cout << l1[1].timeElapsed.count();
//    l1.coutLast();
    
//    std::vector<int> intV;
//    intV.push_back(3);
//    intV.push_back(4);
//    std::cout << intV[4];
    
    
    std::cout << "ENCYKLOPEDIA PRODUKTÓW SKLEPU ZOOLOGICZNEGO" << std::endl;
    
    ListMB<Product*> list;
    int status = 0;
    int lngth = 0;
    while ( (status = decideWhatToDoEncyclopediaMENU(list)) ) {
        if (status == 1) {
            std::cout << "Procedura zakończona!" << std::endl;
            lngth = list.getLength();
            std::cout << "Produkty w encyklopedii:" << std::endl;
            for (int i = 0; i < lngth; i++) {
                std::cout << i+1 << "." << std::string(complementIntegerToNCharacters(i+1, 3), ' ');
                list[i].getNodeData() -> productToOstreamEncyclopedia(std::cout);
                std::cout << "    " << "CZAS UTWORZENIA [ms]: " << list[i].getTimeElapsed().count() << std::endl;
            }
        }
        continue;
    }
    lngth = list.getLength();
    for (int i = 0; i < lngth; i++)
        delete list[i].getNodeData();


    
    
    
    
    
    
    
    
    
    
//INTERAKTYWNY SKLEP ZOO
//    std::ifstream myfile;
//    PetShop ps;
//    myfile.open("wynik.txt");
//    if (createNLengthString(myfile, 1) == "O") {
//        myfile >> ps;
//        myfile.close();
//    }
//    else
//        myfile.close();
//
//    std::ofstream myfile2 ("wynik.txt");
//
//    std::cout << ps;
//    int status = 0;
//    while ( (status = decideWhatToDoMENU(myfile2, ps)) ) {
//        if (status == 1) {
//            std::cout << "Procedura zakończona!" << std::endl;
//            std::cout << ps;
//        }
//        continue;
//    }
//    ps.petShopToOStream(myfile2);
    
    
    
    
    
    

}
//Produkty:



void test1 () {
    PetShop ps;
    ps.presentInfo();
    //test zmiany nazwy sklepu
    ps.updateName("\n");
    ps.updateName("");
    ps.updateName("   12   ");
    ps.updateName("Sklep Jaszczurka");
    std::cout << std::endl;
    
    //test zmiany adresu
    ps.updateAdress("");
    ps.updateAdress("\n");
    ps.updateAdress("   sklepowa 1");
    ps.updateAdress("Nowowiejska 15/19");
    std::cout << std::endl;
    
    //test zmiany numeru NIP
    ps.updateTaxNumber("123456789");
    ps.updateTaxNumber("raz23456789");
    ps.updateTaxNumber("abcdefghijk");
    ps.updateTaxNumber("1234567890");
    
    std::cout << std::endl;
    ps.presentInfo();
    
    
    std::cout << std::endl;
    //test dodania zwierzęta (za drogie)
    ps.addAnimal(Animal::rybka, Animal::male, 1, 1500, 1300);
    ps.addAnimal(Animal::chomik, Animal::male, 2, 35, 15);
    ps.addAnimal(Animal::pajak, Animal::female, 4, 140, 60);
    ps.addAnimal(Animal::snake, Animal::male, 2, 150, 75);
    ps.addAnimal(Animal::rybka, Animal::female, 1, 12, -5);
    ps.addAnimal(Animal::kanarek, Animal::female, 5, 80, 35);
    ps.addAnimal(Animal::snake, Animal::male, 2, 150, 75);
    ps.addAnimal(Animal::mysz, Animal::female, -1, 8, 3);
    
    std::cout << std::endl;
    //test dodania pokarmu
    ps.addPetFood(2, 10, 2, 0.5, 15, PetFood::rybka, "Jedzeniowy Swiat");
    ps.addPetFood(1, 3, 3, 1, 8, PetFood::chomik, "SuperMicha");
    ps.addPetFood(1, 3, 3, 1, 8, PetFood::chomik, "Jedzonko");
    ps.addPetFood(1, 3, 10, 4, 3, PetFood::pajak, "PajakoSzama");
    ps.addPetFood(-3, 10, 1.5, 0.5, 7, PetFood::kanarek, "Jedz i fruwaj");
    ps.addPetFood(1, 2, 150, 100, 15, PetFood::krolik, "Krolicze przysmaki");
    
    std::cout << std::endl;
    //test dodania zabawki
    ps.addPetToy(2, 15, 5, 3, Product::chomik, "Chomiczkowe krolestwo");
    ps.addPetToy(6, 20, 7, 3, Product::kanarek, "Koleczka dla kanarkow");
    
//    std::cout << std::endl << ps << std::endl;
    
    //operator PetShop + PetFood - uzup. zapasów danego pokarmu
    //po zmianie wyżej kupna 7 pokarmu dla krolika odbywa sie testowanie dopełniania pokarmu za całość pieniędzy w kasie (kupuje tyle, ile starczy)
    //po wykomentowaniu wszystkich powyższych dodawań produktów mamy test dla sytuacji uzupełnienia zapasów bez żadnego produktu
    //moge rozwazyc wykluczenie sytuacji uzupelmniania zapasow ktorych nie ma w magazynie
    ps + (*ps.returnPetFood(13));
    ps + (*ps.returnPetFood(-2));
    
    ps + (*ps.returnPetToy(1));
    ps + (*ps.returnPetToy(1));
    
//    std::cout << std::endl << ps << std::endl;
    
    //dodaje do paragonu pokarm o indeksie (tutaj nie ma stworzonego żadnego paragonu)
    ps += ps.returnPetFood(3);
    //analogicznie dla zwierzęcia
    ps += ps.returnAnimal(3);
    
    std::cout << std::endl;
    
    //operator dodający nowy paragon
    ++ps.returnCashRegister();
    std::cout << std::endl;
    
    //dodawanie do rachunku operatorem +=
    ps += ps.returnAnimal(2);
    ps += ps.returnPetFood(1);
    ps += ps.returnAnimal(3);
    ps += ps.returnPetFood(3);
    ps += ps.returnPetToy(1);
    
    //w tym wyświetleniu dostaniemy zwiększoną gotówkę w kasie (ze względu na dodanie do paragonu - sprzedaż) oraz usunięte/zmienione ilości sprzedanych produktów
//    std::cout << std::endl << ps << std::endl;
    
    //wyświetlmy teraz wartość sklepu (suma wszystkich towarów i gotówki w kasie
    std::cout << "Sklep warty jest " << double(ps) << std::endl;
    
    //testujemy teraz operator indeksowania kasy fiskalnej, powinien zwrocic referencje na paragon, w przypadku podania błędnego indeksu program zwróci na najbliższy podanemu indeksowi. Gdy nie ma żadnego paragonu, program zainicjuje paragon domyślny (można zmienić, żeby kończył działanie - jest to sytuacja odwołania do nieistniejącego indexu)
    std::cout << std::endl << ps.returnCashRegister()[-1] << std::endl << std::endl;
    std::cout << ps.returnCashRegister()[1] << std::endl << std::endl;
    std::cout << ps.returnCashRegister()[0] << std::endl << std::endl;
    
    
    //testujemy karmienie zwierząt (aktualizuje się data oraz zmniejsza ilość karmy
    std::cout << ps << std::endl;
    *ps.returnAnimal(0) = *ps.returnPetFood(0);
    *ps.returnAnimal(0) = *ps.returnPetFood(1);
//    std::cout << std::endl << ps << std::endl;
    
    //sprzędajmy karme dla chomika tak zeby jej nie bylo
    for (int i = 0; i < 7; i++) {
        ps += ps.returnPetFood(1);
    }
//    std::cout << std::endl << ps << std::endl;
    //aktualnie nie ma pokarmu, którym chcemy nakarmić. Wyświetla się informacja, że nie ma pokarmu na stanie
    *ps.returnAnimal(0) = *ps.returnPetFood(1);
    
    //sprawdźmy jeszcze ile jest stworzonych sklepow i zwierzat
    std::cout << std::endl << "Tyle sklepów: "<<PetShop::returnHowMany() << " i tyle zwierząt: " << Animal::returnHowMany() << std::endl;
    
    
    //wszystkie operatory i funkcje przetestowane
//    ps.returnCashRegister().saveInReceiptHistoryFile();
    std::cout << ps;
    std::ofstream myfile;
    myfile.open("wynik.txt");
    ps.petShopToOStream(myfile);
}

void test2 () {
    std::ofstream myfile;
    myfile.open("wynik.txt");
    
    PetShop ps;
    ps.presentInfo();
    //test zmiany nazwy sklepu
    ps.updateName("\n");
    ps.updateName("");
    ps.updateName("   12   ");
    ps.updateName("Sklep Jaszczurka");
    std::cout << std::endl;
    
    //test zmiany adresu
    ps.updateAdress("");
    ps.updateAdress("\n");
    ps.updateAdress("   sklepowa 1");
    ps.updateAdress("Nowowiejska 15/19");
    std::cout << std::endl;
    
    //test zmiany numeru NIP
    ps.updateTaxNumber("123456789");
    ps.updateTaxNumber("raz23456789");
    ps.updateTaxNumber("abcdefghijk");
    ps.updateTaxNumber("1234567890");
    
    std::cout << std::endl;
    ps.presentInfo();
    
    
    std::cout << std::endl;
    //test dodania zwierzęta (za drogie)
    ps.addAnimal(Animal::rybka, Animal::male, 1, 1500, 1300);
    ps.addAnimal(Animal::chomik, Animal::male, 2, 35, 15);
    ps.addAnimal(Animal::pajak, Animal::female, 4, 140, 60);
    ps.addAnimal(Animal::snake, Animal::male, 2, 150, 75);
    ps.addAnimal(Animal::rybka, Animal::female, 1, 12, -5);
    ps.addAnimal(Animal::kanarek, Animal::female, 5, 80, 35);
    ps.addAnimal(Animal::snake, Animal::male, 2, 150, 75);
    ps.addAnimal(Animal::mysz, Animal::female, -1, 8, 3);
    
    std::cout << std::endl;
    //test dodania pokarmu
    ps.addPetFood(2, 10, 2, 0.5, 15, PetFood::rybka, "Jedzeniowy Świat");
    ps.addPetFood(1, 3, 3, 1, 8, PetFood::chomik, "SuperMicha");
    ps.addPetFood(1, 3, 3, 1, 8, PetFood::chomik, "Jedzonko");
    ps.addPetFood(1, 3, 10, 4, 3, PetFood::pajak, "PajakoSzama");
    ps.addPetFood(-3, 10, 1.5, 0.5, 7, PetFood::kanarek, "Jedz i fruwaj");
    ps.addPetFood(1, 2, 150, 100, 15, PetFood::krolik, "Krolicze przysmaki");
    
    //    std::cout << std::endl << ps << std::endl;
    
    //operator PetShop + PetFood - uzup. zapasów danego pokarmu
    //po zmianie wyżej kupna 7 pokarmu dla krolika odbywa sie testowanie dopełniania pokarmu za całość pieniędzy w kasie (kupuje tyle, ile starczy)
    //po wykomentowaniu wszystkich powyższych dodawań produktów mamy test dla sytuacji uzupełnienia zapasów bez żadnego produktu
    //moge rozwazyc wykluczenie sytuacji uzupelmniania zapasow ktorych nie ma w magazynie
    ps + (*ps.returnPetFood(13));
    ps + (*ps.returnPetFood(-2));
    
    //    std::cout << std::endl << ps << std::endl;
    
    //dodaje do paragonu pokarm o indeksie (tutaj nie ma stworzonego żadnego paragonu)
    ps += ps.returnPetFood(3);
    //analogicznie dla zwierzęcia
    ps += ps.returnAnimal(3);
    
    std::cout << std::endl;
    
    //operator dodający nowy paragon
    ++ps.returnCashRegister();
    std::cout << std::endl;
    
    //dodawanie do rachunku operatorem +=
    ps += ps.returnAnimal(2);
    ps += ps.returnPetFood(1);
    ps += ps.returnAnimal(3);
    ps += ps.returnPetFood(3);
    
    //w tym wyświetleniu dostaniemy zwiększoną gotówkę w kasie (ze względu na dodanie do paragonu - sprzedaż) oraz usunięte/zmienione ilości sprzedanych produktów
    //    std::cout << std::endl << ps << std::endl;
    
    //wyświetlmy teraz wartość sklepu (suma wszystkich towarów i gotówki w kasie
    std::cout << "Sklep warty jest " << double(ps) << std::endl;
    
    //testujemy teraz operator indeksowania kasy fiskalnej, powinien zwrocic referencje na paragon, w przypadku podania błędnego indeksu program zwróci na najbliższy podanemu indeksowi. Gdy nie ma żadnego paragonu, program zainicjuje paragon domyślny (można zmienić, żeby kończył działanie - jest to sytuacja odwołania do nieistniejącego indexu)
    myfile << std::endl << ps.returnCashRegister()[-1] << std::endl << std::endl;
    myfile << ps.returnCashRegister()[1] << std::endl << std::endl;
    myfile << ps.returnCashRegister()[0] << std::endl << std::endl;
    
    
    //testujemy karmienie zwierząt (aktualizuje się data oraz zmniejsza ilość karmy
    myfile << ps << std::endl;
    *ps.returnAnimal(0) = *ps.returnPetFood(0);
    *ps.returnAnimal(0) = *ps.returnPetFood(1);
    //    std::cout << std::endl << ps << std::endl;
    
    //sprzędajmy karme dla chomika tak zeby jej nie bylo
    for (int i = 0; i < 7; i++) {
        ps += ps.returnPetFood(1);
    }
    //    std::cout << std::endl << ps << std::endl;
    //aktualnie nie ma pokarmu, którym chcemy nakarmić. Wyświetla się informacja, że nie ma pokarmu na stanie
    *ps.returnAnimal(0) = *ps.returnPetFood(1);
    
    //sprawdźmy jeszcze ile jest stworzonych sklepow i zwierzat
    std::cout << std::endl << "Tyle sklepów: "<<PetShop::returnHowMany() << " i tyle zwierząt: " << Animal::returnHowMany() << std::endl;
    
    
    //wszystkie operatory i funkcje przetestowane
}




void INTERAKTYWNY_SKLEP_ZOO() {
    std::ifstream myfile;
    PetShop ps;
    myfile.open("wynik.txt");
    if (createNLengthString(myfile, 1) == "O") {
        myfile >> ps;
        myfile.close();
    }
    else
        myfile.close();
    
    std::ofstream myfile2 ("wynik.txt");
    
    std::cout << ps;
    int status = 0;
    while ( (status = decideWhatToDoMENU(myfile2, ps)) ) {
        if (status == 1) {
            std::cout << "Procedura zakończona!" << std::endl;
            std::cout << ps;
        }
        continue;
    }
    ps.petShopToOStream(myfile2);
}


void ENCYKLOPEDIA_SKLEP_ZOO () {
    std::cout << "ENCYKLOPEDIA PRODUKTÓW SKLEPU ZOOLOGICZNEGO" << std::endl;
    
    ListMB<Product*> list;
    int status = 0;
    int lngth = 0;
    while ( (status = decideWhatToDoEncyclopediaMENU(list)) ) {
        if (status == 1) {
            std::cout << "Procedura zakończona!" << std::endl;
            lngth = list.getLength();
            std::cout << "Produkty w encyklopedii:" << std::endl;
            for (int i = 0; i < lngth; i++) {
                std::cout << i+1 << "." << std::string(complementIntegerToNCharacters(i+1, 3), ' ');
                list[i].getNodeData() -> productToOstreamEncyclopedia(std::cout);
                std::cout << "    " << "CZAS UTWORZENIA [ms]: " << list[i].getTimeElapsed().count() << std::endl;
            }
        }
        continue;
    }
    lngth = list.getLength();
    for (int i = 0; i < lngth; i++)
        delete list[i].getNodeData();
}

