﻿#include "SocialNetwork.h"


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
void SocialNetwork::signup() {
	User current;
	std::cin >> current;
	current.id = SocialNetwork::idCount++;
	if (!containsUser(current)) {
		std::cout << "User already exists" << std::endl;
		return;
	}
	users.pushBack(current);
}

void SocialNetwork::login() {
	if (loggedUser != nullptr) {
		std::cout << "Already logged in" << std::endl;
		return;
	}
	MyString name;
	MyString password;
	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "password: ";
	std::cin >> password;
	int i = 0;
	if ((i = containsUser(name, password)) == -1) {
		std::cout << "Incorrect, please try again" << std::endl;
		return;
	}
	std::cout << "Welcome " << name << std::endl;
	loggedUser = &users[i];
}

void SocialNetwork::logout()
{
	if (loggedUser == nullptr) {
		std::cout << "Can't log out, no logged user" << std::endl;
		return;
	}
	std::cout << "Goodbye," << loggedUser->firstName << " " << loggedUser->lastName << std::endl;
	loggedUser = nullptr;
	openedTopic = nullptr;
	openedPost = nullptr;
}

void SocialNetwork::search(const MyString& topicName)
{
	if (loggedUser == nullptr) {
		std::cout << "No logged user, can't open a topic" << std::endl;
		return;
	}
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (searchInText(topics[i].getHeading(), topicName.c_str())) {
			std::cout << "-  " << topics[i].getHeading() << "{id:" << topics[i].id << "}" << std::endl;
		}
	}
}

void SocialNetwork::create() {
	if (loggedUser == nullptr) {
		std::cout << "Cannot create" << std::endl;
		return;
	}

	Topic newTopic;
	std::cin >> newTopic;
	newTopic.setID(idCount++);
	newTopic.setCreator(*loggedUser);
	newTopic.indexOfCreator = findUser();
	topics.pushBack(newTopic);

}

void SocialNetwork::open(const MyString& topicName) {
	if (loggedUser == nullptr || openedTopic != nullptr) {
		std::cout << "Cannot acces topic" << std::endl;
		return;
	}
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (searchInText(topics[i].getHeading(), topicName.c_str())) {
			std::cout << "Welcome to " << topics[i].heading << std::endl;
			openedTopic = &topics[i];
			return;
		}
	}
	std::cout << "No such topic" << std::endl;
}

void SocialNetwork::open(unsigned id) {
	if (loggedUser == nullptr) {
		std::cout << "Cannot acces topic" << std::endl;
		return;
	}
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (topics[i].getID() == id) {
			std::cout << "Welcome to " << topics[i].heading << std::endl;
			openedTopic = &topics[i];
			return;
		}
	}
	std::cout << "No such topic" << std::endl;
}

void SocialNetwork::post() {
	if (openedTopic == nullptr || loggedUser == nullptr) {
		std::cout << "Cannot post" << std::endl;
		return;
	}
	Post newPost;
	std::cin >> newPost;
	newPost.id = openedTopic->postsCounter++;
	openedTopic->posts.pushBack(newPost);
}
void SocialNetwork::p_open(const MyString& postName) {
	if (loggedUser == nullptr || openedTopic == nullptr) {
		std::cout << "Cannot acces post" << std::endl;
		return;
	}
	int size = openedTopic->getPosts().getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (searchInText(openedTopic->getPosts()[i].getHeading().c_str(), postName.c_str())) {
			std::cout << "Q: " << openedTopic->getPosts()[i];
			openedPost=&(openedTopic->posts[i]);
			return;
		}
	}
	std::cout << "No such post" << std::endl;
}


void SocialNetwork::p_open(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost != nullptr) {
		std::cout << "Cannot acces post" << std::endl;
		return;
	}
	int size = openedTopic->getPosts().getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (openedTopic->getPosts()[i].getID() == id) {
			openedPost = &(openedTopic->posts[i]);
			std::cout << "Q: " << openedTopic->getPosts()[i];
			return;
		}
	}
	std::cout << "No such post" << std::endl;

}

void SocialNetwork::comment() {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot comment" << std::endl;
		return;
	}
	Comment comment;
	std::cout << "Say something: ";
	std::cin >> comment;
	loggedUser->points++;
	comment.id = openedPost->commentsCounter++;
	openedPost->comments.pushBack(comment);
}

void SocialNetwork::comments() {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot see comments" << std::endl;
		return;
	}
	MyString offset(OFFSET);
	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		std::cout << openedPost->comments[i];
		printReplies(openedPost->comments[i], offset);
	}
}

