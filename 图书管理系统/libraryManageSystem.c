#include "libraryManageSystem.h"
static int AccountPassword(const char *userAccount, const char *userPassword);
static int account_retry(const char *userAccount);
static int password_retry(const char *userPassword);
static int Menu_UsersManage(Users_data **linkp);
static int Menu_UsersManage_ShowAllUsers(Users_data *linkp ,int isPause);
static int Menu_BooksManage(Books_data **linkp);
static int Menu_BooksManage_ShowAllBooks(Books_data *linkp, int isPause);
static int Menu_Shopping(Users_data **uLinkp, Books_data **bLinkp);
//��¼����
int SignUp(const char *userAccount, const char *userPassword)
{
    printf("**********************\n");
    printf("*    ͼ�����ϵͳ    *\n");
    printf("*     1.��¼ϵͳ     *\n");
    printf("*     2.�˳�ϵͳ     *\n");
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
            //printf("������ַ���Ч�����������룺\n");
            break;
        }
        if(isBreak)break;
    }

    return 0;
}
//�˺�������棬�ɹ���¼����1�����򷵻�0
static int AccountPassword(const char *userAccount, const char *userPassword)
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
    system("cls");
    return isSuccessful;
}
//���������˺ţ�������������ƣ��ɹ��򷵻�1
static int account_retry(const char *userAccount)
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
static int password_retry(const char *userPassword)
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

//�˵�����

int Menu_Main(Users_data **uLinkp, Books_data **bLinkp)
{
    //while(getchar() != '\n');
    char key = 0;
    while((key = getchar()) != 0)
    {
        system("cls");
        printf("**********************\n");
        printf("*    ͼ�����ϵͳ    *\n");
        printf("*     1.��Ա����     *\n");
        printf("*     2.�鼮����     *\n");
        printf("*     3.�������     *\n");
        printf("*     4.ע��ϵͳ     *\n");
        printf("**********************\n");
        switch(key)
        {
        case '1':
            Menu_UsersManage(uLinkp);
            break;
        case '2':
            Menu_BooksManage(bLinkp);
            break;

        case '3':
            Menu_Shopping(uLinkp, bLinkp);
            break;

        case '4':
            return 1;
            break;
        default:
            //printf("������Ч�����������룺");
            ;
        }


    }
    return 0;
}

//��Ա����
static int Menu_UsersManage(Users_data **linkp)
{
    char key = 0;
    while((key = getchar()) != EOF)
    {
        system("cls");
        printf("**********************\n");
        printf("*      ��Ա����      *\n");
        printf("*   1.��ʾ���л�Ա   *\n");
        printf("*   2.��ӻ�Ա��Ϣ   *\n");
        printf("*   3.�޸Ļ�Ա��Ϣ   *\n");
        printf("*    4.�������˵�    *\n");
        printf("**********************\n");
        switch(key)
        {
        case '1':
            system("cls");
            Menu_UsersManage_ShowAllUsers(*linkp, 1);
            break;
        case '2':
        {
            system("cls");
            printf("�������»�Ա�����֣�");
            char userName[MAX_NAME_LEN] = { 0 };
            scanf("%s", userName);
            printf("������û�Ա�ĳ�ʼ���֣�");
            float credit = 0;
            scanf("%f", &credit);
            if(user_insert(linkp, userName, credit) != 0)
                printf("��ӳɹ���\n");
            else
                printf("���ʧ�ܣ�\n");
            //Sleep(1000);
            printf("\n���������ַ��Է��أ�");
            scanf("%s", userName);
            break;
        }
        case '3':
        {
            system("cls");
            printf("�������Ա�ţ�");
            int number = 0;
            scanf("%d", &number);
            printf("������û�Ա�µ����֣�");
            char userName[MAX_NAME_LEN] = { 0 };
            scanf("%s", userName);
            printf("������Ҫ�޸ĵĻ��֣�");
            float credit = 0;
            scanf("%f", &credit);
            Users_data *l = *linkp;
            for(int i = 1; i < number; i++)
                l = l->link;
            if(user_change(l, l->userName, userName, credit) != 0)
                printf("�޸ĳɹ���\n");
            else
                printf("�޸�ʧ�ܣ�\n");
            //Sleep(1000);
            printf("\n���������ַ��Է��أ�");
            scanf("%s", userName);
            break;
        }
        case '4':

            return 1;
            break;
        default:
            //getchar();
            //printf("������Ч�����������룺");

            ;
        }
    }
    return 0;
}


