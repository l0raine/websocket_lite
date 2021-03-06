cmake_minimum_required(VERSION 3.10)
project(websocket_lite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(BUILD_SHARED_LIBS "Build shared library" OFF) 

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	add_definitions(-D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING)
	add_definitions(-D_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING)
	
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()
add_definitions(-DBOOST_REGEX_NO_LIB -DBOOST_DATE_TIME_NO_LIB -DASIO_STANDALONE -DBOOST_NO_EXCEPTIONS)
find_package(ZLIB REQUIRED) 
find_package(OpenSSL REQUIRED) 
	
include_directories(
	include
	${OPENSSL_INCLUDE_DIR}
	${ZLIB_INCLUDE_DIRs}
)
add_library(${PROJECT_NAME} 	
	include/internal/Utils.h
	include/internal/WebSocketProtocol.h
	include/internal/HeaderParser.h
	include/internal/StringHelpers.h
	include/internal/ThreadContext.h
	include/internal/HubContext.h
	include/internal/WebSocket.h
	include/internal/SocketIOStatus.h
	include/internal/WebSocketContext.h
	include/WS_Lite.h
	src/Utils.cpp
	src/ListenerImpl.cpp
	src/ClientImpl.cpp
	src/HubContext.cpp
)

if(WIN32) 
	add_definitions(-DNOMINMAX -DWIN32_LEAN_AND_MEAN)
endif() 

if(${BUILD_SHARED_LIBS})
	set_target_properties(${PROJECT_NAME} PROPERTIES DEFINE_SYMBOL WS_LITE_DLL)
	if(WIN32) 
		target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} ${OPENSSL_LIBRARIES} Crypt32)
		install (FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION bin OPTIONAL)
	elseif(APPLE) 
		find_package(Threads REQUIRED)
		target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )
	else()
		find_package(Threads REQUIRED)
		target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} dl)
	endif()
endif()

install (TARGETS ${PROJECT_NAME} 
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib)

install (FILES 
	include/WS_Lite.h
	include/Logging.h
	DESTINATION include)

enable_testing() 
add_subdirectory(Test)