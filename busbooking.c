#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

// Define the structure for the Binary Search Tree (BST) node
typedef struct BinarySearchTree BST;
struct BinarySearchTree {
    int PassnNo;          // Passenger number (unique ID for each reservation)
    char name[10];        // Name of the passenger
    struct BinarySearchTree *left;  // Pointer to the left child
    struct BinarySearchTree *right; // Pointer to the right child
};

// Global variables
BST *root = NULL;
int busSeat[32][9] = {0}; // 2D array representing seat status for each bus
// Function prototypes
int cost(BST *r);
void status();
void busLists();
void DisplaySeat(int bus[33]);
void cancel(int x);
BST *reservationInfo(BST *, int, int *);
BST *insert(BST **r, int custID);
void login();
void redColor();
void greencolor();
void blueColor();
void resetColor();

// Function to change text color to red
void redColor() {
    printf("\033[1;31m");
}

// Function to change text color to green
void greencolor() {
    printf("\033[1;32m");
}

// Function to change text color to blue
void blueColor() {
    printf("\033[1;34m");
}

// Function to reset text color to default
void resetColor() {
    printf("\033[0m");
}

// Function to display reservation information based on customer ID
BST *reservationInfo(BST *r, int s, int *custIDmatched) {
    if (r == NULL) return NULL;
    BST *presentnode = r; // Start from the root
    while (presentnode) { // Traverse the tree
        if (presentnode->PassnNo == s) { // Check if current node's passenger number matches the search
            *custIDmatched = 1; // Update match flag
            redColor(); // Set text color to red
            printf("\n-----------------------------------------------------------------");
            printf("\n||              NAME: %10s                               ||", (presentnode->name));
            printf("\n||              CUSTOMER ID: %d                              ||", presentnode->PassnNo);
            printf("\n||              BUS NUMBER: %d                                  ||", (presentnode->PassnNo) / 1000);
            printf("\n||              SEAT NUMBER: %d                                ||", (presentnode->PassnNo) % 100);
            printf("\n||              TICKET COST: Rs.%d                             ||", cost(presentnode));
            printf("\n-----------------------------------------------------------------");
            resetColor(); // Reset text color
            getch(); // Wait for user input
            return r;
        } else if (presentnode->PassnNo > s) { // Traverse left subtree if search value is smaller
            presentnode = presentnode->left;
        } else { // Traverse right subtree if search value is larger
            presentnode = presentnode->right;
        }
    }
    return NULL;
}

// Function to insert a new reservation into the BST
BST *insert(BST **r, int custId) {
    if (*r == NULL) { // If the tree is empty, create a new node
        *r = (BST *)malloc(sizeof(BST));
        (*r)->PassnNo = custId; // Assign the customer ID
        if (*r == NULL) {
            printf("No memory…");
            return NULL;
        } else {
            (*r)->left = (*r)->right = NULL; // Initialize left and right children to NULL
            printf("\n   ENTER THE PERSON NAME: ");
            scanf("%s", &((*r)->name)); // Read passenger name
        }
    } else { // Traverse the tree to find the correct position for the new node
        if ((*r)->PassnNo > custId) { // Go to the left subtree
            (*r)->left = insert(&((*r)->left), custId);
        } else if ((*r)->PassnNo < custId) { // Go to the right subtree
            (*r)->right = insert(&((*r)->right), custId);
        }
    }
    return *r;
}

// Function to display seat status for a bus
void DisplaySeat(int bus[33]) {
    for (int i = 1; i <= 32; i++) { // Loop through all 32 seats
        redColor(); // Set text color to red for seat numbers
        if (i < 10 && i > 0) { // Format single digit seat numbers
            printf("0%d .", i);
        } else {
            printf("%d .", i);
        }
        resetColor(); // Reset text color
        if (bus[i] == 0) // Check if seat is empty
            printf("EMPTY ");
        else // Otherwise, seat is booked
            printf("BOOKED");
        printf("         ");
        if (i % 4 == 0) // Print a newline after every 4 seats
            printf("\n");
    }
}

