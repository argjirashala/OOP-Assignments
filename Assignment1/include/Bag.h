#ifndef BAG_H
#define BAG_H
#include <string>
#include <iostream>
#include <vector>
struct Item {

    int element;
    int frequency;

    Item()
    {
        this->element = 0;
        this->frequency = 0;
    };

    Item(int elem,int freq):element(elem), frequency(freq) {}

    friend std::ostream &operator<<(std::ostream &os, const Item &item) {

        os<<"( element: " << item.element << " frequency: " << item.frequency<< " )";
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Item &item) {

        std::cout<<"Element >>> ";
        is >> item.element;
        return is;
    }

    bool operator==(const Item &leftHandSideItem) {
        return (element == leftHandSideItem.element,frequency == leftHandSideItem.frequency);
    }
};

class Bag
{
    public:
         enum BagError {
            EMPTY_BAG,NONEXISTING_ELEMENT_EXCEPTION
        };

        void add(int a); // add an element to the bag
        void removeElem(int e) throw (BagError);//remove an element
        int largest() const throw (BagError); //get the largest element
        int get_Freq(int element) throw (BagError);//return the frequency of an element
        bool isEmpty() {return items.size() == 0;}//just for testing

        //virtual ~Bag();
        friend std::ostream& operator<<(std::ostream& os, const Bag &b);
        unsigned int getLength() const {return items.size();}
        std::vector<Item> getItems() const;


    //protected:

    private:
        std::vector<Item> items;
        std::pair<bool,int> logSearch(int element) const;
};

#endif // BAG_H
