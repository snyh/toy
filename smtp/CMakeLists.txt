cmake_minimum_required(VERSION 2.8)
find_package(Boost COMPONENTS thread system REQUIRED)
find_package(Threads)
find_package(OpenSSL)

add_executable(test 
	test.cpp
	libamail.cpp
	)

target_link_libraries(test
	${Boost_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
	${OPENSSL_LIBRARIES}
	)


#add_executable(tmp b.cpp)
#target_link_libraries(tmp boost_system boost_thread-mt pthread ssl)
