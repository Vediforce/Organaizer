#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct OrganizerEntry {
    string title;
    string description;
    string date;
};

class Organizer {
private:
    vector<OrganizerEntry> entries;
    string filename;

public:
    Organizer(const string& file) : filename(file) {
        loadEntries();
    }

    void clearAllEntries() {
        entries.clear();
        saveEntries();
        cout << "Все записи успешно удалены.\n";
    }

    void addEntry(const string& title, const string& description, const string& date) {
        OrganizerEntry entry;
        entry.title = title;
        entry.description = description;
        entry.date = date;

        entries.push_back(entry);
        saveEntries();
        cout << "Запись успешно добавлена.\n";
    }

    void removeEntry(int index) {
        if (isValidIndex(index)) {
            entries.erase(entries.begin() + index);
            saveEntries();
            cout << "Запись успешно удалена.\n";
        } else {
            cout << "Недопустимый индекс. Запись не удалена.\n";
        }
    }

    void editEntry(int index, const string& newTitle, const string& newDescription, const string& newDate) {
        if (isValidIndex(index)) {
            entries[index].title = newTitle;
            entries[index].description = newDescription;
            entries[index].date = newDate;
            saveEntries();
            cout << "Запись успешно изменена.\n";
        } else {
            cout << "Недопустимый индекс. Запись не изменена.\n";
        }
    }

    void displayEntries() const {
        if (entries.empty()) {
            cout << "Нет записей в органайзере.\n";
        } else {
            for (size_t i = 0; i < entries.size(); ++i) {
                cout << "Индекс: " << i << ", Заголовок: " << entries[i].title << ", Описание: " << entries[i].description << ", Дата: " << entries[i].date << "\n";
            }
        }
    }

    bool isValidIndex(int index) const {
        return index >= 0 && index < entries.size();
    }

    void searchEntries(const string& query) const {
        if (entries.empty()) {
            cout << "Нет записей в органайзере.\n";
        } else {
            bool found = false;
            for (size_t i = 0; i < entries.size(); ++i) {
                if (entries[i].title.find(query) != string::npos ||
                    entries[i].description.find(query) != string::npos ||
                    entries[i].date.find(query) != string::npos) {
                    found = true;
                    cout << "Индекс: " << i << ", Заголовок: " << entries[i].title << ", Описание: " << entries[i].description << ", Дата: " << entries[i].date << "\n";
                }
            }
            if (!found) {
                cout << "По вашему запросу ничего не найдено.\n";
            }
        }
    }

    void exportEntries(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& entry : entries) {
                file << entry.title << "\n" << entry.description << "\n" << entry.date << "\n";
            }
            file.close();
            cout << "Записи успешно экспортированы в файл " << filename << ".\n";
        } else {
            cout << "Ошибка при экспорте записей.\n";
        }
    }

private:
    void loadEntries() {
        ifstream file(filename);
        if (file.is_open()) {
            while (!file.eof()) {
                OrganizerEntry entry;
                getline(file, entry.title);
                getline(file, entry.description);
                getline(file, entry.date);
                if (!entry.title.empty()) {
                    entries.push_back(entry);
                }
            }
            file.close();
        }
    }

    void saveEntries() const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& entry : entries) {
                file << entry.title << "\n" << entry.description << "\n" << entry.date << "\n";
            }
            file.close();
        }
    }
};

int main() {
    Organizer organizer("organizer_data.txt");

    int choice;
    do {

        cout << "\n=====[ Меню органайзера ]====\n";
        cout << "1. Добавить запись\n";
        cout << "2. Удалить запись\n";
        cout << "3. Редактировать запись\n";
        cout << "4. Показать записи\n";
        cout << "5. Поиск записей\n";
        cout << "6. Экспорт записей\n";
        cout << "999. Очистить все записи\n";
        cout << "0. Выход\n";
        cout << "===Ввод=> ";

        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore();
                string title, description, date;
                cout << "Введите заголовок: ";
                getline(cin, title);
                cout << "Введите описание: ";
                getline(cin, description);
                cout << "Введите дату (например, ДД/ММ/ГГГГ): ";
                getline(cin, date);
                organizer.addEntry(title, description, date);
                break;
            }
            case 2: {
                int index;
                cout << "Введите индекс для удаления: ";
                cin >> index;
                if (organizer.isValidIndex(index)) {
                    organizer.removeEntry(index);
                } else {
                    cout << "Недопустимый индекс. Запись не удалена.\n";
                }
                break;
            }
            case 3: {
                int index;
                cout << "Введите индекс для редактирования: ";
                cin >> index;
                if (organizer.isValidIndex(index)) {
                    cin.ignore();
                    string newTitle, newDescription, newDate;
                    cout << "Введите новый заголовок: ";
                    getline(cin, newTitle);
                    cout << "Введите новое описание: ";
                    getline(cin, newDescription);
                    cout << "Введите новую дату (например, ДД/ММ/ГГГГ): ";
                    getline(cin, newDate);
                    organizer.editEntry(index, newTitle, newDescription, newDate);
                } else {
                    cout << "Недопустимый индекс. Запись не изменена.\n";
                }
                break;
            }
            case 4:
                organizer.displayEntries();
                break;
            case 5: {
                cin.ignore();
                string query;
                cout << "Введите поисковый запрос: ";
                getline(cin, query);
                organizer.searchEntries(query);
                break;
            }
            case 6: {
                cin.ignore();
                string filename;
                cout << "Введите имя файла для экспорта: ";
                getline(cin, filename);
                organizer.exportEntries(filename);
                break;
            }
            case 999:
                organizer.clearAllEntries();
                break;
            case 0:
                cout << "Выход...\n";
                break;
            default:
                cout << "Недопустимый выбор. Пожалуйста, повторите попытку.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}