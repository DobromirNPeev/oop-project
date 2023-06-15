#include "Topic.h"


Topic::Topic(const MyString& heading, const User& creator, const MyString& description) :heading(heading), creator(&creator), description(description), id(0) {};
Topic::Topic(const MyString& heading,const User& creator, const MyString& description, Vector<Post> posts, unsigned id)
	:heading(heading), creator(&creator), description(description), posts(posts), id(id) {};


const MyString& Topic::getHeading() const
{
	return heading;
};
void Topic::setCreator(const User& newCreator) {
	creator = &newCreator;
}
unsigned Topic::getID() const
{
	return id;
}
std::istream& operator>>(std::istream& is, Topic& topic) {
	std::cout << "Enter Topic title:";
	is >> topic.heading;
	std::cout << "Enter Description:";
	is >> topic.description;
	return is;

}
std::ostream& operator<<(std::ostream& os,const Topic& topic) {
	std::cout << ">>Name:" << topic.heading << std::endl;
	std::cout << ">>Description:" << topic.description<<std::endl;
	std::cout << ">>Created by:" << *(topic.creator);
	std::cout << ">>Question asked:" <<topic.getPosts().getSize()<<std::endl;
	return os;
}


void Topic::setID(unsigned id)
{
	this->id = id;
}

const Vector<Post>& Topic::getPosts() const
{
	return posts;
}
