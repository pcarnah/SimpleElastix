set( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )


add_library( ElastixImageFilter sitkPixelIDValuesElastix.cxx sitkElastixImageFilter.cxx sitkElastixImageFilterImpl.h sitkElastixImageFilterImpl.cxx sitkTransformConverter.cxx sitkTransformConverterImpl.h sitkTransformConverterImpl.cxx )
set_target_properties( ElastixImageFilter PROPERTIES SKIP_BUILD_RPATH TRUE )
target_link_libraries( ElastixImageFilter PUBLIC ${SimpleITK_LIBRARIES} )
target_include_directories( ElastixImageFilter PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Elastix/include>
	$<BUILD_INTERFACE:${SimpleITK_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include> )
target_link_libraries( ElastixImageFilter PUBLIC elastix )
sitk_install_exported_target( ElastixImageFilter )

add_library( TransformixImageFilter sitkPixelIDValuesElastix.cxx sitkTransformixImageFilter.cxx sitkTransformixImageFilterImpl.h  sitkTransformixImageFilterImpl.cxx )
set_target_properties( TransformixImageFilter PROPERTIES SKIP_BUILD_RPATH TRUE )
target_link_libraries( TransformixImageFilter PUBLIC ${SimpleITK_LIBRARIES} )
target_include_directories( TransformixImageFilter PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Elastix/include>
    $<INSTALL_INTERFACE:include> )
target_link_libraries( TransformixImageFilter PRIVATE transformix )
sitk_install_exported_target( TransformixImageFilter ) 

