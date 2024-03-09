

add_executable(Consumer consumer.cpp)

add_executable(Creator creator.cpp)

# Have to link against lrt (real time)

target_link_libraries(Consumer PUBLIC "-lrt")

target_link_libraries(Creator PUBLIC "-lrt")

include(GNUInstallDirs)

install(TARGETS Consumer Creator
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
)
