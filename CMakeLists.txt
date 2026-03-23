option(BUILD_DBOW2_STANDALONE "Build DBoW2 as a standalone project" ON) 

# Set name of the module
set(project_name_ "DBoW2")
# Set version number
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

if (BUILD_DBOW2_STANDALONE)
  
  message(STATUS "Building DBoW2 as a standalone project...")
  cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
  project(${project_name_},
          VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

  include(ExternalProject)

  option(BUILD_DBoW2   "Build DBoW2"            ON)
  option(BUILD_Demo    "Build demo application" ON)

  if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
      "MinSizeRel" "RelWithDebInfo")
  endif()

  if(MSVC)
    add_compile_options(/W4)
  else()
    add_compile_options(-Wall -Wextra -Wpedantic)
  endif()

  # Handle dependencies for standalone build
  set(DEPENDENCY_DIR ${CMAKE_CURRENT_BINARY_DIR}/dependencies)
  set(DEPENDENCY_INSTALL_DIR ${DEPENDENCY_DIR}/install)

  find_package(OpenCV REQUIRED)
  include_directories(${OpenCV_INCLUDE_DIRS})
else()
  message(STATUS "Building DBoW2 as library module...")

  set(BUILD_DBoW2 ON) # Set on to enable build
  set(BUILD_Demo ON) 

  # Check if OpenCV found, else find it
  if (NOT OpenCV_FOUND)
    find_package(OpenCV 4.2 REQUIRED)
  endif()

endif()

# Add header files
set(HDRS
  include/DBoW2/BowVector.h           include/DBoW2/FBrief.h
  include/DBoW2/QueryResults.h        include/DBoW2/TemplatedDatabase.h   include/DBoW2/FORB.h
  include/DBoW2/DBoW2.h               include/DBoW2/FClass.h              include/DBoW2/FeatureVector.h
  include/DBoW2/ScoringObject.h       include/DBoW2/TemplatedVocabulary.h)
  
# Add source files
set(SRCS 
  src/BowVector.cpp     
  src/FBrief.cpp        
  src/FORB.cpp
  src/FeatureVector.cpp 
  src/QueryResults.cpp  
  src/ScoringObject.cpp)

if(BUILD_DBoW2)

  set(LIB_TYPE "SHARED")
  if(WIN32)
    set(LIB_SHARED "STATIC")
  endif(WIN32)

  add_library(${project_name_} 
            ${LIB_TYPE} 
            ${SRCS})

  # Define include directories for the include library
  target_include_directories(${project_name_} PUBLIC 
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>  # Used during development
                            $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/${project_name_}>  # Used in installed projects
)

  target_link_libraries(${project_name_} ${OpenCV_LIBS})
  set_target_properties(${project_name_} PROPERTIES CXX_STANDARD 11)

endif(BUILD_DBoW2)

if(BUILD_Demo)

  add_executable(demo demo/demo.cpp)
  target_link_libraries(demo ${project_name_} ${OpenCV_LIBS})
  set_target_properties(demo PROPERTIES CXX_STANDARD 11)
  file(COPY demo/images DESTINATION ${CMAKE_BINARY_DIR}/)

endif(BUILD_Demo)

###### Configure install ########################################

# Install the target and headers
install(TARGETS ${project_name_}
  EXPORT ${project_name_} # Export target to be used by other projects
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#install(DIRECTORY include/ 
#        DESTINATION include)

#install(TARGETS ${project_name_} 
#        DESTINATION lib) # Install targets

#install(DIRECTORY include/DBoW2 
#        DESTINATION include) # Install headers

# Install the config file for cmake
#install(FILES "${CMAKE_CURRENT_BINARY_DIR}/DBoW2Config.cmake"
#  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${project_name_})

#install(FILES "${PROJECT_BINARY_DIR}/DBoW2Config.cmake" 
#  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/DBoW2/)

# Install dependency if standalone
#if (BUILD_DBOW2_STANDALONE)
#  install(DIRECTORY ${DEPENDENCY_INSTALL_DIR}/ 
#          DESTINATION ${CMAKE_INSTALL_PREFIX} OPTIONAL)
#endif()

# Generate Config + Version files
include(CMakePackageConfigHelpers)

# Copy cmake script to build directory
#configure_file(src/DBoW2.cmake.in
#  "${PROJECT_BINARY_DIR}/DBoW2Config.cmake" @ONLY)

# Install the exports and config files
install(EXPORT ${project_name_}
    FILE ${project_name_}Target.cmake
    NAMESPACE ${project_name_}::
    DESTINATION lib/cmake/${project_name_}
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${project_name_}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

# ${project_name_}Config.cmake.in should usually contain only:
#   include("${CMAKE_CURRENT_LIST_DIR}/${project_name_}Targets.cmake")
#   # optional: find_dependency(....)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/src/${project_name_}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${project_name_}Config.cmake"
  INSTALL_DESTINATION lib/cmake/${project_name_})

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${project_name_}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${project_name_}ConfigVersion.cmake"
  DESTINATION lib/cmake/${project_name_})

# Add target export to allow usage of build by other consumer projects
export(EXPORT ${project_name_}
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${project_name_}Target.cmake"
)