#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

// Account class to store account information
class Account {
    private:
        string name;
        string accountNumber;
        double balance;

    public:
        // Constructor
        Account(string name, string accountNumber, double balance) {
            this->name = name;
            this->accountNumber = accountNumber;
            this->balance = balance;
        }

        // Getters
        string getName() const {
            return name;
        }

        string getAccountNumber() const {
            return accountNumber;
        }

        double getBalance() const {
            return balance;
        }

        // Setters
        void setName(string name) {
            this->name = name;
        }

        void setAccountNumber(string accountNumber) {
            this->accountNumber = accountNumber;
        }

        void setBalance(double balance) {
            this->balance = balance;
        }

        // Deposit money to the account
        void deposit(double amount) {
            balance += amount;
        }

        // Withdraw money from the account
        void withdraw(double amount) {
            if (balance >= amount) {
                balance -= amount;
            }
        }
};

// Linked list class to manage accounts
class LinkedList {
    private:
        struct Node {
            Account account;
            Node* next;
        };
        Node* head;

    public:
        // Constructor
        LinkedList() {
            head = NULL;
        }

        // Destructor
        ~LinkedList() {
            Node* current = head;
            while (current != NULL) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }

        // Add a new account to the list
        void addAccount(Account account) {
            Node* newNode = new Node;
            newNode->account = account;
            newNode->next = head;
            head = newNode;
        }

        // Remove an account from the list
        void removeAccount(string accountNumber) {
            Node* current = head;
            Node* previous = NULL;
            while (current != NULL) {
                if (current->account.getAccountNumber() == accountNumber) {
                    if (previous == NULL) {
                        head = current->next;
                    } else {
                        previous->next = current->next;
                    }
                    delete current;
                    break;
                }
                previous = current;
                current = current->next;
            }
        }

        // Search for an account by its account number
        Account* searchAccount(string accountNumber) {
            Node* current = head;
            while (current != NULL) {
                if (current->account.getAccountNumber() == accountNumber) {
                    return &(current->account);
                }
                current = current->next;
            }
            return NULL;
        }

        // Display a list of all accounts
        void displayAccounts() const {
            Node* current = head;
            while (current != NULL) {
                const Account& account = current->account;
                cout << "Name: " << account.getName() << ", Account Number: " << account.getAccountNumber() << ", Balance: " << account.getBalance() << endl;
                current = current->next;
            }
        }
};

