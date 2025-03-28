cmake_minimum_required (VERSION 3.19)

# Set the path to vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/Dependencies/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project ("ComUnity")

# Sources
file (GLOB_RECURSE SOURCES "Source/*.cpp")
file (GLOB_RECURSE HEADERS "Source/*.h")
file (GLOB_RECURSE HPP "Source/*.hpp") #todo remove
file (GLOB_RECURSE VERTEX_SHADER "Source/Shaders/*.vert")
file (GLOB_RECURSE FRAGMENT_SHADER "Source/Shaders/*.frag")
add_executable (ComUnity ${SOURCES} ${HEADERS} ${HPP} ${VERTEX_SHADER} ${FRAGMENT_SHADER})

# Parcourir récursivement les sous-dossiers de Source pour les fichiers .cpp
file(GLOB_RECURSE SRC_LIST "Source/*.cpp")
foreach(_source IN ITEMS ${SRC_LIST})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

# Parcourir récursivement les sous-dossiers de Source pour les fichiers .h
file(GLOB_RECURSE HEADER_LIST "Source/*.h")
foreach(_header IN ITEMS ${HEADER_LIST})
    get_filename_component(_header_path "${_header}" PATH)
    file(RELATIVE_PATH _header_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_header_path}")
    string(REPLACE "/" "\\" _group_path "${_header_path_rel}")
    source_group("${_group_path}" FILES "${_header}")
endforeach()

# Parcourir récursivement les sous-dossiers de Source pour les fichiers .hpp
file(GLOB_RECURSE HPP_LIST "Source/*.hpp")
foreach(_hpp IN ITEMS ${HPP_LIST})
    get_filename_component(_hpp_path "${_hpp}" PATH)
    file(RELATIVE_PATH _hpp_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_hpp_path}")
    string(REPLACE "/" "\\" _group_path "${_hpp_path_rel}")
    source_group("${_group_path}" FILES "${_hpp}")
endforeach()

# Parcourir récursivement les sous-dossiers de Shaders pour les fichiers .vs
file(GLOB_RECURSE VS_SHADER_LIST "Source/*.vert")
foreach(_vsShader IN ITEMS ${VS_SHADER_LIST})
    get_filename_component(_vsShader_path "${_vsShader}" PATH)
    file(RELATIVE_PATH _vsShader_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/Source" "${_vsShader_path}")
    string(REPLACE "/" "\\" _group_path "${_vsShader_path_rel}")
    source_group("${_group_path}" FILES "${_vsShader}")
endforeach()

# Parcourir récursivement les sous-dossiers de Shaders pour les fichiers .fs
file(GLOB_RECURSE FS_SHADER_LIST "Source/*.frag")
foreach(_fsShader IN ITEMS ${FS_SHADER_LIST})
    get_filename_component(_fsShader_path "${_fsShader}" PATH)
    file(RELATIVE_PATH _fsShader_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/Source" "${_fsShader_path}")
    string(REPLACE "/" "\\" _group_path "${_fsShader_path_rel}")
    source_group("${_group_path}" FILES "${_fsShader}")
endforeach()

#####################################################################################

# Dependencies
set(DEPENDENCIES "${CMAKE_SOURCE_DIR}/Dependencies")

# GLFW
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(ComUnity PRIVATE glfw)

# GLEW
find_package(GLEW REQUIRED)
target_link_libraries(ComUnity PRIVATE GLEW::GLEW)

# FMT
find_package(fmt CONFIG REQUIRED)
target_link_libraries(ComUnity PRIVATE fmt::fmt)

# Assimp
find_package(assimp CONFIG REQUIRED)
target_link_libraries(ComUnity PRIVATE assimp::assimp)

# ImGUI
#find_package(imgui CONFIG REQUIRED)
#target_link_libraries(ComUnity PRIVATE imgui::imgui)

# GLM
find_package(glm CONFIG REQUIRED)
target_link_libraries(ComUnity PRIVATE glm::glm)

# Includes
set(INCLUDES 

    #ReactPhysic3D
    "${DEPENDENCIES}/reactphysics3d/include" 

    #IrrKlang
    "${DEPENDENCIES}/IrrKlang/include"
)
target_include_directories(ComUnity PRIVATE ${INCLUDES})

# Libraries
set(LIBRARIES_DIR "${DEPENDENCIES}/Libraries")
file(GLOB_RECURSE STATIC_LIBRARIES "${LIBRARIES_DIR}/Statics/*.lib")
target_link_libraries(ComUnity PRIVATE ${STATIC_LIBRARIES})
message(STATUS "Libraries found: ${STATIC_LIBRARIES}")

# DLLs
set(DYNAMIC_LIBRARIES "${LIBRARIES_DIR}/Dynamics/")

add_custom_command(TARGET ComUnity POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${DYNAMIC_LIBRARIES}
        $<TARGET_FILE_DIR:ComUnity>)

#####################################################################################

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ComUnity PROPERTY CXX_STANDARD 20)
endif()

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()