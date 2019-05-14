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
#if SWIGPYTHON

%begin %{
#include "sitkPython.h"
%}

%{
#include "sitkPyCommand.h"
%}

%include "PythonDocstrings.i"

// ignore overload methods of int type when there is an enum
%ignore itk::simple::CastImageFilter::SetOutputPixelType( PixelIDValueType pixelID );
%ignore itk::simple::GetPixelIDValueAsString( PixelIDValueType type );

// Make __str__ transparent by renaming ToString to __str__
%rename(__str__) ToString;

%rename( __GetPixelAsInt8__ ) itk::simple::Image::GetPixelAsInt8;
%rename( __GetPixelAsUInt8__ ) itk::simple::Image::GetPixelAsUInt8;
%rename( __GetPixelAsInt16__ ) itk::simple::Image::GetPixelAsInt16;
%rename( __GetPixelAsUInt16__ ) itk::simple::Image::GetPixelAsUInt16;
%rename( __GetPixelAsInt32__ ) itk::simple::Image::GetPixelAsInt32;
%rename( __GetPixelAsUInt32__ ) itk::simple::Image::GetPixelAsUInt32;
%rename( __GetPixelAsInt64__ ) itk::simple::Image::GetPixelAsInt64;
%rename( __GetPixelAsUInt64__ ) itk::simple::Image::GetPixelAsUInt64;
%rename( __GetPixelAsFloat__ ) itk::simple::Image::GetPixelAsFloat;
%rename( __GetPixelAsDouble__ ) itk::simple::Image::GetPixelAsDouble;
%rename( __GetPixelAsVectorInt8__ ) itk::simple::Image::GetPixelAsVectorInt8;
%rename( __GetPixelAsVectorUInt8__ ) itk::simple::Image::GetPixelAsVectorUInt8;
%rename( __GetPixelAsVectorInt16__ ) itk::simple::Image::GetPixelAsVectorInt16;
%rename( __GetPixelAsVectorUInt16__ ) itk::simple::Image::GetPixelAsVectorUInt16;
%rename( __GetPixelAsVectorInt32__ ) itk::simple::Image::GetPixelAsVectorInt32;
%rename( __GetPixelAsVectorUInt32__ ) itk::simple::Image::GetPixelAsVectorUInt32;
%rename( __GetPixelAsVectorInt64__ ) itk::simple::Image::GetPixelAsVectorInt64;
%rename( __GetPixelAsVectorUInt64__ ) itk::simple::Image::GetPixelAsVectorUInt64;
%rename( __GetPixelAsVectorFloat32__ ) itk::simple::Image::GetPixelAsVectorFloat32;
%rename( __GetPixelAsVectorFloat64__ ) itk::simple::Image::GetPixelAsVectorFloat64;
%rename( __GetPixelAsComplexFloat32__ ) itk::simple::Image::GetPixelAsComplexFloat32;
%rename( __GetPixelAsComplexFloat64__ ) itk::simple::Image::GetPixelAsComplextFloat64;

%rename( __SetPixelAsInt8__ ) itk::simple::Image::SetPixelAsInt8;
%rename( __SetPixelAsUInt8__ ) itk::simple::Image::SetPixelAsUInt8;
%rename( __SetPixelAsInt16__ ) itk::simple::Image::SetPixelAsInt16;
%rename( __SetPixelAsUInt16__ ) itk::simple::Image::SetPixelAsUInt16;
%rename( __SetPixelAsInt32__ ) itk::simple::Image::SetPixelAsInt32;
%rename( __SetPixelAsUInt32__ ) itk::simple::Image::SetPixelAsUInt32;
%rename( __SetPixelAsInt64__ ) itk::simple::Image::SetPixelAsInt64;
%rename( __SetPixelAsUInt64__ ) itk::simple::Image::SetPixelAsUInt64;
%rename( __SetPixelAsFloat__ ) itk::simple::Image::SetPixelAsFloat;
%rename( __SetPixelAsDouble__ ) itk::simple::Image::SetPixelAsDouble;
%rename( __SetPixelAsVectorInt8__ ) itk::simple::Image::SetPixelAsVectorInt8;
%rename( __SetPixelAsVectorUInt8__ ) itk::simple::Image::SetPixelAsVectorUInt8;
%rename( __SetPixelAsVectorInt16__ ) itk::simple::Image::SetPixelAsVectorInt16;
%rename( __SetPixelAsVectorUInt16__ ) itk::simple::Image::SetPixelAsVectorUInt16;
%rename( __SetPixelAsVectorInt32__ ) itk::simple::Image::SetPixelAsVectorInt32;
%rename( __SetPixelAsVectorUInt32__ ) itk::simple::Image::SetPixelAsVectorUInt32;
%rename( __SetPixelAsVectorInt64__ ) itk::simple::Image::SetPixelAsVectorInt64;
%rename( __SetPixelAsVectorUInt64__ ) itk::simple::Image::SetPixelAsVectorUInt64;
%rename( __SetPixelAsVectorFloat32__ ) itk::simple::Image::SetPixelAsVectorFloat32;
%rename( __SetPixelAsVectorFloat64__ ) itk::simple::Image::SetPixelAsVectorFloat64;
%rename( __SetPixelAsComplexFloat32__ ) itk::simple::Image::SetPixelAsComplexFloat32;
%rename( __SetPixelAsComplexFloat64__ ) itk::simple::Image::SetPixelAsComplextFloat64;

