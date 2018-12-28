#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE
{
    char std_id[20];
    char name[20];
    int group;
    struct NODE *next;
} node;

void freeList(node *head)
{
    node *current,*tmp;
    current=head;
    while(current!=NULL)
    {
        tmp=current;
        current=current->next;
        free(tmp);
    }
}
void grouping();
/*int main()
{

    goruping();


    return 0;
}*/

void grouping(){
    int choice,flag=0,random,exit=0,totalgroup;
    node *head,*current,*pre;
    head=(node *)malloc(sizeof(node));
    head->next=NULL;
    srand(time(NULL));
    printf("Hello! Welcome to the grouping system!\nPlease enter how many groups you wants totally?\n");
    printf("Total groups:");
    scanf("%d",&totalgroup);
    printf("*********************************************************************\n");
    while(1)
    {
        if(exit==1)break;
        printf("Grouping System:1.Single Grouping  2.Grouping Randomly  3.Group List  4.Exit\n");
        scanf("%d",&choice);
        if(choice<1||choice>4){printf("Unavailable Option\n");}
        else{
        switch(choice)
        {
        case 1:
            printf("Please enter Student ID , Student name and the group which student join. \n");
            printf("Example:D1234567 PeterChan 2       (Student name need not space)  \n");
            current=(node *)malloc(sizeof(node));
            scanf("%s %s %d",&current->std_id,&current->name,&current->group);
            printf("*********************************************************************\n");
            if(current->group>totalgroup){
                printf("The group number is wrong!! Please try again\n");
                printf("*********************************************************************\n");
                break;
            }
            if(flag==0)
            {
                head=current;
                flag=1;
            }
            else
            {
                pre->next=current;
            }
            current->next=NULL;
            pre=current;
            break;

        case 2:
            current=(node *)malloc(sizeof(node));
            printf("Please enter Student ID , Student name.It will spread into a group randomly \n");
            printf("Example:D1234567 PeterChan  (Student need not space)  \n");
            scanf("%s %s",&current->std_id,&current->name);
            random=(rand()%totalgroup)+1;
            printf("*********************************************************************\n");
            printf("This student will spread in Group%d.\n",random);
            current->group=random;
            printf("*********************************************************************\n");
            if(flag==0)
            {
                head=current;
                flag=1;
            }
            else
            {
                pre->next=current;
            }
            current->next=NULL;
            pre=current;
            break;

        case 3:

            current=head;

            if(flag==0)
            {
                printf("Opps,It's empty now\n");
                printf("*********************************************************************\n:");
                break;
            }
            else
            {
            printf("*********************************************************************\n");
            while(current!=NULL)
            {
                printf("%s %s %d\n",current->std_id,current->name,current->group);

                current=current->next;

            }
            printf("*********************************************************************\n:");
            break;
            }
        case 4:
            freeList(head);
            exit=1;
            printf("See U again");
            printf("*********************************************************************\n:");
            break;
        }
        }
    }
}

