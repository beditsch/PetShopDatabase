//
//  Receipt.cpp
//  PetShop
//
//  Created by Marcin Badach on 31/10/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "Receipt.hpp"

Receipt::Receipt() {
    totalPrice = 0.0;
    date = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
#ifdef _DEBUG
    std::cout << "Konstuktor paragonu wywołany." << std::endl;
#endif
}

Receipt::~Receipt() {
    int n = static_cast<int>(productsBought.size());
    for (int i = 0; i < n; i++) {
        delete productsBought[i];
    }
#ifdef _DEBUG
    std::cout << "Dekonstruktor paragonu wywołany." << std::endl;
#endif
}


std::ostream & operator<<(std::ostream & os, Receipt & rec) {
    os << std::string(46, ' ') << "PARAGON" << std::string(23, ' ') << std::endl;
    os << "Czas: " << std::ctime(&(rec.date));
    os << "Oto szczegóły transakcji:" << std::endl;
    
    //wyświetlanie produktów
    //lp - 3 pola; typ - 15pól; gatunek - 20 pól; producent - 50 pól; cena - 7 pól (justowanie do prawej)
    os << "Produkty:" << std::endl;
    os << "Lp " << "|" << std::string(6, ' ') << "Typ" << std::string(6, ' ') << "|" << std::string(6, ' ') << "Gatunek" << std::string(7, ' ') << "|" << std::string(21, ' ') << "Producent" << std::string(20, ' ') << "   Cena" << std::endl;
    int num = static_cast<int>(rec.productsBought.size());
    os << std::fixed;
    os << std::setprecision(2);
    int nOfSpacesForNumber = 2;
    for (int i = 0; i < num; i++) {
        //wyświetlanie Lp
        if (i != 0)
            nOfSpacesForNumber = 3 - (floor(log10(i+1)) + 1);
        os << std::string(nOfSpacesForNumber, ' ') << i + 1 << "|";
        //wyświetlanie gatunku
        rec.productsBought[i] -> coutReceiptFormat(os);
    }
    
    //wyświetlanie całkowitego kosztu
    double sum = 0.0;
    for (int i = 0; i < num; i++) {
        sum += (rec.productsBought[i] -> returnPrice());
    }
    os << std::string(46, ' ') << "SUMA: ";
    os << sum << std::endl;
    return os;
}

void Receipt::addProduct (Product * ptr) {
    productsBought.push_back(ptr);
    totalPrice += ptr -> returnPrice();
}



//HISTORIA
