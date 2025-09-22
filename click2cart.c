#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

void login_page();
void registration_page();

int main()
{
    int choice; // user entering choice for login page

    printf("-----------------");
    printf("\n   CLICK2CART\n");
    printf("-----------------");

    printf("\n\nSignup page:\n");
    printf("1. Login\n2. Register\n");

    do
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice); // choice for login or register
        getchar();
        if (choice != 1 && choice != 2)
        {
            printf("please enter valid input!!\n");
        }
    } while (choice != 1 && choice != 2);

    if (choice == 1)
    {
        login_page();
    }
    else
    {
        registration_page();
    };

    printf("cart ");

    return 0;
}

void login_page()
{ // code for login page

    int foundEmail = 0; // match found
    int foundPassword = 0;
    int len;
    char emailId[30];                                         // email id entered by user
    char storedName[30], storedEmail[30], storedPassword[30]; // name and email address from the buffer will be stored in these variables
    char password[30];
    int ch;
    int i = 0;
    char pwd;

    printf("\n\n\n---------------------");
    printf("\nWELCOME TO LOGIN PAGE\n");
    printf("---------------------\n\n\n");

    do
    {
        printf("Enter your Email ID (space and case sensitive): ");
        fgets(emailId, sizeof(emailId), stdin);
        len = strlen(emailId); // length of the email id entered
        if (len <= 1)
        {
            printf("please enter valid input!!!\n\n");
        }
    } while (len <= 1);

    if (len > 0 && emailId[len - 1] == '\n')
    { // solution for input buffer
        emailId[len - 1] = '\0';
    }

    FILE *pFile = fopen("userData.txt", "r"); // reading data from the file and storing in the variable buffer
    char buffer[1024] = {0};
    if (pFile == NULL)
    {
        printf("error reading the data");
        return;
    }
    while (fgets(buffer, sizeof(buffer), pFile) != NULL)
    {                         // while loop while run till end of the data and then will return null and it will read data line by line
        len = strlen(buffer); // length of buffer

        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
        sscanf(buffer, "%[^:]:%[^:]:%s", storedName, storedEmail, storedPassword); // subsets of the string buffer and storing that data
        if (strcmp(emailId, storedEmail) == 0)
        { // if match is found it will return 0 and break will exit the loop
            foundEmail = 1;
            break;
        }
    }
    if (foundEmail != 1)
    {
        printf("user not found\n"); // if user doesnt exist break code
        return;
    }

    do
    { // keep asking until password entered

        printf("enter the password: ");
        i = 0; // reset index everytime loop runs

        while (1)
        {
            ch = getch();
            if (ch == '\r' || ch == '\n')
            { // if user press enter
                if (i == 0)
                {
                    printf("\npassword cannot be empty\n\n");
                    i = -1;
                }
                password[i] = '\0';
                printf("\n");

                break;
            }
            else if (ch == 127 || ch == 8)
            { // ascii for backspace or delete

                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else if (i < (int)sizeof(password) - 1)
            {
                password[i++] = ch;
                printf("*");
            }
        }
        if (i == -1)
        {
            continue;
        }

        if ((strcmp(password, storedPassword) != 0))
        {
            printf("password doesnt match\n\n");
        }
        else
        {
            foundPassword = 1;
        }
    } while (strcmp(password, storedPassword) != 0);

    if (foundEmail == 1 && foundPassword == 1)
    { // if match is found
        printf("welcome %s\n", storedName);
    }
}

void registration_page()
{ // code for registration page
    int len;
    int userExists = 0;
    char Rfname[30]; // R in all the variables stand for registered
    char Rlname[30];
    char Rname[30];
    char Remail[30];
    char Rpassword[30];
    char Rdata[100];
    char storedName[30], storedEmail[30], storedPassword[30];

    printf("\n\n\n----------------------------");
    printf("\nWELCOME TO REGISTRATION PAGE\n");
    printf("----------------------------\n\n\n");

    do
    { // code for first name
        printf("enter your First name: ");
        fgets(Rfname, sizeof(Rfname), stdin);

        if (strlen(Rfname) == 1)
        {
            printf("First name cannot be empty\n\n");
        }
        else
        {
            Rfname[strlen(Rfname) - 1] = '\0';
        }

    } while (strlen(Rfname) == 1);

    do
    { // code for last name
        printf("enter your Last name: ");
        fgets(Rlname, sizeof(Rlname), stdin);

        if (strlen(Rlname) == 1)
        {
            printf("Last name cannot be empty\n\n");
        }
        else
        {
            Rlname[strlen(Rlname) - 1] = '\0';
        }

    } while (strlen(Rlname) == 1);

    do
    { // code for email
        printf("Enter your Email: ");
        fgets(Remail, sizeof(Remail), stdin);

        if (strlen(Remail) == 1)
        {
            printf("Email cannot be empty\n\n");
        }
        else
        {
            Remail[strlen(Remail) - 1] = '\0';
        }

    } while (strlen(Remail) == 1);

    do
    {
        printf("Enter your password: "); // code for password
        fgets(Rpassword, sizeof(Rpassword), stdin);

        if (strlen(Rpassword) == 1)
        {
            printf("password cannot be empty\n\n");
        }
        else
        {
            Rpassword[strlen(Rpassword) - 1] = '\0';
        }

    } while (strlen(Rpassword) == 1);

    snprintf(Rname, sizeof(Rname), "%s %s", Rfname, Rlname);              // joining  first and last name
    snprintf(Rdata, sizeof(Rdata), "%s:%s:%s", Rname, Remail, Rpassword); // joining all the info in variable Rdata

    FILE *pFile = fopen("userData.txt", "r");

    if (pFile == NULL)
    {
        printf("error writing the data");
        return;
    }
    else
    {

        char buffer[1024] = {0};
        while (fgets(buffer, sizeof(buffer), pFile) != NULL)
        {                         // while loop while run till end of the data and then will return null and it will read data line by line
            len = strlen(buffer); // length of buffer

            if (buffer[len - 1] == '\n')
            {
                buffer[len - 1] = '\0';
            }
            sscanf(buffer, "%[^:]:%[^:]:%s", storedName, storedEmail, storedPassword); // subsets of the string buffer and storing that data
            if (strcmp(storedEmail, Remail) == 0)
            { // code to check if user already exists
                printf("user already exist");
                userExists = 1;
                break;
            }
        }
        fclose(pFile);
    }

    if (!userExists)
    { // if user doesnt exist, data is registered in userdata file

        FILE *pFile = fopen("userData.txt", "a");
        if (pFile == NULL)
        {
            printf("error writing the data");
            return;
        }
        fprintf(pFile, "%s\n", Rdata);
        fclose(pFile);
        printf("\nRegistration successfull!! you can now login\n");
        login_page();
    }
}
