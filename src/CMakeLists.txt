project(libWebSocket_Lite)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

if(WIN32)
    set(WEBSOCKET_LITE_PLATFORM_SRC     
	
    )

    set(WEBSOCKET_LITE_PLATFORM_INC     
   
    )

elseif(APPLE)


    set(WEBSOCKET_LITE_PLATFORM_SRC
    )
    set(WEBSOCKET_LITE_PLATFORM_INC
    )
else()
     set(WEBSOCKET_LITE_PLATFORM_SRC
    )
    set(WEBSOCKET_LITE_PLATFORM_INC
    )
	
endif()

set(WEBSOCKET_LITE_COMMON_SRC 
	${CMAKE_CURRENT_SOURCE_DIR}/../include/internal/WebSocketProtocol.h
	${CMAKE_CURRENT_SOURCE_DIR}/../include/internal/SHA.h
	${CMAKE_CURRENT_SOURCE_DIR}/../include/internal/Base64.h
	${CMAKE_CURRENT_SOURCE_DIR}/../include/Logging.h
	${CMAKE_CURRENT_SOURCE_DIR}/../include/WS_Lite.h
	${CMAKE_CURRENT_SOURCE_DIR}/../src/internal/ListenerImpl.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/internal/ClientImpl.cpp
)

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

set(WEBSOCKET_LITE_INCLUDE_DIRS 
	${OPENSSL_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/../include
	${CMAKE_CURRENT_SOURCE_DIR}/../src
	${WEBSOCKET_LITE_PLATFORM_INC}
	CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
 )

set(WEBSOCKET_LITE_LIBS
	${OPENSSL_LIBRARIES} 
	${Boost_LIBRARIES}
	${PROJECT_NAME}
	CACHE INTERNAL "${PROJECT_NAME}: Include Libraries" FORCE
)
include_directories(${WEBSOCKET_LITE_INCLUDE_DIRS})
add_library(${PROJECT_NAME} ${WEBSOCKET_LITE_COMMON_SRC} ${WEBSOCKET_LITE_PLATFORM_SRC})

target_link_libraries(${PROJECT_NAME} ${WEBSOCKET_LITE_PLATFORM_LIBS})

