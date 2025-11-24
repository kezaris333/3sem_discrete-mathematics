#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <set>
#include <map>


void check_empty () {
        std::cout << "Empty set" << std::endl;
        std::cout << "Reflexive: +" << std::endl;
        std::cout << "Antireflexive: +" << std::endl;
        std::cout << "Symmetric: +" << std::endl;
        std::cout << "Antisymmetric: +" << std::endl;
        std::cout << "Asymmetric: +" << std::endl;
        std::cout << "Transitive: +" << std::endl;
        std::cout << "Antitransitive: +" << std::endl;
        std::cout << "Complete: +" << std::endl;
        return;
}

bool pair_exists(char one, char two,
                 const std::vector<std::pair<char, char>> &relation) {
    for (const auto &p: relation) {
        if (p.first == one && p.second == two)
            return true;
    }
    return false;
}

bool is_reflexive(const std::vector<char> &elements,
                  const std::vector<std::pair<char, char>> &relation) {
    for (char el: elements) {
        if (!pair_exists(el, el, relation)) {
            return false;
        }
    }
    return true;
}

bool is_antireflexive(const std::vector<char> &elements,
                      const std::vector<std::pair<char, char>> &relation) {
    for (char el: elements) {
        if (pair_exists(el, el, relation)) {
            return false;
        }
    }
    return true;
}

bool is_simmetric(const std::vector<char> &elements,
                  const std::vector<std::pair<char, char>> &relation) {
    for (int i = 0; i < relation.size(); i++) {
        if (relation[i].first != relation[i].second
            && !pair_exists(relation[i].second, relation[i].first, relation)) {
            return false;
        }
    }
    return true;
}

bool is_antisimmetric(const std::vector<char> &elements,
                      const std::vector<std::pair<char, char>> &relation) {
    for (auto p: relation) {
        if (p.first != p.second && pair_exists(p.second, p.first, relation)) {
            return false;
        }
    }

    return true;

}

bool is_asymmetric(const std::vector<char> &elements,
                   const std::vector<std::pair<char, char>> &relation) {

    for (auto p: relation) {

        if (p.first == p.second) {
            return false;
        }

        if (pair_exists(p.second, p.first, relation)) {
            return false;
        }
    }
    return true;
}

bool is_transitive(const std::vector<char> &elements,
                   const std::vector<std::pair<char, char>> &relation) {
    for (auto &p1: relation) {
        for (auto &p2: relation) {
            if (p1.second == p2.first) {
                if (!pair_exists(p1.first, p2.second, relation)) {
                    return false;
                }
            }
        }
    }
    return true;
}


bool is_antitransitive(const std::vector<char> &elements,
                       const std::vector<std::pair<char, char>> &relation) {
    for (auto &p1: relation) {
        for (auto &p2: relation) {
            if (p1.second == p2.first) {
                if (pair_exists(p1.first, p2.second, relation)) {
                    return false;
                }
            }
        }
    }
    return true;
}


bool is_complete(const std::vector<char> &elements,
                 const std::vector<std::pair<char, char>> &relation) {


    for (int i = 0; i < elements.size(); i++) {
        for (int j = i + 1; j < elements.size(); j++) {
            char a = elements[i];
            char b = elements[j];

            if (!pair_exists(a, b, relation) && !pair_exists(b, a, relation)) {
                return false;
            }
        }
    }
    return true;
}


bool is_eq(const std::vector<char> &elements,
           const std::vector<std::pair<char, char>> &relation) {
    for (auto e: elements) {
        for (auto p1: relation) {
            for (auto p2: relation) {

            }
        }
    }

}


std::set<char>  minimal_el(const std::vector<char> &elements,
                const std::vector<std::pair<char, char>> &relation) {
  std::set <char> minimal;

    for (char el : elements) {
        bool is_minimal = true;
        for (char other : elements) {
            if (el != other && pair_exists(other, el, relation)) {
                is_minimal = false;
                break;
            }
        }
        if (is_minimal) {
            minimal.insert(el);
        }
    }

    return minimal;
}


std::set<char> max_el (const std::vector<char> &elements,
                           const std::vector<std::pair<char, char>> &relation) {
    std::set <char> max;

    for (char el : elements) {
        bool is_max = true;
        for (char other : elements) {
            if (el != other && pair_exists(el, other, relation)) {
                is_max = false;
                break;
            }
        }
        if (is_max) {
            max.insert(el);
        }
    }

    return max;
}


std::vector<std::set<char>> get_equivalence_classes(
        const std::vector<char>& elements,
        const std::vector<std::pair<char, char>>& relation)
{
    std::vector<std::set<char>> all_classes;

    for (char el : elements) {
        std::set<char> eq_class;
        for (char other : elements) {
            if (pair_exists(el, other, relation) && pair_exists(other, el, relation)) {
                eq_class.insert(other);
            }
        }
        all_classes.push_back(eq_class);
    }

    std::vector<std::set<char>> unique_classes;
    for (const auto& cls : all_classes) {
        if (std::find(unique_classes.begin(), unique_classes.end(), cls) == unique_classes.end()) {
            unique_classes.push_back(cls);
        }
    }

    return unique_classes;
}
