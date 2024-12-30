#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

int main(int argc, char *argv[]) {
    // Flags to recognize command-line and GUI modes
    bool cmdMode = false;
    bool guiMode = false;

    // Check if "--cmd" or "--gui" argument is passed to the program
    for (int i = 1; i < argc; ++i) {
        if (QString(argv[i]) == "--cmd") {
            cmdMode = true;
            break;
        } else if (QString(argv[i]) == "--gui") {
            guiMode = true;
            break;
        }
    }

    if (cmdMode) {
        // Command-Line Mode
        QCoreApplication app(argc, argv); // Initialize Qt's core application
        qDebug() << "Running in CMD mode...";

        if (argc < 3) {
            std::cerr << "Usage: xml_editor <command> <options>" << std::endl;
            return 1;
        }

        std::string command = argv[1];
        std::string inputFile;
        std::string outputFile;
        bool fix = false;
        std::vector<int> ids;
        int userId;
        std::string word;
        std::string topic;

        // Parsing command-line arguments
        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-i" && i + 1 < argc) {
                inputFile = argv[++i];
            } else if (arg == "-o" && i + 1 < argc) {
                outputFile = argv[++i];
            } else if (arg == "-f") {
                fix = true;
            } else if (arg == "-ids" && i + 1 < argc) {
                std::string idsString = argv[++i];
                size_t pos = 0;
                while ((pos = idsString.find(",")) != std::string::npos) {
                    ids.push_back(std::stoi(idsString.substr(0, pos)));
                    idsString.erase(0, pos + 1);
                }
                if (!idsString.empty()) {
                    ids.push_back(std::stoi(idsString));
                }
            } else if (arg == "-id" && i + 1 < argc) {
                userId = std::stoi(argv[++i]);
            } else if (arg == "-w" && i + 1 < argc) {
                word = argv[++i];
            } else if (arg == "-t" && i + 1 < argc) {
                topic = argv[++i];
            }
        }

        // Handling specific commands
        if (command == "verify") {
            std::cout << "Starting tag validation..." << std::endl;
            isValid(inputFile); // Assuming isValid is defined elsewhere
        }
        // Handle other commands here...

        return app.exec();  // Enter the event loop for CMD mode (though it's uncommon to use GUI components in this mode)
    } else if (guiMode) {
        // GUI Mode
        QApplication app(argc, argv);  // Initialize the Qt application
        MainWindow window;  // Create the MainWindow object
        window.resize(1000, 600);  // Set the window size
        window.show();  // Display the window
        return app.exec();  // Enter the event loop for GUI mode
    } else {
        std::cerr << "No valid mode specified. Use --cmd or --gui." << std::endl;
        return 1;
    }
}

