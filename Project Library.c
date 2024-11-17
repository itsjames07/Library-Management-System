#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Global declaration
int choice;
int flag = 0;
char temp_choice[20];

// Functions
void menu();
void verification();
void user_panel();
void admin_panel();
void add_book();
void edit_book();
void book_list();
void delete_book();
void search();
void exit_message();
void return_to_menu();
void clear_screen();
void decor();

struct library {
    char book_name[20];
    char author[20];
    char book_code[10];
};
struct library book;

FILE *fp, *temp;

// Main function
int main() {
    clear_screen();
    char exit_program = 'n';
    do {
        menu();
        printf("\n Choose Your Option:");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                user_panel();
                break;
            case 2:
                verification();
                break;
            case 3:
                exit_program = 'y';
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (exit_program != 'y');
    exit_message();
    return 0;
}

// To clear the screen
void clear_screen() {
    system("cls");
}

// Main menu
void menu() {
    clear_screen();
    printf("\n\t\t\t\t  -----------------------------------------------  ");
    printf("\n\t\t\t\t|              WELCOME TO THE LIBRARY             |");
    printf("\n\t\t\t\t|   SARASWATI MULTIPLE CAMPUS, THAMEL, KATHMANDU  |");
    printf("\n\t\t\t\t  -----------------------------------------------  ");
    printf("\n\n\n [ 1 ] >> USER\n");
    printf("\n [ 2 ] >> ADMIN\n");
    printf("\n [ 3 ] >> EXIT\n");
}

// User menu
void user_panel() {
    clear_screen();
    decor();
    printf("\n\n\n | USER PANEL |\n\n");
    printf("\n [ 1 ] >> BOOK LIST\n");
    printf("\n [ 2 ] >> SEARCH\n");
    printf("\n [ 3 ] >> RETURN TO MENU\n");
    printf("\n Choose your Option: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            book_list();
            break;
        case 2:
            search();
            break;
        case 3:
            return_to_menu();
            break;
        default:
            printf("\nInvalid Choice\n");
    }
}

// Admin verification
void verification() {
    int default_pwd = 1234;
    int user_pwd;
    clear_screen();
    decor();
    printf("\n\n\n | IDENTITY VERIFICATION |\n\n");
    printf("  Enter your password: ");
    scanf("%d", &user_pwd);
    if (user_pwd == default_pwd) {
        printf("\n ACCESS GRANTED\n");
        admin_panel();
    } else {
        printf("\n ACCESS DENIED!\n");
    }
}

// Admin panel
void admin_panel() {
    clear_screen();
    decor();
    printf("\n\n\n | ADMIN PANEL |\n");
    printf("\n [ 1 ] >> BOOK LIST\n");
    printf("\n [ 2 ] >> SEARCH\n");
    printf("\n [ 3 ] >> ADD BOOK\n");
    printf("\n [ 4 ] >> EDIT\n");
    printf("\n [ 5 ] >> REMOVE\n");
    printf("\n [ 6 ] >> EXIT\n\n");
    printf(" Choose Your Option: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            book_list();
            break;
        case 2:
            search();
            break;
        case 3:
            add_book();
            break;
        case 4:
            edit_book();
            break;
        case 5:
            delete_book();
            break;
        case 6:
            exit_message();
            break;
        default:
            printf("\n Invalid choice\n");
    }
}

// Display book list
void book_list() {
    clear_screen();
    decor();
    printf("\n\n\n | BOOK LIST |\n\n");
    fp = fopen("library.txt", "r");
    if (fp == NULL) {
        printf(" No books available\n");
        return;
    }
    printf("\n\n Book Name           | Author              | Book Code  \n");
    printf(" --------------------| --------------------| ---------  \n");
    while (fread(&book, sizeof(book), 1, fp)) {
        printf(" %-20s| %-20s| %-4s\n", book.book_name, book.author, book.book_code);
    }

    fclose(fp);
    return_to_menu();
}

// Add book
void add_book() {
    clear_screen();
    decor();
    char yes;
    printf("\n\n\n | ADD BOOK |\n");
    fp = fopen("library.txt", "a");
    if (fp == NULL) {
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("\n Book Name: ");
    scanf(" %[^\n]s", book.book_name);
    printf(" Author: ");
    scanf(" %[^\n]s", book.author);
    printf(" Book Code: ");
    scanf("%5s", book.book_code);

    fwrite(&book, sizeof(book), 1, fp);
    fclose(fp);
    printf(" Book added successfully!\n");
    printf("\n\n Do you want to add more books?(yes/no):");
    scanf("%s",temp_choice);
    if(strcmp("yes",temp_choice) == 0)
    {
    	add_book();
	}
	else{
    return_to_menu();
    }
}
// Edit book
void edit_book() {
    clear_screen();
    decor();
    printf("\n\n\n | EDIT BOOK |\n");

    fp = fopen("library.txt", "r");
    temp = fopen("temp_library.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf(" Error opening file\n");
        return;
    }
    printf("\n Enter book code to edit: ");
    scanf("%s", temp_choice);
    int found = 0;
    while (fread(&book, sizeof(book), 1, fp)) {
        if (strcmp(book.book_code, temp_choice) == 0) {
            found = 1;
            printf(" Editing book: %s | %s | %s\n", book.book_name, book.author, book.book_code);
            printf("\n Enter new book name: ");
            scanf(" %[^\n]s", book.book_name);
            printf("\n Enter new author: ");
            scanf(" %[^\n]s", book.author);
            printf("\n Enter new book code: ");
            scanf("%s", book.book_code);
        }
        fwrite(&book, sizeof(book), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("library.txt");
        rename("temp_library.txt", "library.txt");
        printf(" Book updated successfully\n");
    } else {
        printf(" Book not found\n");
    }
    printf("\n Do you want to edit more books?\n");
    printf(" Enter (yes/no): ");
    scanf("%s", temp_choice);
    if(strcmp("yes",temp_choice) == 0)
    {
    	edit_book();
	}
else {
	return_to_menu();
}
}

// Search book
void search() {
    clear_screen();
    decor();
    char yes;
    printf("\n\n\n | SEARCH BOOK |\n\n");

    fp = fopen("library.txt", "r");
    if (fp == NULL) {
        printf(" No books available\n");
        return;
    }
    printf("\n Enter Book Name or Author to Search:");
    scanf(" %[^\n]s", temp_choice);

    int found = 0;
    while (fread(&book, sizeof(book), 1, fp)) {
        if (strstr(book.book_name, temp_choice) != NULL || strstr(book.author, temp_choice) != NULL) {
            printf(" Book Name           | Author              | Book Code  \n");
            printf(" --------------------| --------------------| ---------  \n");
            printf(" %-20s| %-20s| %-4s\n", book.book_name, book.author, book.book_code);
            found = 1;
        }
    }

    if (!found) {
        printf(" Book not found\n");
    }

    fclose(fp);
    printf("\n Search for another book(yes/no): ");
    scanf("%s",temp_choice);
    if(strcmp("yes",temp_choice) == 0)
    {
    	search();
	}
	else {
		return_to_menu();
	}
}

// Delete book
void delete_book() {
    clear_screen();
    decor();
    printf("\n\n\n | DELETE BOOK |\n");
    fp = fopen("library.txt", "r");
    temp = fopen("temp_library.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf(" Error opening file\n");
        return;
    }
    printf("\n Enter book code to delete: ");
    scanf("%s", temp_choice);

    int found = 0;
    while (fread(&book, sizeof(book), 1, fp)) {
        if (strcmp(book.book_code, temp_choice) != 0) {
            fwrite(&book, sizeof(book), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("library.txt");
        rename("temp_library.txt", "library.txt");
        printf(" Book deleted successfully\n");
    } else {
        printf(" Book not found\n");
    }
    printf("\n Do you want to delete more books? (yes/no):");
    scanf("%s",temp_choice);
    if(strcmp("yes",temp_choice) == 0)
    {
    	delete_book();
	}
    else {
	return_to_menu();
    }
}

// Exit message
void exit_message() {
    clear_screen();
    printf("\n THANKYOU FOR USING THE PROGRAM !\n");
    printf("\n SEE YOU AGAIN\n PROGRAM BY: James Karki");
}

// Return to menu
void return_to_menu() {
    printf("\n Press Enter to return to the Main Menu...\n");
    getchar();
    getchar();  // to consume '\n'
}

//Just for decoration 
void decor()
{
    printf("\n\t\t\t\t  -----------------------------------------------  ");
    printf("\n\t\t\t\t|            LIBRARY MANAGEMENT SYSTEM            |");
    printf("\n\t\t\t\t|   SARASWATI MULTIPLE CAMPUS, THAMEL, KATHMANDU  |");
    printf("\n\t\t\t\t  -----------------------------------------------  ");
}
