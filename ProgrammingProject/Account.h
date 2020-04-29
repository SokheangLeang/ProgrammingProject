#pragma once
#include <iostream>
#include <string>
using namespace std;
//--------------------------
//Base Account Class
//--------------------------
class Account
{
protected:
	string identification; //email or username, not called name as sometime, people use alternate names instead of real name
	string password;
	string multiFactorAuthentication; //Type of authentication such as 2FA, Texting, Phone, etc
	string service; //Name of the service such as Discord, Youtube, Steam, etc
	string type; //Type of account, Email, ECommerce, or Social Media, this will be used to help with file input/output to make sure the account loaded is the correct type of account
public:
	//Constructor
	Account(string i, string p, string mfa, string s)
	{
		identification = i;
		password = p;
		multiFactorAuthentication = mfa;
		service = s;
	}
	//Accessor
	string viewID() { return identification; }
	string viewPassword() { return password; }
	string viewMFA() { return multiFactorAuthentication; }
	string viewService() { return service; }
	string viewType() { return type; }
	//Virtual Accessor
	virtual string toString() { return ""; };
	virtual string viewDomain() { return ""; };
	virtual string viewAddress() { return ""; };
	virtual string viewPayment() { return ""; };
	virtual string viewName() { return ""; };
	//Overloaded operation for toString()
	ostream &operator<<(ostream &output)
	{
		output << toString();
		return output;
	}
};
//--------------------------
//Email Account Class
//--------------------------
class EmailAccount : public Account //Email will require a domain
{
private:
	string domain; //@yahoo.com or @gmail.com, the user would enter gmail.com or yahoo.com, basically the website
public:
	//Constructor
	EmailAccount(string i, string p, string mfa, string s, string d) : Account(i, p, mfa, s)
	{
		domain = d;
		type = "Email";
	}
	//Accessor
	string viewDomain() { return domain; }
	string toString()
	{
		return "ID: " + identification + "@" + viewDomain() + "\nPassword: " + password + "\nAuthentication: " + multiFactorAuthentication + "\nService: "
			+ service + "\nType: " + type;
	}
	//Domain cannot be changed
};
//--------------------------
//E-Commerce Account Class
//--------------------------
class ECommerceAccount : public Account //ECommerce will require address
{
private:
	string address;
	string payment; //Credit card, debit, paypal, etc
public:
	//Constructor
	ECommerceAccount(string i, string p, string mfa, string s, string a, string pay) : Account(i, p, mfa, s)
	{
		address = a;
		payment = pay;
		type = "ECommerce";
	}
	//Accessor
	string viewAddress() { return address; }
	string viewPayment() { return payment; }
	string toString()
	{
		return "ID: " + identification + "\nPassword: " + password + "\nAuthentication: " + multiFactorAuthentication + "\nService: "
			+ service + "\nType: " + type + "\nAddress: " + address + "\nPayment: " + payment;
	}
};
//--------------------------
//Social Media Account Class
//--------------------------
class SocialMediaAccount : public Account //SocialMedia will require real name
{
private:
	string name; //Real name
public:
	//Constructor
	SocialMediaAccount(string i, string p, string mfa, string s, string n) : Account(i, p, mfa, s)
	{
		name = n;
		type = "Social Media";
	}
	//Accessor
	string viewName() { return name; }
	string toString()
	{
		return "ID: " + identification + "\nPassword: " + password + "\nAuthentication: " + multiFactorAuthentication + "\nService: "
			+ service + "\nType: " + type + "\nName: " + name;
	}
};