SimpleElastix Fork
======================
This fork of SimpleElastix aims to seperate the API of Elastix filters from SimpleITK to allow SimpleElastix to be built against and used with existing SimpleITK builds. Currently no SuperBuild exists for this fork so in order to build, you must already have ITK, SimpleITK and elastix built on your system and configure CMake to find these packages manually.

What is SimpleElastix?
======================
Image registration is the process of transforming images into a common coordinate system so corresponding pixels represent homologous biological points. SimpleElastix is an extension of [SimpleITK](https://github.com/SimpleITK/SimpleITK "SimpleITK github repository") that offers a user-friendly API to the popular image registration algorithms of the [elastix](http://elastix.isi.uu.nl/ "Elastix website") C++ library. This makes state-of-the-art medical image registration really easy to do in languages like Python, Java, C# and R. This package provides

- elastix and transformix bindings for C++, Python, Java, R, Ruby, Octave, Lua, Tcl and C# (see [elastix manual](http://elastix.isi.uu.nl/download/elastix_manual_v4.7.pdf "elastix manual") for a list of supported registration algorithms).
- Pre-configured registration methods that work well in many cases and serve as starting points for tuning elastix to domain-specific applications.

- A user-friendly API that aligns with the design philosophy of SimpleITK developed specifically for rapid prototyping. If you are interested, [The Design of SimpleITK](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3874546/ "PubMed") is a great read.
- The complete set of SimpleITK image processing algorithms.

Enough talk, time for some examples! We will use Python for the following code. Say you need to register two images. This can be accomplished with a single line of code:

```python
resultImage = SimpleITK.Elastix(sitk.ReadImage("fixedImage.dcm"), sitk.ReadImage("movingImage.dcm"))
```

Under the hood, Elastix will use stochastic optimization for maximum speed, a multi-resolution strategy and several different transforms of increasing complexity for maximum robustness. All aspects of the registration procedure can be customized via [parameter maps](https://simpleelastix.readthedocs.io/ParameterMaps.html). 

SimpleElastix can also be used for more complex image processing pipelines. Say you want to compare the volume, mean intensity and standard deviation of the intensity of anatomical structures across a population of images using an atlas segmentation. We can accomplish this task with the following lines of Python code:

```python
import SimpleITK as sitk
import SimpleElastix

# The atlas and associated segmentation is loaded once and held in memory
movingImage = sitk.ReadImage('atlasImage.hdr')
movingLabel = sitk.ReadImage('atlasLabel.hdr')

# Images are loaded from disk one at a time. Here we specify an array of 
# paths to images which we will loop over. 
population = ['image1.dcm', 'image2.dcm', ... , 'imageN.dcm']

selx = SimpleElastix.ElastixImageFilter()
selx.SetMovingImage(movingImage)
selx.SetParameterMap(selx.GetDefaultParameterMap('nonrigid'))

for filename in population
  # Register images
  fixedImage = sitk.ReadImage(filename)
  selx.SetFixedImage(fixedImage)
  selx.Execute()

  # Transform label map using the deformation field from above
  resultLabel = SimpleElastix.Transformix(movingLabel, selx.GetTransformParameterMap())

  # Compute statistics for label 1
  LabelStatistics = sitk.LabelStatisticsImageFilter()
  LabelStatistics.Execute(fixedImage, sitk.Cast(resultLabel, sitk.sitkInt8))
  LabelStatistics.GetCount(1)
  LabelStatistics.GetMean(1)
  LabelStatistics.GetVariance(1)
  # etc etc
```

This example demonstrates the efficiency of combining SimpleElastix's object oriented interface (the way we used elastix to register images) and procedural interface (the way we used transformix to warp labels) with SimpleITK (the way we computed statistics). Previously, using elastix and transformix on large datasets would incur a significant overhead, from scripting command line invocations and arguments to copying images and transform parameter files across folders. With SimpleElastix this complexity is easier to manage and more memory and disk I/O efficient. For more examples see [the documentation](https://simpleelastix.readthedocs.org/). 
