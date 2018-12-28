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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"teacherShare.cpp"
#include"teacherAnswer.cpp"
#include"teacherRemind.cpp"

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
    SetConsoleTitle("Login/Register");
    string ans, goToRegister;
    bool loginSuccess;
    printf("Welcome!!");

    do{
        system("CLS");
        printf("Login?[Y\\N]:");
        cin>>ans;
        loginSuccess = false;
        //判斷輸入的正確性
        if(ans == "Y" || ans == "y"){
            loginSuccess = login();
            //錯誤輸入次數超過3次後詢問是否要註冊
            if(!loginSuccess){
                system("CLS");
                printf("Error over three times\n");
                printf("Registering?[Y\\N]:");
                cin>>goToRegister;
                if(goToRegister == "Y" || goToRegister == "y")
                    break;
                else
                    exit(0);
            }

        }

        else if(ans != "N" && ans != "n"){
            printf("Input Error\n");

            system("pause");
            continue;
        }

    }while(ans != "N" && ans != "n" && ans != "Y" && ans != "y");

    while(!loginSuccess &&ans != "N" || ans != "n" && ans != "Y" && ans != "y"){
        system("CLS");
        printf("Register[Y\\N]:");
        cin>>ans;

        //判斷輸入正確性
        if(ans == "Y" || ans == "y"){
            regisiter();
            loginSuccess = login();
        }

        else if(ans != "N" && ans != "n"){
            printf("Input Error\n");
            system("pause");
            continue;
        }

    }
    if(loginSuccess)
        mainBoard();

}

