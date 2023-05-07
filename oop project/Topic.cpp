#include "Topic.h"

Topic::Topic() :heading(""), description(""),posts(nullptr){};
Topic::Topic(const char* heading, const User& creator, const char* description): heading(heading), creator(creator), description(description),id(0),posts(0) {}

const char* Topic::getHeading()
{
	return heading.c_str();
};
void Topic::setCreator(const User& newCreator) {
	creator = newCreator;
}
std::istream& operator>>(std::istream& is, Topic& topic) {
	std::cout << "Enter Topic title:";
	is >> topic.heading;
	std::cout << "Enter Description:";
	is >> topic.description;
	return is;

}
//void Topic::setAcces() {
//	if (!openedTopic) {
//		openedTopic = true;
//	}
//	else {
//		openedTopic = false;
//	}
//}
unsigned Topic::getID() {
	return id;
}


void Topic::setID(unsigned id)
{
	this->id = id;
}

Vector<Post>* Topic::getPosts() const
{
	return posts;
}
