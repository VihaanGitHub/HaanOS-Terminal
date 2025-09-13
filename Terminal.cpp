#include <iostream>  
#include <string>  
#include <map>  
#include <set>  
using namespace std;  
  
int main() {  
    string command;  
    static set<string> createdFiles;           // store file/folder names  
    static map<string, string> fileContents;   // store file content for .txt/.py files  
  
    cout << "                    HaanOS Terminal\n";  
    cout << "Type 'exit' to close the terminal.\n\n";  
  
    while (true) {  
        cout << "haanOS> ";  
        getline(cin, command);  
  
        bool isSudo = false; // must be before the if/else chain  
  
        // --- Exit HaanOS ---  
        if (command == "exit") {  
            cout << "Shutting down HaanOS...\n";  
            break;  
        }  
  
        // --- Enter Python mode ---  
        else if (command == "python") {  
            cout << "Python version 3.13.7. Type 'exit py' to exit Python.\n";  
            while (true) {  
                cout << ">>> ";  
                getline(cin, command);  
  
                if (command == "exit py") {  
                    cout << "Exiting Python...\n";  
                    break;  
                }  
  
                if (command.rfind("print(", 0) == 0 && command.back() == ')') {  
                    string content = command.substr(6, command.size() - 7);  
                    if (!content.empty() && ((content.front() == '"' && content.back() == '"') ||   
                                             (content.front() == '\'' && content.back() == '\''))) {  
                        content = content.substr(1, content.size() - 2);  
                    }  
                    cout << content << "\n";  
                } else {  
                    cout << "Error: Only print() is supported in this Python mode.\n";  
                }  
            }  
        }  
  
        // --- Enter Ubuntu Linux mode ---  
        else if (command == "hsl -u linux") {  
            cout << "Haan subsystem for Ubuntu Linux. NOTE: Minimal installation. Type 'unregister linux' to exit.\n";  
            while (true) {  
                cout << "Ubuntu linux> ";  
                getline(cin, command);  
  
                if (command == "unregister linux") {  
                    cout << "Exiting Linux...\n";  
                    break;  
                } else {  
                    cout << "Command not recognized in Linux mode.\n";  
                }  
            }  
        }  
  
        // --- Handle sudo rm ---  
        else if (command.rfind("sudo rm", 0) == 0) {  
            isSudo = true;  
            command = command.substr(5);  
            if (!command.empty() && command[0] == ' ') command = command.substr(1);  
        }  
  
        // --- Handle rm ---  
        else if (command.rfind("rm", 0) == 0) {  
            string after = command.substr(2);  
            if (!after.empty() && after[0] == ' ') after = after.substr(1);  
  
            if ((after == "user" || after == "system" || after == "drivers") && !isSudo) {  
                cout << "Action restricted, requires admin privileges\n";  
            } else {  
                cout << "Successfully deleted " << after << "!\n";  
                createdFiles.erase(after);  
                fileContents.erase(after);  
            }  
        }  
  
        // --- Handle touch with optional content ---  
        else if (command.rfind("touch", 0) == 0) {  
            string after = command.substr(5);  
            if (!after.empty() && after[0] == ' ') after = after.substr(1);  
  
            string filename;  
            string content = "";  
            size_t contentPos = after.find(" content ");  
            if (contentPos != string::npos) {  
                filename = after.substr(0, contentPos);  
                content = after.substr(contentPos + 9);  
                if (!content.empty() && content.front() == '"' && content.back() == '"' && content.size() > 1) {  
                    content = content.substr(1, content.size() - 2);  
                }  
            } else {  
                filename = after;  
            }  
  
            if (!filename.empty() && filename.front() == '"' && filename.back() == '"' && filename.size() > 1) {  
                filename = filename.substr(1, filename.size() - 2);  
            }  
  
            if (filename.empty()) {  
                cout << "Error: no file name provided.\n";  
            } else if (filename == "folder") {  
                cout << "Folder created successfully!\n";  
                createdFiles.insert("folder");  
            } else {  
                cout << "File created successfully!\n";  
                createdFiles.insert(filename);  
                if ((filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt") ||  
                    (filename.size() > 3 && filename.substr(filename.size() - 3) == ".py")) {  
                    fileContents[filename] = content;  
                }  
            }  
        }  
  
        // --- Handle echo ---  
        else if (command.rfind("echo", 0) == 0) {  
            string after = command.substr(4);  
            if (!after.empty() && after[0] == ' ') after = after.substr(1);  
            if (!after.empty() && after.front() == '"' && after.back() == '"' && after.size() > 1) {  
                after = after.substr(1, after.size() - 2);  
            }  
            cout << after << "\n";  
        }  
  
        // --- Handle find ---  
        else if (command.rfind("find", 0) == 0) {  
            string after = command.substr(4);  
            if (!after.empty() && after[0] == ' ') after = after.substr(1);  
  
            if (after == "system" || after == "user" || after == "drivers") {  
                cout << "Folder does exist on your computer.\n";  
            } else if (createdFiles.count(after)) {  
                cout << "File/Folder exists on your computer.\n";  
            } else {  
                cout << "File/Folder not found.\n";  
            }  
        }  
  
        // --- Execute .py file if typed directly ---  
        else if (createdFiles.count(command) && command.size() > 3 && command.substr(command.size() - 3) == ".py") {  
            string pyContent = fileContents[command];  
            if (pyContent.rfind("print(", 0) == 0 && pyContent.back() == ')') {  
                string content = pyContent.substr(6, pyContent.size() - 7);  
                if (!content.empty() && ((content.front() == '"' && content.back() == '"') ||   
                                         (content.front() == '\'' && content.back() == '\''))) {  
                    content = content.substr(1, content.size() - 2);  
                }  
                cout << content << "\n";  
            } else {  
                cout << "Error: Only print() is supported in .py files.\n";  
            }  
        }  
  
        // --- Unknown command ---  
        else {  
            cout << "Unknown command: " << command << "\n";  
        }  
    }  
  
    return 0;  
}
