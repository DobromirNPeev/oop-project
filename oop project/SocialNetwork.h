#pragma once
#include "Vector.h"
#include "LoggedUser.h"
#include <fstream>

class SocialNetwork
{

	bool containsUser(const User& other) const;
	int containsUser(const MyString& firstName, const MyString& password) const;
	UniquePtr<User> loggedUser;
	UniquePtr<Topic> openedTopic;
	UniquePtr<Post> openedPost;
	Vector<User> users;
	Vector<Topic> topics;
	static unsigned idCount;
	//int findLoggedUser();
public:

	SocialNetwork();
	bool signup();
	bool login(const MyString& name,const MyString& password);
	void search(const MyString& topicName);
	void create();
	void open(const MyString& topicName);
	void open(unsigned id);
	void list();
	void post(const MyString& title, const MyString& description);
	void p_open(const MyString& postName);
	void p_open(unsigned id);
	void comment(const MyString& description);
	void reply(unsigned id);
	void upvote(unsigned id);
	void downvote(unsigned id);
	void p_quit();
	void quit();
	void logout();
};

