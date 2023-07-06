#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define ACCOUNT_FILE "accounts.txt"
#define TIME 0



//In this commit I add the part of my program that related to menu2.




typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    int score;
} User;

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
                    //go to the game
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


