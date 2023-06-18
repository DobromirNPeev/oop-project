#pragma once
#include "User.h"
#include "Vector.hpp"
#include "Constants.h"

class Comment
{
	const User* creator=nullptr;
	size_t indexOfCreator=0;
	MyString description="";
	Vector<Comment> replies;

	Vector<int> IDsofUpvoters;
	Vector<int> IDsofDownvoters;
	
	unsigned upvoteCounter=0;
	unsigned downvoteCounter=0;
	unsigned id=0;
public:
	Comment()=default;
	Comment(const User& creator,const MyString& description);
	void IncreaseUpVote();
	void DecreaseUpVote();
	void IncreaseDownVote();
	void DecreaseDownVote();
	unsigned getID() const;
	void setID(unsigned id);
	void setCreator(const User& user);
	int didUserUpvoted(unsigned id)const;
	int didUserDownvoted(unsigned id)const;
	const Vector<Comment>& getReplies() const;
	Vector<Comment>& getReplies();

	const Vector<int>& getIDsofUpvoters()const;
	Vector<int>& getIDsofUpvoters();

	const Vector<int>& getIDsofDownvoters()const;
	Vector<int>& getIDsofDownvoters();
	friend std::istream& operator>>(std::istream& is, Comment& comment);
	friend std::ostream& operator<<(std::ostream& os,const Comment& comment);
	friend class FileManager;

};
std::istream& operator>>(std::istream& is, Comment& comment);
std::ostream& operator<<(std::ostream& os, const Comment& comment);


