#ifndef __sitkmultiimageregistration_h_
#define __sitkmultiimageregistration_h_

// SimpleITK
#include "sitkDualMemberFunctionFactory.h"
#include "sitkImage.h"
#include "sitkImageFilter.h"
#include "sitkMemberFunctionFactory.h"

namespace itk {
namespace simple {

class SITKBasicFilters_EXPORT MultiImageRegistration
{
  public:
    MultiImageRegistration(void);
    ~MultiImageRegistration(void);

    typedef MultiImageRegistration Self;

    typedef std::vector<Image> VectorOfImage;
    using FloatPixelIDTypeList =
      typelist::MakeTypeList<BasicPixelID<float>>::Type;

    const std::string GetName(void);

    void SetFixedImage(const Image& fixedImage);
    void SetFixedImage(const VectorOfImage& fixedImages);
    void AddFixedImage(const Image& fixedImage);
    Image& GetFixedImage(const unsigned long index);
    VectorOfImage& GetFixedImage(void);
    void RemoveFixedImage(const unsigned long index);
    void RemoveFixedImage(void);
    unsigned int GetNumberOfFixedImages();

    void SetMovingImage(const Image& movingImages);
    void SetMovingImage(const VectorOfImage& movingImage);
    void AddMovingImage(const Image& movingImage);
    Image& GetMovingImage(const unsigned long index);
    VectorOfImage& GetMovingImage(void);
    void RemoveMovingImage(const unsigned long index);
    void RemoveMovingImage(void);
    unsigned int GetNumberOfMovingImages();

    void SetFixedMask(const Image& fixedMask);
    void SetFixedMask(const VectorOfImage& fixedMasks);
    void AddFixedMask(const Image& fixedMask);
    Image& GetFixedMask(const unsigned long index);
    VectorOfImage& GetFixedMask(void);
    void RemoveFixedMask(const unsigned long index);
    void RemoveFixedMask(void);
    unsigned int GetNumberOfFixedMasks();

    void SetMovingMask(const Image& movingMask);
    void SetMovingMask(const VectorOfImage& movingMasks);
    void AddMovingMask(const Image& movingMask);
    Image& GetMovingMask(const unsigned long index);
    VectorOfImage& GetMovingMask(void);
    void RemoveMovingMask(const unsigned long index);
    void RemoveMovingMask(void);
    unsigned int GetNumberOfMovingMasks();

    void SetNumberOfThreads(int n);
    int GetNumberOfThreads(void);

    Image Execute(void);

    Image GetResultImage(void);

    bool IsEmpty(const Image& image);

    // Definitions for SimpleITK member factory
    typedef Image (Self::*MemberFunctionType)(void);
    template<class TFixedImage, class TMovingImage>
    Image DualExecuteInternal(void);
    friend struct detail::DualExecuteInternalAddressor<MemberFunctionType>;
    nsstd::auto_ptr<detail::DualMemberFunctionFactory<MemberFunctionType>>
      m_DualMemberFactory;

    VectorOfImage m_FixedImages;
    VectorOfImage m_MovingImages;
    VectorOfImage m_FixedMasks;
    VectorOfImage m_MovingMasks;
    Image m_ResultImage;

    int m_NumberOfThreads;
};

} // end namespace simple
} // end namespace itk

#endif // __sitkmultiimageregistration_h_
