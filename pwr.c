#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

void menu();
void admin_menu();
void user_menu();
void create_account();
void user_display();
void admin_display();
void bill_generation();
void delete ();


struct user
{
    int cnum;
    char password[20];
    char name[20];
    char address[50];
    int phoneno;
} pUser;

struct admin
{
    char adminname[20];
    char password1[20];
} a;

int canum;
char pwd[10];

int main()
{
    menu();

    return 0;
}

void menu()
{
    FILE *fp1;
    int i;

    system("Color D0");

    printf("\n\n\t\t....WELCOME TO NORTH DELHI POWER MANAGEMENT SYSTEM.....\n");

    printf("\n1. Login as ADMIN\n2. Login as USER\n");
    scanf("%d", &i);

    switch (i)
    {
    case 1: // ADMIN LOGIN //

        strcpy(a.adminname, "aditi");
        strcpy(a.password1, "goyal");

        char id[10], p[10], ch;
        int h = 0;

        fp1 = fopen("admin.txt", "wb");

        if (fp1 == NULL)
        {
            printf(" failed to open.");
        }
        else
        {

            fwrite(&a, sizeof(a), 1, fp1);
        }

        printf("\nAdmin Name:");
        scanf("%s", id);

        printf("\nPassword:");
        do
        {
            p[h] = getch();
            if (p[h] != '\r')
            {
                printf("*");
            }
            h++;
        } while (p[h - 1] != '\r');
        p[h - 1] = '\0';

        fclose(fp1);

        fp1 = fopen("admin.txt", "rb");

        while (fread(&a, sizeof(a), 1, fp1) == 1)
        {
            if ((strcmp(id, a.adminname) == 0))
            {

                if (strcmp(p, a.password1) == 0)
                {
                    printf("\n\nLogin Successful !!");
                }
                system("CLS");
                admin_menu();
            }
            else
            {
                printf("\nWrong Password\n");
                menu();
            }
        }
        fclose(fp1);
        break;

    case 2: // USER LOGIN //
        FILE *fp;

        int flag;

        fp = fopen("file.txt", "rb");

        printf("CA Number : ");
        fflush(stdin);
        scanf("%d", &canum);
        fflush(stdin);

        printf("Password  : ");
        scanf("%s", pwd);
        // do
        // {
        //     pwd[h] = getch();
        //     if (pwd[h] != '\r')
        //     {
        //         printf("*");
        //     }
        //     h++;
        // } while (pwd[h - 1] != '\r');

        // pwd[h - 1] = '\0';

        while (fread(&pUser, sizeof(pUser), 1, fp) == 1)
        {
            if (pUser.cnum == canum)
            {

                if (strcmp(pUser.password, pwd) == 0)
                {
                    flag = 1;
                }
                else
                {
                    flag = 0;
                }
            }
        }
        if (flag == 1)
        {
            printf("\nLogin Success!!\n");
            getch();
            user_menu();
        }
        if (flag == 0)
        {

            printf("\ninvalid username or password :( ");
            getch();
            menu();
        }

        fclose(fp);
        break;
    }
}

void create_account()
{
    FILE *fp;
    char c;
    int number = 1;
    int len, i, k = 0, h = 0; //(variables for validation)

    fp = fopen("file.txt", "ab+");
    do
    {

        printf("\nEnter User's Details :-\n\n");
        printf("Enter User's Name   : ");

        do
        {
            scanf("%s", pUser.name);

            len = strlen(pUser.name);

            for (i = 0; i < len; i++)
            {

                if (isalpha(pUser.name[i]) == 0) // i.e. false
                {
                    k = k + 1;
                    break;
                }
                else
                {
                    k = 0;
                }
            }
            if (k != 0)
                printf("wrong input, try again :) ");

        } while (k != 0);

        printf("Enter User's Address: ");
        scanf("%s", pUser.address);

        printf("Choose A Password   : ");
        scanf("%s", pUser.password);
        // do
        // {
        //     pUser.password[h] = getch();
        //     if (pUser.password[h] != '\r')
        //     {
        //         printf("*");
        //     }
        //     h++;
        // } while (pUser.password[h - 1] != '\r');
        // pUser.password[h - 1] = '\0';

        printf("Enter phone no.     : ");
        while (!scanf("%d", &pUser.phoneno))
        {
            printf("Inlvalid data\n");
            printf("Please enter a integer value\n");
            char c;
            while ((c = getchar()) != '\n')
                return;
        }

        pUser.cnum = number;
        printf("\nYour Details has been addedd with CA Number :%d", pUser.cnum);

        fwrite(&pUser, sizeof(pUser), 1, fp);

        number++;

        printf("\nAdd another account? (Y/N): ");
        scanf(" %c", &c);

    } while (c == 'Y' || c == 'y');

    fclose(fp);
    system("CLS");
    admin_menu();
}

