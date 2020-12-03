//
//  CashRegister.hpp
//  PetShop
//
//  Created by Marcin Badach on 31/10/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef CashRegister_hpp
#define CashRegister_hpp
//#define _DEBUG

#include <stdio.h>
#include <vector>
#include "Receipt.hpp"
#include <fstream>

class CashRegister {
    double cash;
    std::vector<Receipt *> receiptHistory;
    
    //metoda przekazująca stan gotówki do obiektu klasy ostream (40 pól)
    std::ostream& cashToOStream(std::ostream&);
    //metoda pozwalająca zapisać nowo dodane paragony do pliku z historią paragonów
    void saveInReceiptHistoryFile();

public:
    
    ///Konstruktor kasy fiskalnej
    CashRegister(double = 1000.0);
    ///Dekonstruktor kasy fiskalnej
    ~CashRegister();
    
    ///Metoda zwracająca stan gotówki w kasie
    double returnCash();
    ///Metoda zwracająca ilość paragonów w historii (długość wektora)
    int returnLength();
    ///Metoda pozwalająca "wydać" pieniądze
    ///
    ///Odejmuje z kasy n pieniędzy i zwraca 1 jeśli się udało (było wystarczająco dużo) lub 0 jeśli nie starczyło
    ///@param n - kwota do wydania z kasy
    ///@return true - było wystarczająco dużo gotówki; false - nie starczyło gotówki
    bool spendCash(double n);
    ///Metoda dodająca do kasy c pieniędzy (wykorzystywana przy dodawaniu do paragonu)
    ///@param c - ilość pieniędzy, którą należy dodać do kasy fiskalnej
    void collectCash (double c);
    ///Przeciążony operator ++
    ///
    ///Dodaje nowy paragon na koniec wektora
    void operator++();
    ///Przeciążony operator indeksowania []
    ///
    ///Zwraca referencje na i-ty paragon w historii paragonów
    Receipt& operator[](int);
    ///Dodaje produkt na koniec wektora produktów ostatniego paragonu
    void productPushBack(Product *);
    ///Przeciążony operator <<
    ///
    ///Pozwala przekazać do obiektu klasy ostream informacje o obiekcie typu cash register
    ///
    ///Format wyświetlania: interfejs konsolowy
    friend std::ostream & operator<< (std::ostream &, CashRegister &);
    ///Metoda przekazująca kasę fiskalną do obiektu klasy ostream w formacie zapisu do pliku
    ///
    ///Przekazuje informację o ilości gotówki oraz zapisuje nowoutworzone paragony w historii paragonów
    std::ostream& cashRegisterToOStream (std::ostream&);
    ///Przeciążony operator >>
    ///
    ///Czyli metoda wczytująca gotówkę w kasie fiskalnej z pliku
    friend std::istream& operator>>(std::istream& is, CashRegister& cr);
};

#endif /* CashRegister_hpp */
