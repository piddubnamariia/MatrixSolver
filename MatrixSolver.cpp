#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include <limits>

#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

#define MENU "menu"
#define USER_MANUAL "user_manual"

using namespace std;

// Функція для очищення консолі
void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Функція для завантаження вмісту файлу
void loadFileContent(const string &fileName) {
    if (!(fileName == "")) {
        ifstream file(fileName);
        if (file.is_open()) {
            if (file.peek() == ifstream::traits_type::eof()) {
                throw runtime_error("Файл " + fileName + " порожній.");
            }
            cout << file.rdbuf();
            file.close();
        }
        else {
            throw runtime_error("Файлу " + fileName + " не існує.");
        }
    }
    else {
        throw runtime_error("Назву файлу не задано.");
    }
}

// Функція для задання розмірів матриці
void setMatrixSize(int &rows, int &cols) {
    cout << "Введіть кількість рядків: ";
    while (!(cin >> rows) || rows <= 0 || rows > 100) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << RED << "Некоректний ввід. Будь ласка, введіть ціле число від 1 до 100: " << RESET;
    }

    cout << "Введіть кількість стовпців: ";
    while (!(cin >> cols) || cols <= 0 || cols > 100) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << RED << "Некоректний ввід. Будь ласка, введіть ціле число від 1 до 100: " << RESET;
    }
}

// Функція для генерації випадкової матриці розміром rows x cols
vector<vector<double>> generateRandomMatrix(int rows, int cols) {
    vector<vector<double>> matrix(rows, vector<double>(cols, 0.0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 41 - 20;
        }
    }
    return matrix;
}

// Функція для введення матриці вручну
vector<vector<double>> inputMatrix(int rows, int cols) {
    vector<vector<double>> matrix(rows, vector<double>(cols, 0.0));
    cout << "Введіть елементи матриці:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "Елемент [" << i + 1 << "][" << j + 1 << "]: ";
            while (!(cin >> matrix[i][j])) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << RED << "Некоректний ввід. Будь ласка, повторно введіть елемент [" << i + 1 << "][" << j + 1 << "]: " << RESET;
            }
        }
    }
    return matrix;
}

// Функція для зчитування матриці з файлу
vector<vector<double>> readMatrixFromFile(const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Файлу " + fileName + " не існує.");
    }

    if (file.peek() == ifstream::traits_type::eof()) {
        throw runtime_error("Файл " + fileName + " порожній.");
    }

    if (fileName == MENU || fileName == USER_MANUAL) {
        throw runtime_error("Файл " + fileName + " не може бути використаний для зчитування матриці.");
    }

    int rows = 0, cols = 0;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        double num;
        int currentCols = 0;

        // Зчитування чисел з рядка
        while (iss >> num) {
            ++currentCols;
        }

        if (currentCols > 0) {
            if (cols == 0) {
                cols = currentCols;
            }
            else if (cols != currentCols) {
                throw runtime_error("Некоректна кількість стовпців.");
            }

            ++rows;
        }
    }

    file.clear();
    file.seekg(0, ios::beg);

    vector<vector<double>> matrix(rows, vector<double>(cols, 0.0));
    int row = 0;

    while (getline(file, line)) {
        istringstream iss(line);
        double num;
        int col = 0;

        while (iss >> num) {
            if (col < cols) {
                matrix[row][col] = num;
                ++col;
            }
        }

        if (col > 0) {
            ++row;
        }
    }

    return matrix;
}

// Функція для виведення матриці
void printMatrix(const vector<vector<double>> &matrix, const string &message, bool isInverse) {
    cout << message << endl;
    for (const auto &row : matrix) {
        for (double element : row) {
            if (isInverse) {
                cout << setw(14) << left << element;
            }
            else {
                cout << setw(7) << left << element;
            }
        }
        cout << endl;
    }
}

// Функція для коректної назви файлу
void makeFileNameCorrect(string &fileName) {
    if (fileName == MENU || fileName == USER_MANUAL) {
        fileName += "_copy";
    }
}

