TEMPLATE = app
TARGET = reversehashd

QT       += core xml network websockets
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11 c++14

OBJECTS_DIR = tmp/
MOC_DIR = tmp/
RCC_DIR = tmp/

INCLUDEPATH += src/bna
INCLUDEPATH += src/server
INCLUDEPATH += src/interfaces

RESOURCES = reversehashd.qrc

SOURCES += src/main.cpp \
    src/memory.cpp \
    src/helpers.cpp \
    src/memoryitem.cpp \
    src/operations/xor.cpp \
    src/operations/or.cpp \
    src/operations/and.cpp \
    src/vertexes/vertex_in.cpp \
    src/vertexes/vertex.cpp \
    src/vertex_graph.cpp \
    src/bna/bna.cpp \
    src/tests/tests.cpp \
    src/tests/callout_test.cpp \
    src/tests/readwrite_test.cpp \
    src/tests/reverse_test.cpp \
    src/tests/changerandomoperation_test.cpp \
    src/tests/swaprandomvertexins_test.cpp \
    src/tests/clonecopy_test.cpp \
    src/tests/random_remove_vertex_test.cpp \
    src/tests/random_add_vertex_test.cpp \
    src/server/reversehashd_server.cpp \
    src/server/error.cpp \
    src/server/training_thread.cpp \
    src/server/training_thread_item.cpp \
    src/server/training_thread_message.cpp \
    src/server/cmd_handlers/create_cmd_handlers.cpp \
    src/server/cmd_handlers/cmd_hello_handler.cpp \
    src/server/cmd_handlers/cmd_reverse_handler.cpp \
    src/server/cmd_handlers/cmd_statistics_handler.cpp \
    src/server/cmd_handlers/cmd_graph_handler.cpp \

HEADERS += \
    src/memory.h \
    src/helpers.h \
    src/memoryitem.h \
    src/interfaces/ioperation.h \
    src/interfaces/ivertex_operation.h \
    src/interfaces/ivertex_out.h \
    src/interfaces/ivertex_in.h \
    src/interfaces/icmdhandler.h \
    src/interfaces/ireversehashdserver.h \
    src/operations/xor.h \
    src/operations/or.h \
    src/operations/and.h \
    src/vertexes/vertex_in.h \
    src/vertexes/vertex.h \
    src/vertex_graph.h \
    src/bna/bna.h \
    src/tests/tests.h \
    src/tests/ireversehashtest.h \
    src/tests/callout_test.h \
    src/tests/readwrite_test.h \
    src/tests/reverse_test.h \
    src/tests/changerandomoperation_test.h \
    src/tests/swaprandomvertexins_test.h \
    src/tests/clonecopy_test.h \
    src/tests/random_remove_vertex_test.h \
    src/tests/random_add_vertex_test.h \
    src/server/reversehashd_server.h \
	src/server/error.h \
	src/server/training_thread.h \
	src/server/training_thread_item.h \
	src/server/training_thread_message.h \
    src/server/cmd_handlers/create_cmd_handlers.h \
	src/server/cmd_handlers/include/cmd_hello_handler.h \
	src/server/cmd_handlers/include/cmd_reverse_handler.h \
	src/server/cmd_handlers/include/cmd_statistics_handler.h \
	src/server/cmd_handlers/include/cmd_graph_handler.h \
