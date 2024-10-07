# Define the source files for your application
set(APP_SOURCES
    Application.cpp
    Button.cpp
    Cell.cpp
    ControlsState.cpp
    Grid.cpp
    main.cpp
    MainMenuState.cpp
    MusicManager.cpp
    Simulation.cpp
    SimulationState.cpp
)

# Path to resource files (make sure this path is correct)
set(RESOURCE_DIR "${PROJECT_SOURCE_DIR}/src/resources")

# Define the resource files
set(ICON_FILE "${PROJECT_SOURCE_DIR}/assets/app_icon.ico")
set(RC_FILE "${RESOURCE_DIR}/resources.rc")
set(RC_OBJ "${CMAKE_CURRENT_BINARY_DIR}/app.o")  # Adjust build path if necessary

# Debugging paths
message("RESOURCE_DIR: ${RESOURCE_DIR}")
message("RC_FILE: ${RC_FILE}")
message("RC_OBJ: ${RC_OBJ}")

# Add custom command to generate .o file from .rc using windres
add_custom_command(
    OUTPUT ${RC_OBJ}
    COMMAND windres ${RC_FILE} -o ${RC_OBJ}
    DEPENDS ${RC_FILE} ${ICON_FILE}
    COMMENT "Compiling resource file ${RC_FILE}"
)

# Create a library from your application code
add_library(${projectName}_lib ${APP_SOURCES})

# Include directories for the library
target_include_directories(${projectName}_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Link raylib library to your app library
target_link_libraries(${projectName}_lib PUBLIC raylib)

# Create the main executable, including the compiled resource object
add_executable(${projectName} main.cpp ${RC_OBJ})

# Link the application library and raylib into the main executable
target_link_libraries(${projectName} PRIVATE ${projectName}_lib)

# Custom command to copy assets directory after build (if applicable)
add_custom_command(
    TARGET ${projectName} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${projectName}>/assets
)
