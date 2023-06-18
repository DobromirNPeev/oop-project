#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "Constants.h"

class User
{
private:
	MyString firstName="";
	MyString lastName="";
	MyString password="";
	unsigned id=0;
	unsigned points=0;
public:
	User()=default;
	User(const MyString& firstName, const MyString& lastnName, const MyString& password);
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	bool comparePassword(const MyString& password) const;
	unsigned getID() const;
	void setID(unsigned id);
	void IncreasePoints();
	friend std::istream& operator>>(std::istream& is, User& user);
	friend std::ostream& operator<<(std::ostream& os,const User& user);
	bool operator==(const User& other) const;
	friend class FileManager;
	
};
std::istream& operator>>(std::istream& is, User& user);
std::ostream& operator<<(std::ostream& os,const User& user);