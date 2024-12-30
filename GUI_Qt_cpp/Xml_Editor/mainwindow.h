#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QFileDialog>
#include <QLabel>
#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QString>
#include <sstream>
#include <iostream>
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QTextBlockFormat>
#include <QColor>
#include <QTextBlock>
#include <QFontMetrics>

#include "../../Validity_checker/isValid.h"
//#include "../../most_active/most_active.h"
#include "../../Error_Correction/Error_Correction.h"
#include "../../Xml_to_Json/Xml_to_Json/Xml_to_Json.h"
#include "../../Xml_to_Graph/Xml_to_Graph/Xml_to_Graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *container ;
    QHBoxLayout *mainLayout;
    QLabel *inputLabel;
    QTextEdit *inputTextBox;
    QPushButton *loadFileButton;
    QVBoxLayout *inputLayout;
    QVBoxLayout *controlLayout;
    QPushButton *valid_button;
    QPushButton *correct;
    QVBoxLayout *validLayout;
    QPushButton *prettify;
    QPushButton *json;
    QPushButton *minify;
    QPushButton *compress;
    QPushButton *decompress;
    QPushButton *draw;
    QComboBox *networkAnalysis;
    QComboBox *search;
    QLineEdit *searchWord;
    QVBoxLayout *searchLayout;
    QLabel *outputLabel;
    QTextEdit *outputTextBox;
    QPushButton *saveFileButton;
    QPushButton *processButton;
    QVBoxLayout *outputLayout;

    // privare function
    void highlightLine(QTextEdit* textEdit, int lineNumber);
    string saveToXml();
    void clearHighlights(QTextEdit* textEdit);
private slots:
    void processText();             // Slot for processing input text
    void saveFile();                // Slot for saving file
    void loadFile();                // SLot for loading file
    void valid();                   // SLot for valid button
    void corr();                    // SLot for correct button
    void pret();                    // SLot for prettify button
    void mini();                    // SLot for minify button
    void comp();                    // SLot for compress button
    void decomp();                  // SLot for decompress button
    void networkanalysisAction();   // SLot for network analysis Combobox
    void searchAction();            // SLot for search Combobox
    void xml2json();                // SLot for json button
    void drawGraph();               // SLot for draw button
};

#endif // MAINWINDOW_H
