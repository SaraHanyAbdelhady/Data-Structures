#include "mainwindow.h"
#include "ui_mainwindow.h"
/*boso 3lshan nnady elfunctions
1. lw hya void wana 3ayza adisplay elcout
    std::ostringstream oss;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());

    // Call the function
    isValid(filePath);

    // Restore the original cout buffer
    std::cout.rdbuf(oldCoutBuffer);

    // Get the output and append it to QTextEdit
    QString output = QString::fromStdString(oss.str());
    //outputTextBox->setPlainText(output);
da byredirect el cout 3nd el outputtext box
2. lw bya5od file wyrag3 file
    outputTextBox->clear();
    string filePath = saveToXml();;
    string outputPath = "output.xml";
    QFile file(outputPath.c_str());

    // Read the file content
    QString fileContent;
    QTextStream in(&file);
    fileContent = in.readAll();

    if(fileContent == "0") {
        outputTextBox->setPlainText("The XML file is valid and no error correction is needed");
        file.close();
    }
    else
    {

    file.resize(0); // Clear the file before writing
    QTextStream out(&file);
    out << fileContent;
    file.close();
    outputTextBox->setPlainText(fileContent);
    }
*/
bool empt = false;

MainWindow::MainWindow(QWidget *parent) {
    // Main container widget
    container = new QWidget();
    mainLayout = new QHBoxLayout();

    container->setStyleSheet(R"(
    QLabel {
        font-size: 15px;
        font-weight: bold;
        color: #2C3E50;
        font-family: "Arial";
    }
    QTextEdit {
        border: 1px solid #BDC3C7;
        border-radius: 8px;
        padding: 8px;
        font-family: "Courier New";
        font-size: 14px;
        background-color: #FAFAFA;
        color: #2C3E50;
        line-height: 1.6;
    }
    QTextEdit[readOnly="true"] {
        background-color: #F4F6F7; /* Light background for read-only output */
        border-left: 5px solid #2980B9; /* Accent border for read-only text */
        tab-stop-distance: 32px; /* Tab width equivalent to 4 spaces */
    }
    QPushButton {
        background-color: #3498DB;
        color: white;
        border: none;
        padding: 10px 15px;
        border-radius: 8px;
        font-size: 14px;
        font-weight: bold;
        box-shadow: 2px 2px 5px rgba(0, 0, 0, 0.2);
        transition: background-color 0.3s, transform 0.2s;
    }
    QPushButton:hover {
        background-color: #2980B9;
        transform: scale(1.05);
    }
    QPushButton:pressed {
        background-color: #1C6EA4;
        transform: scale(0.95);
    }
)");


    // Input Section
    inputLabel = new QLabel("Input");
    inputTextBox = new QTextEdit();
    inputTextBox->setPlaceholderText("Place your Input Here...");
    loadFileButton = new QPushButton("Load File");
    connect(loadFileButton, &QPushButton::clicked, this, &MainWindow::loadFile);

    inputLayout = new QVBoxLayout();
    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputTextBox);
    inputLayout->addWidget(loadFileButton);

    // Control Section
    controlLayout = new QVBoxLayout();

    valid_button = new QPushButton("Check XML Consistency");
    connect(valid_button, &QPushButton::clicked, this, &MainWindow::valid);

    correct = new QPushButton("Correct to be Valid");
    connect(correct, &QPushButton::clicked, this, &MainWindow::corr);

    prettify = new QPushButton("Prettify XML");
    connect(prettify, &QPushButton::clicked, this, &MainWindow::pret);

    json = new QPushButton("XML to JSON");
    connect(json, &QPushButton::clicked, this, &MainWindow::xml2json);

    minify = new QPushButton("Minify XML");
    connect(minify, &QPushButton::clicked, this, &MainWindow::mini);

    compress = new QPushButton("Compress XML");
    connect(compress, &QPushButton::clicked, this, &MainWindow::comp);

    decompress = new QPushButton("Decompress XML");
    connect(decompress, &QPushButton::clicked, this, &MainWindow::decomp);

    draw = new QPushButton("XML to Graph");
    connect(draw, &QPushButton::clicked, this, &MainWindow::drawGraph);

    // Adding buttons to layout
    controlLayout->addWidget(valid_button);
    controlLayout->addWidget(correct);
    controlLayout->addWidget(prettify);
    controlLayout->addWidget(json);
    controlLayout->addWidget(minify);
    controlLayout->addWidget(compress);
    controlLayout->addWidget(decompress);
    controlLayout->addWidget(draw);

    // Dropdown menus
    networkAnalysis = new QComboBox();
    networkAnalysis->setPlaceholderText("Network Analysis");
    networkAnalysis->addItems({"Most Active", "Most Influencer", "Mutual Users", "Suggested Users"});
    connect(networkAnalysis, &QComboBox::currentIndexChanged, this, &MainWindow::networkanalysisAction);

    searchWord = new QLineEdit();
    searchWord->setPlaceholderText("Enter Search Word Here");

    search = new QComboBox();
    search->setPlaceholderText("Search");
    search->addItems({"With Word", "With Topic"});
    connect(search, &QComboBox::currentIndexChanged, this, &MainWindow::searchAction);

    searchLayout = new QVBoxLayout();
    searchLayout->addWidget(searchWord);
    searchLayout->addWidget(search);

    controlLayout->addWidget(networkAnalysis);
    controlLayout->addLayout(searchLayout);

    // Output Section
    outputLabel = new QLabel("Output");
    outputTextBox = new QTextEdit();
    outputTextBox->setReadOnly(true);
    outputTextBox->setPlaceholderText("Output Will Appear Here...");
    QFontMetrics metrics(outputTextBox->font());
    int tabWidth = 4 * metrics.horizontalAdvance(' '); // Calculate width for 4 spaces
    outputTextBox->setTabStopDistance(tabWidth);
    saveFileButton = new QPushButton("Save File");
    connect(saveFileButton, &QPushButton::clicked, this, &MainWindow::saveFile);

    outputLayout = new QVBoxLayout();
    outputLayout->addWidget(outputLabel);
    outputLayout->addWidget(outputTextBox);
    outputLayout->addWidget(saveFileButton);

    // Combine all layouts
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(controlLayout);
    mainLayout->addLayout(outputLayout);

    container->setLayout(mainLayout);
    setCentralWidget(container);
    setWindowTitle("MM STASH");
}

