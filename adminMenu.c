#include "buyMenu.c"

void showAllUsers(struct UserInfo users[], int numUsers)
{
    // TODO: Update output formatting
    printf("User ID\tPassword\tName\tAddress\tContact Number\n");
    for (int i = 0; i < numUsers; i++)
    {
        printf("%d\t%s\t\t%s\t%s\t%d\n", users[i].userID, users[i].password, users[i].name, users[i].address, users[i].contactNumber);
    }
}

void showAllSellers(struct UserInfo users[], int numUsers, int uniqueSellers[], int numUniqueSellers, struct Item items[], int numItems)
{
    // TODO: Update output formatting
    printf("User ID\tPassword\tName\tAddress\tContact Num\tItems for sale\n");
    for (int i = 0; i < numUsers; i++)
    {
        for (int j = 0; j < numUniqueSellers; j++)
        {
            if (users[i].userID == uniqueSellers[j])
            {
                printf("%d\t%s\t\t%s\t%s\t%d\t\t%d\n", users[i].userID, users[i].password, users[i].name, users[i].address, users[i].contactNumber, sellerProductCount(items, numItems, users[i].userID));
            }
        }
    }
}

int compare_dates(struct Date date1, struct Date date2)
{
    if (date1.year < date2.year)
    {
        return -1;
    }
    else if (date1.year > date2.year)
    {
        return 1;
    }
    else if (date1.month < date2.month)
    {
        return -1;
    }
    else if (date1.month > date2.month)
    {
        return 1;
    }
    else if (date1.day < date2.day)
    {
        return -1;
    }
    else if (date1.day > date2.day)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int getUniqueBuyers(struct Transaction items[], int itemCount, int uniqueSellers[])
{
    int count = 0;
    for (int i = 0; i < itemCount; i++)
    {
        int found = 0;
        for (int j = 0; j < count; j++)
        {
            if (items[i].buyerID == uniqueSellers[j])
            {
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            uniqueSellers[count] = items[i].buyerID;
            count++;
        }
    }

    return count;
}

int getUniqueSellersT(struct Transaction items[], int itemCount, int uniqueSellers[])
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

int getTransactionInDuration(struct Transaction transactions[], int numTransactions, struct Transaction temp[])
{
    struct Date startDate, endDate;
    int found = 0;
    printf("Enter start date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &startDate.day, &startDate.month, &startDate.year);
    printf("Enter end date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &endDate.day, &endDate.month, &endDate.year);

    int result = compare_dates(startDate, endDate);

    if (result == 1)
    {
        printf("\nStart date must be before end date!\n");
        return -1;
    }
    else if (result == 0)
    {
        printf("\nStart date and end date cannot be the same!\n");
        return -1;
    }
    else
    {
        int counter = 0;
        for (int i = 0; i < numTransactions; i++)
        {
            if (compare_dates(transactions[i].date, startDate) == 1 && compare_dates(transactions[i].date, endDate) == -1)
            {
                temp[counter] = transactions[i];
                counter += 1;
            }
        }
        return counter;
    }
}

void showShopaholics(struct Transaction transactions[], int numTransactions, struct UserInfo users[], int numUsers)
{
    struct Transaction newTransactions[50];
    int counter = getTransactionInDuration(transactions, numTransactions, newTransactions);
    if (counter > 0)
    {
        int uniqueBuyers[20];
        float tottalSales[20];
        int numUniqueBuyers = getUniqueBuyers(newTransactions, counter, uniqueBuyers);

        for (int i = 0; i < numUniqueBuyers; i++)
        {
            for (int j = 0; j < counter; j++)
            {
                if (uniqueBuyers[i] == newTransactions[j].buyerID)
                {
                    tottalSales[i] += (newTransactions[j].quantityBought * newTransactions[j].unitPrice);
                }
            }
        }

        printf("Buyer ID\tName\t\tTotal Purchases\n");
        for (int i = 0; i < numUniqueBuyers; i++)
        {
            for (int j = 0; j < numUsers; j++)
            {
                if (uniqueBuyers[i] == users[j].userID)
                {
                    printf("%d\t\t%s\t\t%.2f\n", users[j].userID, users[j].name, tottalSales[i]);
                }
            }
        }
    }
    else
    {
        printf("No transactions found in the given duration!\n");
    }
}
void showSellerSales(struct Transaction transactions[], int numTransactions, struct UserInfo users[], int numUsers)
{
    // TODO: GET Seller Name
    struct Transaction newTransactions[50];
    int counter = getTransactionInDuration(transactions, numTransactions, newTransactions);
    if (counter > 0)
    {
        int uniqueSellers[20];
        float tottalSales[20];
        int numUniqueSellers = getUniqueSellersT(newTransactions, counter, uniqueSellers);

        for (int i = 0; i < numUniqueSellers; i++)
        {
            for (int j = 0; j < counter; j++)
            {
                if (uniqueSellers[i] == newTransactions[j].sellerID)
                {
                    tottalSales[i] += (newTransactions[j].quantityBought * newTransactions[j].unitPrice);
                }
            }
        }

        printf("Seller ID\tTotal Sales\n");
        for (int i = 0; i < numUniqueSellers; i++)
        {
            for (int j = 0; j < numUsers; j++)
            {
                if (uniqueSellers[i] == users[j].userID)
                {
                    printf("%d\t\t%s\t\t%.2f\n", users[j].userID, users[j].name, tottalSales[i]);
                }
            }
        }
    }
    else
    {
        printf("No transactions found in the given duration!\n");
    }
}

void showSalesInDuration(struct Transaction transactions[], int numTransactions)
{
    struct Date startDate, endDate;
    int found = 0;
    printf("Enter start date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &startDate.day, &startDate.month, &startDate.year);
    printf("Enter end date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &endDate.day, &endDate.month, &endDate.year);

    int result = compare_dates(startDate, endDate);
    if (result == 1)
    {
        printf("Start date must be before end date!\n");
    }
    else if (result == 0)
    {
        printf("Start date and end date cannot be the same!\n");
    }
    else
    {
        float tottalSales = 0;
        for (int i = 0; i < numTransactions; i++)
        {
            if (compare_dates(transactions[i].date, startDate) == 1 && compare_dates(transactions[i].date, endDate) == -1)
            {
                if (found == 0)
                {
                    printf("\nProduct ID\tItem Name\tQuantity Available\tUnit Price\tTotal Price\n");
                }
                tottalSales += (transactions[i].quantityBought * transactions[i].unitPrice);
                printf("%10d\t%s\t%18d\t%10.2f\t%10.2f\n", transactions[i].productID, transactions[i].itemName, transactions[i].quantityBought, transactions[i].unitPrice, transactions[i].quantityBought * transactions[i].unitPrice);
                found = 1;
            }
        }
        if (found == 0)
        {
            printf("No sales found in the given duration!\n");
        }
        else
        {
            printf("\nTotal sales for that duration: %.2f\n", tottalSales);
        }
    }
}

void adminMenu(struct UserInfo users[], int *userCount, struct Item items[], int *itemCount)
{
    char input[20];
    printf("Enter password: ");
    scanf("%s", input);

    if (strcmp("H3LLo?", input) == 0)
    {
        printf("\nWelcome to the admin menu!\n");
        int choice;
        struct Transaction transactions[100];
        int transactionCount = 0;
        loadTransaction(transactions, &transactionCount);
        do
        {
            printf("\n[1] Show All Users\n");
            printf("[2] Show All Sellers\n");
            printf("[3] Show All Sales in a Given Duration\n");
            printf("[4] Show All Seller Sales\n");
            printf("[5] Show Shopaholics\n");
            printf("[6] Back to Main Menu\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                showAllUsers(users, *userCount);
                break;
            case 2:
                int uniqueSellers[50];
                int numUniqueSellers = getUniqueSellers(items, *itemCount, uniqueSellers);
                showAllSellers(users, *userCount, uniqueSellers, numUniqueSellers, items, *itemCount);
                break;
            case 3:
                showSalesInDuration(transactions, transactionCount);
                break;
            case 4:
                showSellerSales(transactions, transactionCount, users, *userCount);
                break;
            case 5:
                showShopaholics(transactions, transactionCount, users, *userCount);
                break;
            default:
                printf("Please enter a valid choice!\n");
                break;
            }
        } while (choice != 6);
    }
    else
    {
        printf("Unauthorized access not allowed\n");
    }
}