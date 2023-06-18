#include "SocialNetwork.h"
#include "AdditionalCommands.h"

AdditionalCommands::AdditionalCommands(SocialNetwork& sn) :sn(&sn) {};

bool AdditionalCommands::searchComment(unsigned id, Comment& toSearch, void (AdditionalCommands::*pred)(Comment&)) {
	for (size_t i = 0; i < toSearch.getReplies().getSize(); i++)
	{
		if (toSearch.getReplies()[i].getID() == id) {
			(this->*pred)(toSearch.getReplies()[i]);
			return true;
		}
		else if (toSearch.getReplies()[i].getReplies().getSize() > 0) {
			if(searchComment(id, toSearch.getReplies()[i], pred))
				return true;
		}
	}
	return false;
}

bool AdditionalCommands::containsUser(const User& other) const {
	for (size_t i = 0; i < sn->users.getSize(); i++)
	{
		if (sn->users[i]==other) {
			return true;
		}
	}
	return false;
}
int AdditionalCommands::containsUser(const MyString& firstName, const MyString& password) const {

	for (size_t i = 0; i < sn->users.getSize(); i++)
	{
		if (sn->users[i].getFirstName()== firstName.c_str() && sn->users[i].comparePassword(password)) {
			return i;
		}
	}
	return -1;
}

void AdditionalCommands::upvoteLogic(Comment& comment)
{
	int searchUpvoted =comment.didUserUpvoted(sn->loggedUser->getID());
	int searchDownvoted = comment.didUserDownvoted(sn->loggedUser->getID());
	if (searchUpvoted == -1 && searchDownvoted == -1) {
		comment.IncreaseUpVote();
		comment.getIDsofUpvoters().pushBack(sn->loggedUser->getID());
	}
	else if (searchUpvoted != -1) {
		comment.DecreaseUpVote();
		comment.getIDsofUpvoters().popAt(searchUpvoted);
	}
	else if (searchDownvoted != -1) {
		comment.IncreaseUpVote();
		comment.DecreaseDownVote();
		comment.getIDsofUpvoters().pushBack(sn->loggedUser->getID());
		comment.getIDsofDownvoters().popAt(searchDownvoted);
	}
}

void AdditionalCommands::downvoteLogic(Comment& comment)
{
	int searchUpvoted = comment.didUserUpvoted(sn->loggedUser->getID());
	int searchDownvoted = comment.didUserDownvoted(sn->loggedUser->getID());

	if (searchUpvoted == -1 && searchDownvoted == -1) {
		comment.IncreaseDownVote();
		comment.getIDsofDownvoters().pushBack(sn->loggedUser->getID());
	}
	else if (searchDownvoted != -1) {
		comment.DecreaseDownVote();
		comment.getIDsofDownvoters().popAt(searchDownvoted);
	}
	else if (searchUpvoted != -1) {
		comment.DecreaseUpVote();
		comment.IncreaseDownVote();
		comment.getIDsofDownvoters().pushBack(sn->loggedUser->getID());
		comment.getIDsofUpvoters().popAt(searchUpvoted);
	}
}


void AdditionalCommands::printReplies(const Comment& comment,const MyString& offset) const {
	for (size_t i = 0; i < comment.getReplies().getSize(); i++)
	{
		std::cout << offset << comment.getReplies()[i];
		if (comment.getReplies()[i].getReplies().getSize() > 0) {
			printReplies(comment.getReplies()[i], offset+OFFSET);
		}
	}
}


void AdditionalCommands::saveReply(Comment& comment) {
	std::cout << SAY_SOMETHING;
	Comment answer;
	std::cin >> answer;
	answer.setCreator(*sn->loggedUser);
	answer.setID (sn->openedPost->getCommentsCounter());
	comment.getReplies().pushBack(std::move(answer));
	sn->openedPost->increaseCommentsCounter();
	std::cout << POSTING << std::endl;
	sn->loggedUser->IncreasePoints();
}

bool AdditionalCommands::checkAcces(const MyString& command) const{
	if (sn->loggedUser == nullptr) {
		if (command == SIGNUP || command == LOGIN) {
				return true;
		}
	}
	else {
		if (command==SEARCH || command==CREATE || command == WHOAMI) {
				return true;
			
		}
		else if (sn->openedTopic == nullptr) {
			if (command == OPEN || command == ABOUT || command == LOGOUT) {
				return true;
			}
		}
		else {
			if (command == POST || command == LIST  || command == ABOUT) {
				return true;
			}
			else if (sn->openedPost == nullptr) {
				if (command == P_OPEN || command == QUIT) {
					return true;
				}
			}
			else {
				if (command == COMMENT || command == COMMENTS || command == REPLY || command == UPVOTE || command == DOWNVOTE || command == P_QUIT) {
					return true;
				}
			}
		}
	}
	std::cout << ERROR << std::endl;
	std::cout << std::endl;
	return false;
}