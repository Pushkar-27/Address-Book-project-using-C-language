/*
Name       : Pushkar Dipak Kadam
Batch Id   : 25021_321
Project    : AddressBook Management System
Date       : 17/09/2025

Description:
This project implements a simple AddressBook that allows users to:
- Create contacts with Name, Phone, and Email
- Search contacts by Name, Phone, or Email
- Edit existing contacts
- Delete contacts
- List all contacts with optional sorting
- Save contacts to a CSV file and load them automatically on startup

Input:  
- User selects options from the menu (1–7)
- Provides Name, Phone, and Email when creating or editing contacts

Sample Menu:
Contacts loaded 
========================
Address Book Menu:
========================
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exit
========================
Enter your choice:

Output:
- Confirmation messages on creating, editing, deleting contacts
- Sorted contact list when listing
- Search results for matching contacts
- Error messages for invalid input or duplicates
- Automatic saving and loading of contacts

*/
#include <stdio.h>
#include "contact.h"

int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do
    {
        printf("========================\nAddress Book Menu:\n========================\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save contacts\n");
        printf("7. Exit\n");
        printf("========================\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook);
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            listContacts(&addressBook);
            break;
        case 6:
            printf("Saving...\n");
            saveContactsToFile(&addressBook);
            break;
        case 7:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