void MainWindow::loadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.xml);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString numberedText;
            int lineNumber = 1;

            while (!in.atEnd()) {
                QString line = in.readLine();
                numberedText += QString::number(lineNumber) + ": " + line + "\n";
                ++lineNumber;
            }

            inputTextBox->setPlainText(numberedText);
            file.close();
        }
    }
}

void MainWindow::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << outputTextBox->toPlainText();
            file.close();
        }
    }
}

string MainWindow::saveToXml() {
    QString inputText = inputTextBox->toPlainText();
    if (inputText.isEmpty()) {
        outputTextBox->setTextColor(QColor::fromRgb(255, 0, 0));
        outputTextBox->append("Input is EMPTY, Please enter an input...");
        outputTextBox->setTextColor(QColor::fromRgb(0, 0, 0));
        empt = true;
        return "";
    }

    // Remove line numbers
    QStringList lines = inputText.split('\n');
    QString unnumberedText;
    for (const QString &line : lines) {
        int x = line.toStdString().find(":");
        string trimmedLine = line.toStdString();
        if(x>-1 && x<line.toStdString().length()) trimmedLine  = line.toStdString().substr(x+1);
        //QString trimmedLine = line.section(':', 1).trimmed(); // Remove the part before and including ':'
        if (!trimmedLine.empty()) {

            unnumberedText += QString::fromStdString(trimmedLine)  + '\n';
        }
    }

    // Specify the file path
    QString filePath = "input.xml";

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Create a QTextStream to write text to the file
        QTextStream out(&file);
        out << unnumberedText;

        // Close the file
        file.close();
    }

    return filePath.toStdString();
}


