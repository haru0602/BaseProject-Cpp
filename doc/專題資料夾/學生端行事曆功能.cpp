<<<<<<< Updated upstream:doc/專題資料夾/學生端行事曆功能.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int leapyear(int y);
int daysofmonth(int year,int month );
void printcalendar(int year, int month);
void setEvent(int year,int month);
int ndays[]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
typedef struct event
{
    int flag;//這一天有沒有事件
    char c[100];//事件名稱
} event;
typedef struct monthEvent
{
    int year;
    event thisdayEvent[31];//一個月的事件
} monthEvent;
monthEvent thisYearEvent[12];//總共12個月份

char data[200],ye[5]={' '},mo[3]={' '},da[3]={' '},info[200]={' '},space[1]={' '},change[1]={'\n'};
FILE *file,*fp;


int main(int argc, const char * argv[])
{
    int year, month,select,i;
    char t;
    while (1)
    {
        printf("請選功能(1.顯示行事曆2.設定事件3.結束):");
        scanf("%d",&select);
        switch (select)
        {
            case 1:
                printf("Enter this year:");
                scanf("%d", &year);
                
                printf("Enter this month:");
                scanf("%d", &month);
                printf(" %d年", year);
                printf("%d月", month);
                if(year>9999 || year<1000 || month>12 || month<0)//如果年和月輸入錯就重新輸入
                {
                    printf("\nvalidation error, \nredesignate year and month\n");
                    continue;
                }
                printcalendar(year, month);
                break;
            case 2:
                printf("Enter this year:");
                scanf("%d", &year);
                sprintf(ye,"%d",year);
                printf("Enter this month:");
                scanf("%d", &month);
                sprintf(mo,"%d",month);
                printf(" %d年", year);
                printf("%d月\n", month);
                if(year>9999 || year<1000 || month>12 || month<0)
                {
                    printf("validation error, \nredesignate year and month\n");
                    return 0;
                }
                setEvent(year,month);
                printcalendar(year, month);
                break;
            case 3:
                return -1;
                break;
            default:
                printf("Please Enter again\n");
        }
        
    }
    return 0;
    
    
}
// 閏年判定( leap year : 1、 normal year: 0)
int leapyear(int year)
{
    if (year % 400 == 0)
        return 1;
    else if (year % 100 == 0)
        return 0;
    else if (year % 4 == 0)
        return 1;
    else
        return 0;
}
//計算一個月有幾天
int daysofmonth(int year, int month )
{
    int i, s = 0;//s是一年的日數
    for (i = 1; i < year; i++)//到輸入的year
    {
        if (leapyear(i))
            s += 366;
        else
            s+=365;
    }
    for (i = 1; i < month; i++)
    {
        int days = ndays[ i - 1 ];
        if (i == 2 && leapyear(year))
            days = 29;
        s += days;
    }
    return s;
    
}
// 顯示行事曆
void printcalendar(int year, int month)
{
    int d = (daysofmonth(year, month) + 1) % 7;//判斷這個月的一號是星期幾
    int days = ndays[ month - 1 ];//一個月的總日數
    int i;
    printf( "\n  日 一 二 三 四 五 六\n" );
    if (leapyear(year) && month == 2)
        days = 29;
    for(i=0; i<d; i++)
        printf("   ");
    for (i = 1; i <= days; i++)
    {
        printf( "%3d", i );
        d = (d + 1) % 7;
        if (d == 0)
            printf("\n");
    }
    printf( "\n" );
    printf("這個月的事件\n");
    while (1)
    {
        if (thisYearEvent[month-1].year!=year)
        {
            printf("目前沒有\n");
            break;
        }
        else
        {
            for (int j = 1; j < 32; j++)//這個月的事件全部搜尋
            {
                if (thisYearEvent[month-1].thisdayEvent[j].flag == 1)//有事件就顯示
                {
                    printf("·%d日:\n%s\n",j,thisYearEvent[month-1].thisdayEvent[j].c);
                }
            }
            break;
            
        }
    }
    
    
}
//設定事件
void setEvent(int year,int month)
{
    int n;
    char s[100];
    file=fopen("calendar.txt","a");
    thisYearEvent[month-1].year = year;//先設定幾年的事件
    while (1)
    {
        printf("輸入設定幾號的事件:");
        scanf("%d",&n);//再輸入幾號的
        
        if (n<=0||n>daysofmonth(year, month))//輸入錯再重新
        {
            printf("輸入錯誤格式，再重新輸入\n");
        }
        else
        {
            sprintf(da,"%d",n);
            if (thisYearEvent[month-1].thisdayEvent[n].flag == 1)
            {
                strcat(thisYearEvent[month-1].thisdayEvent[n].c, "\n");//這一天已經有事件的話，後面再加上
            }
            else
                thisYearEvent[month-1].thisdayEvent[n].flag = 1;
            break;
        }
    }
    printf("輸入事件:\n");
    scanf("%s",s);//輸入事件名稱
    strcpy(info,s);//把所有事件資料列在一起
    strcat(data,ye);
    strcat(data,space);
    strcat(data,mo);
    strcat(data,space);
    strcat(data,da);
    strcat(data,space);
    strcat(data,info);
    strcat(data,change);
    fputs(data,file);//最後丟進file裡面
    fclose(file);
    strcat(thisYearEvent[month-1].thisdayEvent[n].c, s);//把事件名稱copy到struct裡面
    
}


