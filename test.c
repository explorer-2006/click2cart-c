#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

void login_page();
void registration_page();
void startShopping();
void loadProducts();
void browseByCategory();
void showOffers();
void viewCart();
void removeFromCart();
void checkout();
void startShopping();

// ---MAIN FUNCTION--- //
int main()
{
    int choice; // user entering choice for login page

    printf("-----------------");
    printf("\n   CLICK2CART\n");
    printf("-----------------");

    printf("\n\nSignup page:\n");
    printf("1. Login\n2. Register\n");

    while (1)
    {
        printf("\nEnter your choice: ");

        // check if scanf successfully read an integer
        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter a valid number (1 or 2)!\n");
            while (getchar() != '\n')
                ; // clear invalid input
            continue;
        }

        // check if choice is valid
        if (choice == 1 || choice == 2)
        {
            break; // valid input → exit loop
        }
        else
        {
            printf("Please enter valid input!!\n");
        }
    }

    if (choice == 1)
    {
        login_page();
    }
    else
    {
        registration_page();
    }

    return 0;
}

// --LOGIN PAGE--- //
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
        getchar();
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

    int attempts = 0;
    while (attempts < 3)
    {
        printf("Enter password: ");
        i = 0;

        while (1)
        {
            ch = getch();
            if (ch == '\r' || ch == '\n')
            {
                if (i == 0)
                {
                    printf("\nPassword cannot be empty!!\n\n");
                    i = -1;
                    break;
                }
                else
                {
                    password[i] = '\0';
                    printf("\n");
                    break;
                }
            }
            else if (ch == 127 || ch == 8) // backspace
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                if (i < (int)sizeof(password) - 1)
                {
                    password[i++] = ch;
                    printf("*");
                }
            }
        }

        if (i == -1)
        {
            continue; // re-ask same attempt if empty password
        }

        if (strcmp(storedPassword, password) != 0)
        {
            attempts++;
            if (attempts < 3)
            {
                printf("Incorrect password. %d attempt(s) left.\n\n", 3 - attempts);
            }
        }
        else
        {
            foundPassword = 1;
            break;
        }
    }

    if (foundPassword == 1)
    {
        printf("Hello %s\n", storedName);
        printf("\nLogin successful! Redirecting to shopping page...\n");
        Sleep(3000);

        loadProducts();
        startShopping();
    }
    else
    {
        printf("Too many failed attempts. Login failed!\n");
    }
}
// ---REGISTRATION PAGE--- //
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

    getchar();

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

// =============== SHOPPING SYSTEM ==================

struct Product
{
    int id;
    char name[50];
    float price;
    int stock;
    char category[30];
    float discount;
};

struct CartItem
{
    struct Product product;
    int quantity;
};

struct Product products[50];
struct CartItem cart[50];
int productCount = 0, cartCount = 0;

void startShopping()
{
   

    int choice;

    printf("\n\n-------------\n");
    printf("  DASHBOARD");
    printf("\n-------------\n\n");

    printf("1. Browse Products by Category\n");
    printf("2. Today's Offers & Discounts\n");
    printf("3. View Cart\n");
    printf("4. Remove from Cart\n");
    printf("5. Checkout & Exit\n");

    do
    {
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter an integer number!!\n");
            getchar();
            continue;
        }
        if (choice > 5 || choice < 1)
        {
            printf("Please enter valid input!!\n");
        }
    } while (choice > 5 || choice < 1);

    switch (choice)
    {
    case 1:
        browseByCategory();
        break;
    case 2:
        showOffers();
        break;
    case 3:
        viewCart();
        break;
    case 4:
        removeFromCart();
        break;
    case 5:
        checkout();
        return;
    default:
        printf("Invalid choice!\n");
    }
}

//---FUNCTION : Load Products ---//
// Purpose : Load products from products.txt
void loadProducts()
{
    FILE *file = fopen("products.txt", "r");

    if (!file)
    {
        printf("Error: could not open products.txt\n");
        //exit(1);
    }

    srand(time(NULL)); // for random discounts

    // Read each line and store product data
    while (fscanf(file, "%d,%[^,],%f,%d,%[^,\n]",
                  &products[productCount].id,
                  products[productCount].name,
                  &products[productCount].price,
                  &products[productCount].stock,
                  products[productCount].category) == 5)
    {
        products[productCount].discount = (rand() % 21) + 10; // random 10–30%
        productCount++;
    }
    fclose(file);
}

