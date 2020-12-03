//
//  UserInterface.hpp
//  PetShop
//
//  Created by Marcin Badach on 17/12/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef UserInterface_hpp
#define UserInterface_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include "PetShop.hpp"
#include "ListMB.h"


//USER INTERFACE FUNCTIONS
///Funkcja, która wyświetla MENU główne dla użytkownika - zarządzanie sklepem
void printMENU ();
///Funkcja, która wyświetla menu dodawania produktów do sklepu - zarządzanie sklepem
void printAddMENU ();
///Funkcja, która wyświetla menu sprzedaży (wyboru typu produktu do sprzedaży) - zarządzanie sklepem
void printSellMENU();
///Funkcja obsługująca interakcje użytkownika z menu głównyn - zarządzanie sklepem
int decideWhatToDoMENU (std::ofstream& destinationFile, PetShop& ps);
///Funkcja obsługująca interakcje użytkownika z  menu dokupowania nowego produktu do sklepu - zarządzanie sklepem
int decideWhatToDoAddMENU (PetShop& ps);
///Funkcja obsługująca interakcje użytkownika z menu dokupowania nowego produktu do sklepu - zarządzanie sklepem
int decideWhatToDoSellMENU (PetShop& ps);

///ENCYKLOPEDIA
///Funkcja wyświetlająca MENU dla użytkownika - encyklopedia obiektów
void printEncyclopediaMENU();
///Funkcja obsługująca interakcje użytkownika z menu encyklopedii
int decideWhatToDoEncyclopediaMENU (ListMB<Product*>& list);
///Funkcja obsługująca wpisywanie numeru na liście przez użytkownika i zwracająca go
int userNumberInput();

#endif /* UserInterface_hpp */
