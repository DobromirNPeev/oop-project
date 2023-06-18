#pragma once
#include <fstream>
#include "User.h"
#include "Topic.h"

class SocialNetwork;

class FileManager
{
	SocialNetwork* sn;

	User readUserFromBinaryFile(std::ifstream& ifs);
	Topic readTopicFromBinaryFile(std::ifstream& ifs);
	Post readPostFromBinaryFile(std::ifstream& ifs);
	Comment readCommentFromBinaryFile(std::ifstream& ifs);

	void writeUserToFile(std::ofstream& ofs, const User& user);
	void writeTopicToFile(std::ofstream& ofs, const Topic& topic);
	void writePostToFile(std::ofstream& ofs, const Post& post);
	void writeCommentToFile(std::ofstream& ofs, const Comment& comment);

public:
	FileManager(SocialNetwork& sn);
	FileManager(const FileManager& other) = delete;
	FileManager& operator=(const FileManager& other) = delete;
	void readSocialNetworkFromBinaryFile();
	void writeSocialNetworkToFile();

};

