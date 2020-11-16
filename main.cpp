//Leonid Suchkov CISC3142 Assignment 4.2
#include<iostream>
#include<conio.h>
#include<vector>
#include<string>

using namespace std;

class ItemRecord{
protected:
    string title;
    double price;
    char rating;
public:
    ItemRecord(string s, double price,char rate);
    void setPrice(double p);
    void setRating(char c);
    //individual getters
    string getTitle();
    double getPrice();
    char getRating();
    //virtual to_string()
    virtual void to_string()=0;
    //overloaded getters
    string getTitle(const ItemRecord&);
    double getPrice(const ItemRecord&);
    char getRating(const ItemRecord&);
    //overloaded operator ==
    bool operator ==(ItemRecord&);
    //Virtual Desctuctor
    virtual ~ItemRecord();
};
//define outside constructor using scope operator::, takes default values
//also check invariants, negative price, invalid rating
ItemRecord::ItemRecord(string s="Place Holder", double price=99,char rate='D'){
    title=s;
    if(price<=0)
        throw range_error("Negative Price " + std::to_string(price));
    this->price=price;
    rate=toupper(rate);
    if(rate!='A' && rate != 'B' && rate != 'C' && rate != 'D')
        throw invalid_argument("Invalid Rating"  + rate);
    rating=rate;
}
ItemRecord::~ItemRecord(){}//Desctuctor

void ItemRecord::setPrice(double p){
    if(p<=0)
        throw range_error("Negative Price" + std::to_string(p));
    price=p;
}
void ItemRecord::setRating(char c){
    char rate=toupper(c);
    string frate="Invalid Rating ";
    frate.append(1,c);
    if(rate!='A' || rate != 'B' || rate != 'C' || rate != 'D')
        throw invalid_argument(frate);
    rating=rate;
}
//create individual getters and setters for title, price, rating
string ItemRecord::getTitle(){
    return title;
}
double ItemRecord::getPrice(){
    return price;
}
inline char ItemRecord::getRating(){
    return rating;
    //overloadedd getters for another object
}
string ItemRecord::getTitle(const ItemRecord& obj){
    return obj.title;
}
double ItemRecord::getPrice(const ItemRecord& obj){
    return obj.price;
}
inline char ItemRecord::getRating(const ItemRecord& obj){
    return obj.rating;
}
//create overloaded operator to compare items og rating
//overload == operator compare equality in all fields, only for ckeck for rating
bool ItemRecord::operator==(ItemRecord &obj){
    return this->rating==obj.rating;
}

//create class decrarations for Books callled BookRecord
class BookRecord:public ItemRecord{//all fuctionallity of ItemRecord is available in BookRecord
private:
    int* chPages;//a pointer to dynamic array,,store pages of every chapters
    int size;//store size of chPages dynamic array
public:
    //create constructor with default values , which used if values are not passed while creating object
   //using vector as a dynamic array is used as argument type and initialized to empty list
    BookRecord(string,double,char,const vector<int>&);
    //create destructor to delete created dynamic array after use has been over
    ~BookRecord();
    //overwrite, declare from virtual in base class
    void to_string();
};
//implement BookRecord class is member functions
BookRecord::BookRecord(string t,double price,char rate,const vector<int>& pages=vector<int>()):ItemRecord(t,price,rate){
    int lenth=pages.size();;
    chPages=new int[lenth];
    for(int i=0;i<lenth;i++)
        chPages[i]=pages[i];
    size=lenth;
}

//destructor dynamic array
BookRecord::~BookRecord(){
    delete[] chPages;
}
//display memeber variables values
void BookRecord::to_string(){
    int tPages=0;
    for(int i=0;i<size;i++)
        tPages+=chPages[i];
    cout << "Book[" << title << "," << price << "," << rating  << "," << tPages << "]" << endl;
}

//create class to maintaion cd records
//inherited from ItemRecord
class CdRecord:public ItemRecord{
private:

    //two memebers
    double* trackTimes;// store play times of ex]ach track in cd
    int size;//size of track dynamic array
public:

    //create constructors as tha same BookRecord
    CdRecord(string,double,char,const vector<double>&);
    ~CdRecord();
    void to_string();
};
CdRecord::CdRecord(string t="Place Holder",double price=99,char rate='D',const vector<double> &tracks=vector<double>()):ItemRecord(t,price,rate){
    int lenth=tracks.size();
    trackTimes=new double[lenth];
    for(int i=0;i<lenth;i++)
        trackTimes[i]=tracks[i];
    size=lenth;
}
CdRecord::~CdRecord(){
    if (trackTimes!=NULL)
//		for(int i=0;i<size,i++)
        delete[] trackTimes;
//	trackTimes=NULL;
}
void CdRecord::to_string(){
    double tTracks=0;
    for(int i = 0 ; i < size ; i++)
        tTracks += trackTimes[i];
    cout << "CD[" << title << "," << price << "," << rating  << "," << tTracks << "]" << endl;
}
int main(){
    //all statements with try cathch block
    try{
        //create a vector a dynamic container to store values
        vector<int> pages;
        vector<double> tracks;

        pages.push_back(2);
        pages.push_back(20);
        pages.push_back(30);
        pages.push_back(40);
        pages.push_back(30);
        pages.push_back(20);
        //create object for book
        BookRecord b1("Sample Book",10.99,'A',pages);
        pages.clear();//clear vector before filling with new book pages or cd paly times
        tracks.push_back(4.5);
        tracks.push_back(15.0);
        tracks.push_back(23.5);
        tracks.push_back(4.3);
        tracks.push_back(5.2);
        tracks.push_back(20.3);
        //create object for cd
        CdRecord c1("Sample CD",14.99,'A',tracks);
        //displaytitle of book and cd by using function getTitle()
        cout << "My book's title is: " << b1.getTitle() << endl;

        //use overloaded getTitle() function for cd
        cout << "My CD's title is: " << b1.getTitle(c1) << endl;
        //set price for both objects by 1 dollar
        b1.setPrice(b1.getPrice()-1);
        c1.setPrice(c1.getPrice()-1);
        cout << "Do you have the Same rating?";
        //compare both objects for equality by rating
        if(b1==c1)
            cout << " -Yes" << endl;
        else
            cout << " -No" << endl;
        //create array to store books and cd
        ItemRecord *items[2];
        items[0]=&b1;
        items[1]=&c1;

        //call to_string() using each iterator to display books and values.
        for(ItemRecord *i :items)
            i->to_string();
    }
    //if negative price enter then range_error
    catch(range_error &e){
        cerr << e.what() << endl;
        getch();
        return -1;
    }
    //if invalid rating character is assigned then invalid_argument error
    catch(invalid_argument &e){
        cerr << e.what() << endl;
        getch();
        return -1;
    }

    getch();
    return 0;
}
