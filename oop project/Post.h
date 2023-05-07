#pragma once
#include "MyString.h"
#include "Comment.h"

template <class T> class Vector;

class Post
{
	MyString heading;
	MyString description;
	Vector<Comment>* comments;
	static unsigned idCount;
	unsigned id;
public:
	Post();
	Post(const MyString& heading, const MyString& description);
	friend std::ostream& operator<<(std::ostream& os, const Post& post);
	const MyString& getHeading() const;
	unsigned getID() const;
	Vector<Comment>* getComments();
};
std::ostream& operator<<(std::ostream& os, const Post& post);

