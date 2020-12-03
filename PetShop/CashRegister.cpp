//
//  CashRegister.cpp
//  PetShop
//
//  Created by Marcin Badach on 31/10/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "CashRegister.hpp"

CashRegister::CashRegister (double cashArg) {
    if (cashArg >= 0.0)
        cash = cashArg;
    else {
        std::cout << "Błędny stan kasy fiskalnej. Wartość ustawiona na 1000.0." << std::endl;
        cash = 1000.0;
    }
#ifdef _DEBUG
    std::cout << "Konstuktor kasy fiskalnej wywołany." << std::endl;
#endif
}

CashRegister::~CashRegister(){
    int n = static_cast<int>(receiptHistory.size());
    for (int i = 0; i < n; i++) {
        delete receiptHistory[i];
    }
#ifdef _DEBUG
    std::cout << "Dekonstuktor kasy fiskalnej wywołany." << std::endl;
#endif
}

double CashRegister::returnCash() {
    return cash;
}

int CashRegister::returnLength() {
    return static_cast<int>(receiptHistory.size());
}


bool CashRegister::spendCash(double n) {
    if (n > cash) {
        std::cout << "W kasie znajduje się za mało gotówki." << std::endl;
        return false;
    }
    else {
        cash -= n;
        return true;
    }
}

void CashRegister::collectCash (double c) {
    if (c < 0) {
        std::cout << "Błąd! Liczba pieniędzy wkładanych do kasy musi być nieujemmna." << std::endl;
        return;
    }
    cash += c;
}


void CashRegister::operator++() {
    Receipt * temp = new Receipt;
    receiptHistory.push_back(temp);
    std::cout << "Nowy paragon został stworzony." << std::endl;
}



Receipt& CashRegister::operator[](int index) {
    int maxIndex = static_cast<int>(receiptHistory.size()) - 1;
    if (maxIndex == -1) {
        std::cout << "Brak rozpoczętego paragonu. Stworzony paragon domyślny." << std::endl;
        maxIndex = 0;
    }
    if (index > maxIndex) {
        std::cout << "Brak paragonu o takim indexie. Zwrócono ostatni." << std::endl;
        return *receiptHistory[maxIndex];
    }
    if (index < 0) {
        std::cout << "Index paragonu musi być dodatni. Zwrócono najmniejszy." << std::endl;
        return *receiptHistory[0];
    }
    return *(receiptHistory[index]);
}

void CashRegister::productPushBack(Product * ptr) {
    int lastIndex = static_cast<int>(receiptHistory.size()) - 1;
    receiptHistory[lastIndex] -> addProduct(ptr);
}


std::ostream & operator<< (std::ostream & os, CashRegister & cr) {
    std::ifstream history;
    history.open("HISTORIA.txt");
    if (history.is_open()) {
        os << "Historia wcześniejszych transakcji: " << std::endl;
        os << history.rdbuf();
    }
    os << "Historia aktualnych transakcji:" << std::endl;
    int n = static_cast<int>(cr.receiptHistory.size());
    
    for (int i = 0; i < n; i++) {
        os << *(cr.receiptHistory[i]);
    }
    history.close();
    os << "GOTÓWKA W KASIE FISKALNEJ: " << cr.cash << std::endl;
    return os;
}




void CashRegister::saveInReceiptHistoryFile () {
    std::ofstream myfile;
    myfile.open("HISTORIA.TXT", std::ios::out | std::ios::app);
    int n = static_cast<int>(receiptHistory.size());
    if (!myfile.is_open()){
        std::ofstream newfile ("HISTORIA.txt");
        for (int i = 0; i < n; i++) {
            newfile << *(receiptHistory[i]) << std::endl;
        }
    }
    else {
        int n = static_cast<int>(receiptHistory.size());
        for (int i = 0; i < n; i++) {
            myfile << *(receiptHistory[i]) << std:: endl;
        }
    }
    myfile.close();
}

std::ostream& CashRegister::cashToOStream(std::ostream& os) {
    os << std::fixed;
    os << std::setprecision(2);
    os << "GOTÓWKA W KASIE FISKALNEJ: " << cash << std::string(complementDoubleToNCharacters(cash, 13), ' ');
    os << std::endl;
    return os;
}


std::ostream& CashRegister::cashRegisterToOStream (std::ostream& os) {
    saveInReceiptHistoryFile();
    cashToOStream(os);
    return os;
}

std::istream& operator>>(std::istream& is, CashRegister& cr) {
    std::string temp = createNLengthString(is, 12);
    shortenString(temp, 0);
    cr.cash = std::stod(temp);
    return is;
}
