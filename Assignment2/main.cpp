#include <iostream>
#include <fstream>
#include <vector>
#include "Plants.h"
#include "Radiation.h"

using namespace std;

void read(const string &filename, vector<Plants*> &plants, int &days) {
    ifstream f(filename);
    if(f.fail()) {
        cout << "Something is wrong with the file!\n";
        exit(1);
    }
    int n; f >> n;
    plants.resize(n);
    for( int i=0; i<n; ++i ){
        string ch; string name; int p;
        f >> name >> ch >> p;
        if (ch == "wom") {
            plants[i] = new Wombleroot(name, p);
        }
        if (ch == "wit") {
            plants[i] = new Wittentoot(name, p);
        }
        if (ch == "wor")  {
            plants[i] = new Woreroot(name, p);
        }
    }
    f >> days;
}
void destroy(vector<Plants*> &plants)
{
    for(int i=0; i<(int)plants.size(); ++i) delete plants[i];
}

int findMaxOfAlivePlants(vector<Plants*> &plants){
int max=0;
for (unsigned int i=0;i<plants.size();i++)
{
    if(plants[i]->alive() && plants[i]->getNutrient() > max)
    {
        max=plants[i]->getNutrient();
    }
}
return max;
}

int stillAlive(vector<Plants*> &plants, int &days,vector<string>&alive){
    alive.clear();
    Radiation *rad = noRadiation::instance();
    cout << "Data from file: " << endl;
    for (int k = 0; k < plants.size(); k++) {
            cout << plants[k]->getName() << " " << plants[k]->getNutrient() << endl;
    }
    for (int j = 0; j < days; j++) {
        int delta = 0;
        int alpha = 0;
        for(unsigned int i = 0; i < plants.size(); i++) {
            plants[i]->changeRad(rad);
            if (plants[i]->getNutrient() > 10) {
                plants[i]->changeNutritient(-plants[i]->getNutrient());
                continue;
            }
            if (plants[i]->getType() == "wom" && plants[i]->alive()) {
                alpha += 10;
            }
            if (plants[i]->getType() == "wit" && plants[i]->getNutrient() < 5 && plants[i]->alive()) {
                delta += 4;
            }
            if (plants[i]->getType() == "wit" && plants[i]->getNutrient() >= 5 && plants[i]->getNutrient() < 10 && plants[i]->alive()) {
                delta += 1;
            }
        }
        if (delta >= alpha + 3) {
            rad = Delta::instance();
            cout<<endl;
            cout<<"Delta radiation: "<<delta;
        }else if (delta + 3 <= alpha) {
            rad = Alpha::instance();
            cout<<endl;
            cout<<"Alpha radiation: "<<alpha;
        }else{
            rad = noRadiation::instance();
            cout<<endl;
            cout<<"no radiation";
        }
        cout << "\nDay: " << j + 1 << endl;
        for (int k = 0; k < plants.size(); k++) {
            if (plants[k]->alive()) {
                cout << plants[k]->getName() << " " << plants[k]->getNutrient() << endl;
            }
        }
    }
         cout<<endl;
     int maxNutrient=findMaxOfAlivePlants(plants);
     if (maxNutrient==0){
            cout<<"No alive plants"<<endl;
            return 0;
            }
     else{
            for (unsigned int i=0;i<plants.size();i++){
             if(plants[i]->getNutrient()== maxNutrient){
                cout<<"The plant who is still alive with max nutrient: "<<plants[i]->getName()<<" "<<plants[i]->getNutrient()<<endl;

            }
        }
        return maxNutrient;
    }
}
// To change between the manual and the unit test mode
//#define NORMAL_MODE
#ifdef NORMAL_MODE
int main()
{
    vector<Plants*> plants;
    int days;
    vector<string> alive;
    read("inp.txt", plants, days);
    stillAlive(plants, days, alive);
    destroy(plants);
    return 0;
}


#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1", "only one day,no radiation,all plants alive")
{
     vector<Plants*> plants;
     int days;
     vector<string> alive;
     read("test1.txt",plants,days);
     CHECK(plants.size()== 4);
     CHECK(stillAlive(plants,days,alive)==6);
     CHECK(plants[0]->alive()== true);
     CHECK(plants[1]->alive()== true);
     CHECK(plants[2]->alive()== true);
     CHECK(plants[3]->alive()== true);

}

TEST_CASE("2", "more days,different radiations,one plant dies")
{
     vector<Plants*> plants;
     int days;
     vector<string> alive;
     read("test2.txt",plants,days);
     CHECK(plants.size()== 3);
     CHECK(stillAlive(plants,days,alive)==6);
     CHECK(plants[0]->alive()== false);
     CHECK(plants[1]->alive()== true);
     CHECK(plants[2]->alive()== true);


}

TEST_CASE("3", "more days,different radiations,all plants alive")
{
     vector<Plants*> plants;
     int days;
     vector<string> alive;
     read("test3.txt",plants,days);
     CHECK(plants.size()== 3);
     CHECK(stillAlive(plants,days,alive)==7);
     CHECK(plants[0]->alive()== true);
     CHECK(plants[1]->alive()== true);
     CHECK(plants[2]->alive()== true);

}

TEST_CASE("4", "more days,different radiations,more than one plant dies")
{
     vector<Plants*> plants;
     int days;
     vector<string> alive;
     read("test4.txt",plants,days);
     CHECK(plants.size()== 5);
     CHECK(stillAlive(plants,days,alive)==7);
     CHECK(plants[0]->alive()== true);
     CHECK(plants[1]->alive()== false);
     CHECK(plants[2]->alive()== true);
     CHECK(plants[3]->alive()== false);
     CHECK(plants[4]->alive()== false);

}

TEST_CASE("5", "more days,different radiations,wombleroot dies")
{
     vector<Plants*> plants;
     int days;
     vector<string> alive;
     read("test5.txt",plants,days);
     CHECK(plants.size()== 3);
     CHECK(stillAlive(plants,days,alive)==6);
     CHECK(plants[0]->alive()== false);
     CHECK(plants[1]->alive()== true);
     CHECK(plants[2]->alive()== true);

}

TEST_CASE("6", "more days,all plants die")
{
     vector<Plants*> plants;
     int days;
     vector<string> alive;
     read("test6.txt",plants,days);
     CHECK(plants.size()== 5);
     CHECK(stillAlive(plants,days,alive)==0);
     CHECK(plants[0]->alive()== false);
     CHECK(plants[1]->alive()== false);
     CHECK(plants[2]->alive()== false);
     CHECK(plants[3]->alive()== false);
     CHECK(plants[4]->alive()== false);

}
TEST_CASE("7", "empty file")
{
     vector<Plants*> plants;
     int days;
     vector<string> alive;
     read("test7.txt",plants,days);
     CHECK(stillAlive(plants,days,alive)==0);

}




#endif // NORMAL_MODE



