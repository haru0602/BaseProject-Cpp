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
//�T������
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

//����
enum Id{
    STUDENT = 0,
    TEACHER = 1
};

//�ϥΪ̸�Ƶ��c
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

//�ϥΪ̸��, �i�Ω�U�ӥ\�त��ܨϥΪ̸��
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



//�}�l�D����
void loginBoard(){
    SetConsoleTitle("�n�J/���U");
    string ans, goToRegister;
    bool loginSuccess;
    printf("Welcome!!");

    do{
        system("CLS");
        printf("�n�J[Y\\N]:");
        cin>>ans;
        loginSuccess = false;
        //�P�_��J�����T��
        if(ans == "Y" || ans == "y"){
            loginSuccess = login();
            //���~��J���ƶW�L3����߰ݬO�_�n���U
            if(!loginSuccess){
                system("CLS");
                printf("���~��J���ƶW�L3��\n");
                printf("�O�_�n�i����U[Y\\N]:");
                cin>>goToRegister;
                if(goToRegister == "Y" || goToRegister == "y")
                    break;
                else
                    exit(0);
            }

        }

        else if(ans != "N" && ans != "n"){
            printf("��J���~\n");
            system("pause");
            continue;
        }

    }while(ans != "N" && ans != "n" && ans != "Y" && ans != "y");

    while(!loginSuccess &&ans != "N" || ans != "n" && ans != "Y" && ans != "y"){
        system("CLS");
        printf("���U[Y\\N]:");
        cin>>ans;

        //�P�_��J���T��
        if(ans == "Y" || ans == "y"){
            regisiter();
            loginSuccess = login();
        }

        else if(ans != "N" && ans != "n"){
            printf("��J���~\n");
            system("pause");
            continue;
        }

    }
    if(loginSuccess)
        mainBoard();

}

