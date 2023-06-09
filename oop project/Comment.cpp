#include "Comment.h"

int Comment::didUserUpvoted(unsigned id) const
{
	for (size_t i = 0; i < indexesOfUpvoters.getSize(); i++)
	{
		if (indexesOfUpvoters[i] == id) {
			return i;
		}
	}
	return -1;
}

int Comment::didUserDownvoted(unsigned id) const
{
	for (size_t i = 0; i < indexesOfDownvoters.getSize(); i++)
	{
		if (indexesOfDownvoters[i] == id) {
			return i;
		}
	}
	return -1;
}

Comment::Comment() : creator(), description(""),upvoteCounter(0),downvoteCounter(0) {};
Comment::Comment(const User& creator, const MyString& description) :creator(&creator),description(description), upvoteCounter(0), downvoteCounter(0) {}
Comment::Comment(const User& creator, const MyString& description, Vector<MyString> replies, unsigned upvoteCounter, unsigned downvoteCounter, unsigned idCount, unsigned id)
					: creator(&creator),description(description), upvoteCounter(upvoteCounter), downvoteCounter(downvoteCounter), id(id){};

unsigned Comment::getID() const
{
	return id;
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
	std::cout << ">>" << comment.description << "{id:" << comment.id << "}";
	if (comment.downvoteCounter != 0 && comment.upvoteCounter != 0)
	{
		std::cout<< "{upvote:" << comment.upvoteCounter << "}" << "{downvote:" << comment.downvoteCounter << "}" <<  std::endl;
	}
	else if (comment.upvoteCounter != 0) {
		std::cout << "{upvote:" << comment.upvoteCounter << "}" << std::endl;
	}
	else if (comment.downvoteCounter != 0) {
		std::cout << "{downvote:" << comment.downvoteCounter << "}" << std::endl;
	}
	else {
		std::cout << std::endl;
	}
	return os;
}
//void printReplies(const char* offset,const Comment& comment) {
//	MyString innerOffset(offset);
//	for (size_t i = 0; i < comment.replies.getSize(); i++)
//	{
//		std::cout << offset<< comment.replies[i];
//		if (comment.replies[i].replies.getSize() != 0) {
//			innerOffset += offset;
//			//printReplies(innerOffset.c_str(), comment.replies[i]);
//		}
//	}
//}