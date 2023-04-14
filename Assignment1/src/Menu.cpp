#include <iostream>
#include "Menu.h"
#include <sstream>
#define menuCount 6 //number of menu items

using namespace std;

void Menu::Run() {
    int value;
    do{
        value = MenuPrint();
        switch(value){
            case 1:
                putIn();            print(); break;
            case 2:
                takeOut();          print(); break;
            case 3:
                get_Frequency();    print(); break;
            case 4:
                get_Max();          print(); break;
            case 5:
                print();                     break;
            case 6:
                loadTest();                  break;
            default:
                cout<<"\nGoodbye!\n";
                break;
        }
    }while(value!=0);
}

int Menu::MenuPrint() {
    int choice;
    cout<<"\n****************************************\n";
    cout<<"0. Exit\n";
    cout<<"1. Put in\n";
    cout<<"2. Take out\n";
    cout<<"3. Get the frequency of an element\n";
    cout<<"4. Get the largest element\n";
    cout<<"5. Print the bag\n";
    cout<<"6. Load test (how many items we can put in the bag)\n";
    cout<<"****************************************\n";

    ostringstream s;
    s << "You should choose a number between 0 and " << menuCount<<"!";
    string errmsg = s.str();

    cout << "Choose a number from the menu: ";
    cin >> choice;
    if (choice > menuCount || choice < 0) cerr << errmsg << endl;

    return choice;
}
void Menu::putIn() {
        cout<<"Enter an element: ";
        int e;
        cin >> e;
        B.add(e);
        cout<<"Success!\n"<<endl;
}


void Menu::takeOut() {

    bool error = false;
    int element;
    cout << "Enter the element that you want to take out: ";
    cin >> element;
    try{
        B.removeElem(element);
        cout<<"Success!\n"<<endl;
    }
    catch(Bag::BagError err){
        error = true;
        if(err == Bag::EMPTY_BAG)
            cerr<<"Take out is unsuccessful, the bag is empty!\n";
        else if(err == Bag::NONEXISTING_ELEMENT_EXCEPTION){
            cerr<<"Take out is unsuccessful, the element does not exist!\n";
        }
         else   cerr<<"Unknown error.\n";
    }
}
void Menu::get_Frequency(){
    bool error = false;
    int element;
    cout << "Enter a element: ";
    cin >> element;

    try{
        int e;
        e = B.get_Freq(element);
        cout<<"The frequency of the element "<<element<<" is: "<<e<<endl;
    }
    catch(Bag::BagError err){
        error = true;
        if(err == Bag::NONEXISTING_ELEMENT_EXCEPTION){
            cerr<<"Getting the frequency is unsuccessful, the element does not exist!\n";
        }
        else if(err == Bag::EMPTY_BAG){
            cerr<<"Getting the frequency is unsuccessful, the bag is empty\n";
        }
        else   cerr<<"Unknown error.\n";
    }
}

void Menu::get_Max(){
    bool error = false;
    try{
        int maxi=B.largest();
        cout<<"The largest element is : "<<maxi<<endl;
    }
    catch(Bag::BagError err){
        error = true;
        if(err == Bag::EMPTY_BAG){
            cerr<<"Getting the largest element is unsuccessful, the bag is empty!\n";
        }
        else   cerr<<"Unknown error.\n";
    }
}

void Menu::print() { cout<<B; }

void Menu::loadTest() {

    const int size = 1000000000;
    Bag B;
    cout<<"Follow the current size of the Bag:\n";
    try{
        for(int i=1; i<size; ++i){

            if(i%1000000==0) cout<<i<<endl;
            B.add(i);
        }
    }catch(...)
    {
        cout<<"The size of the Bag: "<<B.getLength()<<endl;
    }
}



