#include "header.h"

void mainMenu(struct User u)
{   
    int option;
    struct Record r;

    system("clear");
    printf("\n\n\t\t========================= ATM ==========================\n");
    printf("\n\t\t***** Feel free to choose one of the options below *****\n");
    printf("\n\t\t\t\t[1]- Create a new account\n");
    printf("\n\t\t\t\t[2]- Update account information\n");
    printf("\n\t\t\t\t[3]- Check accounts\n");
    printf("\n\t\t\t\t[4]- Check list of owned account\n");
    printf("\n\t\t\t\t[5]- Make Transaction\n");
    printf("\n\t\t\t\t[6]- Remove existing account\n");
    printf("\n\t\t\t\t[7]- Transfer ownership\n");
    printf("\n\t\t\t\t[8]- Exit\n");
    printf("\n\t\t\t\tYour choise : ");

    while (scanf("%d", &option) != 1)
    {
        system("afplay /System/Library/Sounds/Ping.aiff");
        printf(ANSI_COLOR_RED"\n\t\t******* Insert a valid operation! ******\n"ANSI_COLOR_RESET);
        // Vider le flux d'entrée pour éviter une boucle infinie
        while (getchar() != '\n');
        printf("\n\t\t\t\tYour choice : ");
    }

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        updateAcc();
        break;
    case 3:
        checkDet();
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        transact();
        break;
    case 6:
        removeAcc();
        break;
    case 7:
        transferAcc();
        break;
    case 8:
        printf(ANSI_COLOR_GREEN"\n\n\t\t*** Thanks for using ATM! ***\n\n"ANSI_COLOR_RESET);
        exit(1);
        break;
    default:
        system("afplay /System/Library/Sounds/Ping.aiff");
        printf(ANSI_COLOR_RED"\n\n\t\tInvalid operation!\n"ANSI_COLOR_RESET);
    }
}


void initMenu(struct User *u)
{
    int r = 0;
    int option;
    system("clear");
    printf("\t\t==================== ATM ====================\n");
    printf("\n\t\t******* Feel free to login / register *******\n");
    printf("\n\t\t\t\t[1]- Login\n");
    printf("\n\t\t\t\t[2]- Register\n");
    printf("\n\t\t\t\t[3]- Exit\n");
    printf("\n\t\t\t\tYour choice : ");
    while (!r)
    {
        if (scanf("%d", &option) != 1)
        {
            system("afplay /System/Library/Sounds/Ping.aiff");
            printf(ANSI_COLOR_RED"\n\t\t******* Insert a valid operation! ******\n"ANSI_COLOR_RESET);
            printf("\n\t\tYour choise : ");
            // Vider le flux d'entrée pour éviter une boucle infinie
            while (getchar() != '\n');
            continue;
        }
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            encryptPassword(u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                system("afplay /System/Library/Sounds/Pop.aiff");
                printf("\n\n\t\t\t******* Password Match! Welcome %s ******" , u->name);
            }
            else
            {
                system("afplay /System/Library/Sounds/Ping.aiff");
                printf(ANSI_COLOR_RED"\n\t\t******** Wrong password or User Name *********\n"ANSI_COLOR_RESET);
                stayOrReturnInit();
            }
            r = 1;
            break;
        case 2:
            registration(u);
            r = 1;
            break;
        case 3:
            printf(ANSI_COLOR_GREEN"\n\n\t\t*********** Thanks for using ATM! ***********\n\n"ANSI_COLOR_RESET);
            exit(1);
            break;
        default:
            system("afplay /System/Library/Sounds/Ping.aiff");
            printf(ANSI_COLOR_RED"\n\t\t******* Insert a valid operation! ******\n"ANSI_COLOR_RESET);
        }
    }
}


int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
