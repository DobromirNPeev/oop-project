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
	friend std::ostream& operator<<(std::ostream& os, const Post& post);
	friend std::istream& operator>>(std::istream& is, Post& post);
	const MyString& getHeading() const;
	unsigned getID() const;
	void setID(unsigned id);
	unsigned getCommentsCounter() const;
	void increaseCommentsCounter();
	const Vector<Comment>& getComments() const;
	Vector<Comment>& getComments();
	friend class FileManager;

};
std::ostream& operator<<(std::ostream& os, const Post& post);
std::istream& operator>>(std::istream& is, Post& post);

