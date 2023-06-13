#include "SocialNetwork.h"

namespace {
	MyString readStringFromFile(std::ifstream& file) {
		int stringLength;
		file.read((char*)&stringLength, sizeof(int));
		char* str = new char[stringLength + 1];
		file.read(str, stringLength);
		str[stringLength] = '\0';

		return str;
	}

	void writeStringToFile(std::ofstream& file, const char* str) {
		int stringLength = strlen(str);
		file.write((const char*)&stringLength, sizeof(int));
		file.write(str, stringLength);
	}

	Vector<int> readIntegersFromFile(std::ifstream& ifs) {
		Vector<int> curr;
		size_t size = 0;
		ifs.read((char*)&size, sizeof(size));
		for (size_t i = 0; i < size; i++)
		{
			int number = 0;
			ifs.read((char*)&number, sizeof(number));
			curr.pushBack(number);
		}
		return curr;
	}

	void writeIntegersToFile(std::ofstream& ofs,size_t size,const Vector<int>& integers) {
		ofs.write((const char*)&size, sizeof(size_t));
		for (size_t i = 0; i < size; i++)
		{
			ofs.write((const char*)&integers[i], sizeof(int));
		}
	}

}


Comment SocialNetwork::readCommentFromBinaryFile(std::ifstream& ifs) {
	Comment comment;
	size_t indexOfCreator;
	ifs.read((char*)&indexOfCreator, sizeof(indexOfCreator));
	comment.creator = &users[indexOfCreator];
	comment.indexOfCreator = indexOfCreator;
	comment.description = std::move(readStringFromFile(ifs));
	unsigned upVoteCounter;
	ifs.read((char*)&upVoteCounter, sizeof(unsigned));
	comment.upvoteCounter = upVoteCounter;
	unsigned downVoteCounter;
	ifs.read((char*)&downVoteCounter, sizeof(unsigned));
	comment.downvoteCounter = downVoteCounter;
	unsigned commentId;
	ifs.read((char*)&commentId, sizeof(unsigned));
	comment.id = commentId;
	comment.indexesOfUpvoters = std::move(readIntegersFromFile(ifs));
	comment.indexesOfDownvoters = std::move(readIntegersFromFile(ifs));
	int repliesCount;
	ifs.read((char*)&repliesCount, sizeof(int));
	for (size_t i = 0; i < repliesCount; i++)
	{
		comment.replies.pushBack(std::move(readCommentFromBinaryFile(ifs)));
	}
	return comment;
}
Post SocialNetwork::readPostFromBinaryFile(std::ifstream& ifs)
{
	Post post;
	post.heading = std::move(readStringFromFile(ifs));
	post.description = std::move(readStringFromFile(ifs));
	unsigned commentsCounter;
	ifs.read((char*)&commentsCounter, sizeof(unsigned));
	post.commentsCounter = commentsCounter;
	unsigned postId;
	ifs.read((char*)&postId, sizeof(unsigned));
	post.id = postId;
	int commentsCount;
	ifs.read((char*)&commentsCount, sizeof(int));
	for (size_t i = 0; i < commentsCount; i++)
	{
		post.comments.pushBack(std::move(readCommentFromBinaryFile(ifs)));
	}
	return post;
}
Topic SocialNetwork::readTopicFromBinaryFile(std::ifstream& ifs)
{
	Topic topic;
	topic.heading = std::move(readStringFromFile(ifs));
	size_t indexOfCreator;
	ifs.read((char*)&indexOfCreator, sizeof(indexOfCreator));
	topic.creator = &users[indexOfCreator];
	topic.indexOfCreator = indexOfCreator;
	topic.description =std::move(readStringFromFile(ifs));
	unsigned topicId;
	ifs.read((char*)&topicId, sizeof(unsigned));
	topic.id = topicId;
	unsigned postsCounter;
	ifs.read((char*)&postsCounter, sizeof(unsigned));
	topic.postsCounter = postsCounter;
	int postsCount;
	ifs.read((char*)&postsCount, sizeof(postsCount));
	for (size_t i = 0; i < postsCount; i++)
	{
		topic.posts.pushBack(std::move(readPostFromBinaryFile(ifs)));
	}
	return topic;
}

User SocialNetwork::readUserFromBinaryFile(std::ifstream& ifs)
{
	User user;
	user.firstName = std::move(readStringFromFile(ifs));
	user.lastName =std::move(readStringFromFile(ifs));
	user.password =std::move(readStringFromFile(ifs));
	unsigned id;
	ifs.read((char*)&id, sizeof(unsigned));
	user.id = id;
	unsigned points;
	ifs.read((char*)&points, sizeof(unsigned));
	user.points = points;
	return user;
}



void SocialNetwork::writeCommentToFile(std::ofstream& ofs, const Comment& comment) {
	ofs.write((const char*)&comment.indexOfCreator, sizeof(comment.indexOfCreator));
	writeStringToFile(ofs, comment.description.c_str());
	ofs.write((const char*)&comment.upvoteCounter, sizeof(comment.upvoteCounter));
	ofs.write((const char*)&comment.downvoteCounter, sizeof(comment.downvoteCounter));
	ofs.write((const char*)&comment.id, sizeof(comment.id));
	writeIntegersToFile(ofs, comment.indexesOfUpvoters.getSize(), comment.indexesOfUpvoters);
	writeIntegersToFile(ofs, comment.indexesOfDownvoters.getSize(), comment.indexesOfDownvoters);
	int repliesSize = comment.replies.getSize();
	ofs.write((const char*)&repliesSize, sizeof(repliesSize));
	for (size_t i = 0; i < comment.replies.getSize(); i++)
	{
		writeCommentToFile(ofs, comment.replies[i]);
	}
}
void SocialNetwork::writePostToFile(std::ofstream& ofs, const Post& post) {
	writeStringToFile(ofs, post.heading.c_str());
	writeStringToFile(ofs, post.description.c_str());
	ofs.write((const char*)&post.commentsCounter, sizeof(post.commentsCounter));
	ofs.write((const char*)&post.id, sizeof(post.id));
	int commentsSize = post.comments.getSize();
	ofs.write((const char*)&commentsSize, sizeof(commentsSize));
	for (size_t i = 0; i < post.comments.getSize(); i++)
	{
		writeCommentToFile(ofs, post.comments[i]);
	}
}
void SocialNetwork::writeTopicToFile(std::ofstream& ofs, const Topic& topic) {
	writeStringToFile(ofs, topic.heading.c_str());
	ofs.write((const char*)&topic.indexOfCreator, sizeof(topic.indexOfCreator));
	writeStringToFile(ofs, topic.description.c_str());
	ofs.write((const char*)&topic.id, sizeof(topic.id));
	ofs.write((const char*)&topic.postsCounter, sizeof(topic.postsCounter));
	int postsSize = topic.posts.getSize();
	ofs.write((const char*)&postsSize, sizeof(postsSize));
	for (size_t i = 0; i < topic.posts.getSize(); i++)
	{
		writePostToFile(ofs, topic.posts[i]);
	}
}
void SocialNetwork::writeUserToFile(std::ofstream& ofs, const User& user) {
	writeStringToFile(ofs, user.firstName.c_str());
	writeStringToFile(ofs, user.lastName.c_str());
	writeStringToFile(ofs, user.password.c_str());
	ofs.write((const char*)&user.id, sizeof(user.id));
	ofs.write((const char*)&user.points, sizeof(user.points));
}
