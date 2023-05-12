#include "SocialNetwork.h"
MyString readStringFromFile(std::ifstream& file) {
	size_t stringLength;
	file.read((char*)&stringLength, sizeof(size_t));
	char* str = new char[stringLength + 1];
	file.read(str, stringLength);
	str[stringLength] = '\0';

	return str;
}

Comment SocialNetwork::readCommentFromBinaryFile(std::ifstream& ifs) {
	static Comment comment;
	static size_t indexOfCreator;
	ifs.read((char*)&indexOfCreator, sizeof(indexOfCreator));
	comment.creator = &users[indexOfCreator];
	comment.indexOfCreator = indexOfCreator;
	comment.description = readStringFromFile(ifs);
	static int repliesCount;
	ifs.read((char*)&repliesCount, sizeof(size_t));
	for (size_t i = 0; i < repliesCount; i++)
	{
		comment.replies[i] = readStringFromFile(ifs);
	}
	static unsigned upVoteCounter;
	ifs.read((char*)&upVoteCounter, sizeof(unsigned));
	comment.upvoteCounter = upVoteCounter;
	static unsigned downVoteCounter;
	ifs.read((char*)&downVoteCounter, sizeof(unsigned));
	comment.downvoteCounter = downVoteCounter;
	static unsigned commentIdCount;
	ifs.read((char*)&commentIdCount, sizeof(unsigned));
	comment.idCount = commentIdCount;
	static unsigned commentId;
	ifs.read((char*)&commentId, sizeof(unsigned));
	comment.id = commentId;
	return comment;
}
Post SocialNetwork::readPostFromBinaryFile(std::ifstream& ifs)
{
	static Post post;
	post.heading = readStringFromFile(ifs);
	post.description = readStringFromFile(ifs);
	static int commentsCount;
	ifs.read((char*)&commentsCount, sizeof(size_t));
	for (size_t i = 0; i < commentsCount; i++)
	{
		post.comments[i] = readCommentFromBinaryFile(ifs);
	}
	static unsigned postIdCount;
	ifs.read((char*)&postIdCount, sizeof(unsigned));
	post.idCount = postIdCount;
	static unsigned postId;
	ifs.read((char*)&postId, sizeof(unsigned));
	post.id = postId;
	return post;
}
Topic SocialNetwork::readTopicFromBinaryFile(std::ifstream& ifs)
{
	static Topic topic;
	topic.heading = readStringFromFile(ifs);
	static size_t indexOfCreator;
	ifs.read((char*)&indexOfCreator, sizeof(indexOfCreator));
	topic.creator = &users[indexOfCreator];
	topic.indexOfCreator = indexOfCreator;
	static int postsCount;
	ifs.read((char*)&postsCount, sizeof(postsCount));
	for (size_t i = 0; i < postsCount; i++)
	{
		topic.posts[i] = readPostFromBinaryFile(ifs);
	}
	topic.description = readStringFromFile(ifs);
	static unsigned topicId;
	ifs.read((char*)&topicId, sizeof(unsigned));
	topic.id = topicId;
	return topic;
}

