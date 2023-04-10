#include "ENCLONAR.h"

/**
 * @brief Scans an array of UserInfo structures to check if a userID already exists.
 * @param users Array of UserInfo structures.
 * @param numUsers Number of users in the array.
 * @param userID User ID to check for uniqueness.
 * @return Returns 0 if the user ID already exists, 1 otherwise.
 */
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

/**
 * @brief Prompts the user to enter a unique user ID.
 * @param users Array of UserInfo structures.
 * @param numUsers Number of users in the array.
 * @return Returns a unique user ID.
 */
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

/**
 * @brief Registers a new user with the provided user ID.
 * @param userID Unique user ID.
 * @return Returns a UserInfo structure with the user's input.
 */
struct UserInfo registerUser(int userID)
{
    struct UserInfo newUser;
    newUser.userID = userID;

    printf("Enter your password (up to 10 characters): ");
    scanf(" %[^\n]", newUser.password);

    printf("Enter your address (up to 30 characters): ");
    scanf(" %[^\n]", newUser.address);

    printf("Enter your contact number: ");
    scanf("%d", &newUser.contactNumber);

    printf("Enter your name (up to 20 characters): ");
    scanf(" %[^\n]", newUser.name);

    return newUser;
}

/**
 * @brief Saves an array of Item structures to a file named "Items.txt".
 * @param items Array of Item structures.
 * @param itemCount Number of items in the array.
 * @return Returns 1 if successful, 0 otherwise.
 */
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

/**
 * @brief Loads Item structures from a file named "Items.txt" into an array.
 * @param items Array to store the loaded Item structures.
 * @param itemCount Pointer to an integer to store the number of items loaded.
 * @return Returns 1 if successful, 0 otherwise.
 */
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

/**
 * @brief Saves an array of UserInfo structures to a file named "Users.txt".
 * @param users Array of UserInfo structures.
 * @param numUsers Number of users in the array.
 * @return Returns 1 if successful, 0 otherwise.
 */
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

/**
 * @brief Loads UserInfo structures from a file named "Users.txt" into an array.
 * @param users Array to store the loaded UserInfo structures.
 * @param numUsers Pointer to an integer to store the number of users loaded.
 * @return Returns 1 if successful, 0 otherwise.
 */
int loadUsers(struct UserInfo users[], int *numUsers)
{
    FILE *fp;
    fp = fopen("Users.txt", "r");

    if (fp == NULL)
    {
        printf("No Users.txt file found!\n");
        return 0;
    }

    while (fscanf(fp, "%d %[^\n]\n%[^\n]\n%[^\n]\n%d\n\n", &users[*numUsers].userID, users[*numUsers].password, users[*numUsers].name, users[*numUsers].address, &users[*numUsers].contactNumber) != EOF)
    {
        *numUsers = *numUsers + 1;
    }
    fclose(fp);
    return 1;
}

/**
 * @brief Loads Transaction structures from a file named "Transactions.txt" into an array.
 * @param transaction Array to store the loaded Transaction structures.
 * @param transactionCount Pointer to an integer to store the number of transactions loaded.
 * @return Returns 1 if successful, 0 otherwise.
 */
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

/**
 * @brief Saves an array of Item structures as transactions to a file named "Transactions.txt".
 * @param cart Array of Item structures.
 * @param cartCount Number of items in the array.
 * @param date Date structure representing the date of the transactions.
 * @param userID Unique user ID of the buyer.
 * @return Returns 1 if successful, 0 otherwise.
 */
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

/**
 * @brief Loads cart data from a user-specific file into an array of Item structures.
 * @param cart Array to store the loaded Item structures.
 * @param cartCount Pointer to an integer to store the number of items loaded.
 * @param userID Unique user ID of the buyer.
 * @return Returns 1 if successful, 0 otherwise.
 */
int loadCartData(struct Item cart[], int *cartCount, int userID)
{
    int ID = userID;
    FILE *fp;
    char filename[50];
    sprintf(filename, "%d", ID);
    strcat(filename, ".txt");
    fp = fopen(filename, "r");

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