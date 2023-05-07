#pragma once
#include "User.h"
#include "Post.h"

template <class T> class Vector;

class Topic
{
	MyString heading;
	User creator;
	Vector<Post>* posts;
	MyString description;
	unsigned id;
public:
	Topic();
	Topic(const char* heading, const User& creator, const char* description);
	const char* getHeading();
	void setCreator(const User& newCreator);
	//void setAcces();
	unsigned getID();
	void setID(unsigned id);
	friend std::istream& operator>>(std::istream& is, Topic& topic);
	Vector<Post>* getPosts() const;
};
std::istream& operator>>(std::istream& is, Topic& topic);