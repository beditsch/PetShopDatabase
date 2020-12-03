//
//  Receipt.hpp
//  PetShop
//
//  Created by Marcin Badach on 31/10/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef Receipt_hpp
#define Receipt_hpp
//#define _DEBUG

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Animal.hpp"
#include <cmath>
#include "Product.hpp"



class Receipt {
    std::vector<Product *> productsBought;
    double totalPrice;
    std::time_t date;
    
public:
    ///Konstruktor paragonu
    Receipt();
    ///Dekonstruktor paragonu
    ~Receipt();
    ///Przeciążony operator <<
    ///
    ///przekazuje paragon do obiektu klasy ostream w określonym formacie
    friend std::ostream& operator<< (std::ostream &, Receipt&);
    ///Metoda działająca na wektorze wskaźników polimorficznych
    ///
    ///Pozwala na push_back danego produktu do wektora zakupionych produktów
    void addProduct (Product *);
};


#endif /* Receipt_hpp */
