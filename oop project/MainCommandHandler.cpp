#include "MainCommandHandler.h"
#include "SocialNetwork.h"
#include "binarySearchViaID.hpp"

MainCommandHandler::MainCommandHandler(SocialNetwork& sn) :sn(&sn),moreCommands(sn) {};

namespace {
	bool isPrefix(const char* pattern, const char* text)
	{
		while (*text != '\0' && *pattern != '\0')
		{
			if (*text != *pattern)
				return false;
			text++;
			pattern++;
		}
		return *pattern == '\0';
	}

	bool searchInText(const char* text, const char* pattern)
	{
		size_t textLen = strlen(text);
		size_t patternLen = strlen(pattern);
		while (patternLen <= textLen)
		{
			if (isPrefix(pattern, text))
				return true;
			text++;
			textLen--;
		}
		return false;
	}

}
void MainCommandHandler::signup() {
	User current;
	std::cin >> current;
	if (moreCommands.containsUser(current)) {
		std::cout <<USER_EXISTS << std::endl;
		return;
	}
	current.setID(sn->idCount++);
	sn->users.pushBack(std::move(current));
	std::cout << SUCCESS<<std::endl;
}

void MainCommandHandler::login() {
	MyString name;
	MyString password;
	std::cout << TYPE_FIRST_NAME;
	std::cin >> name;
	std::cout << TYPE_PASSWORD;
	std::cin >> password;
	int i = 0;
	if ((i = moreCommands.containsUser(name,password)) == -1) {
		std::cout << USER_NOT_EXISTS << std::endl;
		return;
	}
	std::cout << WELCOME_USER << name << std::endl;
	sn->loggedUser = &sn->users[i];
}

void MainCommandHandler::logout()
{
	std::cout << LOGOUT_MESSAGE << sn->loggedUser->getFirstName() << " " << sn->loggedUser->getLastName() << std::endl;
	sn->loggedUser = nullptr;
}

void MainCommandHandler::search(const MyString& topicName) const
{
	for (size_t i = 0; i < sn->topics.getSize(); i++) {
		if (searchInText(sn->topics[i].getHeading().c_str(), topicName.c_str())) {
			std::cout << "-  " << sn->topics[i].getHeading() << ID_PRINTING << sn->topics[i].getID() << "}" << std::endl;
			return;
		}
	}
	std::cout << TOPIC_NOT_EXISTS << std::endl;
}

void MainCommandHandler::create() {
	Topic newTopic;
	std::cin >> newTopic;
	newTopic.setID(sn->idCount++);
	newTopic.setCreator(*sn->loggedUser);
	newTopic.setIndexOfCreator(moreCommands.binarySearchViaID(sn->users, sn->loggedUser->getID()));
	sn->topics.pushBack(std::move(newTopic));

}

void MainCommandHandler::open(const MyString& topicName) {
	for (size_t i = 0; i < sn->topics.getSize(); i++)
	{
		if (searchInText(sn->topics[i].getHeading().c_str(), topicName.c_str())) {
			std::cout << WELCOME_TOPIC << sn->topics[i].getHeading() << std::endl;
			sn->openedTopic = &sn->topics[i];
			return;
		}
	}
	std::cout << TOPIC_NOT_EXISTS << std::endl;
}

void MainCommandHandler::open(unsigned id) {
	int i = moreCommands.binarySearchViaID(sn->topics, id);
	if (i == -1) {
		std::cout << TOPIC_NOT_EXISTS << std::endl;
	}
	else {
		std::cout << WELCOME_TOPIC << sn->topics[i].getHeading()<< std::endl;
		sn->openedTopic = &sn->topics[i];
	}
}

void MainCommandHandler::post() {
	Post newPost;
	std::cin >> newPost;
	newPost.setID(sn->openedTopic->getPostCounter());
	sn->openedTopic->getPosts().pushBack(std::move(newPost));
	sn->openedTopic->increasePostsCounter();
}
void MainCommandHandler::p_open(const MyString& postName) {
	int size = sn->openedTopic->getPosts().getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (searchInText(sn->openedTopic->getPosts()[i].getHeading().c_str(), postName.c_str())) {
			std::cout << sn->openedTopic->getPosts()[i];
			sn->openedPost = &(sn->openedTopic->getPosts()[i]);
			return;
		}
	}
	std::cout << POST_NOT_EXISTS<< std::endl;
}


void MainCommandHandler::p_open(unsigned id) {
	int i = moreCommands.binarySearchViaID(sn->openedTopic->getPosts(), id);
	if (i == -1) {
		std::cout << POST_NOT_EXISTS << std::endl;
	}
	else {
		sn->openedPost = &(sn->openedTopic->getPosts()[i]);
		std::cout << "Q:" << sn->openedTopic->getPosts()[i].getHeading()<<std::endl;
	}
}

void MainCommandHandler::comment() {
	Comment comment;
	std::cout << SAY_SOMETHING;
	std::cin >> comment;
	sn->loggedUser->IncreasePoints();
	comment.setID(sn->openedPost->getCommentsCounter());
	sn->openedPost->getComments().pushBack(std::move(comment));
	sn->openedPost->increaseCommentsCounter();
}

void MainCommandHandler::comments() const {
	if (sn->openedPost->getComments().getSize() == 0) {
		std::cout << NO_COMMENTS << std::endl;
		return;
	}
	MyString offset(OFFSET);
	for (size_t i = 0; i < sn->openedPost->getComments().getSize(); i++)
	{
		std::cout << sn->openedPost->getComments()[i];
		moreCommands.printReplies(sn->openedPost->getComments()[i], offset);
	}
}

