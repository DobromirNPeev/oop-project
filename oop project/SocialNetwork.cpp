#include "SocialNetwork.h"


SocialNetwork::SocialNetwork() {
	readSocialNetworkFromBinaryFile();
};

SocialNetwork::~SocialNetwork() {
	writeSocialNetworkToFile();
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
	std::cout << WELCOME_MESSAGE <<std::endl;
	std::cout << INSTRUCTION_SIGNUP <<std::endl;
	std::cout << INSTRUCTION_LOGIN << std::endl;
	std::cout << INSTRUCTION_CREATE << std::endl;
	std::cout << INSTRUCTION_SEARCH << std::endl;
	std::cout << INSTRUCTION_OPEN << std::endl;
	std::cout << INSTRUCTION_LIST << std::endl;
	std::cout << INSTRUCTION_POST << std::endl;
	std::cout << INSTRUCTION_P_OPEN << std::endl;
	std::cout << INSTRUCTION_COMMENT << std::endl;
	std::cout << INSTRUCTION_COMMENTS << std::endl;
	std::cout << INSTRUCTION_REPLY << std::endl;
	std::cout << INSTRUCTION_UPVOTE << std::endl;
	std::cout << INSTRUCTION_DOWNVOTE << std::endl;
	std::cout << INSTRUCTION_P_QUIT << std::endl;
	std::cout << INSTRUCTION_QUIT << std::endl;
	std::cout << INSTRUCTION_WHOAMI << std::endl;
	std::cout << INSTRUCTION_ABOUT << std::endl;

	while (true) {
		std::cout << ">";
		std::cin >> command;
		std::cout << std::endl;
		if (!checkAcces(command))
			continue;
		if (command == SIGNUP) {
			signup();
		}
		else if (command == LOGIN) {
			login();
		}
		else if (command == LOGOUT) {

			logout();
		}
		else if (command == SEARCH) {
			static MyString topicName;
			std::cout << ENTER_KEYWORD;
			std::cin >> topicName;
			search(topicName);
		}
		else if (command == CREATE) {
			create();
		}
		else if (command == OPEN) {
			static MyString topicName;
			std::cout << ENTER_ID_OR_NAME;
			std::cin >> topicName;
			int id = fromString(topicName.c_str());
			if (id == -1) {
				open(topicName.c_str());
			}
			else {
				open(id);
			}

		}
		else if (command == P_OPEN) {
			static MyString topicName;
			std::cout << ENTER_ID_OR_NAME;
			std::cin >> topicName;
			int id = fromString(topicName.c_str());
			if (id == -1) {
				p_open(topicName.c_str());
			}
			else {
				p_open(id);
			}
		}
		else if (command == POST) {
			post();
		}
		else if (command == COMMENT) {
			comment();
		}
		else if (command == COMMENTS) {
			comments();
		}
		else if (command == REPLY)  {
			unsigned id;
			std::cout << ENTER_ID;
			std::cin >> id;
			std::cin.ignore();
			reply(id);
		}
		else if (command == UPVOTE) {
			unsigned id;
			std::cout << ENTER_ID;
			std::cin >> id;
			std::cin.ignore();
			upvote(id);
		}
		else if (command == DOWNVOTE) {
			unsigned id;
			std::cout << ENTER_ID;
			std::cin >> id;
			std::cin.ignore();
			downvote(id);
		}
		else if (command == LIST) {
			list();
		}
		else if (command == P_QUIT) {
			p_quit();
		}
		else if (command == QUIT) {
			quit();
		}
		else if (command == WHOAMI) {
			whoami();
		}
		else if (command == ABOUT) {
			unsigned id;
			std::cout << ENTER_ID;
			std::cin >> id;
			std::cin.ignore();
			about(id);
		}
		else if (command == EXIT) {
			break;
		}
		else {
			std::cout << INVALID_COMMAND<<std::endl;
		}
		std::cout << std::endl;
	}

}
