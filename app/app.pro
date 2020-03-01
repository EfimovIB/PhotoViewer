QT                          += quick network
CONFIG                      += c++11 sdk_no_version_check
DEFINES                     += QT_DEPRECATED_WARNINGS

CONFIG( debug, debug|release ) {
    OBJECTS_DIR             +=  tmp/obj/debug

} else {
    OBJECTS_DIR             +=  tmp/obj/release
}

TARGET                      =   photoviewer
MOC_DIR                     +=  tmp/moc
RCC_DIR                     +=  tmp/rcc
UI_DIR                      +=  tmp/uic
DEPENDPATH                  +=  .
VPATH                       +=  ../core
INCLUDEPATH                 +=  .       \
                                tmp/moc \
                                tmp/uic

include($$PWD/app.pri)
