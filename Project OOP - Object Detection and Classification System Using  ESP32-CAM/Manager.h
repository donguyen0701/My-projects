#ifndef MANAGER_H
#define MANAGER_H


#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>
#include<vector>
#include<sstream>

using namespace std;

class Product {
private:
    string desc, name;
    int price;
    int StoreX, StoreY;

public:
    //Constructor
    Product();
    Product(const string &str);

    //Functions
    string getName() const;
    string getDesc() const;
    int getPrice() const;
    void editPrice(const int &newP);
    void editDesc(const string &newDesc);
    void isValidLocation();

    //Operators
    Product& operator=(const string& str);
    // void isCorrectProduct();


};


#endif //MANAGER_H
