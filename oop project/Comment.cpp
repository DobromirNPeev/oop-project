#include "Comment.h"
unsigned Comment::idCount=0;

Comment::Comment() : creator(), description(""),upvoteCounter(0),downvoteCounter(0) {};
Comment::Comment(const User& creator, const MyString& description) :creator(&creator),description(description),id(idCount++), upvoteCounter(0), downvoteCounter(0) {}
Comment::Comment(const User& creator, const MyString& description, Vector<MyString> replies, unsigned upvoteCounter, unsigned downvoteCounter, unsigned idCount, unsigned id)
					: creator(&creator),description(description),replies(replies), upvoteCounter(upvoteCounter), downvoteCounter(downvoteCounter), id(id){};

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
	upvoteCounter--;
	if (upvoteCounter < 0) {
		upvoteCounter = 0;
	}
};
void Comment::IncreaseDownVote() {
	downvoteCounter++;
}
void Comment::DecreaseDownVote() {
	downvoteCounter--;
	if (downvoteCounter < 0) {
		downvoteCounter = 0;
	}
}
