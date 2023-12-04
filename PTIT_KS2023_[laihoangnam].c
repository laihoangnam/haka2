#include <stdio.h>
#include <string.h>
#include <stdbool.h>
struct CD {
    int id;
    char name[50];
    float duration;
    char content[100];
    bool status;
};
void printCDList(struct CD cdList[], int size) {
    printf("Danh sach CD:\n");
    for (int i = 0; i < size; ++i) {
        printf("ID: %d, Ten: %s, Thoi luong: %.2f, Noi dung: %s, Trang thai: %s\n",
               cdList[i].id, cdList[i].name, cdList[i].duration,
               cdList[i].content, cdList[i].status ? "Da cho thue" : "Chua cho thue");
    }
    printf("\n");
}
void addNewCD(struct CD cdList[], int *size) {
    struct CD newCD;
    printf("Nhap ten CD: ");
    getchar();
    fgets(newCD.name, sizeof(newCD.name), stdin);
    strtok(newCD.name, "\n");
    printf("Nhap thoi luong CD: ");
    scanf("%f", &newCD.duration);
    printf("Nhap noi dung CD: ");
    getchar();
    fgets(newCD.content, sizeof(newCD.content), stdin);
    strtok(newCD.content, "\n");
    newCD.status = false;
    newCD.id = *size + 1;
    cdList[(*size)++] = newCD;

    printf("Them CD thanh cong!\n\n");
}
void updateCD(struct CD cdList[], int size) {
    char searchName[50];
    printf("Nhap ten CD can chinh sua: ");
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    strtok(searchName, "\n");
    int index = -1;
    for (int i = 0; i < size; ++i) {
        if (strcmp(cdList[i].name, searchName) == 0) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        printf("Nhap thong tin moi cho CD:\n");
        printf("Nhap ten CD: ");
        getchar();
        fgets(cdList[index].name, sizeof(cdList[index].name), stdin);
        strtok(cdList[index].name, "\n");
        printf("Nhap thoi luong CD: ");
        scanf("%f", &cdList[index].duration);
        printf("Nhap noi dung CD: ");
        getchar();
        fgets(cdList[index].content, sizeof(cdList[index].content), stdin);
        strtok(cdList[index].content, "\n");

        printf("Cap nhat CD thanh cong!\n\n");
    } else {
        printf("Khong tim thay CD!\n\n");
    }
}
void deleteCD(struct CD cdList[], int *size) {
    char deleteName[50];
    printf("Nhap ten CD can xoa: ");
    getchar();
    fgets(deleteName, sizeof(deleteName), stdin);
    strtok(deleteName, "\n");
    int index = -1;
    for (int i = 0; i < *size; ++i) {
        if (strcmp(cdList[i].name, deleteName) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < *size - 1; ++i) {
            cdList[i] = cdList[i + 1];
        }
        (*size)--;

        printf("Xoa CD thanh cong!\n\n");
    } else {
        printf("Khong tim thay CD!\n\n");
    }
}
void sortByDuration(struct CD cdList[], int size) {
    for (int i = 1; i < size; ++i) {
        struct CD key = cdList[i];
        int j = i - 1;
        while (j >= 0 && cdList[j].duration > key.duration) {
            cdList[j + 1] = cdList[j];
            j = j - 1;
        }
        cdList[j + 1] = key;
    }

    printf("Danh sach CD sau khi sap xep:\n");
    printCDList(cdList, size);
}
void binarySearchByName(struct CD cdList[], int size) {
    char searchName[50];
    printf("Nhap ten CD can tim kiem: ");
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    strtok(searchName, "\n");

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (strcmp(cdList[i].name, cdList[j].name) > 0) {
                struct CD temp = cdList[i];
                cdList[i] = cdList[j];
                cdList[j] = temp;
            }
        }
    }
    int left = 0, right = size - 1;
    int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (strcmp(cdList[mid].name, searchName) == 0) {
            result = mid;
            break;
        } else if (strcmp(cdList[mid].name, searchName) < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (result != -1) {
        printf("Thong tin CD can tim:\n");
        printf("ID: %d, Ten: %s, Thoi luong: %.2f, Noi dung: %s, Trang thai: %s\n",
               cdList[result].id, cdList[result].name, cdList[result].duration,
               cdList[result].content, cdList[result].status ? "Da cho thue" : "Chua cho thue");
    } else {
        printf("Khong tim thay CD!\n");
    }
}
void searchByStatus(struct CD cdList[], int size, bool searchStatus) {
    printf("Danh sach CD theo trang thai:\n");
    for (int i = 0; i < size; ++i) {
        if (cdList[i].status == searchStatus) {
            printf("ID: %d, Ten: %s, Thoi luong: %.2f, Noi dung: %s, Trang thai: %s\n",
                   cdList[i].id, cdList[i].name, cdList[i].duration,
                   cdList[i].content, cdList[i].status ? "Da cho thue" : "Chua cho thue");
        }
    }
}

int main() {
    const int MAX_CDS = 100;
    struct CD cdList[MAX_CDS];
    int cdSize = 2;
    cdList[0] = (struct CD){1, "CD1", 10.5, "Nhac Pop", false};
    cdList[1] = (struct CD){2, "CD2", 8.0, "Nhac Rock", true};
    do {
        printf("************************MENU**************************\n");
        printf("1. In toan bo danh sach CD\n");
        printf("2. Them moi CD\n");
        printf("3. Cap nhat thong tin CD\n");
        printf("4. Xoa CD\n");
        printf("5. Sap xep danh sach CD theo thoi luong tang dan\n");
        printf("6. Tim kiem CD theo ten (su dung tim kiem nhi phan)\n");
        printf("7. Tim kiem va in ra toan bo CD theo trang thai\n");
        printf("8. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        int choice;
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printCDList(cdList, cdSize);
                break;
            case 2:
                addNewCD(cdList, &cdSize);
                break;
            case 3:
                updateCD(cdList, cdSize);
                break;
            case 4:
                deleteCD(cdList, &cdSize);
                break;
            case 5:
                sortByDuration(cdList, cdSize);
                break;
            case 6:
                binarySearchByName(cdList, cdSize);
                break;
            case 7:
                printf("Nhap trang thai can tim (0: Chua cho thue, 1: Da cho thue): ");
                bool searchStatus;
                scanf("%d", &searchStatus);
                searchByStatus(cdList, cdSize, searchStatus);
                break;
            case 8:
                exit(0);
            default:
                printf("vui long nhap tu 1-8!\n");
        }
    } while (1==1);

    return 0;
}

