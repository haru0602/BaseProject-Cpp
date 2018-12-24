//<<<<<<< Updated upstream:doc/專題資料夾/老師端分享資源.cpp
#include<stdio.h>
#include<stdlib.h>

void teacherShare();
/*int main(){
    teacherShare();
}*/
void teacherShare(){
    FILE *fp;
    char a[500];
    int i,b;
    printf("請選擇:1 輸入網址 2 輸入書籍名稱 3 重新寫要分享的網站 4 重新寫要分享的書籍名稱:");
    scanf("%d",&i);
    switch(i){
        case 1:
        scanf("%s",a);
        printf("請按1 儲存 2 取消:");
        scanf("%d",&b);
        if(b==1){
        fp=fopen("website.txt","a+");
        fprintf(fp,"%s\r\n",a);
        fclose(fp);
        break;
        }
        else if(b==2){
            printf("以取消");
            break;
        }
        case 2:
            scanf("%s",a);
            printf("請按1 儲存 2 取消:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("book.txt","a+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
        }
        else if(b==2){
            printf("以取消");
            break;
        }
        case 3:
            scanf("%s",a);
            printf("請按1 儲存 2 取消:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("website.txt","w+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
            }
            else if(b==2){
                printf("以取消");
            break;
            }
        case 4:
           scanf("%s",a);
            printf("請按1 儲存 2 取消:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("book.txt","w+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
            }
            else if(b==2){
                printf("以取消");
            break;
            }
    }
}

/*=======
#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *fp;
    char a[500];
    int i,b;
    printf("請選擇:1 輸入網址 2 輸入書籍名稱 3 重新寫要分享的網站 4 重新寫要分享的書籍名稱:");
    scanf("%d",&i);
    switch(i){
        case 1:
        scanf("%s",a);
        printf("請按1 儲存 2 取消:");
        scanf("%d",&b);
        if(b==1){
        fp=fopen("website.txt","a+");
        fprintf(fp,"%s\r\n",a);
        fclose(fp);
        break;
        }
        else if(b==2){
            printf("以取消");
            break;
        }
        case 2:
            scanf("%s",a);
            printf("請按1 儲存 2 取消:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("book.txt","a+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
        }
        else if(b==2){
            printf("以取消");
            break;
        }
        case 3:
            scanf("%s",a);
            printf("請按1 儲存 2 取消:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("website.txt","w+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
            }
            else if(b==2){
                printf("以取消");
            break;
            }
        case 4:
           scanf("%s",a);
            printf("請按1 儲存 2 取消:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("book.txt","w+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
            }
            else if(b==2){
                printf("以取消");
            break;
            }
    }
    return 0;
}
*/
//>>>>>>> Stashed changes:doc/老師端分享資源.cpp
