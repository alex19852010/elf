#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Elf {
public:
    std::string name;
};

class Branch {
public:
    std::string name;
    std::vector<Branch*> children;
    std::vector<Elf*> elves;

    Branch(std::string name) {
        this->name = name;
    }
};


int main()
{
    std::srand(std::time(nullptr));

    std::vector<Branch*> trees;

    // Создаем деревья и их ветви
    for (int i = 0; i < 5; i++) {
        Branch* tree = new Branch("Tree " + std::to_string(i + 1));
        trees.push_back(tree);

        int numBigBranches = std::rand() % 3 + 3;
        for (int j = 0; j < numBigBranches; j++) {
            Branch* bigBranch = new Branch("Big Branch " + std::to_string(j + 1));
            tree->children.push_back(bigBranch);

            int numMidBranches = std::rand() % 2 + 2;
            for (int k = 0; k < numMidBranches; k++) {
                Branch* midBranch = new Branch("Mid Branch " + std::to_string(k + 1));
                bigBranch->children.push_back(midBranch);
            }
        }
    }

    // Заселяем дома эльфами
    for (Branch* tree : trees) {
        std::cout << "Tree: " << tree->name << std::endl;
        for (Branch* bigBranch : tree->children) {
            std::cout << "\tBig Branch: " << bigBranch->name << std::endl;
            for (Branch* midBranch : bigBranch->children) {
                std::cout << "\t\tMid Branch: " << midBranch->name << std::endl;
                std::string elfName;
                std::cout << "\t\t\tEnter elf's name (or None to skip): ";
                std::cin >> elfName;
                if (elfName != "None") {
                    Elf* elf = new Elf();
                    elf->name = elfName;
                    midBranch->elves.push_back(elf);
                }
            }
        }
        std::cout << std::endl;
    }

    // Поиск эльфа по имени и подсчет соседей
    std::string searchName;
    std::cout << "Enter elf's name to search: ";
    std::cin >> searchName;

    int neighborCount = 0;
    for (Branch* tree : trees) {
        for (Branch* bigBranch : tree->children) {
            for (Branch* midBranch : bigBranch->children) {
                for (Elf* elf : midBranch->elves) {
                    if (elf->name == searchName) {
                        for (Branch* neighborMidBranch : bigBranch->children) {
                            if (neighborMidBranch != midBranch) {
                                neighborCount += neighborMidBranch->elves.size();
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

    std::cout << "Total neighbors for " << searchName << ": " << neighborCount << std::endl;

    // Освобождаем память
    for (Branch* tree : trees) {
        for (Branch* bigBranch : tree->children) {
            for (Branch* midBranch : bigBranch->children) {
                for (Elf* elf : midBranch->elves) {
                    delete elf;
                }
                delete midBranch;
            }
            delete bigBranch;
        }
        delete tree;
    }  

  
    return 0;  
  
}