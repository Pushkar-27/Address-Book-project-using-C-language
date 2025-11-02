#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

// Check for valid name or not
int validName(char *name) 
{
    if(name[0] == '\0') return 0;
    for(int i = 0; name[i] != '\0'; i++)
    {
        if(!((name[i] >= 'A' && name[i] <= 'Z') ||(name[i] >= 'a' && name[i] <= 'z') ||name[i] == ' '))
        return 0;
    }
    return 1; 
}

// Check for valid phone number or not
int validphone(AddressBook *addressBook,char *phone)
{
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(phone,addressBook->contacts[i].phone)==0)
        {
            found=1;
            break;
        }
    }
    if(found==1){
        printf("This number allready exist: \n");
        return 0;
    }
    if(phone[0]== '\0') return 0;
    if(phone[0]== '0') return 0;
    int len=0;
    for(int i=0;phone[i] != '\0';i++)
    {
        if(phone[i] <'0' || phone[i] >'9'){
            return 0;
        }
        len++;
    }
    return (len==10);
}
// Check for valid email or not
int validemail(AddressBook *addressBook,char *email)
{
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(email,addressBook->contacts[i].email)==0)
        {
            found=1;
            break;
        }
    }
    if(found==1){
        printf("This Email allready exist: \n");
        return 0;
    }
    if(email[0] == '\0') return 0;

    int dotpos=0,atpos=0,len=0,count=0;
    for(int i=0;email[i] != '\0';i++){
        len++;
        if(email[i]>= 'A' && email[i] <= 'Z' || email[i] == ' '){
            return 0;
        }

        if(email[i]=='@'){

            atpos=i;
            count++;
        }
        if(email[i] == '.'){
            dotpos=i;
        }
    }
    if (len >= 4 && strcmp(&email[len - 4], ".com") != 0) {
        return 0;
    }
    if(count!=1) return 0;
    if( atpos < 1) return 0;
    if(dotpos < atpos+2) return 0;
    if(len - dotpos < 3) return 0;
    return 1;
}
//Search Name
void searchName(AddressBook *addressBook,char *name)
{
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(name,addressBook->contacts[i].name)==0)
        {
            printf("Found: %s |%s |%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            found=1;
        }
    }
    if(!found)
    {
        printf("Not found your name.");
    }
}
//Search Phone
void searchPhone(AddressBook *addressBook,char *phone)
{
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(phone,addressBook->contacts[i].phone)==0)
        {
            printf("Found: %s |%s |%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            found=1;
            break;
        }
    }
    if(!found)
    {
        printf("Not found your Phone.");
    }
}
//Search Email
void searchEmail(AddressBook *addressBook,char *email)
{
    int found=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(email,addressBook->contacts[i].email)==0)
        {
            printf("Found: %s |%s |%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            found=1;
            break;
        }
    }
    if(!found)
    {
        printf("Not found your Email.");
    }
}

extern int compareContact(const void *a, const void *b);

void listContacts(AddressBook *addressBook)
{
    // Sort contacts based on the chosen criteria
     if(addressBook->contactCount==0)
     {
        printf("Contacts are Not found");
     }
     for(int i=0;i<addressBook->contactCount-1;i++)
     {
        for(int j=0;j<addressBook->contactCount-1-i;j++)
        {
            if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
            {
                Contact temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
        }
     }
     printf("\n Contact list.. \n");
     for(int i=0;i<addressBook->contactCount;i++)
     {
        printf("\nContact %d: \n",i+1);
        printf("Name %s\n",addressBook->contacts[i].name);
        printf("Name %s\n",addressBook->contacts[i].phone);
        printf("Name %s\n",addressBook->contacts[i].email);
     }

}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    
    /* Define the logic to create a Contacts */
    if(addressBook->contactCount>=MAX_CONTACTS){
        printf("\nThe address book is full. \n");
        return;
    }
    else{
        Contact new_contact;
        printf("Enter the name: ");
        scanf(" %[^\n]",new_contact.name);
        int i=validName(new_contact.name); 
        if(i==0){
            printf("\nPlese enter valid name..\n");
            return;
        }
        
        printf("Enter the phone number: ");
        scanf(" %[^\n]",new_contact.phone);
        i=validphone(addressBook,new_contact.phone); 
        if(i==0){ 
            printf("\nPlese enter valid phone number..\n");
            return;
        }
        
        printf("Enter the email: ");
        scanf(" %[^\n]",new_contact.email);
        i=validemail(addressBook,new_contact.email); 
        if(i==0){
            printf("\nPlese enter valid Email..\n");
            return;
        }
        addressBook->contacts[addressBook->contactCount]=new_contact;
        addressBook->contactCount++;
    }
    
}

void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */
    int choise;
    char details[200];
    int found;
    do
    {
        printf("\nSearch Menu: \n");
        printf("1.Search By name: \n");
        printf("2.Search By phone number: \n");
        printf("3.Search By email: \n");
        printf("4.Exit the menu: \n");
        printf("Enter the choise: ");
        scanf("%d",&choise);
        getchar();
        found=0;
        switch(choise)
        {
            case 1:
            printf("Enter the your name for search: ");
            scanf(" %[^\n]",details);
            for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].name, details) == 0) {
                        printf("\nContact Found:\n");
                        printf("Name: %s\n", addressBook->contacts[i].name);
                        printf("Phone: %s\n", addressBook->contacts[i].phone);
                        printf("Email: %s\n", addressBook->contacts[i].email);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No contact found with that name.\n");
                }
                break;

            case 2:
            printf("Enter the your Phone number for search: ");
            scanf(" %[^\n]",details);
            for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].phone, details) == 0) {
                        printf("\nContact Found:\n");
                        printf("Name: %s\n", addressBook->contacts[i].name);
                        printf("Phone: %s\n", addressBook->contacts[i].phone);
                        printf("Email: %s\n", addressBook->contacts[i].email);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No contact found with that name.\n");
                }
                break;

            case 3:
            printf("Enter the your Email for search: ");
            scanf(" %[^\n]",details);
            for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].email, details) == 0) {
                        printf("\nContact Found:\n");
                        printf("Name: %s\n", addressBook->contacts[i].name);
                        printf("Phone: %s\n", addressBook->contacts[i].phone);
                        printf("Email: %s\n", addressBook->contacts[i].email);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No contact found with that name.\n");
                }
                break;

            case 4:
            printf("Exit the menu: \n");
            break;

            default :
            printf("Invaid Input");
            break;
        }
        
    } while (choise!= 4);
    
    
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    char name[100];
    printf("Enter the name of the contact to edit: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            printf("Editing contact: %s\n", addressBook->contacts[i].name);

            char confirm;
            printf("Are you sure you want to update this contact? (y/n): ");
            scanf(" %c", &confirm);
            if (confirm != 'y' && confirm != 'Y') {
                printf("Edit cancelled.\n");
                return;
            }
            printf("Enter new name: ");
            scanf(" %[^\n]", addressBook->contacts[i].name);

            printf("Enter new phone: ");
            scanf(" %[^\n]", addressBook->contacts[i].phone);

            printf("Enter new email: ");
            scanf(" %[^\n]", addressBook->contacts[i].email);

            printf("Contact updated successfully.\n");
            return;
           
        }
    }
    printf("Contact not found.\n");
}


void deleteContact(AddressBook *addressBook)
{

    /* Define the logic for deletecontact */
    char name[100];
    printf("Enter the name of the contact to delete: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            for (int j = i; j < addressBook->contactCount - 1; j++) {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            printf("Contact deleted.\n");
            return;
        }
    }
    printf("Contact not found.\n");

}

