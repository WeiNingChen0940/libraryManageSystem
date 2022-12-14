#include "libraryManageSystem.h"
static int AccountPassword(const char *userAccount, const char *userPassword);
static int account_retry(const char *userAccount);
static int password_retry(const char *userPassword);
static int Menu_UsersManage(Users_data **linkp);
static int Menu_UsersManage_ShowAllUsers(Users_data *linkp ,int isPause);
static int Menu_BooksManage(Books_data **linkp);
static int Menu_BooksManage_ShowAllBooks(Books_data *linkp, int isPause);
static int Menu_Shopping(Users_data **uLinkp, Books_data **bLinkp);
//登录界面
int SignUp(const char *userAccount, const char *userPassword)
{
    printf("**********************\n");
    printf("*    图书管理系统    *\n");
    printf("*     1.登录系统     *\n");
    printf("*     2.退出系统     *\n");
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
            //printf("输入的字符无效！请重新输入：\n");
            break;
        }
        if(isBreak)break;
    }

    return 0;
}
//账号输入界面，成功登录返回1，否则返回0
static int AccountPassword(const char *userAccount, const char *userPassword)
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
    system("cls");
    return isSuccessful;
}
//单独输入账号，无输入次数限制，成功则返回1
static int account_retry(const char *userAccount)
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
static int password_retry(const char *userPassword)
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

//菜单构建

int Menu_Main(Users_data **uLinkp, Books_data **bLinkp)
{
    //while(getchar() != '\n');
    char key = 0;
    while((key = getchar()) != 0)
    {
        system("cls");
        printf("**********************\n");
        printf("*    图书管理系统    *\n");
        printf("*     1.会员管理     *\n");
        printf("*     2.书籍管理     *\n");
        printf("*     3.购物结算     *\n");
        printf("*     4.注销系统     *\n");
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
            //printf("输入无效！请重新输入：");
            ;
        }


    }
    return 0;
}

//会员管理
static int Menu_UsersManage(Users_data **linkp)
{
    char key = 0;
    while((key = getchar()) != EOF)
    {
        system("cls");
        printf("**********************\n");
        printf("*      会员管理      *\n");
        printf("*   1.显示所有会员   *\n");
        printf("*   2.添加会员信息   *\n");
        printf("*   3.修改会员信息   *\n");
        printf("*    4.返回主菜单    *\n");
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
            printf("请输入新会员的名字：");
            char userName[MAX_NAME_LEN] = { 0 };
            scanf("%s", userName);
            printf("请输入该会员的初始积分：");
            float credit = 0;
            scanf("%f", &credit);
            if(user_insert(linkp, userName, credit) != 0)
                printf("添加成功！\n");
            else
                printf("添加失败！\n");
            //Sleep(1000);
            printf("\n输入任意字符以返回：");
            scanf("%s", userName);
            break;
        }
        case '3':
        {
            system("cls");
            printf("请输入会员号：");
            int number = 0;
            scanf("%d", &number);
            printf("请输入该会员新的名字：");
            char userName[MAX_NAME_LEN] = { 0 };
            scanf("%s", userName);
            printf("请输入要修改的积分：");
            float credit = 0;
            scanf("%f", &credit);
            Users_data *l = *linkp;
            for(int i = 1; i < number; i++)
                l = l->link;
            if(user_change(l, l->userName, userName, credit) != 0)
                printf("修改成功！\n");
            else
                printf("修改失败！\n");
            //Sleep(1000);
            printf("\n输入任意字符以返回：");
            scanf("%s", userName);
            break;
        }
        case '4':

            return 1;
            break;
        default:
            //getchar();
            //printf("输入无效！请重新输入：");

            ;
        }
    }
    return 0;
}


static int Menu_UsersManage_ShowAllUsers(Users_data *linkp, int isPause)
{
    //while(getchar() != '\n');
    //system("cls");
    printf("序号：\t姓名：\t积分：\n");
    int i = 1;
    while(linkp != NULL)
    {
        printf("%d\t%s\t%.2f\n", i++, linkp->userName, linkp->credit);
        linkp = linkp->link;
    }
    if(isPause != 0)
    {
        printf("\n输入1以返回：");
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
        printf("*      书籍管理      *\n");
        printf("*   1.显示所有书籍   *\n");
        printf("*     2.添加书籍     *\n");
        printf("*     3.修改价格     *\n");
        printf("*     4.删除书籍     *\n");
        printf("*    5.返回主菜单    *\n");
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
            printf("请输入新书的名字：");
            char bookName[MAX_NAME_LEN] = { 0 };
            scanf("%s", bookName);
            printf("请输入该书的价格：");
            float prize = 0;
            scanf("%f", &prize);
            if(book_insert(linkp, bookName, prize) != 0)
                printf("添加成功！\n");
            else
                printf("添加失败！价格不能为非正数！\n");
            //Sleep(1000);
            printf("\n输入任意字符以返回：");
            scanf("%s", bookName);
            break;
        }
        case '3':
        {
            system("cls");
            printf("请输入书名：");
            char bookName[MAX_NAME_LEN] = { 0 };
            scanf("%s", bookName);
            printf("请输入修改后的价格：");
            float prize = 0;
            scanf("%f", &prize);
            Books_data *l = *linkp;
            if(book_change(l, bookName, prize) != 0)
                printf("修改成功！\n");
            else
                printf("修改失败！\n");
            //Sleep(1000);
            printf("\n输入任意字符以返回：");
            scanf("%s", bookName);
            break;
        }
        case '4':
            system("cls");
            printf("请输入书名：");
            char bookName[MAX_NAME_LEN] = { 0 };
            scanf("%s", bookName);
            //Books_data *l = linkp;
            if(book_delete(linkp, bookName) != 0)
                printf("删除成功！\n");
            else
                printf("删除失败！找不到要删除的书籍\n");
            //Sleep(1000);
            printf("\n输入任意字符以返回：");
            scanf("%s", bookName);

            break;
        case '5':
            return 1;
            break;
        default:
            //getchar();
            //printf("输入无效！请重新输入：");

            ;
        }
    }
    return 0;
}

