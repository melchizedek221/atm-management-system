#include "header.h"

void mainMenu(struct User u)
{   
    int option;
    struct Record r;

    system("clear");
    printf("\n\n\t\t=========================== ATM ============================\n");
    printf("\n\t\t******* Feel free to choose one of the options below *******\n");
    printf("\n\t\t\t\t[1]- Create a new account\n");
    printf("\n\t\t\t\t[2]- Update account information\n");
    printf("\n\t\t\t\t[3]- Check accounts\n");
    printf("\n\t\t\t\t[4]- Check list of owned account\n");
    printf("\n\t\t\t\t[5]- Make Transaction\n");
    printf("\n\t\t\t\t[6]- Remove existing account\n");
    printf("\n\t\t\t\t[7]- Transfer ownership\n");
    printf("\n\t\t\t\t[8]- Exit\n");
    printf("\n\t\t\t\tYour choise : ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        // student TODO : add your **Update account information** function
        // here
       updateAcc();
       
    break;

    case 3:
        // student TODO : add your **Check the details of existing accounts** function
        // here
        checkDet();
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        // student TODO : add your **Make transaction** function
        // here
        transact();
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        // here
        removeAcc();

        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        // here
        transferAcc();
        break;

    case 8:
         printf(ANSI_COLOR_GREEN"\n\n\t\t*** Thanks for using ATM! ***\n\n"ANSI_COLOR_RESET);

        exit(1);
        break;

    default:
        printf(ANSI_COLOR_RED"\n\n\t\tInvalid operation!\n"ANSI_COLOR_RESET);
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
    system("clear");
    //system("color F13");
    printf("\t\t==================== ATM ====================\n");
    printf("\n\t\t******* Feel free to login / register *******\n");
    printf("\n\t\t\t\t[1]- Login\n");
    printf("\n\t\t\t\t[2]- Register\n");
    printf("\n\t\t\t\t[3]- Exit\n");
    printf("\n\t\t\t\tYour choice : ");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            encryptPassword(u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                printf(ANSI_COLOR_GREEN"\n\n\t\t\t******* Password Match! Welcome %s ******" , u->name, ANSI_COLOR_RESET);

            }
            else
            {
                printf(ANSI_COLOR_RED"\n\t\t******** Wrong password or User Name *********\n"ANSI_COLOR_RESET);
                stayOrReturnInit();

            }
            r = 1;
            break;
        case 2:
            // student TODO : add your **Registration** function
            // here
            registration(u);
            r = 1;
            break;

        case 3:
            printf(ANSI_COLOR_GREEN"\n\n\t\t*********** Thanks for using ATM! ***********\n\n"ANSI_COLOR_RESET);

            exit(1);
            break;
        default:
            printf(ANSI_COLOR_RED"\n\t\t*** Insert a valid operation! ***\n"ANSI_COLOR_RESET);
        }
    }
};

int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
