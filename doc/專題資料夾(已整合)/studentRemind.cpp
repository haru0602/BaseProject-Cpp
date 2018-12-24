#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int studentRemind();
/*int main()
{

    studentRemind();
}*/

int studentRemind(){
    int i=0,choise;
    FILE *fp,*file;
    char data[200],t='a',temp='a';
    while(1)
    {
        printf("1.查看提醒 2.查看行事曆事件 3.結束\n");
        scanf("%d",&choise);
        switch(choise)
        {
        case 1:
            fp=fopen("rewind.txt","r");
            t=fgetc(fp);//使t去接收文字檔內第一個字
            if(fp!=NULL)//若有此檔案
            {
                if (t!=EOF)//若t不為EOF則代表文字檔內有東西
                {
                    printf("Breaking News!!!\n");
                    printf("There is a unchecked Remind!!\n\n");
                    printf("%c",t);//因為第一個字被拿去判斷了 所以確定不是EOF就要先印出
                    while (!feof(fp))//印出
                    {
//                    fscanf(fp, "%c", &t);
                        t=getc(fp);
                        printf("%c",t);
                    }
                    printf("\n");

                }
                else//檔案內若為EOF則代表裡面沒東西 出現無內容字樣
                    printf("There is nothing in here\n");
            }
            else//無此檔案
            {
                printf("The file is not exist!!\n");
            }
            fclose(fp);//關檔
            break;
        case 2:
            file=fopen("calendar.txt","r");
            temp=fgetc(file);//使t去接收文字檔內第一個字
            if(file!=NULL)//若有此檔案
            {
                if (temp!=EOF)//若t不為EOF則代表文字檔內有東西
                {
                    printf("%c",temp);//因為第一個字被拿去判斷了 所以確定不是EOF就要先印出
                    while (!feof(file))//印出
                    {
//                    fscanf(fp, "%c", &t);
                        temp=getc(file);
                        printf("%c",temp);
                    }
                    printf("\n");

                }
                else//檔案內若為EOF則代表裡面沒東西 出現無內容字樣
                    printf("There is nothing in here\n");
            }
            else//無此檔案
            {
                printf("The file is not exist!!\n");
            }
            fclose(file);//關檔
            break;
        case 3:
            return -1;
            break;
        default:
            printf("Please Enter again\n");
        }
    }
}
