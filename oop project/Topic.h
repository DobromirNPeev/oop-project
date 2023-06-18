#pragma once
#include "User.h"
#include "Constants.h"
#include "Post.h"
#include "Vector.hpp"

class Topic
{
	MyString heading="";
	const User* creator=nullptr;
	unsigned indexOfCreator=0;
	Vector<Post> posts;
	MyString description="";
	unsigned id=0;
	unsigned postsCounter=0;
public:
	Topic()=default;
	Topic(const MyString& heading, const User& creator, const MyString& description);
	const MyString& getHeading() const;
	void setCreator(const User& newCreator);
	void setIndexOfCreator(unsigned ind);
	unsigned getID() const;
	void setID(unsigned id);
	void increasePostsCounter();
	unsigned getPostCounter();
	friend std::istream& operator>>(std::istream& is, Topic& topic);
	friend std::ostream& operator<<(std::ostream& os,const Topic& topic);
	const Vector<Post>& getPosts() const;
	Vector<Post>& getPosts();
	friend class FileManager;

};
std::istream& operator>>(std::istream& is, Topic& topic);
std::ostream& operator<<(std::ostream& os,const Topic& topic);