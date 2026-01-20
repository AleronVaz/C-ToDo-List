#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void addTask();
void viewTask();
void deleteTask();
void markCompleted();

int main()
{
    int choice;

    while (1) {
        printf("\n------ SMART TO-DO LIST ------\n");
        printf("1: Add Task\n");
        printf("2: View Task\n");
        printf("3: Delete Task\n");
        printf("4: Mark Task\n");
        printf("5: Exit\n");
        printf("------------------------------\n");
        printf("Enter your choice: ");

        scanf("%d",&choice);

        if (choice != 1 && choice != 2 && choice !=3 && choice !=4 && choice !=5)
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
            case 3: deleteTask();
                    break;
            case 4: markCompleted();
                    break;
            case 5: printf("Exiting the program\n");
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

void deleteTask()
{
    FILE* smartlist = fopen("tasks.txt","r");

    if (smartlist == NULL)
    {
        printf("no tasks found to delete\n");
        return;
    }
    char task[1000];
    int count;
    count = 0;

    printf("\n------Your Task List------\n");
    while(fgets(task,sizeof(task),smartlist) != NULL)
    {
        count++;
        printf("%d : %s",count,task);
    }
    fclose(smartlist);

    if(count==0)
    {
        printf("No task to delete\n");
        return;
    }
    int del;
    printf("Enter the number corresponding to which task you want to delete\n");
    scanf("%d",&del);
    getchar();

    if(del < 1 || del > count)
    {
        printf("Invalid task number\n");
        return;
    }

    smartlist = fopen("tasks.txt" , "r");
    FILE* temporary;
    temporary = fopen("temp.txt" , "w");

    int current = 0;
    while(fgets(task, sizeof(task),smartlist)!= NULL)
    {
        current++;
        if(current!=del)
        {
            fputs(task,temporary);
        }
    }
    fclose(smartlist);
    fclose(temporary);

    remove("tasks.txt");
    rename("temp.txt","tasks.txt");

    printf("task %d has been succesfully deleted\n",del);
}


void markCompleted()
 {
    FILE* smartlist = fopen("tasks.txt", "r");
    if (smartlist == NULL)
        {
            printf("No tasks found\n");
            return;
        }

    char task[1000];
    int count = 0;

    printf("\n---- Your Tasks ----\n");
    while (fgets(task, sizeof(task), smartlist) != NULL)
    {
        count++;
        printf("%d: %s", count, task);
    }

    fclose(smartlist);

    if (count == 0)
    {
        printf("No tasks to mark.\n");
        return;
    }

    int mark;
    printf("Enter the task number to mark as completed: ");
    scanf("%d", &mark);
    getchar();

    if (mark < 1 || mark > count) {
        printf("Invalid task number.\n");
        return;
    }


    smartlist = fopen("tasks.txt", "r");
    FILE* temporary = fopen("temp.txt", "w");

    int current = 0;

    while (fgets(task, sizeof(task), smartlist) != NULL) {
        current++;
        if (current == mark)
        {
            fprintf(temporary, "[Completed] %s", task);
        }
        else
        {
            fputs(task, temporary);
        }
    }

    fclose(smartlist);
    fclose(temporary);

    remove("tasks.txt");
    rename("temp.txt", "tasks.txt");

    printf("Task %d marked as completed!\n", mark);
}


