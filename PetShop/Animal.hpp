//
//  Animal.hpp
//  PetShop
//
//  Created by Marcin Badach on 31/10/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef Animal_hpp
#define Animal_hpp
//#define _DEBUG

#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "PetFood.hpp"
#include "Product.hpp"



class Animal : public Product {
public:
    ///Definicja typu wyliczeniowego płci
    enum Sex {male = 0, female = 1};
    ///Konstruktor zwierzęcia
    Animal(Species = Product::chomik, Sex = male, int = 1, double = 10.0, double = 10.0);
    ///Dekonstruktor zwierzęcia
    ~Animal();
    ///Statyczna metoda, która zwraca ile obiektów jest aktualnie stworzonych
    static int returnHowMany ();
    ///Metoda zwracająca wiek zwierzęcia
    int returnAge();
    ///Przeciążony operator =
    ///
    ///Karmi (jeśli to dozwolone) zwierze przyrównanym jedzeniem
    ///
    ///Przy pomyślnym nakarmieniu, następuje aktualizacja daty ostatniego karmienia
    void operator=(PetFood &);
    ///Metoda, która zwraca płeć zwierzęcia (typ enum) w postaci stringa
    std::string returnSexString();
    ///Przeciążony operator <<
    ///
    ///Pozwala wyświetlić informacje o zwierzęciu (przekazać go do obiektu klasy ostream)
    ///
    ///Format przekazywania: interfejs konsolowy (data wyświetlana w formacie daty)
    friend std::ostream& operator<< (std::ostream&, Animal&);
    ///Metoda wirtualna decydująca o przecenie
    ///
    ///Jeśli zwierze jest starsze niż 5 lat, jego marża zostaje zmniejszona o 50%
    virtual bool decideIfDiscount ();
    ///Metoda wyświetlająca zwierze w formacie paragonowym
    virtual std::ostream& coutReceiptFormat(std::ostream& os);
    ///Metoda przekazująca zwierzę do obiektu klasy ostream
    ///
    ///Format zapisu do pliku (data ostatniego karmienia wyrażona w sekundach od ...)
    std::ostream& animalToOStream(std::ostream&);
    ///Przeciążony operator >>
    ///
    ///Wczytuje zwierzę zgodnie ze schematem zapisywania w pliku
    friend std::istream& operator>>(std::istream& is, Animal& pt);
    ///Metoda pozwalająca użytkownikowi zaktualizować płeć zwierzęcia
    void userUpdateSex();
    ///Metoda pozwalająca użytkownikowi zaktualizować wiek zwierzęcia
    void userUpdateAge();
    ///Metoda wirtualna przekazująca obiekt w formacie "do wyświetlenia" do obiektu klasy ostream
    virtual std::ostream& productToOstreamEncyclopedia (std::ostream & os);

    
    
private:
    static int howMany;

    Sex sex;
    int age;
    std::time_t lastFeedDate;
    
    //metoda przekazująca wiek do okiektu klasy ostream (10 pól)
    std::ostream& ageToOStream(std::ostream&);
    //metoda przekazująca płeć do okiektu klasy ostream (15 pól)
    std::ostream& sexToOStream(std::ostream&);
    //metoda wczytująca płeć zwierzęcia;
    std::istream& sexFromIStream(std::istream&);
    //metoda wczytująca wiek zwierzęcia;
    std::istream& ageFromIStream(std::istream&);
    //metoda wczytująca ostatnią datę karmienia zwierzęcia;
    std::istream& lastFeedDateFromIStream(std::istream&);
};



#endif /* Animal_hpp */
