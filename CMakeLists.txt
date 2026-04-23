# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("AssociationGraph")

# Include sub-projects.
file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(child ${children})
    # Check if it's a directory and has its own CMakeLists.txt
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child} AND 
       EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${child}/CMakeLists.txt)
        add_subdirectory(${child})
    endif()
endforeach()
