#ifndef __sitktransformiximagefilter_cxx_
#define __sitktransformiximagefilter_cxx_

#include "sitkTransformixImageFilter.h"
#include "sitkTransformixImageFilterImpl.h"

namespace itk {
  namespace simple {

TransformixImageFilter
::TransformixImageFilter( void ) : m_Pimple( new TransformixImageFilterImpl )
{
}

TransformixImageFilter
::~TransformixImageFilter( void )
{
  delete m_Pimple;
  m_Pimple = NULL;
}

const std::string 
TransformixImageFilter
::GetName( void )
{ 
  return this->m_Pimple->GetName();
}

TransformixImageFilter::Self&
TransformixImageFilter
::SetMovingImage( const Image& movingImage )
{
  this->m_Pimple->SetMovingImage( movingImage );
  return *this;
}

Image&
TransformixImageFilter
::GetMovingImage( void )
{
  return this->m_Pimple->GetMovingImage();
}

TransformixImageFilter::Self&
TransformixImageFilter
::RemoveMovingImage( void )
{
  this->m_Pimple->RemoveMovingImage();
  return *this;
}

TransformixImageFilter::Self& 
TransformixImageFilter
::SetFixedPointSetFileName( const std::string movingPointSetFileName )
{
  this->m_Pimple->SetFixedPointSetFileName( movingPointSetFileName );
  return *this;
}

std::string 
TransformixImageFilter
::GetFixedPointSetFileName( void )
{
  return this->m_Pimple->GetFixedPointSetFileName();
}

TransformixImageFilter::Self&
TransformixImageFilter
::RemoveFixedPointSetFileName( void )
{
  this->m_Pimple->RemoveFixedPointSetFileName();
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::SetComputeSpatialJacobian( const bool computeSpatialJacobian )
{
  this->m_Pimple->SetComputeSpatialJacobian( computeSpatialJacobian );
  return *this;
}

bool 
TransformixImageFilter
::GetComputeSpatialJacobian( void )
{
  return this->m_Pimple->GetComputeSpatialJacobian();
}

TransformixImageFilter::Self&
TransformixImageFilter
::ComputeSpatialJacobianOn( void )
{
  this->m_Pimple->SetComputeSpatialJacobian( true );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::ComputeSpatialJacobianOff( void )
{
  this->m_Pimple->SetComputeSpatialJacobian( false );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::SetComputeDeterminantOfSpatialJacobian( const bool computeDeterminantOfSpatialJacobian )
{
  this->m_Pimple->SetComputeDeterminantOfSpatialJacobian( computeDeterminantOfSpatialJacobian );
  return *this;
}

bool 
TransformixImageFilter
::GetComputeDeterminantOfSpatialJacobian( void )
{
  return this->m_Pimple->GetComputeDeterminantOfSpatialJacobian();
}

TransformixImageFilter::Self&
TransformixImageFilter
::ComputeDeterminantOfSpatialJacobianOn( void )
{
  this->m_Pimple->SetComputeDeterminantOfSpatialJacobian( true );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::ComputeDeterminantOfSpatialJacobianOff( void )
{
  this->m_Pimple->SetComputeDeterminantOfSpatialJacobian( false );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::SetComputeDeformationField( const bool computeDeformationField )
{
  this->m_Pimple->SetComputeDeformationField( computeDeformationField );
  return *this;
}

bool
TransformixImageFilter
::GetComputeDeformationField( void )
{
  return this->m_Pimple->GetComputeDeformationField();
}

TransformixImageFilter::Self&
TransformixImageFilter
::ComputeDeformationFieldOn( void )
{
  this->m_Pimple->SetComputeDeformationField( true );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::ComputeDeformationFieldOff( void )
{
  this->m_Pimple->SetComputeDeformationField( false );
  return *this;
}

TransformixImageFilter::Self& 
TransformixImageFilter
::SetOutputDirectory( const std::string outputDirectory )
{
  this->m_Pimple->SetOutputDirectory( outputDirectory );
  return *this;
}

std::string
TransformixImageFilter
::GetOutputDirectory( void )
{
  return this->m_Pimple->GetOutputDirectory();
}

TransformixImageFilter::Self& 
TransformixImageFilter
::RemoveOutputDirectory( void )
{
  this->m_Pimple->RemoveOutputDirectory();
  return *this;
}

TransformixImageFilter::Self& 
TransformixImageFilter
::SetLogFileName( std::string logFileName )
{
  this->m_Pimple->SetLogFileName( logFileName );
  return *this;
}

std::string
TransformixImageFilter
::GetLogFileName( void )
{
  return this->m_Pimple->GetLogFileName();
}

TransformixImageFilter::Self& 
TransformixImageFilter
::RemoveLogFileName( void )
{
  this->m_Pimple->RemoveLogFileName();
  return *this;
}

TransformixImageFilter::Self& 
TransformixImageFilter
::SetLogToFile( bool logToFile )
{
  this->m_Pimple->SetLogToFile( logToFile );
  return *this;
}

bool
TransformixImageFilter
::GetLogToFile( void )
{
  return this->m_Pimple->GetLogToFile();
}

TransformixImageFilter::Self& 
TransformixImageFilter
::LogToFileOn()
{
  this->m_Pimple->SetLogToFile( true );
  return *this;
}

TransformixImageFilter::Self& 
TransformixImageFilter
::LogToFileOff()
{
  this->m_Pimple->SetLogToFile( false );
  return *this;
}

TransformixImageFilter::Self& 
TransformixImageFilter
::SetLogToConsole( bool logToConsole )
{
  this->m_Pimple->SetLogToConsole( logToConsole );
  return *this;
}

bool
TransformixImageFilter
::GetLogToConsole( void )
{
  return this->m_Pimple->GetLogToConsole();
}

TransformixImageFilter::Self& 
TransformixImageFilter
::LogToConsoleOn()
{
  this->m_Pimple->SetLogToConsole( true );
  return *this;
}

TransformixImageFilter::Self& 
TransformixImageFilter
::LogToConsoleOff()
{
  this->m_Pimple->SetLogToConsole( false );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::SetTransformParameterMap( const ParameterMapVectorType transformParameterMapVector )
{
  this->m_Pimple->SetTransformParameterMap( transformParameterMapVector );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::SetTransformParameterMap( const ParameterMapType transformParameterMap )
{
  this->m_Pimple->SetTransformParameterMap( transformParameterMap );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::AddTransformParameterMap( const ParameterMapType transformParameterMap )
{
  this->m_Pimple->AddTransformParameterMap( transformParameterMap );
  return *this;
}

TransformixImageFilter::ParameterMapVectorType
TransformixImageFilter
::GetTransformParameterMap( void )
{
  return this->m_Pimple->GetTransformParameterMap();
}

unsigned int
TransformixImageFilter
::GetNumberOfTransformParameterMaps( void )
{
  return this->m_Pimple->GetNumberOfTransformParameterMaps();
}

TransformixImageFilter::Self&
TransformixImageFilter
::SetTransformParameter( const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->SetTransformParameter( key, value );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::SetTransformParameter( const ParameterKeyType key, const ParameterValueVectorType value )
{
  this->m_Pimple->SetTransformParameter( key, value );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::SetTransformParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->SetTransformParameter( index, key, value );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::SetTransformParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueVectorType value )
{
  this->m_Pimple->SetTransformParameter( index, key, value );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::AddTransformParameter( const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->AddTransformParameter( key, value );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::AddTransformParameter( const unsigned int index, const ParameterKeyType key, const ParameterValueType value )
{
  this->m_Pimple->AddTransformParameter( index, key, value );
  return *this;
}

TransformixImageFilter::ParameterValueVectorType
TransformixImageFilter
::GetTransformParameter( const ParameterKeyType key )
{
  return this->m_Pimple->GetTransformParameter( key );
}

TransformixImageFilter::ParameterValueVectorType
TransformixImageFilter
::GetTransformParameter( const unsigned int index, const ParameterKeyType key )
{
  return this->m_Pimple->GetTransformParameter( index, key );
}

TransformixImageFilter::Self&
TransformixImageFilter
::RemoveTransformParameter( const ParameterKeyType key )
{
  this->m_Pimple->RemoveTransformParameter( key );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::RemoveTransformParameter( const unsigned int index, const ParameterKeyType key )
{
  this->m_Pimple->RemoveTransformParameter( index, key );
  return *this;
}

TransformixImageFilter::ParameterMapType 
TransformixImageFilter
::ReadParameterFile( const std::string parameterFileName )
{
  return this->m_Pimple->ReadParameterFile( parameterFileName );
}

TransformixImageFilter::Self&
TransformixImageFilter
::WriteParameterFile( const ParameterMapType parameterMap, const std::string parameterFileName )
{
  this->m_Pimple->WriteParameterFile( parameterMap, parameterFileName );
  return *this;
}

TransformixImageFilter::Self&
TransformixImageFilter
::PrintParameterMap( void )
{
  this->m_Pimple->PrintParameterMap();
  return *this;
}

TransformixImageFilter::Self& 
TransformixImageFilter
::PrintParameterMap( const ParameterMapType parameterMap )
{
  this->m_Pimple->PrintParameterMap( parameterMap );
  return *this;
}

TransformixImageFilter::Self& 
TransformixImageFilter
::PrintParameterMap( const ParameterMapVectorType parameterMapVector )
{
  this->m_Pimple->PrintParameterMap( parameterMapVector );
  return *this;
}

Image
TransformixImageFilter
::Execute( void )
{
  return this->m_Pimple->Execute();
}

Image
TransformixImageFilter
::GetResultImage( void )
{
  return this->m_Pimple->GetResultImage();
}

/**
 * Procedural interface 
 */

Image
Transformix( const Image& movingImage, const TransformixImageFilter::ParameterMapType parameterMap, const bool logToConsole, const std::string outputDirectory )
{
  TransformixImageFilter::ParameterMapVectorType parameterMapVector;
  parameterMapVector.push_back( parameterMap );
  return Transformix( movingImage, parameterMapVector, logToConsole, outputDirectory );
}

Image
Transformix( const Image& movingImage, const TransformixImageFilter::ParameterMapVectorType parameterMapVector, const bool logToConsole, const std::string outputDirectory )
{
  TransformixImageFilter stfx;
  stfx.SetMovingImage( movingImage );
  stfx.SetTransformParameterMap( parameterMapVector );
  stfx.SetOutputDirectory( outputDirectory );
  stfx.LogToFileOn();
  stfx.SetLogToConsole( logToConsole );

  return stfx.Execute();
}

} // end namespace simple
} // end namespace itk

#endif // __sitktransformiximagefilter_cxx_