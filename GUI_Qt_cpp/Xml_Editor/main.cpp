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
        if (QString(argv[i]) == "--cli") {
            cmdMode = true;
            qDebug() << "Command-line mode enabled.";
            break;
        } else if (QString(argv[i]) == "--gui") {
            guiMode = true;
            qDebug() << "GUI mode enabled.";
            break;
        }
    }

    if (cmdMode) {
        // Command-Line Mode (no QApplication needed)
        std::cout << "=====================================" << std::endl;
        std::cout << "      XML Editor: CMD Mode Active   "<<argc << std::endl;
        std::cout << "=====================================" << std::endl;
        if (argc < 3) {
            std::cerr << "Usage: xml_editor <command> <options>" << std::endl;
            return 1;
        }

        std::string command = argv[2];
        std::string inputFile;
        std::string outputFile;
        bool fix = false;
        std::vector<int> ids;
        int userId;
        std::string word;
        std::string topic;

        for (int i = 3; i < argc; ++i) {
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

        // Your various commands processing logic here
        if (command == "verify") {
            std::cout << "Starting tag validation..." << std::endl;
            isValid(inputFile); // Assuming isValid is defined elsewhere

            std::cout << "Unclosed tags:" << std::endl;
            while (!unClosed.empty()) {
                std::cout << unClosed.top().first << " " <<"Line Number "<<unClosed.top().second << std::endl;
                unClosed.pop();
            }

            std::cout << "Unopened tags:" << std::endl;
            for (const auto& tag : unOpened) {
                std::cout << tag.second << " " <<"Line Number "<< tag.first << std::endl;
            }
        } else if (command == "format") {
            std::cout << "Starting tag formatting..." << std::endl;
            format_XML(inputFile, outputFile);
        } else if (command == "json") {
            std::cout << "Starting tag convertion to json..." << std::endl;
            Xml_to_Json(inputFile, outputFile);
        } else if (command == "mini") {
             std::cout << "Starting tag Minifing..." << std::endl;
            std::ifstream input_file(inputFile);
            std::ofstream output_file(outputFile);
            Minifyingg(input_file, output_file);
        } else if (command == "compress") {
             std::cout << "Starting Compressing..." << std::endl;
            compressing(inputFile, outputFile);
        } else if (command == "decompress") {
             std::cout << "Starting deCompressing..." << std::endl;
            decompressing(inputFile, outputFile);
        } else if (command == "draw") {
             std::cout << "Starting Drawing graph..." << std::endl;
            bool done;
            Xml_to_Graph(inputFile, outputFile,done);
        } else if (command == "most_active") {
             std::cout << "Starting getting the most active user..." << std::endl;
            most_active(inputFile);
        } else if (command == "most_influencer") {
            std::cout << "Starting getting the most influncer..." << std::endl;
            Most_influencers(inputFile);
        } else if (command == "mutual") {
            std::cout << "Starting getting the mutual..." << std::endl;

            // Call the mutual function by extracting elements from the vector
            std::list<std::string> values = mutual(inputFile, ids[0], ids[1], ids[2]);

            if (values.empty()) {
                std::cout << "No mutual values found for the given IDs." << std::endl;
            } else {
                // Output the results
                std::cout << "Mutual values for the given IDs:\n";
                for (const std::string& value : values) {
                    std::cout << value << std::endl;
                }
            }

        } else if (command == "suggest") {
            std::list<std::string> values = suggested_users(inputFile, userId);

            if (values.empty()) {
                std::cout << "No suggested users found for the given ID." << std::endl;
            } else {
                std::cout << "Suggested users for the given ID:\n";
                for (const std::string& value : values) {
                    std::cout << value << std::endl;
                }
            }
        } else if (command == "search" && !word.empty()) {
            wordSearch(inputFile, word);
        } else if (command == "search" && !topic.empty()) {
            topicSearch(inputFile, topic);
        } else {
            std::cerr << "Unknown command or invalid options." << std::endl;
            return 1;
        }
        return 0;

    } else if (guiMode) {
        // GUI Mode
        QApplication app(argc, argv);  // Initialize the Qt application
        MainWindow window;  // Create the MainWindow object
        window.resize(1000, 600);  // Set the window size
        window.show();  // Display the window
        return app.exec();  // Enter the event loop for GUI mode

    } else {
        std::cerr << "No valid mode specified. Use --cli or --gui." << std::endl;
        return 1;
    }
}
