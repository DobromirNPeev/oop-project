#pragma once
#include "MyString.h"
#include "Comment.h"
#include "Vector.hpp"

class Post
{
	MyString heading="";
	MyString description="";
	Vector<Comment> comments;
	unsigned commentsCounter = 0;
	unsigned id=0;
public:
	Post()=default;
	Post(const MyString& heading, const MyString& description);
	Post(const MyString& heading, const MyString& description, const Vector<Comment>& comments,unsigned id);
	friend std::ostream& operator<<(std::ostream& os, const Post& post);
	friend std::istream& operator>>(std::istream& is, Post& post);
	const MyString& getHeading() const;
	unsigned getID() const;
	const Vector<Comment>& getComments() const;
	friend class SocialNetwork;
};
std::ostream& operator<<(std::ostream& os, const Post& post);
std::istream& operator>>(std::istream& is, Post& post);

