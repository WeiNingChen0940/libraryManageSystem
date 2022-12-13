#pragma once
#pragma warning(disable:6031)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _CRT_SECURE_NO_WARNINGS
//#define NULL ((void*)0)
#define MAX_NAME_LEN 50
//文件类型
enum
{
    BOOKS = 1,
    USERS
};

typedef struct BOOKS_DATA
{
    struct BOOKS_DATA *link;
    char *bookName;
    float prize;
}Books_data;
typedef struct USERS_DATA
{
    struct USERS_DATA *link;
    char *userName;
    float credit;
}Users_data;

int SignUp(const char *userAccount, const char *userPassword);
int Menu_Main(Users_data *uLinkp, Books_data *bLinkp);

//int split(char origin[], char sep[], char(*result)[201]);

int book_insert(Books_data **linkp, char *new_bookName, float prize);
int book_change(Books_data *linkp, char *bookName, float new_prize);
int book_delete(Books_data **linkp, char *bookName);
int book_delete_all(Books_data **linkp);
float book_getPrizeByName(Books_data *linkp, const char *bookName);
Books_data *book_getLinkByNumber(Books_data *linkp, int number);

int user_insert(Users_data **linkp, char *new_userName, float credit);
int user_change(Users_data *linkp, char *userName, char *new_userName, float new_credit);
int user_delete(Users_data **linkp, char *userName);
int user_delete_all(Users_data **linkp);
Users_data *user_getLinkByNumber(Users_data *linkp, int number);

int data_save(char *path_noName, int sort, void *rootp);
int data_load(char *path_noName, int sort, void **rootp);