
foreach(p
    CMP0042 # CMake 3.0
    CMP0063 # CMake 3.3.2
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()


# Add individual cxx executables
add_executable ( elx elx.cxx )
target_link_libraries ( elx ${SimpleElastix_LIBRARIES} ${SimpleITK_LIBRARIES} )

add_executable ( tfx tfx.cxx )
target_link_libraries ( tfx ${SimpleElastix_LIBRARIES} ${SimpleITK_LIBRARIES})

# Add subdirectories
add_subdirectory(ITKIntegration)

# Test data directory
set(TEST_HARNESS_TEMP_DIRECTORY ${SimpleElastix_BINARY_DIR}/Testing/Temporary)


macro(add_language_subdirectory lang)
  string(TOUPPER ${lang} LANG)
  if ( WRAP_${LANG} )
    add_subdirectory(${lang})
  endif()
endmacro()

add_language_subdirectory( CSharp )
add_language_subdirectory( Python )


