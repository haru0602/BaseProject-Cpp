#include<iostream>
#include<cstdio>
#include<windows.h>
#include<fstream>
#include<conio.h>
#include <Wincon.h>
#include<string>
#include <unistd.h>
#include<vector>
#include<algorithm>


#include"teacherShare.cpp"
#include"teacherAnswer.cpp"
//#include"teacherRemind.cpp"

#include"studentRemind.cpp"
#include"studentShare.cpp"
#include"studentCalendar.cpp"
#include"studentAskQuestion.cpp"

#include"grouping.cpp"



#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
//禁言次數
#define TALK 0

using namespace std;
//Color
enum Color{
    BLACK = 0,
    DARK_BLUE = 1,
    DARK_GREEN = 2,
    TEAL = 3,
    DARK_RED = 4,
    DARK_PURPLE = 5,
    GOLD = 6,
    GREY = 7,
    DARK_WHITE = 8,
    BLUE = 9,
    GREEN = 10,
    CYAN = 11,
    RED = 12,
    PURPLE = 13,
    YELLOW = 14,
    WHITE = 15
};
Color color;

//身份
enum Id{
    STUDENT = 0,
    TEACHER = 1
};

//使用者資料結構
typedef struct {
    string account;
    string password;
    string name;
    bool permission;
    int sensitiveWordCount;
}User;








void setColor(int , int);
void goToxy(int , int);
void setFontSize(int );
void loginBoard();
bool login();
void regisiter();
void mainBoard();
void commentMainBoard();
void commentBooard(string boardName);
string extractPath();
void browsePostList(string boardName);
void browsePost(string boardName,string postName);
void commentFun(string filePath, bool anonymous);
bool haveSensitiveWord(string statment);
void createPost(string boarName, bool anonymous);

//使用者資料, 可用於各個功能中顯示使用者資料
User user;
//////

 /*int main(){

    loginBoard();

	return 0;
 }*/

