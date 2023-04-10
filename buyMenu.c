#include "sellMenu.c"

// Prints the buy menu
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

/**
 * @brief Retrieves the unique seller IDs from a given array of items.
 * @param items An array of Item structures.
 * @param itemCount The number of items in the array.
 * @param uniqueSellers An array to store unique seller IDs.
 * @return The number of unique sellers found in the items array.
 */
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

/**
 * @brief Displays items from an array of items grouped by unique sellers.
 * @param items An array of Item structures.
 * @param itemCount A pointer to the number of items in the array.
 */
void viewItems(struct Item items[], int *itemCount)
{
    int uniqueSellers[100];
    int sellerCount = getUniqueSellers(items, *itemCount, uniqueSellers);

    for (int i = 0; i < sellerCount; i++)
    {
        printf("\nSeller ID: %d", uniqueSellers[i]);
        showMyProducts(items, *itemCount, uniqueSellers[i], sellerProductCount(items, *itemCount, uniqueSellers[i]), 0);
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

/**
 * @brief Displays items from an array of items by a specific seller.
 * @param items An array of Item structures.
 * @param itemCount The number of items in the array.
 * @param users An array of UserInfo structures.
 * @param userCount The number of users in the array.
 */
void showProductsBySeller(struct Item items[], int itemCount, struct UserInfo users[], int userCount)
{
    int sellerId;
    printf("\nEnter seller ID: ");
    scanf("%d", &sellerId);

    if (scanUsers(users, userCount, sellerId) == 0)
    {
        printf("Products by this seller: \n");
        showMyProducts(items, itemCount, sellerId, sellerProductCount(items, itemCount, sellerId), 0);
        printf("\n");
    }
    else
    {
        printf("Seller ID not found!\n");
    }
}

/**
 * @brief Displays items from an array of items by a specific category.
 * @param items An array of Item structures.
 * @param itemCount The number of items in the array.
 */
void searchProductsByCategory(struct Item items[], int itemCount)
{
    char input[100];
    int count = itemCount, found = 0;
    printf("Enter category: ");
    scanf(" %[^\n]s", input);

    printf("Products by this category\n");
    for (int i = 0; i < count; i++)
    {
        if (strcmp(items[i].category, input) == 0)
        {
            printf("\nProduct ID: %d\n", items[i].productID);
            printf("Product Name: %s\n", items[i].itemName);
            printf("Product Price: %.2f\n", items[i].unitPrice);
            printf("Product Quantity: %d\n", items[i].quantityAvailable);
            printf("Product Description: %s\n", items[i].itemDescription);
            printf("Seller ID: %d\n", items[i].sellerID);
            printf("\n");

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

            found = 1;
        }

        if ((found == 1 && count > 0) && i == count - 1)
        {
            i = -1;
        }
    }
    if (found == 0)
    {
        printf("\nNo products found in this category!\n");
    }
}

/**
 * @brief Displays items from an array of items by a specific name.
 * @param items An array of Item structures.
 * @param itemCount The number of items in the array.
 */
void searchProductsByName(struct Item items[], int itemCount)
{
    char input[21];
    int count = itemCount, found = 0;
    printf("Enter product name: ");
    scanf(" %[^\n]s", input);

    for (int i = 0; i < count; i++)
    {
        char *ptr = strstr(items[i].itemName, input);
        if (ptr != NULL)
        {
            printf("Products by this name:\n");
            printf("Product ID: %d\n", items[i].productID);
            printf("Product Name: %s\n", items[i].itemName);
            printf("Product Price: %.2f\n", items[i].unitPrice);
            printf("Product Quantity: %d\n", items[i].quantityAvailable);
            printf("Product Description: %s\n", items[i].itemDescription);
            printf("Seller ID: %d\n", items[i].sellerID);
            printf("\n");

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

            found = 1;
        }

        if ((found == 1 && count > 0) && i == count - 1)
        {
            i = -1;
        }
    }
    if (found == 0)
    {
        printf("\nNo products found!\n");
    }
}

/**
 * @brief Adds an item to the cart.
 * @param items An array of Item structures.
 * @param itemCount The number of items in the array.
 * @param userID The ID of the user.
 * @param cart An array of Item structures representing the cart.
 * @param cartCount A pointer to the number of items in the cart.
 */
void addToCart(struct Item items[], int itemCount, int userID, struct Item cart[], int *cartCount)
{
    if (*cartCount >= 10)
    {
        printf("Cart is full! Please proceed to checkout or edit cart.\n");
    }
    else
    {
        int productID, quantity;
        printf("Enter product ID: ");
        scanf("%d", &productID);
        printf("Enter quantity: ");
        scanf("%d", &quantity);

        int found = 0;
        for (int i = 0; i < itemCount; i++)
        {
            if (items[i].productID == productID)
            {
                if (items[i].sellerID == userID)
                {
                    printf("You cannot buy your own product!\n");
                }
                else
                {
                    if (items[i].quantityAvailable >= quantity)
                    {
                        int inCart = 0;
                        for (int j = 0; j < *cartCount; j++)
                        {
                            if (cart[j].productID == productID)
                            {
                                printf("Product already in cart! Go to edit cart to edit the quantity.\n");
                                inCart = 1;
                            }
                        }
                        if (inCart == 0)
                        {
                            cart[*cartCount] = items[i];
                            cart[*cartCount].quantityAvailable = quantity;
                            *cartCount = *cartCount + 1;
                            printf("Product added to cart!\n");
                        }
                    }

                    else
                    {
                        printf("Not enough available!\n");
                    }
                }
                found = 1;
            }
        }
        if (found == 0)
        {
            printf("Product not found!\n");
        }
    }
}

/**
 * @brief Removes items from a given seller in the cart.
 * @param cart An array of Item structures representing the cart.
 * @param cartCount A pointer to the number of items in the cart.
 * @param sellerID The ID of the seller whose items should be removed.
 */
void RemoveItemsFromSeller(struct Item cart[], int *cartCount, int sellerID)
{
    for (int i = 0; i < *cartCount; i++)
    {
        if (cart[i].sellerID == sellerID)
        {
            for (int j = i; j < *cartCount - 1; j++)
            {
                cart[j] = cart[j + 1];
            }
            *cartCount = *cartCount - 1;
            i--;
        }
    }
}

/**
 * @brief Removes a specific item from the cart.
 * @param cart An array of Item structures representing the cart.
 * @param cartCount A pointer to the number of items in the cart.
 * @param productID The ID of the product to be removed.
 */
void RemoveSpecificItem(struct Item cart[], int *cartCount, int productID)
{
    for (int i = 0; i < *cartCount; i++)
    {
        if (cart[i].productID == productID)
        {
            for (int j = i; j < *cartCount - 1; j++)
            {
                cart[j] = cart[j + 1];
            }
            *cartCount = *cartCount - 1;
            i--;
        }
    }
}

/**
 * @brief Edits the quantity of a specific item in the cart.
 * @param cart An array of Item structures representing the cart.
 * @param cartCount A pointer to the number of items in the cart.
 * @param productID The ID of the product whose quantity should be edited.
 * @param quantity The new quantity for the specified product.
 */
void EditQuantity(struct Item cart[], int *cartCount, int productID, int quantity)
{
    int found = 0;
    if (quantity > 0)
    {
        for (int i = 0; i < *cartCount; i++)
        {
            if (cart[i].productID == productID)
            {
                cart[i].quantityAvailable = quantity;
                found = 1;
            }
        }
        if (found == 0)
        {
            printf("Product not found!\n");
        }
    }
    else
    {
        printf("Quantity must be greater than 0!\n");
    }
}

/**
 * @brief Checks out a specific product from the cart and updates the item quantity in the items array.
 * @param cart An array of Item structures representing the cart.
 * @param cartCount A pointer to the number of items in the cart.
 * @param productID The ID of the product to be checked out.
 * @param items An array of Item structures.
 * @param itemCount A pointer to the number of items in the array.
 * @param date A Date structure representing the current date.
 * @param userID The ID of the user.
 */
void checkOutByProduct(struct Item cart[], int *cartCount, int productID, struct Item items[], int *itemCount, struct Date date, int userID)
{
    int totalItems = 0;
    float total = 0;
    sortItems(cart, *cartCount);
    struct Item filerteredCart[2];
    for (int i = 0; i < *cartCount; i++)
    {
        if (cart[i].productID == productID)
        {
            if (totalItems == 0)
                printf("\nProduct ID\tItem Name\t\tQuantity\tUnit Price\tTotal Price\n");
            printf("%10d\t%-20s\t%8d\t%10.2f\t%11.2f\n", cart[i].productID, cart[i].itemName, cart[i].quantityAvailable, cart[i].unitPrice, cart[i].quantityAvailable * cart[i].unitPrice);
            total = total + (cart[i].quantityAvailable * cart[i].unitPrice);
            filerteredCart[totalItems] = cart[i];
            totalItems++;
        }
    }
    if (totalItems == 0)
    {
        printf("Product not found!\n");
    }
    else
    {
        printf("\nTotal: %0.2f\n", total);

        printf("Do you wanna proceed with the transaction? (Y/N): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'Y' || choice == 'y')
        {
            // update quantity
            for (int i = 0; i < *itemCount; i++)
            {
                if (items[i].productID == productID)
                {
                    items[i].quantityAvailable = items[i].quantityAvailable - filerteredCart[0].quantityAvailable;
                }
            }
            if (saveTransaction(filerteredCart, totalItems, date, userID) == 1)
            {
                // clear cart
                RemoveSpecificItem(cart, cartCount, productID);
                if (saveItems(items, *itemCount))
                {
                    printf("Transaction successful!\n");
                }
            }
            else
            {
                printf("Transaction failed!\n");
            }
        }
    }
}

/**
 * @brief Checks out all items from a specific seller in the cart and updates the item quantities in the items array.
 * @param cart An array of Item structures representing the cart.
 * @param cartCount A pointer to the number of items in the cart.
 * @param sellerID The ID of the seller whose items should be checked out.
 * @param items An array of Item structures.
 * @param itemCount A pointer to the number of items in the array.
 * @param date A Date structure representing the current date.
 * @param userID The ID of the user.
 */
void checkOutBySeller(struct Item cart[], int *cartCount, int sellerID, struct Item items[], int *itemCount, struct Date date, int userID)
{
    int found = 0, totalItems = 0;
    float total = 0;
    sortItems(cart, *cartCount);
    struct Item filerteredCart[*cartCount];
    for (int i = 0; i < *cartCount; i++)
    {
        if (cart[i].sellerID == sellerID)
        {
            if (found == 0)
                printf("\nProduct ID\tItem Name\t\tQuantity\tUnit Price\tTotal Price\n");
            printf("%10d\t%-20s\t%8d\t%10.2f\t%11.2f\n", cart[i].productID, cart[i].itemName, cart[i].quantityAvailable, cart[i].unitPrice, cart[i].quantityAvailable * cart[i].unitPrice);
            total = total + (cart[i].quantityAvailable * cart[i].unitPrice);
            found = 1;
            filerteredCart[totalItems] = cart[i];
            totalItems++;
        }
    }
    if (found)
    {
        printf("\nTotal: %0.2f\n", total);

        printf("Do you wanna proceed with the transaction? (Y/N): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'Y' || choice == 'y')
        {
            // update quantity
            for (int i = 0; i < *itemCount; i++)
            {
                for (int j = 0; j < totalItems; j++)
                {
                    if (items[i].productID == filerteredCart[j].productID)
                    {
                        items[i].quantityAvailable = items[i].quantityAvailable - filerteredCart[j].quantityAvailable;
                    }
                }
            }
            if (saveTransaction(filerteredCart, totalItems, date, userID) == 1)
            {
                // clear cart
                RemoveItemsFromSeller(cart, cartCount, sellerID);
                if (saveItems(items, *itemCount))
                {
                    printf("Transaction successful!\n");
                }
            }
            else
            {
                printf("Transaction failed!\n");
            }
        }
        else
        {
            printf("Transaction cancelled!\n");
        }
    }
    else
    {
        printf("No items in cart from this seller!\n");
    }
}

/**
 * @brief Displays and allows user to edit the items in the cart.
 * @param cart An array of Item structures representing the cart.
 * @param cartCount A pointer to the number of items in the cart.
 */
void editCart(struct Item cart[], int *cartCount)
{
    if (*cartCount == 0)
    {
        printf("\nCart is empty!\n");
    }
    else
    {
        sortItems(cart, *cartCount);
        printf("\nProduct ID\tItem Name\t\tCategory\tQuantity\tUnit Price\n\n");
        for (int i = 0; i < *cartCount; i++)
        {
            printf("%10d\t%-20s\t%-15s\t%8d\t%10.2f\n", cart[i].productID, cart[i].itemName, cart[i].category, cart[i].quantityAvailable, cart[i].unitPrice);
        }

        int choice;
        do
        {

            printf("\n[1] Remove all items from seller\n");
            printf("[2] Remove specific item\n");
            printf("[3] Edit quantity\n");
            printf("[4] Finish Edit\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                printf("Enter seller ID: ");
                int sellerID;
                scanf("%d", &sellerID);
                RemoveItemsFromSeller(cart, cartCount, sellerID);
                break;
            case 2:
                printf("Enter product ID: ");
                int productID;
                scanf("%d", &productID);
                RemoveSpecificItem(cart, cartCount, productID);
                break;
            case 3:
                printf("Enter product ID: ");
                int iProductID;
                scanf("%d", &iProductID);
                printf("Enter quantity: ");
                int quantity;
                scanf("%d", &quantity);
                EditQuantity(cart, cartCount, iProductID, quantity);
                break;
            case 4:
                break;
            default:
                printf("Please enter choice!\n");
                break;
            }
        } while (choice != 4);
    }
}

/**
 * @brief Checks out all items in the cart and saves the transaction.
 * @param cart An array of Item structures representing the cart.
 * @param cartCount A pointer to the number of items in the cart.
 * @param items An array of Item structures.
 * @param itemCount A pointer to the number of items in the array.
 * @param users An array of UserInfo structures.
 * @param userCount The number of users in the array.
 * @param date A Date structure representing the current date.
 * @param userID The ID of the user.
 */
void checkoutAll(struct Item cart[], int *cartCount, struct Item items[], int *itemCount, struct UserInfo users[], int userCount, struct Date date, int userID)
{
    int uniqueSellers[100];
    int sellerCount = getUniqueSellers(cart, *cartCount, uniqueSellers);
    float total = 0;

    for (int j = 0; j < *cartCount; j++)
    {
        total = total + (cart[j].unitPrice * cart[j].quantityAvailable);
    }

    printf("Transaction list:\n");
    for (int i = 0; i < sellerCount; i++)
    {
        // TODO: EDIT SHOW MY PRODUCTS
        showMyProducts(cart, *cartCount, uniqueSellers[i], sellerProductCount(cart, *cartCount, uniqueSellers[i]), 1);
        for (int j = 0; j < userCount; j++)
        {
            if (users[j].userID == uniqueSellers[i])
            {
                printf("Amount payable to seller %s (ID %d)\n", users[j].name, users[j].userID);
            }
        }
        printf("\n");
    }
    printf("Grand Total: %.2f\n", total);

    printf("Do you wanna proceed with the transaction? (Y/N): ");
    char choice;
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y')
    {
        // update quantity
        for (int i = 0; i < *itemCount; i++)
        {
            for (int j = 0; j < *cartCount; j++)
            {
                if (items[i].productID == cart[j].productID)
                {
                    items[i].quantityAvailable = items[i].quantityAvailable - cart[j].quantityAvailable;
                }
            }
        }
        if (saveTransaction(cart, *cartCount, date, userID) == 1)
        {
            // clear cart
            for (int i = 0; i < *cartCount; i++)
            {
                cart[i] = (struct Item){0, "", "", "", 0, 0, 0};
            }
            if (saveItems(items, *itemCount))
            {
                printf("Transaction successful!\n");
            }
            *cartCount = 0;
        }
        else
        {
            printf("Transaction failed!\n");
        }
    }
    else
    {
        printf("Transaction cancelled!\n");
    }
}

/**
 * @brief Displays the checkout menu to the user.
 * @param cart An array of Item structures representing the cart.
 * @param cartCount A pointer to the number of items in the cart.
 * @param items An array of Item structures.
 * @param itemCount A pointer to the number of items in the array.
 * @param users An array of UserInfo structures.
 * @param userCount The number of users in the array.
 * @param userID The ID of the user.
 */
void checkoutMenu(struct Item cart[], int *cartCount, struct Item items[], int *itemCount, struct UserInfo users[], int userCount, int userID)
{
    if (*cartCount == 0)
    {
        printf("Cart is empty!\n");
    }
    else
    {
        struct Date date;
        int choice;
        printf("Enter date (dd/mm/yyyy): ");
        scanf("%d/%d/%d", &date.day, &date.month, &date.year);

        printf("\n[1] Checkout All Items\n");
        printf("[2] Checkout Items by a Specific Seller\n");
        printf("[3] Checkout a Specific Item\n");
        printf("[4] Cancel Checkout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            checkoutAll(cart, cartCount, items, itemCount, users, userCount, date, userID);
            break;
        case 2:
            printf("Enter seller ID: ");
            int sellerID;
            scanf("%d", &sellerID);
            checkOutBySeller(cart, cartCount, sellerID, items, itemCount, date, userID);
            break;
        case 3:
            printf("Enter product ID: ");
            int productID;
            scanf("%d", &productID);
            checkOutByProduct(cart, cartCount, productID, items, itemCount, date, userID);
            break;
        case 4:
            break;
        default:
            printf("Please a valid enter choice!\n");
            break;
        }
    }
}

/**
 * @brief Displays the buy menu to the user and processes their selections.
 * @param userID The ID of the user.
 * @param items An array of Item structures.
 * @param itemCount A pointer to the number of items in the array.
 * @param users An array of UserInfo structures.
 * @param userCount The number of users in the array.
 * @param cart An array of Item structures representing the cart.
 * @param cartCount A pointer to the number of items in the cart.
 */
void BuyMenu(int userID, struct Item items[], int *itemCount, struct UserInfo users[], int userCount, struct Item cart[], int *cartCount)
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
            showProductsBySeller(items, *itemCount, users, userCount);
            break;
        case 3:
            searchProductsByCategory(items, *itemCount);
            break;
        case 4:
            searchProductsByName(items, *itemCount);
            break;
        case 5:
            addToCart(items, *itemCount, userID, cart, cartCount);
            break;
        case 6:
            editCart(cart, cartCount);
            break;
        case 7:
            checkoutMenu(cart, cartCount, items, itemCount, users, userCount, userID);
            break;
        case 8:
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }
}

/**
 * @brief Saves the contents of the cart to a file.
 * @param cart An array of Item structures representing the cart.
 * @param cartCount A pointer to the number of items in the cart.
 * @param userID The ID of the user.
 * @return 1 if the save operation was successful, 0 otherwise.
 */
void saveCart(struct Item cart[], int *cartCount, int userID)
{
    if (*cartCount > 0)
    {
        int ID = userID;
        FILE *fp;
        char filename[50];
        sprintf(filename, "%d", ID);
        strcat(filename, ".txt");
        fp = fopen(filename, "w");

        if (fp == NULL)
        {
            printf("Error opening file!\n");
        }

        for (int i = 0; i < *cartCount; i++)
        {
            fprintf(fp, "%d %d\n%s\n%s\n%s\n%d %.2f\n\n", cart[i].productID, cart[i].sellerID, cart[i].itemName, cart[i].category, cart[i].itemDescription, cart[i].quantityAvailable, cart[i].unitPrice);
        }
        fclose(fp);
    }
    else
    {
        int ID = userID;
        FILE *fp;
        char filename[50];
        sprintf(filename, "%d", ID);
        strcat(filename, ".txt");
        fp = fopen(filename, "w");
        fclose(fp);
    }
}