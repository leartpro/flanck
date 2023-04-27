add_library(
        flanck SHARED
        src/Stack.h
        src/Lexer.cpp
        src/Lexer.h
        src/Parser.cpp
        src/Parser.h
        src/Interpreter.cpp
        src/Interpreter.h
)
set_target_properties(
        flanck PROPERTIES
        EXPORT_NAME flanck
        VERSION 1.0.0
        SOVERSION 1
)
install(
        TARGETS flanck
        EXPORT flanck-targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include
)
install(
        FILES
        src/Stack.h
        src/Lexer.h
        src/Parser.h
        src/Interpreter.h
        DESTINATION include/flanck
)
install(
        FILES flanck-config.cmake
        DESTINATION lib/cmake/flanck
)
export(
        EXPORT flanck-targets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/flanck-targets.cmake"
        NAMESPACE flanck::
)
configure_file(
        cmake/flanck-config.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/flanck-config.cmake"
        COPYONLY
)
set(ConfigPackageLocation lib/cmake/flanck)
install(
        EXPORT flanck-targets
        FILE flanck-targets.cmake
        NAMESPACE flanck::
        DESTINATION ${ConfigPackageLocation}
)
install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/flanck-config.cmake"
        DESTINATION ${ConfigPackageLocation}
)