#pragma once
#include "MyString.h"

class User
{
private:
	MyString firstName;
	MyString lastName;
	MyString password;
	unsigned id;
	unsigned points;
	bool upVoted = false;
	bool downVoted = false;
public:
	User();
	User(const char* firstName, const char* lastnName, const char* password);
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	friend std::istream& operator>>(std::istream& is, User& user);
	friend class SocialNetwork;
protected:
	const MyString& getPassword() const;

};
std::istream& operator>>(std::istream& is, const User& user);