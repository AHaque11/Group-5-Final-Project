// Group 5 Final Project.cpp : 
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;


struct Inventory // AH
{
    string Title;// AH
    string Author;// AH
    int Quantity = 0;// AH

};


bool ReadInventoryFile(string inventoryFileName, Inventory inventoryArray[]);// AH
void DisplayAndUpdateInventory(Inventory inventoryArray[]);// EH
void WriteOutInventoryFile(Inventory inventoryArray[], string inventoryFileName);// JZ

const string INVENTORY_FILE_NAME = "LibraryInventory.txt";// AH
const int INVENTORY_LIST_LENGTH = 50;// AH



int main()
{
    Inventory inventory[INVENTORY_LIST_LENGTH];// AH

    ReadInventoryFile(INVENTORY_FILE_NAME, inventory);// AH
    DisplayAndUpdateInventory(inventory);//EH

    system("pause");
    return 0;
}


bool ReadInventoryFile(string inventoryFileName, Inventory inventoryArray[])// AH
{
    ifstream inventoryFile;// AH
    inventoryFile.open(inventoryFileName);// AH
    string ch = " ";

    if (inventoryFile)// AH
    {

        for (int index = 0; index < INVENTORY_LIST_LENGTH; index++)
        {

            getline(inventoryFile, inventoryArray[index].Title, ';');
            getline(inventoryFile, inventoryArray[index].Author, ';');
            getline(inventoryFile, ch, '\n');
            inventoryArray[index].Quantity = stoi(ch);
        }

        inventoryFile.close();// AH
        return true;
    }

    return false;// AH
}

void WriteOutInventoryFile(Inventory inventoryArray[], string inventoryFileName) {// JZ
    ofstream MyFile(inventoryFileName);
    for (int i = 0; i < INVENTORY_LIST_LENGTH; i++) {//JZ
        MyFile << inventoryArray[i].Title << "; " 
            << inventoryArray[i].Author << "; "
            << inventoryArray[i].Quantity << "\n";
    }
    
    MyFile.close();//JZ
}

void DisplayAndUpdateInventory(Inventory inventoryArray[])//EH
{
    int bookIDWidth = 7;
    int titleWidth = 45;
    int authorWidth = 30;
    int availableWidth = 15;
    int totalWidth = bookIDWidth + titleWidth + authorWidth + availableWidth;
    int bookCount[50] = { 2,2,3,3,1,2,2,2,3,2,2,2,2,1,2,1,2,1,3,2,2,2,3,3,2,
        2,2,1,1,1,1,1,2,2,2,1,1,2,1,2,3,2,3,2,1,2,1,3,2,2 };

    string programTitle = "Library Inventory";

    char userContinue = 'c';
    int userChoice = 0;

    string checkInCheckOut = "value";

    while (userContinue != 'q')//EH
    {
        cout << endl << setw(static_cast<unsigned __int64>(totalWidth) / 2 + programTitle.length() / 2) << programTitle
            << setw(static_cast<unsigned __int64>(totalWidth) / 2 + programTitle.length() / 2) << endl;

        cout << setw(totalWidth) << setfill('_') << '_' << setfill(' ') << endl << endl;

        cout << setw(bookIDWidth) << "Book ID"
            << setw(titleWidth) << "Title"
            << setw(authorWidth) << "Author"
            << setw(availableWidth) << "# Available" << endl;

        cout << setw(totalWidth) << setfill('_') << '_' << setfill(' ') << endl << endl;

        for (int index = 1; index <= INVENTORY_LIST_LENGTH; index++)//EH
        {
            cout << setw(bookIDWidth) << index << setw(titleWidth) << inventoryArray[index - 1].Title
                << setw(authorWidth) << inventoryArray[index - 1].Author << setw(availableWidth)
                << inventoryArray[index - 1].Quantity << endl;
            cout << setw(totalWidth) << setfill('_') << '_' << setfill(' ') << endl << endl;

        }

        cout << "Enter the ID number of the book you'd like to check in or check out: ";
        cin >> userChoice;
        cout << endl;

        if (userChoice >= 1 && userChoice <= 50)//EH
        {
            cout << "Type \"in\" to check book in, type \"out\" to check book out, or type any character to back out of selection: ";
            cin >> checkInCheckOut;
            transform(checkInCheckOut.begin(), checkInCheckOut.end(), checkInCheckOut.begin(), tolower);
            cout << endl;

            if (checkInCheckOut == "in")
            {
                if (inventoryArray[userChoice - 1].Quantity == bookCount[userChoice - 1])
                    cout << "All copies of \"" << inventoryArray[userChoice - 1].Title << "\" are checked in." << endl << endl;
                else
                    inventoryArray[userChoice - 1].Quantity++;
            }
            else if (checkInCheckOut == "out")
            {
                if (inventoryArray[userChoice - 1].Quantity == 0)
                    cout << "All copies of \"" << inventoryArray[userChoice - 1].Title << "\" are checked out." << endl << endl;
                else
                    inventoryArray[userChoice - 1].Quantity--;
            }
            else
                cout << "Neither \"in\" nor \"out\" entered. The quantity of \"" << inventoryArray[userChoice - 1].Title << "\" will not be updated." << endl << endl;

        else//EH
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid entry. Book IDs are integers between 1 and 50." << endl;
        }


        cout << "Type any character to continue or type 'q' to close program: ";
        cin >> userContinue;
        userContinue = tolower(userContinue);
    }

    if (userContinue == 'q') {// JZ
        WriteOutInventoryFile(inventoryArray, INVENTORY_FILE_NAME);
    }

}
