#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

#define MAX 100

struct Product {
    int id;
    char name[30];
    float price;
    int qty;
};

Product products[MAX];
int productCount = 0;

/* ===== FUNCTION DECLARATIONS ===== */
void login();
void loadProducts();
void saveProducts();
void mainMenu();

void addProduct();
void updateProduct();
void deleteProduct();
void displayProducts();
int searchProduct(int id);

void sellProduct();
void lowStockAlert();
void salesReport();

/* ===== MAIN ===== */
int main() {
    loadProducts();
    login();
    mainMenu();
    saveProducts();
    return 0;
}

/* ===== LOGIN ===== */
void login() {
    char user[20], pass[20];

    do {
        system("cls");
        cout << "====================================\n";
        cout << "        ADMIN LOGIN PANEL\n";
        cout << "====================================\n";
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;

        if (strcmp(user, "admin") != 0 || strcmp(pass, "12345") != 0) {
            cout << "\n❌ Invalid Login!\n";
            system("pause");
        }
    } while (strcmp(user, "admin") != 0 || strcmp(pass, "12345") != 0);
}

/* ===== LOAD PRODUCTS ===== */
void loadProducts() {
    ifstream file("products.txt");
    productCount = 0;

    while (file >> products[productCount].id) {
        file.ignore();
        file.getline(products[productCount].name, 30);
        file >> products[productCount].price;
        file >> products[productCount].qty;
        productCount++;
    }
    file.close();
}

/* ===== SAVE PRODUCTS ===== */
void saveProducts() {
    ofstream file("products.txt");

    for (int i = 0; i < productCount; i++) {
        file << products[i].id << endl;
        file << products[i].name << endl;
        file << products[i].price << endl;
        file << products[i].qty << endl;
    }
    file.close();
}

/* ===== MAIN MENU ===== */
void mainMenu() {
    int choice;
    do {
        system("cls");
        cout << "=============================================\n";
        cout << "     E-COMMERCE STORE MANAGEMENT SYSTEM\n";
        cout << "=============================================\n";
        cout << "1. Add Product\n";
        cout << "2. Update Product\n";
        cout << "3. Delete Product\n";
        cout << "4. Display Products\n";
        cout << "5. Sell Product\n";
        cout << "6. Low Stock Alert\n";
        cout << "7. Sales Report\n";
        cout << "0. Exit\n";
        cout << "---------------------------------------------\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addProduct(); break;
        case 2: updateProduct(); break;
        case 3: deleteProduct(); break;
        case 4: displayProducts(); break;
        case 5: sellProduct(); break;
        case 6: lowStockAlert(); break;
        case 7: salesReport(); break;
        case 0: cout << "Exiting System...\n"; break;
        default: cout << "Invalid Choice!\n";
        }
        system("pause");
    } while (choice != 0);
}

/* ===== ADD PRODUCT ===== */
void addProduct() {
    system("cls");
    cout << "=========== ADD PRODUCT ===========\n";

    cout << "Enter ID: ";
    cin >> products[productCount].id;
    cin.ignore();

    cout << "Enter Name: ";
    cin.getline(products[productCount].name, 30);

    cout << "Enter Price: ";
    cin >> products[productCount].price;

    cout << "Enter Quantity: ";
    cin >> products[productCount].qty;

    productCount++;
    saveProducts();

    cout << "\n✅ Product Added Successfully!\n";
}

/* ===== SEARCH ===== */
int searchProduct(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id)
            return i;
    }
    return -1;
}

/* ===== UPDATE ===== */
void updateProduct() {
    int id;
    system("cls");
    cout << "=========== UPDATE PRODUCT ===========\n";
    cout << "Enter Product ID: ";
    cin >> id;

    int index = searchProduct(id);
    if (index == -1) {
        cout << "❌ Product Not Found!\n";
        return;
    }

    cout << "Enter New Price: ";
    cin >> products[index].price;

    cout << "Enter New Quantity: ";
    cin >> products[index].qty;

    saveProducts();
    cout << "\n✅ Product Updated!\n";
}

/* ===== DELETE ===== */
void deleteProduct() {
    int id;
    system("cls");
    cout << "=========== DELETE PRODUCT ===========\n";
    cout << "Enter Product ID: ";
    cin >> id;

    int index = searchProduct(id);
    if (index == -1) {
        cout << "❌ Product Not Found!\n";
        return;
    }

    for (int i = index; i < productCount - 1; i++)
        products[i] = products[i + 1];

    productCount--;
    saveProducts();
    cout << "\n✅ Product Deleted!\n";
}

/* ===== DISPLAY ===== */
void displayProducts() {
    system("cls");
    cout << "=============== PRODUCT LIST ===============\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Price"
         << setw(10) << "Qty\n";
    cout << "--------------------------------------------\n";

    for (int i = 0; i < productCount; i++) {
        cout << left << setw(10) << products[i].id
             << setw(20) << products[i].name
             << setw(10) << products[i].price
             << setw(10) << products[i].qty << endl;
    }
}

/* ===== SELL + INVOICE ===== */
void sellProduct() {
    int id, qty;
    system("cls");
    cout << "=============== SELL PRODUCT ===============\n";
    cout << "Enter Product ID: ";
    cin >> id;

    int index = searchProduct(id);
    if (index == -1) {
        cout << "❌ Product Not Found!\n";
        return;
    }

    cout << "Enter Quantity: ";
    cin >> qty;

    if (qty > products[index].qty) {
        cout << "❌ Insufficient Stock!\n";
        return;
    }

    products[index].qty -= qty;
    float total = qty * products[index].price;

    ofstream sale("sales.txt", ios::app);
    sale << products[index].id << " "
         << products[index].name << " "
         << qty << " "
         << total << endl;
    sale.close();

    saveProducts();

    cout << "\n============= SALES INVOICE =============\n";
    cout << "Product Name : " << products[index].name << endl;
    cout << "Unit Price  : Rs. " << products[index].price << endl;
    cout << "Quantity    : " << qty << endl;
    cout << "----------------------------------------\n";
    cout << "TOTAL BILL  : Rs. " << total << endl;
    cout << "========================================\n";
}

/* ===== LOW STOCK ===== */
void lowStockAlert() {
    system("cls");
    cout << "=========== LOW STOCK ALERT ===========\n";

    for (int i = 0; i < productCount; i++) {
        if (products[i].qty < 5) {
            cout << products[i].name
                 << " | Qty: " << products[i].qty << endl;
        }
    }
}

/* ===== SALES REPORT ===== */
void salesReport() {
    system("cls");
    ifstream file("sales.txt");
    float totalRevenue = 0;
    int id, qty;
    char name[30];
    float total;

    cout << "=============== SALES REPORT ===============\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Qty"
         << setw(10) << "Total\n";
    cout << "--------------------------------------------\n";

    while (file >> id >> name >> qty >> total) {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(10) << qty
             << setw(10) << total << endl;
        totalRevenue += total;
    }
    file.close();

    cout << "--------------------------------------------\n";
    cout << "TOTAL REVENUE: Rs. " << totalRevenue << endl;
}
