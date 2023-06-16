#include "SocialNetwork.h"

SocialNetwork::SocialNetwork() {
	readSocialNetworkFromBinaryFile();
};

SocialNetwork::~SocialNetwork() {
	writeSocialNetworkToFile();
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
		if (!invokeCommand(command))
			break;
	}

}
