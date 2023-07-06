#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define ACCOUNT_FILE "accounts.txt"
#define TIME 0



//In this commit I add the part of my program that related to game and all things about 2048 except showing ranks.




typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    int score;
} User;

int winOrNo;
int num_users = 0;
User users[MAX_USERS];
char usename12[MAX_USERNAME_LEN];

void load_accounts() {
    FILE *file = fopen(ACCOUNT_FILE, "r");
    if (!file) {
        printf("Error opening the file for reading.\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%s %s %d", users[num_users].username, users[num_users].password, &users[num_users].score) == 3) {
        num_users++;
    }

    fclose(file);
}

void save_accounts() {
    FILE *file = fopen(ACCOUNT_FILE, "w");
    if (!file) {
        printf("Error opening the file for writing.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_users; i++) {
        fprintf(file, "%s %s %d\n", users[i].username, users[i].password, users[i].score);
    }
    fclose(file);
}


int create_account(char username[100],char password[100]) {
    if (num_users >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        sleep(TIME);
        return;
    }

    User new_user;
    strcpy(new_user.username,username);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(new_user.username, users[i].username) == 0) {
            printf("Username already exists. Please choose a different username.\n");
            sleep(TIME);
            return 0;
        }
    }
    strcpy(usename12, new_user.username);

    strcpy(new_user.password,password);
    new_user.score = 0;

    users[num_users++] = new_user;
    save_accounts();

    printf("\nAccount created successfully.\n\n");
    sleep(TIME);
    return 1;
}

int login(char username[100],char password[100]) {
    int x=0;
    int y=0;
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0)  {
            y++;
            if (strcmp(password, users[i].password) == 0)
                {x=1; strcpy(usename12, username);  return x;}
            else
                {x=10; return x;}
        } }
    if (y==0)
         {x=11; return x;}
    return 0;

}

int score;
void initializeBoard(int SIZE,int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void printBoard(int SIZE,int board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j]==0) printf("%6s","-");
            else printf("%6d", board[i][j]);
        }
        printf("\n");
    }
    printf("\n\nScore: %d\n\n", score);
}

bool isGameOver(int SIZE,int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (board[i][j] == board[i][j + 1]) {
                return false;
            }
        }
    }

    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == board[i + 1][j]) {
                return false;
            }
        }
    }

    return true;
}

void generateNewTile(int SIZE,int board[SIZE][SIZE]) {
    int emptyCells[SIZE * SIZE][2];
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                emptyCells[count][0] = i;
                emptyCells[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0) {
        int index = rand() % count;
        int row = emptyCells[index][0];
        int col = emptyCells[index][1];
        board[row][col] = (rand() % 2 + 1) * 2;
    }
}

void moveTilesLeft(int SIZE,int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int index = 0;

        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                board[i][index] = board[i][j];
                if (j != index) {
                    board[i][j] = 0;
                }
                index++;
            }
        }
    }
}

void mergeTilesLeft(int SIZE,int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (board[i][j] == board[i][j + 1]) {
                     if (board[i][j]==1024){
                    if(winOrNo==0){
                        printf("/nYOU WIN, But you can continue the game./n");
                        winOrNo++;
                    }
                score += board[i][j] * 2;
                board[i][j] *= 2;
                board[i][j + 1] = 0;

                }

            }
        }
    }

}

void moveTilesUp(int SIZE,int board[SIZE][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        int index = 0;

        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] != 0) {
                board[index][j] = board[i][j];
                if (i != index) {
                    board[i][j] = 0;
                }
                index++;
            }
        }
    }
}

void mergeTilesUp(int SIZE,int board[SIZE][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE - 1; i++) {
            if (board[i][j] == board[i + 1][j]) {
                    if (board[i][j]==1024){
                    if(winOrNo==0){
                        printf("YOU WIN, But you can continue the game.");
                        winOrNo++;
                    }
                }
                score += board[i][j] * 2;
                board[i][j] *= 2;
                board[i + 1][j] = 0;


            }
        }
    }
}

