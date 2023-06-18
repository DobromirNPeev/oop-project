#pragma once
#include "User.h"
#include "Topic.h"
class SocialNetwork;

class AdditionalCommands
{
	SocialNetwork* sn;
	void printReplies(const Comment& comment, const MyString& offset) const;
	bool containsUser(const User& other) const;
	int containsUser(const MyString& firstName, const MyString& password) const;
	void upvoteLogic(Comment& comment);
	void downvoteLogic(Comment& comment);
	void saveReply(Comment& comment);
	template<typename T>
	int binarySearchViaID(const Vector<T>& arr, int el) const;
	bool searchComment(unsigned id, Comment& toSearch, void (AdditionalCommands::* pred)(Comment&));
	bool checkAcces(const MyString& command) const;
public:
	AdditionalCommands(SocialNetwork& sn);
	AdditionalCommands(const AdditionalCommands& other) = delete;
	AdditionalCommands& operator=(const AdditionalCommands& other)=delete;
	friend class MainCommandHandler;
};

