#pragma once
#include "MyString.h"

static const char* OFFSET = "   ";

//commands
static const MyString SIGNUP = "signup";
static const MyString LOGIN = "login";
static const MyString LOGOUT = "logout";
static const MyString SEARCH = "search";
static const MyString CREATE = "create";
static const MyString OPEN = "open";
static const MyString P_OPEN = "p_open";
static const MyString POST = "post";
static const MyString COMMENT = "comment";
static const MyString COMMENTS = "comments";
static const MyString REPLY = "reply";
static const MyString UPVOTE = "upvote";
static const MyString DOWNVOTE = "downvote";
static const MyString LIST = "list";
static const MyString P_QUIT = "p_quit";
static const MyString QUIT = "quit";
static const MyString WHOAMI = "whoami";
static const MyString ABOUT = "about";
static const MyString EXIT = "exit";

//instructions
static const char* BORDER_UPPER =		  "/------------------------------------------------------------------------------------------\\";
static const char* WELCOME_MESSAGE =      "| Welcome to the Social Network.It works like a regular social network.                    |";
static const char* COMMAND_LIST_MESSAGE = "| Here is the list of commands you can use:                                                |";
static const char* INSTRUCTION_SIGNUP =   "| 1) signup - create an user                                                               |";
static const char* INSTRUCTION_LOGIN  =   "| 2) login - expects a first name and a password and if they are correct the user logs in  |";
static const char* INSTRUCTION_CREATE =   "| 3) create - you can create your own topic                                                |";
static const char* INSTRUCTION_SEARCH =   "| 4) search - you enter a keyword and it shows all the topics that have it                 |";
static const char* INSTRUCTION_OPEN =     "| 5) open - you enter an id or keyword and it opens the desired topic                      |";
static const char* INSTRUCTION_LIST =     "| 6) list - you can see all the posts on the opened topic                                  |";
static const char* INSTRUCTION_POST =     "| 7) post - you can create a post in the opened topic                                      |";
static const char* INSTRUCTION_P_OPEN =   "| 8) p_open - you enter an id or keyword and it opens the desired post in the opened topic |";
static const char* INSTRUCTION_COMMENT =  "| 9) comment - you can add a comment to the opened post                                    |";
static const char* INSTRUCTION_COMMENTS = "| 10) comments - it shows you all the comments under the opened post                       |";
static const char* INSTRUCTION_REPLY =    "| 11) reply - you enter an id of a comment and can reply to it in the opened post          |";
static const char* INSTRUCTION_UPVOTE =   "| 12) upvote - add upvote reaction to a comment                                            |";
static const char* INSTRUCTION_DOWNVOTE = "| 13) downvote - add downvote reaction to a comment                                        |";
static const char* INSTRUCTION_P_QUIT =   "| 14) p_quit - exit post                                                                   |";
static const char* INSTRUCTION_QUIT =     "| 15) quit - exit topic                                                                    |";
static const char* INSTRUCTION_WHOAMI =   "| 16) whoami - shows info about the user                                                   |";
static const char* INSTRUCTION_ABOUT =    "| 17) about - shows info about a certain topic                                             |";
static const char* BORDER_LOWER =         "\\------------------------------------------------------------------------------------------/";

//error message
static const char* INVALID_COMMAND = "Invalid command";
static const char* USER_NOT_EXISTS = "Incorrect, please try again";
static const char* TOPIC_NOT_EXISTS = "No such topic";
static const char* POST_NOT_EXISTS = "No such post";
static const char* COMMENT_NOT_EXISTS = "No such post";
static const char* ERROR = "Error, something went wrong";
static const char* FILE_READ_ERROR = "Unable to open file";
static const char* FILE_WRITE_ERROR = "Unable to open file";
static const char* NO_POSTS = "No posts";
static const char* NO_COMMENTS = "No comments";


//interface messages
static const char* USER_EXISTS = "User already exists";
static const char* ENTER_KEYWORD = "Enter keyword: ";
static const char* ENTER_ID_OR_NAME = "Enter id or name: ";
static const char* ENTER_TITLE = "Enter Topic title:";
static const char* ENTER_DESC = "Enter Description:";
static const char* ENTER_ID = "Enter id: ";
static const char* TYPE_FIRST_NAME = "Enter First Name:";
static const char* TYPE_LAST_NAME = "Enter Last Name:";
static const char* TYPE_PASSWORD = "Enter password:";
static const char* WELCOME_USER = "Welcome, ";
static const char* WELCOME_TOPIC = "Welcome to ";
static const char* LOGOUT_MESSAGE = "Goodbye, ";
static const char* TOPIC_QUIT_MESSAGE = "You just left topic ";
static const char* POST_QUIT_MESSAGE = "You just left post ";
static const char* ID_PRINTING = "{id: ";
static const char* SAY_SOMETHING = "Say something: ";
static const char* POSTING = "Posted";
static const char* UPVOTE_PRINT = " {upvote:";
static const char* DOWNVOTE_PRINT = " {downvote:";
static const char* NAME_PRINT = ">>Name:";
static const char* DESC_PRINT = ">>Description:";
static const char* CREATOR_PRINT = ">>Created by:";
static const char* NUMOFQUESTIONS_PRINT = ">>Question asked:";
static const char* SUCCESS = "Succes!";
