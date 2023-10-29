#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Öğrenci yapısı tanımlandı
struct Student {
    int student_number;
    char name[50];
    int age;
    struct Student *next;
};

// Bağlı liste başlangıç düğümü oluşturuldu
struct Student *head = NULL;

// Yeni bir öğrenci ekleme fonksiyonu
void insertStudent(int student_number, char name[], int age) {
    struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
    newStudent->student_number = student_number;
    strcpy(newStudent->name, name);
    newStudent->age = age;
    newStudent->next = NULL;
    
    if (head == NULL) {
        head = newStudent;
    } else {
        struct Student *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }
}

// Öğrencileri ekranda gösterme fonksiyonu
void displayStudents() {
    struct Student *current = head;
    int index = 1;
    while (current != NULL) {
        printf("%d- %s %d %d\n", index, current->name, current->age, current->student_number);
        current = current->next;
        index++;
    }
}

// Öğrenci numarasına göre öğrencileri başa ve sona ekleme fonksiyonu
void addNumbersToFrontAndBack() {
    struct Student *current = head;
    struct Student *odd_head = NULL;
    struct Student *even_head = NULL;
    
    while (current != NULL) {
        struct Student *next = current->next;
        if (current->student_number % 2 == 1) {
            current->next = odd_head;
            odd_head = current;
        } else {
            current->next = even_head;
            even_head = current;
        }
        current = next;
    }
    
    // Tek ve çift öğrencileri birleştirme
    current = odd_head;
    if (current == NULL) {
        head = even_head;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = even_head;
        head = odd_head;
    }
}

// Öğrencileri isme göre sıralama fonksiyonu
void sortStudentsByName() {
    struct Student *current, *index;
    char temp_name[50];
    int temp_age, temp_student_number;

    if (head == NULL) {
        printf("Liste boş\n");
        return;
    } else {
        for (current = head; current != NULL; current = current->next) {
            for (index = current->next; index != NULL; index = index->next) {
                if (strcmp(current->name, index->name) > 0) {
                    strcpy(temp_name, current->name);
                    strcpy(current->name, index->name);
                    strcpy(index->name, temp_name);
                    
                    temp_age = current->age;
                    current->age = index->age;
                    index->age = temp_age;
                    
                    temp_student_number = current->student_number;
                    current->student_number = index->student_number;
                    index->student_number = temp_student_number;
                }
            }
        }
    }
}

// İsimle öğrenci arama fonksiyonu
void searchStudentByName(char name[]) {
    struct Student *current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("Öğrenci bulundu: %d- %s %d %d\n", current->student_number, current->name, current->age, current->student_number);
            found = 1;
            break;
        }
        current = current->next;
    }
    if (!found) {
        printf("Öğrenci bulunamadı\n");
    }
}

// İsimle öğrencinin bir sonraki öğrencisini silme fonksiyonu
void deleteNextStudentByName(char name[]) {
    struct Student *current = head;
    struct Student *temp = NULL;
    int found = 0;
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->next != NULL) {
                temp = current->next;
                current->next = current->next->next;
                free(temp);
                found = 1;
                printf("%s'in sonraki öğrencisi silindi\n", name);
            } else {
                printf("%s'in sonraki öğrencisi yok\n", name);
            }
            break;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Öğrenci bulunamadı\n");
    }
}

// En uzun ismi bulma fonksiyonu
void findLongestName() {
    struct Student *current = head;
    char longest_name[50];
    int max_length = 0;
    
    while (current != NULL) {
        int length = strlen(current->name);
        if (length > max_length) {
            max_length = length;
            strcpy(longest_name, current->name);
        }
        current = current->next;
    }
    
    printf("Listedeki en uzun isim: %s\n", longest_name);
}

int main() {
    int choice;
    
    do {
        printf("\nMenü:\n");
        printf("1. Öğrenci ekle\n");
        printf("2. Tüm öğrencileri görüntüle\n");
        printf("3. Numaraları başa ve sona ekle\n");
        printf("4. Öğrencileri isme göre sırala\n");
        printf("5. İsme göre öğrenci ara\n");
        printf("6. İsme göre bir sonraki öğrenciyi sil\n");
        printf("7. En uzun ismi bul\n");
        printf("0. Çıkış\n");
        printf("Seçiminizi girin: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int student_number, age;
                char name[50];
                printf("Öğrenci numarasını girin: ");
                scanf("%d", &student_number);
                printf("İsmi girin: ");
                scanf("%s", name);
                printf("Yaşı girin: ");
                scanf("%d", &age);
                insertStudent(student_number, name, age);
                break;
            }
            case 2: {
                displayStudents();
                break;
            }
            case 3: {
                addNumbersToFrontAndBack();
                break;
            }
            case 4: {
                sortStudentsByName();
                break;
            }
            case 5: {
                char search_name[50];
                printf("Aranacak ismi girin: ");
                scanf("%s", search_name);
                searchStudentByName(search_name);
                break;
            }
            case 6: {
                char delete_name[50];
                printf("Bir sonraki öğrenciyi silmek istediğiniz öğrencinin adını girin: ");
                scanf("%s", delete_name);
                deleteNextStudentByName(delete_name);
                break;
            }
            case 7: {
                findLongestName();
                break;
            }
        }
    } while (choice != 0);

    return 0;
}