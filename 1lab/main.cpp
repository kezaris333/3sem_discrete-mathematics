#include "libr.h"

Set* Set::array_of_sets[26] = {nullptr};

Set::Set (char name) : name_of_set (name), right (nullptr), first_element (nullptr), size (0) {
    if (name < 'A' || name > 'Z')
        throw std::invalid_argument ("name_of_set of Set must be from 'A' to Z (UPPER)");


    int index = name - 'A';
    if (array_of_sets[index] == nullptr) {
        array_of_sets[index] = this;
    }
    else
        throw std::invalid_argument ("this name_of_set of Set is exist");
}



Set::Set () : name_of_set ('*'), right (nullptr), first_element (nullptr), size (0) {}

Set::~Set () noexcept {
    clear_elements();
}


Node* Set::add_element (char item) {
    /*if (item < 'a' || item > 'z')
        throw std::invalid_argument ("name_of_set the element of Set must be from 'a' to 'z' (lower)");
*/
    Node * current = first_element;
    while (current != nullptr) {
        if (current->name == item) {
            throw std::invalid_argument("that element exist in Set");
        }
        current = current->down;
    }

    Node* item_n = new Node();
    item_n->name = item;

    if (first_element == nullptr)  {
        first_element = item_n;
        size++;
        return item_n;
    }
    if (item < first_element->name) {
        item_n->down = first_element;
        first_element = item_n;
        size++;
        return item_n;
    }

    current = first_element;

    while (1) {
        if (current-> down == nullptr) {
            current->down = item_n;
            size++;
            return item_n;
        }
        if (current->down->name > item) {
            item_n-> down = current->down;
            current->down = item_n;
            size++;
            return item_n;
        }
        current = current->down;
    }

}




void Set::remove_element (char item) {
    /*if (item < 'a' || item > 'z') {
        throw std::invalid_argument ("name_of_set the element of Set must be from 'a' to 'z' (lower)");
    }*/

    if (first_element == nullptr) {
        std::cout << "element ' " << item << " ' is not found in Set " << name_of_set << std::endl;
        return;
    }
    if (item < first_element->name) {
        std::cout << "element ' " << item << " ' is not found in Set " << name_of_set << std::endl;
        return;
    }
    if (first_element->name == item) {
        ////////////////////////////////////////////////////////////////////
        /*if (first_element->down == nullptr) {
            first_element = nullptr;
            size--;
            return;
        }*/
        Node * temp = first_element;
        first_element = first_element->down;
        size--;
        delete temp;
        return;
    }

    Node * current = first_element;
    while (current->down != nullptr) {
        if (current->down->name == item) {
            Node * temp = current -> down;
            current->down = current->down->down;
            delete temp;
            size--;
            return;
        }
        current = current->down;
    }
    std::cout << "element ' " << item << " ' is not found in Set " << name_of_set << std::endl;
    return;
}



bool Set::equal (const Set & other) const {
    if (this->size != other.size) {
        return false;
    }
    if (this->size == 0 && other.size == 0) {
        return true;
    }
    Node * curr1 = first_element;
    Node * curr2 = other.first_element;
    for (size_t i = 0; i< size; i++ ) {
        if (curr1->name != curr2->name)
            return false;
        curr1 = curr1->down;
        curr2 = curr2->down;
    }
    return true;
}


void Set::print_elements () const {
    if (size == 0) {
        std::cout << "Set " << name_of_set << " dont have elements\n" << std::endl;
        return;
    }
    Node * current = first_element;
    for (int i = 0; i< size; i++) {
        std::cout << "Element # " << i << " : " << current->name << std::endl;
        current = current->down;
    }
    return;
}


Set & Set::copy (Set const & other) {
    if (this != &other) {
        this->clear_elements();
        Node *current = other.first_element;
        while (current != nullptr) {
            this->add_element(current->name);
            current = current->down;
        }
    }
    return *this;
}

void Set::clear_elements () {
    if (first_element == nullptr) {
        return;
    }

    while (first_element != nullptr){
        Node* temp = first_element;
        first_element = first_element->down;
        delete temp;
        size--;
    }
    return;
}

