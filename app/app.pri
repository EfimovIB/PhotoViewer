SOURCES += \
    $$PWD/base/albums_dict.cpp \
    $$PWD/base/photos_dict.cpp \
    $$PWD/base/users_dict.cpp \
    $$PWD/data_source/data_source_factory.cpp \
    $$PWD/data_source/data_source_mock.cpp \
    $$PWD/data_source/data_source_null.cpp \
    $$PWD/data_source/jsonplaceholder/data_source_jsonplaceholder.cpp \
    $$PWD/data_source/jsonplaceholder/downloader.cpp \
    $$PWD/data_source/jsonplaceholder/parser.cpp \
    $$PWD/main.cpp \
    $$PWD/model/album_model.cpp \
    $$PWD/model/photo_model.cpp \
    $$PWD/model/user_model.cpp \
    $$PWD/settings.cpp

HEADERS += \
    $$PWD/base/album.h \
    $$PWD/base/albums_dict.h \
    $$PWD/base/photo.h \
    $$PWD/base/photos_dict.h \
    $$PWD/base/types.h \
    $$PWD/base/user.h \
    $$PWD/base/users_dict.h \
    $$PWD/data_source/data_source.h \
    $$PWD/data_source/data_source_factory.h \
    $$PWD/data_source/data_source_mock.h \
    $$PWD/data_source/data_source_null.h \
    $$PWD/data_source/jsonplaceholder/data_source_jsonplaceholder.h \
    $$PWD/data_source/jsonplaceholder/downloader.h \
    $$PWD/data_source/jsonplaceholder/parser.h \
    $$PWD/model/album_model.h \
    $$PWD/model/photo_model.h \
    $$PWD/model/user_model.h \
    $$PWD/settings.h

RESOURCES += qml.qrc

QML_IMPORT_PATH += $$PWD/qml
QML2_IMPORT_PATH += $$PWD/qml
