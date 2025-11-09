#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define RESET "\033[0m"

void login_page();
void registration_page();
void startShopping();
void loadProducts();
void browseByCategory();
void showOffers();
void viewAndManageCart();
void checkout();
void generate_invoice(char name[], float subtotal, float discount, float total, char payment_mode[], char address[]);
float offers(float total);

// ---MAIN FUNCTION--- //
int main()
{
    int choice; // user entering choice for login page

    printf("-----------------");
    printf(YELLOW "\n   CLICK2CART\n" RESET);
    printf("-----------------");

    printf(GREEN "\n\nSignup page:\n" RESET);
    printf(CYAN "1." RESET "Login\n" CYAN "2." RESET "Register\n");

    while (1)
    {
        printf(CYAN "\nEnter your choice: " RESET);

        // check if scanf successfully read an integer
        if (scanf("%d", &choice) != 1)
        {
            printf(RED "Please enter a valid number (1 or 2)!\n" RESET);
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
            printf(RED "Please enter valid input!!\n" RESET);
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
    printf(YELLOW "\nWELCOME TO LOGIN PAGE\n" RESET);
    printf("---------------------\n\n\n");

    do
    {
        getchar();
        printf(CYAN "Enter your Email ID (space and case sensitive): " RESET);
        fgets(emailId, sizeof(emailId), stdin);
        len = strlen(emailId); // length of the email id entered
        if (len <= 1)
        {
            printf(RED "please enter valid input!!!\n\n" RESET);
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
        printf(RED "error reading the data" RESET);
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
        printf(RED "user not found\n" RESET); // if user doesnt exist break code
        return;
    }

    int attempts = 0;
    while (attempts < 3)
    {
        printf(CYAN "Enter password: " RESET);
        i = 0;

        while (1)
        {
            ch = getch();
            if (ch == '\r' || ch == '\n')
            {
                if (i == 0)
                {
                    printf(RED "\nPassword cannot be empty!!\n\n" RESET);
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
                printf(RED "Incorrect password. %d attempt(s) left.\n\n" RESET, 3 - attempts);
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
        printf(MAGENTA "\nLogin successful! Redirecting to shopping page...\n" RESET);
        Sleep(2000);

        loadProducts();
        startShopping();
    }
    else
    {
        printf(RED "Too many failed attempts. Login failed!\n" RESET);
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
    printf(YELLOW "\nWELCOME TO REGISTRATION PAGE\n" RESET);
    printf("----------------------------\n\n\n");

    getchar();

    do
    { // code for first name
        printf(CYAN "enter your First name: " RESET);
        fgets(Rfname, sizeof(Rfname), stdin);

        if (strlen(Rfname) == 1)
        {
            printf(RED "First name cannot be empty\n\n" RESET);
        }
        else
        {
            Rfname[strlen(Rfname) - 1] = '\0';
        }

    } while (strlen(Rfname) == 1);

    do
    { // code for last name
        printf(CYAN "enter your Last name: " RESET);
        fgets(Rlname, sizeof(Rlname), stdin);

        if (strlen(Rlname) == 1)
        {
            printf(RED "Last name cannot be empty\n\n" RESET);
        }
        else
        {
            Rlname[strlen(Rlname) - 1] = '\0';
        }

    } while (strlen(Rlname) == 1);

    do
    { // code for email
        printf(CYAN "Enter your Email: " RESET);
        fgets(Remail, sizeof(Remail), stdin);

        if (strlen(Remail) == 1)
        {
            printf(RED "Email cannot be empty\n\n" RESET);
        }
        else
        {
            Remail[strlen(Remail) - 1] = '\0';
        }

    } while (strlen(Remail) == 1);

    do
    {
        printf(CYAN "Enter your password: " RESET); // code for password
        fgets(Rpassword, sizeof(Rpassword), stdin);

        if (strlen(Rpassword) == 1)
        {
            printf(RED "password cannot be empty\n\n" RESET);
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
        printf(RED "error reading the data" RESET);
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
            printf(RED "error writing the data" RESET);
            return;
        }
        fprintf(pFile, "%s\n", Rdata);
        fclose(pFile);
        printf(GREEN "\nRegistration successfull!! you can now login\n" RESET);
        login_page();
    }
}

// =============== SHOPPING SYSTEM ==================

struct Product // This defines what each product contains
{
    int id;
    char name[50];
    float price;
    int stock;
    char category[30];
    float discount;
};

struct CartItem // This defines what’s inside your shopping cart
{
    struct Product product;
    int quantity;
};

struct Product products[50];         // All available items (loaded from file)
struct CartItem cart[50];            // What the user added
int productCount = 0, cartCount = 0; // cartCount-variable that keeps track of how many items are currently in the shopping cart.
                                     // productCount-number of products currently loaded
void startShopping() // The main shopping menu
{
    system("cls");

    int choice;

    printf("-------------\n");
    printf(YELLOW "  DASHBOARD" RESET);
    printf("\n-------------\n\n");

    printf(CYAN "1." RESET "Browse Products by Category\n");    // View + Add to Cart
    printf(CYAN "2." RESET "Today's Offers & Discounts\n");     // Shows offers
    printf(CYAN "3." RESET "View and Remove item from Cart\n"); // cart managment
    printf(CYAN "4." RESET "Checkout & Exit\n");                // offers and payment

    do
    {
        printf(CYAN "\nEnter your choice: " RESET);
        if (scanf("%d", &choice) != 1)
        {
            printf(RED "Please enter an integer number!!\n" RESET);
            getchar();
            continue;
        }
        if (choice > 5 || choice < 1)
        {
            printf(RED "Please enter valid input!!\n" RESET);
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
        viewAndManageCart();
        break;
    case 4:
        checkout();
        return;
    default:
        printf(RED "Invalid choice!\n" RESET);
    }
}

//---FUNCTION : Load Products ---//
// Purpose : Load products from products.txt
void loadProducts()
{
    FILE *file = fopen("products.txt", "r");

    if (!file)
    {
        printf(RED "Error: could not open products.txt\n" RESET);
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
    system("cls");
    char category[20][30]; // stores the list of unique product categories.
    int uniqueCount = 0;   // keeps track of how many unique categories have been found so far

    printf("------------\n");
    printf(YELLOW " CATEGORIES" RESET);
    printf("\n------------\n\n");

    // Collect unique categories
    for (int i = 0; i < productCount; i++) // For each product, it checks if the product's category is already in category[].
    {
        int found = 0; // will indicate whether the current product’s category is already in the category[] list
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
            strcpy(category[uniqueCount], products[i].category); // store new unique category
            printf("%d. %s\n", uniqueCount + 1, category[uniqueCount]);
            uniqueCount++;
        }
    }

    int catChoice; // will store the number the user enters corresponding to the category they want to browse.
    do
    {
        printf(CYAN "\nEnter your choice (Enter 0 to return): " CYAN);
        if (scanf("%d", &catChoice) != 1)
        {
            printf(RED "Please enter an integer number!\n" RESET);
            while (getchar() != '\n')
                ; // clear input
            continue;
        }
        if (catChoice > uniqueCount || catChoice < 0) // is a variable that keeps track of the number of unique categories found in your products list
        {
            printf("Please enter a valid input!\n");
        }
    } while (catChoice > uniqueCount || catChoice < 0);

    if (catChoice == 0)
    {
        startShopping();
        return;
    }

    printf(GREEN "\n\n| Products in %s |\n\n" RESET, category[catChoice - 1]);

    // Show all products in that category
    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(products[i].category, category[catChoice - 1]) == 0)
        {
            printf(CYAN "%d." RESET " %s - Rs.%.2f" MAGENTA " (%.0f%% OFF)\n" RESET,
                   products[i].id, products[i].name,
                   (double)products[i].price, (double)products[i].discount);
        }
    }

    // Add to cart section
    int pid, qty; // pid will store the Product ID that the user wants to add to the cart.
                  // qty will store the quantity of that product the user wants.

    while (1)
    {
        int foundInCategory = 0; // This variable keeps track of whether the entered Product ID exists in the chosen category

        printf(CYAN "\nEnter Product ID to add to cart (0 to return): " RESET);
        if (scanf("%d", &pid) != 1)
        {
            printf(RED "Please enter a valid product ID!\n" RESET);
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

                printf(CYAN "Enter Quantity: " RESET);
                if (scanf("%d", &qty) != 1)
                {
                    printf(RED "Invalid quantity!\n" RESET);
                    getchar(); // clear invalid input
                    foundInCategory = 0;
                    break;
                }

                // Add to cart
                cart[cartCount].product = products[i];
                cart[cartCount].quantity = qty;
                cartCount++;

                printf(GREEN "%d x %s added to cart successfully!\n" RESET, qty, products[i].name);
                Sleep(1500);

                startShopping();
                return;
            }
        }

        if (!foundInCategory)
        {
            printf(RED "Invalid Product ID for this category! Please try again.\n" RESET);
        }
    }
}

// 2. Show today’s offers
void showOffers()
{
    system("cls");
    printf("----------------");
    printf(YELLOW " TODAYS OFFER" RESET);
    printf("----------------\n\n");
    for (int i = 0; i < productCount; i = i + 3)
    {
        if (products[i].discount >= 20) // 423 show only products having discount above 20 per
            printf(CYAN "%d." RESET " %s - Rs.%.2f " MAGENTA "(%.0f%% OFF)\n" RESET,

                   products[i].id, products[i].name,
                   products[i].price, products[i].discount);
    }
    printf("\n");
    while (1)
    {
        printf(CYAN "Enter 0 to go back: " RESET); // code to go back
        int back;
        if (scanf("%d", &back) != 1)
        {
            printf(RED "Please enter integer number!!\n\n" RESET);
            getchar();
        }
        else if (back != 0)
        {
            printf(RED "Please enter valid input!!\n\n" RESET);
        }
        else
        {
            startShopping();
        }
    }
}

// 3. View and remove item from cart
void viewAndManageCart()
{
    system("cls");
    if (cartCount == 0)
    {
        printf(RED "\nYour cart is empty!\n" RESET);
        return;
    }

    char choice;

    // Loop so the user can remove multiple items until they choose to exit
    while (1)
    {
        float total = 0;
        printf(GREEN "\n--- Your Cart ---\n\n" RESET);

        // Display all items in cart
        for (int i = 0; i < cartCount; i++)
        {
            float priceAfterDiscount = cart[i].product.price * (1 - cart[i].product.discount / 100);
            float subtotal = priceAfterDiscount * cart[i].quantity;

            printf("%d. [ID: %d] %s\n   Quantity: %d \n   Discount(per product) : Rs. %.2f \n   Price after discount : Rs. %.2f\n   Subtotal : Rs. %.2f\n\n ", // show products in the cart
                   i + 1,
                   cart[i].product.id,
                   cart[i].product.name,
                   cart[i].quantity,
                   cart[i].product.price * (cart[i].product.discount / 100),
                   priceAfterDiscount, subtotal);

            total += subtotal;
        }
        printf("\n --------------------");
        printf("\n|" CYAN "Total: Rs. %.2f" RESET "|\n" RESET, total);
        printf(" --------------------\n");

        // Ask if user wants to remove an item
        printf(CYAN "\nDo you want to remove an item? (y/n): " RESET);
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y')
        {
            int pid, removeQty;
            printf(CYAN "Enter Product ID to remove: " RESET);
            scanf("%d", &pid);

            int found = 0;

            // Search for and remove the product
            for (int i = 0; i < cartCount; i++)
            {
                if (cart[i].product.id == pid)
                {
                    found = 1;
                    printf(GREEN "Current quantity of %s: %d\n" RESET, cart[i].product.name, cart[i].quantity);
                    printf(CYAN "Enter quantity to remove: " RESET);
                    scanf("%d", &removeQty);

                    if (removeQty <= 0)
                    {
                        printf(RED "Invalid quantity!\n" RESET);
                        break;
                    }

                    if (removeQty < cart[i].quantity)
                    {
                        // Reduce only the specified quantity
                        cart[i].quantity -= removeQty;
                        printf(RED "Removed %d of %s from cart." RESET CYAN "Remaining: %d\n" RESET,
                               removeQty, cart[i].product.name, cart[i].quantity);
                    }
                    else
                    {
                        // Remove the entire product if removeQty >= current quantity
                        for (int j = i; j < cartCount - 1; j++)
                            cart[j] = cart[j + 1];
                        cartCount--;
                        printf(CYAN "Removed entire %s from cart!\n" RESET, cart[i].product.name);
                    }

                    break;
                }
            }

            if (!found)
                printf(RED "Product not found in cart!\n" RESET);

            // If cart becomes empty, exit loop automatically
            if (cartCount == 0)
            {
                printf(RED "\nYour cart is now empty!\n" RESET);
                startShopping();
                break;
            }
        }
        else
        {
            // Exit loop and return to main menu
            startShopping();
            break;
        }
    }
}

// 4. Checkout
void checkout()
{
    system("cls");
    int payment_choice;
    char card_no[17] = {};
    int i = 0;
    int valid;
    char ch;
    char expiry[5];
    int cvv[3];
    char address[100];
    char customer_name[50];
    char payment_mode[20];
    float subtotal = 0, discount = 0, total = 0;

    if (cartCount == 0)
    {
        printf("Cart is empty!\n");
        return;
    }

    printf("\n----------------");
    printf(YELLOW "\n    CHECKOUT    \n" RESET);
    printf("----------------\n\n");
    for (int i = 0; i < cartCount; i++)
    {
        float finalPrice = cart[i].product.price * (1 - cart[i].product.discount / 100);
        subtotal += finalPrice * cart[i].quantity;
    }
    printf("Subtotal: Rs. %.2f\n", subtotal);

    printf("\nEnter your name: ");
    scanf(" %[^\n]", customer_name);

    // Apply offers (if any)
    total = offers(subtotal);
    discount = subtotal - total;

    printf("Total amount to pay: Rs.%.2f\n", total);

    while ((getchar()) != '\n' && getchar() != EOF)
        ; // clear buffer before taking address
    printf("\nEnter your delivery address: ");
    fgets(address, sizeof(address), stdin); // code for user address
    if (address[strlen(address) - 1] == '\n')
        address[strlen(address) - 1] = '\0';

    printf(CYAN "\nHow would you like to pay?\n" RESET); // payment options
    printf(CYAN "1." RESET "Cash\n");
    printf(CYAN "2." RESET "Card\n");
    printf(CYAN "3." RESET "UPI \n");

    do
    {
        printf(CYAN "\nEnter your choice: " RESET);
        if (scanf("%d", &payment_choice) != 1)
        {
            printf(RED "Invalid input! Enter again.\n" RESET);
            while (getchar() != '\n') // for clearing input buffer
                ;
            continue;
        }
        if (payment_choice != 1 && payment_choice != 2 && payment_choice != 3)
        {
            printf(RED "Please enter valid input!!\n" RESET);
        }
    } while (payment_choice != 1 && payment_choice != 2 && payment_choice != 3);

    switch (payment_choice)
    {
    case 1:
        strcpy(payment_mode, "Cash");
        printf("\nYou chose to pay by Cash.\n");
        printf(CYAN "Bill Amount:" RESET "Rs. %.2f\n", total);
        printf(CYAN "Payment Status:" RESET "Pending!!!\n");
        break;

    case 2:
        strcpy(payment_mode, "Card"); // code for card payment
        system("cls");
        printf("\nYou chose to pay by Card.\n");

        // CARD NUMBER
        do
        {
            printf(CYAN "\nEnter the card number: " RESET);
            i = 0;
            valid = 1;

            while (i < 16)
            {
                ch = getch();

                if (i > 0 && i % 4 == 0)
                {
                    printf(" ");
                }

                if (ch == '\n' || ch == '\r')
                {
                    printf(RED "\nyou pressed enter before entering all the digits\n\n" RESET);
                    valid = 0;
                    break;
                }
                if (ch == 8 || ch == 127) // for backspace
                {
                    if (i > 0)
                    {
                        if (i % 4 == 0)
                        {
                            printf("\b \b");
                        }
                        printf("\b \b");
                        i--;
                        continue;
                    }
                }

                card_no[i] = ch;

                if (i < 12)
                {
                    printf("*");
                }
                else
                {
                    printf("%c", card_no[i]);
                }
                i = i + 1;
            }

            if (valid && i == 16)
            {
                break;
            }

        } while (1);

        do
        {
            printf(CYAN "\nEnter the Expiry date: " RESET); // code for expiry date
            i = 0;
            valid = 1;
            while (i < 4)
            {
                ch = getch();
                if (i == 2)
                {
                    printf("/");
                }
                if (ch == '\n' || ch == '\r')
                {
                    printf(RED "\nyou pressed enter before entering all the digits\n\n" RESET);
                    valid = 0;
                    break;
                }
                if (ch == 8 || ch == 127)
                {
                    if (i > 0)
                    {
                        if (i == 2)
                        {
                            printf("\b \b");
                        }
                        printf("\b \b");
                        i--;
                        continue;
                    }
                }

                expiry[i] = ch;
                printf("%c", expiry[i]);
                i = i + 1;
            }

            if (valid && i == 4)
            {
                break;
            }
        } while (1);
        do
        {
            printf(CYAN "\nEnter CVV: " RESET); // code for cvv
            i = 0;
            valid = 1;
            while (i < 3)
            {
                ch = getch();
                if (ch == '\n' || ch == '\r')
                {
                    printf(RED "\nyou pressed enter before entering all the digits\n\n" RESET);
                    valid = 0;
                    break;
                }
                if (ch == 8 || ch == 127)
                {
                    if (i > 0)
                    {
                        printf("\b \b");
                        i--;
                        continue;
                    }
                }
                cvv[i] = ch;
                printf("*");
                i = i + 1;
            }

            if (valid && i == 3)
            {
                break;
            }
        } while (1);
        printf("\nProcessing.....");
        Sleep(3000);
        printf(GREEN "\n\nTransaction Approved!!" RESET);
        printf(CYAN "\nAmount charged:" RESET " Rs. %.2f ", total);
        printf(CYAN "\nPayment Status:" RESET " Successful");
        break;

    case 3:
        strcpy(payment_mode, "UPI"); // code for upi
        system("cls");
        printf("\nYou chose to pay by UPI.\n");
        char upi_id[50];

        printf(CYAN "Enter your UPI ID (e.g. yourname@upi): " RESET);
        scanf(" %s", upi_id);

        printf("\nGenerating UPI payment link...");
        Sleep(2000);
        printf("\nProcessing your UPI payment...");
        Sleep(3000);

        printf(GREEN "\n\nTransaction Successful " RESET);
        printf(CYAN "\nAmount Paid: " RESET "Rs. %.2f", total);
        printf(CYAN "\nPayment Status: " RESET "Successful");
        break;
    }
    char invoice_choice, feedback[100];

    printf("\n\nDo you want to generate invoice(Y/N): "); // code to ask if the user wants to generate invoice
    scanf(" %c", &invoice_choice);
    invoice_choice = toupper(invoice_choice);

    if (invoice_choice == 'Y')
    {
        generate_invoice(customer_name, subtotal, discount, total, payment_mode, address);
    }

    else
        printf("\nThank you for shopping with Click2Cart!!");
    printf("\nPlease give us a feedback!!: "); // ask user for feedback
    fgets(feedback, sizeof(feedback), stdin);
    if (feedback[strlen(feedback) - 1] == '\n')
        feedback[strlen(feedback) - 1] = '\0';

    
}

// =============== OFFERS FUNCTION ===============
float offers(float total)
{
    system("cls");
    int valid = 0;
    char code[10];
    char choice, choice_2;

    printf("\nWould you like to view offers ? (y/n): "); // check user to view offers
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
        printf("\n----------------\n");
        printf(YELLOW "   OFFERS\n" RESET);
        printf("----------------\n\n");

        printf("Billing amount over 5,000  --> 10%% off " MAGENTA "(Code: SAVE10)\n" RESET);
        printf("Billing amount over 10,000 --> 15%% off " MAGENTA "(Code: SAVE15)\n" RESET);
        printf("Billing amount over 15,000 --> 25%% off " MAGENTA "(Code: SAVE25)\n" RESET);

        printf(CYAN "\nWould you like to apply a coupon code? (y/n): " RESET);
        scanf(" %c", &choice_2);

        if (choice_2 == 'y' || choice_2 == 'Y')
        {
            printf(CYAN "Enter a coupon code (0 to skip): " RESET);
            scanf(" %s", code);

            if (strcmp(code, "0") == 0)
            {
                printf(RED "No coupon applied!\n" RESET);
                return total;
            }

            if (strcmp(code, "SAVE10") == 0 && total >= 5000)
            {
                total *= 0.9;
                valid = 1;
            }
            else if (strcmp(code, "SAVE15") == 0 && total >= 10000)
            {
                total *= 0.85;
                valid = 1;
            }
            else if (strcmp(code, "SAVE25") == 0 && total >= 15000)
            {
                total *= 0.75;
                valid = 1;
            }
            else
            {
                printf(RED "\nInvalid code or not eligible for the discount.\n" RESET);
                Sleep(1000);
                return total;
            }

            if (valid)
            {
                printf(GREEN "\nCoupon applied successfully!\n" RESET);
                printf(CYAN "New total = " RESET "Rs. %.2f\n", total);
                Sleep(1000);
                return total;
            }
        }
        else
        {
            return total;
        }
    }

    return total;
}

void generate_invoice(char name[], float subtotal, float discount, float total, char payment_mode[], char address[])
{
    char feedback[100];
    time_t t;
    time(&t);

    printf("\n\n===========================================\n"); // code for invoice
    printf(YELLOW "              CLICK2CART INVOICE\n" RESET);
    printf("===========================================\n");
    printf(CYAN "Customer Name    :" RESET " %s\n", name);
    printf(CYAN "Date & Time      :" RESET " %s", ctime(&t));
    printf(CYAN "Delivery Address :" RESET " %s\n", address);
    printf("-------------------------------------------\n");
    printf(CYAN "Subtotal      :" RESET " Rs. %.2f\n", subtotal);
    printf(CYAN "Discount      : " RESET "Rs. %.2f\n", discount);
    printf(CYAN "Final Total   : " RESET "Rs. %.2f\n", total);
    printf(CYAN "Payment Mode  : " RESET "%s\n", payment_mode);
    printf("-------------------------------------------\n");
    printf(MAGENTA "      Thank you for shopping with Click2Cart!\n" RESET);
    printf("===========================================\n");

    printf("\nPlease give us your feedback!!: "); // code to ask user for feedback
    fgets(feedback, sizeof(feedback), stdin);
    if (feedback[strlen(feedback) - 1] == '\n')
        feedback[strlen(feedback) - 1] = '\0';

    
}
