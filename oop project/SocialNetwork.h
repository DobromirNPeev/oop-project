#pragma once
#include "Vector.h"
#include "LoggedUser.h"

class SocialNetwork: public UniquePtr<User>,public UniquePtr<Topic>
{

	bool containsUser(const User& other) const;
	int containsUser(const char* firstName, const char* password) const;
	Vector<User> users;
	Vector<Topic> topics;
	static unsigned idCount;
	//int findLoggedUser();
public:

	bool signup();
	bool login(const char* name,const char* password);
	void search(const char* topicName);
	void create();
	void open(const char* topicName);
	void open(unsigned id);
};

