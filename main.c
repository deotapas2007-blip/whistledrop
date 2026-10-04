#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

struct Report {
    int code;
    char category[20];
    char description[200];
    char status[20];
    char update[150];
};

struct Report reports[MAX];
int count = 0;

char *categories[] = {
    "Security", "Harassment", "Corruption", "Technical", "Other"
};

char *statuses[] = {
    "SUBMITTED", "UNDER_REVIEW", "RESOLVED", "DISMISSED"
};


/* Save reports to file */
void save()
{
    FILE *f = fopen("reports.dat", "wb");

    if (f == NULL)
        return;

    fwrite(&count, sizeof(int), 1, f);
    fwrite(reports, sizeof(struct Report), count, f);

    fclose(f);
}


/* Load reports from file */
void load()
{
    FILE *f = fopen("reports.dat", "rb");

    if (f == NULL)
        return;

    fread(&count, sizeof(int), 1, f);
    fread(reports, sizeof(struct Report), count, f);

    fclose(f);
}


/* Find report using case code */
int findReport(int code)
{
    int i;

    for (i = 0; i < count; i++)
        if (reports[i].code == code)
            return i;

    return -1;
}


/* Submit a new report */
void submit()
{
    int choice;

    if (count >= MAX) {
        printf("\nStorage full.\n");
        return;
    }

    printf("\n--- Submit Anonymous Report ---\n");

    printf("\nCategories:\n");
    for (int i = 0; i < 5; i++)
        printf("%d. %s\n", i + 1, categories[i]);

    printf("Choose category: ");
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > 5) {
        printf("Invalid category.\n");
        return;
    }

    strcpy(reports[count].category, categories[choice - 1]);

    printf("Enter description: ");
    fgets(reports[count].description, 200, stdin);

    reports[count].description[
        strcspn(reports[count].description, "\n")
    ] = '\0';

    /* Generate unique 6-digit case code */
    do {
        reports[count].code = 100000 + rand() % 900000;
    } while (findReport(reports[count].code) != -1);

    strcpy(reports[count].status, "SUBMITTED");
    strcpy(reports[count].update, "Report received.");

    printf("\nReport submitted successfully!\n");
    printf("Your Case Code: WD-%06d\n", reports[count].code);
    printf("Save this code to track your report.\n");

    count++;
    save();
}


/* Check report status */
void check()
{
    int code, i;

    printf("\n--- Check Report ---\n");
    printf("Enter case code number: WD-");
    scanf("%d", &code);
    getchar();

    i = findReport(code);

    if (i == -1) {
        printf("Report not found.\n");
        return;
    }

    printf("\nCase Code: WD-%06d\n", reports[i].code);
    printf("Category: %s\n", reports[i].category);
    printf("Status: %s\n", reports[i].status);
    printf("Latest Update: %s\n", reports[i].update);
}


/* Display all reports */
void viewReports()
{
    if (count == 0) {
        printf("\nNo reports available.\n");
        return;
    }

    printf("\n--- All Reports ---\n");

    for (int i = 0; i < count; i++) {
        printf("\nCase: WD-%06d\n", reports[i].code);
        printf("Category: %s\n", reports[i].category);
        printf("Description: %s\n", reports[i].description);
        printf("Status: %s\n", reports[i].status);
        printf("Update: %s\n", reports[i].update);
    }
}


/* Change report status */
void changeStatus()
{
    int code, choice, i;

    printf("\nEnter case code number: WD-");
    scanf("%d", &code);
    getchar();

    i = findReport(code);

    if (i == -1) {
        printf("Report not found.\n");
        return;
    }

    printf("\n1. SUBMITTED\n");
    printf("2. UNDER_REVIEW\n");
    printf("3. RESOLVED\n");
    printf("4. DISMISSED\n");

    printf("Choose status: ");
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > 4) {
        printf("Invalid status.\n");
        return;
    }

    strcpy(reports[i].status, statuses[choice - 1]);
    save();

    printf("Status updated successfully.\n");
}


/* Add status update */
void addUpdate()
{
    int code, i;

    printf("\nEnter case code number: WD-");
    scanf("%d", &code);
    getchar();

    i = findReport(code);

    if (i == -1) {
        printf("Report not found.\n");
        return;
    }

    printf("Enter status update: ");
    fgets(reports[i].update, 150, stdin);

    reports[i].update[
        strcspn(reports[i].update, "\n")
    ] = '\0';

    save();

    printf("Update added successfully.\n");
}


/* Moderator menu */
void moderator()
{
    int pin, choice;

    printf("\n--- Moderator Login ---\n");
    printf("Enter PIN: ");
    scanf("%d", &pin);
    getchar();

    if (pin != 1234) {
        printf("Invalid PIN.\n");
        return;
    }

    printf("Login successful.\n");

    while (1) {
        printf("\n--- Moderator Menu ---\n");
        printf("1. View Reports\n");
        printf("2. Change Status\n");
        printf("3. Add Status Update\n");
        printf("4. Logout\n");

        printf("Choose: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                viewReports();
                break;

            case 2:
                changeStatus();
                break;

            case 3:
                addUpdate();
                break;

            case 4:
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}


/* Main program */
int main()
{
    int choice;

    srand(time(NULL));
    load();

    printf("\n================================\n");
    printf("         WHISTLEDROP\n");
    printf(" Anonymous Reporting System\n");
    printf("================================\n");

    while (1) {
        printf("\n1. Submit Anonymous Report\n");
        printf("2. Check Report Status\n");
        printf("3. Moderator Access\n");
        printf("4. Exit\n");

        printf("Choose: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                submit();
                break;

            case 2:
                check();
                break;

            case 3:
                moderator();
                break;

            case 4:
                printf("Thank you for using WhistleDrop.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}