///
///  PetShop.hpp
///  PetShop
///
///  Created by Marcin Badach on 31/10/2019.
///  Copyright © 2019 Marcin Badach. All rights reserved.
///




#ifndef PetShop_hpp
#define PetShop_hpp
//#define _DEBUG



#include <stdio.h>
#include <string>
#include <vector>
#include "Animal.hpp"
#include "PetFood.hpp"
#include "CashRegister.hpp"
#include <fstream>

class PetShop {
    
private:
    static int howMany;
    std::string name;
    std::string adress;
    std::string taxNumber;
    std::vector<Animal *> animalVector;
    std::vector<PetFood *> petFoodVector;
    std::vector<PetToy *> petToyVector;
    
    CashRegister cashRegister;
    
    //SZABLON FUNKCJI, która jest funkcją pomocniczą w uzupełnianiu stanu magazynowego produktów typu PetToy i PetFood. Warunki dla uzupełnienia stanu magazynowego (jeśli jakikolwiek produkt tego typu jest w wektorze w sklepie) są takie same, więc funkcja odpowiada za odpowiednie zachowanie.
    template<typename T>
    void restockProduct(T& prod);
    //SZABLON FUNKCJI
    template <typename T>
    void addToyOrFoodToReceipt(T * prod);
    //metoda przekazująca nazwę sklepu do obiektu klasy ostream (60 pól)
    std::ostream& nameToOStream(std::ostream&);
    //metoda przekazująca adres sklepu do obiektu klasy ostream (60 pól)
    std::ostream& adressToOStream(std::ostream&);
    ///metoda przekazująca numer NIP do obiektu klasy ostream (25 pól)
    std::ostream& taxNumberToOStream(std::ostream&);
    //metoda wczytująca nazwę sklepu;
    std::istream& nameFromIStream(std::istream&);
    //metoda wczytująca adres sklepu;
    std::istream& adressFromIStream(std::istream&);
    //metoda wczytująca numer NIP sklepu;
    std::istream& taxNumberFromIStream(std::istream&);
    //metoda wczytująca informacje o sklepie z obiekty klasy istream
    std::istream& shopInfoFromIStream(std::istream&);
    //metoda wczytująca informacje o zwierzętach w sklepie z obiektu klasy istream
    std::istream& animalsFromIStream(std::istream&);
    //metoda wczytująca informacje o pokarmach w sklepie z obiektu klasy istream
    std::istream& petFoodFromIStream(std::istream&);
    //metoda wczytująca informacje o zabawkach w sklepie z obiektu klasy istream
    std::istream& petToyFromIStream(std::istream&);
    
