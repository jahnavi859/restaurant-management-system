#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MENU_FILE "menu.dat"
struct MenuItem {
    int itemId;
    char name[50];
    char category[20];
    float price;
    int available;  
};
struct OrderItem {
    int itemId;
    char itemName[50];
    int quantity;
    float price;
    float subtotal;
};
struct Order {
    int orderId;
    struct OrderItem items[20];
    int itemCount;
    float totalAmount;
};
struct MenuItem menu[100];
int menuCount = 0;
int nextItemId = 1;
struct Order orders[50];
int orderCount = 0;
int nextOrderId = 1;
void displayMainMenu();
void addMenuItem();
void displayMenu();
void searchMenuItem();
void updateMenuItem();
void deleteMenuItem();
void placeOrder();
void generateBill();
void pauseScreen();
void saveMenuToFile();
void loadMenuFromFile();
int main() {
    int choice;
    printf("\n");
    printf("   RESTAURANT MANAGEMENT SYSTEM\n");
    printf("\nWelcome! Starting the system...\n");
    pauseScreen();
    
    while(1) {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addMenuItem();
                break;
            case 2:
                displayMenu();
                break;
            case 3:
                searchMenuItem();
                break;
            case 4:
                updateMenuItem();
                break;
            case 5:
                deleteMenuItem();
                break;
            case 6:
                placeOrder();
                break;
            case 7:
                generateBill();
                break;
            case 8:
                printf("\n✓ Thank you for using Restaurant Management System!\n");
                printf("Exiting...\n\n");
                exit(0);
            default:
                printf("\n✗ Invalid choice! Please try again.\n");
                pauseScreen();
        }
    }
    return 0;
}
void displayMainMenu() {
    printf("\n");
    printf("   RESTAURANT MANAGEMENT SYSTEM\n");
    printf("\n");
    printf("  1. Add New Menu Item\n");
    printf("  2. Display Menu\n");
    printf("  3. Search Menu Item\n");
    printf("  4. Update Menu Item\n");
    printf("  5. Delete Menu Item\n");
    printf("  6. Place Order\n");
    printf("  7. Generate Bill\n");
    printf("  8. Exit\n");
    printf("\n");
}
void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}
void addMenuItem() {
    printf("        ADD NEW MENU ITEM\n");
    
    if(menuCount >= 100) {
        printf(" Menu is full! Cannot add more items.\n");
        pauseScreen();
        return;
    }
    
    struct MenuItem newItem;
    newItem.itemId = nextItemId++;
    printf("Enter item name: ");
    getchar();
    fgets(newItem.name, 50, stdin);
    newItem.name[strcspn(newItem.name, "\n")] = 0;
    
    printf("Enter category (Starter/Main/Dessert/Beverage): ");
    fgets(newItem.category, 20, stdin);
    newItem.category[strcspn(newItem.category, "\n")] = 0;
    printf("Enter price (in ₹): ");
    scanf("%f", &newItem.price);
    newItem.available = 1;
    menu[menuCount++] = newItem;
    saveMenuToFile();
    printf("\nMenu item added successfully!\n");
    printf("  ID: %d\n", newItem.itemId);
    printf("  Name: %s\n", newItem.name);
    printf("  Category: %s\n", newItem.category);
    printf("  Price: ₹%.2f\n", newItem.price);
    printf("  Status: Available\n");
    pauseScreen();
}
void displayMenu() {
   
    printf("                         MENU\n");
    
    if(menuCount == 0) {
        printf("No items in menu yet!\n");
        pauseScreen();
        return;
    }
    printf("%-5s %-30s %-15s %-10s %-10s\n", "ID", "Name", "Category", "Price", "Status");
    for(int i = 0; i < menuCount; i++) {
        printf("%-5d %-30s %-15s ₹%-9.2f %-10s\n", 
               menu[i].itemId, 
               menu[i].name, 
               menu[i].category,
               menu[i].price,
               menu[i].available ? "Available" : "Out of Stock");
    }
    printf("\nTotal Items: %d\n", menuCount);
    pauseScreen();
}void searchMenuItem() {
    printf("        SEARCH MENU ITEM\n");
    if(menuCount == 0) {
        printf(" No items in menu to search!\n");
        pauseScreen();
        return;
    }
    int searchType;
    printf("Search by:\n1. Item ID\n2. Item Name\n");
    printf("Enter choice: ");
    scanf("%d", &searchType);
    if(searchType == 1) {
        int id, found = 0;
        printf("\nEnter Item ID: ");
        scanf("%d", &id);
        for(int i = 0; i < menuCount; i++) {
            if(menu[i].itemId == id) {
                found = 1;
                printf("\n Item Found!\n");
                printf("ID: %d\n", menu[i].itemId);
                printf("Name: %s\n", menu[i].name);
                printf("Category: %s\n", menu[i].category);
                printf("Price: ₹%.2f\n", menu[i].price);
                printf("Status: %s\n", menu[i].available ? "Available" : "Out of Stock");
                break;
            }
        }
        if(!found) {
            printf("\n Item with ID %d not found!\n", id);
        }
    }
    else if(searchType == 2) {
        char searchName[50];
        int found = 0;
        
        printf("\nEnter Item Name (partial or full): ");
        getchar();
        fgets(searchName, 50, stdin);
        searchName[strcspn(searchName, "\n")] = 0;
        
        printf("\n");
        printf("                      SEARCH RESULTS\n");
        
        for(int i = 0; i < menuCount; i++) {
            char menuNameLower[50], searchNameLower[50];
            strcpy(menuNameLower, menu[i].name);
            strcpy(searchNameLower, searchName);
            for(int j = 0; menuNameLower[j]; j++) {

                menuNameLower[j] = tolower(menuNameLower[j]);
            }
            for(int j = 0; searchNameLower[j]; j++) {
                searchNameLower[j] = tolower(searchNameLower[j]);
            }
            
            if(strstr(menuNameLower, searchNameLower) != NULL) {
                if(!found) {
                    printf("%-5s %-30s %-15s %-10s %-10s\n", "ID", "Name", "Category", "Price", "Status");
                }
                found = 1;
                printf("%-5d %-30s %-15s ₹%-9.2f %-10s\n", 
                       menu[i].itemId, 
                       menu[i].name, 
                       menu[i].category, 
                       menu[i].price,
                       menu[i].available ? "Available" : "Out of Stock");
                    }
        }
        if(!found) {
            printf(" No items found matching '%s'\n", searchName);
        } else {
            printf("\n");
        }
    }
    else {
        printf("\n Invalid choice!\n");
    }
    pauseScreen();
}
void updateMenuItem() {
    printf("        UPDATE MENU ITEM\n");
    if(menuCount == 0) {
        printf("✗ No items in menu to update!\n");
        pauseScreen();
        return;
    }
    int id, found = 0, index;
    printf("Enter Item ID to update: ");
    scanf("%d", &id);
    for(int i = 0; i < menuCount; i++) {
        if(menu[i].itemId == id) {
            found = 1;
            index = i;
            break;
        }
    }
    if(!found) {
        printf("\n✗ Item with ID %d not found!\n", id);
        pauseScreen();
        return;
    }
    printf("\nCurrent Details:\n");
    printf("Name: %s\n", menu[index].name);
    printf("Category: %s\n", menu[index].category);
    printf("Price: ₹%.2f\n", menu[index].price);
    printf("Status: %s\n", menu[index].available ? "Available" : "Out of Stock");
    int choice;
    printf("What do you want to update?\n");
    printf("1. Price\n");
    printf("2. Availability\n");
    printf("3. Both\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    if(choice == 1 || choice == 3) {
        printf("\nEnter new price: ₹");
        scanf("%f", &menu[index].price);
    }
    if(choice == 2 || choice == 3) {
        printf("\nIs item available? (1 = Yes, 0 = No): ");
        scanf("%d", &menu[index].available);
    }
    saveMenuToFile();
    printf("\n Menu item updated successfully!\n");
    pauseScreen();
}
void deleteMenuItem() {

    printf("        DELETE MENU ITEM\n");
    if(menuCount == 0) {
        printf("✗ No items in menu to delete!\n");
        pauseScreen();
        return;
    }
    int id, found = 0, index;
    printf("Enter Item ID to delete: ");
    scanf("%d", &id);
    for(int i = 0; i < menuCount; i++) {
        if(menu[i].itemId == id) {
            found = 1;
            index = i;
            break;
        }
    }
    if(!found) {
        printf("\n Item with ID %d not found!\n", id);
        pauseScreen();
        return;
    }
    printf("\nItem to be deleted:\n");
    printf("ID: %d\n", menu[index].itemId);
    printf("Name: %s\n", menu[index].name);
    printf("Price: ₹%.2f\n", menu[index].price);
    char confirm;
    printf("Are you sure you want to delete? (y/n): ");
    scanf(" %c", &confirm);
    if(confirm == 'y' || confirm == 'Y') {
        for(int i = index; i < menuCount - 1; i++) {
            menu[i] = menu[i + 1];
        }
        menuCount--;
        saveMenuToFile();
        printf("\n Menu item deleted successfully!\n");
    } else {
        printf("\n Deletion cancelled.\n");
    }
    pauseScreen();
}void placeOrder() {
    printf("          PLACE ORDER\n");
    if(menuCount == 0) {
        printf(" No items in menu! Please add items first.\n");
        pauseScreen();
        return;
    }
    struct Order newOrder;
    newOrder.orderId = nextOrderId++;
    newOrder.itemCount = 0;
    newOrder.totalAmount = 0;
    printf("Order ID: %d\n\n", newOrder.orderId);
    printf("Available Menu Items:\n");
    for(int i = 0; i < menuCount; i++) {
        if(menu[i].available) {
            printf("%d. %s - ₹%.2f\n", menu[i].itemId, menu[i].name, menu[i].price);
        }
    }
    char addMore;
    do {
        int itemId, quantity, found = 0;
        printf("Enter Item ID: ");
        scanf("%d", &itemId);
        for(int i = 0; i < menuCount; i++) {
            if(menu[i].itemId == itemId && menu[i].available) {
                found = 1;
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                struct OrderItem oi;
                oi.itemId = menu[i].itemId;
                strcpy(oi.itemName, menu[i].name);
                oi.quantity = quantity;
                oi.price = menu[i].price;
                oi.subtotal = oi.price * quantity;
                newOrder.items[newOrder.itemCount++] = oi;
                newOrder.totalAmount += oi.subtotal;
                printf("Added: %s x %d = ₹%.2f\n\n", oi.itemName, quantity, oi.subtotal);
                break;
            }
        }
        if(!found) {
            printf("Item not found or not available!\n\n");
        }
        printf("Add more items? (y/n): ");
        scanf(" %c", &addMore);
        printf("\n");
    } while((addMore == 'y' || addMore == 'Y') && newOrder.itemCount < 20);
    if(newOrder.itemCount > 0) {
        orders[orderCount++] = newOrder;
        printf(" Order placed successfully!\n");
        printf("Order ID: %d\n", newOrder.orderId);
        printf("Total Amount: ₹%.2f\n", newOrder.totalAmount);
    } else {
        printf("No items added to order!\n");
    }
    pauseScreen();
}
void generateBill(){
    printf("         GENERATE BILL\n");
    if(orderCount == 0) {
        printf(" No orders placed yet!\n");
        pauseScreen();
        return;
    }
    int orderId, found = 0, index;
    printf("Enter Order ID: ");
    scanf("%d", &orderId);
    for(int i = 0; i < orderCount; i++) {
        if(orders[i].orderId == orderId) {
            found = 1;
            index = i;
            break;
        }
    }
    if(!found) {
        printf("\n Order ID %d not found!\n", orderId);
        pauseScreen();
        return;
    }
    struct Order ord = orders[index];
    printf("\n");
    printf("                       RESTAURANT BILL\n");
    printf("Order ID: %d\n", ord.orderId);
    
    printf("%-30s %10s %12s %12s\n", "Item", "Quantity", "Price", "Subtotal");
    
    for(int i = 0; i < ord.itemCount; i++) {
        printf("%-30s %10d %12.2f %12.2f\n", ord.items[i].itemName,ord.items[i].quantity,ord.items[i].price,ord.items[i].subtotal);
    }
    printf("%54s ₹%.2f\n", "TOTAL AMOUNT:", ord.totalAmount);
    printf("\n           Thank you for dining with us!\n");
    pauseScreen();
}
void saveMenuToFile() {
    FILE *fp = fopen(MENU_FILE, "wb");
    if(fp == NULL) {
        printf("\nError: Could not save menu to file!\n");
        return;
    }
    fwrite(&menuCount, sizeof(int), 1, fp);
    fwrite(menu, sizeof(struct MenuItem), menuCount, fp);
    fwrite(&nextItemId, sizeof(int), 1, fp);
    fclose(fp);
}
void loadMenuFromFile() {
    FILE *fp = fopen(MENU_FILE, "rb");
    if(fp == NULL) {
        printf("No saved menu found. Starting fresh.\n");
        return;
    }
    fread(&menuCount, sizeof(int), 1, fp);
    fread(menu, sizeof(struct MenuItem), menuCount, fp);
    fread(&nextItemId, sizeof(int), 1, fp);
    fclose(fp);
    printf("Loaded %d menu items from file.\n", menuCount);
}