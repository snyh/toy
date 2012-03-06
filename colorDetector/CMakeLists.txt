cmake_minimum_required(VERSION 2.6.8)

find_package(OpenCV REQUIRED)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(
	colorDetector
	src/main.cpp
	src/MainFrame.cpp
	src/ColorDetectframe.cpp
	src/Model.cpp 
	src/Control.cpp
)

target_link_libraries(colorDetector
	${OpenCV_LIBS} ${wxWidgets_LIBRARIES})
