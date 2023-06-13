#include "SocialNetwork.h"


namespace {
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
		template<typename T>
		int binarySearchInVector(const Vector<T>& arr, int el)
		{
			int left = 0, right = arr.getSize() - 1;

			while (left <= right)
			{
				unsigned mid = left + (right - left) / 2;
				if (arr[mid].getID() == el)
					return mid;
				else if (arr[mid].getID() > el)
					right = mid - 1;
				else //arr[mid] < el
					left = mid + 1;
			}
			return -1;
		}
		template <>
		int binarySearchInVector(const Vector<int>& arr, int el)
		{
			int left = 0, right = arr.getSize() - 1;

			while (left <= right)
			{
				unsigned mid = left + (right - left) / 2;
				if (arr[mid] == el)
					return mid;
				else if (arr[mid] > el)
					right = mid - 1;
				else //arr[mid] < el
					left = mid + 1;
			}
			return -1;
		}

}
void SocialNetwork::signup() {
	User current;
	std::cin >> current;
	current.id = SocialNetwork::idCount++;
	if (!containsUser(current)) {
		std::cout << "User already exists" << std::endl;
		return;
	}
	users.pushBack(std::move(current));
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
	if ((i = containsUser(name, password)) == -1) {
		std::cout << "Incorrect, please try again" << std::endl;
		return;
	}
	std::cout << "Welcome " << name << std::endl;
	loggedUser = &users[i];
}

void SocialNetwork::logout()
{
	if (loggedUser == nullptr) {
		std::cout << "Can't log out, no logged user" << std::endl;
		return;
	}
	std::cout << "Goodbye," << loggedUser->firstName << " " << loggedUser->lastName << std::endl;
	loggedUser = nullptr;
	openedTopic = nullptr;
	openedPost = nullptr;
}

void SocialNetwork::search(const MyString& topicName)
{
	if (loggedUser == nullptr) {
		std::cout << "No logged user, can't open a topic" << std::endl;
		return;
	}
	for (size_t i = 0; i < topics.getSize(); i++) {
		if (searchInText(topics[i].getHeading(), topicName.c_str())) {
			std::cout << "-  " << topics[i].getHeading() << "{id:" << topics[i].id << "}" << std::endl;
			return;
		}
	}
	std::cout << "No such topic" << std::endl;
}

void SocialNetwork::create() {
	if (loggedUser == nullptr) {
		std::cout << "Cannot create" << std::endl;
		return;
	}

	Topic newTopic;
	std::cin >> newTopic;
	newTopic.setID(idCount++);
	newTopic.setCreator(*loggedUser);
	newTopic.indexOfCreator = binarySearchInVector(users,loggedUser->id);
	topics.pushBack(std::move(newTopic));

}

void SocialNetwork::open(const MyString& topicName) {
	if (loggedUser == nullptr || openedTopic != nullptr) {
		std::cout << "Cannot acces topic" << std::endl;
		return;
	}
	for (size_t i = 0; i < topics.getSize(); i++)
	{
		if (searchInText(topics[i].getHeading(), topicName.c_str())) {
			std::cout << "Welcome to " << topics[i].heading << std::endl;
			openedTopic = &topics[i];
			return;
		}
	}
	std::cout << "No such topic" << std::endl;
}

void SocialNetwork::open(unsigned id) {
	if (loggedUser == nullptr || openedTopic!=nullptr) {
		std::cout << "Cannot acces topic" << std::endl;
		return;
	}
	int i = binarySearchInVector(topics, id);
	if (i == -1) {
		std::cout << "No such topic" << std::endl;
	}
	else {
		std::cout << "Welcome to " << topics[i].heading << std::endl;
		openedTopic = &topics[i];
	}
	//for (size_t i = 0; i < topics.getSize(); i++)
	//{
	//	if (topics[i].getID() == id) {
	//		std::cout << "Welcome to " << topics[i].heading << std::endl;
	//		openedTopic = &topics[i];
	//		return;
	//	}
	//}

}

void SocialNetwork::post() {
	if (openedTopic == nullptr || loggedUser == nullptr) {
		std::cout << "Cannot post" << std::endl;
		return;
	}
	Post newPost;
	std::cin >> newPost;
	newPost.id = openedTopic->postsCounter++;
	openedTopic->posts.pushBack(std::move(newPost));
}
void SocialNetwork::p_open(const MyString& postName) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost != nullptr ) {
		std::cout << "Cannot acces post" << std::endl;
		return;
	}
	int size = openedTopic->getPosts().getSize();
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


