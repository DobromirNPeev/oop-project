#pragma once
#include "MyString.h"
#include "UniquePtr.hpp"

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
	User(const MyString& firstName, const MyString& lastnName, const MyString& password);
	User(const MyString& firstName, const MyString& lastnName, const MyString& password,unsigned id,unsigned points,bool upVoted,bool downVoted);
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	friend std::istream& operator>>(std::istream& is, User& user);
	friend std::ostream& operator<<(std::ostream& os,const User& user);
	friend class SocialNetwork;
protected:
	const MyString& getPassword() const;

};
std::istream& operator>>(std::istream& is, User& user);
std::ostream& operator<<(std::ostream& os,const User& user);