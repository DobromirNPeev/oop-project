#include "Post.h"


Post::Post(const MyString& heading, const MyString& description) : heading(heading), description(description) {};

const MyString& Post::getHeading() const
{
	return heading;
}
unsigned Post::getID() const
{
	return id;
}

void Post::setID(unsigned id)
{
	this->id = id;
}

unsigned Post::getCommentsCounter() const
{
	return commentsCounter;
}

void Post::increaseCommentsCounter()
{
		commentsCounter++;
}

const Vector<Comment>& Post::getComments() const
{
	return comments;
}

Vector<Comment>& Post::getComments()
{
	return comments;
}


std::ostream& operator<<(std::ostream& os, const Post& post) {
	return os <<"- " << post.heading << " {id:" << post.id << "}" << std::endl;;
}
std::istream& operator>>(std::istream& is, Post& post) {
	std::cout << "Enter title: ";
	is >> post.heading;
	std::cout << "Enter description: ";
	is >> post.description;
	return is;
}