static int Menu_BooksManage_ShowAllBooks(Books_data *linkp, int isPause)
{
    //while(getchar() != '\n');
    //system("cls");
    printf("序号：\t书名：\t价格：\n");
    int i = 1;
    while(linkp != NULL)
    {
        printf("%d\t%s\t%.2f\n", i++, linkp->bookName, linkp->prize);
        linkp = linkp->link;
    }
    if(isPause != 0)
    {
        printf("\n输入1以返回：");
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
    printf("请输入会员序号：");
    int number = 0;

    scanf("%d", &number);
    float credit = user_getLinkByNumber(*uLinkp, number)->credit;
    if((l = user_getLinkByNumber(*uLinkp, number)) != NULL)
    {
        char isContinue = 'y';
        while(isContinue != 'n')
        {
            printf("请输入要购买的书籍序号：");
            int n = 0, m = 0;
            scanf("%d", &n);
            printf("请输入要购买的本数：");
            scanf("%d", &m);
            float prize = 0;
            if((prize = book_getLinkByNumber(*bLinkp, n)->prize) > 0)
            {
                credit -= prize * m;
                user_getLinkByNumber(*uLinkp, n)->credit = credit;
            }
            else
            {
                printf("找不到该书籍，请重新输入！\n");
                continue;
            }
            printf("你要购买的书籍是《%s》，单价为%.2f元，总共%d本，总价为%.2f元\n", book_getLinkByNumber(*bLinkp, n)->bookName, prize, m, prize * m);
            printf("输入y继续买书，输入n结束购物：");
            scanf("%c", &isContinue);
            scanf("%c", &isContinue);
        }
        return 1;
    }
    else
        return 0;
}

//以下为书籍信息操作函数

//插入链表，每次传入的数据会在链表末尾插入，成功插入则返回1，失败则返回0
int book_insert(Books_data **linkp, char *new_bookName, float prize)
{
    if(prize <= 0)return 0;
    Books_data *book = (Books_data *)malloc(sizeof(Books_data));
    Books_data *current = *linkp;
    if(book != NULL)
    {
        //遍历链表直到末尾
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
//更改链表中储存的某个节点的数据（后续要加上相同书名的判断），成功则返回1，失败则返回0
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
//删除链表节点，成功则返回1，失败则返回0
int book_delete(Books_data **linkp, char *bookName)
{
    Books_data *current = NULL;
    while((current = *linkp) != NULL && strcmp(current->bookName, bookName) != 0)
        linkp = &(current->link);
    if(current != NULL && strcmp(current->bookName, bookName) == 0)
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


//返回书名对应书籍的价格，若没有找到该书籍则返回-1
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
//返回负数则说明没找到书籍
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

//以下为会员信息的操作函数

//插入链表，每次传入的数据会在链表末尾插入，成功插入则返回1，失败则返回0
int user_insert(Users_data **linkp, char *new_userName, float credit)
{
    Users_data *user = (Users_data *)malloc(sizeof(Users_data));
    Users_data *current = *linkp;
    if(user != NULL)
    {
        //遍历链表直到末尾
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
//更改链表中储存的某个节点的数据（后续要加上相同书名的判断），成功则返回1，失败则返回0
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
//删除链表节点，成功则返回1，失败则返回0
int user_delete(Users_data **linkp, char *userName)
{
    Users_data *current = NULL;
    while((current = *linkp) != NULL && strcmp(current->userName, userName) != 0)
        linkp = &(current->link);
    if(current != NULL && strcmp(current->userName, userName) == 0)
    {
        *linkp = current->link;
        //printf("会员 %s 信息删除完毕\n", userName);
        free(current->userName);
        free(current);
        return 1;
    }
    else
    {
        return 0;
    }
}
//删除从*linkp所指向的链表后面所有节点，返回删除的节点个数：i
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

//保存数据，sort请看头文件定义的enum，path可以为空，即""，rootp为链表根指针的地址
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
        //合成完整的文件路径
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
        //合成完整的文件路径
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

//读取数据，参数详解请看data_save的注释
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
        //合成完整的文件路径
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
        //合成完整的文件路径
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