// Group 5 Final Project.cpp : 
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct Inventory // AH
{
    string Title;// AH
    string Author;// AH
    int Quantity;// AH
};


bool ReadInventoryFile(string inventoryFileName, Inventory titleArray[], Inventory authorArray[], Inventory quantityArray[]);// AH


const string INVENTORY_FILE_NAME = "LibraryInventory.txt";// AH
const int INVENTORY_LIST_LENGTH = 50;// AH


int main()
{
    Inventory titles[INVENTORY_LIST_LENGTH];// AH
    Inventory authors[INVENTORY_LIST_LENGTH];// AH
    Inventory quantity[INVENTORY_LIST_LENGTH];// AH

    ReadInventoryFile(INVENTORY_FILE_NAME, titles, authors, quantity);// AH

    system("pause");
    return 0;
}


bool ReadInventoryFile(string inventoryFileName, Inventory titleArray[], Inventory authorArray[], Inventory quantityArray[])// AH
{
    ifstream inventoryFile;// AH
    inventoryFile.open(inventoryFileName);// AH

    if (inventoryFile)// AH
    {
        int titleIndex = 0;
        int quantityIndex;
        int authorIndex;
        while (!inventoryFile.eof() && titleIndex < INVENTORY_LIST_LENGTH)// AH
        {
            getline(inventoryFile, titleArray[titleIndex].Title, ';');

            for (int authorIndex = 0; authorIndex < INVENTORY_LIST_LENGTH; authorIndex++)// AH
            {
                getline(inventoryFile, authorArray[authorIndex].Author, ';');
            }

            for (int quantityIndex = 0; quantityIndex < INVENTORY_LIST_LENGTH; quantityIndex++)// AH
            {
                inventoryFile >> quantityArray[quantityIndex].Quantity;
            }

            titleIndex++;
        }

        inventoryFile.close();// AH
        return true;
    }

    return false;// AH
}

