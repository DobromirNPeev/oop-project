#include "Comment.h"

Comment::Comment(const User& creator, const MyString& description) :creator(&creator), description(description), upvoteCounter(0), downvoteCounter(0) {};

unsigned Comment::getID() const
{
	return id;
}

void Comment::setID(unsigned id)
{
	this->id = id;
}

void Comment::setCreator(const User& user)
{
	if (creator == nullptr)
		creator = &user;
}

int Comment::didUserUpvoted(unsigned id) const
{
	for (size_t i = 0; i < IDsofUpvoters.getSize(); i++)
	{
		if (id == IDsofUpvoters[i]) {
			return i;
		}
	}
	return -1;
}

int Comment::didUserDownvoted(unsigned id) const
{
	for (size_t i = 0; i < IDsofDownvoters.getSize(); i++)
	{
		if (id == IDsofDownvoters[i]) {
			return i;
		}
	}
	return -1;
}

const Vector<Comment>& Comment::getReplies() const
{
	return replies;
}

Vector<Comment>& Comment::getReplies()
{
	return replies;
}

const Vector<int>& Comment::getIDsofUpvoters() const
{
	return IDsofUpvoters;
}

Vector<int>& Comment::getIDsofUpvoters()
{
	return IDsofUpvoters;
}

const Vector<int>& Comment::getIDsofDownvoters() const
{
	return IDsofDownvoters;
}

Vector<int>& Comment::getIDsofDownvoters()
{
	return IDsofDownvoters;
}

void Comment::IncreaseUpVote()
{
	upvoteCounter++;
};
void Comment::DecreaseUpVote()
{
	if (upvoteCounter <= 0) {
		upvoteCounter = 0;
	}
	else {
		upvoteCounter--;
	}
};
void Comment::IncreaseDownVote() {
	downvoteCounter++;
}
void Comment::DecreaseDownVote() {
	if (downvoteCounter <= 0) {
		downvoteCounter = 0;
	}
	else {
		downvoteCounter--;
	}

}
std::istream& operator>>(std::istream& is, Comment& comment) {
	is >> comment.description;
	return is;
}
std::ostream& operator<<(std::ostream& os, const Comment& comment) {
	std::cout << ">>" << comment.description << ID_PRINTING << comment.id << "}";
	if (comment.downvoteCounter != 0 && comment.upvoteCounter != 0)
	{
		std::cout<< UPVOTE_PRINT << comment.upvoteCounter << "}" << DOWNVOTE_PRINT << comment.downvoteCounter << "}" <<  std::endl;
	}
	else if (comment.upvoteCounter != 0) {
		std::cout << UPVOTE_PRINT << comment.upvoteCounter << "}" << std::endl;
	}
	else if (comment.downvoteCounter != 0) {
		std::cout << DOWNVOTE_PRINT << comment.downvoteCounter << "}" << std::endl;
	}
	else {
		std::cout << std::endl;
	}
	return os;
}