#include "libraryManageSystem.h"
//
//typedef struct BOOKS_DATA
//{
//    struct BOOKS_DATA *link;
//    char *bookName;
//    int prize;
//}Books_data;
//Books_data *rootp = NULL;
//登录界面
int SignUp(const char *userAccount, const char *userPassword)
{
    printf("**********************\n");
    printf("*****图书管理系统*****\n");
    printf("***** 1.登录系统 *****\n");
    printf("***** 2.退出系统 *****\n");
    printf("**********************\n");
    char key = 0;
    char isBreak = 0;
    while((key = getchar()) != EOF)
    {
        switch(key)
        {
        case '1':
            return AccountPassword(userAccount, userPassword);
            isBreak = 1;
            break;
        case '2':
            printf("系统已退出\n");
            isBreak = 1;
            break;
        default:
            printf("输入的字符无效！请重新输入：\n");
            break;
        }
        if(isBreak)break;
    }

    return 0;
}
//账号输入界面，成功登录返回1，否则返回0
int AccountPassword(const char *userAccount, const char *userPassword)
{
    int isSuccessful = 0;
    system("cls");
    printf("请输入你的账号：");
    char account[21] = { 0 };
    scanf_s("%s", account, 20);
    printf("请输入账号密码：");
    char password[21] = { 0 };
    scanf_s("%s", password, 20);
    //账号密码都正确
    if(strcmp(account, userAccount) == 0 && strcmp(password, userPassword) == 0)
    {
        isSuccessful = 1;

    }
    else if(strcmp(account, userAccount) == 0)//账号正确，密码错误
    {
        isSuccessful = password_retry(userPassword);
    }
    else if(strcmp(password, userPassword) == 0)//账号错误，密码正确
    {
        isSuccessful = account_retry(userAccount);
    }
    else//账号和密码都错误
    {
        account_retry(userAccount);
        isSuccessful = password_retry(userPassword);
    }
    return isSuccessful;
}
//单独输入账号，无输入次数限制，成功则返回1
int account_retry(const char *userAccount)
{
    char account[21] = { 0 };
    do
    {
        printf("账号不存在，请重新输入：");
        scanf_s("%s", account, 20);
    } while(strcmp(userAccount, account) != 0);
    return 1;
}
//单独输入密码，输入错误达3次会退出，返回0，密码正确则返回1
int password_retry(const char *userPassword)
{
    int isExit = 0;
    char password[21] = { 0 };
    do
    {
        isExit++;
        if(isExit > 3)
        {
            printf("密码错误次数太多，系统已强制退出!\n");
            return 0;
        }
        printf("密码错误！请重新输入:(你还有%d次输入机会)\n", 4 - isExit);
        scanf_s("%s", password, 20);

    } while(strcmp(password, userPassword) != 0);
    return 1;
}

//分割字符串功能：传入一个字符串origin、分割标识字符串sep和结果字符串数组result，分割完整的结果会储存在result中。函数返回结果字符串的数目
int split(char origin[], char sep[], char(*result)[201])
{
    int sepLenth = strlen(sep);
    int originLenth = strlen(origin);
    char *sepLocation = origin;
    char *p2Origin = origin;
    int resultLenth = 0;
    //把含有的分割符都变为\0
    while((sepLocation = strstr(sepLocation, sep)) != 0)
    {
        memset(sepLocation, '\0', sepLenth);
        sepLocation += sepLenth;
    }
    while(p2Origin < origin + originLenth)
    {
        while(*(p2Origin) == '\0')//把指针移动到不为\0的位置
        {
            p2Origin++;
            if(p2Origin >= origin + originLenth)break;
        }
        //利用字符串函数的特性，strcpy会从p2Origin开始复制到result中，一直复制到下一个\0也就是下一个分割符的位置
        strcpy(result[resultLenth++], p2Origin);
        while(*(p2Origin) != '\0')//把指针移动到下一个\0也就是下一个分割符的位置
        {
            p2Origin++;
            if(p2Origin >= origin + originLenth)break;
        }
    }
    return resultLenth;//返回result字符串数组的最终长度，也就是分割后字符串的数目
}

//插入链表，每次传入的数据会在链表末尾插入，成功插入则返回1，失败则返回0
int linkedList_insert(Books_data **linkp, char *new_bookName, int prize)
{
    Books_data *book = (Books_data *)malloc(sizeof(Books_data));
    Books_data *current = *linkp;
    if(book != NULL)
    {
        /*while((current = *linkp) != NULL && new_value > current->index)
        {
            linkp = &(current->link);
        }
        *linkp = &book->link;
        book->link = current;
        book->index = new_value;*/

        //遍历链表直到末尾
        while((current = *linkp) != NULL)
            linkp = &(current->link);
        *linkp = &book->link;
        book->link = current;
        book->bookName = (char *)calloc((strlen(new_bookName) + 1) * sizeof(char), 1);
        if(book->bookName != NULL)
            strcpy(book->bookName, new_bookName);
        else
            return 0;
        book->prize = prize;

        return 1;
    }
    else
    {
        return 0;
    }
}
//更改链表中储存的某个节点的数据（后续要加上相同书名的判断），成功则返回1，失败则返回0
int linkedList_change(Books_data *linkp, char *bookName, int new_prize)
{
    while(linkp != NULL && strcmp(linkp->bookName, bookName) != 0)
        linkp = linkp->link;
    if(linkp == NULL)
    {
        return 0;
    }
    else
    {
        linkp->prize = new_prize;
        return 1;
    }

}
//删除链表节点，成功则返回1，失败则返回0
int linkedList_delete(Books_data **linkp, char *bookName)
{
    Books_data *current = NULL;
    while((current = *linkp) != NULL && strcmp(current->bookName, bookName) != 0)
        linkp = &(current->link);
    if(strcmp(current->bookName, bookName) == 0)
    {
        *linkp = current->link;
        //printf("书籍 %s 删除完毕\n", bookName);
        free(current->bookName);
        free(current);
        return 1;
    }
    else
    {
        return 0;
    }
}
//删除从*linkp所指向的链表后面所有节点，返回删除的节点个数：i
int linkedList_delete_all(Books_data **linkp)
{
    Books_data *current = *linkp;
    Books_data **rootp = linkp;
    int i = 0;
    while(*rootp != NULL)
    {
        current = *rootp;
        linkp = rootp;
        while((current = *linkp)->link != NULL)
            linkp = &current->link;
        linkedList_delete(linkp, current->bookName);
        i++;
    }
    return i;
}
//新建一本书，返回新建的结构体的指针，新建失败则返回空指针
//Books_data *book_new(char *bookName, int prize)
//{
//    Books_data *newBook = (Books_data *)malloc(sizeof(Books_data));
//    if(newBook != NULL)
//    {
//        newBook->bookName = bookName;
//        newBook->prize = prize;
//        return newBook;
//    }
//    else
//    {
//        return NULL;
//    }
//}