void moveTilesDown(int SIZE,int board[SIZE][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        int index = SIZE - 1;

        for (int i = SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                board[index][j] = board[i][j];
                if (i != index) {
                    board[i][j] = 0;
                }
                index--;
            }
        }
    }
}

void mergeTilesDown(int SIZE,int board[SIZE][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        for (int i = SIZE - 1; i > 0; i--) {
                if (board[i][j]==1024){
                    if(winOrNo==0){
                        printf("YOU WIN, But you can continue the game.");
                        winOrNo++;
                    }
                }
            if (board[i][j] == board[i - 1][j]) {
                score += board[i][j] * 2;
                board[i][j] *= 2;
                board[i - 1][j] = 0;


            }
        }
    }
}

void moveTilesRight(int SIZE,int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int index = SIZE - 1;

        for (int j = SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                board[i][index] = board[i][j];
                if (j != index) {
                    board[i][j] = 0;
                }
                index--;
            }
        }
    }
}

void mergeTilesRight(int SIZE,int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - 1; j > 0; j--) {
            if (board[i][j] == board[i][j - 1]) {
                    if (board[i][j]==1024){
                    if(winOrNo==0){
                        printf("YOU WIN, But you can continue the game.");
                        winOrNo++;
                    }
                }
                score += board[i][j] * 2;
                board[i][j] *= 2;
                board[i][j - 1] = 0;



            }
        }
    }
}

void settile(int satr,int sotoon,int value,int SIZE,int board[SIZE][SIZE],int guestOrNot){
    int value2=value;
    int baghimande=0;
    int m=1;
    while(value2!=1){
        baghimande=value2%2;
        if(baghimande!=0){
            baghimande=1;
            break;
        }
        value2/=2;
    }
    if (satr>SIZE || sotoon>SIZE){
        printf("coordinate out of range!\nTry again!\n\n");
        m=0;
    }
    else{
            if (board[satr-1][sotoon-1]==0){
            if (baghimande==0){
                board[satr-1][sotoon-1]=value;
                m=1;
            }
            else{
                printf("invalid value!\nTry again!\n\n");
                sleep(TIME);
                m= 0;
            }
    }

    else{
        printf("cell is not empty!\nTry again!\n\n");
        sleep(TIME);
       m=0;
    }
}

}

void playGame(int guestOrNot,int SIZE,int board[SIZE][SIZE]) {
    initializeBoard(SIZE,board);
    score = 0;
    generateNewTile(SIZE,board);
    generateNewTile(SIZE,board);
    int backornot=0;
    winOrNo=0;
    while (!isGameOver(SIZE,board)) {
        sleep(TIME);
        printBoard(SIZE,board);
        sleep(TIME);
        printf("Enter 'down/up/left/right' \nor you can enter 'exit' for going to the main menu \nor you can enter 'put<i><j><value>' mabey for some cheat:)\n\n");
        sleep(TIME);
        char account2_info[200];
        fgets(account2_info, sizeof(account2_info), stdin);
        account2_info[strcspn(account2_info, "\n")] = '\0';

        char action1[10];
        char action2[10];
        char action3[10];
        char action4[10];
        char action5[10];
        char action6[10];

        sscanf(account2_info, "%2s", action1);
        sscanf(account2_info, "%4s", action2);
        sscanf(account2_info, "%4s", action3);
        sscanf(account2_info, "%5s", action4);
        sscanf(account2_info, "%3s", action5);
        sscanf(account2_info, "%4s", action6);

        int satr=0,sotoon=0,value=0;

            if(strcmp(action1,"up")==0){
                moveTilesUp(SIZE,board);
                mergeTilesUp(SIZE,board);
                moveTilesUp(SIZE,board);
            }

            else if(strcmp(action2,"left")==0){
                moveTilesLeft(SIZE,board);
                mergeTilesLeft(SIZE,board);
                moveTilesLeft(SIZE,board);
            }

            else if(strcmp(action3,"down")==0){
                moveTilesDown(SIZE,board);
                mergeTilesDown(SIZE,board);
                moveTilesDown(SIZE,board);
            }

            else if(strcmp(action4,"right")==0){
                moveTilesRight(SIZE,board);
                mergeTilesRight(SIZE,board);
                moveTilesRight(SIZE,board);
            }

            else if(strcmp(action5,"put")==0){
                sscanf(account2_info, "put %d %d %d", &satr, &sotoon, &value);
                int m=0;
                settile(satr,sotoon,value,SIZE,board,guestOrNot);

            }
            else if(strcmp(action6,"exit")==0){
                StartGame(guestOrNot);
            }
            else{
                printf("invalid command!.Try again.\n\n");
                sleep(TIME);
                continue;

            }

        generateNewTile(SIZE,board);
        if (backornot!=0){
            break;
        }


    }

    if (backornot!=0){
        return 0;
    }


    else {
    printf("Game Over! Final Score: %d\n\n", score);
    sleep(TIME);
}}

