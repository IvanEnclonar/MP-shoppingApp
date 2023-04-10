#include "ENCLONAR.h"

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
}

int saveItems(struct Item items[], int itemCount)
{
    FILE *fp;
    fp = fopen("Items.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    for (int i = 0; i < itemCount; i++)
    {
        fprintf(fp, "%d %d\n%s\n%s\n%s\n%d %.2f\n\n", items[i].productID, items[i].sellerID, items[i].itemName, items[i].category, items[i].itemDescription, items[i].quantityAvailable, items[i].unitPrice);
    }
    fclose(fp);
    return 1;
}

int loadItems(struct Item items[], int *itemCount)
{
    FILE *fp;
    fp = fopen("Items.txt", "r");

    if (fp == NULL)
    {
        printf("No Items.txt file found!\n");
        return 0;
    }

    while (fscanf(fp, "%d %d\n%[^\n]\n%[^\n]\n%[^\n]\n%d %f\n\n", &items[*itemCount].productID, &items[*itemCount].sellerID, items[*itemCount].itemName, items[*itemCount].category, items[*itemCount].itemDescription, &items[*itemCount].quantityAvailable, &items[*itemCount].unitPrice) != EOF)
    {
        *itemCount = *itemCount + 1;
    }
    fclose(fp);
    return 1;
}

int saveUsers(struct UserInfo users[], int numUsers)
{
    FILE *fp;
    fp = fopen("Users.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    for (int i = 0; i < numUsers; i++)
    {
        fprintf(fp, "%d %s\n%s\n%s\n%d\n\n", users[i].userID, users[i].password, users[i].name, users[i].address, users[i].contactNumber);
    }
    fclose(fp);
    return 1;
}

int loadUsers(struct UserInfo users[], int *numUsers)
{
    FILE *fp;
    fp = fopen("Users.txt", "r");

    if (fp == NULL)
    {
        printf("No Users.txt file found!\n");
        return 0;
    }

    while (fscanf(fp, "%d %s\n%[^\n]\n%[^\n]\n%d\n\n", &users[*numUsers].userID, users[*numUsers].password, users[*numUsers].name, users[*numUsers].address, &users[*numUsers].contactNumber) != EOF)
    {
        *numUsers = *numUsers + 1;
    }
    fclose(fp);
    return 1;
}

int loadTransaction(struct Transaction transaction[], int *transactionCount)
{
    FILE *fp;
    fp = fopen("Transactions.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }
    while (fscanf(fp, "%d\\%d\\%d\n%d %d %d\n%[^\n]\n%[^\n]\n%[^\n]\n%d %f\n\n", &transaction[*transactionCount].date.day, &transaction[*transactionCount].date.month, &transaction[*transactionCount].date.year, &transaction[*transactionCount].productID, &transaction[*transactionCount].sellerID, &transaction[*transactionCount].buyerID, transaction[*transactionCount].itemName, transaction[*transactionCount].category, transaction[*transactionCount].itemDescription, &transaction[*transactionCount].quantityBought, &transaction[*transactionCount].unitPrice) != EOF)
    {
        *transactionCount = *transactionCount + 1;
    }
    fclose(fp);
    return 1;
}

int saveTransaction(struct Item cart[], int cartCount, struct Date date, int userID)
{
    FILE *fp;
    fp = fopen("Transactions.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }
    for (int i = 0; i < cartCount; i++)
    {
        fprintf(fp, "%d\\%d\\%d\n", date.day, date.month, date.year);
        fprintf(fp, "%d %d %d\n%s\n%s\n%s\n%d %.2f\n\n", cart[i].productID, cart[i].sellerID, userID, cart[i].itemName, cart[i].category, cart[i].itemDescription, cart[i].quantityAvailable, cart[i].unitPrice);
    }
    fclose(fp);
    return 1;
}

int loadCartData(struct Item cart[], int *cartCount, int userID)
{
    int ID = userID;
    FILE *fp;
    char filename[50];
    sprintf(filename, "%d", ID);
    strcat(filename, ".txt");
    fp = fopen(filename, "r");

    printf("CART: %s\n", filename);

    if (fp == NULL)
    {
        return 0;
    }
    else
    {
        while (fscanf(fp, "%d %d\n%[^\n]\n%[^\n]\n%[^\n]\n%d %f\n\n", &cart[*cartCount].productID, &cart[*cartCount].sellerID, cart[*cartCount].itemName, cart[*cartCount].category, cart[*cartCount].itemDescription, &cart[*cartCount].quantityAvailable, &cart[*cartCount].unitPrice) != EOF)
        {
            *cartCount = *cartCount + 1;
        }
        fclose(fp);
        return 1;
    }
}