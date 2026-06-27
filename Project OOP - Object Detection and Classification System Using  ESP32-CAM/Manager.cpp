#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>
#include<vector>
#include<sstream>
#include "Manager.h"


using namespace std;



Product::Product() {
	name = "-";
	price = -1;
	desc = "";
	StoreX = -1;
	StoreY = -1;
}
Product::Product(const string &str) {
	// desc = getDesc(str);
	// name = str;
	// price = getPrice(str);
	// cout << "hello world";

	//Get description
	ifstream file("Desc.txt"); // Open the file
	if (!file.is_open()) {            // Check if the file opened successfully
		std::cerr << "Error: Could not open the file." << std::endl;
	}

	string descScan;
	while (getline(file, descScan)){
		if(str == descScan) {
			getline(file, desc);
			break;
		}
		else getline(file, descScan);
	}
	file.close();

	name = str;

	// Get Price
	ifstream fileP("Price.txt"); // Open the file
	if (!fileP.is_open()) {            // Check if the file opened successfully
		std::cerr << "Error: Could not open the file." << std::endl;
	}
	price = -1;
	int temp;
	string val, num;
	while (getline(fileP, val)) {
		if(val == str) {
			fileP >> temp;
			price = temp;
			break;
		}
	}
	fileP.close();

	//Get Location
	ifstream filei("Location.txt"); // Open the file
	string item;
	while (filei >> item) {
		int cordX, cordY;
		fileP >> cordX >> cordY;
		if (item == str) {
			StoreX = cordX;
			StoreY = cordY;
		}
	}
	filei.close();

}

string Product::getName() const {
	return name;
}
string Product::getDesc() const{
	return desc;
}
int Product::getPrice() const{
	return price;
}

void Product::editPrice(const int &newP){
	ifstream filein("Price.txt"); // Open the file
	if (!filein.is_open()) {            // Check if the file opened successfully
		std::cerr << "Error: Could not open the file." << std::endl;
	}

	int cnt = 1, pos = -1;
	string item[100],temp;
	int val[100];
	do{
		if (filein.eof()) break;
		getline(filein, temp);
		if (cnt %2 != 0) {
			item[cnt/2] = temp;
			if (item[cnt/2] == name) pos = cnt/2;
		}
		else {
			val[(cnt/2)-1] = stoi(temp);
		}

	}while (cnt +=1);

	filein.close();

	if (pos > 0) {
		val[pos] = newP;
		price = newP;
	}

	ofstream outfile("Price.txt"); // Open the file
	for (int i = 0; i < cnt/2; i++) {
		if (i != 0) outfile << "\n";
		outfile << item[i] << "\n" << val[i];
	}
	outfile.close();

}
void Product::editDesc(const string &newDesc) {
	ifstream filein("Desc.txt"); // Open the file
	if (!filein.is_open()) {            // Check if the file opened successfully
		std::cerr << "Error: Could not open the file." << std::endl;
	}

	int cnt = 1, pos = -1;
	string item[100],temp;
	string val[100];
	do{
		if (filein.eof()) break;
		getline(filein, temp);
		if (cnt %2 != 0) {
			item[cnt/2] = temp;
			if (item[cnt/2] == name) pos = cnt/2;
		}
		else {
			val[(cnt/2)-1] = temp;
		}

	}while (cnt +=1);

	filein.close();

	if (pos > 0) {
		val[pos] = newDesc;
		desc = newDesc;
	}

	ofstream outfile("Desc.txt"); // Open the file
	for (int i = 0; i < cnt/2; i++) {
		if (i != 0) outfile << "\n";
		outfile << item[i] << "\n" << val[i];
	}
	outfile.close();
}

//Operators
Product& Product::operator=(const string& str) {
	Product temp(str);
	this->name = temp.name;
	this->desc = temp.desc;
	this->price = temp.price;
	return *this;
}


vector<vector<string>> getStorage() {
	vector<vector<string>> res;

}