static int Menu_UsersManage_ShowAllUsers(Users_data *linkp, int isPause)
{
    //while(getchar() != '\n');
    //system("cls");
    printf("��ţ�\t������\t���֣�\n");
    int i = 1;
    while(linkp != NULL)
    {
        printf("%d\t%s\t%.2f\n", i++, linkp->userName, linkp->credit);
        linkp = linkp->link;
    }
    if(isPause != 0)
    {
        printf("\n����1�Է��أ�");
        getchar();
    }
    return 0;
}

static int Menu_BooksManage(Books_data **linkp)
{
    char key = 0;
    while((key = getchar()) != EOF)
    {
        system("cls");
        printf("**********************\n");
        printf("*      �鼮����      *\n");
        printf("*   1.��ʾ�����鼮   *\n");
        printf("*     2.����鼮     *\n");
        printf("*     3.�޸ļ۸�     *\n");
        printf("*     4.ɾ���鼮     *\n");
        printf("*    5.�������˵�    *\n");
        printf("**********************\n");
        switch(key)
        {
        case '1':
            system("cls");
            Menu_BooksManage_ShowAllBooks(*linkp, 1);
            break;
        case '2':
        {
            system("cls");
            printf("��������������֣�");
            char bookName[MAX_NAME_LEN] = { 0 };
            scanf("%s", bookName);
            printf("���������ļ۸�");
            float prize = 0;
            scanf("%f", &prize);
            if(book_insert(linkp, bookName, prize) != 0)
                printf("��ӳɹ���\n");
            else
                printf("���ʧ�ܣ��۸���Ϊ��������\n");
            //Sleep(1000);
            printf("\n���������ַ��Է��أ�");
            scanf("%s", bookName);
            break;
        }
        case '3':
        {
            system("cls");
            printf("������������");
            char bookName[MAX_NAME_LEN] = { 0 };
            scanf("%s", bookName);
            printf("�������޸ĺ�ļ۸�");
            float prize = 0;
            scanf("%f", &prize);
            Books_data *l = *linkp;
            if(book_change(l, bookName, prize) != 0)
                printf("�޸ĳɹ���\n");
            else
                printf("�޸�ʧ�ܣ�\n");
            //Sleep(1000);
            printf("\n���������ַ��Է��أ�");
            scanf("%s", bookName);
            break;
        }
        case '4':
            system("cls");
            printf("������������");
            char bookName[MAX_NAME_LEN] = { 0 };
            scanf("%s", bookName);
            //Books_data *l = linkp;
            if(book_delete(linkp, bookName) != 0)
                printf("ɾ���ɹ���\n");
            else
                printf("ɾ��ʧ�ܣ��Ҳ���Ҫɾ�����鼮\n");
            //Sleep(1000);
            printf("\n���������ַ��Է��أ�");
            scanf("%s", bookName);

            break;
        case '5':
            return 1;
            break;
        default:
            //getchar();
            //printf("������Ч�����������룺");

            ;
        }
    }
    return 0;
}

static int Menu_BooksManage_ShowAllBooks(Books_data *linkp, int isPause)
{
    //while(getchar() != '\n');
    //system("cls");
    printf("��ţ�\t������\t�۸�\n");
    int i = 1;
    while(linkp != NULL)
    {
        printf("%d\t%s\t%.2f\n", i++, linkp->bookName, linkp->prize);
        linkp = linkp->link;
    }
    if(isPause != 0)
    {
        printf("\n����1�Է��أ�");
        getchar();
    }

    return 0;
}

static int Menu_Shopping(Users_data **uLinkp, Books_data **bLinkp)
{
    Users_data *l = NULL;
    system("cls");
    Menu_UsersManage_ShowAllUsers(*uLinkp, 0);
    Menu_BooksManage_ShowAllBooks(*bLinkp, 0);
    printf("�������Ա��ţ�");
    int number = 0;

    scanf("%d", &number);
    float credit = user_getLinkByNumber(*uLinkp, number)->credit;
    if((l = user_getLinkByNumber(*uLinkp, number)) != NULL)
    {
        char isContinue = 'y';
        while(isContinue != 'n')
        {
            printf("������Ҫ������鼮��ţ�");
            int n = 0, m = 0;
            scanf("%d", &n);
            printf("������Ҫ����ı�����");
            scanf("%d", &m);
            float prize = 0;
            if((prize = book_getLinkByNumber(*bLinkp, n)->prize) > 0)
            {
                credit -= prize * m;
                user_getLinkByNumber(*uLinkp, n)->credit = credit;
            }
            else
            {
                printf("�Ҳ������鼮�����������룡\n");
                continue;
            }
            printf("��Ҫ������鼮�ǡ�%s��������Ϊ%.2fԪ���ܹ�%d�����ܼ�Ϊ%.2fԪ\n", book_getLinkByNumber(*bLinkp, n)->bookName, prize, m, prize * m);
            printf("����y�������飬����n�������");
            scanf("%c", &isContinue);
            scanf("%c", &isContinue);
        }
        return 1;
    }
    else
        return 0;
}

