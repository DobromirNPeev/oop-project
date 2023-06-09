#include "SocialNetwork.h"

bool SocialNetwork::searchCommentAndUpvote(unsigned id, Comment& toSearch) {
	//обхожда листата
	for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	{
		int searchUpvoted = toSearch.replies[i].didUserUpvoted(loggedUser->id);
		int searchDownvoted = toSearch.replies[i].didUserDownvoted(loggedUser->id);
		if (toSearch.replies[i].id == id && searchUpvoted == -1 && searchDownvoted == -1) {
			toSearch.replies[i].IncreaseUpVote();
			toSearch.replies[i].indexesOfUpvoters.pushBack(loggedUser->id);
			return true;
		}
		else if (toSearch.replies[i].id == id && searchUpvoted != -1) {
			toSearch.replies[i].DecreaseUpVote();
			toSearch.replies[i].indexesOfUpvoters.popAt(searchUpvoted);
			return true;
		}
		else if (toSearch.replies[i].id == id && searchDownvoted != -1) {
			toSearch.replies[i].IncreaseUpVote();
			toSearch.replies[i].DecreaseDownVote();
			toSearch.replies[i].indexesOfUpvoters.pushBack(loggedUser->id);
			toSearch.replies[i].indexesOfDownvoters.popAt(searchDownvoted);
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
		int searchUpvoted = toSearch.replies[i].didUserUpvoted(loggedUser->id);
		int searchDownvoted = toSearch.replies[i].didUserDownvoted(loggedUser->id);

		if (toSearch.replies[i].id == id && searchUpvoted == -1 && searchDownvoted == -1) {
			toSearch.replies[i].IncreaseDownVote();
			toSearch.replies[i].indexesOfDownvoters.pushBack(loggedUser->id);
			return true;
		}
		else if (toSearch.replies[i].id == id && searchDownvoted != -1) {
			toSearch.replies[i].DecreaseDownVote();
			toSearch.replies[i].indexesOfDownvoters.popAt(searchDownvoted);
			return true;
		}
		else if (toSearch.replies[i].id == id && searchUpvoted != -1) {
			toSearch.replies[i].DecreaseUpVote();
			toSearch.replies[i].IncreaseDownVote();
			toSearch.replies[i].indexesOfDownvoters.pushBack(loggedUser->id);
			toSearch.replies[i].indexesOfUpvoters.popAt(searchUpvoted);
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

SocialNetwork::~SocialNetwork() {
	std::ofstream ofs("Data.dat", std::ios::out | std::ios::binary);
	ofs.write((const char*)&idCount, sizeof(idCount));
	int userSize = users.getSize();
	ofs.write((const char*)&userSize, sizeof(userSize));
	for (size_t i = 0; i < userSize; i++)
	{
		writeUserToFile(ofs, users[i]);
	}
	int topicSize = topics.getSize();
	ofs.write((const char*)&topicSize, sizeof(topicSize));
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		writeTopicToFile(ofs, topics[i]);
	}
}

SocialNetwork::SocialNetwork() {
	std::ifstream ifs("Data.dat", std::ios::in | std::ios::binary);
	ifs.read((char*)&idCount, sizeof(idCount));
	int usersSize = 0;
	ifs.read((char*)&usersSize, sizeof(usersSize));
	for (size_t i = 0; i < usersSize; i++)
	{
		users.pushBack(std::move(readUserFromBinaryFile(ifs)));
	}
	int topicsSize = 0;
	ifs.read((char*)&topicsSize, sizeof(topicsSize));
	for (size_t i = 0; i < topicsSize; i++)
	{
		topics.pushBack(std::move(readTopicFromBinaryFile(ifs)));
	}
};

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
			std::cout << "Say somehting: ";
			Comment answer;
			std::cin >> answer;
			answer.creator = loggedUser;
			answer.id = openedPost->commentsCounter++;
			toSearch.replies[i].replies.pushBack(answer);
			std::cout << "Posted" << std::endl;
			loggedUser->points++;
			return true;
		}
		if (toSearch.replies[i].replies.getSize() > 0) {
			searchComment(id, toSearch.replies[i]);
		}
	}
	return false;
}

