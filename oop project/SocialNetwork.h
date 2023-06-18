#pragma once
#include "Constants.h"
#include "MainCommandHandler.h"
#include "AdditionalCommands.h"
#include "FileManager.h"

class SocialNetwork
{
	User* loggedUser=nullptr;
	Topic* openedTopic=nullptr;
	Post* openedPost=nullptr;
	Vector<User> users;
	Vector<Topic> topics;
	static unsigned idCount;
	MainCommandHandler commands;
	FileManager files;
	friend class MainCommandHandler;
	friend class AdditionalCommands;
	friend class FileManager;

public:

	SocialNetwork();
	SocialNetwork(const SocialNetwork& other) = delete;
	SocialNetwork& operator=(const SocialNetwork& other) = delete;
	~SocialNetwork();

	void run();
};

