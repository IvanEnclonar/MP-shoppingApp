#include "register.c"

int uniqueProductID(struct Item items[], int numItems)
{
    int productID = 0, isUnique = 1;

    do
    {
        isUnique = 1;
        printf("Enter product ID (must be unique): ");
        scanf("%d", &productID);

        for (int i = 0; i < numItems; i++)
        {
            if (items[i].productID == productID)
            {
                isUnique = 0;
                printf("Product ID already exists!\n");
            }
        }
    } while (isUnique == 0);

    return productID;
}

int sellerProductCount(struct Item items[], int numItems, int sellerID)
{
    int count = 0;
    for (int i = 0; i < numItems; i++)
    {
        if (items[i].sellerID == sellerID)
        {
            count++;
        }
    }
    return count;
}
struct Item addNewItem(int sellerID, int productID)
{
    struct Item newItem;

    newItem.productID = productID;
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
    newItem.sellerID = sellerID;

    printf("Item added successfully!\n");
    return newItem;
}

void sortItems(struct Item items[], int numItems)
{
    struct Item temp;
    for (int i = 0; i < numItems; i++)
    {
        for (int j = i + 1; j < numItems; j++)
        {
            if (items[i].productID > items[j].productID)
            {
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

void showMyProducts(struct Item items[], int numItems, int sellerID, int myProductCount)
{
    int count = 0;
    struct Item myProducts[myProductCount];
    for (int i = 0; i < numItems; i++)
    {
        if (items[i].sellerID == sellerID)
        {
            myProducts[count] = items[i];
            count++;
        }
    }
    sortItems(myProducts, myProductCount);

    printf("\nProduct ID\tItem Name\tCategory\tQuantity Available\tUnit Price\n");
    for (int i = 0; i < myProductCount; i++)
    {
        printf("%10d\t%s\t\t%s\t\t%18d\t%10.2f\n", myProducts[i].productID, myProducts[i].itemName, myProducts[i].category, myProducts[i].quantityAvailable, myProducts[i].unitPrice);
    }
}

void printEditMenu()
{
    printf("[1] Replenish\n");
    printf("[2] Change unit price\n");
    printf("[3] Change item name\n");
    printf("[4] Change item category\n");
    printf("[5] Change item description\n");
    printf("[6] Finish editing\n");
}

void editStock(struct Item items[], int numItems, int sellerID, int productID)
{
    int i, found = 0;
    for (i = 0; i < numItems; i++)
    {
        if (items[i].productID == productID && items[i].sellerID == sellerID)
        {
            found = 1;
            int editChoice = 0;
            do
            {
                printEditMenu();
                printf("Enter your choice: ");
                scanf("%d", &editChoice);
                switch (editChoice)
                {
                case 1:
                    int amt = 0;
                    printf("Enter quantity to add: ");
                    scanf("%d", &amt);
                    items[i].quantityAvailable = amt + items[i].quantityAvailable;
                    printf("Quantity replenished successfully!\n");
                    break;
                case 2:
                    printf("Enter new unit price: ");
                    scanf("%f", &items[i].unitPrice);
                    printf("Unit price changed successfully!\n");
                    break;
                case 3:
                    printf("Enter new item name: ");
                    scanf("%s", items[i].itemName);
                    printf("Item name changed successfully!\n");
                    break;
                case 4:
                    printf("Enter new item category: ");
                    scanf("%s", items[i].category);
                    printf("Item category changed successfully!\n");
                    break;
                case 5:
                    printf("Enter new item description: ");
                    scanf("%s", items[i].itemDescription);
                    printf("Item description changed successfully!\n");
                    break;
                case 6:
                    printf("Exiting edit menu...\n");
                    break;
                default:
                    printf("Invalid choice!\n");
                    break;
                }
            } while (editChoice != 6);
        }
    }

    if (found == 0)
    {
        printf("Product ID not found!\n");
    }
}

void showLowStocks(struct Item items[], int numItems, int sellerID, int myProductCount)
{
    int quit = 0, count = 0;
    for (int i = 0; i < numItems; i++)
    {
        if (items[i].quantityAvailable < 5 && items[i].sellerID == sellerID)
        {
            count++;
            printf("\nProduct ID: %d\n", items[i].productID);
            printf("Item Name: %s\n", items[i].itemName);
            printf("Category: %s\n", items[i].category);
            printf("Quantity Available: %d\n", items[i].quantityAvailable);
            printf("Unit Price: %.2f\n", items[i].unitPrice);

            char input;
            do
            {
                printf("Press N to see the next product or X to exit: ");
                scanf(" %c", &input);
            } while ((input != 'N' && input != 'n') && (input != 'x' && input != 'X'));

            if (input == 'X' || input == 'x')
            {
                printf("Exiting low stock menu...\n");
                quit = 1;
            }
        }

        if ((quit == 0 && count > 0) && i == numItems - 1)
        {
            i = -1;
        }
    }
    if (count == 0)
    {
        printf("No low stock items!\n");
    }
}