void SocialNetwork::reply(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot reply" << std::endl;
		return;
	}

	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		if (openedPost->comments[i].id == id) {
			std::cout << "Say somehting: ";
			Comment answer;
			std::cin >> answer;
			answer.creator = loggedUser;
			answer.id = openedPost->commentsCounter++;
			openedPost->comments[i].replies.pushBack(answer);
			loggedUser->points++;
			std::cout << "Posted" << std::endl;
			return;
		}
		else {
			if (searchComment(id, openedPost->comments[i]))
				return;
		}
	}
	std::cout << "No such comment" << std::endl;
}

void SocialNetwork::upvote(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot upvote" << std::endl;
		return;
	}
	//Обхожда корените
	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		int searchUpvoted = openedPost->comments[i].didUserUpvoted(loggedUser->id);
		int searchDownvoted = openedPost->comments[i].didUserDownvoted(loggedUser->id);
		if (openedPost->comments[i].id == id && searchUpvoted == -1 && searchDownvoted == -1) {
			openedPost->comments[i].IncreaseUpVote();
			openedPost->comments[i].indexesOfUpvoters.pushBack(loggedUser->id);
			break;
		}
		else if (openedPost->comments[i].id == id && searchUpvoted != -1) {
			openedPost->comments[i].DecreaseUpVote();
			openedPost->comments[i].indexesOfUpvoters.popAt(searchUpvoted);
			break;
		}
		else if (openedPost->comments[i].id == id && searchDownvoted != -1) {
			openedPost->comments[i].IncreaseUpVote();
			openedPost->comments[i].DecreaseDownVote();
			openedPost->comments[i].indexesOfUpvoters.pushBack(loggedUser->id);
			openedPost->comments[i].indexesOfDownvoters.popAt(searchDownvoted);
			break;
		}
		else if (openedPost->comments[i].replies.getSize() > 0) {
			if (searchCommentAndUpvote(id, openedPost->comments[i]))
				return;
		}
	}
}

void SocialNetwork::downvote(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot upvote" << std::endl;
		return;
	}
	//Обхожда корените
	for (size_t i = 0; i < openedPost->getComments().getSize(); i++)
	{
		int searchUpvoted = openedPost->comments[i].didUserUpvoted(loggedUser->id);
		int searchDownvoted = openedPost->comments[i].didUserDownvoted(loggedUser->id);

		if (openedPost->comments[i].id == id && searchUpvoted == -1 && searchDownvoted == -1) {
			openedPost->comments[i].IncreaseDownVote();
			openedPost->comments[i].indexesOfDownvoters.pushBack(loggedUser->id);
			return;
		}
		else if (openedPost->comments[i].id == id && searchDownvoted != -1) {
			openedPost->comments[i].DecreaseDownVote();
			openedPost->comments[i].indexesOfDownvoters.popAt(searchUpvoted);
			return;
		}
		else if (openedPost->comments[i].id == id && searchUpvoted != -1) {
			openedPost->comments[i].DecreaseUpVote();
			openedPost->comments[i].IncreaseDownVote();
			openedPost->comments[i].indexesOfDownvoters.pushBack(loggedUser->id);
			openedPost->comments[i].indexesOfUpvoters.popAt(searchUpvoted);
			return;
		}
		else if (openedPost->comments[i].replies.getSize() > 0) {
			if (searchCommentAndDownvote(id, openedPost->comments[i]))
				return;
		}
	}
}

void SocialNetwork::list() {
	if (loggedUser == nullptr || openedTopic == nullptr) {
		std::cout << "Cannot acces posts" << std::endl;
		return;
	}
	unsigned numberOfPosts = openedTopic->getPosts().getSize();
	for (size_t i = 0; i < numberOfPosts; i++)
	{
		std::cout << openedTopic->getPosts()[i];
	}
}

void SocialNetwork::p_quit() {
	if (openedTopic == nullptr || loggedUser == nullptr || openedPost == nullptr) {
		std::cout << "Cannot post quit" << std::endl;
		return;
	}
	std::cout << "You just left " << openedPost->heading << std::endl;
	openedPost = nullptr;
}

void SocialNetwork::quit() {
	if (openedTopic == nullptr || loggedUser == nullptr) {
		std::cout << "Cannot quit,no opened topic" << std::endl;
		return;
	}
	std::cout << "You just left topic " << openedTopic->heading << std::endl;
	openedTopic = nullptr;
	openedPost = nullptr;
}

void SocialNetwork::whoami() {
	if (loggedUser == nullptr) {
		std::cout << "No logged user" << std::endl;
		return;
	}
	std::cout << *(loggedUser);
}

void SocialNetwork::about(unsigned id) {

	if (findTopic(id) == -1 || loggedUser == nullptr) {
		std::cout << "Cannot access or non-existent" << std::endl;
		return;
	}
	std::cout << topics[findTopic(id)];
}
