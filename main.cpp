#include <iostream>
#include <vector>
#include <cassert>
#include <string>
using namespace std;

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
  vector <Branch*> children;
  vector <Elf*> elves;  

  Branch(string name)
  {
    this->name = name;
  }

};

int main()
{
 srand(time(nullptr));

    vector <Branch*> trees;

    // Создаем деревья и их ветви
    for(int i = 0; i < 5; i ++)
    {
        Branch* tree = new Branch("tree " + to_string(i + 1));
        trees.push_back(tree);

        int numBigBranch = rand() % 3 + 3;
        for(int j = 0; j < numBigBranch; j ++)
        {
          Branch* bigBranch = new Branch("big branch " + to_string(j + 1));
          tree->children.push_back(bigBranch);

           int numMidBranch = rand() % 2 + 2;
           for(int k = 0; k < numBigBranch; k ++)
           {
            Branch* midBranch = new Branch("midl branch " + to_string(k + 1));
            bigBranch->children.push_back(midBranch);
           }
          
        }
    }

    // Заселяем дома эльфами
int count = 0;
for (Branch* tree : trees) {
    cout << "tree: " << tree->name << endl;

    for (Branch* bigBranch : tree->children) {
        cout << "big branch: " << bigBranch->name << endl;

        // Заселение на большие ветки
        count++;
        string elfName = "elf" + to_string(count);
        cout << "the elf's name is: " << elfName << endl;

        if (elfName != "None") {
            Elf* elf = new Elf();
            elf->name = elfName;
            bigBranch->elves.push_back(elf);
        }

        for (Branch* midBranch : bigBranch->children) {
            cout << "midl branch: " << midBranch->name << endl;

            // Заселение на средние ветки
            count++;
            elfName = "elf" + to_string(count);
            cout << "the elf's name is: " << elfName << endl;

            if (elfName != "None") {
                Elf* elf = new Elf();
                elf->name = elfName;
                midBranch->elves.push_back(elf);
            }
        }
    }
    cout << endl;
}

  // Поиск эльфа по имени и подсчет соседей
   string searchName;
cout << "Enter elf's name to search: ";
cin >> searchName;

int neighborCount = 0;
for (Branch* tree : trees) {
    for (Branch* bigBranch : tree->children) {
        for (Branch* midBranch : bigBranch->children) {
            for (Elf* elf : midBranch->elves) {
                if (elf->name == searchName) {
                    // Подсчет соседей на средних ветках
                    for (Branch* neighborMidBranch : bigBranch->children) {
                        if (neighborMidBranch != midBranch) {
                            neighborCount += neighborMidBranch->elves.size();
                        }
                    }
                    // Подсчет соседей на больших ветках
                    for (Elf* elf : bigBranch->elves) {
                        neighborCount++;
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