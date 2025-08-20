QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttonmenu.cpp \
    cbottomctrlbar.cpp \
    ccombinationplay.cpp \
    cmainwindow.cpp \
    cplaybuttongroupwidget.cpp \
    cpositionsliderdialog.cpp \
    ctitlebar.cpp \
    cvolumebutton.cpp \
    cvolumesliderdialog.cpp \
    framelesswidget.cpp \
    main.cpp \
    medialistmodel.cpp \
    playlistdialog.cpp \
    videowidget.cpp \
    vlckits.cpp

HEADERS += \
    buttonmenu.h \
    cbottomctrlbar.h \
    ccombinationplay.h \
    cmainwindow.h \
    cplaybuttongroupwidget.h \
    cpositionsliderdialog.h \
    ctitlebar.h \
    cvolumebutton.h \
    cvolumesliderdialog.h \
    framelesswidget.h \
    medialistmodel.h \
    playlistdialog.h \
    qss.h \
    videowidget.h \
    vlckits.h

FORMS += \
    framelesswidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# macOS 特定配置
macx {
    QMAKE_INFO_PLIST = Info.plist
    ICON = app.icns
}

RESOURCES += \
    res.qrc


macx {
    INCLUDEPATH += /Applications/VLC.app/Contents/MacOS/include
    LIBS += -L/Applications/VLC.app/Contents/MacOS/lib -lvlc -lvlccore
}
