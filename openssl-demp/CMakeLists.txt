#set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)
#find_package(OpenSSL)
#message (STATUS "OPENSSL_INCLUDE_DIR = ${OPENSSL_INCLUDE_DIR} : OPENSSL_LIBRARIES = ${OPENSSL_LIBRARIES}")
#message(STATUS "USE_STATIC_LIBRARIES = ${USE_STATIC_LIBRARIES}")
#
#add_library(UseOpenSSL UseOpenSSL.cpp)
#
#target_link_libraries(UseOpenSSL ssl)