// Group 5 Final Project.cpp : Library Inventory

/******************************************************************************************************************************************************
    This program updates a library inventory based on the number of copies of a book that are checked in/out. The user changes the name of the text 
    file with a list of the inventory with the format: Book Title; Book Author; #  with the number at the end representing the quantity of each title
    available for checkout.

******************************************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;


struct Inventory // AH
{
    string Title;   // Variable to hold book title. -AH
    string Author;  // Variable to hold author. -AH
    int Quantity = 0;   // Variable to hold number of copies. -AH

};


// Function prototypes.
bool ReadInventoryFile(string inventoryFileName, Inventory inventoryArray[]);// AH
void DisplayAndUpdateInventory(Inventory inventoryArray[]);// EH
void WriteOutInventoryFile(Inventory inventoryArray[], string inventoryFileName);// JZ

const string INVENTORY_FILE_NAME = "LibraryInventory.txt";  // Const string to hold the name of the inventory file. -AH
const int INVENTORY_LIST_LENGTH = 50;   // Const int to hold the length of the inventory list. -AH



int main()
{
    Inventory inventory[INVENTORY_LIST_LENGTH]; // Array of structs for each line in the inventory list. -AH

    
    
    // Pass the file name and struct array into the ReadInventoryFile function. If the function returns a failure, display
    // this message and exit the program. -AH
    if(ReadInventoryFile(INVENTORY_FILE_NAME, inventory) == false)
    {
        cout << "Error, could not read inventory file." << endl;
        system("pause");
        return 1;
    }  
    DisplayAndUpdateInventory(inventory);//EH

    system("pause");
    return 0;
}

/********************************************************************************
Function to open and read the inventory file, and store the information into the 
struct array.
********************************************************************************/
bool ReadInventoryFile(string inventoryFileName, Inventory inventoryArray[])// AH
{
    // Create and open the input file for the inventory - AH. 
    ifstream inventoryFile;
    inventoryFile.open(inventoryFileName);
    
    string ch = " "; // Variable to hold the integer (number of copies) at the end of the line. -AH

    if (inventoryFile)// If the file is successfully opened,
    {

        // For each line in the inventory file,
        for (int index = 0; index < INVENTORY_LIST_LENGTH; index++)
        {
            // Read the title and authors as strings to the struct array up to the semicolons, and the final character
            // until a new line begins. - AH
            getline(inventoryFile, inventoryArray[index].Title, ';');
            getline(inventoryFile, inventoryArray[index].Author, ';');
            getline(inventoryFile, ch, '\n');
            inventoryArray[index].Quantity = stoi(ch);
        }
        
        // Close the inventoty file. - AH
        inventoryFile.close();
        return true;
    }

    return false; // If the file could not be read successfully, return false. - AH.
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
    int bookIDWidth = 7;//used for formatting. EH
    int titleWidth = 45;//used for formatting. ED
    int authorWidth = 30;//used for formatting. EH
    int availableWidth = 15;//used for formatting. EH
    int totalWidth = bookIDWidth + titleWidth + authorWidth + availableWidth;//used for formatting. EH
    //the quantity of each book checked in shouldn't exceed the number of copies owned, so this array is used for bounds checking when checking in a book. EH
    int bookCount[50] = { 2,2,3,3,1,2,2,2,3,2,2,2,2,1,2,1,2,1,3,2,2,2,3,3,2,
        2,2,1,1,1,1,1,2,2,2,1,1,2,1,2,3,2,3,2,1,2,1,3,2,2 };

    string programTitle = "Library Inventory";//used for formatting output. EH

    char userContinue = 'c';//this is the sentinel variable of the while loop within which the user checks in/out books. EH
    int userChoice = 0;//this is used to determine which book the user would like to check in/out; each book has an int book ID. EH

    string checkInCheckOut = "value";//this is used to store the user's response to whether he/she is checking in or out a book. EH

    while (userContinue != 'q')//the program continues running unless the user enters 'q' when prompted. EH
    {
        cout << endl << setw(static_cast<unsigned __int64>(totalWidth) / 2 + programTitle.length() / 2) << programTitle//formats program title. EH
            << setw(static_cast<unsigned __int64>(totalWidth) / 2 + programTitle.length() / 2) << endl;

        cout << setw(totalWidth) << setfill('_') << '_' << setfill(' ') << endl << endl;

        cout << setw(bookIDWidth) << "Book ID"
            << setw(titleWidth) << "Title"
            << setw(authorWidth) << "Author"
            << setw(availableWidth) << "# Available" << endl;//formats headers. EH

        cout << setw(totalWidth) << setfill('_') << '_' << setfill(' ') << endl << endl;

        for (int index = 1; index <= INVENTORY_LIST_LENGTH; index++)//EH
        {
            cout << setw(bookIDWidth) << index << setw(titleWidth) << inventoryArray[index - 1].Title
                << setw(authorWidth) << inventoryArray[index - 1].Author << setw(availableWidth)
                << inventoryArray[index - 1].Quantity << endl;
            cout << setw(totalWidth) << setfill('_') << '_' << setfill(' ') << endl << endl;//formats and prints to console array contents. EH

        }

        cout << "Enter the ID number of the book you'd like to check in or check out: ";//prompts user for book ID (int value from 1 to 50). EH
        cin >> userChoice;
        cout << endl;

        if (userChoice >= 1 && userChoice <= 50)//checks whether user input is valid book ID. EH
        {
            cout << "Type \"in\" to check book in, type \"out\" to check book out, or type any character to back out of selection: ";//prompts user for desired action.EH
            cin >> checkInCheckOut;//
            transform(checkInCheckOut.begin(), checkInCheckOut.end(), checkInCheckOut.begin(), tolower);//sets user input to lowercase to simplify following conditional statements.EH
            cout << endl;

            if (checkInCheckOut == "in")
            {
                if (inventoryArray[userChoice - 1].Quantity == bookCount[userChoice - 1])//checks whether number of checked-in books is already the number owned.EH
                    cout << "All copies of \"" << inventoryArray[userChoice - 1].Title << "\" are checked in." << endl << endl;//if it is, the quantity is not incremented.EH
                else
                    inventoryArray[userChoice - 1].Quantity++;//if it isn't, the quantity is incremented.EH
            }
            else if (checkInCheckOut == "out")
            {
                if (inventoryArray[userChoice - 1].Quantity == 0)//checks whether number of books in inventory is zero. EH
                    cout << "All copies of \"" << inventoryArray[userChoice - 1].Title << "\" are checked out." << endl << endl;//if it is, quantity not decremented; no copies to take away.EH
                else
                    inventoryArray[userChoice - 1].Quantity--;//if it isn't, quantity is decremented
            }
            else//prints when user's action selection is not recognized as "in" or "out" EH
                cout << "Neither \"in\" nor \"out\" entered. The quantity of \"" << inventoryArray[userChoice - 1].Title << "\" will not be updated." << endl << endl;
        }
        else//this happens when user's initial input is not an integer between 1 and 50.EH
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid entry. Book IDs are integers between 1 and 50." << endl;
        }


        cout << "Type any character to continue or type 'q' to close program: ";//reassigns sentinel variable so user can run program again or close program.EH
        cin >> userContinue;
        userContinue = tolower(userContinue);
    }

    if (userContinue == 'q') {// JZ
        WriteOutInventoryFile(inventoryArray, INVENTORY_FILE_NAME);
    }

}
