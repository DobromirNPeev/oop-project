#include "SocialNetwork.h"

bool SocialNetwork::searchCommentAndUpvote(unsigned id, Comment& toSearch) {
	//обхожда листата
	for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	{
		if (upvoteLogic(id, toSearch.replies[i])) {
			return true;
		}
		else if (toSearch.replies[i].replies.getSize() > 0) {
			if (searchCommentAndUpvote(id, toSearch.replies[i]))
				return true;
		}
	}
	return false;

}
bool SocialNetwork::searchCommentAndDownvote(unsigned id, Comment& toSearch) {
	//Обхожда листата
	for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	{
		if (downvoteLogic(id, toSearch.replies[i])) {
			return true;
		}
		else if (toSearch.replies[i].replies.getSize() > 0) {
			if (searchCommentAndDownvote(id, toSearch.replies[i]))
				return true;
		}
	}
	return false;
}

bool SocialNetwork::containsUser(const User& other) const {
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i].firstName == other.firstName && users[i].lastName == other.lastName) {
			return false;
		}
	}
	return true;
}
int SocialNetwork::containsUser(const MyString& firstName, const MyString& password) const {

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (!strcmp(users[i].firstName.c_str(), firstName.c_str()) && !strcmp(users[i].password.c_str(), password.c_str())) {
			return i;
		}
	}
	return -1;
}

bool SocialNetwork::upvoteLogic(unsigned id,Comment& comment)
{
	int searchUpvoted = comment.didUserUpvoted(loggedUser->id);
	int searchDownvoted = comment.didUserDownvoted(loggedUser->id);
	if (comment.id == id && searchUpvoted == -1 && searchDownvoted == -1) {
		comment.IncreaseUpVote();
		comment.indexesOfUpvoters.pushBack(loggedUser->id);
		return true;
	}
	else if (comment.id == id && searchUpvoted != -1) {
		comment.DecreaseUpVote();
		comment.indexesOfUpvoters.popAt(searchUpvoted);
		return true;
	}
	else if (comment.id == id && searchDownvoted != -1) {
		comment.IncreaseUpVote();
		comment.DecreaseDownVote();
		comment.indexesOfUpvoters.pushBack(loggedUser->id);
		comment.indexesOfDownvoters.popAt(searchDownvoted);
		return true;
	}

	return false;
}

bool SocialNetwork::downvoteLogic(unsigned id, Comment& comment)
{
	int searchUpvoted = comment.didUserUpvoted(loggedUser->id);
	int searchDownvoted = comment.didUserDownvoted(loggedUser->id);

	if (comment.id == id && searchUpvoted == -1 && searchDownvoted == -1) {
		comment.IncreaseDownVote();
		comment.indexesOfDownvoters.pushBack(loggedUser->id);
		return true;
	}
	else if (comment.id == id && searchDownvoted != -1) {
		comment.DecreaseDownVote();
		comment.indexesOfDownvoters.popAt(searchUpvoted);
		return true;
	}
	else if (comment.id == id && searchUpvoted != -1) {
		comment.DecreaseUpVote();
		comment.IncreaseDownVote();
		comment.indexesOfDownvoters.pushBack(loggedUser->id);
		comment.indexesOfUpvoters.popAt(searchUpvoted);
		return true;
	}
	return false;
}



int SocialNetwork::findUser() {
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (&users[i] == loggedUser) {
			return i;
		}
	}
	return -1;
}
int SocialNetwork::findTopic(unsigned n) {
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (topics[i].id == n) {
			return i;
		}
	}
	return -1;
}

void SocialNetwork::printReplies(const Comment& comment, MyString& offset) {
	for (size_t i = 0; i < comment.replies.getSize(); i++)
	{
		std::cout << offset << comment.replies[i];
		if (comment.replies[i].replies.getSize() > 0) {
			offset += OFFSET;
			printReplies(comment.replies[i], offset);
		}
		offset = OFFSET;
	}
}


bool SocialNetwork::searchComment(unsigned id, Comment& toSearch) {
	for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	{
		if (toSearch.replies[i].id == id) {
			saveReply(id, toSearch.replies[i]);
			return true;
		}
		if (toSearch.replies[i].replies.getSize() > 0) {
			searchComment(id, toSearch.replies[i]);
		}
	}
	return false;
}


void SocialNetwork::saveReply(unsigned id, Comment& comment) {
	std::cout << "Say somehting: ";
	Comment answer;
	std::cin >> answer;
	answer.creator = loggedUser;
	answer.id = openedPost->commentsCounter++;
	comment.replies.pushBack(std::move(answer));
	std::cout << "Posted" << std::endl;
	loggedUser->points++;
}
