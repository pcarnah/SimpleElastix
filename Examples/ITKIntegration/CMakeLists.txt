set( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )

add_executable ( ElastixFilter ElastixFilter.cxx )
target_link_libraries( ElastixFilter ${ELASTIX_LIBRARIES} ${ITK_LIBRARIES} )

add_executable ( TransformixFilter TransformixFilter.cxx )
target_link_libraries( TransformixFilter ${ELASTIX_LIBRARIES} ${ITK_LIBRARIES} )
