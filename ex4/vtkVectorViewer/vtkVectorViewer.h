#ifndef __vtkVectorViewer_h
#define __vtkVectorViewer_h

#include "vtkSimpleImageToImageFilter.h" //superclass: just creates input and output objects for the image data

class vtkVectorViewer : public vtkSimpleImageToImageFilter
{
 public:
  static vtkVectorViewer *New();
  vtkTypeMacro(vtkVectorViewer, vtkSimpleImageToImageFilter);
  
  // TODO add the get and set macros for VectorProperty
  // Hint: http://www.vtk.org/Wiki/VTK/Examples/Developers/Macros
  void SetVectorProperty(int index) { VectorProperty = index; }
  int GetVectorProperty() { return VectorProperty; }
  
  void SimpleExecute(vtkImageData*, vtkImageData*);
 protected:
 private:
  int VectorProperty = 0;
};
#endif
