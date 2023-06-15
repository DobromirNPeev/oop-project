#include "SocialNetwork.h"

SocialNetwork::SocialNetwork() {
	std::ifstream ifs("Data.dat", std::ios::in | std::ios::binary);
	if (!ifs.is_open()) {
		throw std::logic_error("Unable to open file");
	}
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
	ifs.close();
};

SocialNetwork::~SocialNetwork() {
	std::ofstream ofs("Data.dat", std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		throw std::logic_error("Unable to save");
	}
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
	ofs.close();
}


namespace {
	unsigned int convertFromChar(char ch)
	{
		if (ch < '0' || ch > '9')
			return 10;
		return ch - '0';
	}

	unsigned int fromString(const char* str)
	{
		unsigned int result = 0;
		while (*str != '\0')
		{
			int currentDigit = convertFromChar(*str);
			if (currentDigit == 10) {
				return -1;
			}
			(result *= 10) += currentDigit;
			str++;
		}
		return result;
	}
}

unsigned SocialNetwork::idCount = 0;

void SocialNetwork::run(){
	MyString command;
	std::cout << "Welcome to the Social Network. Here is the list of commands you can use:"<<std::endl;
	std::cout << "| signup - create an user"<<std::endl;
	std::cout << "| login - expects a first name and a password and if they are correct the user logs in" << std::endl;
	std::cout << "| create - you can create your own topic" << std::endl;
	std::cout << "| search - you enter a keyword and it shows all the topics that have it" << std::endl;
	std::cout << "| open - you enter an id or keyword and it opens the desired topic" << std::endl;
	std::cout << "| list - you can see all the posts on the opened topic" << std::endl;
	std::cout << "| post - you can create a post int the opened topic" << std::endl;
	std::cout << "| p_open - you enter an id or keyword and it opens the desired post in the opened topic" << std::endl;
	std::cout << "| comment - you can add a comment to the opened post" << std::endl;
	std::cout << "| comments - it shows you all the comments under the opened post" << std::endl;
	std::cout << "| reply - you enter an id of a comment and can reply to it" << std::endl;
	std::cout << "| upvote - add upvote reaction to a comment" << std::endl;
	std::cout << "| downvote - add downvote reaction to a comment" << std::endl;
	std::cout << "| p_quit - exit post reading mode" << std::endl;
	std::cout << "| quit - exit topic" << std::endl;
	std::cout << "| whoami - shows info about the user" << std::endl;
	std::cout << "| about - shows info about a certain topic" << std::endl;

	while (true) {
		std::cout << ">";
		std::cin >> command;
		std::cout << std::endl;

		if (command == "signup") {
			signup();
		}
		else if (command == "login") {
			login();
		}
		else if (command == "logout") {
			logout();
		}
		else if (command == "search") {
			MyString topicName;
			std::cout << "Enter keyword: ";
			std::cin >> topicName;
			search(topicName);
		}
		else if (command == "create") {
			create();
		}
		else if (command == "open") {
			MyString topicName;
			std::cout << "Enter id or topic name: ";
			std::cin >> topicName;
			int id = fromString(topicName.c_str());
			if (id == -1) {
				open(topicName.c_str());
			}
			else {
				open(id);
			}

		}
		else if (command == "p_open") {
			MyString topicName;
			std::cout << "Enter id or post name: ";
			std::cin >> topicName;
			int id = fromString(topicName.c_str());
			if (id == -1) {
				p_open(topicName.c_str());
			}
			else {
				p_open(id);
			}
		}
		else if (command == "post") {
			post();
		}
		else if (command == "comment") {
			comment();
		}
		else if (command == "comments") {
			comments();
		}
		else if (command == "reply")  {
			unsigned id;
			std::cout << "Enter comment id: ";
			std::cin >> id;
			std::cin.ignore();
			reply(id);
		}
		else if (command == "upvote") {
			unsigned id;
			std::cout << "Enter comment id: ";
			std::cin >> id;
			std::cin.ignore();
			upvote(id);
		}
		else if (command == "downvote") {
			unsigned id;
			std::cout << "Enter comment id: ";
			std::cin >> id;
			std::cin.ignore();
			downvote(id);
		}
		else if (command == "list") {
			list();
		}
		else if (command == "p_quit") {
			p_quit();
		}
		else if (command == "quit") {
			quit();
		}
		else if (command == "whoami") {
			whoami();
		}
		else if (command == "about") {
			unsigned id;
			std::cout << "Enter id: ";
			std::cin >> id;
			std::cin.ignore();
			about(id);
		}
		else if (command == "exit") {
			break;
		}
		else {
			std::cout << "Invalid command"<<std::endl;
		}
		std::cout << std::endl;
	}

}
