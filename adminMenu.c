#include "buyMenu.c"

void showAllSellers(struct UserInfo users[], int numUsers)
{
    printf("User ID\tPassword\tName\tAddress\tContact Number");
    for (int i = 0; i < numUsers; i++)
    {
    }
}
void adminMenu(struct UserInfo users[], int *userCount, struct Item items[], int *itemCount)
{
    char input[20];
    printf("Enter password: ");
    scanf("%s", input);

    if (strcmp("H3LLo?", input) == 0)
    {
        printf("Welcome to the admin menu!\n");

        printf("[1] Show All Users\n");
        printf("[2] Show All Sellers\n");
        printf("[3] Show All Sales in a Given Duration\n");
        printf("[4] Show All Seller Sales\n");
        printf("[5] Show Shopaholics\n");
        printf("[6] Back to Main Menu\n");
        printf("Enter choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            break;
        default:
            printf("Please enter a valid choice!\n");
            break;
        }
    }
    else
    {
        printf("Unauthorized access not allowed\n");
    }
}