//����Ϊ�鼮��Ϣ��������

//��������ÿ�δ�������ݻ�������ĩβ���룬�ɹ������򷵻�1��ʧ���򷵻�0
int book_insert(Books_data **linkp, char *new_bookName, float prize)
{
    if(prize <= 0)return 0;
    Books_data *book = (Books_data *)malloc(sizeof(Books_data));
    Books_data *current = *linkp;
    if(book != NULL)
    {
        //��������ֱ��ĩβ
        while((current = *linkp) != NULL)
            linkp = &(current->link);
        //*linkp = &book->link;
        *linkp = book;
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
int book_change(Books_data *linkp, char *bookName, float new_prize)
{
    if(new_prize <= 0)return 0;
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
int book_delete(Books_data **linkp, char *bookName)
{
    Books_data *current = NULL;
    while((current = *linkp) != NULL && strcmp(current->bookName, bookName) != 0)
        linkp = &(current->link);
    if(current != NULL && strcmp(current->bookName, bookName) == 0)
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
int book_delete_all(Books_data **linkp)
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
        book_delete(linkp, current->bookName);
        i++;
    }
    return i;
}


//����������Ӧ�鼮�ļ۸���û���ҵ����鼮�򷵻�-1
float book_getPrizeByName(Books_data *linkp, const char *bookName)
{
    while(linkp != NULL && strcmp(linkp->bookName, bookName) != 0)
    {
        linkp = linkp->link;
    }
    if(linkp != NULL && strcmp(linkp->bookName, bookName) == 0)
        return linkp->prize;
    else
        return -1;
}
//���ظ�����˵��û�ҵ��鼮
//float book_getPrizeByNumber(Books_data *linkp, int number)
//{
//    int i = 1;
//    if(linkp != NULL)
//        for(; i < number; i++)
//        {
//            if(linkp->link != NULL)
//            {
//                linkp = linkp->link;
//            }
//        }
//    if(i != number)
//        return -1;
//    else if(linkp != NULL)
//        return linkp->prize;
//    else
//        return -2;
//}

Books_data *book_getLinkByNumber(Books_data *linkp, int number)
{
    int i = 1;
    if(linkp != NULL)
        for(; i < number; i++)
        {
            if(linkp->link != NULL)
            {
                linkp = linkp->link;
            }
        }
    if(i != number)
        return 0;
    else
        return linkp;
}

//����Ϊ��Ա��Ϣ�Ĳ�������

//��������ÿ�δ�������ݻ�������ĩβ���룬�ɹ������򷵻�1��ʧ���򷵻�0
int user_insert(Users_data **linkp, char *new_userName, float credit)
{
    Users_data *user = (Users_data *)malloc(sizeof(Users_data));
    Users_data *current = *linkp;
    if(user != NULL)
    {
        //��������ֱ��ĩβ
        while((current = *linkp) != NULL)
            linkp = &(current->link);
        //*linkp = &user->link;
        *linkp = user;
        user->link = current;
        user->userName = (char *)calloc((strlen(new_userName) + 1) * sizeof(char), 1);
        if(user->userName != NULL)
            strcpy(user->userName, new_userName);
        else
            return 0;
        user->credit = credit;

        return 1;
    }
    else
    {
        return 0;
    }
}
//���������д����ĳ���ڵ�����ݣ�����Ҫ������ͬ�������жϣ����ɹ��򷵻�1��ʧ���򷵻�0
int user_change(Users_data *linkp, char *userName, char *new_userName, float new_credit)
{
    while(linkp != NULL && strcmp(linkp->userName, userName) != 0)
        linkp = linkp->link;
    if(linkp == NULL)
    {
        return 0;
    }
    else
    {
        free(linkp->userName);
        linkp->userName = (char *)calloc((strlen(new_userName) + 1) * sizeof(char), 1);
        if(linkp->userName != NULL)
            strcpy(linkp->userName, new_userName);
        else
            return 0;
        linkp->credit = new_credit;
        return 1;
    }

}
//ɾ������ڵ㣬�ɹ��򷵻�1��ʧ���򷵻�0
int user_delete(Users_data **linkp, char *userName)
{
    Users_data *current = NULL;
    while((current = *linkp) != NULL && strcmp(current->userName, userName) != 0)
        linkp = &(current->link);
    if(current != NULL && strcmp(current->userName, userName) == 0)
    {
        *linkp = current->link;
        //printf("��Ա %s ��Ϣɾ�����\n", userName);
        free(current->userName);
        free(current);
        return 1;
    }
    else
    {
        return 0;
    }
}
//ɾ����*linkp��ָ�������������нڵ㣬����ɾ���Ľڵ������i
int user_delete_all(Users_data **linkp)
{
    Users_data *current = *linkp;
    Users_data **rootp = linkp;
    int i = 0;
    while(*rootp != NULL)
    {
        current = *rootp;
        linkp = rootp;
        while((current = *linkp)->link != NULL)
            linkp = &current->link;
        user_delete(linkp, current->userName);
        i++;
    }
    return i;
}

Users_data *user_getLinkByNumber(Users_data *linkp, int number)
{
    int i = 1;
    if(linkp != NULL)
        for(; i < number; i++)
        {
            if(linkp->link != NULL)
            {
                linkp = linkp->link;
            }
        }
    if(i != number)
        return 0;
    else
        return linkp;
}

//�������ݣ�sort�뿴ͷ�ļ������enum��path����Ϊ�գ���""��rootpΪ�����ָ��ĵ�ַ
int data_save(char *path_noName, int sort, void *rootp)
{
    char *path_withName = (char *)calloc((strlen(path_noName) + 10) * sizeof(char), 1);
    if(path_withName != NULL)
        strcpy(path_withName, path_noName);
    FILE *f = NULL;
    switch(sort)
    {
    case BOOKS:
    {
        Books_data *linkp = (Books_data *)rootp;
        //�ϳ��������ļ�·��
        if(path_withName != NULL)
        {
            strcat(path_withName, "books.txt");
            f = fopen(path_withName, "w");
        }
        while(linkp != NULL)
        {
            if(f != NULL)fprintf(f, "name : %s\nprize : %.2f\n", linkp->bookName, linkp->prize);
            linkp = linkp->link;
        }

        break;
    }
    case USERS:
    {
        Users_data *linkp = (Users_data *)rootp;
        //�ϳ��������ļ�·��
        if(path_withName != NULL)
        {
            strcat(path_withName, "users.txt");
            f = fopen(path_withName, "w");
        }
        while(linkp != NULL)
        {
            if(f != NULL)fprintf(f, "name : %s\ncredit : %.2f\n", linkp->userName, linkp->credit);
            linkp = linkp->link;
        }        break;
    }
    default:
        if(f != NULL)fclose(f);
        return 0;
    }
    if(f != NULL)fclose(f);
    return 1;
}

//��ȡ���ݣ���������뿴data_save��ע��
int data_load(char *path_noName, int sort, void **rootp)
{
    char *path_withName = (char *)calloc((strlen(path_noName) + 10) * sizeof(char), 1);
    if(path_withName != NULL)
        strcpy(path_withName, path_noName);

    FILE *f = NULL;
    switch(sort)
    {
    case BOOKS:
    {
        char bookName[MAX_NAME_LEN] = { 0 };
        float prize = 0;
        //�ϳ��������ļ�·��
        if(path_withName != NULL)
        {
            strcat(path_withName, "books.txt");
            f = fopen(path_withName, "r");
        }
        if(f != NULL)
            while(fscanf(f, "name : %s\nprize : %f\n", bookName, &prize) != EOF)
            {
                book_insert((Books_data **)rootp, bookName, prize);
            }

        break;
    }
    case USERS:
    {
        char userName[MAX_NAME_LEN] = { 0 };
        float credit = 0;
        //�ϳ��������ļ�·��
        if(path_withName != NULL)
        {
            strcat(path_withName, "users.txt");
            f = fopen(path_withName, "r");
        }
        if(f != NULL)
            while(fscanf(f, "name : %s\ncredit : %f\n", userName, &credit) != EOF)
            {
                user_insert((Users_data **)rootp, userName, credit);
            }

        break;
    }
    default:
        return 0;
    }


    if(f != NULL)fclose(f);
    return 1;

}