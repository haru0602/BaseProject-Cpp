//<<<<<<< Updated upstream:doc/專題資料夾/學生端分享資源.cpp
#include<stdio.h>
#include<stdlib.h>

int studentShare();
/*int main(){
    studentShare();
    return 0;
}*/

int studentShare()
{
    FILE *pf;
    char ch;
    int a;
    while(1)
    {
        printf("Select One: 1 Open website to share 2 Open book to share 3 Exit:");
        scanf("%d",&a);
        if(a==1)
        {
            if((pf=fopen("website.txt","r"))==NULL)
            {
                printf("Can not open the file!\n");
            }
            ch=fgetc(pf);
            while(ch!=EOF)
            {
                putchar(ch);
                ch=fgetc(pf);
            }
            printf("\n");
            fclose(pf);
        }
        else if(a==2)
        {
            if((pf=fopen("book.txt","r"))==NULL)
            {
                printf("Can not open the file!\n");
            }
            ch=fgetc(pf);
            while(ch!=EOF)
            {
                putchar(ch);
                ch=fgetc(pf);
            }
            printf("\n");
            fclose(pf);
        }
        else
            return -1;
    }
}
/*=======
#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *pf;
    char ch;
    int a;
    printf("請選擇功能: 1 開啟website分享內容 2 開啟book分享內容:");
    scanf("%d",&a);
    if(a==1){
    if((pf=fopen("website.txt","r"))==NULL)
    {
        printf("不能開啟此文件!\n");
        exit(0);
    }
    ch=fgetc(pf);
    while(ch!=EOF){
        putchar(ch);
        ch=fgetc(pf);
    }
    printf("\n");
    fclose(pf);
    }
    else if(a==2){
       if((pf=fopen("book.txt","r"))==NULL)
    {
        printf("不能開啟此文件!\n");
        exit(0);
    }
    ch=fgetc(pf);
    while(ch!=EOF){
        putchar(ch);
        ch=fgetc(pf);
    }
    printf("\n");
    fclose(pf);
    }
    return 0;
}
>>>>>>> Stashed changes:doc/學生端分享資源.cpp*/
