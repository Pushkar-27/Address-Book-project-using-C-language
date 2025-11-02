#include <stdio.h>
#include "file.h"
#include <string.h>
#define FILE_NAME "contacts.txt"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *file = fopen("contacts.csv", "w");
    if (file == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(file);
    printf("Contacts saved successfully.\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *file = fopen("contacts.csv", "r");
    if (file == NULL) {
        printf("No saved contacts found. Starting with empty address book.\n");
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), file)) {
        Contact newContact;
        char *token = strtok(line, ",");
        if (token != NULL) {
            strncpy(newContact.name, token, sizeof(newContact.name));
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(newContact.phone, token, sizeof(newContact.phone));
        }

        token = strtok(NULL, ",\n");
        if (token != NULL) {
            strncpy(newContact.email, token, sizeof(newContact.email));
        }

        if (addressBook->contactCount < MAX_CONTACTS) {
            addressBook->contacts[addressBook->contactCount++] = newContact;
        }
    }

    fclose(file);
    printf("Contacts loaded \n");
}
