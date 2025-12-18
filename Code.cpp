#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Task {
public:
    string title;
    bool done;

    Task(string t, bool d = false) : title(t), done(d) {}
};

class TaskManager {
private:
    vector<Task> tasks;

public:
    void addTask(const string& title) {
        tasks.emplace_back(title);
    }

    void markDone(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].done = true;
        }
    }

    void showTasks() const {
        if (tasks.empty()) {
            cout << "Список порожній\n";
            return;
        }

        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". "
                 << tasks[i].title
                 << " [" << (tasks[i].done ? "✓" : " ") << "]\n";
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        for (const auto& task : tasks) {
            file << task.done << ";" << task.title << "\n";
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) return;

        tasks.clear();
        bool done;
        string title;

        while (file >> done) {
            file.ignore();
            getline(file, title);
            tasks.emplace_back(title, done);
        }
    }
};

int main() {
    TaskManager manager;
    manager.loadFromFile("tasks.txt");

    int choice;
    do {
        cout << "\n1. Додати завдання"
             << "\n2. Показати завдання"
             << "\n3. Відмітити виконаним"
             << "\n4. Вийти\n> ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title;
            cout << "Назва: ";
            getline(cin, title);
            manager.addTask(title);
        }
        else if (choice == 2) {
            manager.showTasks();
        }
        else if (choice == 3) {
            int index;
            cout << "Номер завдання: ";
            cin >> index;
            manager.markDone(index - 1);
        }

    } while (choice != 4);

    manager.saveToFile("tasks.txt");
    return 0;
}
