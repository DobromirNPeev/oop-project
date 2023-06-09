#include "SocialNetwork.h"

const char* OFFSET = "   ";

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
		users.pushBack(std::move(readUserFromBinaryFile(ifs)));
	}
	int topicsSize = 0;
	ifs.read((char*)&topicsSize, sizeof(topicsSize));
	for (size_t i = 0; i < topicsSize; i++)
	{
		topics.pushBack(std::move(readTopicFromBinaryFile(ifs)));
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
void SocialNetwork::signup() {
	User current;
	std::cin >> current;
	current.id=SocialNetwork::idCount++;
	if (!containsUser(current)) {
		std::cout << "User already exists" << std::endl;
		return;
	}
	users.pushBack(current);
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
void SocialNetwork::login() {
	if (loggedUser != nullptr) {
		std::cout << "Already logged in" << std::endl;
		return;
	}
	MyString name;
	MyString password;
	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "password: ";
	std::cin >> password;
	int i = 0;
	if ((i=containsUser(name,password))==-1) {
		std::cout << "Incorrect, please try again"<<std::endl;
		return;
	}
	std::cout << "Welcome "<<name<<std::endl;
	loggedUser=&users[i];
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
void SocialNetwork::open(const MyString& topicName) {
	if (loggedUser == nullptr|| openedTopic!=nullptr) {
		std::cout << "Cannot acces topic" << std::endl;
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
	std::cout << "No such topic" << std::endl;
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
	std::cout << "No such topic" << std::endl;

}
void SocialNetwork::list() {
	if (loggedUser == nullptr || openedTopic==nullptr) {
		std::cout << "Cannot acces posts" << std::endl;
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
	std::cout << "No such post" << std::endl;
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
			printReplies(openedPost->comments[i],offset);
			//std::cout<<std::endl;
	}
}
void SocialNetwork::p_open(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost!=nullptr) {
		std::cout << "Cannot acces post" << std::endl;
		return;
	}
	int size = openedTopic->getPosts().getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (openedTopic->getPosts()[i].getID() == id) {
			openedPost=&(openedTopic->posts[i]);
			std::cout <<"Q: "<< openedTopic->getPosts()[i];
			return;
		}
	}
	std::cout << "No such post" << std::endl;

}

bool SocialNetwork::searchComment(unsigned id, Comment& toSearch) {
	for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	{
		if (toSearch.replies[i].id == id) {
			std::cout << "Say somehting: ";
			Comment answer;
			std::cin >> answer;
			answer.creator = loggedUser;
			answer.id = openedPost->commentsCounter++;
			toSearch.replies[i].replies.pushBack(answer);
			std::cout << "Posted" << std::endl;
			return true;
		}
		if (toSearch.replies[i].replies.getSize()> 0) {
			searchComment(id, toSearch.replies[i]);
		}
	}
	return false;
}
void SocialNetwork::reply(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot reply" << std::endl;
		return;
	}
	
	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		if (openedPost->comments[i].id == id) {
			std::cout << "Say somehting: ";
			Comment answer;
			std::cin >> answer;
			answer.creator = loggedUser;
			answer.id = openedPost->commentsCounter++;
			openedPost->comments[i].replies.pushBack(answer);
			std::cout << "Posted" << std::endl;
			return;
		}
		else {
			if (searchComment(id, openedPost->comments[i]))
				return;
		}
	}
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
		std::cout << std::endl;
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
	}

}
bool SocialNetwork::searchCommentAndUpvote(unsigned id, Comment& toSearch) {
	for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	{
		int searchUpvoted = toSearch.replies[i].didUserUpvoted(loggedUser->id);
		int searchDownvoted = toSearch.replies[i].didUserDownvoted(loggedUser->id);
		if (toSearch.replies[i].id == id && searchUpvoted == -1 && searchDownvoted == -1) {
			toSearch.replies[i].IncreaseUpVote();
			toSearch.replies[i].indexesOfUpvoters.pushBack(loggedUser->id);
			return true;
		}
		else if (toSearch.replies[i].id == id && searchUpvoted != -1) {
			toSearch.replies[i].DecreaseUpVote();
			toSearch.replies[i].indexesOfUpvoters.popAt(searchUpvoted);
			return true;
		}
		else if (toSearch.replies[i].id == id && searchDownvoted != -1) {
			toSearch.replies[i].IncreaseUpVote();
			toSearch.replies[i].DecreaseDownVote();
			toSearch.replies[i].indexesOfUpvoters.pushBack(loggedUser->id);
			toSearch.replies[i].indexesOfDownvoters.popAt(searchDownvoted);
			return true;
		}
		else if (toSearch.replies[i].replies.getSize() > 0) {
			if (searchCommentAndUpvote(id, toSearch.replies[i]))
				return true;
		}
	}
	return false;
	/*int searchUpvoted = loggedUser->searchUpvotedId(id);
	int searchDownVoted = loggedUser->searchDownvotedId(id);
	for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	{

		if (toSearch.replies[i].id == id && searchUpvoted == -1 && searchDownVoted == -1) {
			toSearch.replies[i].IncreaseUpVote();
			loggedUser->upvotedComments.pushBack(id);
			return true;
		}
		else if (toSearch.replies[i].id == id && searchUpvoted != -1) {
			toSearch.replies[i].DecreaseUpVote();
			loggedUser->upvotedComments.popAt(searchUpvoted);
			return true;
		}
		else if (toSearch.replies[i].id == id && searchDownVoted != -1) {
			toSearch.replies[i].IncreaseUpVote();
			toSearch.replies[i].DecreaseDownVote();
			loggedUser->upvotedComments.pushBack(id);
			loggedUser->downvotedComments.popAt(searchUpvoted);
			return true;
		}
		if (toSearch.replies[i].replies.getSize() > 0) {
			if (searchCommentAndUpvote(id, toSearch.replies[i]))
				return true;
		}
	}
	return false;*/
	/*for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	{
		if (toSearch.replies[i].id == id && loggedUser->voted == false) {
			toSearch.replies[i].IncreaseUpVote();
			loggedUser->voted = true;
			loggedUser->votedComments.pushBack(id);
			return true;
		}
		else if (toSearch.replies[i].id == id && loggedUser->voted == true) {
			toSearch.replies[i].DecreaseUpVote();
			loggedUser->voted = false;
			loggedUser->votedComments.pushBack(id);
			return true;
		}
		if (toSearch.replies[i].replies.getSize() > 0) {
			if (searchCommentAndUpvote(id, toSearch.replies[i]))
				return true;
		}
	}
	return false;*/
}
bool SocialNetwork::searchCommentAndDownvote(unsigned id, Comment& toSearch) {
	for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	{
		int searchUpvoted = toSearch.replies[i].didUserUpvoted(loggedUser->id);
		int searchDownvoted = toSearch.replies[i].didUserDownvoted(loggedUser->id);

		if (toSearch.replies[i].id == id && searchUpvoted == -1 && searchDownvoted == -1) {
			toSearch.replies[i].IncreaseDownVote();
			toSearch.replies[i].indexesOfDownvoters.pushBack(loggedUser->id);
			//loggedUser->downvotedComments.pushBack(id);
			return true;
		}
		else if (toSearch.replies[i].id == id && searchDownvoted != -1) {
			toSearch.replies[i].DecreaseDownVote();
			toSearch.replies[i].indexesOfDownvoters.popAt(searchDownvoted);

			//loggedUser->downvotedComments.popAt(searchDownVoted);
			return true;
		}
		else if (toSearch.replies[i].id == id && searchUpvoted != -1) {
			toSearch.replies[i].DecreaseUpVote();
			toSearch.replies[i].IncreaseDownVote();
			toSearch.replies[i].indexesOfDownvoters.pushBack(loggedUser->id);
			toSearch.replies[i].indexesOfUpvoters.popAt(searchUpvoted);
			//loggedUser->downvotedComments.pushBack(id);
			//loggedUser->upvotedComments.popAt(searchUpvoted);
			return true;
		}
		else if (toSearch.replies[i].replies.getSize() > 0) {
			if (searchCommentAndDownvote(id, toSearch.replies[i]))
				return true;
		}
	}
	return false;
	//for (size_t i = 0; i < toSearch.replies.getSize(); i++)
	//{
	//	if (toSearch.replies[i].id == id && loggedUser->searchId(id)==-1) {
	//		toSearch.replies[i].IncreaseDownVote();
	//		loggedUser->votedComments.pushBack(id);
	//		loggedUser->voted = true;
	//		return true;
	//	}
	//	else if (toSearch.replies[i].id == id && loggedUser->searchId(id)!=-1) {
	//		toSearch.replies[i].DecreaseDownVote();
	//		//loggedUser->votedComments(id);
	//		loggedUser->voted = false;
	//		return true;
	//	}
	//	if (toSearch.replies[i].replies.getSize() > 0) {
	//		if (searchCommentAndUpvote(id, toSearch.replies[i]))
	//			return true;
	//	}
	//}
	//return false;
}
void SocialNetwork::upvote(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot upvote" << std::endl;
		return;
	}
	
	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		int searchUpvoted = openedPost->comments[i].didUserUpvoted(loggedUser->id);
		int searchDownvoted = openedPost->comments[i].didUserDownvoted(loggedUser->id);
		if (openedPost->comments[i].id == id && searchUpvoted == -1 && searchDownvoted==-1) {
			openedPost->comments[i].IncreaseUpVote();
			openedPost->comments[i].indexesOfUpvoters.pushBack(loggedUser->id);
			break;
		}
		else if (openedPost->comments[i].id == id && searchUpvoted != -1) {
			openedPost->comments[i].DecreaseUpVote();
			openedPost->comments[i].indexesOfUpvoters.popAt(searchUpvoted);
			break;
		}
		else if (openedPost->comments[i].id == id &&  searchDownvoted != -1) {
			openedPost->comments[i].IncreaseUpVote();
			openedPost->comments[i].DecreaseDownVote();
			openedPost->comments[i].indexesOfUpvoters.pushBack(loggedUser->id);
			openedPost->comments[i].indexesOfDownvoters.popAt(searchDownvoted);
			break;
		}
		else if (openedPost->comments[i].replies.getSize() > 0) {
			if (searchCommentAndUpvote(id, openedPost->comments[i]))
				return;
		}
	}
}
void SocialNetwork::downvote(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot upvote" << std::endl;
		return;
	}
	for (size_t i = 0; i < openedPost->getComments().getSize(); i++)
	{
		int searchUpvoted = openedPost->comments[i].didUserUpvoted(loggedUser->id);
		int searchDownvoted = openedPost->comments[i].didUserDownvoted(loggedUser->id);

		if (openedPost->comments[i].id == id && searchUpvoted == -1 && searchDownvoted == -1) {
			openedPost->comments[i].IncreaseDownVote();
			openedPost->comments[i].indexesOfDownvoters.pushBack(loggedUser->id);
			//loggedUser->downvotedComments.pushBack(id);
			return;
		}
		else if (openedPost->comments[i].id == id && searchDownvoted != -1) {
			openedPost->comments[i].DecreaseDownVote();
			openedPost->comments[i].indexesOfDownvoters.popAt(searchUpvoted);

			//loggedUser->downvotedComments.popAt(searchDownVoted);
			return;
		}
		else if (openedPost->comments[i].id == id && searchUpvoted != -1) {
			openedPost->comments[i].DecreaseUpVote();
			openedPost->comments[i].IncreaseDownVote();
			openedPost->comments[i].indexesOfDownvoters.pushBack(loggedUser->id);
			openedPost->comments[i].indexesOfUpvoters.popAt(searchUpvoted);
			//loggedUser->downvotedComments.pushBack(id);
			//loggedUser->upvotedComments.popAt(searchUpvoted);
			return;
		}
		else if(openedPost->comments[i].replies.getSize()>0) {
			if (searchCommentAndDownvote(id, openedPost->comments[i]))
				return;
		}
	}
	//if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
	//	std::cout << "Cannot downvote" << std::endl;
	//	return;
	//}
	////static Vector<Comment> comments = openedPost.get()->getComments();
	//for (size_t i = 0; i < openedPost->getComments().getSize(); i++)
	//{
	//	if (openedPost->comments[i].id == id && loggedUser->voted == false) {
	//		openedPost->comments[i].IncreaseDownVote();
	//		loggedUser->votedComments.pushBack(id);
	//		loggedUser->voted = true;
	//	}
	//	else if (openedPost->getComments()[i].getID() == id && loggedUser->voted == true) {
	//		openedPost->comments[i].DecreaseDownVote();
	//		loggedUser->votedComments.pushBack(id);
	//		loggedUser->voted = false;
	//	}
	//	else {
	//		if (searchCommentAndDownvote(id, openedPost->comments[i]))
	//			break;

	//	}
	//}
}
void SocialNetwork::quit() {
	if (openedTopic == nullptr || loggedUser==nullptr ) {
		std::cout << "Cannot quit,no opened topic" << std::endl;
		return;
	}
	std::cout << "You just left topic " << openedTopic->heading << std::endl;
	openedTopic=nullptr;
	openedPost = nullptr;
}
void SocialNetwork::logout()
{
	if (loggedUser == nullptr) {
		std::cout << "Can't log out, no logged user" << std::endl;
		return;
	}
		std::cout << "Goodbye," << loggedUser->firstName<<" " << loggedUser->lastName << std::endl;
		loggedUser=nullptr;
		openedTopic = nullptr;
		openedPost = nullptr;
}
void SocialNetwork::p_quit() {
	if (openedTopic == nullptr || loggedUser == nullptr||openedPost==nullptr) {
		std::cout << "Cannot post quit" << std::endl;
		return;
	}
	std::cout << "You just left " << openedPost->heading<<std::endl;
	openedPost=nullptr;
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