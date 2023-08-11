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
    for(Branch* tree:trees)
    {
      cout << "tree: " << tree->name << endl;

      for(Branch* bigBranch:tree->children)
      {
        cout << "big branch: " << bigBranch->name << endl;

        for(Branch* midBranch:bigBranch->children)
        {
            cout << "midl branch: " << midBranch->name << "  ";
            count ++;
            string elfName = "elf";
            elfName += to_string(count);
            cout << "the elf's name is: " << elfName << endl;

            if(elfName != "None")
            {
                Elf* elf = new Elf();
                elf->name = elfName;
                midBranch->elves.push_back(elf);
            }
        }
      }
      cout << endl;
    }
    
    return 0;  
 }