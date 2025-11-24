#include "lib.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        throw std::invalid_argument("must be one argument");
    }

    std::ifstream f(argv[1]);
    if (!(f.is_open())) {
        throw std::invalid_argument("impossible open file");
    }

    std::string str;
    std::vector<char> elements;
    std::vector<std::pair<char, char>> relation;

    getline(f, str);
    std::stringstream ss(str);
    char ch;
    while (ss >> ch) {
        elements.push_back(ch);
    }

    while (getline(f, str)) {
        std::stringstream ss2(str);
        char one, two;
        while (ss2 >> one >> two) {
            relation.push_back({one, two});
        }
    }

    f.close();


    if (elements.empty()) {
        check_empty();
        return 0;
    }


    bool reflexive = is_reflexive(elements, relation);
    bool antireflexive = is_antireflexive(elements, relation);
    bool symmetric = is_simmetric(elements, relation);
    bool antisymmetric = is_antisimmetric(elements, relation);
    bool asymmetric = is_asymmetric(elements, relation);
    bool transitive = is_transitive(elements, relation);
    bool antitransitive = is_antitransitive(elements, relation);
    bool complete = is_complete(elements, relation);

    std::cout << "Reflexive: " << (reflexive ? "+" : "-") << std::endl;
    std::cout << "Antireflexive: " << (antireflexive ? "+" : "-") << std::endl;
    std::cout << "Symmetric: " << (symmetric ? "+" : "-") << std::endl;
    std::cout << "Antisymmetric: " << (antisymmetric ? "+" : "-") << std::endl;
    std::cout << "Asymmetric: " << (asymmetric ? "+" : "-") << std::endl;
    std::cout << "Transitive: " << (transitive ? "+" : "-") << std::endl;
    std::cout << "Antitransitive: " << (antitransitive ? "+" : "-") << std::endl;
    std::cout << "Complete: " << (complete ? "+" : "-") << std::endl;



    if (reflexive && symmetric && transitive) {
        std::cout << "\nEquivalence relation" << std::endl;
        auto classes = get_equivalence_classes(elements, relation);
        std::cout << "Equivalence classes:" << std::endl;
        for (size_t i = 0; i < classes.size(); i++) {
            std::cout << "Class " << i + 1 << ":{";
            for (auto it = classes[i].begin(); it != classes[i].end(); ++it) {
                if (it != classes[i].begin()) std::cout << ", ";
                std::cout << *it;
            }
            std::cout << "}" << std::endl;
        }
        std::cout << "Index: " << classes.size() << std::endl;
    }


    if (reflexive && antisymmetric && transitive) {

        auto minimal = minimal_el(elements, relation);
        auto maximal = max_el(elements, relation);

        std::cout << "Min elements: {";
        for (auto it = minimal.begin(); it != minimal.end(); ++it) {
            if (it != minimal.begin()) std::cout << ", ";
            std::cout << *it;
        }
        std::cout << "}" << std::endl;

        std::cout << "Max elements: { ";
        for (auto it = maximal.begin(); it != maximal.end(); ++it) {
            if (it != maximal.begin()) std::cout << ", ";
            std::cout << *it;
        }
        std::cout << "}" << std::endl;
    }

    return 0;
}