=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int leapyear(int y);
int daysofmonth(int year,int month );
void printcalendar(int year, int month);
void setEvent(int year,int month);
int ndays[]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
typedef struct event
{
    int flag;//這一天有沒有事件
    char c[100];//事件名稱
} event;
typedef struct monthEvent
{
    int year;
    event thisdayEvent[31];//一個月的事件
} monthEvent;
monthEvent thisYearEvent[12];//總共12個月份

char data[200],ye[5]={' '},mo[3]={' '},da[3]={' '},info[200]={' '},space[1]={' '},change[1]={'\n'};
FILE *file,*fp;


int main(int argc, const char * argv[])
{
    int year, month,select,i;
    char t;
    while (1)
    {
        printf("請選功能(1.顯示行事曆2.設定事件3.結束):");
        scanf("%d",&select);
        switch (select)
        {
            case 1:
                printf("Enter this year:");
                scanf("%d", &year);

                printf("Enter this month:");
                scanf("%d", &month);
                printf(" %d年", year);
                printf("%d月", month);
                if(year>9999 || year<1000 || month>12 || month<0)//如果年和月輸入錯就重新輸入
                {
                    printf("\nvalidation error, \nredesignate year and month\n");
                    continue;
                }
                printcalendar(year, month);
                break;
            case 2:
                printf("Enter this year:");
                scanf("%d", &year);
                sprintf(ye,"%d",year);
                printf("Enter this month:");
                scanf("%d", &month);
                sprintf(mo,"%d",month);
                printf(" %d年", year);
                printf("%d月\n", month);
                if(year>9999 || year<1000 || month>12 || month<0)
                {
                    printf("validation error, \nredesignate year and month\n");
                    return 0;
                }
                setEvent(year,month);
                printcalendar(year, month);
                break;
            case 3:
                return -1;
                break;
            default:
                printf("Please Enter again\n");
        }

    }
    return 0;


}
// 閏年判定( leap year : 1、 normal year: 0)
int leapyear(int year)
{
    if (year % 400 == 0)
        return 1;
    else if (year % 100 == 0)
        return 0;
    else if (year % 4 == 0)
        return 1;
    else
        return 0;
}
//計算一個月有幾天
int daysofmonth(int year, int month )
{
    int i, s = 0;//s是一年的日數
    for (i = 1; i < year; i++)//到輸入的year
    {
        if (leapyear(i))
            s += 366;
        else
            s+=365;
    }
    for (i = 1; i < month; i++)
    {
        int days = ndays[ i - 1 ];
        if (i == 2 && leapyear(year))
            days = 29;
        s += days;
    }
    return s;

}
// 顯示行事曆
void printcalendar(int year, int month)
{
    int d = (daysofmonth(year, month) + 1) % 7;//判斷這個月的一號是星期幾
    int days = ndays[ month - 1 ];//一個月的總日數
    int i;
    printf( "\n  日 一 二 三 四 五 六\n" );
    if (leapyear(year) && month == 2)
        days = 29;
    for(i=0; i<d; i++)
        printf("   ");
    for (i = 1; i <= days; i++)
    {
        printf( "%3d", i );
        d = (d + 1) % 7;
        if (d == 0)
            printf("\n");
    }
    printf( "\n" );
    printf("這個月的事件\n");
    while (1)
    {
        if (thisYearEvent[month-1].year!=year)
        {
            printf("目前沒有\n");
            break;
        }
        else
        {
            for (int j = 1; j < 32; j++)//這個月的事件全部搜尋
            {
                if (thisYearEvent[month-1].thisdayEvent[j].flag == 1)//有事件就顯示
                {
                    printf("·%d日:\n%s\n",j,thisYearEvent[month-1].thisdayEvent[j].c);
                }
            }
            break;

        }
    }


}
//設定事件
void setEvent(int year,int month)
{
    int n;
    char s[100];
    file=fopen("calendar.txt","a");
    thisYearEvent[month-1].year = year;//先設定幾年的事件
    while (1)
    {
        printf("輸入設定幾號的事件:");
        scanf("%d",&n);//再輸入幾號的

        if (n<=0||n>daysofmonth(year, month))//輸入錯再重新
        {
            printf("輸入錯誤格式，再重新輸入\n");
        }
        else
        {
            sprintf(da,"%d",n);
            if (thisYearEvent[month-1].thisdayEvent[n].flag == 1)
            {
                strcat(thisYearEvent[month-1].thisdayEvent[n].c, "\n");//這一天已經有事件的話，後面再加上
            }
            else
                thisYearEvent[month-1].thisdayEvent[n].flag = 1;
            break;
        }
    }
    printf("輸入事件:\n");
    scanf("%s",s);//輸入事件名稱
    strcpy(info,s);//把所有事件資料列在一起
    strcat(data,ye);
    strcat(data,space);
    strcat(data,mo);
    strcat(data,space);
    strcat(data,da);
    strcat(data,space);
    strcat(data,info);
    fputs(data,file);//最後丟進file裡面
    fclose(file);
    strcat(thisYearEvent[month-1].thisdayEvent[n].c, s);//把事件名稱copy到struct裡面

}


>>>>>>> Stashed changes:doc/專題資料夾/學生端行事曆功能.c