// Function to handle user login
void login() {
    char userName[20] = "user";
    char passWord[10] = "team15";
    char matchPass[10];
    char matchUser[10];
    int value;

    redColor(); // Set text color to red for welcome message
    printf("\n\n=========================================================================================\n");
    printf("\n\t\t\tWELCOME TO ONLINE BUS RESERVATION");
    printf("\n\n=========================================================================================\n\n");
    resetColor(); // Reset text color

login:
    blueColor(); // Set text color to blue for input prompts
    printf("\n\nUserName: ");
    resetColor(); // Reset text color
    greencolor(); // Set text color to green for user input
    gets(matchUser); // Read username
    resetColor(); // Reset text color
    blueColor(); // Set text color to blue for password prompt
    printf("\nPassWord: ");
    resetColor(); // Reset text color
    greencolor(); // Set text color to green for password input
    gets(matchPass); // Read password
    resetColor(); // Reset text color
    value = strcmp(passWord, matchPass); // Compare input password with stored password
    if (value != 0 || strcmp(userName, matchUser) != 0) { // If credentials do not match
        redColor(); // Set text color to red for error message
        printf("\nINVALID DETAILS TRY AGAIN...\n");
        resetColor(); // Reset text color
        goto login; // Go back to login prompt
    } else {
        greencolor(); // Set text color to green for success message
        printf("\nLOGGED IN SUCCESSFULLY...\n");
        resetColor(); // Reset text color
    }
}

// Function to calculate ticket cost based on bus number
int cost(BST *r) {
    int buscost = (r->PassnNo) / 1000; // Extract bus number from passenger number
    switch (buscost % 3) { // Determine cost based on bus number
        case 1: return 700; // Cost for bus numbers divisible by 3 with remainder 1
        case 2: return 550; // Cost for bus numbers divisible by 3 with remainder 2
        case 0: return 400; // Cost for bus numbers divisible by 3 with remainder 0
        default: return 0;
    }
}

// Function to display bus seat status
void status() {
    int busNum;
    busLists(); // Display available buses
busInput:
    printf("\n\nENTER YOUR BUS NUMBER : ");
    scanf("%d", &busNum); // Read bus number from user
    if (busNum <= 0 || busNum >= 10) { // Validate bus number
        redColor(); // Set text color to red for error message
        printf("\n  PLEASE ENTER CORRECT BUS NUMBER !!\n");
        resetColor(); // Reset text color
        goto busInput; // Go back to bus number prompt
    }
    printf("\n");
    DisplaySeat(busSeat[busNum]); // Display seat status for the selected bus
    getch(); // Wait for user input
}

// Function to display the list of available buses
void busLists() {
    redColor(); // Set text color to red for header
    printf("------------------------------------------------------------------------------------------------");
    printf("\nBus.No\tName\t\t\tDestinations      \t\tCharges       \t\tTime\n");
    printf("------------------------------------------------------------------------------------------------");
    resetColor(); // Reset text color
    printf("\n1\tGangaTravels         \tCoimbatore to Chennai     \tRs.700    \t\t07:00  AM");
    printf("\n2\tPhaphara Travels     \tCoimbatore to Madurai     \tRs.550    \t\t01:30  PM");
    printf("\n3\tShiv Ganga Travels   \tCoimbatore to Trichy      \tRs.400    \t\t03:50  PM");
    printf("\n4\tSuper Deluxe         \tCoimbatore to Kochi       \tRs.700    \t\t01:00  AM");
    printf("\n5\tSai Baba Travels     \tCoimbatore to Tirupathi   \tRs.550    \t\t12:05  AM");
    printf("\n6\tShine On Travels     \tCoimbatore to Banglore    \tRs.400    \t\t09:30  AM");
    printf("\n7\tTNSTC                \tCoimbatore to Kerala      \tRs.700    \t\t11:00  AM");
    printf("\n8\tKPN                  \tCoimbatore to Salem       \tRs.550    \t\t10:00  AM");
    printf("\n9\tRathimeena           \tCoimbatore to Pondichery  \tRs.400    \t\t04:00  PM\n");
}

