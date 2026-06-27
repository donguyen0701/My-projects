#include "communicator.h"
#include "Manager.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    while (true) {
        int option;
        cout << "\n\n\n\n\n\nSelect an operation mode: \n1 - Component identifier\n2 - Component edit\n3 - Checkout mode\n4 - Storage manager\n5 - Exit\n\n-> ";
        cin >> option;
        if (option == 1) {
            cout << "Put the component under the camera...\n";
            cout << "Scanning for item...\n";
            string tag = getComp();
            Product prd(tag);
            cout << "\n--------------------\nPredicted item: " << prd.getName() << "\n";
            cout << "Quick description: " << prd.getDesc() << "\nPrice: " << prd.getPrice() << "\n";

            cin.ignore(); cin.get();
        }
        else if (option == 2) {
            string tag;
            while (true) {
                cout << "Put the component under the camera...\n";
                cout << "Scanning for item...\n";
                tag = getComp();
                cout << "\nPredicted item: " << tag << "\nEnter '1' to change description, '2' to change price, '3' to rescan:\n-> ";
                int choice; cin.ignore(); cin >> choice;
                if (choice == 3) continue;
                Product prd(tag);
                if (choice == 1) {
                    string newval;
                    cin.ignore();
                    cout << "Enter new description: "; getline(cin, newval);
                    prd.editDesc(newval);
                    cout << "The description of <" << prd.getName() << "> has been modified\n";
                }
                if (choice == 2) {
                    int newval;
                    cout << "Enter new price: "; cin >> newval;
                    prd.editPrice(newval);
                    cout << "The price of <" << prd.getName() << "> is now " << prd.getPrice() << "\n";
                }
                break;
            }
            cin.ignore();cin.get();
        }
        else if (option == 3) {
            vector<Product> einkaufsliste;
            int total = 0;
            while (true) {
                cout << "Current Basket:\t<" << einkaufsliste.size() << "> item(s)\tTotal price: " << total << "\n";
                cout << "Pick an option:\n1 - Show basket\n2 - Add item to basket\n3 - Remove item\n4 - Checkout\n-> ";
                int mode; cin >> mode;
                if (mode == 1 || mode == 3 || mode ==4) {
                    if (mode == 4) cout << "Final list:\n";
                    cout << "No.\t\tName\t\tPrice\n";
                    for (int i=0; i<einkaufsliste.size(); i++) {
                        cout << i+1 << "\t\t" << einkaufsliste[i].getName() << "\t\t" << einkaufsliste[i].getPrice() << "\n";
                    }
                    if (mode == 3) {
                        cout << "Enter the index of the item to be removed\n-> ";
                        int index; cin >> index;
                        total -= einkaufsliste[index].getPrice();
                        einkaufsliste.erase(einkaufsliste.begin() + index);
                        cout << "Item deleted!";
                        cin.ignore(); cin.get();
                        continue;
                    }
                    if (mode == 4 || mode ==1) {
                        cout << "Total basket price: " << total << "\nPress any key to continue";
                        cin.ignore(); cin.get();
                        if (mode == 4) break;

                    }

                }
                else if (mode == 2) {
                    while (true) {
                        cout << "Put the component under the camera...\n";
                        cout << "Scanning for item...\n";
                        string tag = getComp();
                        cout << "\nPredicted item: " << tag << "\nEnter '1' recans, '2' to accept\n-> ";
                        int choice; cin.ignore(); cin >> choice;
                        if (choice == 2) {
                            Product add(tag);
                            einkaufsliste.push_back(add);
                            total += add.getPrice();
                            break;
                        }
                    }
                }
            }
        }
        else if (option == 4) {
            while (true) {
                int modeS, NumWH, NumSlot;
                Product nll;
                ifstream fileP("Location.txt");
                fileP >> NumWH >> NumSlot;
                // cout << NumWH << " " << NumSlot << "\n";
                vector<vector<Product>> Storage; Storage.resize(NumWH);
                for (int i=0; i<NumWH; i++) {
                    Storage[i].resize(NumSlot);
                    for (int j=0; j<NumSlot; j++) Storage[i][j] = nll;
                }
                string item;
                while (fileP >> item) {
                    // cout << item << "---ooooo---";
                    int cordX, cordY;
                    fileP >> cordX >> cordY;
                    Product tmp(item);
                    Storage[cordX][cordY] = tmp;
                }
                fileP.close();
                cout << "Pick a mode: \n1 - Show map\n2 - Add/Move item\n-> "; cin >> modeS;
                if (modeS == 1) {
                    cout << "\t\t\t";
                    for (int j=0; j<NumSlot; j++) cout << j << "\t\t";
                    cout << "\n";
                    for (int i=0; i<NumWH; i++) {
                        cout << "Storage " << char(65+i) << "\t";
                        for (int j=0; j<NumSlot; j++) {
                            cout << Storage[i][j].getName().substr(0, 3) << "\t\t";
                        }
                        cout << "\n";
                    }
                    for (int i=0; i<NumWH; i++) {
                        for (int j=0; j<NumSlot; j++) {
                            if (Storage[i][j].getName() != "-") {
                                cout << Storage[i][j].getName().substr(0, 3) << "\t\t" << Storage[i][j].getName() << "\n";
                            }
                        }
                    }
                    cin.ignore(); cin.get();
                }
                else if (modeS == 2) {
                    // cout << "";
                    cout << "Enter component name: ";
                    string tag;
                    cin.ignore(); getline(cin, tag);
                    while (true) {
                        char SName;
                        cout << "Enter the storage (A->Z): "; cin >> SName;
                        int posx = int(SName-'A');
                        int posy;
                        cout << "Enter the storage slot: "; cin >> posy;
                        if (Storage[posx][posy].getName() == "-") {
                            for (int i=0; i<NumWH; i++) {
                                for (int j=0; j<NumSlot; j++) {
                                    if (Storage[i][j].getName() == tag) Storage[i][j] = nll;
                                }
                            }
                            Product newsign(tag);
                            Storage[posx][posy] = newsign;
                            break;
                        }
                        else cout << "Invalid location! Try again...";
                        cin.ignore(); cin.get();
                    }
                    ofstream fileO("Location.txt");
                    fileO << NumWH << " " << NumSlot << "\n";
                    for (int i=0; i<NumWH; i++) {
                        for (int j=0; j<NumSlot; j++) {
                            if (Storage[i][j].getName() != "-") {
                                fileO << Storage[i][j].getName() << "\n" << i << " " << j << "\n";
                            }
                        }
                    }
                    fileO.close();
                }
                else {
                    break;
                }
            }
        }
        else if (option == 5) break;
        else cout << "\n\n\nInvalid option, please try again.\n";
    }

    return 0;
}