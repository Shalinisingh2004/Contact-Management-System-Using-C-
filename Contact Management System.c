#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "contacts.dat"

typedef struct {
    char name[50];
    char phone[15];
    char address[100];
    char email[50];
} Contact;

void addContact();
void listContacts();
void searchContact();
void editContact();
void deleteContact();
void displayContact(Contact c);

int main() {
    int choice;

    while (1) {
        printf("\n*** Welcome to Contact Management System ****\n");
        printf("\nMAIN MENU\n");
        printf("[1] Add a new Contact\n");
        printf("[2] List all Contacts\n");
        printf("[3] Search for contact\n");
        printf("[4] Edit a Contact\n");
        printf("[5] Delete a Contact\n");
        printf("[0] Exit\n");
        printf("Enter the choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                listContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                editContact();
                break;
            case 5:
                deleteContact();
                break;
            case 0:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void addContact() {
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Contact c;
    printf("Enter name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter phone number: ");
    scanf(" %[^\n]", c.phone);
    printf("Enter address: ");
    scanf(" %[^\n]", c.address);
    printf("Enter email: ");
    scanf(" %[^\n]", c.email);

    fwrite(&c, sizeof(Contact), 1, file);
    fclose(file);

    printf("Contact added successfully!\n");
}

void listContacts() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("No contacts found!\n");
        return;
    }

    Contact c;
    printf("\n=====================================\n");
    printf("           LIST OF CONTACTS           \n");
    printf("=====================================\n");
    printf("Name                           Phone No        Address               E-mail ad.          \n");
    printf("=====================================\n");
    while (fread(&c, sizeof(Contact), 1, file)) {
        printf("Name    : %s\n", c.name);
        printf("Phone   : %s\n", c.phone);
        printf("Address : %s\n", c.address);
        printf("Email   : %s\n", c.email);
        printf("=====================================\n");
    }
    fclose(file);
}

void searchContact() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("No contacts found!\n");
        return;
    }

    char query[50];
    printf("Enter name or phone number to search: ");
    scanf(" %[^\n]", query);

    Contact c;
    int found = 0;
    while (fread(&c, sizeof(Contact), 1, file)) {
        if (strstr(c.name, query) != NULL || strstr(c.phone, query) != NULL) {
            displayContact(c);
            found = 1;
        }
    }

    if (!found) {
        printf("No contact found with the given information.\n");
    }
    fclose(file);
}

void editContact() {
    FILE *file = fopen(FILENAME, "rb+");
    if (file == NULL) {
        printf("No contacts found!\n");
        return;
    }

    char query[50];
    printf("Enter name or phone number to edit: ");
    scanf(" %[^\n]", query);

    Contact c;
    int found = 0;
    long pos;
    while (fread(&c, sizeof(Contact), 1, file)) {
        if (strstr(c.name, query) != NULL || strstr(c.phone, query) != NULL) {
            pos = ftell(file) - sizeof(Contact);
            fseek(file, pos, SEEK_SET);

            printf("Enter new name: ");
            scanf(" %[^\n]", c.name);
            printf("Enter new phone number: ");
            scanf(" %[^\n]", c.phone);
            printf("Enter new address: ");
            scanf(" %[^\n]", c.address);
            printf("Enter new email: ");
            scanf(" %[^\n]", c.email);

            fwrite(&c, sizeof(Contact), 1, file);
            found = 1;
            printf("Contact updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("No contact found with the given information.\n");
    }
    fclose(file);
}

void deleteContact() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("No contacts found!\n");
        return;
    }

    char query[50];
    printf("Enter name or phone number to delete: ");
    scanf(" %[^\n]", query);

    Contact c;
    FILE *temp = fopen("temp.dat", "wb");
    int found = 0;
    while (fread(&c, sizeof(Contact), 1, file)) {
        if (strstr(c.name, query) != NULL || strstr(c.phone, query) != NULL) {
            found = 1;
        } else {
            fwrite(&c, sizeof(Contact), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove(FILENAME);
        rename("temp.dat", FILENAME);
        printf("Contact deleted successfully!\n");
    } else {
        printf("No contact found with the given information.\n");
        remove("temp.dat");
    }
}

void displayContact(Contact c) {
    printf("\nName    : %s\n", c.name);
    printf("Phone   : %s\n", c.phone);
    printf("Address : %s\n", c.address);
    printf("Email   : %s\n", c.email);
}