void setColor(int fontColor , int background){
    int color = fontColor + background *16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void goToxy(int x, int y ){
    COORD coord={x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



//開始主介面
void loginBoard(){
    SetConsoleTitle("登入/註冊");
    string ans, goToRegister;
    bool loginSuccess;
    printf("Welcome!!");

    do{
        system("CLS");
        printf("登入[Y\\N]:");
        cin>>ans;
        loginSuccess = false;
        //判斷輸入的正確性
        if(ans == "Y" || ans == "y"){
            loginSuccess = login();
            //錯誤輸入次數超過3次後詢問是否要註冊
            if(!loginSuccess){
                system("CLS");
                printf("錯誤輸入次數超過3次\n");
                printf("是否要進行註冊[Y\\N]:");
                cin>>goToRegister;
                if(goToRegister == "Y" || goToRegister == "y")
                    break;
                else
                    exit(0);
            }

        }

        else if(ans != "N" && ans != "n"){
            printf("輸入錯誤\n");
            system("pause");
            continue;
        }

    }while(ans != "N" && ans != "n" && ans != "Y" && ans != "y");

    while(!loginSuccess &&ans != "N" || ans != "n" && ans != "Y" && ans != "y"){
        system("CLS");
        printf("註冊[Y\\N]:");
        cin>>ans;

        //判斷輸入正確性
        if(ans == "Y" || ans == "y"){
            regisiter();
            loginSuccess = login();
        }

        else if(ans != "N" && ans != "n"){
            printf("輸入錯誤\n");
            system("pause");
            continue;
        }

    }
    if(loginSuccess)
        mainBoard();

}

//登入介面
bool login(){
    SetConsoleTitle("登入");
    ifstream file;
    User input;
    bool loginSuccess = false ;
    int wrongCount =0;
    string filePath = extractPath() + "\\登入\\UserName.txt";
    string userAccount;
    file.open(filePath.c_str(), ios::in);
    do{
        system("CLS");
        setColor(PURPLE,BLACK);
        printf("帳號:");
        cin>>input.account;
        printf("密碼:");
        cin>>input.password;

        //判斷帳號密碼的格式
        if(input.account.length() < 6 || input.password.length() < 6){
            printf("帳號或密碼格式錯誤\n");
            system("pause");
            continue;
        }

        if(file.is_open()){

            while(!file.eof()){
                //讀取檔案內容
                file>>userAccount;

                //判斷登入的帳號及密碼是否正確
                if(userAccount == input.account){
                    string userPath = extractPath() + "\\登入\\" + userAccount + ".txt";
                    ifstream readUserFile(userPath.c_str(), ios::in);
                    if(readUserFile.is_open()){
                        readUserFile>>user.name;

                        readUserFile>>user.permission;

                        readUserFile>>user.sensitiveWordCount;

                        readUserFile>>user.account;

                        readUserFile>>user.password;

                        if(user.password == input.password){
                            loginSuccess = true;
                            break;
                        }

                    }

                }

            }

        }
        else{
            cout<<"login.txt not found"<<endl;
            system("pause");
        }

        system("CLS");
        if(loginSuccess)
            break;
        wrongCount++;
        printf("已錯誤輸入%d次\n",wrongCount);
        system("pause");
        //重置檔案指標
        file.clear();
        file.seekg(0, ios::beg);
    }while(!loginSuccess && wrongCount<3);

    file.close();
    setColor(WHITE,BLACK);
    return loginSuccess;
}

//註冊介面
void regisiter(){
    SetConsoleTitle("註冊");
    string name,account_Input, password_Input, password_Confirm, identity;
    bool success, permission;
    string filePath = extractPath() + "\\登入\\UserName.txt";
    ofstream file;

    do{
        success = false;
        system("CLS");
        setColor(YELLOW,BLACK);
        //輸入註冊資訊
        printf("姓名:");
        cin>>name;
        printf("身份(學生/老師):");
        cin>>identity;
        if(identity == "學生")
            permission = STUDENT;
        else if(identity == "老師")
            permission = TEACHER;
        else{
            printf("身份錯誤\n");
            system("pause");
            continue;
        }
        printf("帳號:");
        cin>>account_Input;
        printf("密碼:");
        cin>>password_Input;
        //判斷帳號密碼的格式
        if(account_Input.length() < 6 || password_Input.length() < 6){
            printf("帳號或密碼格式錯誤\n");
            system("pause");
            continue;
        }
        system("CLS");
        //確認密碼
        printf("確認密碼:");
        cin>>password_Confirm;
        if(password_Input != password_Confirm){
            system("CLS");
            printf("密碼不相同\n");
            system("pause");
            continue;
        }
        system("CLS");
        //寫入註冊成功的資料
        file.open(filePath.c_str(), ios::app);
        if(file.is_open()){
            file<<account_Input<<endl;
            string userFilePath = extractPath() + "\\登入\\" +account_Input + ".txt";
            ofstream userFile;
            userFile.open(userFilePath.c_str(), ios::out);
            userFile<<name<<endl;
            userFile<<permission<<endl;
            userFile<<0<<endl;
            userFile<<account_Input<<endl;
            userFile<<password_Input<<endl;
        }
        else{
            cout<<"login.txt not found"<<endl;
            system("pause");
        }

        success = true;
    }while(!success);
    file.close();
    setColor(WHITE,BLACK);
}

//功能主介面
void mainBoard(){
    SetConsoleTitle("主介面");
    bool inputCorrect = true;
    int choose;
    setColor(CYAN,BLACK);
    do{
        system("CLS");
        cout<<"你好, "<<user.name;
        if(user.permission == TEACHER)
            printf("老師\n");
        else
            printf("同學\n");

        printf("功\能列表\n");
        printf("1: 留言版\n");
        printf("2: 資源分享\n");
        printf("3: 分組功\能\n");
        printf("4: 行事曆\n");
        printf("5: 提醒頁面\n");
        if(user.permission == TEACHER)
            printf("6:  老師專用功\能\n");

        printf("輸入功\能代號:");
        cin>>choose;
        inputCorrect = true;

        switch(choose){
            case 1:
                commentMainBoard();
                break;
            case 2:
                //進入資源分享
                system("CLS");
                setColor(YELLOW,BLACK);
                if(user.permission == TEACHER)
                    teacherShare();
                else{
                    studentShare();
                }

                break;
            case 3:
                system("CLS");
                setColor(RED,BLACK);
                grouping();
                //進入分組功能
                break;
            case 4:
                system("CLS");
                setColor(RED,BLACK);
                studentCalendar();
                //進入行事曆
                break;
            case 5:
                system("CLS");
                setColor(GREEN,BLACK);
                if(user.permission == TEACHER)
                    //teacherRemind();
                    printf("教師版提醒功\能\n");
                else
                    studentRemind();
                //進入提醒頁面
                break;
            case 6:
                system("CLS");
                setColor(DARK_WHITE,BLACK);
                if(user.permission == TEACHER){
                    //進入老師專用功能
                    teacherAnswer();
                    break;
                }
            default:
                printf("輸入錯誤\n");
                system("pause");
                inputCorrect = false;
                break;


        }
    }while(!inputCorrect);
}

//留言版功能選擇主介面
void commentMainBoard(){
    SetConsoleTitle("留言版主介面");
    int choose;
    bool chooseCorrect;
    do{
        system("CLS");
        if(user.sensitiveWordCount>TALK)
            printf("你已被禁言!!\n");
        printf("1: 上課發問版（匿名）\n");
        printf("2: 發問版\n");
        printf("輸入版面代號:");
        cin>>choose;
        chooseCorrect = true;

        switch(choose){
            case 1:
                commentBooard("上課發問版");
                break;
            case 2:
                commentBooard("發問版");
                break;
            case KEY_UP:
                mainBoard();
                break;
            default:
                printf("輸入錯誤\n");
                chooseCorrect = false;
                system("pause");
                break;
        }

    }while(!chooseCorrect);

}


//讀取現在所在的地點
string extractPath(){
    char cwd[PATH_MAX];
   string path;
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
        path = cwd;
        return path;
   } else {
       perror("getcwd() error");
       return NULL;
   }
}

//留言版功能選擇介面
void commentBooard(string boardName){
    SetConsoleTitle(boardName.c_str());
    int choose;
    bool chooseCorrect;
    do{
        system("CLS");
        chooseCorrect = true;
        if(user.sensitiveWordCount>TALK)
            printf("你已被禁言!!\n");
        printf("1: 瀏覽帖子\n");
        printf("2: 開新帖子\n");
        printf("輸入功\能代號:");
        cin>>choose;
        switch(choose){
            case 1:
                //瀏覽帖子列表
                chooseCorrect = false;
                browsePostList(boardName);
                break;
            case 2:
                //開新帖子
                chooseCorrect = false;
                if(boardName == "上課發問版")
                    createPost(boardName, true);
                else
                    createPost(boardName, false);
                break;
            case KEY_UP:
                commentMainBoard();
                break;
            default:
                chooseCorrect = false;
                printf("輸入錯誤\n");
                break;

        }

    }while(!chooseCorrect);
}

//瀏覽帖子列表
void browsePostList(string boardName){
    bool chooseCorrect;
    int cur = 0, postNum;
    string postName[10], junk;
    string filePath = extractPath() +"\\" + "留言版" +  "\\" + boardName +"\\postName.txt";
    ifstream file(filePath.c_str(), ios::in);
    if(file.is_open()){
        do{
            system("CLS");
            if(user.sensitiveWordCount>TALK)
                printf("你已被禁言!!\n");
            chooseCorrect = true;
            file.clear();
            file.seekg(0, ios::beg);
            //讓檔案指標回到想要的位置
            for(int i =0; i<cur;i++)
                file>>junk;

            //每次只顯示10個帖子
            for(int i = 0, postNum = 0; i<10&&!file.eof(); i++, postNum++){
                file>>postName[postNum];
                if(file.eof())break;
                cout<<postNum+1 <<": " << postName[postNum]<<endl;
                printf("---------------------------------------\n");
            }
            printf("%-20s%-20s%-20s\n", cur==0? "":"上一頁:方向鍵左", "返回:方向鍵上", file.eof()==true? "":"下一頁:方向鍵右");
            char charChoose;
            charChoose = _getch();
            int intChoose = charChoose - '0';
            if(intChoose>=1 && intChoose<=10)
                //瀏覽帖子
                browsePost(boardName, postName[--intChoose]);


            else{
                //判斷方向鍵
                switch(intChoose = _getch()){
                    case KEY_UP:
                        commentBooard(boardName);
                        break;
                    case KEY_LEFT:
                        chooseCorrect = false;
                        cur -= 10;
                        break;
                    case KEY_RIGHT:
                        chooseCorrect = false;
                        cur += 10;
                        break;
                    default:
                        chooseCorrect = false;
                        printf("輸入錯誤\n");
                        system("pause");
                        break;
                }
            }
        }while(!chooseCorrect);
        file.close();
    }
    else{
        cout<< boardName<<"\\postName.txt not found"<<endl;
        system("pause");
    }
}

//瀏覽帖子內容
void browsePost(string boardName,string postName){
    string filePath = extractPath() + "\\" + "留言版" + "\\" + boardName + "\\" +postName + ".txt";
    ifstream file(filePath.c_str(), ios::in);
    string comment, commenter;
    bool chooseCorrect;
    int cur=0, choose;
    SetConsoleTitle(postName.c_str());
    if(file.is_open()){
        do
        {

            system("CLS");
            file.clear();
            file.seekg(0, ios::beg);
            if(user.sensitiveWordCount>TALK)
                printf("你已被禁言!!\n");
            printf("標題:");
            file>>comment;
            cout<<comment<<endl;
            printf("作者:");
            file>>commenter;
            cout<<commenter<<endl;
            chooseCorrect = true;

            string junk;
            //讓檔案指標回到想要的位置
            for(int i =0; i<cur; i++)
                file>>junk;

            printf("---------------------------------------\n");
            //每次只顯示10個留言
            for(int i = 0, postNum = 0; i<10&&!file.eof(); i++, postNum++)
            {
                file>>comment;
                if(file.eof())break;
                cout<<comment<<endl;
                file>>commenter;
                printf("留言人:");
                cout<<commenter<<endl;
                printf("---------------------------------------\n");
            }
            printf("%-20s%-20s%-20s%-20s\n", cur==0? "":"上一頁:方向鍵左", "返回:方向鍵上", "留言:方向鍵下", file.eof()==true? "":"下一頁:方向鍵右");
            _getch();
            switch((choose = _getch()))
            {
            case KEY_UP:
                browsePostList(boardName);
                break;
            case KEY_DOWN:
                chooseCorrect = false;
                if(user.sensitiveWordCount <= TALK)
                {
                    //留言
                    if(boardName == "上課發問版")
                        commentFun(filePath,true);
                    else
                        commentFun(filePath, false);
                    system("pause");
                }

                else
                {
                    printf("你已被禁言!!\n");
                    system("pause");
                }
                break;
            case KEY_LEFT:
                chooseCorrect = false;
                cur -= 10;
                break;
            case KEY_RIGHT:
                chooseCorrect = false;
                cur += 10;
                break;
            default:
                chooseCorrect = false;
                printf("輸入錯誤\n");
                system("pause");
                break;
            }
        }while(!chooseCorrect);
    }

    else{
    chooseCorrect = false;
    printf("帖了不存在\n");
    system("pause");
    browsePostList(boardName);
    }
    file.close();


}

//留言功能
void commentFun(string filePath, bool anonymous){
    ofstream file(filePath.c_str(), ios::app);
    string input;
    if(file.is_open()){
        system("CLS");
        printf("請輸入留言:\n");
        cin>>input;
        //如果沒有敏感字眼的話把留言寫入檔案
        if(!haveSensitiveWord(input)){
            file<<input<<endl;
            if(anonymous)
                file<<"匿名"<<endl;
            else
                file<<user.name<<endl;
        }

    }
    file.close();
}

//檢查敏感字眼
bool haveSensitiveWord(string statment){
    vector<string> sensitiveWord ;
    string tmp = statment, word;
    string filePath = extractPath() + "\\留言版\\sensitiveWord.txt";
    ifstream file(filePath.c_str(), ios::in);
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    bool haveWord = false;
    if(file.is_open()){
        //讀取所有敏感字眼
        while(!file.eof()){
            file>>word;
            sensitiveWord.push_back(word);
        }
    }
    for(int i =0; i < sensitiveWord.size(); i++){
            //尋找敏感字眼
        if(statment.find(sensitiveWord[i].c_str()) != string::npos || tmp.find(sensitiveWord[i].c_str()) != string::npos){
            //如留言有敏感字眼, 更新使用者資料
            user.sensitiveWordCount++;
            system("CLS");
            printf("句子含有敏感字眼\n");
            string userFilePath = extractPath() + "\\登入\\" + user.account + ".txt";
            ofstream userFile(userFilePath.c_str(), ios::out);
            if(userFile.is_open()){
                userFile<<user.name<<endl;
                userFile<<user.permission<<endl;
                userFile<<user.sensitiveWordCount<<endl;
                userFile<<user.account<<endl;
                userFile<<user.password<<endl;
            }
            system("pause");
            haveWord = true;
            break;
        }
    }
    file.close();
    return haveWord;
}


void createPost(string boarName, bool anonymous){
    system("CLS");
    string title, filePath;
    printf("輸入標題:\n");
    cin>>title;
    filePath = extractPath() + "\\留言版\\" + boarName + "\\" + title +".txt";
    ofstream file(filePath.c_str(), ios::out);
    string postNamePath = extractPath() + "\\留言版\\" + boarName + "\\postName.txt";
    ifstream inputPostName(postNamePath.c_str(), ios::in);
    ofstream outputPostName(postNamePath.c_str(), ios::app);
    string file_Input_Post_Name;
    bool postNameRepeat = false;
    if(file.is_open()){
        //檢查敏感字眼
        if(!haveSensitiveWord(title)){
            if(inputPostName.is_open()){
                //檢查標題是重複
                while(!inputPostName.eof()){
                    inputPostName>>file_Input_Post_Name;
                    if(file_Input_Post_Name == title){
                        postNameRepeat = true;
                        printf("帖子標題重複\n");
                        system("pause");
                        break;
                    }
                }

            }
                inputPostName.close();
            }
            if(!postNameRepeat){
                file<<title<<endl;
                if(anonymous)
                    file<<"匿名"<<endl;
                else
                    file<<user.name<<endl;
                //更新已創造的帖子
                if(outputPostName.is_open())
                    outputPostName<<title<<endl;

        }

    }
    file.close();
    outputPostName.close();

}
