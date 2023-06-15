#include "SocialNetwork.h"
#include "Queue.hpp"


namespace {
	int binarySearchInVectorIntegers(const Vector<int>& arr, int el)
	{
		int left = 0, right = arr.getSize() - 1;

		while (left <= right)
		{
			unsigned mid = left + (right - left) / 2;
			if (arr[mid] == el)
				return mid;
			else if (arr[mid] > el)
				right = mid - 1;
			else //arr[mid] < el
				left = mid + 1;
		}
		return -1;
	}

}
bool SocialNetwork::searchComment(unsigned id, Comment& toSearch, void (SocialNetwork::*pred)(Comment&)) {
		//MyQueue<Comment*> queue;
		//queue.push(&toSearch);

		//while (!queue.isEmpty()) {
		//	Comment* current = queue.peek();
		//	queue.pop();

		//	if (current->id == id) {
		//		(this->*pred)(*current);
		//		return true;
		//	}

		//	for (size_t i = 0; i < current->replies.getSize(); ++i) {
		//		queue.push(&(current->replies[i]));
		//	}
		//}

		//return false;
	for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	{
		if (toSearch.replies[i].id == id) {
			(this->*pred)(toSearch.replies[i]);
			return true;
		}
		else if (toSearch.replies[i].replies.getSize() > 0) {
			if (searchComment(id, toSearch.replies[i],pred))
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

void SocialNetwork::upvoteLogic(Comment& comment)
{
	int searchUpvoted = binarySearchInVectorIntegers(comment.indexesOfUpvoters, loggedUser->id);
	int searchDownvoted = binarySearchInVectorIntegers(comment.indexesOfDownvoters, loggedUser->id);
	if (searchUpvoted == -1 && searchDownvoted == -1) {
		comment.IncreaseUpVote();
		comment.indexesOfUpvoters.pushBack(loggedUser->id);
	}
	else if (searchUpvoted != -1) {
		comment.DecreaseUpVote();
		comment.indexesOfUpvoters.popAt(searchUpvoted);
	}
	else if (searchDownvoted != -1) {
		comment.IncreaseUpVote();
		comment.DecreaseDownVote();
		comment.indexesOfUpvoters.pushBack(loggedUser->id);
		comment.indexesOfDownvoters.popAt(searchDownvoted);
	}
}

void SocialNetwork::downvoteLogic(Comment& comment)
{
	int searchUpvoted = binarySearchInVectorIntegers(comment.indexesOfUpvoters, loggedUser->id);
	int searchDownvoted = binarySearchInVectorIntegers(comment.indexesOfDownvoters, loggedUser->id);

	if (searchUpvoted == -1 && searchDownvoted == -1) {
		comment.IncreaseDownVote();
		comment.indexesOfDownvoters.pushBack(loggedUser->id);
	}
	else if (searchDownvoted != -1) {
		comment.DecreaseDownVote();
		comment.indexesOfDownvoters.popAt(searchDownvoted);
	}
	else if (searchUpvoted != -1) {
		comment.DecreaseUpVote();
		comment.IncreaseDownVote();
		comment.indexesOfDownvoters.pushBack(loggedUser->id);
		comment.indexesOfUpvoters.popAt(searchUpvoted);
	}
}


void SocialNetwork::printReplies(const Comment& comment,const MyString& offset) const {
	for (size_t i = 0; i < comment.replies.getSize(); i++)
	{
		std::cout << offset << comment.replies[i];
		if (comment.replies[i].replies.getSize() > 0) {
			printReplies(comment.replies[i], offset+OFFSET);
		}
	}
}


void SocialNetwork::saveReply(Comment& comment) {
	std::cout << "Say somehting: ";
	Comment answer;
	std::cin >> answer;
	answer.creator = loggedUser;
	answer.id = openedPost->commentsCounter++;
	comment.replies.pushBack(std::move(answer));
	std::cout << "Posted" << std::endl;
	loggedUser->points++;
}

bool SocialNetwork::checkAcces(const MyString& command) const{
	if (command == SIGNUP) {
		if (loggedUser != nullptr) {
			std::cout << ERROR_LOGGED_IN << std::endl;
			return false;
		}
	}
	else if (command == LOGIN) {
		if (loggedUser != nullptr) {
		std::cout << ERROR_LOGGED_IN << std::endl;
		return false;
		}
	}
	else if (command == LOGOUT) {
		if (loggedUser == nullptr) {
		std::cout << ERROR_NOT_LOGGED_IN << std::endl;
		return false;
		}
	}
	else if (command == SEARCH) {
		if (loggedUser == nullptr) {
		std::cout << ERROR_NOT_LOGGED_IN << std::endl;
		return false;
		}
	}
	else if (command == CREATE) {
		if (loggedUser == nullptr) {
			std::cout << ERROR_NOT_LOGGED_IN << std::endl;
			return false;
		}
	}
	else if (command == OPEN) {
		if (loggedUser == nullptr || openedTopic != nullptr) {
		std::cout << ERROR_ACCESS_TOPIC << std::endl;
		return false;
		}
	}
	else if (command == POST) {
		if (openedTopic == nullptr || loggedUser == nullptr) {
		std::cout << ERROR_NO_POSTING << std::endl;
		return false;
		}
	}
	else if (command == P_OPEN) {
		if (loggedUser == nullptr || openedTopic == nullptr || openedPost != nullptr ) {
		std::cout << ERROR_ACCESS_POST << std::endl;
		return false;
		}
	}
	else if (command == COMMENT) {
		if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << ERROR_NO_COMMENTING << std::endl;
		return false;
		}
	}
	else if (command == COMMENTS) {
		if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << ERROR_ACCESS_COMMENTS << std::endl;
		return false;
		}
	}
	else if (command == REPLY) {
		if (loggedUser == nullptr || openedTopic == nullptr || openedPost != nullptr) {
			std::cout << ERROR_NO_REPLYING << std::endl;
			return false;
		}
	}
	else if (command == UPVOTE) {
		if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << ERROR_NO_UPVOTING << std::endl;
		return false;
		}
	}
	else if (command == DOWNVOTE) {
		if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << ERROR_NO_DOWNVOTING << std::endl;
		return false;
		}
	}
	else if (command == LIST) {
		if (loggedUser == nullptr || openedTopic == nullptr) {
			std::cout << ERROR_ACCESS_POSTS << std::endl;
			return false;
		}
	}
	else if (command == P_QUIT) {
		if (openedTopic == nullptr || loggedUser == nullptr || openedPost == nullptr) {
			std::cout << ERROR_NO_POSTQUITING << std::endl;
			return false;
		}
	}
	else if (command == QUIT) {
		if (openedTopic == nullptr || loggedUser == nullptr) {
		std::cout << ERROR_NO_QUITING << std::endl;
		return false;
		}
	}
	else if (command == WHOAMI) {
		if (loggedUser == nullptr){
			std::cout << ERROR_NOT_LOGGED_IN << std::endl;
			return false;
		}
	}
	else if (command == ABOUT) {
		if (openedTopic == nullptr || loggedUser==nullptr) {
			std::cout << ERROR_NO_OPENEDTOPIC << std::endl;
			return false;
		}
	}
	return true;
}