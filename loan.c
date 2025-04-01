#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Loan {
    int id;
    char name[50];
    char type[20];
    float emi;
    int repayments;
};

void applyLoan() {
    FILE *file = fopen("loan.txt", "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    struct Loan loan;
    printf("Enter Loan ID: ");
    scanf("%d", &loan.id);
    printf("Enter Name: ");
    scanf(" %s", loan.name);
    printf("Enter Loan Type: ");
    scanf(" %19s", loan.type);
    printf("Enter EMI Amount: ");
    scanf("%f", &loan.emi);
    printf("Enter Repayments (months): ");
    scanf("%d", &loan.repayments);

    fwrite(&loan, sizeof(struct Loan), 1, file);
    fclose(file);
    printf("Loan applied successfully!\n");
}

void viewLoans() {
    FILE *file = fopen("loan.txt", "r");
    if (!file) {
        printf("No loan records found.\n");
        return;
    }

    struct Loan loan;
    printf("\nLoan Records:\n");
    while (fread(&loan, sizeof(struct Loan), 1, file)) {
        printf("ID: %d, Name: %s, Type: %s, EMI: %.2f, Repayments: %d\n",
               loan.id, loan.name, loan.type, loan.emi, loan.repayments);
    }
    fclose(file);
}

void modifyLoan() {
    FILE *file = fopen("loan.txt", "r+"), *tempFile;
    if (!file) {
        printf("No loan records found.\n");
        return;
    }
    
    int id, found = 0;
    printf("Enter Loan ID to modify: ");
    scanf("%d", &id);

    struct Loan loan;
    tempFile = fopen("temp.txt", "w");

    while (fread(&loan, sizeof(struct Loan), 1, file)) {
        if (loan.id == id) {
            found = 1;
            printf("Enter New Name: ");
            scanf(" %s", loan.name);
            printf("Enter New Loan Type: ");
            scanf(" %19s", loan.type);
            printf("Enter New EMI Amount: ");
            scanf("%f", &loan.emi);
            printf("Enter New Repayments: ");
            scanf("%d", &loan.repayments);
        }
        fwrite(&loan, sizeof(struct Loan), 1, tempFile);
    }
    fclose(file);
    fclose(tempFile);
    remove("loan.txt");
    rename("temp.txt","loan.txt");

    if (found)
        printf("Loan record updated successfully!\n");
    else
        printf("Loan ID not found!\n");
}

void deleteLoan() {
    FILE *file = fopen("loan.txt", "r"), *tempFile;
    if (!file) {
        printf("No loan records found.\n");
        return;
    }
    
    int id, found = 0;
    printf("Enter Loan ID to delete: ");
    scanf("%d", &id);

    struct Loan loan;
    tempFile = fopen("temp.txt", "w");

    while (fread(&loan, sizeof(struct Loan), 1, file)) {
        if (loan.id == id) {
            found = 1;
            continue;
        }
        fwrite(&loan, sizeof(struct Loan), 1, tempFile);
    }
    fclose(file);
    fclose(tempFile);
    remove("loan.txt");
    rename("temp.txt", "loan.txt");

    if (found)
        printf("Loan record deleted successfully!\n");
    else
        printf("Loan ID not found!\n");
}

int main() {
    int choice;
    while (1) {
        printf("\nLoan Management System\n");
        printf("1. Apply for Loan\n");
        printf("2. View Loans\n");
        printf("3. Modify Loan\n");
        printf("4. Delete Loan\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: applyLoan(); break;
            case 2: viewLoans(); break;
            case 3: modifyLoan(); break;
            case 4: deleteLoan(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
