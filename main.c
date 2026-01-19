#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void addTask();
void viewTask();

int main()
{
    int choice;

    while (1) {
        printf("\n------ SMART TO-DO LIST ------\n");
        printf("1: Add Task\n");
        printf("2: View Task\n");
        printf("3: Exit\n");
        printf("------------------------------\n");
        printf("Enter your choice: ");

        scanf("%d",&choice);

        if (choice != 1 && choice != 2 && choice !=3)
            {
                printf("Please enter a valid number\n");
                continue;
            }


        getchar();

        switch (choice) {
            case 1: addTask();
                    break;
            case 2: viewTask();
                    break;
            case 3: printf("Exiting the program\n");
                    exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void addTask()
{
    FILE* smartlist = fopen("tasks.txt", "a");
    if (smartlist == NULL) {
        printf("Error opening smartlist!\n");
        return;
    }

    char task[1000];
    printf("Enter your task (one line): ");
    fgets(task, sizeof(task), stdin);



    char date[20];
    printf("Enter due date (DD/MM/YYYY): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0';

    fprintf(smartlist, "[%s] %s", date, task);

    fclose(smartlist);

    printf("Task saved!\n");
}
void viewTask()
{
    FILE* smartlist = fopen("tasks.txt", "r");
    if (smartlist == NULL) {
        printf("Error opening smartlist!\n");
        return;
    }

    char task[1000];
    int count = 0;
    printf("\n--- Your Tasks ---\n");
    while (fgets(task, sizeof(task), smartlist) != NULL)
    {
        count++;
        printf("%d : %s",count,task);
    }
    printf("-----------------\n");

    fclose(smartlist);
}
