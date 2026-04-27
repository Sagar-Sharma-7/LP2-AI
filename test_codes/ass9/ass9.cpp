#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
====================================================
Elementary Chatbot for Customer Interaction Application
Application: Online Shopping Customer Support
====================================================
*/

string toLowerCase(string text) {
    for (char &c : text) {
        c = tolower(c);
    }
    return text;
}

int main() {
    string userInput;

    cout << "=====================================\n";
    cout << " Welcome to ShopEasy Customer Support\n";
    cout << "=====================================\n";
    cout << "Type your question (type 'exit' to quit)\n\n";

    cin.ignore();

    while (true) {
        cout << "You: ";
        getline(cin, userInput);

        userInput = toLowerCase(userInput);

        if (userInput == "exit") {
            cout << "Bot: Thank you for visiting ShopEasy. Goodbye!\n";
            break;
        }
        else if (userInput.find("hello") != string::npos ||
                 userInput.find("hi") != string::npos) {
            cout << "Bot: Hello! How can I help you today?\n";
        }
        else if (userInput.find("order") != string::npos &&
                 userInput.find("track") != string::npos) {
            cout << "Bot: Please enter your Order ID in the orders section to track your package.\n";
        }
        else if (userInput.find("refund") != string::npos) {
            cout << "Bot: Refunds are processed within 5 to 7 business days after approval.\n";
        }
        else if (userInput.find("cancel") != string::npos) {
            cout << "Bot: You can cancel an order before it is shipped from the My Orders page.\n";
        }
        else if (userInput.find("payment") != string::npos) {
            cout << "Bot: We accept UPI, Debit Card, Credit Card, Net Banking, and Cash on Delivery.\n";
        }
        else if (userInput.find("delivery") != string::npos) {
            cout << "Bot: Standard delivery takes 3 to 5 working days.\n";
        }
        else if (userInput.find("contact") != string::npos) {
            cout << "Bot: You can contact our support team at support@shopeasy.com.\n";
        }
        else {
            cout << "Bot: Sorry, I did not understand that. Please try another question.\n";
        }
    }

    return 0;
}

/*
====================================================
Dummy Input Test Case
====================================================

hello
track order
refund status
payment methods
cancel my order
delivery time
contact support
exit

====================================================
Expected Output
====================================================

Bot: Hello! How can I help you today?
Bot: Please enter your Order ID in the orders section to track your package.
Bot: Refunds are processed within 5 to 7 business days after approval.
Bot: We accept UPI, Debit Card, Credit Card, Net Banking, and Cash on Delivery.
Bot: You can cancel an order before it is shipped from the My Orders page.
Bot: Standard delivery takes 3 to 5 working days.
Bot: You can contact our support team at support@shopeasy.com.
Bot: Thank you for visiting ShopEasy. Goodbye!

====================================================
*/