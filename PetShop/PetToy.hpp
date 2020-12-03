//
//  PetToy.hpp
//  PetShop
//
//  Created by Marcin Badach on 15/12/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef PetToy_hpp
#define PetToy_hpp
//#define _DEBUG

#include <stdio.h>
#include "Product.hpp"
#include <string>
#include <iostream>
#include <iomanip>

class PetToy : public Product {
    
public:
    ///Konstruktor zabawki
    PetToy(int minAgeArg = 0, double priceArg = 10.0, double costArg = 10.0, Species speciesArg = Product::chomik, int stockNumberArg = 1, std::string manufacturerArg = "Producent");
    ///Dekonstruktor zabawki
    ~PetToy();
    ///Zwraca pole producenta w postaci string
    std::string returnManufacturer();
    ///Zwraca minimalny wiek zwierzęcia odbiorcy
    int returnMinAge();
    ///Przeciążony operator <<
    ///
    ///Pozwala wyświetlić informację o pokarmie (przekazuje obiekt do obiektu klasy ostream)
    ///
    ///Format wyświetlania zgodny z wyświetlaniem w interfejsie oraz zapisywaniem do pliku
    friend std::ostream& operator<< (std::ostream&, PetToy&);
    ///Metoda wirtualna decydująca o obniżeniu ceny
    ///
    ///Jeśli zabawki jest więcej niż 20 -> zmniejsza marżę o połowę
    virtual bool decideIfDiscount();
    ///Metoda wirtualna
    ///
    ///Przekazuje zabawkę w formacie paragonowym do obiektu klasy ostream
    virtual std::ostream& coutReceiptFormat(std::ostream& os);
    //Zwraca ilość produktu na stanie
    int returnStockNumber();
    ///Pozwala na zmane ilości na magazynie
    ///@param n - nowa wartość stanu magazynowego produktu
    void changeStock(int n);
    ///Przeciążony operator >>
    ///
    ///Wczytuje zabawkę zgodnie ze schematem zapisywania w pliku
    friend std::istream& operator>>(std::istream& is, PetToy& pt);
    ///Metoda pozwalająca użytkownikowi zaktualizować minimalny wiek zwierzęcia
    void userUpdateMinAge();
    ///Metoda pozwalająca użytkownikowi zaktualizować stan magazynowy
    ///
    ///Uwaga: po zmianie stanu nie pobiera pieniędzy za dodany produkt
    void userUpdateStockNumber();
    ///Metoda pozwalająca użytkownikowi zaktualizować producenta
    void userUpdateManufacturer();
    ///Metoda wirtualna przekazująca obiekt w formacie "do wyświetlenia" do obiektu klasy ostream
    virtual std::ostream& productToOstreamEncyclopedia (std::ostream & os);
    
    
    
    
    
protected:
    int minAge;
    std::string manufacturer;
    int stockNumber;
    
    //metoda przekazująca wiek minimalny do okiektu klasy ostream (20 pól)
    std::ostream& minAgeToOStream(std::ostream&);
    //metoda przekazująca producenta do okiektu klasy ostream (60 pól)
    std::ostream& manufacturerToOStream(std::ostream&);
    //metoda przekazująca stan magazynu do okiektu klasy ostream (60 pól)
    std::ostream& stockNumberToOStream(std::ostream&);
    //metoda wczytująca stan magazynu produktu;
    std::istream& stockNumberFromIStream(std::istream&);
    //metoda wczytująca wiek minimalny odbiorcy produktu;
    std::istream& minAgeFromIStream(std::istream&);
    //metoda wczytująca producenta produktu;
    std::istream& manufacturerFromIStream(std::istream&);
};





#endif /* PetToy_hpp */
