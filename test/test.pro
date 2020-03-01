QT                          += testlib
QT                          -= gui

CONFIG                      += qt console warn_on depend_includepath testcase sdk_no_version_check
CONFIG                      -= app_bundle

TEMPLATE                    = app
INCLUDEPATH                 += ../app/

include(test.pri)
