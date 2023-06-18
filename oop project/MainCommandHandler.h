#pragma once
#include "MyString.h"
#include "AdditionalCommands.h"

class SocialNetwork;

class MainCommandHandler
{
	SocialNetwork* sn;
	AdditionalCommands moreCommands;

	void signup();
	void login();
	void logout();
	void search(const MyString& topicName) const;
	void create();
	void open(const MyString& topicName);
	void open(unsigned id);
	void post();
	void p_open(const MyString& postName);
	void p_open(unsigned id);
	void comment();
	void comments() const;
	void reply(unsigned id);
	void upvote(unsigned id);
	void downvote(unsigned id);
	void list() const;
	void p_quit();
	void quit();
	void whoami() const;
	void about(unsigned id) const;
public:
	MainCommandHandler(SocialNetwork& sn);
	MainCommandHandler(const MainCommandHandler& other) = delete;
	MainCommandHandler& operator=(const MainCommandHandler& other) = delete;
	void execute(const MyString& command);
};

