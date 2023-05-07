#pragma once
#include "User.h"

template <class T> class Vector;

class Comment
{
	User creator;
	MyString description;
	Vector<MyString>* replies;
	unsigned upvoteCounter;
	unsigned downvoteCounter;
	static unsigned idCount;
	unsigned id;
public:
	Comment();
	Comment(const User& creator,const MyString& description);
	void IncreaseUpVote();
	void DecreaseUpVote();
	void IncreaseDownVote();
	void DecreaseDownVote();
	unsigned getID() const;
	Vector<MyString> getReplies() const;
};

