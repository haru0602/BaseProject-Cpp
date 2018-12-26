//<<<<<<< Updated upstream:doc/專題資料夾/老師端分享資源.cpp
#include<stdio.h>
#include<stdlib.h>

int teacherShare();
/*int main(){
    teacherShare();
}*/
int teacherShare(){
    FILE *fp;
    char a[500];
    int i,b;
    while(1){
    printf("Select one:1.Input website 2.Input the name of the book 3.Redo input website 4.Redo Input the name of the book 5.Exit:");
    scanf("%d",&i);
    switch(i){
        case 1:
        scanf("%s",a);
        printf("Press 1.Save 2.cancel:");
        scanf("%d",&b);
        if(b==1){
        fp=fopen("website.txt","a+");
        fprintf(fp,"%s\r\n",a);
        fclose(fp);
        break;
        }
        else if(b==2){
            printf("Canceled");
            break;
        }
        else{
        	continue;
		}
        case 2:
            scanf("%s",a);
            printf("Press 1.Save 2.cancel:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("book.txt","a+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
        }
        else if(b==2){
            printf("Canceled");
            break;
        }
        else{
        	continue;
		}
        case 3:
            scanf("%s",a);
            printf("Press 1.Save 2.cancel:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("website.txt","w+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
            }
            else if(b==2){
                printf("Canceled");
            break;
            }
            else{
        	continue;
		}
        case 4:
           scanf("%s",a);
            printf("Press 1 Save 2 cancel:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("book.txt","w+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
            }
            else if(b==2){
                printf("Canceled");
            break;
            }
            else{
        	continue;
		}
        case 5:
            return -1;
            break;
        default:
            printf("Please enter again!!\n");
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
