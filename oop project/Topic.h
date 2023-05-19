#pragma once
#include "User.h"
#include "Post.h"
#include "Vector.hpp"

class Topic
{
	MyString heading;
	const User* creator=nullptr;
	size_t indexOfCreator=0;
	Vector<Post> posts;
	MyString description;
	unsigned id=0;
	unsigned postsCounter=0;
public:
	Topic();
	Topic(const MyString& heading, const User& creator, const MyString& description);
	Topic(const MyString& heading,const User& creator, const MyString& description,Vector<Post> posts,unsigned id);
	const char* getHeading();
	void setCreator(const User& newCreator);
	//void setAcces();
	unsigned getID();
	void setID(unsigned id);
	friend std::istream& operator>>(std::istream& is, Topic& topic);
	friend std::ostream& operator<<(std::ostream& os,const Topic& topic);
	Vector<Post> getPosts() const;
	friend class SocialNetwork;
};
std::istream& operator>>(std::istream& is, Topic& topic);
std::ostream& operator<<(std::ostream& os,const Topic& topic);