// Функції для зберігання матриці у файл
void saveMatrixToFile(const vector<vector<double>> &matrix, const string &fileName, string message, bool isInverse) {
    if (!(fileName == "")) {
        ofstream file(fileName, ios::app);
        if (!isInverse) {
            ofstream file(fileName);
        }
        if (file.is_open()) {
            file << message << endl;
            for (const auto &row : matrix) {
                for (double element : row) {
                    if (isInverse) {
                        file << setw(14) << left << element;
                    }
                    else {
                    file << setw(7) << left << element;
                    }
                }
                file << endl;
            }
            file.close();
        }
        else {
            throw runtime_error("Не вдалося відкрити файл " + fileName + " для запису.");
        }
    }
    else {
        throw runtime_error("Назву файлу не задано.");
    }
}

// Функція для перевірки, чи матриця квадратна
bool isSquareMatrix(const vector<vector<double>> &matrix) {
    return (matrix.size() == matrix[0].size());
}

// Функція для перевірки, чи визначник матриці дорівнює нулю
bool isDeterminantZero(double det) {
    return (det == 0);
}

// Функція для обчислення визначника матриці за теоремою Лапласа
double determinant(const vector<vector<double>> &matrix) {
    int n = matrix.size();
    if (!isSquareMatrix(matrix)) {
        throw runtime_error("Визначник заданої матриці не може бути знайдений, оскільки задана матриця не квадратна.");
    }

    double det;
    
    // Обробка різних випадків
    switch (n)
    {
    case 1:
        return matrix[0][0];
        break;
    case 2:
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        break;
    case 3:
        det = matrix[0][0] * matrix[1][1] * matrix[2][2] +
              matrix[0][1] * matrix[1][2] * matrix[2][0] +
              matrix[0][2] * matrix[1][0] * matrix[2][1] -
              matrix[0][2] * matrix[1][1] * matrix[2][0] -
              matrix[0][0] * matrix[1][2] * matrix[2][1] -
              matrix[0][1] * matrix[1][0] * matrix[2][2];
        return det;
        break;
    default:
        for (int j = 0; j < n; ++j) {
            vector<vector<double>> submatrix(n - 1, vector<double>(n - 1, 0.0));
            for (int i = 1; i < n; ++i) {
                for (int k = 0; k < n; ++k) {
                    if (k < j) {
                        submatrix[i - 1][k] = matrix[i][k];
                    }
                    else if (k > j) {
                        submatrix[i - 1][k - 1] = matrix[i][k];
                    }
                }
            }
            det += (j % 2 == 0 ? 1 : -1) * matrix[0][j] * determinant(submatrix);
        }
        return det;
        break;
    }
}

// Функція для зберігання визначника у файл
void saveDeterminantToFile(double det, const string &fileName) {
    if (!(fileName == "")) {
        ofstream file(fileName);
        if (file.is_open()) {
            file << "Визначник заданої матриці: " << det << endl;
            file.close();
        }
        else {
            throw runtime_error("Файлу " + fileName + " не існує.");
        }
    }
    else {
        throw runtime_error("Назву файлу не задано.");
    }
}

// Функція для обчислення зворотної матриці методом алгебраїчних доповнень
vector<vector<double>> inverseMatrix(const vector<vector<double>> &matrix) {
    int n = matrix.size();
    vector<vector<double>> invMatrix(n, vector<double>(n, 0.0));

    if (!isSquareMatrix(matrix)) {
        throw runtime_error("Зворотня матриця не може бути знайдена, оскільки задана матриця не квадратна.");
    }

    double det = determinant(matrix);
    if (isDeterminantZero(det)) {
        throw runtime_error("Зворотня матриця не може бути знайдена, оскільки визначник заданої матриці дорівнює нулю.");
    }

    // Обробка різних випадків 
    switch (n)
    {
    case 1:
        invMatrix[0][0] = 1 / det;
        return invMatrix;
        break;
    case 2:
        invMatrix[0][0] = matrix[1][1] / det;
        invMatrix[1][1] = matrix[0][0] / det;
        invMatrix[0][1] = matrix[0][1] / -det;
        invMatrix[1][0] = matrix[1][0] / -det;
        return invMatrix;
        break;
    default:
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                vector<vector<double>> minor(n - 1, vector<double>(n - 1, 0.0));
                for (int row = 0; row < n; ++row) {
                    for (int col = 0; col < n; ++col) {
                        if (row != i && col != j)
                        {
                            minor[row < i ? row : row - 1][col < j ? col : col - 1] = matrix[row][col];
                        }
                    }
                }
                invMatrix[j][i] = pow(-1, i + j) * determinant(minor) / det;
            }
        }
        return invMatrix;
        break;
    }
}

