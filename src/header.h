#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char userName[100];
    int accountId;
    struct Date deposit;
    char country[100];
    int phone;
    double balance;
    char accountType[10];
    struct Date withdraw;
}r,cr,tr,ch,rm;

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void initMenu(struct User *u);
void checkAllAccounts(struct User u);
void registration(struct User *u);
void updateAcc(void);
void transact(void);
void checkDet(void);
void removeAcc(void);
void transferAcc(void);
void stayOrReturnMain();
void stayOrReturnInit();
void message();