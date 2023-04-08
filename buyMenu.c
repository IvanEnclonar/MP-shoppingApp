#include "sellMenu.c"

void printBuyMenu()
{
    printf("\n[1] View all items\n");
    printf("[2] Show all products by a specific seller\n");
    printf("[3] Show all products by a specific category\n");
    printf("[4] Search Products by Name\n");
    printf("[5] Add to cart\n");
    printf("[6] Edit cart\n");
    printf("[7] Checkout menu\n");
    printf("[8] Exit Buy Menu\n");
    printf("Enter choice: ");
}

int getUniqueSellers(struct Item items[], int itemCount, int uniqueSellers[])
{
    int count = 0;
    for (int i = 0; i < itemCount; i++)
    {
        int found = 0;
        for (int j = 0; j < count; j++)
        {
            if (items[i].sellerID == uniqueSellers[j])
            {
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            uniqueSellers[count] = items[i].sellerID;
            count++;
        }
    }

    return count;
}

void viewItems(struct Item items[], int *itemCount)
{
    int uniqueSellers[100];
    int sellerCount = getUniqueSellers(items, *itemCount, uniqueSellers);

    for (int i = 0; i < sellerCount; i++)
    {
        printf("Seller ID: %d", uniqueSellers[i]);
        showMyProducts(items, *itemCount, uniqueSellers[i], sellerProductCount(items, *itemCount, uniqueSellers[i]));
        printf("\n");

        char input;
        do
        {
            printf("Press N to see the next product list or X to exit: ");
            scanf(" %c", &input);
        } while ((input != 'N' && input != 'n') && (input != 'x' && input != 'X'));

        if (input == 'X' || input == 'x')
        {
            printf("Exiting low stock menu...\n");
            sellerCount = -1;
        }

        if (sellerCount > 0 && i == sellerCount - 1)
        {
            i = -1;
        }
    }
}

void showProductsBySeller(struct Item items[], int itemCount)
{
    int sellerId;
    printf("\nEnter seller ID: ");
    scanf("%d", &sellerId);

    printf("Products by this seller: \n");
    showMyProducts(items, itemCount, sellerId, sellerProductCount(items, itemCount, sellerId));
    printf("\n");
}

// void findCategories(struct Item items[], int itemCount, char categories[][100], int *categoryCount)
// {
//     for (int i = 0; i < itemCount; i++)
//     {
//         int found = 0;
//         for (int j = 0; j < *categoryCount; j++)
//         {
//             if (strcmp(items[i].category, categories[j]) == 0)
//             {
//                 found = 1;
//                 break;
//             }
//         }
//         if (found == 0)
//         {
//             strcpy(categories[*categoryCount], items[i].category);
//             *categoryCount = *categoryCount + 1;
//         }
//     }
// }

void searchProductsByCategory(struct Item items[], int itemCount)
{
    char input[100];
    int count = itemCount;
    printf("\nEnter category: ");
    scanf(" %[^\n]s", input);

    printf("Products by this category: %s\n", input);
    for (int i = 0; i < count; i++)
    {
        if (strcmp(items[i].category, input) == 0)
        {
            printf("Product ID: %d\n", items[i].productID);
            printf("Product Name: %s\n", items[i].itemName);
            printf("Product Price: %.2f\n", items[i].unitPrice);
            printf("Product Quantity: %d\n", items[i].quantityAvailable);
            printf("Product Description: %s\n", items[i].itemDescription);
            printf("Seller ID: %d\n", items[i].sellerID);
            printf("\n");
        }

        char input;
        do
        {
            printf("Press N to see the next product or X to exit: ");
            scanf(" %c", &input);
        } while ((input != 'N' && input != 'n') && (input != 'x' && input != 'X'));

        if (input == 'X' || input == 'x')
        {
            printf("Exiting...\n");
            count = -1;
        }

        if (count > 0 && i == count - 1)
        {
            i = -1;
        }
    }
}

void BuyMenu(int userID, struct Item items[], int *itemCount)
{
    int choice = 0;
    while (choice != 8)
    {
        printBuyMenu();
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            viewItems(items, itemCount);
            break;
        case 2:
            showProductsBySeller(items, *itemCount);
            break;
        case 3:
            searchProductsByCategory(items, *itemCount);
            break;
        case 4:
            break;
        case 8:
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }
}