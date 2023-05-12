#pragma once
#include "User.h"
#include "Vector.hpp"


class Comment
{
	const User* creator;
	size_t indexOfCreator=0;
	MyString description;
	Vector<MyString> replies;
	unsigned upvoteCounter;
	unsigned downvoteCounter;
	static unsigned idCount;
	unsigned id;
public:
	Comment();
	Comment(const User& creator,const MyString& description);
	Comment(const User& creator,const MyString& description,Vector<MyString> replies,unsigned upvoteCounter,unsigned downvoteCounter,unsigned idCount,unsigned id);
	void IncreaseUpVote();
	void DecreaseUpVote();
	void IncreaseDownVote();
	void DecreaseDownVote();
	unsigned getID() const;
	Vector<MyString> getReplies() const;
	friend class SocialNetwork;
};

