#include "mainwindow.h"
#include "ui_mainwindow.h"

bool empt = false;

MainWindow::MainWindow(QWidget *parent) {
    // Main container widget
    container = new QWidget();
    mainLayout = new QHBoxLayout();

    // Input Section
    inputLabel = new QLabel("Input");
    inputTextBox = new QTextEdit();
    inputTextBox->setPlaceholderText("Place your Input Here...");
    loadFileButton = new QPushButton("Load File");
    connect(loadFileButton, &QPushButton::clicked, this, &MainWindow::loadFile);

    
   // inputTextBox->setPlainText("Line 1\nLine 2\nLine 3\nLine 4");


    inputLayout = new QVBoxLayout();
    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputTextBox);
    inputLayout->addWidget(loadFileButton);

    // Control Section
    controlLayout = new QVBoxLayout();


    // Buttons
    valid_button = new QPushButton(QString("Check the XML consistency"));
    valid_button->setMaximumWidth(200);
    connect(valid_button, &QPushButton::clicked, this, &MainWindow::valid);

    correct = new QPushButton(QString("Correct to be valid"));
    correct->setMaximumWidth(200);
    connect(correct, &QPushButton::clicked, this, &MainWindow::corr);

    validLayout = new QVBoxLayout();
    validLayout->addWidget(valid_button);
    validLayout->addWidget(correct);
    controlLayout->addLayout(validLayout);

    prettify = new QPushButton(QString("Prettify XML"));
    prettify->setMaximumWidth(200);
    connect(prettify, &QPushButton::clicked, this, &MainWindow::pret);
    controlLayout->addWidget(prettify);

    json = new QPushButton(QString("XML --> Json"));
    json->setMaximumWidth(200);
    connect(json, &QPushButton::clicked, this, &MainWindow::xml2json);
    controlLayout->addWidget(json);

    minify = new QPushButton(QString("Minify XML"));
    minify->setMaximumWidth(200);
    connect(minify, &QPushButton::clicked, this, &MainWindow::mini);
    controlLayout->addWidget(minify);

    compress = new QPushButton(QString("Compress XML"));
    compress->setMaximumWidth(200);
    connect(compress, &QPushButton::clicked, this, &MainWindow::comp);
    controlLayout->addWidget(compress);

    decompress = new QPushButton(QString("Decompress XML"));
    decompress->setMaximumWidth(200);
    connect(decompress, &QPushButton::clicked, this, &MainWindow::decomp);
    controlLayout->addWidget(decompress);

    draw = new QPushButton(QString("XML --> Graph"));
    draw->setMaximumWidth(200);
    connect(draw, &QPushButton::clicked, this, &MainWindow::drawGraph);
    controlLayout->addWidget(draw);

    // Dropdown menus
    networkAnalysis = new QComboBox();
    networkAnalysis->setPlaceholderText("Network Analysis");
    networkAnalysis->setMaximumWidth(200);
    networkAnalysis->addItems({"Most Active", "Most Infleuncer", "Mutual Users", "Suggested Users"});
    connect(networkAnalysis, &QComboBox::currentIndexChanged, this, &MainWindow::networkanalysisAction);

    searchWord =  new QLineEdit();
    searchWord->setPlaceholderText("Enter Search word Here");
    searchWord->setMaximumWidth(200);
    search = new QComboBox();
    search->setPlaceholderText("Search");
    search->setMaximumWidth(200);
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
    outputTextBox->setReadOnly(1);
    outputTextBox->setPlaceholderText("Output Will Appear Here");
    saveFileButton = new QPushButton("Save File");
    connect(saveFileButton, &QPushButton::clicked, this, &MainWindow::saveFile);
    // Highlight line 2 (index starts at 0)



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
    if (dropdown->currentIndex() == 0){
        // call "Most Active"
        //outputTextBox->append(lw elfunction void nadoha hena);
        // Redirect cout to a string stream

    }
    else if (dropdown->currentIndex() == 1){
        // call "Most Infleuncer"
        //outputTextBox->append(lw elfunction void nadoha hena);
    }
    else if (dropdown->currentIndex() == 2){
        // call "Mutual Users"
        //outputTextBox->append(lw elfunction void nadoha hena);
    }
    else if (dropdown->currentIndex() == 3){
        // call "Suggested Users"
        //outputTextBox->append(lw elfunction void nadoha hena);
    }
}

void MainWindow::searchAction() {
    QComboBox *dropdown = qobject_cast<QComboBox *>(sender());
    outputTextBox->clear();
    string filePath = saveToXml();
    if (dropdown->currentIndex() == 0){
        // call "search with word"
        //outputTextBox->append(lw elfunction void nadoha hena);
    }
    else if (dropdown->currentIndex() == 1){
        // call "search with topic"
        //outputTextBox->append(lw elfunction void nadoha hena);
    }
}

void MainWindow::drawGraph() {
    outputTextBox->clear();
    string filePath = saveToXml();
    QString imgPath1 = "graph.jpg";
    string imgPath = "graph.jpg";
    //call graph function(filePath,imgPath)
    outputTextBox->append("<img src='"+imgPath1+"' width='300' height='200' />");
}

void MainWindow::decomp() {
    outputTextBox->clear();

}

void MainWindow::comp() {
    outputTextBox->clear();
    string filePath = saveToXml();
}

void MainWindow::mini() {
    outputTextBox->clear();
    string filePath = saveToXml();
}

void MainWindow::xml2json() {
    outputTextBox->clear();
    string filePath = saveToXml();
}

void MainWindow::pret() {
    outputTextBox->clear();
    string filePath = saveToXml();
    if(!empt){
        //call function here
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
    outputTextBox->append(output);

    QString fileName =QString::fromStdString(filePath);
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
              outputTextBox->setPlainText(in.readAll());

        }


            file.close();
        }


    if(!isValid(filePath))
     {     stack<pair<string, long long>> copy = unClosed;
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
    }

}

void MainWindow::corr() {
    outputTextBox->clear();
    string filePath = saveToXml();
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
        blockFormat.setBackground(Qt::white); // Reset background to default
        blockCursor.setBlockFormat(blockFormat);
    }
}





MainWindow::~MainWindow(){}
