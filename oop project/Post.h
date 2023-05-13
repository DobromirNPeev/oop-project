#pragma once
#include "MyString.h"
#include "Comment.h"
#include "Vector.hpp"

class Post
{
	MyString heading;
	MyString description;
	Vector<Comment> comments;
	static unsigned idCount;
	unsigned id;
public:
	Post();
	Post(const MyString& heading, const MyString& description);
	Post(const MyString& heading, const MyString& description, const Vector<Comment>& comments,unsigned id);
	friend std::ostream& operator<<(std::ostream& os, const Post& post);
	friend std::istream& operator>>(std::istream& is, Post& post);
	const MyString& getHeading() const;
	unsigned getID() const;
	Vector<Comment> getComments();
	friend class SocialNetwork;
};
std::ostream& operator<<(std::ostream& os, const Post& post);
std::istream& operator>>(std::istream& is, Post& post);

