//
//  Product.hpp
//  PetShop
//
//  Created by Marcin Badach on 09/12/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef Product_hpp
#define Product_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "GlobalFunctions.hpp"
#include <iomanip>

class Product {
public:
    ///Definicja typu wyliczeniowego dla gatunku/gatunku przeznaczenia
    enum Species {chomik, kanarek, krolik, mysz, pajak, papuga, rybka, snake};
    ///Definicja typu wyliczeniowego dla typu produktu
    enum ProductType {zwierze, zabawka, pokarm};
    ///Konstruktor produktu
    Product(Species = chomik, double = 10.0, double = 10.0);
    ///Dekonstruktor produktu
    virtual ~Product();
    ///Statyczna metoda, która zwraca ile obiektów klasy Produkt jest aktualnie stworzonych
    static int returnHowMany ();
    ///Zwraca cenę produktu
    double returnPrice();
    ///Zwraca koszt zakupu produktu
    double returnCost();
    ///Zwraca gatunek/gatunek przeznaczenia produktu w postaci int
    ///@return int odpowiadający gatunkowi produktu (od 0 - chomik do 7 - snake)
    int returnSpecies();
    ///Zwraca string będący nazwą gatunku produktu
    std::string returnSpeciesString();
    ///Zwraca typ produktu w postaci int
    ///@return 0 - zwierze; 1 - zabawka; 2 - pokarm
    int returnProductType();
    ///Zwraca string będący typem produktu
    std::string returnProductTypeString();
    ///Przeciążony operator <<
    ///
    ///Operator strumieniowy pozwalający przekazać cenę i koszt produktu w odpowiednim formacie do obiektu klasy ostream
    ///
    ///Format odpowiedni do wyświetlania oraz zgodny z formatem zapisu do pliku
    friend std::ostream& operator<< (std::ostream&, Product&);
    ///Metoda wirtualna
    ///
    ///Pobiera i zwraca referencje na obiekt klasy ostream i "przekazuje" mu produkt w formacie paragonowym (wykorzystuje metody wyświetlające typ, gatunek i cene w formacie paragonowym)
    ///
    ///Format wyświetlania zgodny z formatem na paragonie
    virtual std::ostream& coutReceiptFormat(std::ostream&) = 0;
    ///Metoda wirtualna
    ///
    ///Analizuje produkt i robi jego przecenę, jeśli ma to sens (aby sprzedać zalegające produkty).
    ///
    ///Warunkiem koniecznym przeceny jest cena wyższa od kosztu zakupu
    ///
    ///Zwierzę zostaje przecenione, gdy jest stare, tzn gdy ma więcej niż 5 lat
    ///
    ///Zabawka zostaje przeceniona, gdy jest jej więcej niż 20
    ///
    ///Pokarm zostaje przeceniowy, gdy jest go więcej niż 20 i ma wąskie zastosowanie, tzn. wiek maksymalny karmionego zwierzęcia różni się od wieku minimalnego o maksymalnie 2 lata.
    ///
    ///Jeśli są spełnione warunki to zmniejsza marżę o 50%
    ///@return Zwraca informację, czy podjęta została decyzja o przecenie.
    virtual bool decideIfDiscount() = 0;
    ///Pozwala użytkownikowi wprowadzić gatunek w formacie tekstowtym
    ///
    ///Po poprawnym wprowadzeniu aktualizuje gatunek produktu
    void userUpdateSpecies();
    ///Pozwala użytkownikowi wprowadzić cenę
    ///
    ///Po poprawnym wprowadzeniu aktualizuje cenę produktu
    void userUpdatePrice();
    ///Pozwala użytkownikowi wprowadzić koszt
    ///
    ///Po poprawnym wprowadzeniu aktualizuje koszt
    void userUpdateCost();
    ///Metoda wirtualna przekazująca obiekt w formacie "do wyświetlenia" do obiektu klasy ostream
    virtual std::ostream& productToOstreamEncyclopedia (std::ostream & os) = 0;
    
    
    
    
private:
    static int howMany;
    
protected:
    Species species;
    double price;
    double cost;
    ProductType productType;
    
    //metoda wyświetlająca typ produktu oraz gatunek w formacie paragonowym
    std::ostream& coutReceiptFormat_TypeSpecies(std::ostream& os);
    //metoda wyświetlająca cenę w formacie paragonowym
    std::ostream& coutReceiptFormat_Price(std::ostream& os);
    //metoda przekazująca gatunek do obiektu klasy ostream (25 pól w sumie - razem z napisem GATUNEK:)
    std::ostream& speciesToOStream(std::ostream&);
    //metoda przekazująca koszt do okiektu klasy ostream (15 pól)
    std::ostream& costToOStream(std::ostream&);
    //metoda przekazująca cenę do okiektu klasy ostream (15 pól)
    std::ostream& priceToOStream(std::ostream&);
    //metoda przekazująca typ produktu do okiektu klasy ostream (20 pól)
    std::ostream& typeToOStream(std::ostream&);
    //metoda wczytująca gatunek produktu;
    std::istream& speciesFromIStream(std::istream&);
    //metoda wczytująca cenę produktu;
    std::istream& priceFromIStream(std::istream&);
    //metoda wczytująca koszt produktu;
    std::istream& costFromIStream(std::istream&);
    
};






#endif /* Product_hpp */
