#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

// ---LOGIN AND REGISTRATION PAGE--- //

//Loads products from file
void login_page();

//Displays login page and allows user to login
void registration_page();

//Starts shopping after successful login
void startShopping(); 

// ---MAIN FUNCTION--- //
int main() {
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
            while (getchar() != '\n'); // clear invalid input
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
    } else
    {
        registration_page();
    }

    printf("\nWelcome to Cart\n");
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
        /* --- FUNCTION: startShopping ---

        Purpose : Allows user to browse and select products

        Features:
        1. Displays category-wise products
        2. Lets user add products to cart
        3. Calculates total bill and shows summary
        */
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
        printf("\nRegistration successful!! Redirecting to shopping page...\n");
        startShopping(); 

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

//---FUNCTION : Load Products ---//
//Purpose : Load products from products.txt
void loadProducts() 
{
    FILE *file = fopen("products.txt", "r");
    if (!file)
     {
        printf("Error: could not open products.txt\n");
        exit(1);
    }

    srand(time(NULL)); // for random discounts

     // Read each line and store product data
    while (fscanf(file, "%d,%[^,],%f,%d,%[^,\n]", 
                  &products[productCount].id,
                  products[productCount].name,
                  &products[productCount].price,
                  &products[productCount].stock,
                  products[productCount].category) == 5) {
        products[productCount].discount = (rand() % 21) + 10; // random 10–30%
        productCount++;
    }
    fclose(file);
}

//1. View all categories
void browseByCategory()
 {
    char category[20][30];//category stores unique categories name 
    int uniqueCount = 0;//count of different  categories 

    printf("\n--- Categories ---\n");
    for (int i = 0; i < productCount; i++) 
    {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++)
            if (strcmp(products[i].category, category[j]) == 0)
                found = 1;
        if (!found) 
        {
            strcpy(category[uniqueCount], products[i].category);
            printf("%d. %s\n", uniqueCount + 1, category[uniqueCount]);
            uniqueCount++;
        }
    }

    int catChoice;
    printf("Choose a category (0 to return): ");
    scanf("%d", &catChoice);
    getchar();
    if (catChoice < 1 || catChoice > uniqueCount) return;

    printf("\nProducts in %s:\n", category[catChoice - 1]);
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].category, category[catChoice - 1]) == 0) 
        {
            printf("%d. %s - Rs.%.2f (%.0f%% OFF)\n",
                   products[i].id, products[i].name,
                   products[i].price, products[i].discount);
        }
    }

    int pid, qty;
    printf("Enter Product ID to add to cart (0 to skip): ");
    scanf("%d", &pid);
    if (pid == 0) 
    return;
    printf("Quantity: ");
    scanf("%d", &qty);

    for (int i = 0; i < productCount; i++) 
    {
        if (products[i].id == pid) {
            cart[cartCount].product = products[i];
            cart[cartCount].quantity = qty;
            cartCount++;
            printf("%d x %s added to cart!\n", qty, products[i].name);
            return;
        }
    }
    printf("Invalid Product ID!\n");
}

//2. Show today’s offers
void showOffers() {
    printf("\n--- Today's Offers ---\n");
    for (int i = 0; i < productCount; i++)
     {
        if (products[i].discount >= 20)
            printf("%d. %s - Rs.%.2f (%.0f%% OFF)\n",
                   products[i].id, products[i].name,
                   products[i].price, products[i].discount);
    }
}

//3. View cart
void viewandManagecart() {
    if (cartCount == 0) 
    {
        printf("\nYour cart is empty!\n");
        return;
    }
    float total = 0;
    printf("\n--- Your Cart ---\n");
    for (int i = 0; i < cartCount; i++)
     {
        float priceAfterDiscount = cart[i].product.price * (1 - cart[i].product.discount / 100);
        float subtotal = priceAfterDiscount * cart[i].quantity;
        printf("%d x %s - Rs.%.2f each = Rs.%.2f\n",
               cart[i].quantity, cart[i].product.name,
               priceAfterDiscount, subtotal);
        total += subtotal;
    }
    printf("Total: Rs.%.2f\n", total);
}

//4. Remove from cart
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
            return;
        }
    }
    printf("Product not found in cart!\n");
}

//5. Checkout
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

// Shopping menu
void startShopping() 
{
    loadProducts();

    int choice;
    while (1) {
        printf("\n===== SHOPPING MENU =====\n");
        printf("1. Browse Products by Category\n");
        printf("2. Today's Offers & Discounts\n");
        printf("3. View Cart\n");
        printf("4. Remove from Cart\n");
        printf("5. Checkout & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) 
        {
            case 1: browseByCategory(); 
                break;
            case 2: showOffers(); 
                break;
            case 3: viewCart();
                 break;
            case 4: removeFromCart(); 
                break;
            case 5: checkout(); 
                return;
            default: printf("Invalid choice!\n");
        }
    }
}
