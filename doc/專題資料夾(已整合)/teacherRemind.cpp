#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//#include"學生版提醒功能.h"
int teacherRemind();
/*int main()
{
    teacherRemind();
}*/

int teacherRemind(){
    FILE *file,*fp;
    int choise,lengh=0;
    char temp[200]= {' '},t,check;

    while(1)
    {
        file=fopen("rewind.txt","a+");//開檔
        fp=fopen("rewind.txt","a+");//讀檔
        printf("1.新增提醒文字 2.查看提醒文字 3.跳出\n");
        scanf("%d",&choise);//使用者選擇
        switch(choise)
        {
        case 1://新增文字
            if(file==NULL)//若無檔案則出現開檔失敗字樣
            {
                printf("open failure!!\n");
                break;
            }
            else
            {
                scanf("%s",temp);//輸入字串
//                printf("%s\n",temp);
                lengh=strlen(temp);
                temp[lengh]='\n';//在輸入字串後加上換行
                temp[lengh+1]='\0';
//                fputs(temp,file);
                if(temp!=EOF)//成功寫入陣列的話
                {
                    fputs(temp,file);//寫檔

                    printf("Successfully Inputed\n");
                }
                else
                {
                    printf("Input Fail\n");
                }

                fclose(file);//關檔
                break;
            }

        case 2:
            check=getc(file);//讓check去接收檔案的第一個字
            if(check!=EOF)//若不為EOF則表示檔案內有文字
            {
                while (!feof(fp))//印出
                {
//                    fscanf(fp, "%c", &t);
                    t=getc(fp);
                    printf("%c",t);
                }
                printf("\n");
            }
            else//為EOF則顯示檔案內無文字字樣
                printf("There is noting in here\n");
            fclose(fp);
            break;
        case 3://跳出
            return -1;
            break;
        default://若輸入數字不為1 2 3則請使用者重新輸入
            printf("Please Input again\n");
        }
    }

}