void MainWindow::networkanalysisAction() {
    QComboBox *dropdown = qobject_cast<QComboBox *>(sender());
    string filePath = saveToXml();
    outputTextBox->clear();

    // Redirect cout to capture output
    std::ostringstream oss;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());

    if (dropdown->currentIndex() == 0) {
        // Call "Most Active"
        most_active(filePath);
        std::cout.rdbuf(oldCoutBuffer);  // Restore the original cout buffer

        // Get the output and append it to QTextEdit
        QString output = QString::fromStdString(oss.str());
        outputTextBox->setPlainText("Most Active Users:\n" + output);
    }
    else if (dropdown->currentIndex() == 1) {
        // Call "Most Influencer"
        Most_influencers(filePath);
        std::cout.rdbuf(oldCoutBuffer);  // Restore the original cout buffer

        // Get the output and append it to QTextEdit
        QString output = QString::fromStdString(oss.str());
        outputTextBox->setPlainText("Most Influencer Users:\n" + output);
    }
    else if (dropdown->currentIndex() == 2) {
        // Call "Mutual Users"
        list<string> mutualUsers = mutual(filePath, 1, 2, 3);  // Example user IDs

        // Convert list<string> to QString
        QString output;
        if (mutualUsers.empty()) {
            output = "No Mutual Users found.";
        } else {
            output = "Mutual Users:\n";
            for (const auto& userName : mutualUsers) {
                output += QString::fromStdString(userName) + "\n";
            }
        }

        outputTextBox->setPlainText(output);
    }
    else if (dropdown->currentIndex() == 3) {
        // Call "Suggested Users"
        list<string> suggestedUsers = suggested_users(filePath, 1);  // Example user ID

        // Convert list<string> to QString
        QString output;
        if (suggestedUsers.empty()) {
            output = "No Suggested Users found.";
        } else {
            output = "Suggested Users:\n";
            for (const auto& userName : suggestedUsers) {
                output += QString::fromStdString(userName) + "\n";
            }
        }

        outputTextBox->setPlainText(output);
    }

    // Restore the original cout buffer
    std::cout.rdbuf(oldCoutBuffer);
}

void MainWindow::searchAction() {
    QComboBox *dropdown = qobject_cast<QComboBox *>(sender());
    outputTextBox->clear();

    // Get the text from the input field (assuming searchWord is a QLineEdit)
    QString searchText = searchWord->text();  // This retrieves the text from the QLineEdit

    string filePath = saveToXml();
    std::ostringstream oss;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());

    if (dropdown->currentIndex() == 0) {
        wordSearch(filePath, searchText.toStdString());  // Pass the text as string
        std::cout.rdbuf(oldCoutBuffer);  // Restore the original cout buffer

        // Get the output and append it to QTextEdit
        QString output = QString::fromStdString(oss.str());
        outputTextBox->setPlainText( output);

    } else if (dropdown->currentIndex() == 1) {
        topicSearch(filePath, searchText.toStdString());  // Pass the text as string
        std::cout.rdbuf(oldCoutBuffer);  // Restore the original cout buffer

        // Get the output and append it to QTextEdit
        QString output = QString::fromStdString(oss.str());
        outputTextBox->setPlainText( output);
    }
}

void MainWindow::drawGraph() {
    outputTextBox->clear();
    string filePath = saveToXml();
    QString imgPath1 = "graph.jpg";
    string imgPath = "graph.jpg";
    bool done = false;
    std::ostringstream oss;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());

    Xml_to_Graph(filePath,imgPath,done);

    std::cout.rdbuf(oldCoutBuffer);  // Restore the original cout buffer

    // Get the output and append it to QTextEdit
    QString output = QString::fromStdString(oss.str());

    QImage image(imgPath1);
    if(image.isNull() || image.width() == 0 || image.height() == 0)
    {
        outputTextBox->setPlainText("The XML file is valid and no error correction is needed");
    }
    else if (done) outputTextBox->append("<img src='"+imgPath1+"' width='370' height='500' />");
    else{
        outputTextBox->setPlainText( output);
    }
}

