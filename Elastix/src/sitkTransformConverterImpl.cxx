/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#include "elxIncludes.h"
#include "elxElastixTemplate.h"
#include "elxTransformBase.h"

#include "sitkTransformConverterImpl.h"
#include "sitkPixelIDValues.h"
#include "sitkPixelIDValuesElastix.h"

#include "itkExceptionObject.h"
#include "itkTransformBase.h"

namespace itk {
	namespace simple {

		TransformConverter::TransformConverterImpl::
			TransformConverterImpl()
		{

			// Register this class with SimpleITK
			this->m_DualMemberFactory.reset(new detail::DualMemberFunctionFactory< MemberFunctionType >(this));
			this->m_DualMemberFactory->RegisterMemberFunctions< FloatPixelIDTypeList, FloatPixelIDTypeList, 2 >();
			this->m_DualMemberFactory->RegisterMemberFunctions< FloatPixelIDTypeList, FloatPixelIDTypeList, 3 >();

			this->m_DummyArgMap.insert( ArgumentMapEntryType("-def", "all") );
			this->m_DummyArgMap.insert(ArgumentMapEntryType("-out", "output_path_not_set"));

			// Setup xout
			if (elx::xoutSetup("SimpleElastix.log", false, false))
			{
				sitkExceptionMacro("Error while setting up xout");
			}

			this->m_Configuration = ConfigurationType::New();
			this->m_Configuration->Initialize(this->m_DummyArgMap, this->m_ParameterMap);

			this->s_CDB = ComponentDataBaseType::New();

			this->s_ComponentLoader = ComponentLoaderType::New();
			this->s_ComponentLoader->SetComponentDatabase(this->s_CDB);
			
			this->s_ComponentLoader->LoadComponents("");
			
		}

		TransformConverter::TransformConverterImpl::
			~TransformConverterImpl()
		{
		}

		Transform
			TransformConverter::TransformConverterImpl::
			Execute()
		{			
			
			this->m_Configuration->ReadParameter(m_FixedImageTypeString, "FixedInternalImagePixelType", 0);

			this->m_Configuration->ReadParameter(m_MovingImageTypeString, "MovingInternalImagePixelType", 0);

			m_FixedImageDimension = 3;
			this->m_Configuration->ReadParameter(m_FixedImageDimension, "FixedImageDimension", 0);

			m_MovingImageDimension = 3;
			this->m_Configuration->ReadParameter(m_MovingImageDimension, "MovingImageDimension", 0);

			PixelIDValueType FixedImageType = GetPixelIDValueFromElastixString(m_FixedImageTypeString);
			PixelIDValueType MovingImageType = GetPixelIDValueFromElastixString(m_MovingImageTypeString);

			if (this->m_DualMemberFactory->HasMemberFunction(FixedImageType, MovingImageType, m_FixedImageDimension))
			{
				return this->m_DualMemberFactory->GetMemberFunction(FixedImageType, MovingImageType, m_FixedImageDimension)();
			}
		}

		void TransformConverter::TransformConverterImpl::
			SetParameterMap(ParameterMapType parameterMap)
		{
			this->m_ParameterMap = parameterMap;

			this->m_Configuration->Initialize(this->m_DummyArgMap, this->m_ParameterMap);
		}

		template< typename TFixedImage, typename TMovingImage >
		Transform
			TransformConverter::TransformConverterImpl
			::DualExecuteInternal(void)
		{
			typedef elastix::ElastixTemplate<TFixedImage, TMovingImage> elxTemplate;
			typedef elastix::TransformBase<elxTemplate>					elxTransformBase;
			
			unsigned int DBIndex = this->s_CDB->GetIndex(
				this->m_FixedImageTypeString,
				this->m_FixedImageDimension,
				this->m_MovingImageTypeString,
				this->m_MovingImageDimension
			);

			std::string transformName = "AffineTransform";
			this->m_Configuration->ReadParameter(transformName, "Transform", 0);

			/** A pointer to the New() function. */
			PtrToCreator  testcreator = 0;
			testcreator = this->s_CDB->GetCreator(transformName, DBIndex);

			// Note that ObjectPointer() yields a default-constructed SmartPointer (null).
			ObjectPointer testpointer = testcreator ? testcreator() : ObjectPointer();

			if (testpointer.IsNull())
			{
				sitkExceptionMacro(<< "The following component could not be created: " << transformName);
			}

			elxTransformBase* transform = dynamic_cast<elxTransformBase*>(testpointer.GetPointer());
			transform->SetConfiguration(this->m_Configuration);
			transform->ReadFromFile();



			return Transform(transform->GetAsITKBaseType());
		}


	}
}