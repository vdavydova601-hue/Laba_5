Работа с билетами и данных о покупателях, создание меню theater_db.c :
#include "theater_db.h"


Record* create_record(int id, int d, int m, int y, int hr, int min, 
                     const char* show, int r, int s) {
    Record* new = (Record*)malloc(sizeof(Record));
    if (new) {
        new->id = id;
        new->day = d; new->month = m; new->year = y;
        new->hour = hr; new->minute = min;
        strncpy(new->show, show, MAX_NAME-1);
        new->row = r;
        new->seat = s;
        new->next = NULL;
    }
    return new;
}


Record* add_record(Record* head, int* next_id) {
    int d, m, y, hr, min, r, s;
    char show[MAX_NAME];
    
    printf("Дата (д м г): "); scanf("%d %d %d", &d, &m, &y);
    printf("Время (ч м): "); scanf("%d %d", &hr, &min);
    printf("Спектакль: "); getchar(); fgets(show, MAX_NAME, stdin);
    show[strcspn(show, "\n")] = 0;
    printf("Ряд и место: "); scanf("%d %d", &r, &s);
    
    Record* new = create_record((*next_id)++, d, m, y, hr, min, show, r, s);
    
    if (!head) return new;
    
    Record* current = head;
    while (current->next) current = current->next;
    current->next = new;
    return head;
}

Record* remove_record(Record* head, int id) {
    if (!head) return NULL;
    
    if (head->id == id) {
        Record* temp = head->next;
        free(head);
        return temp;
    }
    
    Record* current = head;
    while (current->next && current->next->id != id) {
        current = current->next;
    }
    
    if (current->next) {
        Record* to_delete = current->next;
        current->next = to_delete->next;
        free(to_delete);
    }
    
    return head;
}


Record* find_by_id(Record* head, int id) {
    Record* current = head;
    while (current && current->id != id) {
        current = current->next;
    }
    return current;
}


void print_all(Record* head) {
    if (!head) {
        printf("База пуста\n");
        return;
    }
    
    printf("ID\tДата\t\tВремя\tСпектакль\t\tРяд\tМесто\n");
    printf("------------------------------------------------------------\n");
    
    Record* current = head;
    while (current) {
        printf("%d\t%02d.%02d.%d\t%02d:%02d\t%-20s\t%d\t%d\n",
               current->id,
               current->day, current->month, current->year,
               current->hour, current->minute,
               current->show,
               current->row, current->seat);
        current = current->next;
    }
}


void save_to_file(Record* head) {
    FILE* file = fopen(FILENAME, "w");
    if (!file) return;
    
    Record* current = head;
    while (current) {
        fprintf(file, "%d %d %d %d %d %d %s %d %d\n",
                current->id,
                current->day, current->month, current->year,
                current->hour, current->minute,
                current->show,
                current->row, current->seat);
        current = current->next;
    }
    
    fclose(file);
    printf("Сохранено\n");
}


Record* load_from_file(int* next_id) {
    FILE* file = fopen(FILENAME, "r");
    if (!file) return NULL;
    
    Record* head = NULL;
    Record* tail = NULL;
    *next_id = 1;
    
    int id, d, m, y, hr, min, r, s;
    char show[MAX_NAME];
    
    while (fscanf(file, "%d %d %d %d %d %d %s %d %d",
                  &id, &d, &m, &y, &hr, &min, show, &r, &s) == 9) {
        Record* new = create_record(id, d, m, y, hr, min, show, r, s);
        
        if (!head) {
            head = new;
            tail = new;
        } else {
            tail->next = new;
            tail = new;
        }
        
        if (id >= *next_id) *next_id = id + 1;
    }
    
    fclose(file);
    return head;
}


void free_list(Record* head) {
    Record* current = head;
    while (current) {
        Record* next = current->next;
        free(current);
        current = next;
    }
}





