#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct City {
    char name[100];
    int population;
    int medianIncome;
    struct City* next;
} City;

typedef struct {
    City* head;
    City* tail;
} CityLinkedList;

CityLinkedList* createCityLinkedList() {
    CityLinkedList* list = (CityLinkedList*)malloc(sizeof(CityLinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

City* createCity(const char* name, int population, int medianIncome) {
    City* newCity = (City*)malloc(sizeof(City));
    strcpy(newCity->name, name);
    newCity->population = population;
    newCity->medianIncome = medianIncome;
    newCity->next = NULL;
    return newCity;
}

void addCityAtTail(CityLinkedList* list, const char* name, int population, int medianIncome) {
    City* newCity = createCity(name, population, medianIncome);
    if (list->tail == NULL) {
        list->head = newCity;
        list->tail = newCity;
        list->head = list->tail;
    } else {
        list->tail->next = newCity;
        list->tail = newCity;
    }
}

void addCityAtHead(CityLinkedList* list, const char* name, int population, int medianIncome) {
    City* newCity = createCity(name, population, medianIncome);
    if (list->head == NULL) {
        list->head = newCity;
        list->tail = newCity;
        list->head = list->tail;
    } else {
        newCity->next = list->head;
        list->head = newCity;
    }
}

void displayCityWithLargestPopulation(CityLinkedList* list) {
    if (list->head == NULL) {
        printf("No city records\n");
        return;
    }
    City* largest = list->head;
    City* current = list->head;
    while (current != NULL) {
        if (current->population > largest->population) {
            largest = current;
        }
        current = current->next;
    }
    printf("%s, %d, $%d\n", largest->name, largest->population, largest->medianIncome);
}

void displayAllCities(CityLinkedList* list) {
    if (list->head == NULL) {
        printf("No city records\n");
        return;
    }
    City* current = list->head;
    while(current!=NULL) {
        printf("%s, %d, $%d\n", current->name, current->population, current->medianIncome);
        current=current->next;
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    CityLinkedList* CityLinkedList = createCityLinkedList();
    int choice;
    char name[100];
    int population, medianIncome;
    while (1) {
        printf("\n===================\n");
        printf("City Management Menu\n");
        printf("===================\n");
        printf("1. Add a city record at the tail.\n");
        printf("2. Add city record at the head.\n");
        printf("3. Display the city with the largest population.\n");
        printf("4. Display all the city records.\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number between 1 and 5.\n");
            continue;
        }
        switch (choice) {
            case 1:
            case 2:
                printf("Enter city name: ");
                clearInputBuffer();
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline character

                printf("Enter city population: ");
                if (scanf("%d", &population) != 1) {
                    clearInputBuffer();
                    printf("Invalid input. Please enter a valid population.\n");
                    continue;
                }
                printf("Enter city median household income: ");
                if (scanf("%d", &medianIncome) != 1) {
                    clearInputBuffer();
                    printf("Invalid input. Please enter a valid median household income.\n");
                    continue;
                }
                if (choice == 1) {
                    addCityAtTail(CityLinkedList, name, population, medianIncome);
                } else {
                    addCityAtHead(CityLinkedList, name, population, medianIncome);
                }
                printf("City record added successfully!\n");
                break;
            case 3:
                printf("Displaying city with the largest population...\n");
                displayCityWithLargestPopulation(CityLinkedList);
                break;
            case 4:
                printf("Displaying all city records...\n");
                displayAllCities(CityLinkedList);
                break;
            case 5:
                printf("Exiting the program...\n");
                free(CityLinkedList);
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }
}