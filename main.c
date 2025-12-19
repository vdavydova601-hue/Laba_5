Оснавная работа с меню main.c :
#include "theater_db.h"

void print_menu() {
    printf("\n=== ТЕАТР ===\n");
    printf("1. Показать все\n");
    printf("2. Добавить\n");
    printf("3. Найти по ID\n");
    printf("4. Поиск по ряду и месту\n");
    printf("5. Удалить\n");
    printf("6. Сохранить\n");  
    printf("0. Выход\n");      
    printf("Выбор: ");
}

void search_by_seat(Record* head) {
    int target_row, target_seat;
    
    printf("\n=== ПОИСК ПО РЯДУ И МЕСТУ ===\n");
    printf("Введите ряд для поиска: ");
    scanf("%d", &target_row);
    printf("Введите место для поиска: ");
    scanf("%d", &target_seat);
    
    Record* current = head;
    int found_count = 0;
    
    printf("\nРезультаты поиска (Ряд %d, Место %d):\n", target_row, target_seat);
    printf("------------------------------------------------\n");
    
    while (current != NULL) {
        if (current->row == target_row && current->seat == target_seat) {
            printf("ID: %d\n", current->id);
            printf("Дата: %02d.%02d.%d\n", 
                   current->day, current->month, current->year);
            printf("Время: %02d:%02d\n", 
                   current->hour, current->minute);
            printf("Спектакль: %s\n", current->show);
            printf("---\n");
            found_count++;
        }
        current = current->next;
    }
    
    if (found_count == 0) {
        printf("Записей не найдено\n");
    } else {
        printf("Найдено записей: %d\n", found_count);
    }
}

int main() {
    Record* database = NULL;
    int next_id = 1;
    int choice;

    database = load_from_file(&next_id);
    if (database) {
        printf("Данные загружены из файла '%s'\n", FILENAME);
    } else {
        printf("Файл '%s' не найден. Создана новая база данных.\n", FILENAME);
    }
    
    do {
        print_menu();
        scanf("%d", &choice);
        
        // Очищаем буфер ввода
        while(getchar() != '\n');
        
        switch(choice) {
            case 1:  
                print_all(database);
                break;
                
            case 2:  
                database = add_record(database, &next_id);
                break;
                
            case 3: {  
                int id;
                printf("\n=== ПОИСК ПО ID ===\n");
                printf("Введите ID для поиска: ");
                scanf("%d", &id);
                
                Record* found = find_by_id(database, id);
                if (found) {
                    printf("\nНайдена запись:\n");
                    printf("ID: %d\n", found->id);
                    printf("Дата: %02d.%02d.%d\n", 
                           found->day, found->month, found->year);
                    printf("Время: %02d:%02d\n", 
                           found->hour, found->minute);
                    printf("Спектакль: %s\n", found->show);
                    printf("Ряд: %d, Место: %d\n", 
                           found->row, found->seat);
                } else {
                    printf("Запись с ID %d не найдена\n", id);
                }
                break;
            }
                
            case 4:  
                search_by_seat(database);
                break;
                
            case 5: { 
                int id;
                printf("\n=== УДАЛЕНИЕ ===\n");
                printf("Введите ID для удаления: ");
                scanf("%d", &id);
                database = remove_record(database, id);
                printf("Запись удалена (если существовала)\n");
                break;
            }
                
            case 6:  
                save_to_file(database);
                break;
                
            case 0:  
                printf("\nВыход из программы...\n");
                break;
                
            default:
                printf("\nНеверный выбор! Попробуйте снова.\n");
        }
        
        // Пауза для просмотра результатов (кроме выхода)
        if (choice != 0) {
            printf("\nНажмите Enter для продолжения...");
            getchar();
        }
        
    } while(choice != 0);
    

    save_to_file(database);
    free_list(database);
    
    printf("Данные сохранены в файл '%s'\n", FILENAME);
    return 0;
}




