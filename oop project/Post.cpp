#include "Post.h"

unsigned Post::idCount=0;

Post::Post() :Post("", "") {};
Post::Post(const MyString& heading, const MyString& description) : heading(heading), description(description), id(idCount++) {};
Post::Post(const MyString& heading, const MyString& description,const Vector<Comment>& comments, unsigned id):
			heading(heading),description(description),comments(comments),id(id){};

const MyString& Post::getHeading() const
{
	return heading;
}
unsigned Post::getID() const
{
	return id;
}
Vector<Comment> Post::getComments() 
{
	return comments;
};
std::ostream& operator<<(std::ostream& os, const Post& post) {
	return os <<"-  "<< post.heading;
}