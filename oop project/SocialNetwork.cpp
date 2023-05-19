#include "SocialNetwork.h"

const char* OFFSET = "   ";

MyString readStringFromFile(std::ifstream& file) {
	int stringLength;
	file.read((char*)&stringLength, sizeof(int));
	char* str = new char[stringLength + 1];
	file.read(str, stringLength);
	str[stringLength] = '\0';

	return str;
}

Comment SocialNetwork::readCommentFromBinaryFile(std::ifstream& ifs) {
	Comment comment;
	size_t indexOfCreator;
	ifs.read((char*)&indexOfCreator, sizeof(indexOfCreator));
	comment.creator = &users[indexOfCreator];
	comment.indexOfCreator = indexOfCreator;
	comment.description = readStringFromFile(ifs);
	unsigned upVoteCounter;
	ifs.read((char*)&upVoteCounter, sizeof(unsigned));
	comment.upvoteCounter = upVoteCounter;
	unsigned downVoteCounter;
	ifs.read((char*)&downVoteCounter, sizeof(unsigned));
	comment.downvoteCounter = downVoteCounter;
	//unsigned commentIdCount;
	//ifs.read((char*)&commentIdCount, sizeof(unsigned));
	//comment.idCountComments = commentIdCount;
	unsigned commentId;
	ifs.read((char*)&commentId, sizeof(unsigned));
	comment.id = commentId;
	int repliesCount;
	ifs.read((char*)&repliesCount, sizeof(int));
	for (size_t i = 0; i < repliesCount; i++)
	{
		comment.replies.pushBack(readCommentFromBinaryFile(ifs));
	}
	return comment;
}
Post SocialNetwork::readPostFromBinaryFile(std::ifstream& ifs)
{
	Post post;
	post.heading = readStringFromFile(ifs);
	post.description = readStringFromFile(ifs);
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
		post.comments.pushBack(readCommentFromBinaryFile(ifs));
	}
	return post;
}
Topic SocialNetwork::readTopicFromBinaryFile(std::ifstream& ifs)
{
	Topic topic;
	topic.heading = readStringFromFile(ifs);
	size_t indexOfCreator;
	ifs.read((char*)&indexOfCreator, sizeof(indexOfCreator));
	topic.creator = &users[indexOfCreator];
	topic.indexOfCreator = indexOfCreator;
	topic.description = readStringFromFile(ifs);
	unsigned topicId;
	ifs.read((char*)&topicId, sizeof(unsigned));
	topic.id = topicId;
	int postsCount;
	ifs.read((char*)&postsCount, sizeof(postsCount));
	for (size_t i = 0; i < postsCount; i++)
	{
		topic.posts.pushBack(readPostFromBinaryFile(ifs));
	}
	return topic;
}

User SocialNetwork::readUserFromBinaryFile(std::ifstream& ifs)
{	
	User user;
	user.firstName = readStringFromFile(ifs);
	user.lastName = readStringFromFile(ifs);
	user.password = readStringFromFile(ifs);
	unsigned id;
	ifs.read((char*)&id, sizeof(unsigned));
	user.id = id;
	unsigned points;
	ifs.read((char*)&points, sizeof(unsigned));
	user.points = points;
	bool upOrDownVoted;
	ifs.read((char*)&upOrDownVoted, sizeof(bool));
	user.upVoted = upOrDownVoted;
	ifs.read((char*)&upOrDownVoted, sizeof(bool));
	user.downVoted = upOrDownVoted;
	return user;
}
void writeStringToFile(std::ofstream& file, const char* str) {
	int stringLength = strlen(str);
	file.write((const char*)&stringLength, sizeof(int));
	file.write(str, stringLength);
}

