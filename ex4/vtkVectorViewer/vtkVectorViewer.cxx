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

  vtkSmartPointer<vtkFloatArray> foo = vtkSmartPointer<vtkFloatArray>::New();
  foo->SetName("VeryImportantName");
  foo->SetNumberOfTuples(1);
  foo->SetNumberOfComponents(1);

  vtkDataArray* data = input->GetPointData()->GetScalars();

  switch(VectorProperty) {
  case 0: // velocity magnitude
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      // absolute of vector
      double* scalar = data->GetTuple(i);
      double mag = std::sqrt(vtkMath::Dot(scalar, scalar));
      foo->InsertTuple(i, &mag);
    }
    break;
  case 1: // x component
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      double* scalar = data->GetTuple(i);
      foo->InsertTuple(i, &scalar[0]);
    }
    break;
  case 2: // y component
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      double* scalar = data->GetTuple(i);
      foo->InsertTuple(i, &scalar[1]);
    }
    break;
  case 3: // z component
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      double* scalar = data->GetTuple(i);
      foo->InsertTuple(i, &scalar[2]);
    }
    break;
  case 4: // r
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      double* scalar = data->GetTuple(i);
      double mag = std::sqrt(vtkMath::Dot(scalar, scalar));
      foo->InsertTuple(i, &mag);
    }
    break;
  case 5: // theta
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      double* scalar = data->GetTuple(i);
      double r = atan(scalar[1]/scalar[0]);
      foo->InsertTuple(i, &r);
    }
    break;
  case 6: // phi
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      double* scalar = data->GetTuple(i);
      double r = std::sqrt(vtkMath::Dot(scalar, scalar));
      double phi = acos(scalar[2]/r);
      foo->InsertTuple(i, &phi);
    }
    break;
  };
  
  // TODO add the array content to the output
  // Hint: http://www.vtk.org/doc/nightly/html/classvtkImageData.html
  output->GetPointData()->SetScalars(foo);
}
