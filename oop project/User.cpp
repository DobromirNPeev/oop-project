#include "User.h"


User::User(const MyString& firstName, const MyString& lastName, const MyString& password) :
		firstName(firstName), lastName(lastName), password(password), id(0), points(0)  {};
const MyString& User::getFirstName() const {
	return firstName;
}
const MyString& User::getLastName() const {
	return lastName;
}

bool User::comparePassword(const MyString& password) const
{
	return this->password == password;
}

unsigned User::getID() const
{
	return id;
}

void User::setID(unsigned id)
{
	this->id = id;
}

void User::IncreasePoints()
{
	points++;
}

bool User::operator==(const User& other) const
{
	return firstName == other.firstName && lastName == other.lastName && password == other.password;
}

std::istream& operator>>(std::istream& is,User& user) {
	std::cout << TYPE_FIRST_NAME;
	is >> user.firstName;
	std::cout << TYPE_LAST_NAME;
	is >> user.lastName;
	std::cout << TYPE_PASSWORD;
	is >> user.password;
	return is;
}
std::ostream& operator<<(std::ostream& os,const User& user) {
	std::cout << user.firstName << " " << user.lastName << ", " << "having " << user.points << " points." << std::endl;
	return os;
}