//登入介面
bool login(){
    SetConsoleTitle("Login");
    ifstream file;
    User input;
    bool loginSuccess = false ;
    int wrongCount =0;
    string filePath = extractPath() + "\\Login\\UserName.txt";
    string userAccount;
    file.open(filePath.c_str(), ios::in);
    do{
        system("CLS");
        setColor(PURPLE,BLACK);
        printf("Account:");
        cin>>input.account;
        printf("Password:");
        cin>>input.password;

        //判斷帳號密碼的格式
        if(input.account.length() < 6 || input.password.length() < 6){
            printf("Account or Password is wrong format\n");
            system("pause");
            continue;
        }

        if(file.is_open()){

            while(!file.eof()){
                //讀取檔案內容
                file>>userAccount;

                //判斷登入的帳號及密碼是否正確
                if(userAccount == input.account){
                    string userPath = extractPath() + "\\Login\\" + userAccount + ".txt";
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
        printf("Have inputed wrong for %d times\n",wrongCount);
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
    SetConsoleTitle("Register");
    string name,account_Input, password_Input, password_Confirm, identity;
    bool success, permission;
    string filePath = extractPath() + "\\Login\\UserName.txt";
    ofstream file;

    do{
        success = false;
        system("CLS");
        setColor(YELLOW,BLACK);
        //輸入註冊資訊
        printf("Name:");
        cin>>name;
        printf("Your Identity(Student/Teacher):");
        cin>>identity;
        if(identity == "Student")
            permission = STUDENT;
        else if(identity == "Teacher")
            permission = TEACHER;
        else{
            printf("Identity Error\n");
            system("pause");
            continue;
        }
        printf("Account:");
        cin>>account_Input;
        printf("Password:");
        cin>>password_Input;
        //判斷帳號密碼的格式
        if(account_Input.length() < 6 || password_Input.length() < 6){
            printf("Account or Password is wrong format\n");
            system("pause");
            continue;
        }
        system("CLS");
        //確認密碼
        printf("Confirming Password:");
        cin>>password_Confirm;
        if(password_Input != password_Confirm){
            system("CLS");
            printf("Different Password\n");
            system("pause");
            continue;
        }
        system("CLS");
        //寫入註冊成功的資料
        file.open(filePath.c_str(), ios::app);
        if(file.is_open()){
            file<<account_Input<<endl;
            string userFilePath = extractPath() + "\\Login\\" +account_Input + ".txt";
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
    SetConsoleTitle("MainBoard");
    bool inputCorrect = true, exit = false;
    char choose;
    setColor(CYAN,BLACK);
    do{
        system("CLS");
        cout<<"Hello, "<<user.name;
        if(user.permission == TEACHER)
            printf(" ,Teacher\n");
        else
            printf(" ,Studnet\n");

        printf("Function List\n");
        printf("0: Exit\n");
        printf("1: Message Board\n");
        printf("2: Sharing Information\n");
        printf("3: Grouping\n");
        printf("4: Calendar\n");
        printf("5: Rewinding\n");
        if(user.permission == TEACHER)
            printf("6: Teacher-specific function\n");

        printf("Input your choice:");
        cin>>choose;
        choose -= '0';
        inputCorrect = true;

        switch(choose){
            case 0:
                exit = true;
                break;
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
                    teacherRemind();
//                    printf("Teacher-specific function\n");
                else
                    studentRemind();
                //進入提醒頁面
                break;
            case 6:
                system("CLS");
                setColor(DARK_WHITE,BLACK);
                if(user.permission == TEACHER){
                        printf("in\n");
                system("pause");
                    teacherAnswer();

                }else{
                studentAskQuestion();
                }
            default:
                printf("Input Error\n");
                system("pause");
                inputCorrect = false;
                break;


        }
    }while(!inputCorrect || !exit);
}

//留言版功能選擇主介面
void commentMainBoard(){
    SetConsoleTitle("CommentBoard");
    char choose;
    bool chooseCorrect;
    do{
        system("CLS");
        if(user.sensitiveWordCount>TALK)
            printf("You are banned!!\n");

        printf("1: Questioning Board During Class(Anonymous)\n");
        printf("2: Questioning Board\n");
        printf("3: Exit\n");
        printf("Input your choice:");
        cin>>choose;
        choose -= '0';
        chooseCorrect = true;

        switch(choose){

            case 1:
                commentBooard("QuestioningBoardDuringClass(Anonymous)");
                break;
            case 2:
                commentBooard("QuestioningBoard");
                break;
            case 3:
                mainBoard();
                break;
            default:
                printf("Input Error\n");
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
    char choose;
    bool chooseCorrect;
    do{
        system("CLS");
        chooseCorrect = true;
        if(user.sensitiveWordCount>TALK)
            printf("You are banned\n");
        printf("1: Browse all the conversation\n");
        printf("2: Starting new conversation\n");
        printf("3: Exit\n");
        printf("Input your choice:");
        cin>>choose;
        choose -= '0';
        switch(choose){
            case 1:
                //瀏覽帖子列表
                chooseCorrect = false;
                browsePostList(boardName);
                break;
            case 2:
                //開新帖子
                chooseCorrect = false;
                if(boardName == "QuestioningBoardDuringClass(Anonymous)")
                    createPost(boardName, true);
                else
                    createPost(boardName, false);
                break;
            case 3:
                commentMainBoard();
                break;
            default:
                chooseCorrect = false;
                printf("Input Error\n");
                break;

        }

    }while(!chooseCorrect);
}

//瀏覽帖子列表
void browsePostList(string boardName){
    bool chooseCorrect;
    int cur = 0, postNum;
    string postName[10], junk;
    string filePath = extractPath() +"\\" + "CommentBoard" +  "\\" + boardName +"\\postName.txt";
    ifstream file(filePath.c_str(), ios::in);
    if(file.is_open()){
        do{
            system("CLS");
            if(user.sensitiveWordCount>TALK)
                printf("You are banned!!\n");
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
                cout<<postNum <<": " << postName[postNum]<<endl;
                printf("---------------------------------------\n");
            }
            printf("%-20s%-20s%-20s\n", cur==0? "":"Previous Page : Left Bottom", "Returning to Main Board : Up Bottom", file.eof()==true? "":"Next Page : Right Bottom");
            char charChoose;
            charChoose = _getch();
            int intChoose = charChoose - '0';
            if(intChoose>=1 && intChoose<=10)
                //瀏覽帖子
                browsePost(boardName, postName[intChoose]);


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
                        printf("Input Error\n");
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
    string filePath = extractPath() + "\\" + "CommentBoard" + "\\" + boardName + "\\" +postName + ".txt";
    ifstream file(filePath.c_str(), ios::in);
    string comment, commenter;
    bool chooseCorrect;
    int cur=0;
    char choose;
    SetConsoleTitle(postName.c_str());
    if(file.is_open()){
        do
        {

            system("CLS");
            file.clear();
            file.seekg(0, ios::beg);
            if(user.sensitiveWordCount>TALK)
                printf("You are banned!!\n");
            printf("Title:");
            file>>comment;
            cout<<comment<<endl;
            printf("Author:");
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
                printf("Message From:");
                cout<<commenter<<endl;
                printf("---------------------------------------\n");
            }
            printf("%-20s%-20s%-20s%-20s\n", cur==0? "":"Previous Page : Left Bottom ", " --Returning to Main Board : Up Bottom", " --Leave a comment : Down Bottom", file.eof()==true? "":"Next Page : Right Bottom");
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
                    if(boardName == "QuestioningBoardDuringClass(Anonymous)")
                        commentFun(filePath,true);
                    else
                        commentFun(filePath, false);
                    system("pause");
                }

                else
                {
                    printf("You are banned!!\n");
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
                printf("Input Error\n");
                system("pause");
                break;
            }
        }while(!chooseCorrect);
    }

    else{
    chooseCorrect = false;
    printf("The comment does not exist\n");
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
        printf("Input Comment:\n");
        cin>>input;
        //如果沒有敏感字眼的話把留言寫入檔案
        if(!haveSensitiveWord(input)){
            file<<input<<endl;
            if(anonymous)
                file<<"Anonymous"<<endl;
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
    string filePath = extractPath() + "\\CommentBoard\\sensitiveWord.txt";
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
            printf("There are some sensitive word in the sentence\n");
            string userFilePath = extractPath() + "\\Login\\" + user.account + ".txt";
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
    printf("Enter title:\n");
    cin>>title;
    filePath = extractPath() + "\\CommentBoard\\" + boarName + "\\" + title +".txt";
    ofstream file(filePath.c_str(), ios::out);
    string postNamePath = extractPath() + "\\CommentBoard\\" + boarName + "\\postName.txt";
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
                        printf("Repeat Title Name\n");
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
                    file<<"Anonymous"<<endl;
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
