#include "Bag.h"

using namespace std;

pair<bool,int> Bag::logSearch(int element) const{    //taken from lab

    bool exists = false;
    int lowerBound = 0;
    int upperBound = items.size()-1;
    int middlePoint;

    while (!exists && lowerBound <= upperBound){

        middlePoint = (lowerBound + upperBound) / 2;
        if (items[middlePoint].element>element) { upperBound = middlePoint - 1; }
        else if (items[middlePoint].element<element) { lowerBound = middlePoint + 1; }
        else { exists = true; }
    }
    if (!exists) middlePoint = lowerBound;

    return pair<bool,int>(exists,middlePoint);
}

void Bag::add(int element){

    pair<bool,int> out = logSearch(element);

    if (!out.first){ // if an element doesn't exist in the bag
        Item e;
        e.element=element;

        items.resize(items.size()+1);
        e.frequency = 1;


        for (int i = items.size() - 2; i >= out.second; i--)
         items[i+1] = items[i];

        items[out.second] = e;
    }
    else if (out.first){//if element exist
        items[out.second].frequency++;

    }

}

void Bag::removeElem(int element) throw (BagError) {

    if(items.size() == 0){//if bag is empty
        throw EMPTY_BAG;
    }

    std::pair<bool,int> out = logSearch(element);

    if ((out.first) && (items[out.second].frequency == 1)) { //if element exists and its frequency is 1
           for (unsigned int i=out.second+1;i<items.size();i++)
           items[i-1] = items[i];
           items.pop_back();
    }
    else if( (out.first) && (items[out.second].frequency > 1)){//if element exists and its frequency is greater than 1
            items[out.second].frequency--;
         }
    else  throw NONEXISTING_ELEMENT_EXCEPTION;//otherwise the element does not exist(it is not in the bag)

}

int Bag::largest() const throw (BagError){
    if (items.size() != 0){//if the bag is not empty
        Item largest = items[items.size()-1];
        return largest.element;
    }
    else throw EMPTY_BAG;//if it is empty
}

int Bag::get_Freq(int element) throw (BagError) { //return frequency

    if(items.size() == 0){//if bag is empty
        throw EMPTY_BAG;
    }
    pair<bool,int> out = logSearch(element);

    if (out.first) {//if the element exists
        return items[out.second].frequency;
    }
    else throw NONEXISTING_ELEMENT_EXCEPTION;//if the element does not exist

}



ostream& operator<<(std::ostream& s, const Bag &b) {

    s << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    s << "Number of elements: " << b.items.size() << "\nContent: " << endl;
    for(unsigned i = 0; i < b.items.size(); i++){
        s << " " << b.items[i];
    }
    s << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
    return s;
}

std::vector<Item> Bag::getItems() const {

    std::vector<Item> v;
    for(unsigned i=0; i<items.size(); ++i) v.push_back(items[i]);

    return v;
}
