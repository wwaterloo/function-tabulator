#include <iostream>
#include <cmath>
#include <limits>
#include <fstream> 
#include <Windows.h>
#include <string>    
#include <sstream>   
#include <iomanip>

using namespace std;

// змінні для зберігання меж (a, b), кроку (h), кількості ітерацій (n) та стану програми
double a, b, h, n_raw;
int n;
bool data_is_loaded = false;

// очищення буфера введення після помилково введених даних
void clear_input() {
    cin.clear();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

// перевірка всіх введених даних на логічні помилки
bool verify_all_data() {
    if (a > b) {
        cout << "Wrong range. 'a' cannot be greater than 'b'\n";
        return false;
    }
    if (h <= 0) {
        cout << "Wrong data. 'h' must be greater than 0 to avoid infinite loop. Please try again\n";
        return false;
    }
    if (n_raw > 10000) {
        cout << "Wrong data. The number is too large to process. Max 'n' is 10000\n";
        return false;
    }
    if (n_raw != floor(n_raw) || n_raw < 2) {
        cout << "Wrong data. 'n' must be an integer greater than or equal to 2\n";
        return false;
    }
    return true;
}

// зчитування рядку, перевірка на 'q' для виходу та конвертування в число
bool read_and_check(const string& prompt, double& target, const string& error_msg, bool check_range = false) {
    string input_str;
    while (true) {
        cout << prompt;
        if (!(cin >> input_str)) { // перевірка на успішне зчитування рядка
            clear_input();
            continue;
        }

        if (input_str == "q" || input_str == "Q") { // якщо користувач ввів 'q' — вертаємося до головного меню
            cout << "\nInput cancelled. Returning to Main Menu...\n";
            return false;
        }

        stringstream ss(input_str);
        double temp_val;
        if (ss >> temp_val && ss.eof()) {
            if (check_range && a > temp_val) {
                cout << "Wrong range. 'a' cannot be greater than 'b'. Please try again\n";
                continue;
            }
            target = temp_val;
            return true;
        }
        cout << error_msg;
    }
}

// покрокове введення даних користувачем з клавіатури з валідацією
void input_from_keyboard() {
    cout << "\n---------- Keyboard Input -----------";
    cout << "\n\n'b' must be ≥ 'a'. Step 'h' must be > 0. Argument limit 'n' must be an integer and ≥ 2.";
    cout << "\n(Type 'q' at any step to cancel and return to Main Menu)\n";

    cout << "\n|===================================|\n";
    if (!read_and_check("Enter 'a': ", a, "Wrong data. 'a' must be a number. Please try again\n")) return;

    cout << "|===================================|\n";
    if (!read_and_check("Enter 'b' (must be greater than or equal to 'a'): ", b, "Wrong data. 'b' must be a number. Please try again\n", true)) return;

    cout << "|===================================|\n";
    while (true) { // цикл для гарантії введення додатного кроку 'h'
        if (!read_and_check("Enter 'h' (must be positive): ", h, "Wrong data. 'h' must be a number. Please try again\n")) return;
        if (h > 0) break;
        cout << "Wrong data. Step 'h' must be positive to avoid infinite loop. Try again\n";
    }

    cout << "|===================================|\n";
    while (true) { // перевірка, що 'n' — це ціле число від 2 до 10000
        if (!read_and_check("Enter 'n' (must be greater than or equal to 2): ", n_raw, "Wrong data. 'n' must be a number. Please try again\n")) return;
        if (n_raw > 10000) {
            cout << "The number is too large to process. Max 'n' is 10000. Please try again\n";
            continue;
        }
        if (n_raw == floor(n_raw) && n_raw >= 2) {
            n = static_cast<int>(n_raw);
            break;
        }
        cout << "Wrong data. 'n' must be an integer greater than or equal to 2. Please try again\n";
    }

    cout << "|===================================|\n";
    cout << "\nData entered and verified successfully\n";
    data_is_loaded = true; // фіксація, що дані успішно завантажені
}

// зчитування вхідних даних з текстового файлу
void input_from_file() {
    string filename;
    cout << "\nEnter input filename (e.g., input.txt): ";
    cin >> filename;
    ifstream infile(filename); // відкриття файлу для читання
    if (!infile) {
        cout << "\nError: Cannot open file. Make sure this file is in the project folder\n";
        return;
    }
    if (!(infile >> a) || !(infile >> b) || !(infile >> h) || !(infile >> n_raw)) { // зчитування 4-х чисел поспіль
        cout << "\nError: Invalid data format inside the file. Make sure it contains 4 pure numbers, each on a separate line\n";
        infile.close();
        return;
    }
    cout << "\nRead from file: a=" << a << ", b=" << b << ", h=" << h << ", n=" << n_raw << endl;
    if (verify_all_data()) { // перевірка коректності зчитаних з файлу даних
        cout << "Data loaded from file and verified successfully\n";
        n = static_cast<int>(n_raw);
        data_is_loaded = true;
    }
    else {
        cout << "File data verification failed\n";
    }
    infile.close(); // обов'язкове закриття файлу після роботи
}

// обчислення функції на проміжку від a до b з кроком h та запис результатів
void calculate_and_save_result() {
    if (!data_is_loaded) { // перевірка, чи взагалі є дані для обчислень
        cout << "Error: you must input the data first (Option 1)\n";
        return;
    }
    ofstream outfile("results.txt"); // створення/відкриття файлу для запису результатів
    if (!outfile) {
        cout << "Warning: Cannot create results.txt for saving\n";
    }

    cout << "\n------------- Results ---------------\n";
    if (outfile.is_open()) {
        outfile << "------------- Results ---------------\n\n";
    }

    // налаштування виведення чисел у фіксованому форматі без десяткової частини
    cout << fixed << setprecision(0);
    if (outfile.is_open()) {
        outfile << fixed << setprecision(0);
    }

    // виведення шапки таблиці в консоль
    cout << "\n+----------------------+----------------------+\n";
    cout << "| " << setw(20) << left << "x" << " | " << setw(20) << left << "y" << " |\n";
    cout << "+----------------------+----------------------+\n";

    // точний розрахунок кількості кроків, щоб уникнути нескінченного циклу
    long long steps = static_cast<long long>(floor((b - a) / h)) + 1;

    for (long long step = 0; step < steps; ++step) {
        // точне обчислення x для поточного кроку
        double x = a + step * h;

        if (x == 0) { // захист від ділення на нуль, якщо x = 0
            if (outfile.is_open()) outfile << "x = 0, y = Error (division by zero)\n";
            continue;
        }

        double y;
        if (x < 0) { // перша гілка умови (x від'ємний)
            double sum_val = 0;
            for (int i = 2; i <= (n + 1); ++i) {
                sum_val += (i - x * x);
            }
            y = 12 * x - sum_val;
        }
        else { // друга гілка умови (x додатній)
            double sum_val = 0;
            double x_squared = x * x;
            for (int i = 0; i <= n; ++i) {
                double mlt = 1;
                for (int j = 1; j <= (n - 1); ++j) {
                    mlt *= (static_cast<double>(i + j) / x_squared);
                    if (mlt == 0.0 || isinf(mlt)) {
                        break;
                    }
                }
                sum_val += mlt;
            }
            y = sum_val - 5 * x;
        }

        // записуємо всі результати у файл без обмежень
        if (isinf(y)) {
            if (outfile.is_open()) outfile << "x = " << x << ", y = [Result is too large (Infinity)]\n";
        }
        else {
            if (outfile.is_open()) outfile << "x = " << x << ", y = " << y << "\n";
        }

        // фільтр для консолі: виведення на екран лише кожного 1000-го кроку + початковий та кінцевий у вигляді таблиці
        if (step == 0 || step == steps - 1 || step % 1000 == 0) {
            if (isinf(y)) {
                cout << "| " << setw(20) << left << x << " | " << setw(20) << left << "[Infinity]" << " |\n";
            }
            else {
                cout << "| " << setw(20) << left << x << " | " << setw(20) << left << y << " |\n";
            }
        }
    }

    // закриваємо рамку таблиці в консолі
    cout << "+----------------------+----------------------+\n";

    if (outfile.is_open()) {
        cout << "\nResults automatically saved to 'results.txt'\n";
        outfile.close(); // закриття файлу з результатами
    }

    // скидаємо налаштування консолі до стандартних для іншого виводу програми
    cout << defaultfloat << setprecision(6);
}

int main() {
    SetConsoleCP(65001); // налаштування кодування UTF-8 для введення в консолі
    SetConsoleOutputCP(65001); // налаштування кодування UTF-8 для виведення в консолі (підтримка укр. мови та символів)
    int choice;
    cout << "|====================================|\n";
    cout << "|         FUNCTION TABULATOR         |\n";
    cout << "|====================================|\n\n";
    cout << "Welcome to the enhanced function tabulation application!\n";
    cout << "This software computes an advanced math algorithm with deep nested loops.\n\n";
    cout << "--- IMPORTANT USER INSTRUCTIONS & FILE FORMAT RULES ---\n\n";
    cout << "1. Inputs via keyboard are real-time bulletproof validated (prevents crashes).\n";
    cout << "2. 'b' must be ≥ 'a'. Step 'h' must be > 0. Argument limit 'n' must be an integer and ≥ 2.\n";
    cout << "3. Avoid inputs that contain x = 0 to bypass division-by-zero errors.\n";
    cout << "4. At any input stage, type 'q' to cancel and return to Main Menu. Type any letter in other cases to return.\n";
    cout << "5. IF USING FILE INPUT:\n";
    cout << "   - File must be located directly inside the project directory.\n";
    cout << "   - It must contain exactly 4 pure numbers each on a new line.\n";
    cout << "   - Ensure no extra letters, commas, or empty trailing rows exist.\n\n";
    cout << "Press Enter to load the application Main Menu...";
    cin.get(); // очікування натискання клавіші Enter від користувача перед стартом
    while (true) { // головний нескінченний цикл програми для роботи з меню
        cout << "\n=====================================\n";
        cout << "             Main Menu               \n";
        cout << "=====================================\n";
        cout << "1. Input data\n";
        cout << "2. Calculate result\n";
        cout << "3. Exit\n";
        cout << "\nSelect option: ";
        if (!(cin >> choice)) { // перевірка, чи користувач ввів саме число для вибору пункту меню
            cout << "Invalid menu option. Please try again\n";
            clear_input(); // очищення буфера у разі введення літери замість цифри
            continue; // повернення на початок циклу меню
        }
        if (choice == 1) { // гілка меню 1 - введення даних
            int input_choice;
            cout << "\nChoose input method:\n1. Input from Keyboard\n2. Input from File\n\nSelect: ";
            if (cin >> input_choice) { // перевірка успішності введення підпункту
                if (input_choice == 1) input_from_keyboard(); // виклик введення з клавіатури
                else if (input_choice == 2) input_from_file(); // виклик читання з файлу
                else {
                    cout << "Invalid input choice. Returning to Main Menu...\n";
                }
            }
            else { // обробка помилки, якщо замість 1 чи 2 ввели літеру та повернення до головного меню
                cout << "Invalid input choice. Returning to Main Menu...\n";
                clear_input(); // очищення некоректного вводу
            }
        }
        else if (choice == 2) { // гілка меню 2 - запуск обчислень та збереження результатів
            calculate_and_save_result();
        }
        else if (choice == 3) { // гілка меню 3 - вихід з програми
            cout << "\nExiting program. Goodbye!\n";
            break; // переривання головного циклу while для завершення роботи
        }
        else { // обробка ситуації, коли ввели число, якого немає в меню (наприклад, 15)
            cout << "Wrong option. Please select 1, 2 or 3\n";
        }
    }
    return 0;
}

