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
    printf("Enter your name: ");
    fgets(user_name, sizeof(user_name), stdin);
    strtok(user_name, "\n");

    printf("Welcome, %s! Please use the following options:\n", user_name);
        int caz;
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
    scanf("%d", &caz);

    switch (caz) {
        case 1:
            borrow_books(&users[0]);
            break;
        case 2:
            return_books(&users[0]);
            break;
        case 3:
            donate_books();
        case 4:
            view_loans(&users[0]);
        case 5:
            search_books();
        case 0:
            printf("Program finished successfully!");
            return 0;
            break;
        default:
            printf("Choose one of the options from above to continue");
            break;
    }
    borrow_books(&users[0]);
    return_books(&users[0]);
    donate_books();
    view_loans(&users[0]);
    search_books();

    return 0;
}

void borrow_books(struct User *user) {
    int i, j;
    char title[100];

    printf("Enter the title of the book you want to borrow: ");
    fgets(title, sizeof(title), stdin);
    strtok(title, "\n");

    for (i = 0; i < num_books; i++) {
        if (strcmp(library[i].title, title) == 0 && library[i].copies_available > 0) {
            strcpy(user->borrowed_books[user->num_borrowed_books].title, library[i].title);
            strcpy(user->borrowed_books[user->num_borrowed_books].author, library[i].author);
            user->num_borrowed_books++;
            library[i].copies_available--;
            printf("Book \"%s\" borrowed successfully.\n", title);
            return;
        }
    }
    printf("Book \"%s\" is either not available or does not exist in the library.\n", title);
}

void return_books(struct User *user) {
    int i;
    char title[100];

    printf("Enter the title of the book you want to return: ");
    fgets(title, sizeof(title), stdin);
    strtok(title, "\n"); // remove newline character from fgets

    for (i = 0; i < user->num_borrowed_books; i++) {
        if (strcmp(user->borrowed_books[i].title, title) == 0) {
            // Book found
            user->num_borrowed_books--;
            printf("Book \"%s\" returned successfully.\n", title);
            return;
        }
    }

    printf("Book \"%s\" was not borrowed by you.\n", title);
}

void donate_books() {
    char title[100], author[100];
    int copies;

    printf("Enter the title of the book you want to donate: ");
    fgets(title, sizeof(title), stdin);
    strtok(title, "\n");

    printf("Enter the author of the book: ");
    fgets(author, sizeof(author), stdin);
    strtok(author, "\n");

    printf("Enter the number of copies you want to donate: ");
    scanf("%d", &copies);

    strcpy(library[num_books].title, title);
    strcpy(library[num_books].author, author);
    library[num_books].copies_available = copies;
    num_books++;

    printf("Book \"%s\" donated successfully.\n", title);
}

void view_loans(struct User *user) {
    int i;

    printf("Books borrowed by %s %s:\n", user->name, user->surname);
    for (i = 0; i < user->num_borrowed_books; i++) {
        printf("%d. %s by %s\n", i + 1, user->borrowed_books[i].title, user->borrowed_books[i].author);
    }
}

void search_books() {
    int i;
    char query[100];

    printf("Enter title or author to search: ");
    fgets(query, sizeof(query), stdin);
    strtok(query, "\n"); // remove newline character from fgets

    printf("Search results:\n");
    for (i = 0; i < num_books; i++) {
        if (strstr(library[i].title, query) || strstr(library[i].author, query)) {
            printf("%d. %s by %s (%d copies available)\n", i + 1, library[i].title, library[i].author, library[i].copies_available);
        }
    }
}