Node * Set::operator[](int i) const {
    if (i < 0 || i>=size) {
        throw std::out_of_range("invalid number of element (set[i])");
    }
    if (first_element == nullptr) {
        throw std::runtime_error("set is empty");
    }
    Node * current = first_element;
    for (int j = 0; j< i; j++) {
        current = current->down;
    }
    return current;
}

std::vector <std::vector<char>> Set::boolean_set ()const{

    int total_set_size = 1 << size; //всего подмнож 2^size
    std::vector <std::vector<char>> total_vec;
    /*допустим у нас маска 3 -это 011
     конъюнкция с i
     001 - вкл первый элемент
     010  - вкл второй элемент
     100 - не вкл третий
     */
    for (int mask = 0; mask < total_set_size; mask++) {
        std::vector<char> subset;
        for (int i = 0; i < size; i++) {
            if ((mask & (1<<i) )!= 0) {
                subset.push_back((*this)[i]->name);
            }
        }
        total_vec.push_back(subset);
    }
    return total_vec;
}


void printer_elements (const Set & item) {
    item.print_elements();
    return;
}

void printer_sets () {
    std::cout << "List sets: " <<std::endl;
    for (int i = 0; i< 26; i++) {
        if (Set::array_of_sets[i] == nullptr)
            continue;
        std::cout << Set::array_of_sets[i]->name_of_set <<std::endl;
    }
    return;
}




void meld_union (const Set & one, const Set & two) {

    if (one.size == 0 && two.size == 0) {
        std::cout << "Empty set" << std::endl;
        return;
    }

    Set *new_set = new Set();

    if (one.size == 0) {
        //вернуть копию второго
        new_set->copy(two);
        new_set->print_elements();
        delete new_set;
        return;
    }

    if (two.size == 0) {
        new_set->copy(one);
        new_set->print_elements();
        delete new_set;
        return;
    }


    //создаем два указателя и одновременно сравниваем, сохраняем минимальный элемент
    Node * one_curr = one.first_element;
    Node * two_curr = two.first_element;
    while (one_curr !=nullptr && two_curr != nullptr) {
        if (one_curr->name<two_curr->name)  {
            new_set->add_element(one_curr->name);
            one_curr = one_curr->down;
        }
        else if (one_curr->name>two_curr->name) {
            new_set->add_element(two_curr->name);
            two_curr = two_curr->down;
        }
        else { //если элементы равны
            new_set->add_element(two_curr->name);
            two_curr = two_curr->down;
            one_curr = one_curr->down;
        }
    }

    while (one_curr != nullptr) {
        new_set->add_element(one_curr->name);
        one_curr = one_curr->down;
    }

    while (two_curr != nullptr) {
        new_set->add_element(two_curr->name);
        two_curr = two_curr->down;
    }

    new_set->print_elements();
    delete new_set;
    return;

}



void meld_crossing (const Set & one, const Set & two) {

    if (one.size == 0 || two.size == 0) {
        std::cout << "Empty set" << std::endl;
        return;
    }
    Set *result_set = new Set ();

    Node * one_curr = one.first_element;
    Node * two_curr = two.first_element;
    while (one_curr != nullptr && two_curr != nullptr) {
        if (one_curr->name == two_curr->name ) { //почему мб nullptr, если проверка размера имеется?
            result_set->add_element(one_curr->name);
            one_curr = one_curr->down;
            two_curr = two_curr->down;
        }
        else if (one_curr->name < two_curr->name) {
            one_curr = one_curr->down;
        }
        else {
            two_curr = two_curr-> down;
        }
    }
    if (result_set->size == 0) {
        std::cout << "Empty set" << std::endl;
    } else {
        result_set->print_elements();
    }
    delete result_set;
    return;
}



//9
void difference_set (const Set & one, const Set & two) {

    if (one.size == 0) {
        std::cout << "Result set empty" << std::endl;
        return;
    }

    if (two.size == 0) {
        one.print_elements();
        return;
    }

    Set* set_result = new Set();

    Node * one_curr = one.first_element;
    Node * two_curr = two.first_element;

    while (one_curr != nullptr) {
        if (two_curr == nullptr) {
            set_result->add_element(one_curr->name);
            one_curr = one_curr->down;
            continue;
        }

        if (one_curr->name == two_curr->name) {
            one_curr = one_curr->down;
            two_curr = two_curr -> down;
            continue;
        }

        if (one_curr-> name < two_curr->name) {
            set_result->add_element(one_curr->name);
            one_curr = one_curr->down;
            continue;
        }

        if (one_curr-> name > two_curr->name) {
            two_curr = two_curr->down;
            continue;
        }
    }
    if (set_result->size == 0) {
        std::cout<< "Result Set is empty" << std::endl;
        return;
    }
    else {
        set_result->print_elements();
    }
    delete set_result;
    return;
}



