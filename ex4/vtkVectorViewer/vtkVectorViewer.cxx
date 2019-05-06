#include "vtkObjectFactory.h" //for new() macro
#include "vtkSmartPointer.h" //for newly created data array
#include "vtkFloatArray.h" //for newly created data array
#include "vtkPointData.h" //for GetPointData() getter
#include "vtkImageData.h" 
#include "vtkVectorViewer.h"
#include "vtkMath.h" //math functions

#include <iostream>

vtkStandardNewMacro(vtkVectorViewer);

void vtkVectorViewer::SimpleExecute(vtkImageData* input, vtkImageData* output) {
  output->DeepCopy(input);

  // TODO Allocate an array, name it, set the number of components and tuples.
  // Hint: http://www.vtk.org/doc/nightly/html/classvtkFloatArray.html
  // and: http://www.vtk.org/Wiki/VTK/Examples/Cxx/Utilities/KnownLengthArray
 

  switch(VectorProperty) {
  case 0: // velocity magnitude
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      
    }
    break;
  case 1: // x component
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      
    }
    break;
  case 2: // y component
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      
    }
    break;
  case 3: // z component
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      
    }
    break;
  case 4: // r
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      
    }
    break;
  case 5: // theta
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      
    }
    break;
  case 6: // phi
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      
    }
    break;
  };
  
  // TODO add the array content to the output
  // Hint: http://www.vtk.org/doc/nightly/html/classvtkImageData.html
  
}
