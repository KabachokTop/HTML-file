#include <iostream>
#include <fstream>
#include <string>
#include <clocale>

using namespace std;

bool validateHTML(const string& filePath) {
    ifstream file(filePath);

    if (!file.is_open()) {
        cout << "Помилка: Не вдалося відкрити файл за шляхом: " << filePath << endl;
        return false;
    }

    char ch;
    int openBrackets = 0;
    int lineNumber = 1;

    while (file.get(ch)) {
        if (ch == '\n') {
            lineNumber++;
        }
        else if (ch == '<') {
            openBrackets++;
            if (openBrackets > 1) {
                cout << "Помилка (рядок " << lineNumber
                    << "): знайдено '<' без закриття попереднього '>'." << endl;
                file.close();
                return false;
            }
        }
        else if (ch == '>') {
            openBrackets--;
            if (openBrackets < 0) {
                cout << "Помилка (рядок " << lineNumber
                    << "): знайдено незакриту дужку '>'." << endl;
                file.close();
                return false;
            }
        }
    }

    file.close();

    if (openBrackets != 0) {
        cout << "Помилка: не всі дужки '<' закриті символом '>'." << endl;
        return false;
    }

    return true;
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    string filePath;

    cout << "=== Валідатор HTML-файлів ===" << endl;
    cout << "Введіть повний шлях до файлу (або перетягніть файл сюди): ";

    getline(cin, filePath);

    if (!filePath.empty() && (filePath.front() == '"' || filePath.front() == '\'')) {
        filePath.erase(0, 1);
    }
    if (!filePath.empty() && (filePath.back() == '"' || filePath.back() == '\'')) {
        filePath.pop_back();
    }

    if (validateHTML(filePath)) {
        cout << "\n[УСПІХ] Файл є валідним!" << endl;
    }
    else {
        cout << "\n[ПОМИЛКА] Файл не пройшов перевірку." << endl;
    }

    return 0;
}