void admin_menu()
{
    int i;
    printf("\n\n\t\t  WELLCOME TO ELECTRTICITY BOARD DEPPARTMENT\n\n");

    printf("\t\t********************************************\n");

    printf("\n1....ADD A NEW ACCOUNT\n\n");
    printf("2....DELETE AN ACCOUNT\n\n");
    printf("3....FETCH USER'S DETAILS\n\n");
    printf("4....EXIT\n\n");

    printf("choose an option: ");
    scanf("%d", &i);
    switch (i)
    {
    case 1:
        create_account();
        break;
    case 2:
        delete ();
        break;
    case 3:
        admin_display();
        break;
    case 4:
       menu();
        break;
    // case 5:
    //     menu();
    // }
}}

void user_menu()
{
    int i;
    printf("\n\n\t\t WELLCOME TO ELECTRTICITY BOARD DEPPARTMENT\n\n");

    printf("\t\t********************************************");

    printf("\n1....GENERATE BILL\n\n");
    printf("2....DISPLAY DETAILS\n\n");
    printf("3....EXIT\n\n");

    printf("choose an option: ");
    scanf("%d", &i);

    switch (i)
    {
    case 1:
        bill_generation();
        break;
    case 2:
        user_display();
        break;
    case 3:
        menu();
        break;
    }
}

void user_display()
{
    FILE *fp;

    fp = fopen("file.txt", "rb");

    printf("\n=========================================================\n");

    printf("\n\n\t\t-----Customer Details-----\n");

    if (fp == NULL)
    {

        printf("Cannot open file \n");

        exit(0);
    }
    else
    {
        while ((fread(&pUser, sizeof(pUser), 1, fp) == 1))
        {
            printf("\n\t\t CA no.   : %d", pUser.cnum);
            printf("\n\t\t password : %s", pUser.password);
            printf("\n\t\t Name     : %s", pUser.name);
            printf("\n\t\t Address  : %s", pUser.address);
            printf("\n\t\t phone no.: %d\n\n", pUser.phoneno);
        }
    }
    printf("\n\n\n=========================================================");
    fclose(fp);
    printf("\n\nPress enter to return back ");
    getch();
    user_menu();
}

void admin_display()
{
    FILE *fp;

    fp = fopen("file.txt", "r");

    printf("\n=========================================================\n");

    printf("\n\n\t\t-----Customer Details-----\n");

    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    while ((fread(&pUser, sizeof(pUser), 1, fp) == 1))
    {
        printf("\n\t\t CA no.   : %d", pUser.cnum);
        printf("\n\t\t password : %s", pUser.password);
        printf("\n\t\t Name     : %s", pUser.name);
        printf("\n\t\t Address  : %s", pUser.address);
        printf("\n\t\t phone no.: %d\n\n", pUser.phoneno);
    }
    printf("\n\n\n=========================================================\n");

    fclose(fp);
   
    printf("\n\nPress enter to return back \n\n");
    getch() ;
    admin_menu();
}

