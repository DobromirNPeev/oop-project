#include "Post.h"

Post::Post() :Post("", "") {};
Post::Post(const char* heading, const char* description) :heading(heading), description(description), id(id++) {};