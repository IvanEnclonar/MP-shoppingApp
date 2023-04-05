#include "register.c"

struct Item addNewItem()
{
    struct Item newItem;

    printf("Enter product ID: ");
    scanf("%d", &newItem.productID);
    printf("Enter item name: ");
    scanf("%s", newItem.itemName);
    printf("Enter category: ");
    scanf("%s", newItem.category);
    printf("Enter item description: ");
    scanf("%s", newItem.itemDescription);
    printf("Enter quantity available: ");
    scanf("%d", &newItem.quantityAvailable);
    printf("Enter unit price: ");
    scanf("%f", &newItem.unitPrice);
    printf("Enter seller ID: ");
    scanf("%d", &newItem.sellerID);

    return newItem;
}