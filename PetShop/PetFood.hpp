//
//  PetFood.hpp
//  PetShop
//
//  Created by Marcin Badach on 31/10/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef PetFood_hpp
#define PetFood_hpp
//#define _DEBUG

#include <stdio.h>
#include <string>
#include <iostream>
#include "GlobalFunctions.hpp"
#include <iomanip>
#include "PetToy.hpp"

class PetFood : public PetToy {
    
    
public:
    ///Konstruktor pokarmy
    PetFood (int minAgeArg = 0, int maxAgeArg = 10, double priceArg = 10.0, double costArg = 10.0, int stockNumberArg = 1, Species speciesArg = Product::chomik, std::string manufacturerArg="");
    ///Dekonstruktor pokarmu
    ~PetFood ();
    ///Zwraca maksymalny wiek zwierzęcia odbiorcy
    int returnMaxAge();
    ///Przeciążony operator <<
    ///
    ///Pozwala wyświetlić informację o pokarmie (przekazuje obiekt do obiektu klasy ostream)
    ///
    ///Format wyświetlania zgodny z zapisem do pliku
    friend std::ostream& operator<< (std::ostream&, PetFood&);
    ///Metoda wirtualna decydująca o promocji produktu
    ///
    ///Jeśli pokarmu jest dużo (>=20) i jest przeznaczony dla wąskiego grona zwierząt (maxAge - minAge <= 2) zmniejsza marżę o 50%
    virtual bool decideIfDiscount();
    ///Przeciążony operator >>
    ///
    ///Pozwala wczytać pokarm zgodnie ze schematem zapisywania w pliku
    friend std::istream& operator>>(std::istream& is, PetFood& pf);
    ///Metoda pozwalająca użytkownikowi zaktualizować wiek maksymalny
    void userUpdateMaxAge();
    ///Metoda wirtualna przekazująca obiekt w formacie "do wyświetlenia" do obiektu klasy ostream
    virtual std::ostream& productToOstreamEncyclopedia (std::ostream & os);
    
private:
    int maxAge;
    
    //metoda przekazująca wiek maksymalny do okiektu klasy ostream (21 pól)
    std::ostream& maxAgeToOStream(std::ostream&);
    //metoda wczytująca wiek maksymalny odbiorcy produktu;
    std::istream& maxAgeFromIStream(std::istream&);

};

#endif /* PetFood_hpp */