void SocialNetwork::p_open(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost != nullptr) {
		std::cout << "Cannot acces post" << std::endl;
		return;
	}
	int i = binarySearchInVector(openedTopic->posts, id);
	if (i == -1) {
		std::cout << "No such post" << std::endl;
	}
	else {
		openedPost = &(openedTopic->posts[i]);
		std::cout << "Q: " << openedTopic->posts[i];
	}
	/*int size = openedTopic->getPosts().getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (openedTopic->getPosts()[i].getID() == id) {
			openedPost = &(openedTopic->posts[i]);
			std::cout << "Q: " << openedTopic->getPosts()[i];
			return;
		}
	}*/


}

void SocialNetwork::comment() {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot comment" << std::endl;
		return;
	}
	Comment comment;
	std::cout << "Say something: ";
	std::cin >> comment;
	loggedUser->points++;
	comment.id = openedPost->commentsCounter++;
	openedPost->comments.pushBack(std::move(comment));
}

void SocialNetwork::comments() {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot see comments" << std::endl;
		return;
	}
	MyString offset(OFFSET);
	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		std::cout << openedPost->comments[i];
		printReplies(openedPost->comments[i], offset);
	}
}

void SocialNetwork::reply(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot reply" << std::endl;
		return;
	}

	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		//Обхожда корените
		if (openedPost->comments[i].id == id) {
			saveReply(id, openedPost->comments[i]);
			return;
		}
		else {
			if (searchComment(id, openedPost->comments[i]))
				return;
		}
	}
	std::cout << "Non-existent comment" << std::endl;
}

void SocialNetwork::upvote(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot upvote" << std::endl;
		return;
	}
	for (size_t i = 0; i < openedPost->comments.getSize(); i++)
	{
		//Обхожда корените
		if (openedPost->comments[i].id == id) {
			upvoteLogic(id, openedPost->comments[i]);
			return;
		}
		else if (openedPost->comments[i].replies.getSize() > 0) {
			if (searchCommentAndUpvote(id, openedPost->comments[i]))
				return;
		}
	}
	std::cout << "Non-existent comment" << std::endl;

}

void SocialNetwork::downvote(unsigned id) {
	if (loggedUser == nullptr || openedTopic == nullptr || openedPost == nullptr) {
		std::cout << "Cannot upvote" << std::endl;
		return;
	}
	//Обхожда корените
	for (size_t i = 0; i < openedPost->getComments().getSize(); i++)
	{
		if (openedPost->comments[i].replies[i].id == id) {
			downvoteLogic(id, openedPost->comments[i].replies[i]);
			return;
		}
		else if (openedPost->comments[i].replies.getSize() > 0) {
			if (searchCommentAndDownvote(id, openedPost->comments[i]))
				return;
		}
	}
	std::cout << "Non-existent comment"<<std::endl;
}

void SocialNetwork::list() {
	if (loggedUser == nullptr || openedTopic == nullptr) {
		std::cout << "Cannot acces posts" << std::endl;
		return;
	}
	unsigned numberOfPosts = openedTopic->getPosts().getSize();
	for (size_t i = 0; i < numberOfPosts; i++)
	{
		std::cout << openedTopic->posts[i];
	}
}

void SocialNetwork::p_quit() {
	if (openedTopic == nullptr || loggedUser == nullptr || openedPost == nullptr) {
		std::cout << "Cannot post quit" << std::endl;
		return;
	}
	std::cout << "You just left " << openedPost->heading << std::endl;
	openedPost = nullptr;
}

void SocialNetwork::quit() {
	if (openedTopic == nullptr || loggedUser == nullptr) {
		std::cout << "Cannot quit" << std::endl;
		return;
	}
	std::cout << "You just left topic " << openedTopic->heading << std::endl;
	openedTopic = nullptr;
	openedPost = nullptr;
}

void SocialNetwork::whoami() {
	if (loggedUser == nullptr) {
		std::cout << "No logged user" << std::endl;
		return;
	}
	std::cout << *(loggedUser);
}

void SocialNetwork::about(unsigned id) {

	int topicId = binarySearchInVector(topics,id);
	if (topicId == -1 || loggedUser == nullptr) {
		std::cout << "Cannot access or non-existent" << std::endl;
		return;
	}
	std::cout << topics[topicId];
}
