#include <iostream>
#include "seqinfileenumerator.hpp"
#include "stringstreamenumerator.hpp"
#include "maxsearch.hpp"
#include "summation.hpp"
#include "linsearch.hpp"

using namespace std;

///TO DOs
///For Task 1:Count the number of fishes for each angler and return the max
///For Task 2:Count the number of fishes for each contest and return the count of those that had zero

struct Pair
{
  string fish;
  int size;
  friend istream& operator>>(istream& is, Pair &p)
  {
      is >> p.fish >> p.size;
      return is;
  }
};

class counting : public Summation<Pair, int>
{
protected:
    int func(const Pair& e) const override
    {
        return 1;
    }
    int neutral() const override { return 0; }
    int add( const int& a, const int& b) const override
    {
        return a + b;
    }
};

struct Angler
{
    string name;
    string competition;
    int fishes;

    friend istream& operator>>(istream& inp, Angler &a);
};


istream& operator>>(istream& inp, Angler &a)
{
    string line;
    getline(inp, line, '\n');
    stringstream is(line);
    is >> a.name;
    is >> a.competition;
    counting pr;
    StringStreamEnumerator<Pair> enor(is);
    pr.addEnumerator(&enor);

    pr.run();

    if (pr.result() > 0) { a.fishes = pr.result(); }
    else { a.fishes = 0; }

    return inp;
}

class BestAngler : public MaxSearch<Angler, int>
{
protected:
    int func(const Angler& e) const override
    {
        return e.fishes;
    }
};

///Task2

struct ContestID{
    string name;
    int noFishesCount;

    ContestID(): name(""),noFishesCount(0) {}
    ContestID (const string &n,int cnt) : name(n),noFishesCount(cnt) {}

};

class contestResult : public Summation <Angler,ContestID>{
public:
    contestResult(const string &contestid) : contestid(contestid){}
private:
    string contestid;
    ContestID func(const  Angler &e)const override {
        return ContestID(e.competition,e.fishes);
    }

    ContestID neutral() const override {return ContestID();}
    ContestID add(const ContestID &a, const ContestID &b)const override{
        return ContestID(
            b.name,a.noFishesCount + b.noFishesCount);
    }
    void first() override{}
    bool whileCond (const Angler& current) const override{
        return current.competition == contestid;
    }
};

class ContestEnumerator : public Enumerator<ContestID>{
private:
    SeqInFileEnumerator<Angler>*f;
    ContestID c;
    bool m_end;
    bool empty;
public:
    ContestEnumerator(const string &fname) : empty(true){
        f = new SeqInFileEnumerator<Angler>(fname);
    }
    ~ContestEnumerator(){delete f;}
    void first() override {f->first(); next();
           if(!end()) empty = false;
    }
    void next() override;
    ContestID current() const override {return c;}
    bool end() const override {return m_end;}

    bool isEmpty() const {return empty;}

};

void ContestEnumerator :: next(){
    if(m_end = f->end()){
        return;
    }
    c.name = f->current().competition;
    contestResult pr(c.name);
    pr.addEnumerator(f);
    pr.run();
    c = pr.result();


}

class counting2 : public Summation<ContestID, int>
{
protected:
    int func(const ContestID& e) const override
    {
        return 1;
    }
    int neutral() const override { return 0; }
    int add( const int& a, const int& b) const override
    {
        return a + b;
    }
    bool cond(const ContestID &e)const override{
        return e.noFishesCount == 0;
    }
};

int main()
{
    try
    {
        BestAngler pr;
        SeqInFileEnumerator<Angler> myenor("input.txt");
        pr.addEnumerator(&myenor);

        pr.run();

        if (pr.found())
        {
            cout<<"First task:"<<endl;
            cout << "The angler who has caught the most fishes in one contest is:  " << pr.optElem().name << ", whose number of fishes is: " << pr.opt() <<" ,in the contest with ID: "<<pr.optElem().competition<< endl;
        }
        else { cout << "Empty file the first task cannot be solved!\n"; }

        ContestEnumerator enor("input.txt");
        counting2 pr2;
        pr2.addEnumerator(&enor);
        pr2.run();
        cout<<endl;
        cout<<"Second task:"<<endl;
        cout << "The number of contests where no fishes were caught: ";
        cout<<pr2.result()<<endl;
    }
    catch (SeqInFileEnumerator<Angler>::Exceptions exc)
    {
        cout << "File does not exist!\n";
        return 1;
    }

    return 0;
}
