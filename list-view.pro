HEADERS += \
    columns.hpp \
    list_view.hpp \
    person_model.hpp \
    vip_delegate.hpp

SOURCES += \
    list_view.cpp \
    main.cpp \
    person_model.cpp \
    vip_delegate.cpp

DISTFILES += \
    columns.qdoc

CONFIG += c++20 strict_c++
QT += widgets
