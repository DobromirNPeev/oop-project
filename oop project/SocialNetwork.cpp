#include "SocialNetwork.h"
void saveToBinaryFile(std::ofstream& ofs, const SocialNetwork& sn)
{
	
	/*int nameLen = strlen(st.name);
	ofs.write((const char*)&nameLen, sizeof(int));
	ofs.write(st.name, nameLen + 1);

	ofs.write((const char*)&st.age, sizeof(st.age));
	ofs.write((const char*)&st.fn, sizeof(st.fn));*/

}

SocialNetwork::SocialNetwork() {
	std::ifstream ifs("Data.dat", std::ios::in | std::ios::binary);
	int usersSize = 0;
	ifs.read((char*)usersSize, sizeof(usersSize));
	for (size_t i = 0; i < usersSize; i++)
	{

	}
};

unsigned SocialNetwork::idCount = 0;
bool SocialNetwork::signup() {
	static User current;
	std::cin >> current;
	current.id=SocialNetwork::idCount++;
	if (!containsUser(current)) {
		return false;
	}
	users.pushBack(current);
	return true;
}
bool SocialNetwork::login(const MyString& name, const MyString& password) {
	int i = 0;
	if (i=(containsUser(name,password)==-1)) {
		std::cout << "Incorrect, please try again";
		return false;
	}
	std::cout << "Welcome "<<name<<std::endl;
	loggedUser.set(&users[i]);
	return true;
}
bool isPrefix(const char* pattern, const char* text)
{
	while (*text != '\0' && *pattern != '\0')
	{
		if (*text != *pattern)
			return false;
		text++;
		pattern++;
	}
	return *pattern == '\0';
}

bool searchInText(const char* text, const char* pattern)
{
	size_t textLen = strlen(text);
	size_t patternLen = strlen(pattern);
	while (patternLen <= textLen)
	{
		if (isPrefix(pattern, text))
			return true;
		text++;
		textLen--;
	}
	return false;
}
//int SocialNetwork::findLoggedUser() {
//	for (size_t i = 0; i < users.getSize(); i++)
//	{
//		if (users[i].loggedIn) {
//			return i;
//		}
//	}
//}
void SocialNetwork::open(const MyString& topicName) {
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (searchInText(topics[i].getHeading(), topicName.c_str())) {
				openedTopic.set(&topics[i]);
		}
	}
}
void SocialNetwork::open(unsigned id) {
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (topics[i].getID() == id) {
			openedTopic.set(&topics[i]);
		}
	}
}
void SocialNetwork::list() {
	unsigned numberOfPosts = openedTopic.get()->getPosts()->getSize();
	static Vector<Post> posts = *(openedTopic.get()->getPosts());
	for (size_t i = 0; i < numberOfPosts; i++)
	{
		std::cout << posts[i];
	}
}
void SocialNetwork::p_open(const MyString& postName) {
	int size = openedTopic.get()->getPosts()->getSize();
	static Vector<Post> posts = *(openedTopic.get()->getPosts());
	for (size_t i = 0; i < size; i++)
	{
		if (searchInText(posts[i].getHeading().c_str(), postName.c_str())) {
			openedPost.set(&posts[i]);
		}
	}
}
void SocialNetwork::comment(const MyString& description) {
	loggedUser.get()->points++;
	openedPost.get()->getComments()->pushBack(Comment(*(loggedUser.get()),description));
}
void SocialNetwork::p_open(unsigned id) {
	int size = openedTopic.get()->getPosts()->getSize();
	static Vector<Post> posts = *(openedTopic.get()->getPosts());
	for (size_t i = 0; i < size; i++)
	{
		if (posts[i].getID() == id) {
			openedPost.set(&posts[i]);
		}
	}
}
void SocialNetwork::reply(unsigned id) {
	MyString answer;
	std::cin >> answer;
	static Vector<Comment> comments = *(openedPost.get()->getComments());
	for (size_t i = 0; i < openedPost.get()->getComments()->getSize(); i++)
	{
		if (comments[i].getID() == id) {
			openedPost.get()->getComments()->pushBack(Comment(*(loggedUser.get()), answer));
		}
	}
}
void SocialNetwork::post(const MyString& title, const MyString& description){
	openedTopic.get()->getPosts()->pushBack(Post(title, description));
}
void SocialNetwork::upvote(unsigned id) {
	static Vector<Comment> comments = *(openedPost.get()->getComments());
	for (size_t i = 0; i < openedPost.get()->getComments()->getSize(); i++)
	{
		if (comments[i].getID() == id && loggedUser.get()->upVoted==false) {
			comments[i].IncreaseUpVote();
			*(openedPost.get()->getComments()) = comments;
			loggedUser.get()->upVoted = true;
		}
		else if (comments[i].getID() == id && loggedUser.get()->upVoted == true) {
			comments[i].DecreaseUpVote();
			*(openedPost.get()->getComments()) = comments;
			loggedUser.get()->upVoted = false;
		}
	}
}
void SocialNetwork::quit() {
	openedTopic.set(nullptr);
}
void SocialNetwork::logout()
{
	loggedUser.set(nullptr);
}
void SocialNetwork::p_quit() {
	openedPost.set(nullptr);
}
void SocialNetwork::downvote(unsigned id) {
	static Vector<Comment> comments = *(openedPost.get()->getComments());
	for (size_t i = 0; i < openedPost.get()->getComments()->getSize(); i++)
	{
		if (comments[i].getID() == id && loggedUser.get()->downVoted == false) {
			comments[i].IncreaseDownVote();
			*(openedPost.get()->getComments()) = comments;
			loggedUser.get()->downVoted = true;
		}
		else if (comments[i].getID() == id && loggedUser.get()->downVoted == true) {
			comments[i].DecreaseDownVote();
			*(openedPost.get()->getComments()) = comments;
			loggedUser.get()->downVoted = false;
		}
	}
}
void SocialNetwork::create() {
	if (loggedUser.get() == nullptr)
		return;
	Topic newTopic;
	std::cin >> newTopic;
	newTopic.setID(idCount++);
	newTopic.setCreator(*(UniquePtr<User>::get()));
	topics.pushBack(newTopic);

}
void SocialNetwork::search(const MyString& topicName)
{
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (searchInText(topics[i].getHeading(), topicName.c_str())) {
			std::cout<<"-  "<<topics[i].getHeading();
		}
	}
}
bool SocialNetwork::containsUser(const User& other) const {
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (!strcmp(users[i].firstName.c_str(), other.firstName.c_str()) && !strcmp(users[i].lastName.c_str(), other.lastName.c_str()));
		return false;
	}
	return true;
}
int SocialNetwork::containsUser(const MyString& firstName, const MyString& password) const {

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (!strcmp(users[i].firstName.c_str(), firstName.c_str()) && !strcmp(users[i].password.c_str(), password.c_str())) {
			return i;
		}
	}
	return -1;
}