#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *pf;
    char ch;
    int a;
    printf("�п�ܥ\��: 1 �}��website���ɤ��e 2 �}��book���ɤ��e:");
    scanf("%d",&a);
    if(a==1){
    if((pf=fopen("website.txt","r"))==NULL)
    {
        printf("����}�Ҧ����!\n");
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
        printf("����}�Ҧ����!\n");
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
