//
//  ListMB.h
//  PetShop
//
//  Created by Marcin Badach on 30/12/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef ListMB_h
#define ListMB_h
#include <stdio.h>
#include <string>
#include <vector>
#include "GlobalFunctions.hpp"
#include <iomanip>

///WEZEŁ
template <typename T>
class NodeMB {
    std::chrono::milliseconds timeElapsed;
    NodeMB<T> * next;
    T nodeData;
public:
    ///konstruktor
    NodeMB(std::chrono::milliseconds refTime, T nodeDataArg);
    ///zwraca referencje na next
    NodeMB<T>*& getNext();
    ///zwraca referencje na dane
    T& getNodeData();
    ///zwraca czas inicjalizacji w milisekundach
    std::chrono::milliseconds& getTimeElapsed();
    
};

template<typename T>
NodeMB<T>::NodeMB(std::chrono::milliseconds refTime, T nodeDataArg) {
    timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - refTime;
    nodeData = nodeDataArg;
}

template<typename T>
NodeMB<T>*& NodeMB<T>::getNext() {
    return next;
}

template<typename T>
T& NodeMB<T>::getNodeData() {
    return nodeData;
}

template<typename T>
std::chrono::milliseconds& NodeMB<T>::getTimeElapsed () {
    return timeElapsed;
}






///LISTA
template <typename T>
class ListMB {
    std::chrono::milliseconds timeOfInit;
    NodeMB<T> * listHead;
    NodeMB<T> * listTail;
    unsigned int length;
    
public:
    ///konstruktor
    ListMB();
    ///konstruktor kopiujący
    ListMB(ListMB<T>& lArg);
    ///dekonstruktor
    ~ListMB();
    ///zwraca długość listy
    int getLength();
    ///zwraca czas inicjalizacji w milisekundach
    std::chrono::milliseconds& getTimeOfInit();
    ///pushBack
    void pushBack(T pb);
    ///pushFront
    void pushFront(T pb);
    ///pozwala dodać daną do listy na indeks n (następne przesuwa na indeks o 1 większy)
    ///jeśli n jest większy równy długości listy, to dana pb zostaje dodana na koniec listy
    ///jeśli n jest mniejszy od zera, dana pb zostaje dodana na początek
    void pushData(T pb, int n);
    ///usuwa ostatni element
    void popBack();
    ///usuwa pierwszy element
    void popFront();
    ///pozwala usunąć daną z listy na indeksie n (następne przesuwa na indeks o 1 mniejszy)
    ///jeśli n jest większy równy długości listy, to usunięty zostaje ostatni element z listy
    ///jeśli n <= 0 to usunięty zostaje pierwszy element listy
    void popData(int n);
//    ///wyświetla ostatni
//    void coutLast();
    ///operator indeksowania
    NodeMB<T>& operator[](int n);
    ///operator przypisania
    ListMB<T>& operator= (ListMB<T>& list2);
};


template <typename T>
ListMB<T>::ListMB() {
    timeOfInit = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    listHead = nullptr;
    listTail = nullptr;
    length = 0;
}

template <typename T>
ListMB<T>::ListMB(ListMB<T>& lArg) {
    timeOfInit = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    
    int length1 = lArg.getLength();
    ///dodaje węzły z odpowiednimi wartościami
    for (int i = 0; i < length1; i++)
        pushBack(lArg[i].getNodeData());
    return *this;
}

template<typename T>
ListMB<T>::~ListMB<T>() {
    int length1 = length;
    for(int i = 1; i < length1; i++)
        popBack();
}


template <typename T>
int ListMB<T>::getLength() {
    return length;
}

template <typename T>
std::chrono::milliseconds& ListMB<T>::getTimeOfInit() {
    return timeOfInit;
}

template <typename T>
void ListMB<T>::pushBack(T pb) {
    NodeMB<T> * newEl = new NodeMB<T>(timeOfInit, pb);
    if (length == 0) {
        listTail = newEl;
        listHead = newEl;
    }
    else {
        (listTail -> getNext()) = newEl;
        listTail = newEl;
    }
    ++length;
}

template <typename T>
void ListMB<T>::pushFront(T pb) {
    NodeMB<T> * newEl = new NodeMB<T>(timeOfInit, pb);
    if (length == 0) {
        listTail = newEl;
        listHead = newEl;
    }
    else {
        newEl -> getNext() = listHead;
        listHead = newEl;
    }
    ++length;
}

template<typename T>
void ListMB<T>::pushData(T pb, int n) {
    if (n >= length) {
        pushBack(pb);
    }
    else if (n <= 0) {
        pushFront(pb);
    }
    else {
        NodeMB<T> * newEl = new NodeMB<T>(timeOfInit, pb);
        newEl -> getNext() = (*this)[n-1].getNext();
        (*this)[n-1].getNext() = newEl;
        ++length;
    }
}

template<typename T>
void ListMB<T>::popBack() {
    if (length == 0)
        return;
    else if (length == 1) {
        delete listTail;
        listHead = nullptr;
        listTail = nullptr;
        --length;
    }
    else {
        delete ((*this)[length - 2].getNext());
        ((*this)[length - 2].getNext()) = nullptr;
        listTail = &((*this)[length - 2]);
        --length;
    }
}

template<typename T>
void ListMB<T>::popFront() {
    if (length == 0)
        return;
    else if (length == 1) {
        delete listHead;
        listHead = nullptr;
        listTail = nullptr;
        --length;
    }
    else {
        NodeMB<T> * temp = listHead;
        listHead = &((*this)[1]);
        delete temp;
        --length;
    }
}

template<typename T>
void ListMB<T>::popData(int n) {
    if (n >= length - 1) {
        popBack();
    }
    else if (n <= 0) {
        popFront();
    }
    else {
        NodeMB<T> * temp = (*this)[n - 1].getNext();
        (*this)[n - 1].getNext() = (*this)[n].getNext();
        delete temp;
        --length;
    }
}

//template<typename T>
//void ListMB<T>::coutLast() {
//    std::cout << listTail -> nodeData;
//    std::cout << std::endl << listHead -> nodeData;
//    std::cout << std::endl << (listHead -> timeElapsed).count();
//    std::cout << std::endl << (listTail -> timeElapsed).count();
//    std::cout << std::endl;
//    std::cout << timeOfInit.count();
//}

template<typename T>
NodeMB<T>& ListMB<T>::operator[](int n) {
    if (n >= length) {
        std::cout << "List index out of bound, exiting." << std::endl;
        exit(0);
    }
    NodeMB<T> * temp;
    temp = listHead;
    for (int i = 0; i < n; i++) {
        temp = temp -> getNext();
    }
    return *temp;
}

template <typename T>
ListMB<T>& ListMB<T>::operator= (ListMB<T>& list2) {
    if (list2 == *this)
        return;
    
    int length1 = length;
    int length2 = list2.getLength();
    ///zeruje listę pierwszą
    for (int i = 0; i < length1; i++)
        popBack();
    ///dodaje węzły z odpowiednimi wartościami
    for (int i = 0; i < length2; i++)
        pushBack(list2[i].getNodeData());
    return *this;
}




#endif /* ListMB_h */