void MainWindow::decomp() {
    outputTextBox->clear();

    // Input compressed file path and output decompressed file path
    std::string inputPath = "output.comp"; // Assuming this is the compressed file
    std::string outputPath = "decompressed.xml";

    // Call the decompressing function
    decompressing(inputPath, outputPath);

    // Open the output file using QFile
    QFile file(outputPath.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        outputTextBox->setPlainText("Error: Unable to open the decompressed file.");
        return;
    }

    // Read the content of the file
    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    // Display the decompressed content
    outputTextBox->setPlainText("Decompression Completed\n" + fileContent);
}


void MainWindow::comp() {
    outputTextBox->clear();

    // Save the XML file and get the file path
    std::string filePath = saveToXml();
    std::string outputPath = "output.comp";

    // Call the compressing function
    compressing(filePath, outputPath);

    // Open the output file using QFile
    QFile file(outputPath.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        outputTextBox->setPlainText("Error: Unable to open the output file.");
        return;
    }

    // Read the content of the file
    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    // Check the content of the output file
    if (fileContent.trimmed() == "0") {
        outputTextBox->setPlainText("The XML file is valid and no error correction is needed");
    } else {
        outputTextBox->setPlainText("Compression Completed\n" + fileContent);
    }
}

void MainWindow::mini() {
    outputTextBox->clear();

    // Save the XML file and get the file path
    std::string filePath = saveToXml();
    std::string outputPath = "output.xml";

    // Open input and output file streams
    std::ifstream input_file(filePath);
    std::ofstream output_file(outputPath);

    if (!input_file.is_open() || !output_file.is_open()) {
        outputTextBox->setPlainText("Error: Unable to open input or output file.");
        return;
    }

    // Minify the file
    Minifyingg(input_file, output_file);

    // Close the file streams after use
    input_file.close();
    output_file.close();

    // Open the output file for reading
    QFile file(outputPath.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        outputTextBox->setPlainText("Error: Unable to read the output file.");
        return;
    }

    // Read the content of the file
    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    if (fileContent.trimmed() == "0") {
        outputTextBox->setPlainText("The XML file is valid and no error correction is needed");
    } else {
        outputTextBox->setPlainText("Minifying Done\n" + fileContent);
    }
}



void MainWindow::xml2json() {
    outputTextBox->clear();
    string filePath = saveToXml();;
    string outputPath = "output_json.json";
    ifstream input(filePath);
    Xml_to_Json(filePath, outputPath);

    QFile file(outputPath.c_str());
    if (!isValid(filePath))                   //if xml file not valid
    {
        outputTextBox->setPlainText("The XML file is INVALID, please input a valid file.....");
        return;
    }
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open file: " + file.errorString());
        return;
    }

    // Read the file content
    QString fileContent;
    QTextStream in(&file);
    fileContent = in.readAll();

    if(fileContent == "0") {
        outputTextBox->setPlainText("The XML file is Empty, please input a valid file.....");
        file.close();
    }


    else{
        // Perform edits on the file content (example: appending text)
        //fileContent += "\nEdited content added to the file.";

        // Write the modified content back to the file
        file.resize(0); // Clear the file before writing
        QTextStream out(&file);
        out << fileContent;

        file.close();

        // Display the updated file content in the outputTextBox
        outputTextBox->setPlainText(fileContent);
    }
}

void MainWindow::pret() {

    std::string filePath = saveToXml();
    std::string outputPath = "output.xml";
    format_XML(filePath, outputPath);
    // Open the output file for reading
    QFile file(outputPath.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        outputTextBox->setPlainText("Error: Unable to read the output file.");
        return;
    }

    // Read the content of the file
    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    if (fileContent.trimmed() == "0") {
        outputTextBox->setPlainText("The XML file is valid and no error correction is needed");
    } else {
        outputTextBox->setPlainText("Prettifying Done\n" + fileContent);
    }

}

