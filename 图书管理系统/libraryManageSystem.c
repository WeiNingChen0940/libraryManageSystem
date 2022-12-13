#include "libraryManageSystem.h"
//
//typedef struct BOOKS_DATA
//{
//    struct BOOKS_DATA *link;
//    char *bookName;
//    int prize;
//}Books_data;
//Books_data *rootp = NULL;
//��¼����
int SignUp(const char *userAccount, const char *userPassword)
{
    printf("**********************\n");
    printf("*****ͼ�����ϵͳ*****\n");
    printf("***** 1.��¼ϵͳ *****\n");
    printf("***** 2.�˳�ϵͳ *****\n");
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
            printf("ϵͳ���˳�\n");
            isBreak = 1;
            break;
        default:
            printf("������ַ���Ч�����������룺\n");
            break;
        }
        if(isBreak)break;
    }

    return 0;
}
//�˺�������棬�ɹ���¼����1�����򷵻�0
int AccountPassword(const char *userAccount, const char *userPassword)
{
    int isSuccessful = 0;
    system("cls");
    printf("����������˺ţ�");
    char account[21] = { 0 };
    scanf_s("%s", account, 20);
    printf("�������˺����룺");
    char password[21] = { 0 };
    scanf_s("%s", password, 20);
    //�˺����붼��ȷ
    if(strcmp(account, userAccount) == 0 && strcmp(password, userPassword) == 0)
    {
        isSuccessful = 1;

    }
    else if(strcmp(account, userAccount) == 0)//�˺���ȷ���������
    {
        isSuccessful = password_retry(userPassword);
    }
    else if(strcmp(password, userPassword) == 0)//�˺Ŵ���������ȷ
    {
        isSuccessful = account_retry(userAccount);
    }
    else//�˺ź����붼����
    {
        account_retry(userAccount);
        isSuccessful = password_retry(userPassword);
    }
    return isSuccessful;
}
//���������˺ţ�������������ƣ��ɹ��򷵻�1
int account_retry(const char *userAccount)
{
    char account[21] = { 0 };
    do
    {
        printf("�˺Ų����ڣ����������룺");
        scanf_s("%s", account, 20);
    } while(strcmp(userAccount, account) != 0);
    return 1;
}
//�����������룬��������3�λ��˳�������0��������ȷ�򷵻�1
int password_retry(const char *userPassword)
{
    int isExit = 0;
    char password[21] = { 0 };
    do
    {
        isExit++;
        if(isExit > 3)
        {
            printf("����������̫�࣬ϵͳ��ǿ���˳�!\n");
            return 0;
        }
        printf("�����������������:(�㻹��%d���������)\n", 4 - isExit);
        scanf_s("%s", password, 20);

    } while(strcmp(password, userPassword) != 0);
    return 1;
}

//�ָ��ַ������ܣ�����һ���ַ���origin���ָ��ʶ�ַ���sep�ͽ���ַ�������result���ָ������Ľ���ᴢ����result�С��������ؽ���ַ�������Ŀ
int split(char origin[], char sep[], char(*result)[201])
{
    int sepLenth = strlen(sep);
    int originLenth = strlen(origin);
    char *sepLocation = origin;
    char *p2Origin = origin;
    int resultLenth = 0;
    //�Ѻ��еķָ������Ϊ\0
    while((sepLocation = strstr(sepLocation, sep)) != 0)
    {
        memset(sepLocation, '\0', sepLenth);
        sepLocation += sepLenth;
    }
    while(p2Origin < origin + originLenth)
    {
        while(*(p2Origin) == '\0')//��ָ���ƶ�����Ϊ\0��λ��
        {
            p2Origin++;
            if(p2Origin >= origin + originLenth)break;
        }
        //�����ַ������������ԣ�strcpy���p2Origin��ʼ���Ƶ�result�У�һֱ���Ƶ���һ��\0Ҳ������һ���ָ����λ��
        strcpy(result[resultLenth++], p2Origin);
        while(*(p2Origin) != '\0')//��ָ���ƶ�����һ��\0Ҳ������һ���ָ����λ��
        {
            p2Origin++;
            if(p2Origin >= origin + originLenth)break;
        }
    }
    return resultLenth;//����result�ַ�����������ճ��ȣ�Ҳ���Ƿָ���ַ�������Ŀ
}

//��������ÿ�δ�������ݻ�������ĩβ���룬�ɹ������򷵻�1��ʧ���򷵻�0
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

        //��������ֱ��ĩβ
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
//���������д����ĳ���ڵ�����ݣ�����Ҫ������ͬ�������жϣ����ɹ��򷵻�1��ʧ���򷵻�0
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
//ɾ������ڵ㣬�ɹ��򷵻�1��ʧ���򷵻�0
int linkedList_delete(Books_data **linkp, char *bookName)
{
    Books_data *current = NULL;
    while((current = *linkp) != NULL && strcmp(current->bookName, bookName) != 0)
        linkp = &(current->link);
    if(strcmp(current->bookName, bookName) == 0)
    {
        *linkp = current->link;
        //printf("�鼮 %s ɾ�����\n", bookName);
        free(current->bookName);
        free(current);
        return 1;
    }
    else
    {
        return 0;
    }
}
//ɾ����*linkp��ָ�������������нڵ㣬����ɾ���Ľڵ������i
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
//�½�һ���飬�����½��Ľṹ���ָ�룬�½�ʧ���򷵻ؿ�ָ��
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

