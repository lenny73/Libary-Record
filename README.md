# Libary-Record
The ItemRecord class maintains books and other media records for a library. Its attributes include the title(string), price(double), rating(char: 'A'-'D' in descending popularity). The operations include:
a constructor that takes default values ("placeholder", 0.99, 'D'), and checks for invariants (negative price, invalid rating letters, etc)
individual getters that return the item's title, price, and rating
overloaded “<<” operator which outputs the title only, implemented as a friend function (this function only)
overloaded “==” operator which only compares the item's rating
setPrice(double), which throws a range_error exception with the message “negative price”, if the double value < 0.
a pure virtual function, to_string(), that's meant to return a string of the description of the whole record
a virtual destructor
Implement the class using inline functions except for setPrice, for which you should use an external function.

Now, derive two classes from ItemRecord, and name them BookRecord and CdRecord. The differences are as follows:
BookRecord has an extra data field, int* chPages, which is implemented as a dynamic array of integers, i.e. its contents are the numbers of pages for the preface (index 0), chapter 1 (index 1), and so on
CdRecord has a different extra data field, double* trackTimes, which is implemented as a dynamic array of doubles, i.e. its contents are numbers of minutes of track 1 (index 0), track 2 (index 1), and so on
you may have to keep the size of these data fields
Implement both derived classes, and specifically,
In both constructors, take the same default values, and you can accept a vector of int/double for initialization of the new data fields which could be empty for their default values
you must release resource properly
for simplicity's sake, copy constructor/assignment can be omitted here, though they are absolutely required for these classes in production code because you can't copy pointers (one of the data members is a pointer)
make sure that the to_string() function can display the total # of pages for BookRecord and total play time for CdRecord, like the follows
Book[title, price, rating, total # of pages]
CD[title, price, rating, total play time in minutes] 

Then write some user code in your main() to test your classes:
instantiate an example of both a book and a cd, using the following:
book1: title: "SampleBook", price: 10.99, rating: 'A', # of pages by chapter: {2, 20, 30, 40, 30, 20}.
cd1: title: "SampleCD", price: 14.99, rating: 'B', play times by track: {4.5, 15.0, 23.5, 4.3, 5.2, 20.3}.
display their individual titles by using your overloaded <<
reduce each item's price by $1, using setPrice()
show whether these two items have the same rating by using your overloaded ==
make an array of ItemRecord* to store the two items, then iteratively call the to_string() function using the pointer to display their detail
this is an example of run-time polymorphism
Example output
My book's title is: SampleBook
My CD's title is: SampleCD
Do they have the same rating? No

Their details in [title, price, rating, total pages/minutes]:
Book[ SampleBook, 9.99, A, 142 ]
CD[ SampleCD, 13.99, B, 72.8 ]
