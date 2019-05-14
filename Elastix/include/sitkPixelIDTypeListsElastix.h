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
#ifndef sitkPixelIDTypeListsElastix_h
#define sitkPixelIDTypeListsElastix_h

#include <stdint.h>

#include "sitkConfigure.h"
#include "sitkPixelIDTypes.h"

#include "Ancillary/TypeList.h"

#include <complex>

namespace itk
{
namespace simple
{

/** SimpleElastix and SimpleTransformix is compiled with float pixel type only. This
 * saves compile time and reduces binary size. Images are automacially casted to and
 * from float before and after registration.
 */
typedef typelist::MakeTypeList< BasicPixelID< float > >::Type FloatPixelIDTypeList;

}
}
#endif // sitkPixelIDTypeListsElastix_h
