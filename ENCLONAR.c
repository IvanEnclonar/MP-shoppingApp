#include "adminMenu.c"

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
            showMyProducts(items, *itemCount, userID, sellerProductCount(items, *itemCount, userID), 0);
            printf("Enter the product ID of the item you want to edit: ");
            scanf(" %d", &productEditID);
            editStock(items, *itemCount, userID, productEditID);
            break;
        case 3:
            showMyProducts(items, *itemCount, userID, sellerProductCount(items, *itemCount, userID), 0);
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
        printf("[3] Admin Menu\n");
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
                struct Item cart[21];
                int cartCount = 0;
                int userMenuChoice = 0;
                printf("Logged in successfully.\n");
                if (loadCartData(cart, &cartCount, userID) == 1)
                {
                    printf("\nCart data loaded successfully!\n");
                }
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
                        BuyMenu(userID, items, &itemCount, users, userCount, cart, &cartCount);
                        break;
                    case 3:
                        if (cartCount > 0)
                        {
                            exitUserMenu(cart, &cartCount, userID);
                        }
                        break;
                    default:
                        printf("Invalid choice!\n");
                        break;
                    }
                } while (userMenuChoice != 3);
            }
            break;
        case 3:
            adminMenu(users, &userCount, items, &itemCount);
            break;
        case 0:
            if (saveUsers(users, userCount) && saveItems(items, itemCount))
            {
                printf("Data saved successfully!\n");
            }
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }
}