// Main function
int main() {
    // Create a linked list to store accounts
    LinkedList accounts;

    // Create a SFML window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Bank Management System");

    // Create a SFML font for text display
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }

    // Create a SFML text object for title
    sf::Text title("Bank Management System", font, 30);
    title.setPosition(sf::Vector2f(150, 50));

    // Create a SFML text object for instruction
    sf::Text instruction("Press 'N'to create a new account, 'D' to deposit, 'W' to withdraw, 'T' to transfer, 'S' to search, 'L' to display all accounts, or 'Q' to quit.", font, 20);
    instruction.setPosition(sf::Vector2f(50, 150));

    // Main loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::N) {
                    // Create a new account
                    string name, accountNumber;
                    double balance;
                    sf::Text nameText("Enter name:", font, 20);
                    nameText.setPosition(sf::Vector2f(50, 200));
                    sf::Text accountNumberText("Enter account number:", font, 20);
                    accountNumberText.setPosition(sf::Vector2f(50, 250));
                    sf::Text balanceText("Enter initial balance:", font, 20);
                    balanceText.setPosition(sf::Vector2f(50, 300));
                    sf::String inputName, inputAccountNumber, inputBalance;
                    sf::Text inputNameText("", font, 20);
                    inputNameText.setPosition(sf::Vector2f(300, 200));
                    sf::Text inputAccountNumberText("", font, 20);
                    inputAccountNumberText.setPosition(sf::Vector2f(300, 250));
                    sf::Text inputBalanceText("", font, 20);
                    inputBalanceText.setPosition(sf::Vector2f(300, 300));
                    bool inputting = true;
                    while (inputting) {
                        window.clear();
                        window.draw(title);
                        window.draw(instruction);
                        window.draw(nameText);
                        window.draw(accountNumberText);
                        window.draw(balanceText);
                        window.draw(inputNameText);
                        window.draw(inputAccountNumberText);
                        window.draw(inputBalanceText);
                        window.display();
                        sf::Event inputEvent;
                        while (window.pollEvent(inputEvent)) {
                            if (inputEvent.type == sf::Event::TextEntered) {
                                if (inputEvent.text.unicode == '\b') {
                                    if (inputName.getSize() > 0) {
                                        inputName.erase(inputName.getSize() - 1, 1);
                                    }
                                    if (inputAccountNumber.getSize() > 0) {
                                        inputAccountNumber.erase(inputAccountNumber.getSize() - 1, 1);
                                    }
                                    if (inputBalance.getSize() > 0) {
                                        inputBalance.erase(inputBalance.getSize() - 1, 1);
                                    }
                                } else if (inputEvent.text.unicode == '\r') {
                                    if (inputName.getSize() > 0 && inputAccountNumber.getSize() > 0 && inputBalance.getSize() > 0) {
                                        name = inputName;
                                        accountNumber = inputAccountNumber;
                                        balance = stod(inputBalance);
                                        inputting = false;
                                    }
                                } else {
                                    if (inputName.getSize() < 20 && inputEvent.text.unicode >= 32 && inputEvent.text.unicode <= 126) {
                                        inputName += inputEvent.text.unicode;
                                    }
                                    if (inputAccountNumber.getSize() < 10 && inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57) {
                                        inputAccountNumber += inputEvent.text.unicode;
                                    }
                                    if (inputBalance.getSize() < 10 && (inputEvent.text.unicode == '.' || (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57))) {
                                        inputBalance += inputEvent.text.unicode;
                                    }
                                }
                                inputNameText.setString(inputName);
                                inputAccountNumberText.setString(inputAccountNumber);
                                inputBalanceText.setString(inputBalance);
                            }
                        }
                    }
                    Account newAccount(name, accountNumber, balance);
                    accounts.addAccount(newAccount);
                } else if (event.key.code == sf::Keyboard::D) {
                    // Deposit money to an account
                    sf::Text accountNumberText("Enter account number:", font, 20);
                    accountNumberText.setPosition(sf::Vector2f(50, 200));
                    sf::Text amountText("Enter amount to deposit:", font, 20);
                    amountText.setPosition(sf::Vector2f(50, 250));
                    sf::String inputAccountNumber, inputAmount;
                    sf::Text inputAccountNumberText("", font, 20);
                    inputAccountNumberText.setPosition(sf::Vector2f(300, 200));
                    sf::Text inputAmountText("", font, 20);
                    inputAmountText.setPosition(sf::Vector2f(300, 250));
                    bool inputting = true;
                    while (inputting) {
                        window.clear();
                        window.draw(title);
                        window.draw(instruction);
                        window.draw(accountNumberText);
                        window.draw(amountText);
                        window.draw(inputAccountNumberText);
                        window.draw(inputAmountText);
                        window.display();
                        sf::Event inputEvent;
                        while (window.pollEvent(inputEvent)) {
                            if (inputEvent.type == sf::Event::TextEntered) {
                                if (inputEvent.text.unicode == '\b') {
                                    if (inputAccountNumber.getSize() > 0) {
                                        inputAccountNumber.erase(inputAccountNumber.getSize() - 1, 1);
                                    }
                                    if (inputAmount.getSize() > 0) {
                                        inputAmount.erase(inputAmount.getSize() - 1, 1);
                                    }
                                } else if (inputEvent.text.unicode == '\r') {
                                    if (inputAccountNumber.getSize() > 0 && inputAmount.getSize() > 0) {
                                        Account* account = accounts.searchAccount(inputAccountNumber);
                                        if (account != NULL) {
                                            double amount = stod(inputAmount);
                                            account->deposit(amount);
                                            inputting = false;
                                        }
                                    }
                                } else {
                                    if (inputAccountNumber.getSize() < 10 && inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57) {
                                        inputAccountNumber += inputEvent.text.unicode;
                                    }
                                    if (inputAmount.getSize() < 10 && (inputEvent.text.unicode == '.' || (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57))) {
                                        inputAmount += inputEvent.text.unicode;
                                    }
                                }
                                inputAccountNumberText.setString(inputAccountNumber);
                                inputAmountText.setString(inputAmount);
                            }
                        }
                    }
                } else if (event.key.code == sf::Keyboard::W) {
                    // Withdraw money from an account
                    sf::Text accountNumberText("Enter account number:", font, 20);
                    accountNumberText.setPosition(sf::Vector2f(50, 200));
                    sf::Text amountText("Enter amount to withdraw:", font, 20);
                    amountText.setPosition(sf::Vector2f(50, 250));
                    sf::String inputAccountNumber, inputAmount;
                    sf::Text inputAccountNumberText("", font, 20);
                    inputAccountNumberText.setPosition(sf::Vector2f(300, 200));
                    sf::Text inputAmountText("", font, 20);
                    inputAmountText.setPosition(sf::Vector2f(300, 250));
                    bool inputting = true;
                    while (inputting) {
                        window.clear();
                        window.draw(title);
                        window.draw(instruction);
                        window.draw(accountNumberText);
                        window.draw(amountText);
                        window.draw(inputAccountNumberText);
                        window.draw(inputAmountText);
                        window.display();
                        sf::Event inputEvent;
                        while (window.pollEvent(inputEvent)) {
                            if (inputEvent.type == sf::Event::TextEntered) {
                                if (inputEvent.text.unicode == '\b') {
                                    if (inputAccountNumber.getSize() > 0) {
                                        inputAccountNumber.erase(inputAccountNumber.getSize() - 1, 1);
                                    }
                                    if (inputAmount.getSize() > 0) {
                                        inputAmount.erase(inputAmount.getSize() - 1, 1);
                                    }
                                } else if (inputEvent.text.unicode == '\r') {
                                    if (inputAccountNumber.getSize() > 0 && inputAmount.getSize() > 0) {
                                        Account* account = accounts.searchAccount(inputAccountNumber);
                                        if (account != NULL) {
                                            double amount = stod(inputAmount);
                                            account->withdraw(amount);
                                            inputting = false;
                                        }
                                    }
                                } else {
                                    if (inputAccountNumber.getSize() < 10 && inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57) {
                                        inputAccountNumber += inputEvent.text.unicode;
                                    }
                                    if (inputAmount.getSize() < 10 && (inputEvent.text.unicode == '.' || (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57))) {
                                        inputAmount += inputEvent.text.unicode;
                                    }
                                }
                                inputAccountNumberText.setString(inputAccountNumber);
                                inputAmountText.setString(inputAmount);
                            }
                        }
                    }
                } else if (event.key.code == sf::Keyboard::T) {
                    // Transfer money between accounts
                    sf::Text fromAccountNumberText("Enter account number to transfer from:", font, 20);
                    fromAccountNumberText.setPosition(sf::Vector2f(50, 200));
                    sf::Text toAccountNumberText("Enter account number to transfer to:", font, 20);
                    toAccountNumberText.setPosition(sf::Vector2f(50, 250));
                    sf::Text amountText("Enter amount to transfer:", font, 20);
                    amountText.setPosition(sf::Vector2f(50, 300));
                    sf::String inputFromAccountNumber, inputToAccountNumber, inputAmount;
                    sf::Text inputFromAccountNumberText("", font, 20);
                    inputFromAccountNumberText.setPosition(sf::Vector2f(400, 200));
                    sf::Text inputToAccountNumberText("", font, 20);
                    inputToAccountNumberText.setPosition(sf::Vector2f(400, 250));
                    sf::Text inputAmountText("", font, 20);
                    inputAmountText.setPosition(sf::Vector2f(400, 300));
                    bool inputting = true;
                    while (inputting) {
                        window.clear();
                        window.draw(title);
                        window.draw(instruction);
                        window.draw(fromAccountNumberText);
                        window.draw(toAccountNumberText);
                        window.draw(amountText);
                        window.draw(inputFromAccountNumberText);
                        window.draw(inputToAccountNumberText);
                        window.draw(inputAmountText);
                        window.display();
                        sf::Event inputEvent;
                        while (window.pollEvent(inputEvent)) {
                            if (inputEvent.type == sf::Event::TextEntered) {
                                if (inputEvent.text.unicode == '\b') {
                                    if (inputFromAccountNumber.getSize() > 0) {
                                        inputFromAccountNumber.erase(inputFromAccountNumber.getSize() - 1, 1);
                                    }
                                    if (inputToAccountNumber.getSize() > 0) {
                                        inputToAccountNumber.erase(inputToAccountNumber.getSize() - 1, 1);
                                    }
                                    if (inputAmount.getSize() > 0) {
                                        inputAmount.erase(inputAmount.getSize() - 1, 1);
                                    }
                                } else if (inputEvent.text.unicode == '\r') {
                                    if (inputFromAccountNumber.getSize() > 0 && inputToAccountNumber.getSize() > 0 && inputAmount.getSize() > 0) {
                                        Account* fromAccount = accounts.searchAccount(inputFromAccountNumber);
                                        Account* toAccount = accounts.searchAccount(inputToAccountNumber);
                                        if (fromAccount != NULL && toAccount != NULL) {
                                            double amount = stod(inputAmount);
                                            fromAccount->withdraw(amount);
                                            toAccount->deposit(amount);
                                            inputting = false;
                                        }
                                    }
                                } else {
                                    if (inputFromAccountNumber.getSize() < 10 && inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57) {
                                        inputFromAccountNumber += inputEvent.text.unicode;
                                    }
                                    if (inputToAccountNumber.getSize() < 10 && inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57) {
                                        inputToAccountNumber += inputEvent.text.unicode;
                                    }
                                    if (inputAmount.getSize() < 10 && (inputEvent.text.unicode == '.' || (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57))) {
                                        inputAmount += inputEvent.text.unicode;
                                    }
                                }
                                inputFromAccountNumberText.setString(inputFromAccountNumber);
                                inputToAccountNumberText.setString(inputToAccountNumber);
                                inputAmountText.setString(inputAmount);
                            }
                        }
                    }
                }
            }
        }
        window.close();
        return 0;
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Banking System");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font file\n";
        return 1;
    }
    sf::Text title("Banking System", font, 40);
    title.setPosition(sf::Vector2f(250, 50));
    sf::Text instruction("Press C to create an account, D to deposit money, W to withdraw money, T to transfer money, or Q to quit", font, 20);
    instruction.setPosition(sf::Vector2f(50, 150));
    AccountDatabase accounts;
    bool running = true;
    while (running) {
        window.clear();
        window.draw(title);
        window.draw(instruction);
        window.display();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    running = false;
                } else if (event.key.code == sf::Keyboard::C) {
                    // Create a new account
                    sf::Text nameText("Enter account holder name:", font, 20);
                    nameText.setPosition(sf::Vector2f(50, 200));
                    sf::Text balanceText("Enter starting balance:", font, 20);
                    balanceText.setPosition(sf::Vector2f(50, 250));
                    sf::String inputName, inputBalance;
                    sf::Text inputNameText("", font, 20);
                    inputNameText.setPosition(sf::Vector2f(300, 200));
                    sf::Text inputBalanceText("", font, 20);
                    inputBalanceText.setPosition(sf::Vector2f(300, 250));
                    bool inputting = true;
                    while (inputting) {
                        window.clear();
                        window.draw(title);
                        window.draw(instruction);
                        window.draw(nameText);
                        window.draw(balanceText);
                        window.draw(inputNameText);
                        window.draw(inputBalanceText);
                        window.display();
                        sf::Event inputEvent;
                        while (window.pollEvent(inputEvent)) {
                            if (inputEvent.type == sf::Event::TextEntered) {
                                if (inputEvent.text.unicode == '\b') {
                                    if (inputName.getSize() > 0) {
                                        inputName.erase(inputName.getSize() - 1, 1);
                                    }
                                    if (inputBalance.getSize() > 0) {
                                        inputBalance.erase(inputBalance.getSize() - 1, 1);
                                    }
                                } else if (inputEvent.text.unicode == '\r') {
                                    if (inputName.getSize() > 0 && inputBalance.getSize() > 0) {
                                        std::string name = inputName;
                                        double balance = stod(inputBalance);
                                        accounts.addAccount(name, balance);
                                        inputting = false;
                                    }
                                } else {
                                    if (inputName.getSize() < 50 && ((inputEvent.text.unicode >= 65 && inputEvent.text.unicode <= 90) || (inputEvent.text.unicode >= 97 && inputEvent.text.unicode <= 122))) {
                                        inputName += inputEvent.text.unicode;
                                    }
                                    if (inputBalance.getSize() < 10 && (inputEvent.text.unicode == '.' || (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57))) {
                                        inputBalance += inputEvent.text.unicode;
                                    }
                                }
                                inputNameText.setString(inputName);
                                inputBalanceText.setString(inputBalance);
                            }
                        }
                    }
                } else if (event.key.code == sf::Keyboard::D) {
                    // Deposit money into an account
                    sf::Text accountNumberText("Enter account number:", font, 20);
                    accountNumberText.setPosition(sf::Vector2f(50, 200));
                    sf::Text amountText("Enter amount to deposit:", font, 20);
                    amountText.setPosition(sf::Vector2f(50, 250));
                    sf::String inputAccountNumber, inputAmount;
                    sf::Text inputAccountNumberText("", font, 20);
                    inputAccountNumberText.setPosition(sf::Vector2f(300, 200));
                    sf::Text inputAmountText("", font, 20);
                    inputAmountText.setPosition(sf::Vector2f(300, 250));
                    bool inputting = true;
                    while (inputting) {
                        window.clear();
                        window.draw(title);
                        window.draw(instruction);
                        window.draw(accountNumberText);
                        window.draw(amountText);
                        window.draw(inputAccountNumberText);
                        window.draw(inputAmountText);
                        window.display();
                        sf::Event inputEvent;
                        while (window.pollEvent(inputEvent)) {
                            if (inputEvent.type == sf::Event::TextEntered) {
                                if (inputEvent.text.unicode == '\b') {
                                    if (inputAccountNumber.getSize() > 0) {
                                        inputAccountNumber.erase(inputAccountNumber.getSize() - 1, 1);
                                    }
                                    if (inputAmount.getSize() > 0) {
                                        inputAmount.erase(inputAmount.getSize() - 1, 1);
                                    }
                                } else if (inputEvent.text.unicode == '\r') {
                                    if (inputAccountNumber.getSize() > 0 && inputAmount.getSize() > 0) {
                                        int accountNumber = stoi(inputAccountNumber);
                                        double amount = stod(inputAmount);
                                        if (accounts.accountExists(accountNumber)) {
                                            accounts.deposit(accountNumber, amount);
                                            inputting = false;
                                        }
                                    }
                                } else {
                                    if (inputAccountNumber.getSize() < 10 && (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57)) {
                                        inputAccountNumber += inputEvent.text.unicode;
                                    }
                                    if (inputAmount.getSize() < 10 && (inputEvent.text.unicode == '.' || (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57))) {
                                        inputAmount += inputEvent.text.unicode;
                                    }
                                }
                                inputAccountNumberText.setString(inputAccountNumber);
                                inputAmountText.setString(inputAmount);
                            }
                        }
                    }
                } else if (event.key.code == sf::Keyboard::W) {
                    // Withdraw money from an account
                    sf::Text accountNumberText("Enter account number:", font, 20);
                    accountNumberText.setPosition(sf::Vector2f(50, 200));
                    sf::Text amountText("Enter amount to withdraw:", font, 20);
                    amountText.setPosition(sf::Vector2f(50, 250));
                    sf::String inputAccountNumber, inputAmount;
                    sf::Text inputAccountNumberText("", font, 20);
                    inputAccountNumberText.setPosition(sf::Vector2f(300, 200));
                    sf::Text inputAmountText("", font, 20);
                    inputAmountText.setPosition(sf::Vector2f(300, 250));
                    bool inputting = true;
                    while (inputting) {
                        window.clear();
                        window.draw(title);
                        window.draw(instruction);
                        window.draw(accountNumberText);
                        window.draw(amountText);
                        window.draw(inputAccountNumberText);
                        window.draw(inputAmountText);
                        window.display();
                        sf::Event inputEvent;
                        while (window.pollEvent(inputEvent)) {
                            if (inputEvent.type == sf::Event::TextEntered) {
                                if (inputEvent.text.unicode == '\b') {
                                    if (inputAccountNumber.getSize() > 0) {
                                        inputAccountNumber.erase(inputAccountNumber.getSize() - 1, 1);
                                    }
                                    if (inputAmount.getSize() > 0) {
                                        inputAmount.erase(inputAmount.getSize() - 1, 1);
                                    }
                                } else if (inputEvent.text.unicode == '\r') {
                                    if (inputAccountNumber.getSize() > 0 && inputAmount.getSize() > 0) {
                                        int accountNumber = stoi(inputAccountNumber);
                                        double amount = stod(inputAmount);
                                        if (accounts.accountExists(accountNumber)) {
                                            if (accounts.getBalance(accountNumber) >= amount) {
                                                accounts.withdraw(accountNumber, amount);
                                                inputting = false;
                                            }
                                        }
                                    }
                                } else {
                                    if (inputAccountNumber.getSize() < 10 && (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57)) {
                                        inputAccountNumber += inputEvent.text.unicode;
                                    }
                                    if (inputAmount.getSize() < 10 && (inputEvent.text.unicode == '.' || (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57))) {
                                        inputAmount += inputEvent.text.unicode;
                                    }
                                }
                                inputAccountNumberText.setString(inputAccountNumber);
                                inputAmountText.setString(inputAmount);
                            }
                        }
                    }
                } else if (event.key.code == sf::Keyboard::T) {
                    // Transfer money from one account to another
                    sf::Text sourceAccountNumberText("Enter source account number:", font, 20);
                    sourceAccountNumberText.setPosition(sf::Vector2f(50, 200));
                    sf::Text destinationAccountNumberText("Enter destination account number:", font, 20);
                    destinationAccountNumberText.setPosition(sf::Vector2f(50, 250));
                    sf::Text amountText("Enter amount to transfer:", font, 20);
                    amountText.setPosition(sf::Vector2f(50, 300));
                    sf::String inputSourceAccountNumber, inputsf::String inputDestinationAccountNumber, inputAmount;
                    sf::Text inputSourceAccountNumberText("", font, 20);
                    inputSourceAccountNumberText.setPosition(sf::Vector2f(300, 200));
                    sf::Text inputDestinationAccountNumberText("", font, 20);
                    inputDestinationAccountNumberText.setPosition(sf::Vector2f(300, 250));
                    sf::Text inputAmountText("", font, 20);
                    inputAmountText.setPosition(sf::Vector2f(300, 300));
                    bool inputting = true;
                    while (inputting) {
                        window.clear();
                        window.draw(title);
                        window.draw(instruction);
                        window.draw(sourceAccountNumberText);
                        window.draw(destinationAccountNumberText);
                        window.draw(amountText);
                        window.draw(inputSourceAccountNumberText);
                        window.draw(inputDestinationAccountNumberText);
                        window.draw(inputAmountText);
                        window.display();
                        sf::Event inputEvent;
                        while (window.pollEvent(inputEvent)) {
                            if (inputEvent.type == sf::Event::TextEntered) {
                                if (inputEvent.text.unicode == '\b') {
                                    if (inputSourceAccountNumber.getSize() > 0) {
                                        inputSourceAccountNumber.erase(inputSourceAccountNumber.getSize() - 1, 1);
                                    }
                                    if (inputDestinationAccountNumber.getSize() > 0) {
                                        inputDestinationAccountNumber.erase(inputDestinationAccountNumber.getSize() - 1, 1);
                                    }
                                    if (inputAmount.getSize() > 0) {
                                        inputAmount.erase(inputAmount.getSize() - 1, 1);
                                    }
                                } else if (inputEvent.text.unicode == '\r') {
                                    if (inputSourceAccountNumber.getSize() > 0 && inputDestinationAccountNumber.getSize() > 0 && inputAmount.getSize() > 0) {
                                        int sourceAccountNumber = stoi(inputSourceAccountNumber);
                                        int destinationAccountNumber = stoi(inputDestinationAccountNumber);
                                        double amount = stod(inputAmount);
                                        if (accounts.accountExists(sourceAccountNumber) && accounts.accountExists(destinationAccountNumber)) {
                                            if (accounts.getBalance(sourceAccountNumber) >= amount) {
                                                accounts.transfer(sourceAccountNumber, destinationAccountNumber, amount);
                                                inputting = false;
                                            }
                                        }
                                    }
                                } else {
                                    if (inputSourceAccountNumber.getSize() < 10 && (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57)) {
                                        inputSourceAccountNumber += inputEvent.text.unicode;
                                    }
                                    if (inputDestinationAccountNumber.getSize() < 10 && (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57)) {
                                        inputDestinationAccountNumber += inputEvent.text.unicode;
                                    }
                                    if (inputAmount.getSize() < 10 && (inputEvent.text.unicode == '.' || (inputEvent.text.unicode >= 48 && inputEvent.text.unicode <= 57))) {
                                        inputAmount += inputEvent.text.unicode;
                                    }
                                }
                                inputSourceAccountNumberText.setString(inputSourceAccountNumber);
                                inputDestinationAccountNumberText.setString(inputDestinationAccountNumber);
                                inputAmountText.setString(inputAmount);
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}