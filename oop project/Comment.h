#pragma once
#include "User.h"
#include "Vector.hpp"


class Comment
{
	const User* creator=nullptr;
	size_t indexOfCreator=0;
	MyString description="";
	Vector<Comment> replies;
	Vector<int> indexesOfUpvoters;
	Vector<int> indexesOfDownvoters;
	
	unsigned upvoteCounter=0;
	unsigned downvoteCounter=0;
	unsigned id=0;
	int didUserUpvoted(unsigned id) const;
	int didUserDownvoted(unsigned id) const;
public:
	Comment()=default;
	Comment(const User& creator,const MyString& description);
	Comment(const User& creator,const MyString& description,Vector<MyString> replies,unsigned upvoteCounter,unsigned downvoteCounter,unsigned idCount,unsigned id);
	void IncreaseUpVote();
	void DecreaseUpVote();
	void IncreaseDownVote();
	void DecreaseDownVote();
	unsigned getID() const;
	friend std::istream& operator>>(std::istream& is, Comment& comment);
	friend std::ostream& operator<<(std::ostream& os,const Comment& comment);
	friend class SocialNetwork;
};
std::istream& operator>>(std::istream& is, Comment& comment);
std::ostream& operator<<(std::ostream& os, const Comment& comment);


