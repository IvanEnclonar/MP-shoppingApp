#include <stdio.h>
#include <string.h>

/**
 * @brief Initializes a Date structure with provided values.
 * @param month The month (1-12) of the date.
 * @param day The day (1-31) of the month.
 * @param year The year of the date.
 * @return A Date structure with the specified month, day, and year.
 */
struct Date
{
    int month;
    int day;
    int year;
};

/**
 * @brief Initializes a UserInfo structure with provided values.
 * @param userID Unique ID of the user.
 * @param password Password of the user (maximum length 10 characters).
 * @param address User's address (maximum length 30 characters).
 * @param contactNumber User's contact number.
 * @param name User's name (maximum length 20 characters).
 * @return A UserInfo structure with the specified values.
 */
struct UserInfo
{
    int userID;
    char password[11];
    char address[31];
    int contactNumber;
    char name[21];
};

/**
 * @brief Initializes an Item structure with provided values.
 * @param productID Unique ID of the product.
 * @param itemName Name of the item (maximum length 20 characters).
 * @param category Category of the item (maximum length 15 characters).
 * @param itemDescription Description of the item (maximum length 30 characters).
 * @param quantityAvailable Quantity of the item available in stock.
 * @param unitPrice Unit price of the item.
 * @param sellerID Unique ID of the seller.
 * @return An Item structure with the specified values.
 */
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

/**
 * @brief Initializes a Transaction structure with provided values.
 * @param date Date structure representing the date of the transaction.
 * @param productID Unique ID of the product.
 * @param itemName Name of the item (maximum length 20 characters).
 * @param category Category of the item (maximum length 15 characters).
 * @param itemDescription Description of the item (maximum length 30 characters).
 * @param quantityBought Quantity of the item bought.
 * @param unitPrice Unit price of the item.
 * @param sellerID Unique ID of the seller.
 * @param buyerID Unique ID of the buyer.
 * @return A Transaction structure with the specified values.
 */
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