#include "libraryManageSystem.h"

int main()
{
    Books_data *bRootp = NULL;
    Books_data *bLinkp = NULL;
    Users_data *uRootp = NULL;
    Users_data *uLinkp = NULL;
    char name[] = "aUser";
    float prize = 100;
    float credit = 200;

    if(data_load("", BOOKS, &bRootp) == 0)
        for(int i = 0; i < 10; i++)
        {
            name[0] = 'a' + i;
            prize = 100.0f + i;
            book_insert(&bRootp, name, prize);
        }

    if(data_load("", USERS, &uRootp) == 0)
        for(int i = 0; i < 10; i++)
        {
            name[0] = 'a' + i;
            credit = 200.0f + i;
            user_insert(&uRootp, name, credit);
        }

    if(SignUp((const char *)"test", (const char *)"123456") != 0)
    {
        printf("登录成功！\n");
    }
    Menu_Main(uRootp,bRootp);

    bLinkp = bRootp;
    uLinkp = uRootp;

    //int i = 1;
    //while(bLinkp != NULL)
    //{
    //    printf("第%d本书:书名《%s》  价格为%.2f元\n", i++, bLinkp->bookName, bLinkp->prize);
    //    bLinkp = bLinkp->link;
    //}

    //i = 1;
    //while(uLinkp != NULL)
    //{
    //    printf("第%d个会员：%s  积分为%.2f\n", i++, uLinkp->userName, uLinkp->credit);
    //    uLinkp = uLinkp->link;
    //}

    data_save("", USERS, uRootp);
    data_save("", BOOKS, bRootp);
    book_delete_all(&bRootp);
    user_delete_all(&uRootp);

    return 0;
}