User SocialNetwork::readUserFromBinaryFile(std::ifstream& ifs)
{	
	static User user;
	user.firstName = readStringFromFile(ifs);
	user.lastName = readStringFromFile(ifs);
	user.password = readStringFromFile(ifs);
	static unsigned id;
	ifs.read((char*)&id, sizeof(unsigned));
	user.id = id;
	static unsigned points;
	user.points = points;
	ifs.read((char*)&points, sizeof(unsigned));
	static bool upOrDownVoted;
	ifs.read((char*)&upOrDownVoted, sizeof(bool));
	user.upVoted = upOrDownVoted;
	ifs.read((char*)&upOrDownVoted, sizeof(bool));
	user.downVoted = upOrDownVoted;
	return user;
}
void writeStringToFile(std::ofstream& file, const char* str) {
	size_t stringLength = strlen(str);
	file.write((const char*)&stringLength, sizeof(size_t));
	file.write(str, stringLength);
}
void SocialNetwork::writeCommentToFile(std::ofstream& ofs, const Comment& comment) {
	ofs.write((const char*)&comment.indexOfCreator, sizeof(comment.indexOfCreator));
	writeStringToFile(ofs, comment.description.c_str());
	int repliesSize = comment.replies.getSize();
	ofs.write((const char*)&repliesSize, sizeof(repliesSize));
	for (size_t i = 0; i < comment.replies.getSize(); i++)
	{
		writeStringToFile(ofs, comment.replies[i].c_str());
	}
	ofs.write((const char*)&comment.upvoteCounter, sizeof(comment.upvoteCounter));
	ofs.write((const char*)&comment.downvoteCounter, sizeof(comment.downvoteCounter));
	ofs.write((const char*)&comment.idCount, sizeof(comment.idCount));
	ofs.write((const char*)&comment.id, sizeof(comment.id));
}
void SocialNetwork::writePostToFile(std::ofstream& ofs, const Post& post) {
	writeStringToFile(ofs, post.heading.c_str());
	writeStringToFile(ofs, post.description.c_str());
	int commentsSize = post.comments.getSize();
	ofs.write((const char*)&commentsSize, sizeof(commentsSize));
	for (size_t i = 0; i < post.comments.getSize(); i++)
	{
		writeCommentToFile(ofs, post.comments[i]);
	}
	ofs.write((const char*)&post.idCount, sizeof(post.idCount));
	ofs.write((const char*)&post.id, sizeof(post.id));
}
void SocialNetwork::writeTopicToFile(std::ofstream& ofs, const Topic& topic) {
	writeStringToFile(ofs, topic.heading.c_str());
	ofs.write((const char*)&topic.indexOfCreator, sizeof(topic.indexOfCreator));
	int postsSize = topic.posts.getSize();
	ofs.write((const char*)&postsSize, sizeof(postsSize));
	for (size_t i = 0; i < topic.posts.getSize(); i++)
	{
		writePostToFile(ofs, topic.posts[i]);
	}
	writeStringToFile(ofs, topic.description.c_str());
	ofs.write((const char*)&topic.id, sizeof(topic.id));
}
void SocialNetwork::writeUserToFile(std::ofstream& ofs,const User& user) {
	writeStringToFile(ofs, user.firstName.c_str());
	writeStringToFile(ofs, user.lastName.c_str());
	writeStringToFile(ofs, user.password.c_str());
	ofs.write((const char*)&user.id, sizeof(user.id));
	ofs.write((const char*)&user.points, sizeof(user.points));
	ofs.write((const char*)&user.upVoted, sizeof(user.upVoted));
	ofs.write((const char*)&user.downVoted, sizeof(user.downVoted));
}

SocialNetwork::~SocialNetwork() {
	std::ofstream ofs("Data.dat", std::ios::out | std::ios::binary);
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
}

SocialNetwork::SocialNetwork() {
	std::ifstream ifs("Data.dat", std::ios::in | std::ios::binary);
	ifs.read((char*)&idCount, sizeof(idCount));
	int usersSize = 0;
	ifs.read((char*)&usersSize, sizeof(usersSize));
	for (size_t i = 0; i < usersSize; i++)
	{
		users.pushBack(readUserFromBinaryFile(ifs));
	}
	int topicsSize = 0;
	ifs.read((char*)&topicsSize, sizeof(topicsSize));
	for (size_t i = 0; i < topicsSize; i++)
	{
		topics.pushBack(readTopicFromBinaryFile(ifs));
	}
};

