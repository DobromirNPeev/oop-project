#pragma once
#include "MyString.h"

class Post
{
	MyString heading;
	MyString description;
	unsigned id=0;
public:
	Post();
	Post(const char* heading, const char* description);
};

