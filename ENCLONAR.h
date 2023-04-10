#include <stdio.h>
#include <string.h>

// Structure used to tract the date
struct Date
{
    int month;
    int day;
    int year;
};

// Structure used to store the user information
struct UserInfo
{
    int userID;
    char password[11];
    char address[31];
    int contactNumber;
    char name[21];
};

// Structure used to store the item information
struct Item
{
    int productID;
    char itemName[21];
    char category[16];
    char itemDescription[31];
    int quantityAvailable;
    float unitPrice;
    int sellerID;
};

// Structure used to store the transaction information
struct Transaction
{
    struct Date date;
    int productID;
    char itemName[21];
    char category[16];
    char itemDescription[31];
    int quantityBought;
    float unitPrice;
    int sellerID;
    int buyerID;
};