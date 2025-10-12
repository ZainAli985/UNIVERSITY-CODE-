#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    // Menu items and prices
    string item1 = "Coke";
    string item2 = "Pepsi";
    string item3 = "Water";
    string item4 = "Chips";
    string item5 = "Chocolate";
    string item6 = "Juice";
    string item7 = "Sandwich";
    string item8 = "Coffee";

    double price1 = 1.50;
    double price2 = 1.40;
    double price3 = 1.00;
    double price4 = 1.75;
    double price5 = 2.00;
    double price6 = 2.25;
    double price7 = 3.50;
    double price8 = 1.80;

    string selectedItem;
    double selectedPrice = 0.0;
    double gst = 0.0;
    double discount = 0.0;
    double total = 0.0;

    cout << fixed << setprecision(2);
    cout << "==============================\n";
    cout << "      VENDING MACHINE MENU\n";
    cout << "==============================\n";
    cout << "1. " << setw(12) << left << item1 << " - $" << price1 << endl;
    cout << "2. " << setw(12) << left << item2 << " - $" << price2 << endl;
    cout << "3. " << setw(12) << left << item3 << " - $" << price3 << endl;
    cout << "4. " << setw(12) << left << item4 << " - $" << price4 << endl;
    cout << "5. " << setw(12) << left << item5 << " - $" << price5 << endl;
    cout << "6. " << setw(12) << left << item6 << " - $" << price6 << endl;
    cout << "7. " << setw(12) << left << item7 << " - $" << price7 << endl;
    cout << "8. " << setw(12) << left << item8 << " - $" << price8 << endl;

    cout << "\nEnter the item number you want to buy: ";
    int choice;
    cin >> choice;

    // Item selection using if-else
    if (choice == 1) {
        selectedItem = item1;
        selectedPrice = price1;
    } else if (choice == 2) {
        selectedItem = item2;
        selectedPrice = price2;
    } else if (choice == 3) {
        selectedItem = item3;
        selectedPrice = price3;
    } else if (choice == 4) {
        selectedItem = item4;
        selectedPrice = price4;
    } else if (choice == 5) {
        selectedItem = item5;
        selectedPrice = price5;
    } else if (choice == 6) {
        selectedItem = item6;
        selectedPrice = price6;
    } else if (choice == 7) {
        selectedItem = item7;
        selectedPrice = price7;
    } else if (choice == 8) {
        selectedItem = item8;
        selectedPrice = price8;
    } else {
        cout << "Invalid Choice! Exiting Program.\n";
        return 0;
    }

    // Show selected item
    cout << "\nYou Selected: " << selectedItem << " ($" << selectedPrice << ")\n";

    // GST and discount calculation
    gst = selectedPrice * 0.03;  // 3% GST
    discount = 0.00;             // Discount
    total = selectedPrice + gst - discount;

    cout << "\n==============================\n";
    cout << "          BILL DETAILS\n";
    cout << "==============================\n";
    cout << "Item:        " << selectedItem << endl;
    cout << "Base Price:  $" << selectedPrice << endl;
    cout << "GST (3%):    $" << gst << endl;
    cout << "Discount:    $" << discount << endl;
    cout << "------------------------------\n";
    cout << "Total Bill:  $" << total << endl;

    // Payment section
    cout << "\n==============================\n";
    cout << "        PAYMENT SECTION\n";
    cout << "==============================\n";
    cout << "Select Payment Mode:\n";
    cout << "1. Cash\n2. Card\nEnter Choice: ";
    int paymentMode;
    cin >> paymentMode;

    if (paymentMode == 1) {
        double cash;
        cout << "Enter Cash Amount: $";
        cin >> cash;

    // ADDED +0.09 DUE TO FLOATING POINT ROUNDING ERROR 
        if (cash + 0.09 < total) {
            cout << "Insufficient Amount. Transaction Cancelled.\n";
            return 0;
        } else {
            double change = cash - total;
            cout << "Payment Successful (Cash)\n";
            if (change > 0)
                cout << "Change Returned: $" << change << endl;
        }

    } else if (paymentMode == 2) {
        int cardType;
        cout << "\nSelect Card Type:\n";
        cout << "1. MasterCard\n2. VISA\nEnter choice: ";
        cin >> cardType;

        string cardNumber;
        if (cardType == 1) {
            cout << "Enter your MasterCard number: ";
            cin >> cardNumber;
            cout << "Payment Successful (MasterCard)\n";
        } else if (cardType == 2) {
            cout << "Enter your VISA card number: ";
            cin >> cardNumber;
            cout << "Payment Successful (VISA)\n";
        } else {
            cout << "Invalid Card Type. Transaction Cancelled.\n";
            return 0;
        }

    } else {
        cout << "Invalid payment option. Transaction cancelled.\n";
        return 0;
    }

    // Final receipt
    cout << "\n==============================\n";
    cout << "         ORDER SUMMARY\n";
    cout << "==============================\n";
    cout << "Item:        " << selectedItem << endl;
    cout << "Base Price:  $" << selectedPrice << endl;
    cout << "GST (3%):    $" << gst << endl;
    cout << "Discount:    $" << discount << endl;
    cout << "------------------------------\n";
    cout << "Total Paid:  $" << total << endl;

    if (paymentMode == 1)
        cout << "Payment Mode: Cash\n";
    else
        cout << "Payment Mode: Card\n";

    cout << "==============================\n";
    cout << "   Thank You For Your Purchase!\n";
    cout << "==============================\n";

    return 0;
}
