#include <stdio.h>
#include <string.h>

struct Date
{
    int month;
    int day;
    int year;
};

struct UserInfo
{
    int userID;
    char password[11];
    char address[31];
    int contactNumber;
    char name[21];
};

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