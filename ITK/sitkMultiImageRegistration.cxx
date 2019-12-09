#ifndef __sitkelastiximagefilterimpl_cxx_
#define __sitkelastiximagefilterimpl_cxx_

#include "sitkMultiImageRegistration.h"
#include "MultiMetricMultiResolutionRegistration\itkCombinationImageToImageMetric.h"
#include "MultiMetricMultiResolutionRegistration\itkMultiMetricMultiResolutionImageRegistrationMethod.h"
#include "itkNormalizedCorrelationImageToImageMetric.h"
#include "itkRecursiveMultiResolutionPyramidImageFilter.h"

namespace itk {
namespace simple {

MultiImageRegistration ::MultiImageRegistration(void)
{
    // Register this class with SimpleITK
    this->m_DualMemberFactory.reset(
      new detail::DualMemberFunctionFactory<MemberFunctionType>(this));
    this->m_DualMemberFactory->RegisterMemberFunctions<FloatPixelIDTypeList,
                                                       FloatPixelIDTypeList,
                                                       3>();

    this->m_FixedImages = VectorOfImage();
    this->m_MovingImages = VectorOfImage();
    this->m_FixedMasks = VectorOfImage();
    this->m_MovingMasks = VectorOfImage();
    this->m_ResultImage = Image();

    // Use all available threads by default
    this->m_NumberOfThreads = 0;
}

MultiImageRegistration::~MultiImageRegistration(void) {}

Image
MultiImageRegistration ::Execute(void)
{
    if (this->GetNumberOfFixedImages() == 0) {
        sitkExceptionMacro("Fixed image not set.");
    }

    if (this->GetNumberOfMovingImages() == 0) {
        sitkExceptionMacro("Moving image not set.");
    }

    const PixelIDValueEnum FixedImagePixelID =
      this->GetFixedImage(0).GetPixelID();
    const unsigned int FixedImageDimension =
      this->GetFixedImage(0).GetDimension();
    const PixelIDValueEnum MovingImagePixelID =
      this->GetMovingImage(0).GetPixelID();
    const unsigned int MovingImageDimension =
      this->GetMovingImage(0).GetDimension();

    for (unsigned int i = 1; i < this->GetNumberOfFixedImages(); ++i) {
        if (this->GetFixedImage(i).GetDimension() != FixedImageDimension) {
            sitkExceptionMacro(
              "Fixed images must be of same dimension (fixed image at index 0 "
              "is of dimension "
              << this->GetFixedImage(0).GetDimension()
              << ", fixed image at index " << i << " is of dimension \""
              << this->GetFixedImage(i).GetDimension() << "\").");
        }
    }

    for (unsigned int i = 1; i < this->GetNumberOfMovingImages(); ++i) {
        if (this->GetMovingImage(i).GetDimension() != FixedImageDimension) {
            sitkExceptionMacro(
              "Moving images must be of same dimension as fixed images (fixed "
              "image at index 0 is of dimension "
              << this->GetFixedImage(0).GetDimension()
              << ", moving image at index " << i << " is of dimension \""
              << this->GetMovingImage(i).GetDimension() << "\").");
        }
    }

    if (this->GetNumberOfFixedMasks() != 0 &&
        this->GetNumberOfFixedMasks() != 1 &&
        this->GetNumberOfFixedMasks() != this->GetNumberOfFixedImages()) {
        sitkExceptionMacro("Number of fixed masks must be 0, 1 or "
                           << this->GetNumberOfFixedImages()
                           << " (the number of fixed images).")
    }

    if (this->GetNumberOfMovingMasks() != 0 &&
        this->GetNumberOfMovingMasks() != 1 &&
        this->GetNumberOfMovingMasks() != this->GetNumberOfMovingImages()) {
        sitkExceptionMacro("Number of moving masks must be 0, 1 or "
                           << this->GetNumberOfMovingImages()
                           << " (the number of moving images).")
    }

    for (unsigned int i = 0; i < this->GetNumberOfFixedMasks(); ++i) {
        if (this->GetFixedMask(i).GetPixelID() != sitkUInt8) {
            sitkExceptionMacro(
              "Fixed mask must be of pixel type sitkUInt8 but fixed mask "
              << i << " is of type \""
              << GetPixelIDValueAsString(this->GetFixedMask(i).GetPixelID())
              << "\". Cast with `SimpleITK.Cast(mask, sitk.sitkUInt8)`.");
        }

        if (this->GetFixedMask(i).GetDimension() != FixedImageDimension) {
            sitkExceptionMacro(
              "Fixed masks must be of same dimension as fixed images (fixed "
              "images are of dimension "
              << this->GetFixedImage(0).GetDimension()
              << ", fixed mask at index " << i << " is of dimension \""
              << this->GetFixedMask(i).GetDimension() << "\").");
        }

        if (this->GetFixedMask(i).GetOrigin() !=
            this->GetFixedImage(i).GetOrigin()) {
            sitkExceptionMacro("Fixed masks must have same origins as fixed "
                               "images (fixed image at index 0 has origin at "
                               << this->GetFixedImage(i).GetOrigin()
                               << ", fixed mask at index " << i
                               << " has origin at  \""
                               << this->GetFixedMask(i).GetOrigin() << "\").");
        }

        if (this->GetFixedMask(i).GetDirection() !=
            this->GetFixedImage(i).GetDirection()) {
            sitkExceptionMacro(
              "Fixed masks must have same direction cosines as fixed images "
              "(fixed image at index "
              << i << " has direction cosine "
              << this->GetFixedImage(i).GetDirection()
              << ", fixed mask at index " << i << " has direction cosine \""
              << this->GetFixedMask(i).GetDirection() << "\").");
        }

        if (this->GetFixedMask(i).GetSpacing() !=
            this->GetFixedImage(i).GetSpacing()) {
            sitkExceptionMacro(
              "Fixed masks must have same spacing as fixed images (fixed image "
              "at index "
              << i << " has spacing " << this->GetFixedImage(i).GetSpacing()
              << ", fixed mask at index " << i << " has spacing  \""
              << this->GetFixedMask(i).GetSpacing() << "\").");
        }
    }

    for (unsigned int i = 0; i < this->GetNumberOfMovingMasks(); ++i) {
        if (this->GetMovingMask(i).GetPixelID() != sitkUInt8) {
            sitkExceptionMacro(
              "Moving mask must be of pixel type sitkUInt8 but moving mask "
              << i << " is of type \""
              << GetPixelIDValueAsString(this->GetFixedMask(i).GetPixelID())
              << "\". Cast with `SimpleITK.Cast(mask, sitk.sitkUInt8)`.");
        }

        if (this->GetMovingMask(i).GetDimension() != MovingImageDimension) {
            sitkExceptionMacro(
              "Moving masks must be of same dimension as moving images (moving "
              "images are of dimension "
              << this->GetMovingImage(0).GetDimension()
              << ", moving mask at index " << i << " is of dimension \""
              << this->GetMovingMask(i).GetDimension() << "\").");
        }

        if (this->GetMovingMask(i).GetOrigin() !=
            this->GetMovingImage(i).GetOrigin()) {
            sitkExceptionMacro(
              "Moving masks must have same origins as moving images (moving "
              "image at index "
              << i << " has origin " << this->GetMovingImage(i).GetOrigin()
              << ", moving mask at index " << i << " has origin \""
              << this->GetMovingMask(i).GetOrigin() << "\").");
        }

        if (this->GetMovingMask(i).GetDirection() !=
            this->GetMovingImage(i).GetDirection()) {
            sitkExceptionMacro(
              "Moving masks must have same direction cosines as moving images "
              "(moving image at index "
              << i << " has direction cosine "
              << this->GetMovingImage(i).GetDirection()
              << ", moving mask at index " << i << " has direction cosine \""
              << this->GetMovingMask(i).GetDirection() << "\").");
        }

        if (this->GetMovingMask(i).GetSpacing() !=
            this->GetMovingImage(i).GetSpacing()) {
            sitkExceptionMacro(
              "Moving masks must have same spacing as moving images (moving "
              "image at index "
              << i << " has spacing " << this->GetMovingImage(i).GetSpacing()
              << ", moving mask at index " << i << " has spacing  \""
              << this->GetMovingMask(i).GetSpacing() << "\").");
        }
    }

    if (this->m_DualMemberFactory->HasMemberFunction(
          sitkFloat32, sitkFloat32, FixedImageDimension)) {
        return this->m_DualMemberFactory->GetMemberFunction(
          sitkFloat32, sitkFloat32, FixedImageDimension)();
    }

    sitkExceptionMacro(
      << "MultiImageRegistration does not support the combination of "
      << FixedImageDimension << "-dimensional "
      << GetPixelIDValueAsString(FixedImagePixelID) << " fixed image and a "
      << MovingImageDimension << "-dimensional "
      << GetPixelIDValueAsString(MovingImagePixelID) << " moving image. ")
}

// Modify this to directly use itkMultiMetric registration
template<typename TFixedImage, typename TMovingImage>
Image
MultiImageRegistration::DualExecuteInternal(void)
{
    using RegMethodType =
      itk::MultiMetricMultiResolutionImageRegistrationMethod<TFixedImage,
                                                             TMovingImage>;
    using RegMethodPointer = typename RegMethodType::Pointer;
    using FixedMaskType = itk::Image<unsigned char, 3>;
    using MovingMaskType = itk::Image<unsigned char, 3>;
    using MetricType =
      itk::NormalizedCorrelationImageToImageMetric<TFixedImage, TMovingImage>;
    using MetricPointer = typename MetricType::Pointer;
    using FixedPyramidType =
      itk::RecursiveMultiResolutionPyramidImageFilter<TFixedImage, TFixedImage>;

    try {
        RegMethodPointer regMethod = RegMethodType::New();

        regMethod->GetCombinationMetric()->SetNumberOfMetrics(
          this->m_FixedImages.size());

        // Create metric for each fixed image
        for (int i = 0; i < this->m_FixedImages.size(); i++) {
            // Needs image sampler as well
            MetricPointer metric = MetricType::New();
            regMethod->GetCombinationMetric()->SetMetric(metric.GetPointer(),
                                                         i);

            regMethod->SetFixedImage(itkDynamicCastInDebugMode<TFixedImage*>(
                                       this->m_FixedImages[i].GetITKBase()),
                                     i);

            FixedPyramidType::Pointer pyramid = FixedPyramidType::New();
            regMethod->SetFixedImagePyramid(pyramid, i);
        }

        for (int i = 0; i < this->m_MovingImages.size(); i++) {
            regMethod->SetMovingImage(itkDynamicCastInDebugMode<TMovingImage*>(
                                        this->m_MovingImages[i].GetITKBase()),
                                      i);
        }

    } catch (itk::ExceptionObject& e) {
        sitkExceptionMacro(<< e);
    }

    return this->m_ResultImage;
}

const std::string
MultiImageRegistration::GetName(void)
{
    const std::string name = "MultiImageRegistration";
    return name;
}

void
MultiImageRegistration::SetFixedImage(const Image& fixedImage)
{
    if (this->IsEmpty(fixedImage)) {
        sitkExceptionMacro("Image is empty.")
    }

    this->RemoveFixedImage();
    this->m_FixedImages.push_back(fixedImage);
}

void
MultiImageRegistration::SetFixedImage(const VectorOfImage& fixedImages)
{
    if (fixedImages.size() == 0u) {
        sitkExceptionMacro("Cannot set fixed images from empty vector");
    }

    this->RemoveFixedImage();
    this->m_FixedImages = fixedImages;
}

void
MultiImageRegistration::AddFixedImage(const Image& fixedImage)
{
    if (this->IsEmpty(fixedImage)) {
        sitkExceptionMacro("Image is empty.")
    }

    this->m_FixedImages.push_back(fixedImage);
}

Image&
MultiImageRegistration::GetFixedImage(const unsigned long index)
{
    if (index < this->m_FixedImages.size()) {
        return this->m_FixedImages[index];
    }

    sitkExceptionMacro("Index out of range (index: "
                       << index << ", number of fixed images: "
                       << this->m_FixedImages.size() << ")");
}

MultiImageRegistration::VectorOfImage&
MultiImageRegistration ::GetFixedImage(void)
{
    return this->m_FixedImages;
}

void
MultiImageRegistration ::RemoveFixedImage(const unsigned long index)
{
    if (index < this->m_FixedImages.size()) {
        this->m_FixedImages.erase(this->m_FixedImages.begin() + index);
    }

    sitkExceptionMacro("Index out of range (index: "
                       << index << ", number of fixed images: "
                       << this->m_FixedImages.size() << ")");
}

void
MultiImageRegistration ::RemoveFixedImage(void)
{
    this->m_FixedImages.clear();
}

unsigned int
MultiImageRegistration ::GetNumberOfFixedImages(void)
{
    return this->m_FixedImages.size();
}

void
MultiImageRegistration::SetMovingImage(const Image& movingImage)
{
    if (this->IsEmpty(movingImage)) {
        sitkExceptionMacro("Image is empty.")
    }

    this->RemoveMovingImage();
    this->m_MovingImages.push_back(movingImage);
}

void
MultiImageRegistration ::SetMovingImage(const VectorOfImage& movingImages)
{
    if (movingImages.size() == 0u) {
        sitkExceptionMacro("Cannot set moving images from empty vector");
    }

    this->RemoveMovingImage();
    this->m_MovingImages = movingImages;
}

void
MultiImageRegistration ::AddMovingImage(const Image& movingImage)
{
    if (this->IsEmpty(movingImage)) {
        sitkExceptionMacro("Image is empty.")
    }

    this->m_MovingImages.push_back(movingImage);
}

Image&
MultiImageRegistration ::GetMovingImage(const unsigned long index)
{
    if (index < this->m_MovingImages.size()) {
        return this->m_MovingImages[index];
    }

    sitkExceptionMacro("Index out of range (index: "
                       << index << ", number of moving images: "
                       << this->m_MovingImages.size() << ")");
}

MultiImageRegistration::VectorOfImage&
MultiImageRegistration ::GetMovingImage(void)
{
    return this->m_MovingImages;
}

void
MultiImageRegistration ::RemoveMovingImage(const unsigned long index)
{
    if (index < this->m_MovingImages.size()) {
        this->m_MovingImages.erase(this->m_MovingImages.begin() + index);
    }

    sitkExceptionMacro("Index out of range (index: "
                       << index << ", number of moving images: "
                       << this->m_MovingImages.size() << ")");
}

void
MultiImageRegistration ::RemoveMovingImage(void)
{
    this->m_MovingImages.clear();
}

unsigned int
MultiImageRegistration ::GetNumberOfMovingImages(void)
{
    return this->m_MovingImages.size();
}

void
MultiImageRegistration ::SetFixedMask(const Image& fixedMask)
{
    if (this->IsEmpty(fixedMask)) {
        sitkExceptionMacro("Image is empty.")
    }

    this->RemoveFixedMask();
    this->m_FixedMasks.push_back(fixedMask);
}

void
MultiImageRegistration ::SetFixedMask(const VectorOfImage& fixedMasks)
{
    if (fixedMasks.size() == 0u) {
        sitkExceptionMacro("Cannot set fixed images from empty vector");
    }

    this->RemoveFixedMask();
    this->m_FixedMasks = fixedMasks;
}

void
MultiImageRegistration ::AddFixedMask(const Image& fixedMask)
{
    if (this->IsEmpty(fixedMask)) {
        sitkExceptionMacro("Image is empty.")
    }

    this->m_FixedMasks.push_back(fixedMask);
}

Image&
MultiImageRegistration ::GetFixedMask(const unsigned long index)
{
    if (index < this->m_FixedMasks.size()) {
        return this->m_FixedMasks[index];
    }

    sitkExceptionMacro("Index out of range (index: "
                       << index << ", number of fixed masks: "
                       << this->m_FixedMasks.size() << ")");
}

MultiImageRegistration::VectorOfImage&
MultiImageRegistration ::GetFixedMask(void)
{
    return this->m_FixedMasks;
}

void
MultiImageRegistration ::RemoveFixedMask(const unsigned long index)
{
    if (index < this->m_FixedMasks.size()) {
        this->m_FixedMasks.erase(this->m_FixedMasks.begin() + index);
    }

    sitkExceptionMacro("Index out of range (index: "
                       << index << ", number of fixed masks: "
                       << this->m_FixedMasks.size() << ")");
}

void
MultiImageRegistration ::RemoveFixedMask(void)
{
    this->m_FixedMasks.clear();
}

unsigned int
MultiImageRegistration ::GetNumberOfFixedMasks(void)
{
    return this->m_FixedMasks.size();
}

void
MultiImageRegistration ::SetMovingMask(const Image& movingMask)
{
    if (this->IsEmpty(movingMask)) {
        sitkExceptionMacro("Image is empty.")
    }

    this->RemoveMovingMask();
    this->m_MovingMasks.push_back(movingMask);
}

void
MultiImageRegistration ::SetMovingMask(const VectorOfImage& movingMasks)
{
    if (movingMasks.size() == 0u) {
        sitkExceptionMacro("Cannot set moving masks from empty vector");
    }

    this->RemoveMovingMask();
    this->m_MovingMasks = movingMasks;
}

void
MultiImageRegistration ::AddMovingMask(const Image& movingMask)
{
    if (this->IsEmpty(movingMask)) {
        sitkExceptionMacro("Image is empty.")
    }

    this->m_MovingMasks.push_back(movingMask);
}

Image&
MultiImageRegistration ::GetMovingMask(const unsigned long index)
{
    if (index < this->m_MovingMasks.size()) {
        return this->m_MovingMasks[index];
    }

    sitkExceptionMacro("Index out of range (index: "
                       << index << ", number of moving masks: "
                       << this->m_MovingMasks.size() << ")");
}

MultiImageRegistration::VectorOfImage&
MultiImageRegistration::GetMovingMask(void)
{
    return this->m_MovingMasks;
}

void
MultiImageRegistration::RemoveMovingMask(const unsigned long index)
{
    if (index < this->m_MovingMasks.size()) {
        this->m_MovingMasks.erase(this->m_MovingMasks.begin() + index);
    }

    sitkExceptionMacro("Index out of range (index: "
                       << index << ", number of moving masks: "
                       << this->m_MovingMasks.size() << ")");
}

void
MultiImageRegistration ::RemoveMovingMask(void)
{
    this->m_MovingMasks.clear();
}

unsigned int
MultiImageRegistration ::GetNumberOfMovingMasks(void)
{
    return this->m_MovingMasks.size();
}

void
MultiImageRegistration ::SetNumberOfThreads(int n)
{
    this->m_NumberOfThreads = n;
}

int
MultiImageRegistration ::GetNumberOfThreads()
{
    return this->m_NumberOfThreads;
}

bool
MultiImageRegistration ::IsEmpty(const Image& image)
{
    const bool isEmpty = image.GetWidth() == 0 && image.GetHeight() == 0;
    return isEmpty;
}

} // end namespace simple
} // end namespace itk

#endif // __sitkelastiximagefilterimpl_cxx_
