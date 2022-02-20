target_sources(${BUILD_NAME} PRIVATE
    # put source files here
    src/midi_stm32.cpp    
    src/midi_common.cpp
)

target_include_directories(${BUILD_NAME} PRIVATE inc)