#include "buyMenu.c"

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
            return userID;
        }
    }
    printf("Invalid userID or password. Please try again.\n");
    return 0;
}

void SellMenu(int userID, struct Item items[], int *itemCount)
{
    int choice = 0;
    while (choice != 5)
    {
        printf("\n[1] Add New Item\n");
        printf("[2] Edit Stock\n");
        printf("[3] Show My Products\n");
        printf("[4] Show low stock products\n");
        printf("[5] Exit Sell Menu\n");
        printf("Enter choice: ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            if (sellerProductCount(items, *itemCount, userID) >= 20)
            {
                printf("You have reached the maximum number of items you can sell.\n");
                break;
            }
            else
            {
                items[*itemCount] = addNewItem(userID, uniqueProductID(items, *itemCount));
                *itemCount = *itemCount + 1;
                break;
            }
        case 2:
            int productEditID = 0;
            showMyProducts(items, *itemCount, userID, sellerProductCount(items, *itemCount, userID));
            printf("Enter the product ID of the item you want to edit: ");
            scanf(" %d", &productEditID);
            editStock(items, *itemCount, userID, productEditID);
            break;
        case 3:
            showMyProducts(items, *itemCount, userID, sellerProductCount(items, *itemCount, userID));
            break;
        case 4:
            showLowStocks(items, *itemCount, userID, sellerProductCount(items, *itemCount, userID));
            break;
        case 5:
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }
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
    printf("Items saved successfully!\n");
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
    printf("Users saved successfully!\n");
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

int main()
{
    int choice = 1;
    struct UserInfo users[100];
    struct Item items[100];
    int userCount = 0, itemCount = 0;
    if (loadUsers(users, &userCount) && loadItems(items, &itemCount))
    {
        printf("Data loaded successfully!\n");
    }

    while (choice != 0)
    {
        printf("\n[1] Register User\n");
        printf("[2] Main Menu\n");
        printf("[0] Exit\n");
        printf("Enter choice: ");
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            users[userCount] = registerUser(getUniqueUserID(users, userCount));
            userCount++;
            break;
        case 2:
            int userID = login(users, userCount);
            if (userID)
            {
                int userMenuChoice = 0;
                printf("Logged in successfully.\n");
                do
                {
                    printf("\n[1] Sell Menu\n");
                    printf("[2] Buy Menu\n");
                    printf("[3] Exit User Menu\n");
                    printf("Enter choice: ");
                    scanf(" %d", &userMenuChoice);
                    switch (userMenuChoice)
                    {
                    case 1:
                        SellMenu(userID, items, &itemCount);
                        break;
                    case 2:
                        BuyMenu(userID, items, &itemCount);
                        break;
                    case 3:
                        break;
                    default:
                        printf("Invalid choice!\n");
                        break;
                    }
                } while (userMenuChoice != 3);
            }
            break;
        case 0:
            saveUsers(users, userCount);
            saveItems(items, itemCount);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }
}