void bill_generation()
{
    FILE *fp;
    int cid, conu, i;
    float chg, fixedchg = 0, gramt, netamt;
    char cuname[25];
    int a;

    printf("\n\n\t\t WELCOME TO ELECTRICITY BOARD DEPARTMENT\n\n");

    for (i = 0; i < 70; i++)
    {
        printf("=");
    }
    printf("\n\n\t\t\tCHARGES AS PER UNITS\n\n\n");
    printf("\tUpto 100 Units   .............................. =Rs 1.20/Unit     |\n\n");
    printf("\t100 To 300 Units .............................. =Rs 1.50/Unit     |\n\n");
    printf("\t300 To 500 Units .............................. =Rs 1.80/Unit     |\n\n");
    printf("\t500 To 700 Units .............................. =Rs 2.00/Unit     |\n\n");
    printf("\t700 To 900 Units .............................. =Rs 2.40/Unit     |\n\n");
    printf("\t900+ Units .................................... =Rs 3.00/Unit     |\n\n");

    for (i = 0; i < 70; i++)
    {
        printf("=");
    }

    printf("\n\nInput the unit consumed by the customer : ");
    while (!scanf("%d", &conu))
    {
        printf("Inlvalid data\n");
        printf("Please enter a integer value\n");
        char c;
        while ((c = getchar()) != '\n')
            return;
    }
    fflush(stdin);

    if (conu < 100)
        gramt = conu * 1.20;
    else if (conu >= 100 && conu < 300)
        gramt = 100 * 1.20 + (conu - 100) * 1.50;
    else if (conu >= 300 && conu < 500)
        gramt = 100 * 1.20 + 200 * 1.50 + (conu - 300) * 1.80;
    else if (conu >= 500 && conu < 700)
        gramt = 100 * 1.20 + 200 * 1.50 + 200 * 1.80 + (conu - 500) * 2.00;
    else if (conu >= 700 && conu < 900)
        gramt = 100 * 1.20 + 200 * 1.50 + 200 * 1.80 + 200 * 2.00 + (conu - 700) * 2.40;
    else if (conu > 900)
        gramt = 100 * 1.20 + 200 * 1.50 + 200 * 1.80 + 200 * 2.40 + (conu - 900) * 3.00;

    if (gramt > 200)
        fixedchg = gramt * 15 / 100.0;
    netamt = gramt + fixedchg;
    if (netamt < 100)
        netamt = 100;

    cid = canum;
    time_t t = time(NULL);
    printf("\n\t\tELECTRICITY BILL\n\n");
    printf("\nCA No.                              :   %d\n", cid);
    printf("\nUnits Consumed                      :   %d\n", conu);
    printf("\nFixed Amount                        :%8.2f\n", fixedchg);
    printf("\nNet Amount Paid By the Customer     : %8.2f\n", netamt);
    printf("\nBill date and time is               :   %s\n\n", ctime(&t));
    

    getch();
    user_menu();
}

void delete ()
{

    FILE *fp;
    FILE *fp1;
    int deleteCANo, a;

    printf("\t\t\t\t=======DELETE THE RECORD=======\n\n\n");
    fp = fopen("file.txt", "rb");
    fp1 = fopen("temp.txt", "wb");
    printf("\t\t\t\tEnter the ca no : ");
    scanf("%d", &deleteCANo);
    if (fp == NULL)
    {
        printf("can't open file\n");
        exit(0);
    }

    while (fread(&pUser, sizeof(pUser), 1, fp) == 1)
    {
        if (deleteCANo != pUser.cnum)
        {
            fwrite(&pUser, sizeof(pUser), 1, fp1);
        }

        if (deleteCANo == pUser.cnum)
        {
            a = 1;
        }
    }
    if (a == 1)
    {
        printf("\n\t\t\t\tRecord deleted successfully\n");
    }
    if (a != 1)
    {
        printf("\n\t\t\t\tRecord not found\n");
    }
    fclose(fp);
    fclose(fp1);
    remove("file.txt");
    rename("temp.txt", "file.txt");
    printf("\n\nPress enter to return back\n\n");
    getch();
    admin_menu();
}