// 1. View all categories
void browseByCategory()
{
    char category[20][30];
    int uniqueCount = 0;

    printf("\n\n------------\n");
    printf(" CATEGORIES");
    printf("\n------------\n\n");

    // Collect unique categories
    for (int i = 0; i < productCount; i++)
    {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++)
        {
            if (strcmp(products[i].category, category[j]) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            strcpy(category[uniqueCount], products[i].category);
            printf("%d. %s\n", uniqueCount + 1, category[uniqueCount]);
            uniqueCount++;
        }
    }

    int catChoice;
    do
    {
        printf("\nEnter your choice (Enter 0 to return): ");
        if (scanf("%d", &catChoice) != 1)
        {
            printf("Please enter an integer number!\n");
            while (getchar() != '\n')
                ; // clear input
            continue;
        }
        if (catChoice > uniqueCount || catChoice < 0)
        {
            printf("Please enter a valid input!\n");
        }
    } while (catChoice > uniqueCount || catChoice < 0);

    if (catChoice == 0)
    {
        startShopping();
        return;
    }

    printf("\n\n| Products in %s |\n\n", category[catChoice - 1]);

    // Show all products in that category
    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(products[i].category, category[catChoice - 1]) == 0)
        {
            printf("%d. %s - Rs.%.2f (%.0f%% OFF)\n",
                   products[i].id, products[i].name,
                   products[i].price, products[i].discount);
        }
    }

    // Add to cart section
    int pid, qty;

    while (1)
    {
        int foundInCategory = 0; // reset every time user re-enters

        printf("\nEnter Product ID to add to cart (0 to return): ");
        if (scanf("%d", &pid) != 1)
        {
            printf("Please enter a valid product ID!\n");
            while (getchar() != '\n')
                ; // clear input
            continue;
        }

        if (pid == 0)
        {
            browseByCategory();
        }

        // Check if ID belongs to chosen category
        for (int i = 0; i < productCount; i++)
        {
            if (products[i].id == pid && strcmp(products[i].category, category[catChoice - 1]) == 0)
            {
                foundInCategory = 1;

                printf("Enter Quantity: ");
                if (scanf("%d", &qty) != 1)
                {
                    printf("Invalid quantity!\n");
                    getchar(); // clear invalid input
                    foundInCategory = 0;
                    break;
                }

                // Add to cart
                cart[cartCount].product = products[i];
                cart[cartCount].quantity = qty;
                cartCount++;

                printf("%d x %s added to cart successfully!\n", qty, products[i].name);
                Sleep(1500);

                startShopping();
                return;
            }
        }

        if (!foundInCategory)
        {
            printf("Invalid Product ID for this category! Please try again.\n");
        }
    }
}

// 2. Show today’s offers
void showOffers()
{
     printf("\n----------------");
     printf("\n TODAYS OFFERS\n");
     printf("----------------\n\n");
    for (int i = 0; i < productCount; i = i+3)
    {
        if (products[i].discount >= 20)
            printf("%d. %s - Rs.%.2f (%.0f%% OFF)\n",

                   products[i].id, products[i].name,
                   products[i].price, products[i].discount);
    }
    printf("\n");
    while (1)
    {
        printf("Enter 0 to go back: ");
        int back;
        if (scanf("%d", &back) != 1)
        {
            printf("Please enter integer number!!\n\n");
            getchar();
        }
        else if(back != 0){
            printf("Please enter valid input!!\n\n");
        }
        else{
            startShopping();
        }
    }
}

// 3. View cart
void viewCart()
{
     printf("\n------");
     printf("\n CART\n");
     printf("------\n\n");

    if (cartCount == 0)
    {
        printf("\nYour cart is empty!\n");
        startShopping();
    }
    float total = 0;
  
    for (int i = 0; i < cartCount; i++)
    {
        float priceAfterDiscount = cart[i].product.price * (1 - cart[i].product.discount / 100);
        float subtotal = priceAfterDiscount * cart[i].quantity;
        printf("Product Name: %s\n", cart[i].product.name);
        printf("Product Quantity: %d\n", cart[i].quantity);
        printf("Discount(per product): Rs. %.2f\n", cart[i].product.price*(cart[i].product.discount/100));
        printf("Price after discount: Rs. %.2f\n", priceAfterDiscount);
        printf("Subtotal: Rs. %.2f\n\n", subtotal);



        total += subtotal;
    }
    printf("\n---------------------");
    printf("\n|Total: Rs. %.2f|\n", total);
    printf("---------------------\n");
    while (1)
    {  
         int back;
        printf("Enter 0 to go back: ");
        scanf("%d", &back); 
       
        if (back == 0)
        {
            printf("in condition");
         startShopping();
           
        }
        else{
            printf("Please enter integer number ie 0!!\n\n");
            getchar();
        }
    }


}

// 4. Remove from cart
void removeFromCart()
{
    if (cartCount == 0)
    {
        printf("Cart is empty!\n");
        return;
    }
    int pid;
    printf("Enter Product ID to remove: ");
    scanf("%d", &pid);

    for (int i = 0; i < cartCount; i++)
    {
        if (cart[i].product.id == pid)
        {
            for (int j = i; j < cartCount - 1; j++)
                cart[j] = cart[j + 1];
            cartCount--;
            printf("Removed from cart!\n");
            startShopping();
        }
    }
    printf("Product not found in cart!\n");
}

// 5. Checkout
void checkout()
{
    if (cartCount == 0)
    {
        printf("Cart is empty!\n");
        return;
    }

    float total = 0;
    printf("\n--- Checkout ---\n");
    for (int i = 0; i < cartCount; i++)
    {
        float finalPrice = cart[i].product.price * (1 - cart[i].product.discount / 100);
        total += finalPrice * cart[i].quantity;
    }
    printf("Total amount to pay: Rs.%.2f\n", total);
    printf("Thank you for shopping with Click2Cart!\n");
}

// Shopping menu1