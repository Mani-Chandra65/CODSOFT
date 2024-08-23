#include <iostream>
#include <string>
using namespace std;
const int MAX_TASKS = 100;

class Task {
private:
    string description;
    bool completed;

public:
    
    Task(string desc = "") : description(desc), completed(false) {}

    void markCompleted() {
        completed = true;
    }

    bool isCompleted() const {
        return completed;
    }

    string getDescription() const {
        return description;
    }

    void printTask() const {
        cout << (completed ? "[x] " : "[ ] ") << description << endl;
    }
};

class ToDoList {
private:
    Task tasks[MAX_TASKS];
    int taskCount;

public:
    ToDoList() : taskCount(0) {}

    void addTask(const string & description) {
        if (taskCount < MAX_TASKS) {
            tasks[taskCount++] = Task(description);
            cout << "Task added: " << description << endl;
        } else {
            cout << "Task list is full!" << endl;
        }
    }

    void completeTask(int index) {
        if (index >= 0 && index < taskCount) {
            tasks[index].markCompleted();
            cout << "Task " << index + 1 << " marked as completed." << endl;
        } else {
            cout << "Invalid task index!" << endl;
        }
    }

    void printTasks() const {
        if (taskCount == 0) {
            cout << "No tasks in the list." << endl;
        } else {
            for (int i = 0; i < taskCount; ++i) {
                cout << i + 1 << ". ";
                tasks[i].printTask();
            }
        }
    }
};

int main() {
    ToDoList myList;
    int choice;
    string description;
    int taskNumber;

    do {
        cout << "\n1. Add Task\n2. Complete Task\n3. Show Tasks\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cin.ignore();
                cout << "Enter task description: ";
                getline(cin, description);
                myList.addTask(description);
                break;

            case 2:
                cout << "Enter task number to complete: ";
                cin >> taskNumber;
                myList.completeTask(taskNumber - 1);
                break;

            case 3:
                myList.printTasks();
                break;

            case 4:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