int startgame2(int guestOrNot){

        int m=0;
        while (m==0){
        sleep(TIME);
        printf("Menu:\n");
        sleep(TIME);
        printf("1. Start Game:\nTo start the game, just enter 'start<size>'\n\n");
        sleep(TIME);
        printf("2. Show Score Board:\nTo see the score board, enter 'scoreboard'\n\n");
        sleep(TIME);
        printf("3. Logout:\nTo logout from your account Or perhaps as a guest just go back to the previous menu, enter 'logout'\n\n");
        sleep(TIME);
        printf("Enter your choice: ");
        sleep(TIME);
        char account2_info[200];
        fgets(account2_info, sizeof(account2_info), stdin);
        account2_info[strcspn(account2_info, "\n")] = '\0';
        char action[10];
        sscanf(account2_info, "%5s", action);
        int SIZE=0;
            if((strcmp(action, "start") == 0)){
                sscanf(account2_info, "start %d", &SIZE);
                if (SIZE<3)
                    {
                    SIZE=0;
                    printf("invalid size, size must be bigger than 2!\n\n");
                    }
                else{
                    m++;
                    int board[SIZE][SIZE];
                    playGame(guestOrNot,SIZE,board);
                }

            }

            else if((strcmp(action, "score") == 0)){
                //show score board
                printf("\nMenu:\n");
                sleep(TIME);
                printf("1. Show My Score:\nTo see your score, just enter 'myrank'!\n\n");
                sleep(TIME);
                printf("2. Back To Last Menu:\nThat is easy, just enter 'back'\n\n");
                int choice2=0;
                printf("Enter your choice: ");
                char account3_info[200];
                fgets(account3_info, sizeof(account3_info), stdin);
                account3_info[strcspn(account3_info, "\n")] = '\0';
                char action1[10];
                sscanf(account3_info, "%4s", action1);

                while (strcasecmp(action1, "myra")!=0 && strcasecmp(action1, "back")!=0){
                printf("invalid command!.Try again.\n");
                printf("\nMenu:\n");
                sleep(TIME);
                printf("1. Show My Score:\nTo see your score, just enter 'myrank'!\n\n");
                sleep(TIME);
                printf("2. Back To Last Menu:\nThat is easy, just enter 'back'\n\n");
                int choice2=0;
                printf("Enter your choice: ");
                char account3_info[200];
                fgets(account3_info, sizeof(account3_info), stdin);
                account3_info[strcspn(account3_info, "\n")] = '\0';
                char action1[10];
                sscanf(account3_info, "%4s", action1);
                }

                if(strcasecmp(action1, "myra")==0){
                        if (guestOrNot==0){
                            //show myrank
                            printf("\nMenu:\n");
                            sleep(TIME);
                            printf("1. Back To Last Menu:\nThat is easy, just enter 'back'\n\n");
                            int choice4=0;
                            printf("Enter your choice: ");
                            char account4_info[200];
                            fgets(account4_info, sizeof(account4_info), stdin);
                            account4_info[strcspn(account4_info, "\n")] = '\0';
                            char action2[10];
                            sscanf(account4_info, "%4s", action2);
                            while (strcasecmp(action2, "back")!=0){
                                printf("invalid command!.Try again.\n\n");
                                printf("Menu:\n");
                                sleep(TIME);
                                printf("1. Back To Last Menu:\nThat is easy, just enter 'back'\n\n");
                                printf("Enter your choice: ");
                                char account4_info[200];
                                fgets(account4_info, sizeof(account4_info), stdin);
                                account4_info[strcspn(account4_info, "\n")] = '\0';
                                char action1[10];
                                sscanf(account4_info, "%4s", action2);
                            }

                            startgame2(guestOrNot);
                            m++;

                        }

                        else
                        {
                            printf("you are guest!\n");
                            printf("\nMenu:\n");
                            sleep(TIME);
                            printf("1. Back To Last Menu:\nThat is easy, just enter 'back'\n\n");
                            printf("Enter your choice: ");
                            char account4_info[200];
                            fgets(account4_info, sizeof(account4_info), stdin);
                            account4_info[strcspn(account4_info, "\n")] = '\0';
                            char action2[10];
                            sscanf(account4_info, "%4s", action2);
                            while (strcasecmp(action2, "back")!=0){
                                printf("invalid command!.Try again.\n\n");
                                printf("Menu:\n");
                                sleep(TIME);
                                printf("1. Back To Last Menu:\nThat is easy, just enter 'back'\n\n");

                                printf("Enter your choice: ");
                                char account4_info[200];
                                fgets(account4_info, sizeof(account4_info), stdin);
                                account4_info[strcspn(account4_info, "\n")] = '\0';
                                char action2[10];
                                sscanf(account4_info, "%4s", action2);
                            }
                            startgame2(guestOrNot);
                            m++;


                        }
                }
                    else if(strcasecmp(action1, "back")==0){
                        startgame2(guestOrNot);
                        m++;
                    }
                }

            else if(strcasecmp(action, "logou")==0){
                printf("LogOut!\n\n");
                StartGame();
                m++;
            }
            else{
                printf("invalid command!.Try again.\n\n");
                sleep(TIME);
        }
    }
}



