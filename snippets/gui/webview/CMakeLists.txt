CPMAddPackage(NAME webview GIT_REPOSITORY https://github.com/zserge/webview GIT_TAG 50e4bcc420abdc7be96a54b7c79934a000b76901
        VERSION 0.1.1 DOWNLOAD_ONLY TRUE)
add_library(webview INTERFACE)
target_include_directories(webview INTERFACE ${webview_SOURCE_DIR})
add_executable(webview_hello webview_hello.cpp)
target_link_libraries(webview_hello PUBLIC webview)
if (UNIX)
    # See: https://github.com/webview/webview/blob/master/script/build.sh
    if (APPLE)
        target_compile_definitions(webview_hello PUBLIC WEBVIEW_COCOA)
        target_compile_definitions(webview_hello PUBLIC "GUI_SOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"")
        target_compile_options(webview_hello PUBLIC -Wall -Wextra -Wpedantic -Wno-delete-non-abstract-non-virtual-dtor)
        target_link_libraries(webview_hello PUBLIC "-framework WebKit")
    else ()
        target_compile_definitions(webview_hello PUBLIC WEBVIEW_GTK)
        target_compile_options(webview_hello PUBLIC -Wall -Wextra -Wpedantic)
        target_link_libraries(webview_hello PUBLIC "$(pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0)")
    endif()
else()
    # Link windows
    # See: https://github.com/webview/webview/blob/master/script/build.bat
endif()