// Function to cancel a reservation based on customer ID
void cancel(int x) {
    int custId, busnumber;
    char c;
aa:
    redColor(); // Set text color to red for header
    printf("\n----------------------------------------------------------------------------");
    printf("\n                           CANCEL RESERVATION                                  ");
    printf("\n----------------------------------------------------------------------------");
    resetColor(); // Reset text color
    printf("\nENTER THE CUSTOMER ID: ");
    scanf("%d", &custId); // Read customer ID from user
    busnumber = custId / 1000; // Extract bus number from customer ID
    if (busnumber <= 0 || busnumber > 9) { // Validate bus number
        redColor(); // Set text color to red for error message
        printf("\n  PLEASE ENTER CORRECT CUSTOMER ID\n");
        resetColor(); // Reset text color
        goto aa; // Go back to customer ID prompt
    }
    if (busSeat[busnumber][custId % 100] != 0) { // Check if seat is booked
        printf("\n\n  DO YOU WANT TO CANCEL THE RESERVATION (Y/N): ");
        c = getch(); // Read user confirmation
        if (c == 'y' || c == 'Y') { // If user confirms cancellation
            busSeat[busnumber][custId % 100] = 0; // Mark seat as empty
            printf("\n\n  TICKET CANCELED SUCCESSFULLY !!!");
            getch(); // Wait for user input
        } else if (c == 'n' || c == 'N') { // If user cancels operation
            goto aa; // Go back to customer ID prompt
        } else {
            redColor(); // Set text color to red for error message
            printf("\n\n PLEASE ENTER CORRECT KEY !!! \n");
            resetColor(); // Reset text color
            goto aa; // Go back to customer ID prompt
        }
    } else { // If no reservation found for the customer ID
        printf("\n\n   NO RESERVATION FOUND FOR THIS CUSTOMER ID !!!");
        getch(); // Wait for user input
    }
}
// Main function to provide the main menu and handle user choices
int main() {
    int choice = 0, input, m, n, p, custID, randomNum = 0;
    login(); // Handle user login
mainmenu:
    system("cls"); // Clear the screen
    redColor(); // Set text color to red for header   printf("\n\n=============================================================================\n");
    printf("\t\t\t BUS RESERVATION SYSTEM\n");   printf("\n=============================================================================\n\n");
    resetColor(); // Reset text color
    printf("\t\t\t\t1>> Reserve A Ticket\n");
    printf("\t\t\t\t-------------------------\n");
    printf("\t\t\t\t2>> Show My Reservation\n");
    printf("\t\t\t\t-------------------------\n");
    printf("\t\t\t\t3>> Display Buses List\n");
    printf("\t\t\t\t-------------------------\n");
    printf("\t\t\t\t4>> Show Seat Status\n");
    printf("\t\t\t\t-------------------------\n");
    printf("\t\t\t\t5>> Cancel My Reservation\n");
    printf("\t\t\t\t-------------------------\n");
    printf("\t\t\t\t6>> Exit\n");
    printf("\t\t\t\t-------------------------\n");
    printf("\n\n\n\t\t\t ENTER YOUR CHOICE: ");
    scanf("%d", &choice); // Read user choice from menu
    switch (choice) {
        case 1: // Reserve a ticket
            busLists(); // Display available buses
            printf("\n  ENTER YOUR BUS NUMBER: ");
            scanf("%d", &m); // Read bus number from user
            printf("\n  HOW MANY SEATS DO YOU WANT TO BOOK: ");
            scanf("%d", &p); // Read number of seats to book
            for (int i = 0; i < p; i++) {
                printf("\n   ENTER THE SEAT NUMBER: ");
                scanf("%d", &n); // Read seat number from user
                busSeat[m][n] = 1; // Mark seat as booked
                randomNum = rand(); // Generate a random number
                custID = (m * 1000) + n + randomNum % 100; // Generate unique customer ID
                root = insert(&root, custID); // Insert reservation into BST
                printf("\n========================================\n");
                greencolor(); // Set text color to green for success message
                printf("   YOUR CUSTOMER ID IS: %d", custID); // Display customer ID
                resetColor(); // Reset text color
                printf("\n========================================\n");
            }
            break;
        case 2: // Show reservation
            printf("\n   ENTER YOUR CUSTOMER ID: ");
            scanf("%d", &input); // Read customer ID from user
            int custIDmatched = 0; // Initialize match flag
            root = reservationInfo(root, input, &custIDmatched); // Retrieve reservation details
            if (custIDmatched == 0) { // If no reservation found
                printf("\n  NO RESERVATION FOUND FOR THIS CUSTOMER ID !!!");
                getch(); // Wait for user input
            }
            break;
        case 3: // Display buses list
            busLists(); // Display available buses
            break;
        case 4: // Show seat status
            status(); // Display seat status
            break;
        case 5: // Cancel reservation
            cancel(randomNum); // Handle reservation cancellation
            break;
        case 6: // Exit
            exit(0); // Exit the program
            break;
        default: // Invalid choice
            printf("\n  INVALID CHOICE !!!");
            getch(); // Wait for user input
            break;
    }
    goto mainmenu; // Go back to main menu
    return 0;
}
