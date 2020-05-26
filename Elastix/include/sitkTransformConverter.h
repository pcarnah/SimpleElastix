#ifndef __sitktransformconverter_h_
#define __sitktransformconverter_h_

#include "sitkCommon.h"
#include "sitkTransform.h"
#include <map>


/** \class TransformConverter
* \brief A class that will return itk base type transforms from a parameter map.
*/
namespace itk {
	namespace simple {
		class SITKCommon_EXPORT TransformConverter
		{
		public:
			TransformConverter();
			~TransformConverter();

			typedef std::string                                             ParameterKeyType;
			typedef std::string                                             ParameterValueType;
			typedef std::vector< ParameterValueType >                       ParameterValueVectorType;
			typedef ParameterValueVectorType::iterator                      ParameterValueVectorIterator;
			typedef std::map< ParameterKeyType, ParameterValueVectorType >  ParameterMapType;
			typedef std::vector< ParameterMapType >                         ParameterMapVectorType;
			typedef ParameterMapType::iterator                              ParameterMapIterator;
			typedef ParameterMapType::const_iterator                        ParameterMapConstIterator;

			TransformConverter& SetParameterMap(ParameterMapType parameterMap);
			
			Transform Execute();

		private:
			class TransformConverterImpl;
			TransformConverterImpl* m_Pimple;
		};
	}
}


#endif // __sitktransformconverter_h_