void MainCommandHandler::reply(unsigned id) {
	for (size_t i = 0; i < sn->openedPost->getComments().getSize(); i++)
	{
		//Обхожда корените
		if (sn->openedPost->getComments()[i].getID() == id) {
			moreCommands.saveReply(sn->openedPost->getComments()[i]);
			return;
		}
		else if (sn->openedPost->getComments()[i].getReplies().getSize() > 0) {
			if (moreCommands.searchComment(id, sn->openedPost->getComments()[i], &AdditionalCommands::saveReply))
				return;
		}
	}
	std::cout << COMMENT_NOT_EXISTS << std::endl;
}

void MainCommandHandler::upvote(unsigned id) {
	for (size_t i = 0; i < sn->openedPost->getComments().getSize(); i++)
	{
		//Обхожда корените
		if (sn->openedPost->getComments()[i].getID() == id) {
			moreCommands.upvoteLogic(sn->openedPost->getComments()[i]);
			return;
		}
		else if (sn->openedPost->getComments()[i].getReplies().getSize() > 0) {
			if (moreCommands.searchComment(id, sn->openedPost->getComments()[i], &AdditionalCommands::upvoteLogic))
				return;
		}
	}
	std::cout << COMMENT_NOT_EXISTS << std::endl;

}

void MainCommandHandler::downvote(unsigned id) {
	//Обхожда корените
	for (size_t i = 0; i < sn->openedPost->getComments().getSize(); i++)
	{
		if (sn->openedPost->getComments()[i].getID() == id) {
			moreCommands.downvoteLogic(sn->openedPost->getComments()[i]);
			return;
		}
		else if (sn->openedPost->getComments()[i].getReplies().getSize() > 0) {
			if (moreCommands.searchComment(id, sn->openedPost->getComments()[i], &AdditionalCommands::downvoteLogic))
				return;
		}
	}
	std::cout << COMMENT_NOT_EXISTS << std::endl;
}

void MainCommandHandler::list() const {
	unsigned numberOfPosts = sn->openedTopic->getPosts().getSize();
	if (numberOfPosts == 0) {
		std::cout << NO_POSTS << std::endl;
		return;
	}
	for (size_t i = 0; i < numberOfPosts; i++)
	{
		std::cout << sn->openedTopic->getPosts()[i];
	}
}

void MainCommandHandler::p_quit() {
	std::cout << POST_QUIT_MESSAGE << sn->openedPost->getHeading() << std::endl;
	sn->openedPost = nullptr;
}

void MainCommandHandler::quit() {
	std::cout << TOPIC_QUIT_MESSAGE << sn->openedTopic->getHeading()<< std::endl;
	sn->openedTopic = nullptr;
	//sn->openedPost = nullptr;
}

void MainCommandHandler::whoami() const {
	std::cout << *(sn->loggedUser);
}

void MainCommandHandler::about(unsigned id) const {
	int topicId = moreCommands.binarySearchViaID(sn->topics, id);
	if (topicId == -1) {
		std::cout << TOPIC_NOT_EXISTS << std::endl;
		return;
	}
	std::cout <<sn-> topics[topicId];
}
namespace {
	unsigned int convertFromChar(char ch)
	{
		if (ch < '0' || ch > '9')
			return 10;
		return ch - '0';
	}

	unsigned int fromString(const char* str)
	{
		unsigned int result = 0;
		while (*str != '\0')
		{
			int currentDigit = convertFromChar(*str);
			if (currentDigit == 10) {
				return -1;
			}
			(result *= 10) += currentDigit;
			str++;
		}
		return result;
	}
}
void MainCommandHandler::execute(const MyString& command) {
	if (!moreCommands.checkAcces(command)) {
		return;
	}
	if (command == SIGNUP) {
		signup();
	}
	else if (command == LOGIN) {
		login();
	}
	else if (command == LOGOUT) {

		logout();
	}
	else if (command == SEARCH) {
		static MyString topicName;
		std::cout << ENTER_KEYWORD;
		std::cin >> topicName;
		search(topicName);
	}
	else if (command == CREATE) {
		create();
	}
	else if (command == OPEN) {
		static MyString topicName;
		std::cout << ENTER_ID_OR_NAME;
		std::cin >> topicName;
		int id = fromString(topicName.c_str());
		if (id == -1) {
			open(topicName.c_str());
		}
		else {
			open(id);
		}

	}
	else if (command == P_OPEN) {
		static MyString topicName;
		std::cout << ENTER_ID_OR_NAME;
		std::cin >> topicName;
		int id = fromString(topicName.c_str());
		if (id == -1) {
			p_open(topicName.c_str());
		}
		else {
			p_open(id);
		}
	}
	else if (command == POST) {
		post();
	}
	else if (command == COMMENT) {
		comment();
	}
	else if (command == COMMENTS) {
		comments();
	}
	else if (command == REPLY) {
		unsigned id;
		std::cout << ENTER_ID;
		std::cin >> id;
		std::cin.ignore();
		reply(id);
	}
	else if (command == UPVOTE) {
		unsigned id;
		std::cout << ENTER_ID;
		std::cin >> id;
		std::cin.ignore();
		upvote(id);
	}
	else if (command == DOWNVOTE) {
		unsigned id;
		std::cout << ENTER_ID;
		std::cin >> id;
		std::cin.ignore();
		downvote(id);
	}
	else if (command == LIST) {
		list();
	}
	else if (command == P_QUIT) {
		p_quit();
	}
	else if (command == QUIT) {
		quit();
	}
	else if (command == WHOAMI) {
		whoami();
	}
	else if (command == ABOUT) {
		unsigned id;
		std::cout << ENTER_ID;
		std::cin >> id;
		std::cin.ignore();
		about(id);
	}
	else {
		std::cout << INVALID_COMMAND << std::endl;
	}
	std::cout << std::endl;
}