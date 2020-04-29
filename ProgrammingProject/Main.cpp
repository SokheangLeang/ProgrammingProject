#include <iostream>
#include <string>
#include "Account.h"
#include "AccountList.h"
using namespace std;
/*
AccountList by Sokheang Leang
Last edited 12-16-2019
The purpose of AccountList is to create a account storage system
*/
void printMenuOption(); //Prints out option to interact with the account list

int main()
{
	AccountList accountList;
	int cmd, cmd2; //Will be use when

	accountList.fileToVector();
	do
	{
		printMenuOption();
		cout << "Select a option: ";
		cin >> cmd;
		switch (cmd)
		{
		case 0: //Stop the loop
			cout << "Account storage turned off" << endl;
			break;
		case 1: //View list
			accountList.viewList();
			break;
		case 2: //Create and add account
			accountList.addAccount();
			break;
		case 3: //Delete Account
			accountList.viewAccount();
			cout << "Which accout do you want to delete: ";
			cin >> cmd2;
			accountList.removeAccount(cmd2 - 1);
			break;
		case 4: //Add to favorites
			accountList.viewAccount();
			cout << "Which accout do you want to add to favorites(0 to cancel): ";
			cin >> cmd2;
			if (cmd2 != 0)
			{
				accountList.addFavorite(cmd2 - 1);
			}
			break;
		case 5: //Remove from favorites
			accountList.viewFavorite();
			cout << "Which accout do you want to remove from favorites(0 to cancel): ";
			cin >> cmd2;
			if (cmd2 != 0)
			{
				accountList.removeFavorite(cmd2 - 1);
			}
			break;
		default:
			cout << "Invalid option" << endl;
			break;
		}

		cout << "-------------------" << endl;
	} while (cmd != 0);
	accountList.vectorToFile();

	system("pause");
	return 0;
}

//Functions
void printMenuOption()
{
	cout << "0. Exit list\n1. View list\n2. Add account\n3. Delete account\n4. Add Favorite\n5. Delete favorite" << endl;
}
