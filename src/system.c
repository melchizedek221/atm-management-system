#include "header.h"

#define MAX_LEN 100
#define FILENAME_SIZE 1024
#define MAX_LINE 2048

const char *RECORDS = "./data/records.txt";
const char *USERS = "./data/users.txt";

int main_exit;

//Read line of a file pointed to ptr
int getAccountFromFile(FILE *ptr, struct Record *r, struct User *u)
{
    struct Record cr;

    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
		          &u->id,
                  &r->id,
                  r->userName,
                  &r->accountId,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->balance,
                  r->accountType)!= EOF;
}

//Write line of a file pointed to ptr
void saveAccountToFile(FILE *ptr, struct Record r, struct User u)
{
    struct Record cr;
    
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            u.id,
            r.id,
	        r.userName,
            r.accountId,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.balance,
            r.accountType);
}

//Write struct user in file
void saveUsersToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %s %s\n\n",
	        r.id,
            u.name,
            u.password);
}

void success(struct User u)
{
    int option;
    printf("\n\n\t\t✔ Success!\n\n");
invalid:
    printf("\n\t\tEnter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("\n\t\tInsert a valid operation!\n");
        goto invalid;
    }
}

//Read all lines in a file and give de index of last line
int lastId(FILE* file) {
    char line[100];
    int num_lines = 0;

    rewind(file); // Rewind file pointer to beginning of file

    while (fgets(line, 100, file) != NULL) {
        // Check if line is empty (only contains whitespace)
        if (strspn(line, " \t\n") == strlen(line)) {
            continue;  // Ignore empty lines
        }
        num_lines++;
    }

    rewind(file); // Rewind file pointer to beginning of file
    return num_lines;
}

// function to check if the user name already exists
void checkUsername(struct Record cr) {
    
    FILE *fp = fopen(RECORDS, "r");
   
    struct User u;
    struct Record r;

    while (getAccountFromFile(fp, &r, &u))
    {
        if (cr.id==r.id)
        {
            /* code */
            printf("\n\t\t*** ✖This id already exists! ***\n");
                add_invalid:
            printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
            scanf("%d",&main_exit);
            
            system("clear"); 
            if (main_exit==1)
                initMenu(&u);
            else if(main_exit==0)
            exit(1);
    else
        {
            printf("\n\t\t************ Invalid! **************\a");
            goto add_invalid;
        }
        }
        

    }
    fclose(fp);
}

//Create a new account / register
void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    
    FILE *pf = fopen(RECORDS, "a+");
    FILE *pf1 = fopen(USERS, "a+");

    system("clear");

    u.id=lastId(pf);

    printf("\n\n\t\t================== New Record ==================\n");
    printf("\n\n\t\tEnter today's date(mm/dd/yyyy) : ");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\n\n\t\tEnter your name : ");
    scanf("%s", r.userName);
    printf("\n\n\t\tEnter your Id : ");
    scanf("%d", &r.id);
    printf("\n\n\t\tEnter your account number : ");
    scanf("%d", &r.accountId);
    printf("\n\n\t\tEnter your country : ");
    scanf("%s", r.country);
    printf("\n\n\t\tEnter your phone number : ");
    scanf("%d", &r.phone);
    printf("\n\n\t\tEnter amount to deposit : $");
    scanf("%lf", &r.balance);
    printf("\n\n\t\tChoose the type of account :\n\n\t\t\t-> saving\n\n\t\t\t-> current\n\n\t\t\t-> fixed01(for 1 year)\n\n\t\t\t-> fixed02(for 2 years)\n\n\t\t\t-> fixed03(for 3 years)\n\n\n\t\t\tEnter your choice : ");
    scanf("%s", r.accountType);

   
    saveAccountToFile(pf, r, u);

    fclose(pf);
    fclose(pf1);

    success(u);
}

