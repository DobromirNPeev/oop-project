#include "User.h"

User::User() :firstName(""), lastName(""), password(""), id(0), points(0) {};
User::User(const char* firstName, const char* lastName, const char* password) :
		firstName(firstName), lastName(lastName), password(password), id(0), points(0)  {};
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
	return is >> user.firstName >> user.lastName >> user.password;
}