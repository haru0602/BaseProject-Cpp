#include<stdio.h>

int main(){
    FILE *fp;
    char a[500];
    int i,b;
    printf("�п��:1 ��J���} 2 ��J���y�W�� 3 ���s�g�n���ɪ����� 4 ���s�g�n���ɪ����y�W��:");
    scanf("%d",&i);
    switch(i){
        case 1:
        scanf("%s",a);
        printf("�Ы�1 �x�s 2 ����:");
        scanf("%d",&b);
        if(b==1){
        fp=fopen("website.txt","a+");
        fprintf(fp,"%s\r\n",a);
        fclose(fp);
        break;
        }
        else if(b==2){
            printf("�H����");
            break;
        }
        case 2:
            scanf("%s",a);
            printf("�Ы�1 �x�s 2 ����:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("book.txt","a+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
        }
        else if(b==2){
            printf("�H����");
            break;
        }
        case 3:
            scanf("%s",a);
            printf("�Ы�1 �x�s 2 ����:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("website.txt","w+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
            }
            else if(b==2){
                printf("�H����");
            break;
            }
        case 4:
           scanf("%s",a);
            printf("�Ы�1 �x�s 2 ����:");
            scanf("%d",&b);
            if(b==1){
            fp=fopen("book.txt","w+");
            fprintf(fp,"%s\r\n",a);
            fclose(fp);
            break;
            }
            else if(b==2){
                printf("�H����");
            break;
            }
    }
    return 0;
}