    //metoda dodająca wskaźnik na zwierze do sklepu.
    void addAnimalPointer(Animal * ptr);
    //metoda dodająca wskaźnik na zabawke do sklepu.
    void addPetToyPointer(PetToy * ptr);
    //metoda dodająca wskaźnik na jedzenie do sklepu.
    void addPetFoodPointer(PetFood * ptr);
    
    
public:
    ///Konstruktor sklepu, który ma również podane parametry domyślne
    ///
    PetShop(std::string = "Sklep zoologiczny", std::string = "Sklepowa 1", std::string = "0000000000");
    ///Dekonstruktor sklepu
    ~PetShop();
    ///Statyczna metoda, która zwraca liczbę zainicjalizowanych obiektów klasy PetShop
    static int returnHowMany();
    ///Zwraca referencje kasy fiskalnej, która jest podobiektem obiektu klasy PetShop
    CashRegister& returnCashRegister ();
    ///Prezentuje podstawowe informacje o sklepie (cout adres, nazwa, nip)
    void presentInfo();
    ///Pozwala użytkownikowi zaktualizować informacje o sklepie
    ///Pyta się czy użytkownik chce zmodyfikować każdy modyfikowalny parametr i jeśli tak, to wywołuje odpowiednie prywatne funkcje modyfikujące
    ///Obsługuje błędy
    void updateShopDetails();
    ///Pozwala użytkownikowi wpisać nową nazwę sklepu i zwraca ją
    ///Obsługuje błędy
    std::string userUpdateName();
    ///Pozwala użytkownikowi wpisać nowy adres sklepu i zwraca go
    ///Obsługuje błędy
    std::string userUpdateAdress();
    ///Pozwala użytkownikowi wpisać nowy numer NIP sklepu i zwraca go
    ///Obsługuje błędy - NIP musi być ciągiem dokładnie 10 cyfr
    std::string userUpdateTaxNumber();
    ///Uaktualnia nazwę sklepu na podaną jako parametr
    ///@param newName - nazwa sklepu, która ma zastąpić aktualną
    void updateName(std::string newName);
    ///Uaktualnia adres sklepu na podany jako parametr
    ///@param newAdress - adres sklepu, który ma zastąpić aktualny
    void updateAdress(std::string newAdress);
    ///Uaktualnia numer NIP sklepu na podany jako parametr
    ///@param newTaxNumber - numer NIP, który ma zastąpić aktualny
    void updateTaxNumber(std::string newTaxNumber);
    ///Przeciążony operator dodawania
    ///Pozwala uzupełnić stan magazynowy konkretnego jedzenia do 25, ale tylko wtedy gdy są na to pieniądze
    ///Jeśli nie ma, uzupełnia tylko o tyle o ile się da (ile jest pieniędzy)
    ///Jeśli stan magazynowy jedzenie jest większy/równy 25, metoda nie wywołuje zmian
    ///@param pf - referencja na pokarm, którego stan magazynowy ma zostać uzupełniony
    void operator+(PetFood& pf);
    ///Przeciążony operator dodawania
    ///Pozwala uzupełnić stan magazynowy konkretnej zabawki do 25, ale tylko wtedy gdy są na to pieniądze
    ///Jeśli nie ma, uzupełnia tylko o tyle o ile się da (ile jest pieniędzy)
    ///Jeśli stan magazynowy jedzenie jest większy/równy 25, metoda nie wywołuje zmian
    ///@param pt - referencja na zabawkę, której stan magazynowy ma zostać uzupełniony
    void operator+(PetToy& pt);
    ///Przeciążony operator rzutowania
    ///Sklep zrzutowany na double jest teoretyczną wartością sklepu - sumą cen wszystkich produktów i gotówki w kasie
    operator double();
    ///Przeciążony operator +=
    ///Operator dodawania zwierzęcia do ostatniego rachunku w kasie
    ///Metoda sprawdza, czy jest jakikolwiek paragon w kasie i czy taki wskaźnik (przekazany jako parametr) jest w wektorze zwierząt sklepu, jeśli tak, to wstawia jego kopie do paragonu, a następnie wyrzuca oryginalny z wektora wskaźników zwierząt w sklepie
    ///Dodaje pieniądze ze sprzedaży do kasy fiskalnej
    ///@param anim - wskaźnik na zwierzę, które ma zostać dodane do paragonu
    void operator+= (Animal * anim);
    ///Przeciążony operator +=
    ///Operator dodawania pokarmu do rachunku (ostatniego w kasie)
    ///Metoda sprawdza, czy jest jakikolwiek paragon w kasie i czy taki wskaźnik jest w wektorze pokarmu sklepu, jeśli tak, to w zależności od stanu magazynu jedzenia, tworzy nowy obiekt i wstawia wskaźnik do wektora w paragonie i zmniejsza stan magazynowy obiektu w sklepie, albo nie pozwala dokonać zakupu (gdy stan == 0)
    ///Dodaje pieniądze ze sprzedaży do kasy fiskalnej
    ///@param pf - wskaźnik na pokarm, który ma zostać sprzedany
    void operator+= (PetFood * pf);
    ///Przeciążony operator +=
    ///Operator dodawania zabawki do rachunku (ostatniego w kasie)
    ///Metoda sprawdza, czy jest jakikolwiek paragon w kasie i czy taki wskaźnik jest w wektorze zabawek sklepu, jeśli tak, to w zależności od stanu magazynu zabawki, tworzy nowy obiekt i wstawia wskaźnik do wektora w paragonie i zmniejsza stan magazynowy obiektu w sklepie, albo nie pozwala dokonać zakupu (gdy stan == 0)
    ///Dodaje pieniądze ze sprzedaży do kasy fiskalnej
    ///@param pt - wskaźnik na pokarm, który ma zostać sprzedany
    void operator+= (PetToy * pt);
    ///Przeciążony operator <<
    ///Operator umożliwiający przekazanie obiektu klasy sklep do obiektu klasy ostream w celu wyświetlenia go
    ///Wyświetlanie w formacie interfejsu
    friend std::ostream& operator<< (std::ostream &, PetShop&);
    ///Metoda pozwalająca dodać nowe zwierzę do sklepu (a właściwie kupić, bo trzeba wydać na nie pieniądze z kasy)
    ///Nowe zwierze ma cechy takie, jak parametry wejściowe funkcji i jest dodawane do wektora zwierząt sklepu
    void addAnimal (Animal::Species spArg, Animal::Sex sexArg, int ageArg, double priceArg, double costArg);
    ///Metoda pozwalająca dodać nowy pokarm do sklepu (a właściwie kupić, bo trzeba wydać na niego pieniądze z kasy)
    ///Nowy pokarm ma cechy takie, jak parametry wejściowe funkcji i jest dodawany do wektora pokarmów sklepu
    void addPetFood (int minAgeArg, int maxAgeArg, double priceArg, double costArg, int stockNumberArg, PetFood::Species animalsTypeArg, std::string manufacturerArg);
    ///Metoda pozwalająca dodać nową zabawkę do sklepu (a właściwie kupić, bo trzeba wydać na nią pieniądze)
    ///Nowa zabawka ma cechy takie, jak parametry wejściowe funkcji i jest dodawana do wektora zabawek sklepu
    void addPetToy (int minAgeArg, double priceArg, double costArg, int stockNumberArg, PetFood::Species animalsTypeArg, std::string manufacturerArg);
    ///Metoda zwracająca n-ty element wektora pokarmu w sklepie
    ///Notacja programistyczna, n=0 to pierwszy element
    ///Obsługuje błędy - gdy podany za duży numer - zwraca ostatni, gdy za mały - pierwszy
    PetFood * returnPetFood (int n);
    ///Metoda zwracająca n-ty element wektora zwierząt w sklepie
    ///Notacja programistyczna, n=0 to pierwszy element
    ///Obsługuje błędy - gdy podany za duży numer - zwraca ostatni, gdy za mały - pierwszy
    Animal * returnAnimal (int n);
    ///Metoda zwracająca n-ty element wektora zabawek w sklepie
    ///Notacja programistyczna, n=0 to pierwszy element
    ///Obsługuje błędy - gdy podany za duży numer - zwraca ostatni, gdy za mały - pierwszy
    PetToy * returnPetToy (int n);
    ///Metoda przekazująca sklep do obiektu klasy ostream w formacie zapisu do pliku
    std::ostream& petShopToOStream(std::ostream&);
    ///Przeciążony operator >>
    ///Operator wczytujący sklep z pliku (wymagany konkretny format)
    friend std::istream& operator>>(std::istream& is, PetShop& ps);
    ///Metoda zwracająca ilość zwierząt w sklepie
    int returnAnimalVectorLength ();
    ///Metoda zwracająca ilość zabawek w sklepie
    int returnPetToyVectorLength ();
    ///Metoda zwracająca ilość pokarmów w sklepie
    int returnPetFoodVectorLength ();
    ///Podejmuje dla każdego produktu decyzję czy przecenić
    ///Dla każdego produktu w sklepie wywołuje funkcję wirtualną decydującą (i ewentualnie wykonującą) o obzniżce
    void decideIfDiscount();
    ///Pozwala dokupić do sklepu zdefiniowane przez użytkownika zwierze
    ///Obsługuje błędy
    void userAddAnimal();
    ///pozwala dokupić do sklepu zdefiniowaną przez użytkownika zabawkę
    ///Obsługuje błędy
    void userAddPetToy();
    ///pozwala dokupić do sklepu zdefiniowany przez użytkownika pokarm
    ///Obsługuje błędy
    void userAddPetFood();
    