void MainWindow::valid() {
    outputTextBox->clear();
    string filePath = saveToXml();
    clearHighlights(outputTextBox);

    std::ostringstream oss;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());

    // Call the function
    isValid(filePath);

    // Restore the original cout buffer
    std::cout.rdbuf(oldCoutBuffer);

    // Get the output and append it to QTextEdit
    QString output = QString::fromStdString(oss.str());
    //outputTextBox->setPlainText(output);



    if(!isValid(filePath))
    {
        QMessageBox::information(this, "Info", output);
        QString fileName =QString::fromStdString(filePath);
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                outputTextBox->setPlainText(in.readAll());

            }


            file.close();
        }
        stack<pair<string, long long>> copy = unClosed;
        while(!copy.empty())
    {
             highlightLine(outputTextBox,copy.top().second-1);
            qInfo() << copy.top().first<<"\n";
            qInfo() << copy.top().second<<"\n";
            copy.pop();
    }//stack
        if(!unOpened.empty())
    {    for(long long k=0;k<unOpened.size();k++)
        {
        highlightLine(outputTextBox, unOpened[k].first-1);
        qInfo() <<unOpened[k].second<<"\n";
        qInfo() <<unOpened[k].first<<"\n";
        }//vector
        }
    }else outputTextBox->setPlainText("The XML file is valid......");

}


void MainWindow::corr() {
    outputTextBox->clear();

        // Save input to an XML file
        string filePath = saveToXml();
        string outputPath = "sample4Soln.txt";

         errorCorrection(filePath, outputPath);

    QFile file(outputPath.c_str());
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open file: " + file.errorString());
        return;
    }

    // Read the file content
    QString fileContent;
    QTextStream in(&file);
    fileContent = in.readAll();

    if(fileContent == "0") {
        outputTextBox->setPlainText("The XML file is valid and no error correction is needed");
         file.close();
    }


    else{
    // Perform edits on the file content (example: appending text)
    //fileContent += "\nEdited content added to the file.";

    // Write the modified content back to the file
    file.resize(0); // Clear the file before writing
    QTextStream out(&file);
    out << fileContent;

    file.close();

    // Display the updated file content in the outputTextBox
    outputTextBox->setPlainText(fileContent);
    }
}


void MainWindow::processText() {
    outputTextBox->clear();
    string filePath = saveToXml();
}

void MainWindow::highlightLine(QTextEdit* textEdit, int lineNumber) {
    if (!textEdit) return;
    QTextDocument* doc = textEdit->document();
    if (lineNumber < 0 || lineNumber >= doc->blockCount()) return; // Ensure lineNumber is valid

    // Highlight the specified line
    QTextBlock block = doc->findBlockByLineNumber(lineNumber);
    if (!block.isValid()) return;

    QTextCursor cursor(block);
    QTextBlockFormat blockFormat;
    blockFormat.setBackground(QColor(Qt::yellow)); // Set highlight color (yellow in this case)
    cursor.setBlockFormat(blockFormat);
}
// void MainWindow::clearHighlights(QTextEdit* textEdit) {
//     if (!textEdit) return;

//     QTextDocument* doc = textEdit->document();
//     QTextCursor clearCursor(doc);
//     clearCursor.select(QTextCursor::Document);
//     QTextBlockFormat clearFormat;
//     clearFormat.setBackground(Qt::white); // Reset background to default
//     clearCursor.setBlockFormat(clearFormat);
// }

void MainWindow::clearHighlights(QTextEdit* textEdit) {
    if (!textEdit) return;

    QTextDocument* doc = textEdit->document();
    QTextCursor cursor(doc);

    // Iterate through each block in the document
    for (QTextBlock block = doc->begin(); block.isValid(); block = block.next()) {
        QTextCursor blockCursor(block);
        QTextBlockFormat blockFormat;
        //blockFormat.setBackground(Qt::white); // Reset background to default
        blockCursor.setBlockFormat(blockFormat);
    }
}





MainWindow::~MainWindow(){}
