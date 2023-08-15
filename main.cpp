#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Elf
{
public:
    string name;
};

class Branch
{
public:
    string name;
    vector<Branch*> children;
    Elf elves; // заменяем vector<Elf*> elves на Elf elves

    Branch(string name)
    {
        this->name = name;
    }
};



int main()
{
 srand(time(nullptr));

    vector<Branch*> trees;

    // Создаем деревья и их ветви
    for (int i = 0; i < 5; i++)
    {
        Branch* tree = new Branch("tree " + to_string(i + 1));
        trees.push_back(tree);

        int numBigBranch = rand() % 3 + 3;
        for (int j = 0; j < numBigBranch; j++)
        {
            Branch* bigBranch = new Branch("big branch " + to_string(j + 1));
            tree->children.push_back(bigBranch);

            int numMidBranch = rand() % 2 + 2;
            for (int k = 0; k < numMidBranch; k++)
            {
                Branch* midBranch = new Branch("midl branch " + to_string(k + 1));
                bigBranch->children.push_back(midBranch);
            }
        }
    }

    // Заселяем дома эльфами
    int count = 0;
    for (Branch* tree : trees)
    {
        cout << "tree: " << tree->name << endl;

        for (Branch* bigBranch : tree->children)
        {
            cout << "big branch: " << bigBranch->name << "  ";

            // Заселение на большие ветки
            count++;
            string elfName = rand() % 5 ? "elf" + to_string(count) : "None";
            cout << "the elf's name is: " << elfName << endl;

            if (elfName != "None")
            {
                Elf elf;
                elf.name = elfName;
                bigBranch->elves = elf;
            }

            for (Branch* midBranch : bigBranch->children)
            {
                cout << "midl branch: " << midBranch->name << " ";

                // Заселение на средние ветки
                count++;
                elfName = rand() % 5 ? "elf" + to_string(count) : "None";
                cout << "the elf's name is: " << elfName << endl;

                if (elfName != "None")
                {
                    Elf elf;
                    elf.name = elfName;
                    midBranch->elves = elf;
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    // Поиск эльфа по имени и подсчет соседей
       string searchName;
    cout << "Enter elf's name to search: ";
    cin >> searchName;

    int neighborCount = 0;
    for (Branch* tree : trees)
    {
        for (Branch* bigBranch : tree->children)
        {
            if (bigBranch->elves.name == searchName)
            {
                // neighborCount = bigBranch->children.size();
                // break;
                 for (Branch* midBranch : bigBranch->children)
                    {
                        if(midBranch->elves.name != "")
                        {
                          neighborCount ++;
                        }
                    }
            }
            for (Branch* midBranch : bigBranch->children)
            {
                if (midBranch->elves.name == searchName)
                {
                    // Подсчет соседей на средних ветках
                    for (Branch* neighborMidBranch : bigBranch->children)
                    {
                        if (neighborMidBranch != midBranch)
                        {
                            neighborCount += neighborMidBranch->elves.name != "" ? 1 : 0;
                        }
                    }
                    // Подсчет соседей на больших ветках
                    neighborCount += bigBranch->elves.name != "" ? 1 : 0;
                    break;
                }
            }
        }
    }
    cout << "Total neighbors for " << searchName << ": " << neighborCount << endl;

    // Освобождаем память
    for (Branch* tree : trees)
    {
        for (Branch* bigBranch : tree->children)
        {
            delete bigBranch;
        }
        delete tree;
        
    }


    return 0;  
 
   
}