void SocialNetwork::writeCommentToFile(std::ofstream& ofs, const Comment& comment) {
	ofs.write((const char*)&comment.indexOfCreator, sizeof(comment.indexOfCreator));
	writeStringToFile(ofs, comment.description.c_str());
	ofs.write((const char*)&comment.upvoteCounter, sizeof(comment.upvoteCounter));
	ofs.write((const char*)&comment.downvoteCounter, sizeof(comment.downvoteCounter));
	//ofs.write((const char*)&comment.idCountComments, sizeof(comment.idCountComments));
	ofs.write((const char*)&comment.id, sizeof(comment.id));
	int repliesSize = comment.replies.getSize();
	ofs.write((const char*)&repliesSize, sizeof(repliesSize));
	for (size_t i = 0; i < comment.replies.getSize(); i++)
	{
		//writeStringToFile(ofs, comment.replies[i]);
		//writeStringToFile(ofs, comment.replies[i].c_str());
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
	int postsSize = topic.posts.getSize();
	ofs.write((const char*)&postsSize, sizeof(postsSize));
	for (size_t i = 0; i < topic.posts.getSize(); i++)
	{
		writePostToFile(ofs, topic.posts[i]);
	}
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
		if (&users[i] == loggedUser) {
			return i;
		}
	}
	return -1;
}
bool SocialNetwork::signup() {
	User current;
	std::cin >> current;
	current.id=SocialNetwork::idCount++;
	if (!containsUser(current)) {
		std::cout << "User already exists" << std::endl;
		return false;
	}
	users.pushBack(current);
	return true;
}
int SocialNetwork::findTopic(unsigned n) {
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (topics[i].id == n) {
			return i;
		}
	}
	return -1;
}
void SocialNetwork::whoami() {
	if (loggedUser == nullptr) {
		std::cout << "No logged user" << std::endl;
		return;
	}
	std::cout << *(loggedUser);
}
void SocialNetwork::about(unsigned id) {

	if (findTopic(id) == -1 || loggedUser==nullptr) {
		std::cout << "Cannot access or non-existent" << std::endl;
		return;
	}
	std::cout << topics[findTopic(id)];
}
bool SocialNetwork::login() {
	MyString name;
	MyString password;
	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "password: ";
	std::cin >> password;
	int i = 0;
	if ((i=containsUser(name,password))==-1) {
		std::cout << "Incorrect, please try again"<<std::endl;
		return false;
	}
	std::cout << "Welcome "<<name<<std::endl;
	loggedUser=&users[i];
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
	if (loggedUser == nullptr) {
		std::cout << "Cannot acces topic, no logged user" << std::endl;
		return;
	}
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (searchInText(topics[i].getHeading(), topicName.c_str())) {
			std::cout << "Welcome to " << topics[i].heading << std::endl;
			openedTopic=&topics[i];
			return;
		}
	}
}
void SocialNetwork::open(unsigned id) {
	if (loggedUser == nullptr) {
		std::cout << "Cannot acces topic, no logged user" << std::endl;
		return;
	}
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (topics[i].getID() == id) {
			std::cout << "Welcome to " << topics[i].heading<<std::endl;
			openedTopic=&topics[i];
			return;
		}
	}
}
void SocialNetwork::list() {
	if (loggedUser == nullptr || openedTopic==nullptr) {
		std::cout << "Cannot acces topics" << std::endl;
		return;
	}
	unsigned numberOfPosts = openedTopic->getPosts().getSize();
	for (size_t i = 0; i < numberOfPosts; i++)
	{
		std::cout << openedTopic->getPosts()[i];
	}
}
void SocialNetwork::p_open(const MyString& postName) {
	if (loggedUser == nullptr || openedTopic == nullptr) {
		std::cout << "Cannot acces post" << std::endl;
		return;
	}
	int size = openedTopic->getPosts().getSize();
	//static Vector<Post> posts = openedTopic.get()->getPosts();
	for (size_t i = 0; i < size; i++)
	{
		if (searchInText(openedTopic->getPosts()[i].getHeading().c_str(), postName.c_str())) {
			std::cout << "Q: " << openedTopic->getPosts()[i];
			openedPost=&(openedTopic->posts[i]);
			return;
		}
	}
}
void SocialNetwork::comment() {
	if (loggedUser == nullptr || openedTopic==nullptr || openedPost==nullptr) {
		std::cout << "Cannot comment" << std::endl;
		return;
	}
	Comment comment;
	std::cout << "Say something: ";
	std::cin >> comment;
	loggedUser->points++;
	comment.id = openedPost->commentsCounter++;
	openedPost->comments.pushBack(comment);
}
void SocialNetwork::printReplies(const Comment& comment,MyString& offset) {
	//MyString offsetCopy(offset);
	for (size_t i = 0; i < comment.replies.getSize(); i++)
	{
		std::cout << offset << comment.replies[i];
		if (comment.replies[i].replies.getSize() > 0) {
			offset += OFFSET;
			printReplies(comment.replies[i], offset);
		}
		offset = OFFSET;
	}
}
void SocialNetwork::comments() {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot see comments" << std::endl;
		return;
	}
	MyString offset(OFFSET);
	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		std::cout<< openedPost->comments[i];
		if (openedPost->comments[i].downvoteCounter!=0) {
			std::cout << "{downvote:" << openedPost->comments[i].downvoteCounter << "}" << std::endl;
		}
		else if(openedPost->comments[i].upvoteCounter != 0) {
			std::cout << "{upvote:" << openedPost->comments[i].upvoteCounter << "}"<<std::endl;
		}
		else if (openedPost->comments[i].downvoteCounter != 0 && openedPost->comments[i].upvoteCounter != 0) {
			std::cout << "{downvote:" << openedPost->comments[i].downvoteCounter << "}" << "{upvote:" << openedPost->comments[i].upvoteCounter << "}" << std::endl;
		}
		else {
			printReplies(openedPost->comments[i],offset);
			//std::cout<<std::endl;
		}
	}
}
void SocialNetwork::p_open(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost!=nullptr) {
		std::cout << "Cannot acces post" << std::endl;
		return;
	}
	int size = openedTopic->getPosts().getSize();
	//static Vector<Post> posts = openedTopic.get()->getPosts();
	for (size_t i = 0; i < size; i++)
	{
		if (openedTopic->getPosts()[i].getID() == id) {
			openedPost=&(openedTopic->posts[i]);
			std::cout << openedTopic->getPosts()[i];
			return;
		}
	}
}
bool SocialNetwork::searchComment(unsigned id,const Comment& answer,Comment& toSearch) {
	for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	{
		if (toSearch.replies[i].id == id) {
			toSearch.replies[i].replies.pushBack(answer);
			std::cout << "Posted" << std::endl;
			return true;
		}
		if (toSearch.replies[i].replies.getSize()> 0) {
			searchComment(id,answer, toSearch.replies[i]);
		}
	}
	return false;
}
void SocialNetwork::reply(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot reply" << std::endl;
		return;
	}
	std::cout << "Say somehting: ";
	Comment answer;
	std::cin>>answer;
	answer.creator = loggedUser;
	answer.id = openedPost->commentsCounter++;
	//answer.creator = loggedUser.get();
	//static Vector<Comment> comments = openedPost.get()->getComments();
	//for (size_t i = 0; i < openedPost.get()->getComments().getSize(); i++)
	//{
	//	if (openedPost.get()->comments[i].getID() == id) {
	//		//openedPost.get()->comments[i].replies.pushBack(answer);
	//		std::cout << "Posted" << std::endl;
	//	}
	//}
	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		if (openedPost->comments[i].id == id) {
			openedPost->comments[i].replies.pushBack(answer);
			std::cout << "Posted" << std::endl;
			return;
		}
		else {
			if (searchComment(id, answer, openedPost->comments[i]))
				break;
		}

		//if (openedPost->comments[i].getID() == id) {
		//	openedPost->comments[i].replies.pushBack(answer);
		//	std::cout << "Posted" << std::endl;
		//	return;
		//}
		//if (openedPost->comments[i].replies.getSize() > 0) {
		//	searchComment(id, answer);
		//}
	}
	/*searchComment(id,answer,);*/
}
void SocialNetwork::post(){
	if (openedTopic == nullptr || loggedUser==nullptr) {
		std::cout << "Cannot post" << std::endl;
		return;
	}
	Post newPost;
	std::cin >> newPost;
	newPost.id = openedTopic->postsCounter++;
	openedTopic->posts.pushBack(newPost);
}
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
			static MyString topicName;
			std::cout << "Enter keyword: ";
			std::cin >> topicName;
			search(topicName);
		}
		else if (command == "create") {
			create();
		}
		else if (command == "open") {
			static MyString topicName;
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
			static MyString topicName;
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
		else if (command == "reply") {
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
	}

}
void SocialNetwork::upvote(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot upvote" << std::endl;
		return;
	}
	for (size_t i = 0; i < openedPost->getComments().getSize(); i++)
	{
		if (openedPost->comments[i].getID() == id && loggedUser->upVoted == false) {
			openedPost->comments[i].IncreaseUpVote();
			//openedPost.get()->getComments() = comments;
			loggedUser->upVoted = true;
		}
		else if (openedPost->comments[i].getID() == id && loggedUser->upVoted == true) {
			openedPost->comments[i].DecreaseUpVote();
			//openedPost.get()->getComments() = comments;
			loggedUser->upVoted = false;
		}
	}
}
void SocialNetwork::quit() {
	if (openedTopic == nullptr || loggedUser==nullptr ) {
		std::cout << "Cannot quit,no opened topic" << std::endl;
		return;
	}
	openedTopic=nullptr;
}
void SocialNetwork::logout()
{
	if (loggedUser == nullptr) {
		std::cout << "Can't log out, no logged user" << std::endl;
		return;
	}
		std::cout << "Goodbye," << loggedUser->firstName<<" " << loggedUser->lastName << std::endl;
		loggedUser=nullptr;
}
void SocialNetwork::p_quit() {
	if (openedTopic == nullptr || loggedUser == nullptr||openedPost==nullptr) {
		std::cout << "Cannot post quit" << std::endl;
		return;
	}
	openedPost=nullptr;
}
void SocialNetwork::downvote(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot downvote" << std::endl;
		return;
	}
	//static Vector<Comment> comments = openedPost.get()->getComments();
	for (size_t i = 0; i < openedPost->getComments().getSize(); i++)
	{
		if (openedPost->getComments()[i].getID() == id && loggedUser->downVoted == false) {
			openedPost->getComments()[i].IncreaseDownVote();
			loggedUser->downVoted = true;
		}
		else if (openedPost->getComments()[i].getID() == id && loggedUser->downVoted == true) {
			openedPost->getComments()[i].DecreaseDownVote();
			loggedUser->downVoted = false;
		}
	}
}
void SocialNetwork::create() {
	if (loggedUser == nullptr){
		std::cout << "Cannot create"<<std::endl;
		return;
	}

	Topic newTopic;
	std::cin >> newTopic;
	newTopic.setID(idCount++);
	newTopic.setCreator(*loggedUser);
	newTopic.indexOfCreator = findUser();
	topics.pushBack(newTopic);

}
void SocialNetwork::search(const MyString& topicName)
{
	if (loggedUser == nullptr) {
		std::cout << "No logged user, can't open a topic"<<std::endl;
		return;
	}
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (searchInText(topics[i].getHeading(), topicName.c_str())) {
			std::cout<<"-  "<<topics[i].getHeading()<<"{id:"<<topics[i].id<<"}"<<std::endl;
		}
	}
}
bool SocialNetwork::containsUser(const User& other) const {
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i].firstName == other.firstName && users[i].lastName == other.lastName) {
			return false;
		}
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