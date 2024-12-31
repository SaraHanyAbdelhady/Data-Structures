QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += console
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../Error_Correction/Error_Correction.cpp \
    ../../Minifying_XML/Minifying.cpp \
    ../../Most_influencer/Most_influencer.cpp \
    ../../Mutual_Users/Mutual_Users.cpp \
    ../../Search/topicSearch.cpp \
    ../../Search/wordSearch.cpp \
    ../../Suggested_users/SuggestedUsers.cpp \
    ../../Validity_checker/isValid.cpp \
    ../../Xml_to_Graph/Xml_to_Graph/Xml_to_Graph.cpp \
    ../../Xml_to_Json/Xml_to_Json/Xml_to_Json.cpp \
    ../../compress_decompress/compress_decompress.cpp \
    ../../parseXML/parseXML.cpp \
    ../../most_active/most_active.cpp \
    ../../Formatting_XML/format_xml.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../Error_Correction/Error_Correction.h \
    ../../Minifying_XML/Minifying.h \
    ../../Most_influencer/Most_influencer.h \
    ../../Mutual_Users/Mutual_Users.h \
    ../../Search/topicSearch.h \
    ../../Search/wordSearch.h \
    ../../Suggested_users/Suggested_users.h \
    ../../Validity_checker/isValid.h \
    ../../Xml_to_Graph/Xml_to_Graph/Xml_to_Graph.h \
    ../../Xml_to_Json/Xml_to_Json/Xml_to_Json.h \
    ../../compress_decompress/compress_decompress.h \
    ../../Formatting_XML/format_xml.h \
    ../../most_active/most_active.h \
    ../../parseXML/parseXML.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../../XML/Data-Structures/Test_samples/Xml_to_Json/sample.xml