unsigned SocialNetwork::idCount = 0;
int SocialNetwork::findUser() {
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (&users[i] == loggedUser.get()) {
			return i;
		}
	}
	return -1;
}
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
int SocialNetwork::findTopic(unsigned n) {
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (topics[i].id == n) {
			return n;
		}
	}
	return -1;
}
void SocialNetwork::whoiami() {
	std::cout << loggedUser.get();
}
void SocialNetwork::about(unsigned id) {
	std::cout << topics[findTopic(id)];
}
bool SocialNetwork::login() {
	static MyString name;
	static MyString password;
	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "password: ";
	std::cin >> password;
	int i = 0;
	if (i=(containsUser(name,password)==-1)) {
		std::cout << "Incorrect, please try again"<<std::endl;
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
			std::cout << "Welcome to" << topics[i].heading;
				openedTopic.set(&topics[i]);
		}
	}
}
void SocialNetwork::open(unsigned id) {
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (topics[i].getID() == id) {
			std::cout << "Welcome to" << topics[i].heading;
			openedTopic.set(&topics[i]);
		}
	}
}
void SocialNetwork::list() {
	static unsigned numberOfPosts = openedTopic.get()->getPosts().getSize();
	for (size_t i = 0; i < numberOfPosts; i++)
	{
		std::cout << openedTopic.get()->getPosts()[i];
	}
}
void SocialNetwork::p_open(const MyString& postName) {
	int size = openedTopic.get()->getPosts().getSize();
	static Vector<Post> posts = openedTopic.get()->getPosts();
	for (size_t i = 0; i < size; i++)
	{
		if (searchInText(posts[i].getHeading().c_str(), postName.c_str())) {
			openedPost.set(&posts[i]);
		}
	}
}
void SocialNetwork::comment(const MyString& description) {
	loggedUser.get()->points++;
	openedPost.get()->getComments().pushBack(Comment(*(loggedUser.get()), description));
}
void SocialNetwork::p_open(unsigned id) {
	int size = openedTopic.get()->getPosts().getSize();
	static Vector<Post> posts = openedTopic.get()->getPosts();
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
	//static Vector<Comment> comments = openedPost.get()->getComments();
	for (size_t i = 0; i < openedPost.get()->getComments().getSize(); i++)
	{
		if (openedPost.get()->getComments()[i].getID() == id) {
			openedPost.get()->getComments().pushBack(Comment(*(loggedUser.get()), answer));
		}
	}
}
void SocialNetwork::post(const MyString& title, const MyString& description){
	openedTopic.get()->getPosts().pushBack(Post(title, description));
}
void SocialNetwork::run(){
	MyString command;
	while (command != "exit") {
		std::cout << "Command: ";
		std::cin >> command;

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
			search();
		}
		else if (command == "create") {
			create();
		}
		else if (command == "open") {

		}
	}

}
void SocialNetwork::upvote(unsigned id) {
	static Vector<Comment> comments = openedPost.get()->getComments();
	for (size_t i = 0; i < openedPost.get()->getComments().getSize(); i++)
	{
		if (comments[i].getID() == id && loggedUser.get()->upVoted==false) {
			comments[i].IncreaseUpVote();
			openedPost.get()->getComments() = comments;
			loggedUser.get()->upVoted = true;
		}
		else if (comments[i].getID() == id && loggedUser.get()->upVoted == true) {
			comments[i].DecreaseUpVote();
			openedPost.get()->getComments() = comments;
			loggedUser.get()->upVoted = false;
		}
	}
}
void SocialNetwork::quit() {
	openedTopic.set(nullptr);
}
void SocialNetwork::logout()
{
	std::cout << "Goodbye," << loggedUser.get()->firstName << loggedUser.get()->lastName;
	loggedUser.set(nullptr);
}
void SocialNetwork::p_quit() {
	openedPost.set(nullptr);
}
void SocialNetwork::downvote(unsigned id) {
	static Vector<Comment> comments = openedPost.get()->getComments();
	for (size_t i = 0; i < openedPost.get()->getComments().getSize(); i++)
	{
		if (comments[i].getID() == id && loggedUser.get()->downVoted == false) {
			comments[i].IncreaseDownVote();
			openedPost.get()->getComments()= comments;
			loggedUser.get()->downVoted = true;
		}
		else if (comments[i].getID() == id && loggedUser.get()->downVoted == true) {
			comments[i].DecreaseDownVote();
			openedPost.get()->getComments() = comments;
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
	newTopic.setCreator(*loggedUser.get());
	newTopic.indexOfCreator = findUser();
	topics.pushBack(newTopic);

}
void SocialNetwork::search()
{
	static MyString topicName;
	std::cin >> topicName;
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