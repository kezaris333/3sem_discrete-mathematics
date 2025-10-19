#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <sstream>


class Node {
public:
    char name;
    Node* down;
};



class Set {
public:
    char name_of_set;
    Set* right;
    Node *  first_element;
    char size;
    static Set * array_of_sets [26];

    // 6, 4, 3, 2(), 1, 11
    //5, 7, 8, 9, 10

    Set (char name);
    Set ();
    ~Set () noexcept;


    Node* add_element (char item); //3
    void remove_element (char item); //4
    bool equal (const Set & other) const; //11
    void print_elements () const;
    Set & copy (Set const & other); //без имени
    void clear_elements ();
    std::vector <std::vector<char>> boolean_set () const;
    Node * operator[](int i) const;

};


void printer_elements (const Set & myclass);
void printer_sets ();
void meld_union (const Set & one, const Set & two); //7
void meld_crossing (const Set & one, const Set & two); //8
void difference_set (const Set & one, const Set & two); //9
void is_subset (const Set & one, const Set & two); //10


