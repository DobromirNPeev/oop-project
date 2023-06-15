#pragma once
#include "User.h"
#include "Topic.h"
#include <fstream>
#include "Vector.hpp"

static const char* OFFSET = "   ";

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

	void printReplies(const Comment& comment,const MyString& offset) const;
	bool containsUser(const User& other) const;
	int containsUser(const MyString& firstName, const MyString& password) const;
	void upvoteLogic(Comment& comment);
	void downvoteLogic(Comment& comment);
	void saveReply(Comment& comment);
	template<typename T>
	int binarySearchViaID(const Vector<T>& arr, int el) const;
	bool searchComment(unsigned id, Comment& toSearch,  void (SocialNetwork::*pred)(Comment&));


	User* loggedUser=nullptr;
	Topic* openedTopic=nullptr;
	Post* openedPost=nullptr;
	Vector<User> users;
	Vector<Topic> topics;
	static unsigned idCount;


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

	SocialNetwork();
	SocialNetwork(const SocialNetwork& other) = delete;
	SocialNetwork& operator=(const SocialNetwork& other) = delete;
	~SocialNetwork();

	void run();
};

