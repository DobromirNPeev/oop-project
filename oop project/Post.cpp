#include "Post.h"


Post::Post() : Post("", "") {};
Post::Post(const MyString& heading, const MyString& description) : heading(heading), description(description) {};
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
	return os <<"- " << post.heading << " {id:" << post.id << "}" << std::endl;;
}
std::istream& operator>>(std::istream& is, Post& post) {
	std::cout << "Enter title: ";
	is >> post.heading;
	std::cout << "Enter description: ";
	is >> post.description;
	return is;
}