void is_subset (const Set & one, const Set & two) {

    if (one.size == 0) {
        std::cout << one.name_of_set << " is subset " << two.name_of_set << std::endl;
        return;
    }

    if (two.size == 0) {
        std::cout << one.name_of_set<< " is NOT subset " << two.name_of_set << std::endl;
        return;
    }

    Node * one_curr = one.first_element;
    Node * two_curr = two.first_element;

    while (one_curr != nullptr) {

        if (two_curr == nullptr || one_curr->name < two_curr->name) {
            std::cout << one.name_of_set << " is NOT subset " << two.name_of_set<< std::endl;
            return;
        }

        if (one_curr->name == two_curr->name) {
            one_curr = one_curr->down;
            two_curr = two_curr -> down;
            continue;
        }

        if (one_curr->name > two_curr->name ) {
            two_curr = two_curr -> down;
            continue;
        }

    }
    std::cout << one.name_of_set << " is subset " << two.name_of_set << std::endl;
    return;
}




void delete_set (Set & other) {
    int index = other.name_of_set - 'A';
    Set::array_of_sets [index] = nullptr;
    other.~Set();
}


int main () {
    std::cout << "Set Operations Program" << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "  new A - create new set A" << std::endl;
    std::cout << "  del A - delete set A" << std::endl;
    std::cout << "  add A x- add element x to set A" << std::endl;
    std::cout << "  rem A x- remove element x from set A" << std::endl;
    std::cout << "  pow A - compute power set (boolean) of A" << std::endl;
    std::cout << "  see [A] - show elements of set A, or all sets if no argument" << std::endl;
    std::cout << "  A + B - union of sets A and B" << std::endl;
    std::cout << "  A & B - intersection of sets A and B" << std::endl;
    std::cout << "  A - B - difference of sets A and B" << std::endl;
    std::cout << "  A < B - check if A is subset of B" << std::endl;
    std::cout << "  A = B - check if sets A and B are equal" << std::endl;
    std::cout << "  exit - exit program" << std::endl;
    std::cout << std::endl;

    std::string command;

    while (1) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command.empty()) continue;

        std::istringstream iss(command);
        std::string cmd;

        iss >> cmd;
