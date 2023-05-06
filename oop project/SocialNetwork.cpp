#include "SocialNetwork.h"

unsigned SocialNetwork::idCount = 0;
bool SocialNetwork::signup() {
	User current;
	std::cin >> current;
	current.id=SocialNetwork::idCount++;
	if (!containsUser(current)) {
		return false;
	}
	users.pushBack(current);
	return true;
}
bool SocialNetwork::login(const char* name, const char* password) {
	int i = 0;
	if (i=(containsUser(name,password)==-1)) {

		return false;
	}
	UniquePtr<User>::set(&users[i]);
	return true;
}
bool isPrefix(const char* pattern, const char* text)
{
	while (*text != '\0' && *pattern != '\0')
	{
		if (*text != *pattern)
			return false;
		text++;
		pattern++;
	}
	return *pattern == '\0';
}

bool searchInText(const char* text, const char* pattern)
{
	size_t textLen = strlen(text);
	size_t patternLen = strlen(pattern);
	while (patternLen <= textLen)
	{
		if (isPrefix(pattern, text))
			return true;
		text++;
		textLen--;
	}
	return false;
}
//int SocialNetwork::findLoggedUser() {
//	for (size_t i = 0; i < users.getSize(); i++)
//	{
//		if (users[i].loggedIn) {
//			return i;
//		}
//	}
//}
void SocialNetwork::open(const char* topicName) {
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (searchInText(topics[i].getHeading(), topicName)) {
				UniquePtr<Topic>::set(&topics[i]);
		}
	}
}
void SocialNetwork::open(unsigned id) {
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (topics[i].getID() == id) {
			UniquePtr<Topic>::set(&topics[i]);
		}
	}
}
void SocialNetwork::create() {
	Topic newTopic;
	std::cin >> newTopic;
	newTopic.setID(idCount++);
	newTopic.setCreator(*(UniquePtr<User>::get()));
	topics.pushBack(newTopic);

}
void SocialNetwork::search(const char* topicName)
{
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (searchInText(topics[i].getHeading(), topicName)) {
			std::cout<<"-  "<<topics[i].getHeading();
		}
	}
}
bool SocialNetwork::containsUser(const User& other) const {
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (!strcmp(users[i].firstName.c_str(), other.firstName.c_str()) && !strcmp(users[i].lastName.c_str(), other.lastName.c_str()));
		return false;
	}
	return true;
}
int SocialNetwork::containsUser(const char* firstName, const char* password) const {

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (!strcmp(users[i].firstName.c_str(), firstName) && !strcmp(users[i].password.c_str(), password));
		return i;
	}
	return -1;
}