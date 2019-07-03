#ifndef __sitktransformconverterimpl_h_
#define __sitktransformconverterimpl_h_

#include "sitkTransformConverter.h"

#include "sitkCommon.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkDualMemberFunctionFactory.h"
#include "sitkTransform.h"

#include "itkParameterMapInterface.h"

#include "elxTransformixMain.h"
#include "elxComponentDatabase.h"
#include "elxComponentLoader.h"


/** \class TransformConverter
* \brief A class that will return itk base type transforms from a parameter map.
*/
namespace itk {
	namespace simple {
		class TransformConverter::TransformConverterImpl
		{
		public:
			TransformConverterImpl();
			~TransformConverterImpl();

			typedef TransformConverterImpl Self;

			typedef itk::Object             ObjectType;
			typedef ObjectType::Pointer     ObjectPointer;

			typedef std::string                                             ParameterKeyType;
			typedef std::string                                             ParameterValueType;
			typedef std::vector< ParameterValueType >                       ParameterValueVectorType;
			typedef ParameterValueVectorType::iterator                      ParameterValueVectorIterator;
			typedef std::map< ParameterKeyType, ParameterValueVectorType >  ParameterMapType;
			typedef std::vector< ParameterMapType >                         ParameterMapVectorType;
			typedef ParameterMapType::iterator                              ParameterMapIterator;
			typedef ParameterMapType::const_iterator                        ParameterMapConstIterator;


			typedef elastix::ElastixBase									ElastixBaseType;
			typedef elastix::TransformixMain								TransformixMainType;
			typedef TransformixMainType::Pointer							TransformixMainPointer;
			typedef ElastixBaseType::ConfigurationType						ConfigurationType;
			typedef ConfigurationType::CommandLineArgumentMapType			ArgumentMapType;
			typedef ArgumentMapType::value_type								ArgumentMapEntryType;
			typedef ConfigurationType::Pointer								ConfigurationPointer;
			typedef itk::TransformBase										itkTransformType;

			typedef elastix::ComponentDatabase								ComponentDataBaseType;
			typedef ComponentDataBaseType::Pointer							ComponentDataBasePointer;
			typedef elastix::ComponentLoader								ComponentLoaderType;
			typedef ComponentLoaderType::Pointer							ComponentLoaderPointer;
			typedef ComponentDataBaseType::PtrToCreator						PtrToCreator;

			void SetParameterMap(ParameterMapType parameterMap);
			
			Transform Execute();

			// Definitions for SimpleITK member factory
			typedef Transform(Self::*MemberFunctionType)(void);
			template< class TFixedImage, class TMovingImage > Transform DualExecuteInternal(void);
			friend struct detail::DualExecuteInternalAddressor< MemberFunctionType >;
			nsstd::auto_ptr< detail::DualMemberFunctionFactory< MemberFunctionType > > m_DualMemberFactory;
		
			ParameterMapType m_ParameterMap;
			ArgumentMapType m_DummyArgMap;
			ConfigurationPointer m_Configuration;
			ComponentDataBasePointer s_CDB;
			ComponentLoaderPointer s_ComponentLoader;
			
			std::string m_FixedImageTypeString;
			std::string m_MovingImageTypeString;
			unsigned int m_FixedImageDimension;
			unsigned int m_MovingImageDimension;
		};
	}
}


#endif // __sitktransformconverterimpl_h_