try {
    if (cmd == "exit") {
        std::cout << "Exit..." << std::endl;
        break;
    }

        //new a
    else if (cmd == "new") {
        char set_name;
        iss >> set_name;
        if (set_name < 'A' || set_name > 'Z') {
            std::cout << "Error set name_of_set. Set name_of_set must be A-Z" << std::endl;
            continue;
        }
        Set *new_set = new Set(set_name);
        std::cout << "Set " << set_name << " created" << std::endl;
    }

        //del a
    else if (cmd == "del") {
        char set_name;
        iss >> set_name;
        if (set_name < 'A' || set_name > 'Z') {
            std::cout << "Error set name_of_set. Set name_of_set must be A-Z" << std::endl;
            continue;
        }
        int index = set_name - 'A';
        //тут разве не надо использовать мою функцию?
        if (Set::array_of_sets[index] != nullptr) {
            delete Set::array_of_sets[index];
            Set::array_of_sets[index] = nullptr;
            std::cout << "Set " << set_name << " deleted" << std::endl;
        } else {
            std::cout << "Set " << set_name << " does not exist" << std::endl;
        }
    }

        //add a x
    else if (cmd == "add") {
        char set_name, element;
        iss >> set_name >> element;
        if (set_name < 'A' || set_name > 'Z') {
            std::cout << "Error. Set name_of_set must be A-Z" << std::endl;
            continue;
        }
        int index = set_name - 'A';
        if (Set::array_of_sets[index] != nullptr) {
            Set::array_of_sets[index]->add_element(element);
            std::cout << "Element '" << element << "' added to set " << set_name << std::endl;
        } else {
            std::cout << "Set " << set_name << " does not exist" << std::endl;
        }
    }

        //rem A x
    else if (cmd == "rem") {
        char set_name, element;
        iss >> set_name >> element;
        if (set_name < 'A' || set_name > 'Z') {
            std::cout << "Error: Set name must be A-Z" << std::endl;
            continue;
        }
        int index = set_name - 'A';
        if (Set::array_of_sets[index] != nullptr) {
            Set::array_of_sets[index]->remove_element(element);
        } else {
            std::cout << "Set " << set_name << " does not exist" << std::endl;
        }
    }


        //pow a
    else if (cmd == "pow") {
        char set_name;
        iss >> set_name;
        if (set_name < 'A' || set_name > 'Z') {
            std::cout << "Error: Set name must be A-Z" << std::endl;
            continue;
        }
        int index = set_name - 'A';
        if (Set::array_of_sets[index] != nullptr) {
            std::cout << "Power set of " << set_name << ":" << std::endl;
            auto power_set = Set::array_of_sets[index]->boolean_set();

            for (size_t i = 0; i < power_set.size(); i++) {
                std::cout << "{ ";
                for (size_t j = 0; j < power_set[i].size(); j++) {
                    std::cout << (char) power_set[i][j];
                    if (j < power_set[i].size() - 1) std::cout << ", ";
                }
                std::cout << " }" << std::endl;
            }
        } else {
            std::cout << "Set " << set_name << " does not exist" << std::endl;
        }
    }


        //see [a]
    else if (cmd == "see") {
        char set_name;
        if (iss >> set_name) {
            if (set_name < 'A' || set_name > 'Z') {
                std::cout << "Error: Set name must be A-Z" << std::endl;
                continue;
            }
            int index = set_name - 'A';
            if (Set::array_of_sets[index] != nullptr) {
                Set::array_of_sets[index]->print_elements();
            } else {
                std::cout << "Set " << set_name << " does not exist" << std::endl;
            }
        } else {
            printer_sets();
        }
    } else {
        char set_A = cmd[0];
        if (set_A < 'A' || set_A > 'Z') {
            std::cout << "Unknown command: " << command << std::endl;
            continue;
        }

        std::string op;
        char set_B;
        iss >> op >> set_B;

        if (set_B < 'A' || set_B > 'Z') {
            std::cout << "Error: Set name must be A-Z" << std::endl;
            continue;
        }

        int index_A = set_A - 'A';
        int index_B = set_B - 'A';

        if (Set::array_of_sets[index_A] == nullptr) {
            std::cout << "Set " << set_A << " does not exist" << std::endl;
            continue;
        }
        if (Set::array_of_sets[index_B] == nullptr) {
            std::cout << "Set " << set_B << " does not exist" << std::endl;
            continue;
        }


        if (op == "+") {
            std::cout << "Union of " << set_A << " and " << set_B << ":" << std::endl;
            meld_union(*Set::array_of_sets[index_A], *Set::array_of_sets[index_B]);
        }
            //пересечение
        else if (op == "&") {
            std::cout << "Intersection of " << set_A << " and " << set_B << ":" << std::endl;
            meld_crossing(*Set::array_of_sets[index_A], *Set::array_of_sets[index_B]);
        } else if (op == "-") {
            std::cout << "Difference " << set_A << " - " << set_B << ":" << std::endl;
            difference_set(*Set::array_of_sets[index_A], *Set::array_of_sets[index_B]);
        }
            //проверка подмножества
        else if (op == "<") {
            is_subset(*Set::array_of_sets[index_A], *Set::array_of_sets[index_B]);
        } else if (op == "=") {
            if (Set::array_of_sets[index_A]->equal(*Set::array_of_sets[index_B])) {
                std::cout << "Sets " << set_A << " and " << set_B << " are equal" << std::endl;
            } else {
                std::cout << "Sets " << set_A << " and " << set_B << " are NOT equal" << std::endl;
            }
        } else {
            std::cout << "Unknown operation: " << op << std::endl;
        }
    }
}
        catch (const std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

    }

    for (int i = 0; i < 26; i++) {
        if (Set::array_of_sets[i] != nullptr) {
            delete Set::array_of_sets[i];
            Set::array_of_sets[i] = nullptr;
        }
    }
        return 0;
    }

