#include "Topic.h"


Topic::Topic(const MyString& heading, const User& creator, const MyString& description) :heading(heading), creator(&creator), description(description), id(0) {};

const MyString& Topic::getHeading() const
{
	return heading;
};
void Topic::setCreator(const User& newCreator) {
	if(creator==nullptr)
		creator = &newCreator;
}
void Topic::setIndexOfCreator(unsigned ind)
{
	indexOfCreator = ind;
}
unsigned Topic::getID() const
{
	return id;
}
std::istream& operator>>(std::istream& is, Topic& topic) {
	std::cout << ENTER_TITLE;
	is >> topic.heading;
	std::cout << ENTER_DESC;
	is >> topic.description;
	return is;

}
std::ostream& operator<<(std::ostream& os,const Topic& topic) {
	std::cout << NAME_PRINT << topic.heading << std::endl;
	std::cout << DESC_PRINT << topic.description<<std::endl;
	std::cout << CREATOR_PRINT << *(topic.creator);
	std::cout << NUMOFQUESTIONS_PRINT <<topic.getPosts().getSize()<<std::endl;
	return os;
}


void Topic::setID(unsigned id)
{
	this->id = id;
}


unsigned Topic::getPostCounter()
{
	return postsCounter;
}


void Topic::increasePostsCounter()
{
		postsCounter++;
}

const Vector<Post>& Topic::getPosts() const
{
	return posts;
}

Vector<Post>& Topic::getPosts()
{
	return posts;
}
