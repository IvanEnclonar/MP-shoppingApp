#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

struct User
{
    int userID;
    char password[11];
    char address[31];
    int contactNumber;
    char name[21];
};

struct User users[MAX_USERS];
int numUsers = 0;

int isUserIDTaken(int userID)
{
    for (int i = 0; i < numUsers; i++)
    {
        if (users[i].userID == userID)
        {
            return 1;
        }
    }
    return 0;
}

void registerUser()
{
    printf("Enter your userID (must be unique): ");
    int userID;
    scanf("%d", &userID);

    if (isUserIDTaken(userID))
    {
        printf("That userID is already taken. Please choose another.\n");
        return;
    }

    struct User newUser;
    newUser.userID = userID;

    printf("Enter your password (up to 10 characters): ");
    scanf("%s", newUser.password);

    printf("Enter your address (up to 30 characters): ");
    scanf(" %[^\n]", newUser.address);

    printf("Enter your contact number: ");
    scanf("%d", &newUser.contactNumber);

    printf("Enter your name (up to 20 characters): ");
    scanf("%s", newUser.name);

    users[numUsers++] = newUser;

    printf("User registered successfully.\n");
}

int main()
{
    int choice;

    do
    {
        printf("Menu:\n");
        printf("[1] Register as a User\n");
        printf("[2] Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 2);

    return 0;
}