//�n�J����
bool login(){
    SetConsoleTitle("�n�J");
    ifstream file;
    User input;
    bool loginSuccess = false ;
    int wrongCount =0;
    string filePath = extractPath() + "\\�n�J\\UserName.txt";
    string userAccount;
    file.open(filePath.c_str(), ios::in);
    do{
        system("CLS");
        setColor(PURPLE,BLACK);
        printf("�b��:");
        cin>>input.account;
        printf("�K�X:");
        cin>>input.password;

        //�P�_�b���K�X���榡
        if(input.account.length() < 6 || input.password.length() < 6){
            printf("�b���αK�X�榡���~\n");
            system("pause");
            continue;
        }

        if(file.is_open()){

            while(!file.eof()){
                //Ū���ɮפ��e
                file>>userAccount;

                //�P�_�n�J���b���αK�X�O�_���T
                if(userAccount == input.account){
                    string userPath = extractPath() + "\\�n�J\\" + userAccount + ".txt";
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
        printf("�w���~��J%d��\n",wrongCount);
        system("pause");
        //���m�ɮ׫���
        file.clear();
        file.seekg(0, ios::beg);
    }while(!loginSuccess && wrongCount<3);

    file.close();
    setColor(WHITE,BLACK);
    return loginSuccess;
}

//���U����
void regisiter(){
    SetConsoleTitle("���U");
    string name,account_Input, password_Input, password_Confirm, identity;
    bool success, permission;
    string filePath = extractPath() + "\\�n�J\\UserName.txt";
    ofstream file;

    do{
        success = false;
        system("CLS");
        setColor(YELLOW,BLACK);
        //��J���U��T
        printf("�m�W:");
        cin>>name;
        printf("����(�ǥ�/�Ѯv):");
        cin>>identity;
        if(identity == "�ǥ�")
            permission = STUDENT;
        else if(identity == "�Ѯv")
            permission = TEACHER;
        else{
            printf("�������~\n");
            system("pause");
            continue;
        }
        printf("�b��:");
        cin>>account_Input;
        printf("�K�X:");
        cin>>password_Input;
        //�P�_�b���K�X���榡
        if(account_Input.length() < 6 || password_Input.length() < 6){
            printf("�b���αK�X�榡���~\n");
            system("pause");
            continue;
        }
        system("CLS");
        //�T�{�K�X
        printf("�T�{�K�X:");
        cin>>password_Confirm;
        if(password_Input != password_Confirm){
            system("CLS");
            printf("�K�X���ۦP\n");
            system("pause");
            continue;
        }
        system("CLS");
        //�g�J���U���\�����
        file.open(filePath.c_str(), ios::app);
        if(file.is_open()){
            file<<account_Input<<endl;
            string userFilePath = extractPath() + "\\�n�J\\" +account_Input + ".txt";
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

//�\��D����
void mainBoard(){
    SetConsoleTitle("�D����");
    bool inputCorrect = true;
    int choose;
    setColor(CYAN,BLACK);
    do{
        system("CLS");
        cout<<"�A�n, "<<user.name;
        if(user.permission == TEACHER)
            printf("�Ѯv\n");
        else
            printf("�P��\n");

        printf("�\\��C��\n");
        printf("1: �d����\n");
        printf("2: �귽����\n");
        printf("3: ���ե\\��\n");
        printf("4: ��ƾ�\n");
        printf("5: ��������\n");
        if(user.permission == TEACHER)
            printf("6:  �Ѯv�M�Υ\\��\n");

        printf("��J�\\��N��:");
        cin>>choose;
        inputCorrect = true;

        switch(choose){
            case 1:
                commentMainBoard();
                break;
            case 2:
                //�i�J�귽����
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
                //�i�J���ե\��
                break;
            case 4:
                system("CLS");
                setColor(RED,BLACK);
                studentCalendar();
                //�i�J��ƾ�
                break;
            case 5:
                system("CLS");
                setColor(GREEN,BLACK);
                if(user.permission == TEACHER)
                    //teacherRemind();
                    printf("�Юv�������\\��\n");
                else
                    studentRemind();
                //�i�J��������
                break;
            case 6:
                system("CLS");
                setColor(DARK_WHITE,BLACK);
                if(user.permission == TEACHER){
                    //�i�J�Ѯv�M�Υ\��
                    teacherAnswer();
                    break;
                }
            default:
                printf("��J���~\n");
                system("pause");
                inputCorrect = false;
                break;


        }
    }while(!inputCorrect);
}

//�d�����\���ܥD����
void commentMainBoard(){
    SetConsoleTitle("�d�����D����");
    int choose;
    bool chooseCorrect;
    do{
        system("CLS");
        if(user.sensitiveWordCount>TALK)
            printf("�A�w�Q�T��!!\n");
        printf("1: �W�ҵo�ݪ��]�ΦW�^\n");
        printf("2: �o�ݪ�\n");
        printf("��J�����N��:");
        cin>>choose;
        chooseCorrect = true;

        switch(choose){
            case 1:
                commentBooard("�W�ҵo�ݪ�");
                break;
            case 2:
                commentBooard("�o�ݪ�");
                break;
            case KEY_UP:
                mainBoard();
                break;
            default:
                printf("��J���~\n");
                chooseCorrect = false;
                system("pause");
                break;
        }

    }while(!chooseCorrect);

}


//Ū���{�b�Ҧb���a�I
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

//�d�����\���ܤ���
void commentBooard(string boardName){
    SetConsoleTitle(boardName.c_str());
    int choose;
    bool chooseCorrect;
    do{
        system("CLS");
        chooseCorrect = true;
        if(user.sensitiveWordCount>TALK)
            printf("�A�w�Q�T��!!\n");
        printf("1: �s�����l\n");
        printf("2: �}�s���l\n");
        printf("��J�\\��N��:");
        cin>>choose;
        switch(choose){
            case 1:
                //�s�����l�C��
                chooseCorrect = false;
                browsePostList(boardName);
                break;
            case 2:
                //�}�s���l
                chooseCorrect = false;
                if(boardName == "�W�ҵo�ݪ�")
                    createPost(boardName, true);
                else
                    createPost(boardName, false);
                break;
            case KEY_UP:
                commentMainBoard();
                break;
            default:
                chooseCorrect = false;
                printf("��J���~\n");
                break;

        }

    }while(!chooseCorrect);
}

//�s�����l�C��
void browsePostList(string boardName){
    bool chooseCorrect;
    int cur = 0, postNum;
    string postName[10], junk;
    string filePath = extractPath() +"\\" + "�d����" +  "\\" + boardName +"\\postName.txt";
    ifstream file(filePath.c_str(), ios::in);
    if(file.is_open()){
        do{
            system("CLS");
            if(user.sensitiveWordCount>TALK)
                printf("�A�w�Q�T��!!\n");
            chooseCorrect = true;
            file.clear();
            file.seekg(0, ios::beg);
            //���ɮ׫��Ц^��Q�n����m
            for(int i =0; i<cur;i++)
                file>>junk;

            //�C���u���10�ө��l
            for(int i = 0, postNum = 0; i<10&&!file.eof(); i++, postNum++){
                file>>postName[postNum];
                if(file.eof())break;
                cout<<postNum+1 <<": " << postName[postNum]<<endl;
                printf("---------------------------------------\n");
            }
            printf("%-20s%-20s%-20s\n", cur==0? "":"�W�@��:��V�䥪", "��^:��V��W", file.eof()==true? "":"�U�@��:��V��k");
            char charChoose;
            charChoose = _getch();
            int intChoose = charChoose - '0';
            if(intChoose>=1 && intChoose<=10)
                //�s�����l
                browsePost(boardName, postName[--intChoose]);


            else{
                //�P�_��V��
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
                        printf("��J���~\n");
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

//�s�����l���e
void browsePost(string boardName,string postName){
    string filePath = extractPath() + "\\" + "�d����" + "\\" + boardName + "\\" +postName + ".txt";
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
                printf("�A�w�Q�T��!!\n");
            printf("���D:");
            file>>comment;
            cout<<comment<<endl;
            printf("�@��:");
            file>>commenter;
            cout<<commenter<<endl;
            chooseCorrect = true;

            string junk;
            //���ɮ׫��Ц^��Q�n����m
            for(int i =0; i<cur; i++)
                file>>junk;

            printf("---------------------------------------\n");
            //�C���u���10�ӯd��
            for(int i = 0, postNum = 0; i<10&&!file.eof(); i++, postNum++)
            {
                file>>comment;
                if(file.eof())break;
                cout<<comment<<endl;
                file>>commenter;
                printf("�d���H:");
                cout<<commenter<<endl;
                printf("---------------------------------------\n");
            }
            printf("%-20s%-20s%-20s%-20s\n", cur==0? "":"�W�@��:��V�䥪", "��^:��V��W", "�d��:��V��U", file.eof()==true? "":"�U�@��:��V��k");
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
                    //�d��
                    if(boardName == "�W�ҵo�ݪ�")
                        commentFun(filePath,true);
                    else
                        commentFun(filePath, false);
                    system("pause");
                }

                else
                {
                    printf("�A�w�Q�T��!!\n");
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
                printf("��J���~\n");
                system("pause");
                break;
            }
        }while(!chooseCorrect);
    }

    else{
    chooseCorrect = false;
    printf("���F���s�b\n");
    system("pause");
    browsePostList(boardName);
    }
    file.close();


}

//�d���\��
void commentFun(string filePath, bool anonymous){
    ofstream file(filePath.c_str(), ios::app);
    string input;
    if(file.is_open()){
        system("CLS");
        printf("�п�J�d��:\n");
        cin>>input;
        //�p�G�S���ӷP�r�����ܧ�d���g�J�ɮ�
        if(!haveSensitiveWord(input)){
            file<<input<<endl;
            if(anonymous)
                file<<"�ΦW"<<endl;
            else
                file<<user.name<<endl;
        }

    }
    file.close();
}

//�ˬd�ӷP�r��
bool haveSensitiveWord(string statment){
    vector<string> sensitiveWord ;
    string tmp = statment, word;
    string filePath = extractPath() + "\\�d����\\sensitiveWord.txt";
    ifstream file(filePath.c_str(), ios::in);
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    bool haveWord = false;
    if(file.is_open()){
        //Ū���Ҧ��ӷP�r��
        while(!file.eof()){
            file>>word;
            sensitiveWord.push_back(word);
        }
    }
    for(int i =0; i < sensitiveWord.size(); i++){
            //�M��ӷP�r��
        if(statment.find(sensitiveWord[i].c_str()) != string::npos || tmp.find(sensitiveWord[i].c_str()) != string::npos){
            //�p�d�����ӷP�r��, ��s�ϥΪ̸��
            user.sensitiveWordCount++;
            system("CLS");
            printf("�y�l�t���ӷP�r��\n");
            string userFilePath = extractPath() + "\\�n�J\\" + user.account + ".txt";
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
    printf("��J���D:\n");
    cin>>title;
    filePath = extractPath() + "\\�d����\\" + boarName + "\\" + title +".txt";
    ofstream file(filePath.c_str(), ios::out);
    string postNamePath = extractPath() + "\\�d����\\" + boarName + "\\postName.txt";
    ifstream inputPostName(postNamePath.c_str(), ios::in);
    ofstream outputPostName(postNamePath.c_str(), ios::app);
    string file_Input_Post_Name;
    bool postNameRepeat = false;
    if(file.is_open()){
        //�ˬd�ӷP�r��
        if(!haveSensitiveWord(title)){
            if(inputPostName.is_open()){
                //�ˬd���D�O����
                while(!inputPostName.eof()){
                    inputPostName>>file_Input_Post_Name;
                    if(file_Input_Post_Name == title){
                        postNameRepeat = true;
                        printf("���l���D����\n");
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
                    file<<"�ΦW"<<endl;
                else
                    file<<user.name<<endl;
                //��s�w�гy�����l
                if(outputPostName.is_open())
                    outputPostName<<title<<endl;

        }

    }
    file.close();
    outputPostName.close();

}
