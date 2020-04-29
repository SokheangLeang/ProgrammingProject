#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Account.h"
using namespace std;
//--------------------------
//AccountList Class
//--------------------------
class AccountList //AccountList does not need a constructor
{
private:
	vector<Account*> accounts;
	vector<Account*> favorites;
public:

	//--------------------------
	//Accessor
	//--------------------------
	void viewList() //Prints out favorite first before the other accounts
	{
		viewFavorite();
		viewAccount();
	}
	void viewAccount() //Prints out the non-favorites account only
	{
		cout << "-----Accounts-----" << endl;
		for (unsigned int i = 0; i < accounts.size(); i++)
		{
			cout << "-------------------" << endl;
			cout << i + 1 << ":\n" << accounts[i]->toString() << endl;
		}
		cout << endl;
	}
	void viewFavorite() //Prints out the favorites only
	{
		cout << "-----Favorites-----" << endl;
		for (unsigned int i = 0; i < favorites.size(); i++)
		{
			cout << "-------------------" << endl;
			cout << i + 1 << ":\n" << favorites[i]->toString() << endl;
		}
		cout << endl;
	}

	//--------------------------
	//Mutator
	//--------------------------
	void addAccount() //Create and add account to the vector
	{
		string id, password, mfa, service, domain, payment, address, name;
		int cmd;
		cout << "1. Email\n2. ECommerce\n3. Social Media" << endl;
		cout << "What type of account do you want to create: ";
		cin >> cmd;
		cin.ignore();
		cout << "What is your account id: ";
		getline(cin, id);
		cout << "What is your password: ";
		getline(cin, password);
		cout << "What is your multi-factor authentication method: ";
		getline(cin, mfa);
		cout << "What is the name of the service: ";
		getline(cin, service);
		switch (cmd)
		{
		case 1:
			EmailAccount *email;
			cout << "What is the domain: ";
			getline(cin, domain);
			email = new EmailAccount(id, password, mfa, service, domain);
			accounts.push_back(email);
			break;
		case 2:
			ECommerceAccount *ecomm;
			cout << "What is your address: ";
			getline(cin, address);
			cout << "What is your payment type: ";
			getline(cin, payment);
			ecomm = new ECommerceAccount(id, password, mfa, service, address, payment);
			accounts.push_back(ecomm);
			break;
		case 3:
			SocialMediaAccount *socmed;
			cout << "What is your real name: ";
			getline(cin, name);
			socmed = new SocialMediaAccount(id, password, mfa, service, name);
			accounts.push_back(socmed);
			break;
		default:
			cout << "Invalid option" << endl;
			break;
		}
	}
	void removeAccount(int i) 
	{
		cout << accounts[i]->viewID() << " removed." << endl;
		accounts.erase(accounts.begin() + i);
	}
	void addFavorite(int i)
	{
		cout << accounts[i]->viewID() << " added to favorites." << endl;
		favorites.push_back(accounts[i]);
		accounts.erase(accounts.begin() + i);
	}
	void removeFavorite(int i)
	{
		cout << favorites[i]->viewID() << " removed from favorites." << endl;
		accounts.push_back(favorites[i]);
		favorites.erase(favorites.begin() + i);
	}

	//--------------------------
	//FileIO
	//--------------------------
	void fileToVector()
	{
		string id, password, mfa, service, type, domain, address, payment, name, favorited;
		EmailAccount *email; ECommerceAccount *ecomm; SocialMediaAccount *socmed;
		ifstream read;
		read.open("accounts.txt");
		if (read.is_open())
		{
			getline(read, type);
			while (!read.eof())
			{
				getline(read, id);
				getline(read, password);
				getline(read, mfa);
				getline(read, service);
				if (type == "Email")
				{
					getline(read, domain);
					
					email = new EmailAccount(id, password, mfa, service, domain);
					getline(read, favorited);
					if (favorited == "False")
					{
						accounts.push_back(email);
					}
					else
					{
						favorites.push_back(email);
					}
					
				}
				else if (type == "ECommerce")
				{
					getline(read, address);
					getline(read, payment);
					ecomm = new ECommerceAccount(id, password, mfa, service, address, payment);
					getline(read, favorited);
					if (favorited == "False")
					{
						accounts.push_back(ecomm);
					}
					else
					{
						favorites.push_back(ecomm);
					}
				}
				else
				{
					getline(read, name);
					socmed = new SocialMediaAccount(id, password, mfa, service, name);
					getline(read, favorited);
					if (favorited == "False")
					{
						accounts.push_back(socmed);
					}
					else
					{
						favorites.push_back(socmed);
					}
				}
				getline(read, type);
			}
		}
		else
		{
			std::cout << "accounts.txt failed to open" << endl;
		}
		read.close();
	}
	void vectorToFile()
	{
		ofstream write;
		write.open("accounts.txt", ios::trunc);
		for (unsigned int i = 0; i < accounts.size(); i++)
		{
			write << accounts[i]->viewType() << endl;
			write << accounts[i]->viewID() << endl;
			write << accounts[i]->viewPassword() << endl;
			write << accounts[i]->viewMFA() << endl;
			write << accounts[i]->viewService() << endl;
			if (accounts[i]->viewType() == "Email")
			{
				write << accounts[i]->viewDomain() << endl;
			}
			else if (accounts[i]->viewType() == "ECommerce")
			{
				write << accounts[i]->viewAddress() << endl;
				write << accounts[i]->viewPayment() << endl;
			}
			else
			{
				write << accounts[i]->viewName() << endl;
			}
			write << "False" << endl;
		}
		for (unsigned int i = 0; i < favorites.size(); i++)
		{
			write << favorites[i]->viewType() << endl;
			write << favorites[i]->viewID() << endl;
			write << favorites[i]->viewPassword() << endl;
			write << favorites[i]->viewMFA() << endl;
			write << favorites[i]->viewService() << endl;
			if (favorites[i]->viewType() == "Email")
			{
				write << favorites[i]->viewDomain() << endl;
			}
			else if (favorites[i]->viewType() == "ECommerce")
			{
				write << favorites[i]->viewAddress() << endl;
				write << favorites[i]->viewPayment() << endl;
			}
			else
			{
				write << favorites[i]->viewName() << endl;
			}
			write << "True" << endl;
		}
		write.close();
	}
};