// Функція для запиту користувача про видалення файлу
bool askForFileDeletion(const string &fileName) {
    char answer;
    cout << "Ви впевнені, що хочете видалити файл " << fileName << "? (y/n): ";
    cin >> answer;
    if (tolower(answer) != 'y' && tolower(answer) != 'n') {
        cerr << RED << "Некоректний ввід. Будь ласка, введіть 'y' або 'n'." << RESET << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return askForFileDeletion(fileName);
    }
    return (tolower(answer) == 'y');
}

// Функція для видалення файлу
void deleteFile(const string &fileName) {
    if (fileName == MENU || fileName == USER_MANUAL) {
        throw runtime_error("Файл " + fileName + " не може бути видалений.");
    }
    ifstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Файлу " + fileName + " не існує.");
    }
    file.close();
    if (askForFileDeletion(fileName)) {
        if (remove(fileName.c_str()) == 0) {
            cout << GREEN << "Файл " << fileName << " успішно видалено." << RESET << endl;
        }
        else {
            throw runtime_error("Не вдалося видалити файл " + fileName + ".");
        }
    }
    else {
        cout << RED << "Видалення файлу " << fileName << " скасовано." << RESET << endl;
    }
}

// Функція для звільнення пам'яті
void freeMemory(vector<vector<double>> &matrix, vector<vector<double>> &invMatrix) {
    matrix.clear();
    invMatrix.clear();
}