int StartGame(){
    int readyOrNot=0;
    int choice;
    int guestOrNot=0;
    printf("Welcome to the game!\n\n");
    do {

        sleep(TIME);
        printf("Menu:\n");
        sleep(TIME);
        printf("1. Create Account:\nTo create an account, enter 'signup<username><password>'\n\n");
        sleep(TIME);
        printf("2. Login:\nTo log in, enter 'login<username><password>'\n\n");
        sleep(TIME);
        printf("3. Guest:\nTo enter as a guest, just enter 'guest'!\n\n");
        sleep(TIME);
        printf("Enter your choice: ");
        sleep(TIME);
        char account_info[200];
        fgets(account_info, sizeof(account_info), stdin);
        account_info[strcspn(account_info, "\n")] = '\0';
        char action[10];
        sscanf(account_info, "%6s", action);
        int c=0;
        guestOrNot=0;
            if (strcmp(action, "signup") == 0){
                char username[100];
                char password[100];
                sscanf(account_info, "signup %s %s", username, password);
                if (create_account(username,password)){{readyOrNot++;}}}
                else if(strcmp(action, "login<") == 0){
                char username[100];
                char password[100];
                sscanf(account_info, "login %s %s", username, password);
                c=login(username,password);
                if (c==1) {
                    printf("Login successful.\n\n");sleep(TIME);readyOrNot++;
                } else if(c==10){
                    printf("password incorrect!\n\n"); sleep(TIME);}
                  else if(c==11){
                    printf("username not found!\n\n"); sleep(TIME);}
            }
            else if (strcmp(action, "guest") == 0){
                guestOrNot++;
                printf("Ok so you play as a guest.\n\n");
                sleep(TIME);
                readyOrNot++;
        }
            else{
                printf("invalid command!.Try again.\n\n");
            }

    }while(readyOrNot==0);
    startgame2(guestOrNot);
}


int main() {
    fopen(ACCOUNT_FILE, "a");
    load_accounts();
    int logout=1;
    while(1)
    StartGame();

    return 0;
}