//check accounts with same id
void checkAllAccounts(struct User u)
{
    struct Record r;
    struct User cu;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\n\t\t******** Check Accounts *********\n");       
    printf("\n\n\t\t Your username : ");
    scanf("%s", cu.name);
    printf("\n\n\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, &r, &u))
    {

        if (strcmp(cu.name, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountId,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.balance,
                   r.accountType);
        }else{
                printf("\t\t No match ");

        }
    }
    fclose(pf);
    success(u);
}

//Create a new account / register
void registration(struct User *u)
{
    struct Record r;
    
    FILE *pf = fopen(RECORDS, "a+");
    FILE *pf1 = fopen(USERS, "a+");

    system("clear");

    u->id=lastId(pf);

    printf("\n\n\t\t================== New Record ==================\n");
    printf("\n\n\t\tEnter today's date(mm/dd/yyyy) : ");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\n\n\t\tEnter your name : ");
    scanf("%s", r.userName);
    printf("\n\n\t\tEnter your username : ");
    scanf("%s", u->name);
    printf("\n\n\t\tEnter your user ID : ");
    scanf("%d", &cr.id);
    checkUsername(cr);

    r.id=cr.id;
    printf("\n\n\t\tEnter the account number : ");
    scanf("%d", &r.accountId);
    printf("\n\n\t\tEnter the country : ");
    scanf("%s", r.country);
    printf("\n\n\t\tEnter the phone number : ");
    scanf("%d", &r.phone);
    printf("\n\n\t\tEnter amount to deposit : $");
    scanf("%lf", &r.balance);
    printf("\n\n\t\tChoose the type of account :\n\n\t\t\t-> saving\n\n\t\t\t-> current\n\n\t\t\t-> fixed01(for 1 year)\n\n\t\t\t-> fixed02(for 2 years)\n\n\t\t\t-> fixed03(for 3 years)\n\n\n\t\t\tEnter your choice : ");
    scanf("%s", r.accountType);
    printf("\n\n\t\tEnter your password : ");
    scanf("%s", u->password);

    saveAccountToFile(pf, r, *u);
    saveUsersToFile(pf1, *u, r);

    fclose(pf);
    fclose(pf1);

    success(*u);
}

//Update Account information
void updateAcc(void)
{
    int choice,test=0;
    FILE *old,*newrec;
    old=fopen(RECORDS,"r");
    newrec=fopen("new.txt","w");
    struct User u;

        if (old == NULL) {
        printf("Error while opening the file.");
        return;
    }
        if (newrec == NULL) {
        printf("Error while opening the file.");
        return;
    }

    system("clear");
    printf("\n\t\t******** Update Account Information *********\n");       
    printf("\n\n\tYour account number : ");
    scanf("%d",&cr.accountId);
    
    while(getAccountFromFile(old, &r, &u))
    {
        if (r.accountId==cr.accountId)
        {   
            test=1;
            
            system("clear");
            printf("\n\t\t******** Update Account Information *********\n");       
            printf("\n\n\t\tWhich information do you want to change?\n\n\t\t\t1. Country\n\n\t\t\t2. Phone ");
            printf("\n\n\n\t\t\tEnter your choice : ");
            scanf("%d",&choice);
            
            system("clear");
            printf("\n\t\t******** Update Account Information *********\n");                
            if(choice==1)
                {
                    printf("\n\n\t\tEnter the new country : ");
                scanf("%s",cr.country);
                fprintf(newrec, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    u.id,
                    r.id,
	                r.userName,
                    r.accountId,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    cr.country,
                    r.phone,
                    r.balance,
                    r.accountType);

                success(u);
                }
            else if(choice==2)
                {
                printf("\n\n\t\tEnter the new phone number:");
                scanf("%d",&cr.phone);
                fprintf(newrec, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    u.id,
                    r.id,
	                r.userName,
                    r.accountId,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    cr.phone,
                    r.balance,
                    r.accountType);                
                     
                success(u);
                }
            else
                {
                    fprintf(newrec, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    u.id,
                    r.id,
	                r.userName,
                    r.accountId,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.balance,
                    r.accountType);  
                }  
        }
    }

    if(test==0) 
    {  
        printf("\n\t\tRecord not found!!\a\a\a\n");
        remove("new.txt");
        stayOrReturnMain();
    }
fclose(old);
fclose(newrec);
remove(RECORDS);
rename("new.txt", RECORDS);

}

//Transactions
void transact(void)

{   int choice,test=0;
    FILE *old,*newrec;
    old=fopen(RECORDS,"r");
    newrec=fopen("new.txt","w");
    struct Record tr;
    struct User u;

    printf("\n\t\t*********** Transaction ************");       
    printf("\n\n\t\tEnter the account number of the customer : ");
    scanf("%d",&tr.accountId);
    while (getAccountFromFile(old, &r, &u))
   {

            if(r.accountId==tr.accountId)
            {   test=1;
                if(strcasecmp(r.accountType,"fixed01")==0 || strcasecmp(r.accountType,"fixed02")==0 || strcasecmp(r.accountType,"fixed03")==0)
                {
                    printf("\a\a\a\n\n\t\tYOU CANNOT DEPOSIT OR WITHDRAW CASH IN FIXED ACCOUNTS!!!!!");

                stayOrReturnMain();
                }

                printf("\n\n\t\tDo you want to\n\n\t\t\t1.Deposit\n\n\t\t\t2.Withdraw?\n\n\t\t\tEnter your choice : ");
                scanf("%d",&choice);
                if (choice==1)
                {
                    printf("\n\n\t\tEnter the amount you want to deposit :$ ");
                    scanf("%lf",&tr.balance);

                    r.balance+=tr.balance;

                fprintf(newrec, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    u.id,
                    r.id,
	                r.userName,
                    r.accountId,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.balance,
                    r.accountType);                   
                 success(u);
                }
                else
                {
                    printf("\n\n\t\tEnter the amount you want to withdraw : $ ");
                    scanf("%lf",&tr.balance);

                    r.balance-=tr.balance;
                fprintf(newrec, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    u.id,
                    r.id,
	                r.userName,
                    r.accountId,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.balance,
                    r.accountType); 
                    
                     success(u);                 
                }

            }
            else
            {
                fprintf(newrec, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    u.id,
                    r.id,
	                r.userName,
                    r.accountId,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.balance,
                    r.accountType);             }
   }
   if(test==0)
   {
       printf("\n\n\t\tRecord not found!!\n");
       stayOrReturnMain();
   }else
    {
        printf("\n\n\t\tInvalid!");
    stayOrReturnMain();
    }
fclose(old);
fclose(newrec);
remove(RECORDS);
rename("new.txt", RECORDS);

}

//Check the details of existing accounts
void checkDet(void)
{
    FILE *ptr;
    int test=0,rate;
    int choice;
    float time;
    float intrst;
    struct User u;
    struct Record ch;


    ptr=fopen(RECORDS,"r");

    system("clear");
    printf("\n\t\t******** Check the details of existing accounts *********\n");       
    
        printf("\n\t\tEnter the account number : ");
        scanf("%d",&ch.accountId);

        while (getAccountFromFile(ptr, &r, &u))
        {
            if(r.accountId==ch.accountId)
            {
                test=1;

                printf("\n\n\t\tAccount NO. :%d \n\n\t\tName :%s \n\n\t\tDOB :%d/%d/%d \n\n\t\tCountry :%s \n\n\t\tPhone number :%d \n\n\t\tType Of Account :%s \n\n\t\tAmount deposited:$ %f",
                    r.accountId,
	                r.userName,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.accountType,
                    r.balance);

                if(strcmp(r.accountType,"fixed1")==0)
                    {
                        time=1.0;
                        rate=9;
                        intrst=(time * r.balance *rate)/100;
                        printf("\n\n\n\t\tYou will get $%.2f as interest on %d/%d/%d",intrst,r.deposit.month,r.deposit.day,r.deposit.year+1);
                    }
                else if(strcmp(r.accountType,"fixed2")==0)
                    {
                        time=2.0;
                        rate=11;
                        intrst=(time * r.balance *rate)/100;
                        printf("\n\n\n\t\tYou will get $%.2f as interest on %d/%d/%d",intrst,r.deposit.month,r.deposit.day,r.deposit.year+2);

                    }
                else if(strcmp(r.accountType,"fixed3")==0)
                    {
                        time=3.0;
                        rate=13;
                        intrst=(time * r.balance *rate)/100;
                        printf("\n\n\n\t\tYou will get $%.2f as interest on %d/%d/%d",intrst,r.deposit.month,r.deposit.day,r.deposit.year+3);

                    }
                 else if(strcmp(r.accountType,"saving")==0)
                    {
                        time=(1.0/12.0);
                        rate=8;
                        intrst=(time * r.balance *rate)/100;
                        printf("\n\n\n\t\tYou will get $%.2f as interest on %d of every month",intrst,r.deposit.day);

                     }
                 else if(strcmp(r.accountType,"current")==0)
                    {

                        printf("\n\n\n\t\tYou will get no interest\a\a");

                     }

            }
        }
    
    fclose(ptr);
     if(test==0)
        {   
            printf("\n\n\t\tRecord not found!!\n");
            stayOrReturnMain();
        }
    else
        {printf("\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);}
        if (main_exit==1)
        {
            mainMenu(u);
        }

        else
           {
            exit(1);
            }

}

//Remove existing account
void removeAcc(void)
{
    struct User u;
    struct Record rm;
    struct Record r;
    struct User ru;

    FILE *old, *newrec, *user, *newuser;
    int test=0;
    old=fopen(RECORDS,"r");
    newrec=fopen("new.txt","w");
    user=fopen(USERS,"r");
    newuser=fopen("new2.txt","w");

    system("clear");
    printf("\n\t\t********** Remove Existing Account *8*********\n");       

    printf("\n\n\t\tEnter the account number of the customer you want to delete : ");
    scanf("%d",&rm.accountId);

    printf("\n\n\t\tEnter the username of the customer you want to delete : ");
    scanf("%s",ru.name);
    
    while (getAccountFromFile(old, &r, &u)) 
    {
        if(r.accountId!=rm.accountId)
        {
            fprintf(newrec, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    u.id,
                    r.id,
                    r.userName,
                    r.accountId,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.balance,
                    r.accountType); 

        }

        fscanf(user, "%d %s %s", &r.id, u.name, u.password);
        if (strcmp(ru.name, u.name)!=0)
        {
            fprintf(newuser, "%d %s %s \n\n",
                    r.id,
                    u.name,
                    u.password);  
        }
        else
        {
            test++;
            success(u);
        }

    }
    fclose(old);
    fclose(user);
    fclose(newrec);
    fclose(newuser);

    remove(RECORDS);
    remove(USERS);
    rename("new.txt",RECORDS);
    rename("new2.txt",USERS);

    if(test==0)
    {
        printf("\nRecord not found!!\a\a\a");
       stayOrReturnMain();
    }else
        {
            printf("\n\n\t\tInvalid!\a");
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        if (main_exit==1){
            mainMenu(u);
        }
        else{
            exit(1);}
    }
}

//Tranfert account
void transferAcc(void){

    int choice,test=0;
    FILE *old,*newrec, *user, *message;
    old=fopen(RECORDS,"r");
    newrec=fopen(USERS,"r");
    newrec=fopen("new.txt","w");
    message=fopen("message.txt","w");

    struct User u;
    struct User cu;
    struct User bu;



        if (old == NULL) {
        printf("Error while opening the file.");
        return;
    }
        if (newrec == NULL) {
        printf("Error while opening the file.");
        return;
    }

    system("clear");
    printf("\n\t\t********** Change Account Owner ***********\n");       
    printf("\n\n\t\tAccount number : ");
    scanf("%d",&cr.accountId);
 
    while(getAccountFromFile(old, &r, &u))
    {
        if (r.accountId==cr.accountId) 
        
        {   test=1;
            
            system("clear");
            printf("\n\t\t******** Change Account Owner *********\n");       
            printf("\n\n\n\t\t\tEnter the name of reciever : ");
            scanf("%s",cr.userName);

            {
                fprintf(newrec, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    u.id,
                    r.id,
	                cr.userName,
                    r.accountId,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.balance,
                    r.accountType);


            }
            
            success(u);
            fprintf(message, "You just owned a new account (Account Number :  %d) ", cr.accountId);

        }
        else
                fprintf(newrec, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    u.id,
                    r.id,
	                r.userName,
                    r.accountId,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.balance,
                    r.accountType);    

    }
    fclose(message);
    fclose(old);
    fclose(newrec);
    remove(RECORDS);
    rename("new.txt",RECORDS);

if(test==0)
{ 
    printf("\nRecord not found!!\n");
    stayOrReturnMain();
            
}

}

void message() {

    FILE *fichier = fopen("messages.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    char message[100];
    
    printf(" Messages :\n");
    while (fgets(message, sizeof(message), fichier)) {
        printf("- %s", message);
    }
    
    fclose(fichier);
}

void stayOrReturnInit(){
    struct User u;
    edit_invalid:
              printf("\n\t\tEnter 0 to return to main menu and 1 to Exit:");
              scanf("%d",&main_exit);
               
                 if (main_exit==0)

                    initMenu(&u);
                else if (main_exit==1)
                    exit(1);
                else
                    {printf("\n\t\t************ Invalid! ***************\a");
                    goto edit_invalid;}
}

void stayOrReturnMain(){
    struct User u;
    edit_invalid:
              printf("\n\t\tEnter 0 to return to main menu and 1 to Exit : ");
              scanf("%d",&main_exit);
               
                 if (main_exit==0)

                    mainMenu(u);
                else if (main_exit==1)
                    exit(2);
                else
                    {printf("\n\t\t************ Invalid! ***************\a");
                    goto edit_invalid;}
}