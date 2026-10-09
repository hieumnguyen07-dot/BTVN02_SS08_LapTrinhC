#include <stdio.h>
#include <string.h>

struct Account {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
    long long final_fee;
    int is_downgraded;
};

int main() {
    int n;
    printf("Nhap so luong tai khoan (1 <= N <= 100): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
        printf("[Loi] So luong tai khoan khong hop le (phai tu 1 den 100).\n");
        return 1;
    }

    struct Account accounts[100];
    int downgraded_count = 0;
    long long total_revenue = 0;

    for (int i = 0; i < n; i++) {
        printf(" Nhap thong tin tai khoan thu %d \n", i + 1);
        
        printf("Ma tai khoan (user_id): ");
        scanf("%d", &accounts[i].user_id);

        printf("Ten tai khoan (username): ");
        scanf("%s", accounts[i].username);

        while (1) {
            printf("Loai goi hien tai (1: Free, 2: Personal, 3: Family): ");
            scanf("%d", &accounts[i].plan_type);
            if (accounts[i].plan_type >= 1 && accounts[i].plan_type <= 3) {
                break;
            }
            printf("[Loi du lieu] Loai goi khong ton tai. Vui long nhap lai tu 1 den 3!\n");
        }

        while (1) {
            printf("So ngay no cuoc (days_overdue >= 0): ");
            scanf("%d", &accounts[i].days_overdue);
            if (accounts[i].days_overdue >= 0) {
                break;
            }
            printf("[Loi du lieu] So ngay no cuoc khong the am. Vui long nhap lai!\n");
        }

        while (1) {
            printf("So thiet bi dang ket noi (active_devices >= 0): ");
            scanf("%d", &accounts[i].active_devices);
            if (accounts[i].active_devices >= 0) {
                break;
            }
            printf("[Loi du lieu] So thiet bi ket noi khong the am. Vui long nhap lai!\n");
        }

        accounts[i].is_downgraded = 0;
    }

    for (int i = 0; i < n; i++) {
        // Quy tac 1: Ha cap do no cuoc (days_overdue >= 3)
        if (accounts[i].days_overdue >= 3) {
            if (accounts[i].plan_type != 1) {
                downgraded_count++;
                accounts[i].is_downgraded = 1;
            }
            accounts[i].plan_type = 1;
            accounts[i].final_fee = 0;
        } else {
            if (accounts[i].plan_type == 1) {
                accounts[i].final_fee = 0;
            } 
            else if (accounts[i].plan_type == 2) {
                accounts[i].final_fee = 120000;

                if (accounts[i].active_devices > 1) {
                    int excess_devices = accounts[i].active_devices - 1;
                    accounts[i].final_fee += (long long)excess_devices * 30000;
                }
            } 
            else if (accounts[i].plan_type == 3) {
                accounts[i].final_fee = 250000;
            }
        }
        total_revenue += accounts[i].final_fee;
    }

    printf("-----------------------------------------------------------------------------------------\n");
    printf("                    BAO CAO KET QUA RA SOAT & XU LY NO CUOC STREAMFLOW SaaS                \n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-10s | %-15s | %-10s | %-12s | %-12s | %-18s\n", 
           "Ma TK", "Ten TK", "Ma Goi", "So Thiet Bi", "So Ngay No", "Phi Thuc Thu (VND)");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-10d | %-15s | %-10d | %-12d | %-12d | %-18lld\n",
               accounts[i].user_id,
               accounts[i].username,
               accounts[i].plan_type,
               accounts[i].active_devices,
               accounts[i].days_overdue,
               accounts[i].final_fee);
    }
    printf("-----------------------------------------------------------------------------------------\n");
    printf("THONG KE TONG KET:\n");
    printf("- Tong doanh thu thuc te thu duoc trong ky: %lld VND\n", total_revenue);
    printf("- Tong so tai khoan dã bi ha cap ve goi Free: %d\n", downgraded_count);
    printf("-----------------------------------------------------------------------------------------\n");

    return 0;
}
