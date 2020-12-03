//
//  GlobalFunctions.hpp
//  PetShop
//
//  Created by Marcin Badach on 01/11/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef GlobalFunctions_hpp
#define GlobalFunctions_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>

///Funkcja służąca do obsługi podstawowego inputu
///
///Zwraca true jeśli użytkownik wpisał 'T', a false jeśli 'N'
///
///Zapętlona dopóki użytkownik nie wpisze któregoś z tych dwóch znaków. Potrzebna do wczytywania danych od użytkownika
bool checkInput();
///Funkcja sprawdzajaca czy string składa się z dokładnie tylu cyfr i tylko z cyfr
///@param numOfDigits - ilu cyfrową liczbą powien być nasz string
///@param str - string, który należy sprawdzić
bool checkIfDigit(int numOfDigits, std::string str);
///Funkcja sprawdzająca czy int ma dokładnie taką długość jak podana w parametrze
///@param num - liczba, której długość należy sprawdzić
///@param length - długość, którą oczekujemy od num
bool checkIntLength (int num, int length);
///Funkcja, która zwraca liczbę spacji potrzebnych do dopisania za liczbą typu double (precyzja 2), aby w sumie było zajęte n znaków
///@param num - liczba, która będzie dopełniana do n znaków
///@param n - długość, do której ma zostać dopełniona liczba num
///@return liczba spacji, która jest potrzebna, aby dopełnić zapis liczby num do n znaków
int complementDoubleToNCharacters (double num, int n);
//Funkcja, która zwraca liczbę spacji potrzebnych do dopisania za liczbą typu int, aby w sumie było zajęte n znaków
///@param num - liczba, która będzie dopełniana do n znaków
///@param n - długość, do której ma zostać dopełniona liczba num
///@return liczba spacji, która jest potrzebna, aby dopełnić zapis liczby num do n znaków
int complementIntegerToNCharacters (int num, int n);
///Funkcja, która przycina string o wszystkie ostatnie spacje (skraca go o spacje) oraz usuwa n znaków z przodu
///@param str - referencja na string, na którym należy wykonać operacje
///@param n - liczba, ile znaków z przodu string należy usunąć
void shortenString (std::string& str, int n);
///Funkcja, która pobiera n znaków z obiektu klasy istream i zwraca string utworzony z tych znaków
std::string createNLengthString (std::istream& is, int n);
///Funkcja, która sprawdza czy string jest liczbą int
bool is_number(const std::string& s);
///Funkcja, która sprawdza czy string jest liczbą double
bool is_double(const std::string& s);




#endif /* GlobalFunctions_hpp */
