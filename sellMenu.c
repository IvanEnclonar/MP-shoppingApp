#include "register.c"

/**
@brief Checks if a given product ID is unique among the existing items.
@param items[] An array of Item structures representing the inventory.
@param numItems An integer representing the number of items in the inventory.
@return An integer representing a unique product ID.
*/
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

/**
@brief Calculates the number of products a seller has in the inventory.
@param items[] An array of Item structures representing the inventory.
@param numItems An integer representing the number of items in the inventory.
@param sellerID An integer representing the seller's ID.
@return An integer representing the number of products a seller has in the inventory.
*/
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

/**
@brief Creates a new item and adds it to the inventory.
@param sellerID An integer representing the seller's ID.
@param productID An integer representing the product's ID.
@return A struct Item representing the new item added to the inventory.
*/
struct Item addNewItem(int sellerID, int productID)
{
    struct Item newItem;

    newItem.productID = productID;
    printf("Enter item name: ");
    scanf(" %[^\n]", newItem.itemName);
    printf("Enter category: ");
    scanf(" %[^\n]", newItem.category);
    printf("Enter item description: ");
    scanf(" %[^\n]", newItem.itemDescription);
    printf("Enter quantity available: ");
    scanf("%d", &newItem.quantityAvailable);
    printf("Enter unit price: ");
    scanf("%f", &newItem.unitPrice);
    newItem.sellerID = sellerID;

    printf("Item added successfully!\n");
    return newItem;
}

/**
@brief Sorts the items in the inventory based on their product ID.
@param items[] An array of Item structures representing the inventory.
@param numItems An integer representing the number of items in the inventory.
*/
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

/**
@brief Displays the products of a seller.
@param items[] An array of Item structures representing the inventory.
@param numItems An integer representing the number of items in the inventory.
@param sellerID An integer representing the seller's ID.
@param myProductCount An integer representing the number of products a seller has in the inventory.
@param isCheckout An integer flag that determines if the function is called during a checkout process (1 for true, 0 for false).
*/
void showMyProducts(struct Item items[], int numItems, int sellerID, int myProductCount, int isCheckout)
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

    if (isCheckout == 0)
    {
        printf("\nProduct ID\tItem Name\t\tCategory\tQuantity Available\tUnit Price\n\n");
        for (int i = 0; i < myProductCount; i++)
        {
            printf("%10d\t%-20s\t%-15s\t\t%10d\t%10.2f\n", myProducts[i].productID, myProducts[i].itemName, myProducts[i].category, myProducts[i].quantityAvailable, myProducts[i].unitPrice);
        }
    }
    else
    {
        float total = 0;
        printf("\nProduct ID\tItem Name\t\tQuantity\tUnit Price\tTotal Price\n");
        for (int i = 0; i < myProductCount; i++)
        {
            total += myProducts[i].quantityAvailable * myProducts[i].unitPrice;
            printf("%10d\t%-20s\t%8d\t%10.2f\t%10.2f\n", myProducts[i].productID, myProducts[i].itemName, myProducts[i].quantityAvailable, myProducts[i].unitPrice, myProducts[i].quantityAvailable * myProducts[i].unitPrice);
        }
        printf("Total: %.2f\n", total);
    }
}

/**
@brief Prints the edit menu options for the user.
*/
void printEditMenu()
{
    printf("[1] Replenish\n");
    printf("[2] Change unit price\n");
    printf("[3] Change item name\n");
    printf("[4] Change item category\n");
    printf("[5] Change item description\n");
    printf("[6] Finish editing\n");
}

/**
@brief Allows a seller to edit the details of a product in the inventory.
@param items[] An array of Item structures representing the inventory.
@param numItems An integer representing the number of items in the inventory.
@param sellerID An integer representing the seller's ID.
@param productID An integer representing the product's ID.
*/
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
                    scanf(" %[^\n]", items[i].itemName);
                    printf("Item name changed successfully!\n");
                    break;
                case 4:
                    printf("Enter new item category: ");
                    scanf(" %[^\n]", items[i].category);
                    printf("Item category changed successfully!\n");
                    break;
                case 5:
                    printf("Enter new item description: ");
                    scanf(" %[^\n]", items[i].itemDescription);
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

/**
@brief Displays the products with low stock (less than 5) for a seller.
@param items[] An array of Item structures representing the inventory.
@param numItems An integer representing the number of items in the inventory.
@param sellerID An integer representing the seller's ID.
@param myProductCount An integer representing the number of products a seller has in the inventory.
*/
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
            printf("Item Description: %s\n", items[i].itemDescription);
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