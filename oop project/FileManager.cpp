#include "FileManager.h"
#include "SocialNetwork.h"

FileManager::FileManager(SocialNetwork& sn) :sn(&sn) {};

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

void FileManager::readSocialNetworkFromBinaryFile() {
	std::ifstream ifs("Data.dat", std::ios::in | std::ios::binary);
	if (!ifs.is_open()) {
		throw std::logic_error(FILE_READ_ERROR);
	}
	ifs.read((char*)&sn->idCount, sizeof(sn->idCount));
	int usersSize = 0;
	ifs.read((char*)&usersSize, sizeof(usersSize));
	for (size_t i = 0; i < usersSize; i++)
	{
		sn->users.pushBack(std::move(readUserFromBinaryFile(ifs)));
	}
	int topicsSize = 0;
	ifs.read((char*)&topicsSize, sizeof(topicsSize));
	for (size_t i = 0; i < topicsSize; i++)
	{
		sn->topics.pushBack(std::move(readTopicFromBinaryFile(ifs)));
	}
	ifs.close();
}

void FileManager::writeSocialNetworkToFile() {
	std::ofstream ofs("Data.dat", std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		throw std::logic_error(FILE_WRITE_ERROR);
	}
	ofs.write((const char*)&sn->idCount, sizeof(sn->idCount));
	int userSize = sn->users.getSize();
	ofs.write((const char*)&userSize, sizeof(userSize));
	for (size_t i = 0; i < userSize; i++)
	{
		writeUserToFile(ofs, sn->users[i]);
	}
	int topicSize = sn->topics.getSize();
	ofs.write((const char*)&topicSize, sizeof(topicSize));
	for (size_t i = 0; i < sn->topics.getSize(); i++)
	{
		writeTopicToFile(ofs, sn->topics[i]);
	}
	ofs.close();
}

Comment FileManager::readCommentFromBinaryFile(std::ifstream& ifs) {
	Comment comment;
	size_t indexOfCreator;
	ifs.read((char*)&indexOfCreator, sizeof(indexOfCreator));
	comment.creator = &(sn->users[indexOfCreator]);
	comment.indexOfCreator = indexOfCreator;
	comment.description = std::move(readStringFromFile(ifs));
	ifs.read((char*)&comment.upvoteCounter, sizeof(unsigned));
	ifs.read((char*)&comment.downvoteCounter, sizeof(unsigned));
	ifs.read((char*)&comment.id, sizeof(unsigned));
	comment.IDsofUpvoters = std::move(readIntegersFromFile(ifs));
	comment.IDsofDownvoters = std::move(readIntegersFromFile(ifs));
	int repliesCount;
	ifs.read((char*)&repliesCount, sizeof(int));
	for (size_t i = 0; i < repliesCount; i++)
	{
		comment.replies.pushBack(std::move(readCommentFromBinaryFile(ifs)));
	}
	return comment;
}
Post FileManager::readPostFromBinaryFile(std::ifstream& ifs)
{
	Post post;
	post.heading = std::move(readStringFromFile(ifs));
	post.description = std::move(readStringFromFile(ifs));
	ifs.read((char*)&post.commentsCounter, sizeof(unsigned));
	ifs.read((char*)&post.id, sizeof(unsigned));
	int commentsCount;
	ifs.read((char*)&commentsCount, sizeof(int));
	for (size_t i = 0; i < commentsCount; i++)
	{
		post.comments.pushBack(std::move(readCommentFromBinaryFile(ifs)));
	}
	return post;
}
Topic FileManager::readTopicFromBinaryFile(std::ifstream& ifs)
{
	Topic topic;
	topic.heading = std::move(readStringFromFile(ifs));
	ifs.read((char*)&topic.indexOfCreator, sizeof(topic.indexOfCreator));
	topic.creator = &(sn->users[topic.indexOfCreator]);
	topic.description =std::move(readStringFromFile(ifs));
	ifs.read((char*)&topic.id, sizeof(unsigned));
	ifs.read((char*)&topic.postsCounter, sizeof(unsigned));
	int postsCount;
	ifs.read((char*)&postsCount, sizeof(postsCount));
	for (size_t i = 0; i < postsCount; i++)
	{
		topic.posts.pushBack(std::move(readPostFromBinaryFile(ifs)));
	}
	return topic;
}

User FileManager::readUserFromBinaryFile(std::ifstream& ifs)
{
	User user;
	user.firstName = std::move(readStringFromFile(ifs));
	user.lastName =std::move(readStringFromFile(ifs));
	user.password =std::move(readStringFromFile(ifs));
	ifs.read((char*)&user.id, sizeof(unsigned));
	ifs.read((char*)&user.points, sizeof(unsigned));
	return user;
}



void FileManager::writeCommentToFile(std::ofstream& ofs, const Comment& comment) {
	ofs.write((const char*)&comment.indexOfCreator, sizeof(comment.indexOfCreator));
	writeStringToFile(ofs, comment.description.c_str());
	ofs.write((const char*)&comment.upvoteCounter, sizeof(comment.upvoteCounter));
	ofs.write((const char*)&comment.downvoteCounter, sizeof(comment.downvoteCounter));
	ofs.write((const char*)&comment.id, sizeof(comment.id));
	writeIntegersToFile(ofs, comment.IDsofUpvoters.getSize(), comment.IDsofUpvoters);
	writeIntegersToFile(ofs, comment.IDsofDownvoters.getSize(), comment.IDsofDownvoters);
	int repliesSize = comment.replies.getSize();
	ofs.write((const char*)&repliesSize, sizeof(repliesSize));
	for (size_t i = 0; i < comment.replies.getSize(); i++)
	{
		writeCommentToFile(ofs, comment.replies[i]);
	}
}
void FileManager::writePostToFile(std::ofstream& ofs, const Post& post) {
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
void FileManager::writeTopicToFile(std::ofstream& ofs, const Topic& topic) {
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
void FileManager::writeUserToFile(std::ofstream& ofs, const User& user) {
	writeStringToFile(ofs, user.firstName.c_str());
	writeStringToFile(ofs, user.lastName.c_str());
	writeStringToFile(ofs, user.password.c_str());
	ofs.write((const char*)&user.id, sizeof(user.id));
	ofs.write((const char*)&user.points, sizeof(user.points));
}
