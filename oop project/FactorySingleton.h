//#include "Command.h"
//
//class FactorySingleton {
//private:
//    static FactorySingleton* instance;
//
//    FactorySingleton() {}
//
//public:
//    static FactorySingleton* getInstance() {
//        if (instance == nullptr) {
//            instance = new FactorySingleton();
//        }
//        return instance;
//    }
//
//    Command* createProduct(const char* comm,SocialNetwork* soc) {
//        switch (comm) {
//        case "login":return new Login(soc);
//        }
//    }
//};