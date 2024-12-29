QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../Error_Correction/Error_Correction.cpp \
    ../../Validity_checker/isValid.cpp \
    ../../Xml_to_Graph/Xml_to_Graph/Xml_to_Graph.cpp \
    ../../Xml_to_Json/Xml_to_Json/Xml_to_Json.cpp \
    ../../most_active/most_active.cpp \
    ../../parseXML/parseXML.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../Error_Correction/Error_Correction.h \
    ../../Validity_checker/isValid.h \
    ../../Xml_to_Graph/Xml_to_Graph/Xml_to_Graph.h \
    ../../Xml_to_Json/Xml_to_Json/Xml_to_Json.h \
    ../../most_active/most_active.h \
    ../../parseXML/parseXML.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
