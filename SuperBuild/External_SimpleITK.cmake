set(proj SimpleITK)
set(ep_common_cxx_flags "${CMAKE_CXX_FLAGS_INIT} ${ADDITIONAL_CXX_FLAGS}")

get_cmake_property( _varNames VARIABLES )

foreach (_varName ${_varNames})
  if(_varName MATCHES "^SimpleITK_" OR _varName MATCHES "^SITK_" )
    if (NOT _varName MATCHES "^SITK_LANGUAGES_VARS"
          AND
        NOT _varName MATCHES "^SimpleITK_VARS"
          AND
        NOT _varName MATCHES "^SimpleITK_USE_SYSTEM"
          AND
        NOT _varName MATCHES "^SimpleITK_.*_COMPILE_OPTIONS"
          AND
        NOT _varName MATCHES "^SITK_UNDEFINED_SYMBOLS_ALLOWED")
      message( STATUS "Passing variable \"${_varName}=${${_varName}}\" to SimpleElastix external project.")
      list(APPEND SimpleITK_VARS ${_varName})
    endif()
  elseif(_varName MATCHES "^BUILD_DOCUMENTS$"
       OR
         _varName MATCHES "^BUILD_DOXYGEN$"
       OR
         _varName MATCHES "^DOXYGEN_"
       OR
         _varName MATCHES "^CMAKE_DISABLE_FIND_PACKAGE_"
         )
    message( STATUS "Passing variable \"${_varName}=${${_varName}}\" to SimpleElastix external project.")
    list(APPEND SimpleITK_VARS ${_varName})
  elseif(_varName MATCHES "^PYTHON_")
    message( STATUS "Passing variable \"${_varName}=${${_varName}}\" to SimpleElastix external project.")
    list(APPEND SimpleITK_VARS ${_varName})
  endif()
endforeach()


list(APPEND SimpleITK_VARS ExternalData_OBJECT_STORES)

VariableListToCache( SimpleITK_VARS  ep_simpleitk_cache )
VariableListToArgs( SimpleITK_VARS  ep_simpleitk_args )
VariableListToCache( SITK_LANGUAGES_VARS  ep_languages_cache )
VariableListToArgs( SITK_LANGUAGES_VARS  ep_languages_args )

file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-build/CMakeCacheInit.txt" "${ep_simpleitk_cache}${ep_common_cache}\n${ep_languages_cache}" )

if(NOT DEFINED ${proj}_DIR AND NOT ${CMAKE_PROJECT_NAME}_USE_SYSTEM_${proj})

  if(NOT DEFINED git_protocol)
    set(git_protocol "git")
  endif()
  

  set(${proj}_INSTALL_DIR ${CMAKE_BINARY_DIR}/${proj}-install)
  set(${proj}_DIR ${CMAKE_BINARY_DIR}/${proj}-build)
  set(${proj}_RUNTIME_DIR ${CMAKE_BINARY_DIR}/${Slicer_THIRDPARTY_BIN_DIR})
  
  set(${proj}_cxx_flags "${ep_common_cxx_flags}")
  
  if (APPLE)
    set(${proj}_cxx_flags "${ep_common_cxx_flags} -Wno-inconsistent-missing-override")
  endif()

  ExternalProject_Add(${proj}
    # Slicer
    ${${proj}_EP_ARGS}
    SOURCE_DIR ${CMAKE_BINARY_DIR}/${proj}
    #SOURCE_SUBDIR src # requires CMake 3.7 or later
    BINARY_DIR ${proj}-build
    INSTALL_DIR ${${proj}_INSTALL_DIR}
    GIT_REPOSITORY "${git_protocol}://github.com/SimpleITK/SimpleITK.git"
    GIT_TAG "d6026bbd64eeca43b2c4f54703c361e917de105f"
    #--Patch step-------------
    PATCH_COMMAND ""
    #--Configure step-------------
    CMAKE_ARGS
      --no-warn-unused-cli
    -DCMAKE_TOOLCHAIN_FILE:FILEPATH=${CMAKE_TOOLCHAIN_FILE}
    -C "${CMAKE_CURRENT_BINARY_DIR}/SimpleITK-build/CMakeCacheInit.txt"
    ${ep_simpleitk_args}
    ${ep_common_args}
    -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DCMAKE_LIBRARY_OUTPUT_DIRECTORY:PATH=<BINARY_DIR>/lib
    -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY:PATH=<BINARY_DIR>/lib
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY:PATH=<BINARY_DIR>/bin
    -DCMAKE_BUNDLE_OUTPUT_DIRECTORY:PATH=<BINARY_DIR>/bin
    ${ep_languages_args}
    -DITK_DIR:PATH=${ITK_DIR}
    -DElastix_DIR:PATH=${Elastix_DIR}
    -DSWIG_DIR:PATH=${SWIG_DIR}
    -DSWIG_EXECUTABLE:PATH=${SWIG_EXECUTABLE}
    -DBUILD_TESTING:BOOL=${BUILD_TESTING}
    -DWRAP_LUA:BOOL=${WRAP_LUA}
    -DWRAP_PYTHON:BOOL=${WRAP_PYTHON}
    -DWRAP_RUBY:BOOL=${WRAP_RUBY}
    -DWRAP_JAVA:BOOL=${WRAP_JAVA}
    -DWRAP_TCL:BOOL=${WRAP_TCL}
    -DWRAP_CSHARP:BOOL=${WRAP_CSHARP}
    -DWRAP_R:BOOL=${WRAP_R}
    -DWRAP_NODE:BOOL=${WRAP_NODE}
    -DBUILD_EXAMPLES:BOOL=${BUILD_TESTING}
    #--Build step-----------------
    #--Install step-----------------
    INSTALL_COMMAND ""
    DEPENDS
      ${${CMAKE_PROJECT_NAME}_DEPENDENCIES}
    )
  #set(${proj}_DIR ${${proj}_INSTALL_DIR})
  #if(UNIX)
  #  set(${proj}_DIR ${${proj}_INSTALL_DIR}/share/elastix)
  #endif()
  
else()
  ExternalProject_Add_Empty(${proj} DEPENDS ${${proj}_DEPENDS})
endif()

ExternalProject_Get_Property( SimpleITK BINARY_DIR )
set( SimpleITK_DIR ${BINARY_DIR} )
