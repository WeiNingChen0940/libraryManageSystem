#include "libraryManageSystem.h"

int main()
{
    /*if(SignUp((const char *)"test", (const char *)"123456") != 0)
    {
        printf("µÇÂ¼³É¹¦£¡\n");
    }*/
    
    Books_data *rootp = NULL;
    Books_data *linkp = NULL;;
    char name[] = "hello";
    int prize = 100;
    //Books_data *linkp = NULL;
    /*rootp = book_new(name, prize);*/
    for(int i = 0; i < 20; i++)
    {
        name[0] = 'a' + i;
        prize = 100 + i;
        linkedList_insert(&rootp, name, prize);
    }
    linkp = rootp;
    while(linkp != NULL)
    {
        printf("%s  %d\n", linkp->bookName, linkp->prize);
        linkp = linkp->link;
    }
    linkedList_delete_all(&rootp);

    return 0;
}