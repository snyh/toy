cmake_minimum_required(VERSION 2.6.8)

find_package(wxWidgets COMPONENTS core base REQUIRED)
find_package(Boost COMPONENTS system signals serialization thread program_options REQUIRED)
set(Boost_USE_MULTITHREAD ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Threads)
if(WIN32)
	set(CMAKE_CPP_FLAGS "-DBOOST_THREAD_USE_LIB")
	set(WIN_LIB  ws2_32)
endif(WIN32)

include(${wxWidgets_USE_FILE})
add_executable(editer
	canvas.cpp
	gui.cpp
	main.cpp
	my_data.cpp
	)
target_link_libraries(editer ${wxWidgets_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${WIN_LIB})
