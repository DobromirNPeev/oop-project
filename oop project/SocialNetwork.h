#pragma once
#include "User.h"
#include "Topic.h"
#include <fstream>
#include "Vector.hpp"
#include "fileOperations.h"
#include "FactorySingleton.h"


class SocialNetwork
{

	User readUserFromBinaryFile(std::ifstream& ifs);
	Topic readTopicFromBinaryFile(std::ifstream& ifs);
	Post readPostFromBinaryFile(std::ifstream& ifs);
	Comment readCommentFromBinaryFile(std::ifstream& ifs);

	void writeUserToFile(std::ofstream& ofs, const User& user);
	void writeTopicToFile(std::ofstream& ofs, const Topic& topic);
	void writePostToFile(std::ofstream& ofs, const Post& post);
	void writeCommentToFile(std::ofstream& ofs, const Comment& comment);

	void printReplies(const Comment& comment,MyString& offset);
	bool searchComment(unsigned id, const Comment& answer, Comment& toSearch);
	bool searchCommentAndUpvote(unsigned id, Comment& toSearch);
	bool searchCommentAndDownvote(unsigned id, Comment& toSearch);
	int findUser();
	int findTopic(unsigned n);
	bool containsUser(const User& other) const;
	int containsUser(const MyString& firstName, const MyString& password) const;

	//FactorySingleton fac;

	User* loggedUser;
	Topic* openedTopic;
	Post* openedPost;
	Vector<User> users;
	Vector<Topic> topics;
	static unsigned idCount;

	void signup();
	void login();
	void logout();
	void search(const MyString& topicName);
	void create();
	void open(const MyString& topicName);
	void open(unsigned id);
	void post();
	void p_open(const MyString& postName);
	void p_open(unsigned id);
	void comment();
	void comments();
	void reply(unsigned id);
	void upvote(unsigned id);
	void downvote(unsigned id);
	void list();
	void p_quit();
	void quit();
	void whoami();
	void about(unsigned id);
public:

	SocialNetwork();
	
	~SocialNetwork();

	void run();
};

