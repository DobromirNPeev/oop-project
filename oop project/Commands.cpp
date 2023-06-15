﻿#include "SocialNetwork.h"
#include "binarysearch.hpp"

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
	if (!containsUser(current)) {
		std::cout << "User already exists" << std::endl;
		return;
	}
	current.id = SocialNetwork::idCount++;
	users.pushBack(std::move(current));
}

void SocialNetwork::login() {
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
	std::cout << "Goodbye," << loggedUser->firstName << " " << loggedUser->lastName << std::endl;
	loggedUser = nullptr;
	openedTopic = nullptr;
	openedPost = nullptr;
}

void SocialNetwork::search(const MyString& topicName) const
{
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (searchInText(topics[i].getHeading().c_str(), topicName.c_str())) {
			std::cout << "-  " << topics[i].getHeading() << "{id:" << topics[i].id << "}" << std::endl;
			return;
		}
	}
	std::cout << "No such topic" << std::endl;
}

void SocialNetwork::create() {
	Topic newTopic;
	std::cin >> newTopic;
	newTopic.setID(idCount++);
	newTopic.setCreator(*loggedUser);
	newTopic.indexOfCreator = binarySearchViaID(users,loggedUser->id);
	topics.pushBack(std::move(newTopic));

}

void SocialNetwork::open(const MyString& topicName) {
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (searchInText(topics[i].getHeading().c_str(), topicName.c_str())) {
			std::cout << "Welcome to " << topics[i].heading << std::endl;
			openedTopic = &topics[i];
			return;
		}
	}
	std::cout << "No such topic" << std::endl;
}

void SocialNetwork::open(unsigned id) {
	int i = binarySearchViaID(topics, id);
	if (i == -1) {
		std::cout << "No such topic" << std::endl;
	}
	else {
		std::cout << "Welcome to " << topics[i].heading << std::endl;
		openedTopic = &topics[i];
	}
}

void SocialNetwork::post() {
	Post newPost;
	std::cin >> newPost;
	newPost.id = openedTopic->postsCounter++;
	openedTopic->posts.pushBack(std::move(newPost));
}
void SocialNetwork::p_open(const MyString& postName) {
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
	int i = binarySearchViaID(openedTopic->posts, id);
	if (i == -1) {
		std::cout << "No such post" << std::endl;
	}
	else {
		openedPost = &(openedTopic->posts[i]);
		std::cout << "Q: " << openedTopic->posts[i];
	}
}

void SocialNetwork::comment() {
	Comment comment;
	std::cout << "Say something: ";
	std::cin >> comment;
	loggedUser->points++;
	comment.id = openedPost->commentsCounter++;
	openedPost->comments.pushBack(std::move(comment));
}

void SocialNetwork::comments() const {
	MyString offset(OFFSET);
	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		std::cout << openedPost->comments[i];
		printReplies(openedPost->comments[i], offset);
	}
}

void SocialNetwork::reply(unsigned id) {
	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		//Обхожда корените
		if (openedPost->comments[i].id == id) {
			saveReply(openedPost->comments[i]);
			return;
		}
		else if (openedPost->comments[i].replies.getSize() > 0){
			if (searchComment(id, openedPost->comments[i],&SocialNetwork::saveReply))
				return;
		}
	}
	std::cout << "Non-existent comment" << std::endl;
}

void SocialNetwork::upvote(unsigned id) {
	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		//Обхожда корените
		if (openedPost->comments[i].id == id) {
			upvoteLogic(openedPost->comments[i]);
			return;
		}
		else if (openedPost->comments[i].replies.getSize() > 0) {
			if (searchComment(id, openedPost->comments[i], &SocialNetwork::upvoteLogic))
				return;
		}
	}
	std::cout << "Non-existent comment" << std::endl;

}

void SocialNetwork::downvote(unsigned id) {
	//Обхожда корените
	for (size_t i = 0; i < openedPost->getComments().getSize(); i++)
	{
		if (openedPost->comments[i].id == id) {
			downvoteLogic(openedPost->comments[i]);
			return;
		}
		else if (openedPost->comments[i].replies.getSize() > 0) {
			if (searchComment(id, openedPost->comments[i], &SocialNetwork::downvoteLogic))
				return;
		}
	}
	std::cout << "Non-existent comment"<<std::endl;
}

void SocialNetwork::list() const{
	unsigned numberOfPosts = openedTopic->getPosts().getSize();
	for (size_t i = 0; i < numberOfPosts; i++)
	{
		std::cout << openedTopic->posts[i];
	}
}

void SocialNetwork::p_quit() {
	std::cout << "You just left post" << openedPost->heading << std::endl;
	openedPost = nullptr;
}

void SocialNetwork::quit() {
	std::cout << "You just left topic " << openedTopic->heading << std::endl;
	openedTopic = nullptr;
	openedPost = nullptr;
}

void SocialNetwork::whoami() const{
	std::cout << *(loggedUser);
}

void SocialNetwork::about(unsigned id) const{
	int topicId = binarySearchViaID(topics,id);
	if (topicId == -1) {
		std::cout << "No such topic" << std::endl;
		return;
	}
	std::cout << topics[topicId];
}
