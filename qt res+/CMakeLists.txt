# CMakeList.txt: проект CMake для button; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("button")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(AUTORCC_EXECUTABLE ON)

set(SOURCES button.cpp)


set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.12.12\\5.12.12\\msvc2017_64\\lib\\cmake")

find_package(Qt5 COMPONENTS
		Core
		Gui
		Widgets
		REQUIRED
		)


# Добавьте источник в исполняемый файл этого проекта.
QT5_ADD_RESOURCES(SOURCES img.qrc)
add_executable(button "button.cpp" 
			qrc_img.cpp)

target_link_libraries(button
		Qt5::Widgets
		Qt5::Gui
		Qt5::Core
		)


foreach (QT_LIB Qt5Widgets Qt5Gui Qt5Core libGLESv2)
	add_custom_command(TARGET button POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
			"C:\\Qt\\Qt5.12.12\\5.12.12\\msvc2017_64\\bin\\${QT_LIB}d.dll"
			"$<TARGET_FILE_DIR:button>")
endforeach (QT_LIB)