cmake_minimum_required (VERSION 3.19)

project ("Engine")

# Sources
file (GLOB_RECURSE SOURCES "Source/*.cpp")
file (GLOB_RECURSE HEADERS "Source/*.h")
file (GLOB_RECURSE VERTEX_SHADER "Source/Shaders/*.vert")
file (GLOB_RECURSE FRAGMENT_SHADER "Source/Shaders/*.frag")
file (GLOB_RECURSE HPP "Source/*.hpp")
add_executable (Engine ${SOURCES} ${HEADERS} ${VERTEX_SHADER} ${FRAGMENT_SHADER} ${HPP})

# Parcourir récursivement les sous-dossiers de Source pour les fichiers .cpp
file (GLOB_RECURSE SRC_LIST "*.cpp")
foreach(_source IN ITEMS ${SRC_LIST})
  get_filename_component(_source_path "${_source}" PATH)
  file (RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
  string (REPLACE "/" "\\" _group_path "${_source_path_rel}")
  source_group("${_group_path}" FILES "${_source}")
endforeach()

# Parcourir récursivement les sous-dossiers de Source pour les fichiers .h
file (GLOB_RECURSE HEADER_LIST "*.h")
foreach(_header IN ITEMS ${HEADER_LIST})
  get_filename_component(_header_path "${_header}" PATH)
  file (RELATIVE_PATH _header_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_header_path}")
  string (REPLACE "/" "\\" _group_path "${_header_path_rel}")
  source_group("${_group_path}" FILES "${_header}")
endforeach()

# Parcourir récursivement les sous-dossiers de Source/Shaders pour les fichiers .vert
file (GLOB_RECURSE VERT_SHADER_LIST "*.vert")
foreach(_vsShader IN ITEMS ${VERT_SHADER_LIST})
  get_filename_component(_vsShader_path "${_vsShader}" PATH)
  file (RELATIVE_PATH _vsShader_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/Source" "${_vsShader_path}")
  string (REPLACE "/" "\\" _group_path "${_vsShader_path_rel}")
  source_group("${_group_path}" FILES "${_vsShader}")
endforeach()

# Parcourir récursivement les sous-dossiers de Source/Shaders pour les fichiers .frag
file (GLOB_RECURSE FRAG_SHADER_LIST "*.frag")
foreach(_fsShader IN ITEMS ${FRAG_SHADER_LIST})
  get_filename_component(_fsShader_path "${_fsShader}" PATH)
  file (RELATIVE_PATH _fsShader_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/Source" "${_fsShader_path}")
  string (REPLACE "/" "\\" _group_path "${_fsShader_path_rel}")
  source_group("${_group_path}" FILES "${_fsShader}")
endforeach()

# Parcourir récursivement les sous-dossiers de Source/Shaders pour les fichiers .hpp
file (GLOB_RECURSE HPP_LIST "*.hpp")
foreach(_hpp IN ITEMS ${HPP_LIST})
  get_filename_component(_hpp_path "${_hpp}" PATH)
  file (RELATIVE_PATH _hpp_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_hpp_path}")
  string (REPLACE "/" "\\" _group_path "${_hpp_path_rel}")
  source_group("${_group_path}" FILES "${_hpp}")
endforeach()


# Find packages
find_package(OpenGL REQUIRED)

# Includes
include_directories(Dependencies/Includes)

# Libraries
set (ALL_LIBS
  ${OPENGL_LIBRARY}
  D:/LucienAxel/Github/ComUnity/Dependencies/Libraries/glfw3.lib
  D:/LucienAxel/Github/ComUnity/Dependencies/Libraries/GLEW_1130.lib
  D:/LucienAxel/Github/ComUnity/Dependencies/Libraries/assimp-vc143-mtd.lib
  D:/LucienAxel/Github/ComUnity/Dependencies/Libraries/zlibstaticd.lib
)

link_directories(Dependencies/Libraries)
target_link_libraries(Engine ${ALL_LIBS})

# Definitions
add_definitions(
  -DTW_STATIC
  -DTW_NO_LIB_PRAGMA
  -DTW_NO_DIRECT3D
  -DGLEW_STATIC
  -D_CRT_SECURE_NO_WARNINGS 
)

#####################################################################################

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()