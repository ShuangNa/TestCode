QT += core widgets gui

TARGET = MainCtrl
TEMPLATE = lib
DEFINES += MAINCTRL_LIBRARY

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/../../lib

CONFIG(debug, debug|release){
    copydir = $$PWD/../../../build/debug
}else {
    copydir = $$PWD/../../../build/release
}
outDllFile = $$DESTDIR/$${TARGET}.dll
outLibFile = $$DESTDIR/lib$${TARGET}.a

INCLUDEPATH += \
    $$PWD/../../include/public

SOURCES += \
    MainCtrl.cpp

HEADERS += \
    ../../include/public/IMainTimer.hpp \
    ../../include/public/IMainDrawer.hpp \
    ../../include/public/ICommand.hpp \
    ../../include/public/IComponent.hpp \
    ../../include/public/IMainCtrl.hpp \
    ../../include/public/IMessage.hpp \
    ../../include/public/IObjectCreator.hpp \
    MainCtrl.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


#将输入目录中的"/"替换为"\"
copydir = $$replace(copydir, /, \\)
outDllFile = $$replace(outDllFile, /, \\)
outLibFile = $$replace(outLibFile, /, \\)

#执行copy命令
QMAKE_POST_LINK += copy /Y $$outDllFile $$copydir && copy /Y $$outLibFile $$copydir

