#include "sellMenu.c"

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
            return 1;
        }
    }
    printf("Invalid userID or password. Please try again.\n");
    return 0;
}

void printMenu()
{
    printf("\n[1] Register User\n");
    printf("[2] Main Menu\n");
    printf("[0] Exit\n");
}

void printUserMenu()
{
    printf("\n[1] Sell Menu\n");
    printf("[2] Buy Menu\n");
    printf("[3] Exit User Menu\n");
}

int main()
{
    int choice = 1;
    struct UserInfo users[100];
    struct Item items[100];
    int userCount = 0;

    while (choice != 0)
    {
        printMenu();
        printf("Enter choice: ");
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
            users[userCount] = registerUser(getUniqueUserID(users, userCount));
            userCount++;
            break;
        case 2:
            if (login(users, userCount))
            {
                int userMenuChoice = 0;
                printf("Logged in successfully.\n");
                printUserMenu();
                printf("Enter choice: ");
                scanf(" %d", &userMenuChoice);
                switch (userMenuChoice)
                {
                case 1:

                    break;
                }
            }
            break;
        case 0:
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }
}