cmake_minimum_required (VERSION 3.0)
project (painter)

set(LD_AUX "") 
#windows
if (WIN32) 
	# on visual
	if (MSVC)
            set ( CMAKE_CXX_FLAGS "-DOS_WINDOWS")
            set(QTDIR "C:\\Qt\\5.14.1\\5.12.5\\msvc2017_64\\")
	# on min mingw
	else()
            set ( CMAKE_CXX_FLAGS "-DOS_LINUX -g -fPIC -Wunused-parameter -pipe -std=gnu++17 -frtti -Wall -Wextra -fexceptions -pthread -Wno-unused-function -Wno-unused-variable")
            set(QTDIR "./ext/mingw73_32")
	endif(MSVC)

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/windows/)
        set(QT_INCLUDE_DIR ${QTDIR}/include)
#linux
else()
	set(LD_AUX "dl") 
	set(CMAKE_CXX_FLAGS "-DOS_LINUX -g -fPIC -Wunused-parameter -pipe -std=gnu++17 -frtti -Wall -Wextra -fexceptions -pthread -Wno-unused-function -Wno-unused-variable")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/linux/)
    #linux64
    if (EXISTS "/usr/include/x86_64-linux-gnu/qt5/")
            set(QT_INCLUDE_DIR "/usr/include/x86_64-linux-gnu/qt5/")
    #linux32
    else()
            set(QT_INCLUDE_DIR "/usr/include/i386-linux-gnu/qt5/")
    endif()
endif (WIN32)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.tmp/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.tmp/lib)


set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH ${QTDIR})
set(CMAKE_CXX_STANDARD 17)

find_package (Qt5Widgets)
find_package (Qt5Core)
find_package (Qt5Gui)
find_package (Qt5DataVisualization)
find_package (Qt5Charts)
#find_package (Qt5Svg)
#find_package (Qt5Xml)

include_directories(./include)

include_directories(${QT_INCLUDE_DIR}/)
include_directories(${QT_INCLUDE_DIR}/QtCore)
include_directories(${QT_INCLUDE_DIR}/QtGui)
include_directories(${QT_INCLUDE_DIR}/QtCore)
include_directories(${QT_INCLUDE_DIR}/QtWidgets)
include_directories(${QT_INCLUDE_DIR}/Qt5DataVisualization/)
include_directories(${QT_INCLUDE_DIR}/Qt5Charts/)
include_directories("C:\\Programs\\eigen3\\")


add_subdirectory (${PROJECT_SOURCE_DIR}/gui)
add_subdirectory (${PROJECT_SOURCE_DIR}/core)
add_subdirectory (${PROJECT_SOURCE_DIR}/parser)
add_subdirectory (${PROJECT_SOURCE_DIR}/QRibbon)
add_subdirectory (${PROJECT_SOURCE_DIR}/rq_plugin/)

add_executable(thermoIC ${PROJECT_SOURCE_DIR}/main.cpp )
add_dependencies(thermoIC core gui parser QRibbon rq_plugin )
target_link_libraries (thermoIC core gui parser QRibbon rq_plugin Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Charts Qt5::DataVisualization ${LD_AUX})