%pythoncode %{
   import operator
   import sys
%}


// This is included inline because SwigMethods (SimpleITKPYTHON_wrap.cxx)
// is declared static.
%{
#include "sitkNumpyArrayConversion.cxx"
%}
// Numpy array conversion support
%native(_GetMemoryViewFromImage) PyObject *sitk_GetMemoryViewFromImage( PyObject *self, PyObject *args );
%native(_SetImageFromArray) PyObject *sitk_SetImageFromArray( PyObject *self, PyObject *args );

%pythoncode %{

HAVE_NUMPY = True
try:
    import numpy
except ImportError:
    HAVE_NUMPY = False


def _get_numpy_dtype( sitkImage ):
    """Given a SimpleITK image, returns the numpy.dtype which describes the data"""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    # this is a mapping from sitk's pixel id to numpy's dtype
    _sitk_np = {sitkUInt8:numpy.uint8,
                sitkUInt16:numpy.uint16,
                sitkUInt32:numpy.uint32,
                sitkUInt64:numpy.uint64,
                sitkInt8:numpy.int8,
                sitkInt16:numpy.int16,
                sitkInt32:numpy.int32,
                sitkInt64:numpy.int64,
                sitkFloat32:numpy.float32,
                sitkFloat64:numpy.float64,
                sitkComplexFloat32:numpy.complex64,
                sitkComplexFloat64:numpy.complex128,
                sitkVectorUInt8:numpy.uint8,
                sitkVectorInt8:numpy.int8,
                sitkVectorUInt16:numpy.uint16,
                sitkVectorInt16:numpy.int16,
                sitkVectorUInt32:numpy.uint32,
                sitkVectorInt32:numpy.int32,
                sitkVectorUInt64:numpy.uint64,
                sitkVectorInt64:numpy.int64,
                sitkVectorFloat32:numpy.float32,
                sitkVectorFloat64:numpy.float64,
                sitkLabelUInt8:numpy.uint8,
                sitkLabelUInt16:numpy.uint16,
                sitkLabelUInt32:numpy.uint32,
                sitkLabelUInt64:numpy.uint64
                }

    return _sitk_np[ sitkImage.GetPixelIDValue() ]



def _get_sitk_pixelid(numpy_array_type):
    """Returns a SimpleITK PixelID given a numpy array."""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    # This is a Mapping from numpy array types to sitks pixel types.
    _np_sitk = {numpy.character:sitkUInt8,
                numpy.uint8:sitkUInt8,
                numpy.uint16:sitkUInt16,
                numpy.uint32:sitkUInt32,
                numpy.uint64:sitkUInt64,
                numpy.int8:sitkInt8,
                numpy.int16:sitkInt16,
                numpy.int32:sitkInt32,
                numpy.int64:sitkInt64,
                numpy.float32:sitkFloat32,
                numpy.float64:sitkFloat64,
                numpy.complex64:sitkComplexFloat32,
                numpy.complex128:sitkComplexFloat64
                }

    try:
        return _np_sitk[numpy_array_type.dtype]
    except KeyError:
        for key in _np_sitk:
            if numpy.issubdtype(numpy_array_type.dtype, key):
                return _np_sitk[key]
        raise TypeError('dtype: {0} is not supported.'.format(numpy_array_type.dtype))

def _get_sitk_vector_pixelid(numpy_array_type):
    """Returns a SimpleITK vecotr PixelID given a numpy array."""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    # This is a Mapping from numpy array types to sitks pixel types.
    _np_sitk = {numpy.character:sitkVectorUInt8,
                numpy.uint8:sitkVectorUInt8,
                numpy.uint16:sitkVectorUInt16,
                numpy.uint32:sitkVectorUInt32,
                numpy.uint64:sitkVectorUInt64,
                numpy.int8:sitkVectorInt8,
                numpy.int16:sitkVectorInt16,
                numpy.int32:sitkVectorInt32,
                numpy.int64:sitkVectorInt64,
                numpy.float32:sitkVectorFloat32,
                numpy.float64:sitkVectorFloat64,
                }

    try:
        return _np_sitk[numpy_array_type.dtype]
    except KeyError:
        for key in _np_sitk:
            if numpy.issubdtype(numpy_array_type.dtype, key):
                return _np_sitk[key]
        raise TypeError('dtype: {0} is not supported.'.format(numpy_array_type.dtype))


# SimplyITK <-> Numpy Array conversion support.

def GetArrayViewFromImage(image):
    """Get a NumPy ndarray view of a SimpleITK Image.

    Returns a Numpy ndarray object as a "view" of the SimpleITK's Image buffer. This reduces pixel buffer copies, but requires that the SimpleITK image object is kept around while the buffer is being used.


    """

    if not HAVE_NUMPY:
        raise ImportError('NumPy not available.')


    pixelID = image.GetPixelIDValue()
    assert pixelID != sitkUnknown, "An SimpleITK image of Unknown pixel type should not exists!"

    dtype = _get_numpy_dtype( image )

    shape = image.GetSize();
    if image.GetNumberOfComponentsPerPixel() > 1:
      shape = ( image.GetNumberOfComponentsPerPixel(), ) + shape

    image.MakeUnique()

    imageMemoryView =  _SimpleITK._GetMemoryViewFromImage(image)
    arrayView = numpy.asarray(imageMemoryView).view(dtype = dtype)
    arrayView.shape = shape[::-1]

    return arrayView

def GetArrayFromImage(image):
    """Get a NumPy ndarray from a SimpleITK Image.

    This is a deep copy of the image buffer and is completely safe and without potential side effects.
    """

    # TODO: If the image is already not unique then a second copy may be made before the numpy copy is done.
    arrayView = GetArrayViewFromImage(image)

    # perform deep copy of the image buffer
    return numpy.array(arrayView, copy=True)


def GetImageFromArray( arr, isVector=None):
    """Get a SimpleITK Image from a numpy array. If isVector is True, then the Image will have a Vector pixel type, and the last dimension of the array will be considered the component index. By default when isVector is None, 4D images are automatically considered 3D vector images."""

    if not HAVE_NUMPY:
        raise ImportError('Numpy not available.')

    z = numpy.asarray( arr )

    if isVector is None:
      if z.ndim == 4:
        isVector = True

    if isVector:
      id = _get_sitk_vector_pixelid( z )
      if z.ndim > 2:
        number_of_components = z.shape[-1]
        shape = z.shape[-2::-1]
      else:
        number_of_components = 1
        shape = z.shape[::-1]
    else:
      number_of_components = 1
      id = _get_sitk_pixelid( z )
      shape = z.shape[::-1]

    # SimpleITK throws an exception if the image dimension is not supported
    img = Image( shape, id, number_of_components )

    _SimpleITK._SetImageFromArray( z.tostring(), img )

    return img
%}



// Enable Python classes derived from Command Execute method to be
// called from C++
%feature("director") itk::simple::Command;

%extend itk::simple::ProcessObject {
 int AddCommand( itk::simple::EventEnum e, PyObject *obj )
 {
   if (!PyCallable_Check(obj))
     {
     return 0;
     }
   itk::simple::PyCommand *cmd = NULL;
   try
     {
       cmd = new itk::simple::PyCommand();
       cmd->SetCallbackPyCallable(obj);
       int ret = self->AddCommand(e,*cmd);
       cmd->OwnedByProcessObjectsOn();
       return ret;
     }
   catch(...)
     {
       delete cmd;
       throw;
     }
 }
};

#endif
