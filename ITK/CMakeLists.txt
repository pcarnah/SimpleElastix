set( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )

add_library( sitkMultiImageRegistration sitkMultiImageRegistration.cxx sitkMultiImageRegistration.h )
set_target_properties( sitkMultiImageRegistration PROPERTIES SKIP_BUILD_RPATH TRUE )
target_link_libraries( sitkMultiImageRegistration PUBLIC ${SimpleITK_LIBRARIES} ${ITK_LIBRARIES} )
target_include_directories( sitkMultiImageRegistration PUBLIC
	$<BUILD_INTERFACE:${SimpleITK_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include> )
#target_link_libraries( sitkMultiImageRegistration PUBLIC elastix )
sitk_install_exported_target( sitkMultiImageRegistration )
