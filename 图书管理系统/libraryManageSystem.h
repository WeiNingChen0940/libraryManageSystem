#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define NULL ((void*)0)

typedef struct BOOKS_DATA
{
    struct BOOKS_DATA *link;
    char *bookName;
    int prize;
}Books_data;
//Books_data *rootp = NULL;

int SignUp(const char *userAccount, const char *userPassword);
int AccountPassword(const char *userAccount, const char *userPassword);
int account_retry(const char *userAccount);
int password_retry(const char *userPassword);
int split(char origin[], char sep[], char(*result)[201]);
int linkedList_insert(Books_data **linkp, char *new_bookName, int prize);
int linkedList_change(Books_data *linkp, char *bookName, int new_prize);
int linkedList_delete(Books_data **linkp, char *bookName);
int linkedList_delete_all(Books_data **linkp);
//Books_data *book_new(char *bookName, int prize);