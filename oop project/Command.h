//#include "SocialNetwork.h"
//class Command {
//public:
//	virtual void run(SocialNetwork* soc) const = 0;
//	virtual ~Command()=default;
//};
//
//struct Login: Command {
//public:
//	void run(SocialNetwork* soc) const override {
//		MyString name;
//		MyString password;
//		std::cout << "Name: ";
//		std::cin >> name;
//		std::cout << "password: ";
//		std::cin >> password;
//		int i = 0;
//		if ((i = soc->containsUser(name, password)) == -1) {
//			std::cout << "Incorrect, please try again" << std::endl;
//		}
//		std::cout << "Welcome " << name << std::endl;
//		soc->loggedUser = &(soc->users[i]);
//	}
//};