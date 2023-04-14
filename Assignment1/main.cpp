#include <iostream>
#include <vector>
#include "Bag.h"
#include "Menu.h"
using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    cout << "Bag" << endl;

    Menu menu;
    menu.Run();

    return 0;
}
#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Bag.h"
TEST_CASE("isEmpty()","[Bag]")
{
    Bag B1;
    CHECK( B1.isEmpty() == TRUE );

    B1.add(3);
    CHECK( B1.isEmpty() == FALSE );

    B1.removeElem(3);
    CHECK( B1.isEmpty() == TRUE );
}
TEST_CASE("add different elements only once","[Bag]")
{
    Bag B;

    {
        B.add(3);
        CHECK( 1 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( v[0].element == 3 );
        CHECK( v[0].frequency == 1 );
    }

    {
        B.add(4);B.add(2);B.add(5);B.add(1);
        CHECK( 5 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( 1 == v[0].element); CHECK( 2 == v[1].element); CHECK( 3 == v[2].element); CHECK( 4 == v[3].element); CHECK( 5 == v[4].element);
        CHECK( 1 == v[0].frequency);  CHECK( 1 == v[1].frequency);  CHECK( 1 == v[2].frequency);  CHECK( 1 == v[3].frequency);  CHECK( 1 == v[4].frequency);
    }
}
TEST_CASE("add different elements twice","[Bag]")
{
    Bag B;

    {
        B.add(3);
        B.add(3);
        CHECK( 1 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( v[0].element == 3 );
        CHECK( v[0].frequency == 2 );
    }

    {
        B.add(4);B.add(2);B.add(5);B.add(1);
        B.add(4);B.add(2);B.add(5);B.add(1);
        CHECK( 5 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( 1 == v[0].element); CHECK( 2 == v[1].element); CHECK( 3 == v[2].element); CHECK( 4 == v[3].element); CHECK( 5 == v[4].element);
        CHECK( 2 == v[0].frequency);  CHECK( 2 == v[1].frequency);  CHECK( 2 == v[2].frequency);  CHECK( 2 == v[3].frequency);  CHECK( 2 == v[4].frequency);
    }
}
TEST_CASE("add the same element more times","[Bag]")
{
    Bag B;

    {
        B.add(3);
        B.add(3);
        B.add(3);
        B.add(3);
        B.add(3);
        B.add(3);
        CHECK( 1 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( v[0].element == 3 );
        CHECK( v[0].frequency == 6 );
    }

}
TEST_CASE("add different elements with different frequency","[Bag]")
{
    Bag B;

    {
        B.add(3);
        B.add(3);
        CHECK( 1 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( v[0].element == 3 );
        CHECK( v[0].frequency == 2 );
    }

    {
        B.add(4);B.add(2);B.add(5);B.add(1);B.add(1);
        B.add(2);B.add(5);B.add(1);B.add(1);
        B.add(2);B.add(5);B.add(5);B.add(1);
        CHECK( 5 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( 1 == v[0].element); CHECK( 2 == v[1].element); CHECK( 3 == v[2].element); CHECK( 4 == v[3].element); CHECK( 5 == v[4].element);
        CHECK( 5 == v[0].frequency);  CHECK( 3 == v[1].frequency);  CHECK( 2 == v[2].frequency);  CHECK( 1 == v[3].frequency); CHECK( 4 == v[4].frequency);
    }
}
TEST_CASE("add different elements only once(same frequency) and remove them","[Bag]")
{
    Bag B;

    {
        B.add(3);
        CHECK( 1 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( v[0].element == 3 );
        CHECK( v[0].frequency == 1 );
        B.removeElem(3);
        CHECK( 0 == B.getLength());
    }

    {
        B.add(4);B.add(2);B.add(5);B.add(1);
        CHECK( 4 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( 1 == v[0].element); CHECK( 2 == v[1].element); CHECK( 4 == v[2].element); CHECK( 5 == v[3].element);
        CHECK( 1 == v[0].frequency);  CHECK( 1 == v[1].frequency); CHECK( 1 == v[2].frequency);  CHECK( 1 == v[3].frequency);
        B.removeElem(4);
        CHECK( 3 == B.getLength());
        B.removeElem(2);
        CHECK( 2 == B.getLength());
        B.removeElem(1);
        CHECK( 1 == B.getLength());
        B.removeElem(5);
        CHECK( 0 == B.getLength());

    }
}
TEST_CASE("throws error","[Bag]")
{
    Bag B;
    CHECK_THROWS(B.removeElem(4));
    CHECK_THROWS(B.largest());
    CHECK_THROWS(B.get_Freq(5));
    Bag B1;
    B.add(4);
    B.add(2);
    CHECK_THROWS(B1.removeElem(3));
    CHECK_THROWS(B1.get_Freq(6));

}
TEST_CASE("add different elements three times (same frequency) and remove them just one time","[Bag]")
{
    Bag B;

    {
        B.add(3);
        B.add(3);
        B.add(3);
        CHECK( 1 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( v[0].element == 3 );
        CHECK(B.get_Freq(3) == 3 );
        B.removeElem(3);
        CHECK( B.get_Freq(3) == 2 );
        CHECK( 1 == B.getLength());
    }

    {
        B.add(4);B.add(2);B.add(5);B.add(1);
        B.add(4);B.add(2);B.add(5);B.add(1);
        B.add(4);B.add(2);B.add(5);B.add(1);
        CHECK( 5 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( 1 == v[0].element); CHECK( 2 == v[1].element);CHECK( 3 == v[2].element); CHECK( 4 == v[3].element); CHECK( 5 == v[4].element);
        CHECK( B.get_Freq(3) == 2 );CHECK( B.get_Freq(4) == 3 );CHECK( B.get_Freq(1) == 3 );CHECK( B.get_Freq(2) == 3 );CHECK( B.get_Freq(5) == 3 );
        B.removeElem(4);
        CHECK( B.get_Freq(4) == 2 );
        CHECK( 5 == B.getLength());
        B.removeElem(2);
        CHECK( B.get_Freq(2) == 2);
        CHECK( 5 == B.getLength());
        B.removeElem(1);
        CHECK( B.get_Freq(1) == 2 );
        CHECK( 5 == B.getLength());
        B.removeElem(5);
        CHECK( B.get_Freq(5) == 2);
        CHECK( 5 == B.getLength());


    }

}
TEST_CASE("different numbers remove different times","[Bag]")
{

    Bag B;

    {
        B.add(7);
        B.add(7);
        B.add(7);
        B.add(7);
        CHECK( 1 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( v[0].element == 7 );
        CHECK(B.get_Freq(7) == 4 );
        B.removeElem(7);
        CHECK( B.get_Freq(7) == 3 );
        B.removeElem(7);
        CHECK( B.get_Freq(7) == 2 );
        CHECK( 1 == B.getLength());
    }

    {
        B.add(12);B.add(23);B.add(5);B.add(12);B.add(23);B.add(12);B.add(23);B.add(12);
        CHECK( 4 == B.getLength());
        vector<Item> v= B.getItems();
        CHECK( 5 == v[0].element); CHECK( 7 == v[1].element);CHECK( 12 == v[2].element); CHECK( 23 == v[3].element);
        CHECK( B.get_Freq(12) == 4 );CHECK( B.get_Freq(5) == 1 );CHECK( B.get_Freq(23) == 3 );
        B.removeElem(23);
        CHECK( B.get_Freq(23) == 2 );
        CHECK( 4 == B.getLength());
        B.removeElem(7);
        B.removeElem(7);
        CHECK( 3 == B.getLength());
        B.removeElem(12);
        B.removeElem(12);
        B.removeElem(12);
        CHECK( B.get_Freq(12) == 1);
        CHECK( 3 == B.getLength());
        B.removeElem(5);
        CHECK( 2 == B.getLength());


    }

}

TEST_CASE("Get the largest element","[Bag]")
{
    Bag B;
    B.add(6);
    CHECK(B.largest() == 6);
    B.add(8);
    CHECK(B.largest() == 8);
    B.add(12);
    CHECK(B.largest() == 12);
    B.add(12);
    CHECK(B.largest() == 12);
    B.removeElem(12);
    CHECK(B.largest() == 12);
    B.removeElem(12);
    CHECK(B.largest() == 8);
    B.removeElem(8);
    CHECK(B.largest() == 6);
    B.removeElem(6);
    CHECK( B.isEmpty() == TRUE );
}

TEST_CASE("Get frequency","[Bag]")
{
    Bag B;
    B.add(6);
    B.add(8);
    B.add(12);
    CHECK(B.get_Freq(6)== 1);
    CHECK(B.get_Freq(12)== 1);
    B.add(12);
    CHECK(B.get_Freq(12)== 2);
    B.removeElem(12);
    CHECK(B.get_Freq(12)== 1);
    B.add(6);
    CHECK(B.get_Freq(6)== 2);
    B.add(12);
    B.add(12);
    CHECK(B.get_Freq(12)== 3);
    CHECK(B.get_Freq(8)== 1);
    B.removeElem(6);
    B.removeElem(6);
    B.removeElem(12);
    B.removeElem(12);
    B.removeElem(12);
    B.removeElem(8);

    CHECK( B.isEmpty() == TRUE );
}








#endif // NORMAL_MODE
