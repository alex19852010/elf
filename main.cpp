#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Branch
{
public:
    Branch *parent;
    std::vector<Branch *> children;
    std::string elfName;

    Branch(Branch *parent)
    {
        this->parent = parent;
    }
};

int main()
{
    srand(time(0)); // Инициализация генератора случайных чисел

    // Генерация деревьев
    Branch *trees[5];
    for (int i = 0; i < 5; i++)
    {
        trees[i] = new Branch(nullptr);
    }

    // Генерация больших ветвей на каждом дереве
    for(int i = 0; i < 5; i ++)
    {
        int numberbranches = rand() % 3 + 3;
        for(int j = 0; j < numberbranches; j ++)
        {
          Branch* branch = new Branch(trees[i]);
          trees[i]->children.push_back(branch);
        }
    }

    // Генерация средних ветвей на каждой большой ветке
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < trees[i]->children.size(); j++) {
            int numBranches = rand() % 2 + 2;
            for (int k = 0; k < numBranches; k++) {
                Branch* branch = new Branch(trees[i]->children[j]);
                trees[i]->children[j]->children.push_back(branch);
            }
        }
    }

     // Размещение эльфов в домах
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < trees[i]->children.size(); j++) {
            std::string elfName;
            std::cout << "enter the name of the elf for the house in village " << i+1 << ", branch " << j+1 << ": ";
            std::cin >> elfName;
            if (elfName != "None") {
                trees[i]->children[j]->elfName = elfName;
            }
        }
    }

    // Поиск эльфа по имени и подсчет соседей
    std::string searchName;
    std::cout << "Enter elf name to search: ";
    std::cin >> searchName;

    int neighborCount = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < trees[i]->children.size(); j++) {
            if (trees[i]->children[j]->elfName == searchName) {
                neighborCount = trees[i]->children[j]->parent->children.size() - 1;
                break;
            }
        }
    }

     std::cout << "Number of neighbors for an elf " << searchName << ": " << neighborCount << std::endl;

    // Очистка памяти
    for (int i = 0; i < 5; i++) {
        delete trees[i];
    }

    return 0;
}