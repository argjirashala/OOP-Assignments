#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "Bag.h"
class Menu
{
    public:
        Menu(){};
        void Run();
    private:
        int MenuPrint();
        void putIn();
        void takeOut();
        void get_Frequency();
        void get_Max();
        void print();
        void loadTest();
        Bag B;

};


#endif // MENU_H_INCLUDED

