#include "ENCLONAR.h"

int scanUsers(struct UserInfo users[], int numUsers, int userID)
{
    for (int i = 0; i < numUsers; i++)
    {
        if (userID == users[i].userID)
        {
            return 0;
        }
    }
    return 1;
}

int getUniqueUserID(struct UserInfo users[], int numUsers)
{
    int userID = 0, isUnique = 0;
    do
    {
        printf("Enter your userID (must be unique): ");
        scanf("%d", &userID);

        if (scanUsers(users, numUsers, userID))
        {
            isUnique = 1;
        }
        else
        {
            printf("User ID already exists!\n");
        }
    } while (isUnique == 0);

    return userID;
}

struct UserInfo registerUser(int userID)
{
    struct UserInfo newUser;
    newUser.userID = userID;

    printf("Enter your password (up to 10 characters): ");
    scanf("%s", newUser.password);

    printf("Enter your address (up to 30 characters): ");
    scanf(" %[^\n]", newUser.address);

    printf("Enter your contact number: ");
    scanf("%d", &newUser.contactNumber);

    printf("Enter your name (up to 20 characters): ");
    scanf("%s", newUser.name);

    return newUser;
}