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
#include "sitkPixelIDValues.h"
#include "sitkPixelIDValuesElastix.h"

namespace itk
{
namespace simple
{

const std::string GetPixelIDValueAsElastixParameter( PixelIDValueType type )
{

  if ( type == sitkUnknown )
    {
    // Unknow must be first because other enums may be -1 if they are
    // not instantiated
    return "Unknown pixel id";
    }
  else if ( type == sitkUInt8 )
    {
    return "unsigned char";
    }
  else if ( type == sitkInt8 )
    {
    return "char";
   }
  else if ( type ==  sitkUInt16 )
    {
    return "unsigned short";
    }
  else if ( type == sitkInt16 )
    {
    return "short";
    }
  else if ( type == sitkUInt32 )
    {
    return "unsigned int";
    }
  else if ( type == sitkInt32 )
    {
   return "int";
    }
   else if ( type == sitkUInt64 )
    {
    return "unsigned long";
    }
  else if ( type == sitkInt64 )
    {
    return "long";
    }
  else if ( type == sitkFloat32 )
    {
    return "float";
    }
  else if ( type == sitkFloat64 )
    {
    return "double";
    }
  else
    {
    return "Unsupported pixel type.";
    }

}


PixelIDValueType GetPixelIDValueFromElastixString(const std::string &enumString)
{

	if (enumString == "sitkUnknown")
	{
		// Unknow must be first because other enums may be -1 if they are
		// not instantiated
		return sitkUnknown;
	}
	else if (enumString == "unsigned char")
	{
		return sitkUInt8;
	}
	else if (enumString == "char")
	{
		return sitkInt8;
	}
	else if (enumString == "unsigned short")
	{
		return sitkUInt16;
	}
	else if (enumString == "short")
	{
		return sitkInt16;
	}
	else if (enumString == "unsigned int")
	{
		return sitkUInt32;
	}
	else if (enumString == "int")
	{
		return sitkInt32;
	}
	else if (enumString == "float")
	{
		return sitkFloat32;
	}
	else if (enumString == "double")
	{
		return sitkFloat64;
	}
	else
	{
		return -99;
	}
}



}
}
