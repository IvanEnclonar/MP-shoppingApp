#include <stdio.h>
#include <string.h>

struct Date
{
    int month;
    int day;
    int year;
};

struct UserInfo
{
    int userID;
    char password[11];
    char address[31];
    int contactNumber;
    char name[21];
};

struct Item
{
    int productID;
    char itemName[21];
    char category[16];
    char itemDescription[31];
    int quantityAvailable;
    float unitPrice;
    int sellerID;
};

struct Transaction
{
    struct Date date;
    struct Item items[5];
    int buyerID;
    int sellerID;
    float totalAmount;
};

int scanUsers(struct UserInfo users[], int numUsers, int userID)
{
    for (int i = 0; i < numUsers; i++)
    {
        if (userID == users[i].userID)
        {
            return 0;
        }
    }
    return 1;
}

int getUniqueUserID(struct UserInfo users[], int numUsers)
{
    int userID = 0, isUnique = 0;
    do
    {
        printf("Enter your userID (must be unique): ");
        scanf("%d", &userID);

        if (scanUsers(users, numUsers, userID))
        {
            isUnique = 1;
        }
        else
        {
            printf("User ID already exists!\n");
        }
    } while (isUnique == 0);

    return userID;
}

struct UserInfo registerUser(int userID)
{
    struct UserInfo newUser;
    newUser.userID = userID;

    printf("Enter your password (up to 10 characters): ");
    scanf("%s", newUser.password);

    printf("Enter your address (up to 30 characters): ");
    scanf(" %[^\n]", newUser.address);

    printf("Enter your contact number: ");
    scanf("%d", &newUser.contactNumber);

    printf("Enter your name (up to 20 characters): ");
    scanf("%s", newUser.name);

    return newUser;

    printf("User registered successfully.\n");
}

int login(struct UserInfo users[], int numUsers)
{
    int userID;
    char password[11];
    printf("Enter your userID: ");
    scanf("%d", &userID);
    printf("Enter your password: ");
    scanf("%s", &password);

    for (int i = 0; i < numUsers; i++)
    {
        if (userID == users[i].userID && strcmp(password, users[i].password) == 0)
        {
            return 1;
        }
    }
    printf("Invalid userID or password. Please try again.\n");
    return 0;
}

void printMenu()
{
    printf("\n[1] Register User\n");
    printf("[2] Main Menu\n");
    printf("[0] Exit\n");
}

void printUserMenu()
{
    prinf("\n[1] Sell Menu\n");
    prinf("[2] Buy Menu\n");
    printf("[3] Exit User Menu\n");
}

struct Item addNewItem()
{
    struct Item newItem;

    printf("Enter product ID: ");
    scanf("%d", &newItem.productID);
    printf("Enter item name: ");
    scanf("%s", newItem.itemName);
    printf("Enter category: ");
    scanf("%s", newItem.category);
    printf("Enter item description: ");
    scanf("%s", newItem.itemDescription);
    printf("Enter quantity available: ");
    scanf("%d", &newItem.quantityAvailable);
    printf("Enter unit price: ");
    scanf("%f", &newItem.unitPrice);
    printf("Enter seller ID: ");
    scanf("%d", &newItem.sellerID);

    return newItem;
}

int main()
{
    int choice = 1;
    struct UserInfo users[100];
    struct Item items[100];
    int userCount = 0;

    while (choice != 0)
    {
        printMenu();
        printf("Enter choice: ");
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            users[userCount] = registerUser(getUniqueUserID(users, userCount));
            userCount++;
            break;
        case 2:
            if (login(users, userCount))
            {
                int userMenuChoice = 0;
                printf("Logged in successfully.\n");
                printUserMenu();
                printf("Enter choice: ");
                scanf(" %d", &userMenuChoice);
                switch (userMenuChoice)
                {
                case 1:

                    break;
                }
            }
            break;
        case 0:
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }
}