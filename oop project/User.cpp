#include "User.h"

User::User() :firstName(""), lastName(""), password(""), id(0), points(0) {};
User::User(const MyString& firstName, const MyString& lastName, const MyString& password) :
		firstName(firstName), lastName(lastName), password(password), id(0), points(0)  {};
User::User(const MyString& firstName, const MyString& lastnName, const MyString& password, unsigned id, unsigned points, bool voted)
			:firstName(firstName),lastName(lastName),password(password),id(id),points(points),voted(voted){};

const MyString& User::getFirstName() const {
	return firstName;
}
const MyString& User::getLastName() const {
	return lastName;
}

const MyString& User::getPassword() const {
	return password;
}
std::istream& operator>>(std::istream& is,User& user) {
	std::cout << "Enter First Name:";
	is >> user.firstName;
	std::cout << "Enter Last Name:";
	is >> user.lastName;
	std::cout << "Enter password:";
	is >> user.password;
	return is;
}
std::ostream& operator<<(std::ostream& os,const User& user) {
	std::cout << user.firstName << " " << user.lastName << "," << "having " << user.points << " points." << std::endl;
	return os;
}