int main() {
    int menuOption, rows, cols, mode, precisionValue;
    double det;
    bool flag = false;
    vector<vector<double>> matrix, invMatrix;
    string inputFileName, outputFileName, fileNameToDelete, fileNameToReadMatrix;

    srand(time(nullptr));

    clearConsole();

    try {
    loadFileContent(MENU);
    }
    catch (const exception &ex) {
        cerr << RED << "Помилка! " << ex.what() << RESET << endl;
        return 1;
    }


    while (menuOption != 10) {
        cout << "\nОберіть пункт меню: ";
        cin >> menuOption;

        switch (menuOption) {
        case 1:
            // Виведення інструкції користувача
            try {
                loadFileContent(USER_MANUAL);
            }
            catch (const exception &ex) {
                cerr << RED << "Помилка! " << ex.what() << RESET << endl;
                return 1;
            }
            break;
        case 2:
        modeInput:
            cout << "Оберіть спосіб введення матриці (1 - вручну, 2 - випадково, 3 - з файлу): ";
            cin >> mode;
            switch (mode) {
            case 1:
                // Введення матриці вручну
                setMatrixSize(rows, cols);
                matrix = inputMatrix(rows, cols);
                printMatrix(matrix, "Задана матриця:", false);
                break;
            case 2:
                // Генерація випадкової матриці
                setMatrixSize(rows, cols);
                matrix = generateRandomMatrix(rows, cols);
                printMatrix(matrix, "Задана матриця:", false);
                break;
            case 3:
                // Завантаження матриці з файлу
                cout << "Введіть назву файлу: ";
                cin >> fileNameToReadMatrix;
                try {
                    matrix = readMatrixFromFile(fileNameToReadMatrix);
                    printMatrix(matrix, "Задана матриця:", false);
                }
                catch (const exception &ex) {
                    cerr << RED << "Помилка! " << ex.what() << RESET << endl;
                    break;
                }
                break;
            default:
                cerr << RED << "Некоректний ввід. Спробуйте ще раз." << RESET << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto modeInput;
            }
            break;
        case 3:
            // Збережння вхідних даних у файл
            if (!matrix.empty()) {
                cout << "Введіть назву файлу для збереження вхідних даних: ";
                cin >> inputFileName;
                makeFileNameCorrect(inputFileName);
                try {
                    saveMatrixToFile(matrix, inputFileName, "Задана матриця:", false);
                    cout << GREEN << "Матриця успішно записана у файл " << inputFileName << "." << RESET << endl;
                }
                catch (const exception &ex) {
                    cerr << RED << "Помилка! " << ex.what() << RESET << endl;
                }
            }
            else {
                cerr << RED << "Спочатку необхідно ввести або згенерувати матрицю." << RESET << endl;
            }
            break;
        case 4:
            // Завантаження вхідних даних з файлу
            try {
                loadFileContent(inputFileName);
            }
            catch (const exception &ex) {
                cerr << RED << "Помилка! " << ex.what() << RESET << endl;
            }
            break;
        case 5:
            // Обчислення визначника матриці
            if (!matrix.empty()) {
                // Обчислення визначника
                try {
                    det = determinant(matrix);
                    cout << "Введіть точність, з якою будуть виводитись значення: ";
                    while (!(cin >> precisionValue) || precisionValue < 0 || precisionValue > 100) {
                        cerr << RED << "Некоректний ввід. Будь ласка, введіть ціле число від 0 до 100: " << RESET;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cout << fixed << setprecision(precisionValue);
                    cout << fixed << setprecision(precisionValue);
                    cout << "Визначник заданої матриці: " << det << endl;
                    flag = true;
                    }
                catch (const exception &ex) {
                        cerr << RED << "Помилка! " << ex.what() << RESET << endl;
                        break;
                    }
        
                // Обчислення зворотної матриці
                try {
                invMatrix = inverseMatrix(matrix);
                printMatrix(invMatrix, "Зворотня матриця:", true);
                }
                catch (const exception &ex) {
                cerr << RED << "Помилка! " << ex.what() << RESET << endl;
                }
            } else {
                cerr << RED << "Спочатку необхідно ввести або згенерувати матрицю." << RESET << endl;
                break;
            }
            break;
        case 6:
            // Збереження вихідних даних у файл
            if (!matrix.empty()) {
                if (flag) {
                    cout << "Введіть назву файлу для збереження вихідних даних: ";
                    cin >> outputFileName;
                    makeFileNameCorrect(outputFileName);

                    saveDeterminantToFile(det, outputFileName);
                    if (!isDeterminantZero(det))
                    {
                        try
                        {
                            saveMatrixToFile(invMatrix, outputFileName, "Обернена матриця:", true);
                        }
                        catch (const exception &ex)
                        {
                            cerr << RED << "Помилка! " << ex.what() << RESET << endl;
                        }
                    }
                    cout << GREEN "Вихідні дані успішно збережені у файл " << outputFileName << "." << RESET << endl;
                }
                else {
                    cerr << RED << "Спочатку необхідно обчислити визначник та обернену матрицю." << RESET << endl;
                }
            }
            else {
                cerr << RED "Спочатку необхідно ввести або згенерувати матрицю." << RESET << endl;
            }
            break;
        case 7:
            // Завантаження вихідних даних з файлу
            try {
                loadFileContent(outputFileName);
            }
            catch (const exception &ex) {
                cerr << RED << "Помилка! " << ex.what() << RESET << endl;
            }
            break;
        case 8:
            // Видалити файл
            cout << "Введіть назву файлу, який бажаєте видалити: ";
            cin >> fileNameToDelete;
            try {
                deleteFile(fileNameToDelete);
            }
            catch (const exception &ex) {
                cerr << RED << "Помилка! " << ex.what() << RESET << endl;
            }
            break;
        case 9:
            // Видалити вихідний файл
            clearConsole();
            break;
        case 10:
            // Вихід з програми
            cout << GREEN << "Вихід з програми успішно виконано." << RESET << endl;
            break;
        default:
            cerr << RED << "Некоректний ввід. Введіть число від 1 до 10." << RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Звільнення пам'яті
    freeMemory(matrix, invMatrix);

    return 0;
} 
