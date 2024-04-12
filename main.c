#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_USERS 100

struct Book {
    char title[100];
    char author[100];
    int copies_available;
};

struct User {
    char name[50];
    char surname[50];
    struct Book borrowed_books[MAX_BOOKS];
    int num_borrowed_books;
};

struct Book library[MAX_BOOKS];
int num_books = 0;
struct User users[MAX_USERS];
int num_users = 0;
char user_name[80];

void borrow_books(struct User *user);
void return_books(struct User *user);
void donate_books();
void view_loans(struct User *user);
void search_books();

int main() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    while (fscanf(file, "%s %s %d", library[num_books].title, library[num_books].author, &library[num_books].copies_available) == 3) {
        num_books++;
    }
    fclose(file);

    printf("Enter your name: ");
    fgets(user_name, sizeof(user_name), stdin);
    strtok(user_name, "\n");
    strcpy(users[0].name, user_name);
    printf("Welcome, %s! Please use the following options:\n", user_name);
    menu1();
    case_func();
    }
void clear_console() {
    system("cls");
}

void menu1(){
    printf("\n\n\n");
    printf("**************************************************************************************\n");
    printf("*                                       MENU                                         *\n");
    printf("**************************************************************************************\n");
    printf("*                                                                                    *\n");
    printf("*                                 1.Borrow Books                                     *\n");
    printf("*                                                                                    *\n");
    printf("*                                 2.Return Books                                     *\n");
    printf("*                                                                                    *\n");
    printf("*                                 3.Donate Books                                     *\n");
    printf("*                                                                                    *\n");
    printf("*                                 4.View Loans                                       *\n");
    printf("*                                                                                    *\n");
    printf("*                                 5.Search Books                                     *\n");
    printf("*                                                                                    *\n");
    printf("*                                 0.Exit                                             *\n");
    printf("*                                                                                    *\n");
    printf("**************************************************************************************\n");
}
void case_func(){
    int caz;
    scanf("%d", &caz);
        switch (caz) {
        case 1:
            borrow_books(&users[0]);
        case 2:
            return_books(&users[0]);
        case 3:
            donate_books();
        case 4:
            view_loans(&users[0]);
        case 5:
            search_books();
        case 0:
            printf("Program finished successfully!\n");
            return 0;
            break;
        default:
            printf("Choose one of the options from above to continue\n");
            break;
    }

    printf("Program finished successfully!\n"); // Additional line to print message
    return 0;
}

void borrow_books(struct User *user) {
    char title[100];
    int copies_available = 0;

    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    clear_console();
    printf("#Please enter the name of the book with underlines instead of spaces#\n");
    printf("Enter the title of the book you want to borrow: ");
    scanf("%s", title);

    char temp_title[100], author[100];
    while (fscanf(file, "%s %s %d", temp_title, author, &copies_available) == 3) {
        if (strcmp(temp_title, title) == 0 && copies_available > 0) {
            strcpy(user->borrowed_books[user->num_borrowed_books].title, temp_title);
            strcpy(user->borrowed_books[user->num_borrowed_books].author, author);
            user->num_borrowed_books++;
            copies_available--;
            clear_console();
            printf("Book \"%s\" borrowed successfully.\n", title);
            menu1();
            case_func();

            FILE *temp_file = fopen("temp.txt", "w");
            rewind(file);
            while (fscanf(file, "%s %s %d", temp_title, author, &copies_available) == 3) {
                if (strcmp(temp_title, title) == 0) {
                    fprintf(temp_file, "%s %s %d\n", temp_title, author, copies_available);
                } else {
                    fprintf(temp_file, "%s %s %d\n", temp_title, author, copies_available);
                }
            }
            fclose(file);
            fclose(temp_file);
            remove("books.txt");
            rename("temp.txt", "books.txt");
            return;
        }
    }
    clear_console();
    printf("Book \"%s\" is either not available or does not exist in the library.\n", title);
    fclose(file);
    menu1();
    case_func();
}

void return_books(struct User *user) {
    char title[100];

    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    clear_console();
    printf("Enter the title of the book you want to return: ");
    scanf("%s", title);

    int i;
    for (i = 0; i < user->num_borrowed_books; i++) {
        if (strcmp(user->borrowed_books[i].title, title) == 0) {
            int copies_available;
            char temp_title[100], author[100];
            FILE *temp_file = fopen("temp.txt", "w");
            rewind(file);
            while (fscanf(file, "%s %s %d", temp_title, author, &copies_available) == 3) {
                if (strcmp(temp_title, title) == 0) {
                    copies_available++;
                    fprintf(temp_file, "%s %s %d\n", temp_title, author, copies_available);
                } else {
                    fprintf(temp_file, "%s %s %d\n", temp_title, author, copies_available);
                }
            }
            fclose(file);
            fclose(temp_file);
            remove("books.txt");
            rename("temp.txt", "books.txt");

            for (; i < user->num_borrowed_books - 1; i++) {
                strcpy(user->borrowed_books[i].title, user->borrowed_books[i + 1].title);
                strcpy(user->borrowed_books[i].author, user->borrowed_books[i + 1].author);
            }
            user->num_borrowed_books--;
            clear_console();
            printf("Book \"%s\" returned successfully.\n", title);
            menu1();
            case_func();
            return;
        }
    }
    clear_console();
    printf("Book \"%s\" was not borrowed by you.\n", title);
    fclose(file);
    menu1();
    case_func();
}


void donate_books() {
    char title[100], author[100];
    int copies;

    FILE *file = fopen("books.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    clear_console();
    printf("Enter the title of the book you want to donate: ");
    scanf("%s", title);

    printf("Enter the author of the book: ");
    scanf("%s", author);

    printf("Enter the number of copies you want to donate: ");
    scanf("%d", &copies);

    fprintf(file, "%s %s %d\n", title, author, copies);
    fclose(file);

    clear_console();
    printf("Book \"%s\" donated successfully.\n", title);
    menu1();
    case_func();
}

void view_loans(struct User *user) {
    int i;
    clear_console();
    printf("Books borrowed by %s:\n", user->name);
    for (i = 0; i < user->num_borrowed_books; i++) {
        printf("%d. %s by %s\n", i + 1, user->borrowed_books[i].title, user->borrowed_books[i].author);
    }
    menu1();
    case_func();
}

void search_books() {
    int i;
    char query[100];
    clear_console();
    printf("Enter title or author to search: ");
    scanf("%s", query);
    getchar();

    clear_console();
    printf("Search results:\n");
    for (i = 0; i < num_books; i++) {
        if (strstr(library[i].title, query) != NULL || strstr(library[i].author, query) != NULL) {
            printf("%d. %s by %s (%d copies available)\n", i + 1, library[i].title, library[i].author, library[i].copies_available);
        }
    }
    menu1();
    case_func();
}