    ///Pozwala wybrać użytkownikowi numer zwierzęcia, z dostępnych, a następnie zwraca go w postaci int
    ///Obsługuje błędy - sprawdza czy zwierze o danym numerze istnieje itp.
    ///@return numer (int) wybranego przez użytkownika zwierzęcia (numeracja od 1)
    int userChooseAnimal();
    ///Pozwala wybrać użytkownikowi numer zabawi, z dostępnych, a następnie zwraca go w postaci int
    ///Obsługuje błędy - sprawdza czy zabawka o danym numerze istnieje itp.
    ///@return numer (int) wybranej przez użytkownika zabawki (numeracja od 1)
    int userChoosePetToy();
    ///Pozwala wybrać użytkownikowi numer jedzenia, z dostępnych, a następnie zwraca go w postaci int
    ///Obsługuje błędy - sprawdza czy pokarm o danym numerze istnieje itp.
    ///@return numer (int) wybranego przez użytkownika pokarmu (numeracja od 1)
    int userChoosePetFood();
    
    ///Pozwala użytkownikowi nakarmić wybrane przez niego zwierze wybranym przez niego produktem
    ///Pyta użytkownika o to, które zwierze nakarmić którym produktem.
    void userFeedAnimal();
};



#endif /* PetShop_hpp */
