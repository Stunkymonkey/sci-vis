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
  foo->SetNumberOfComponents(3);
  foo->SetNumberOfValues(1);
  foo->SetNumberOfTuples(input->GetNumberOfPoints());

  switch(VectorProperty) {
  case 0: // velocity magnitude
    for(vtkIdType i=0; i<input->GetNumberOfPoints(); i++) {
      // TODO read the relevant values from the input, compute the wanted value and write it to the created array
      // absolute of vector
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
      double result [3];
      input->GetPoint(i, result);
      //std::cout << result[0] << ":" << result[1] << ":" << result[2] << std::endl;

      double velo [3];
      //input->GetPointData(i, velo);
      vtkPointData* data = input->GetPointData();
      auto asd = input->GetScalarPointer();
      float* pixel = static_cast<float*>(asd);
      /*std::cout << pixel[0] << std::endl;
      std::cout << pixel[1] << std::endl;
      std::cout << pixel[2] << std::endl;*/

      /*float* pixel = static_cast<float*>(input->GetScalarPointer(result));
      pixel[0] = 1.0;
      pixel[1] = 2.0;
      */

      //vtkCell* asdf = input->GetCell(i);
      //std::cout << asdf->GetNumberOfPoints() << std::endl;


      //std::cout << data->GetNumberOfArrays() << std::endl;
      //std::cout << array << std::endl;
      //std::cout << input->GetPointData()->GetScalars()->GetName() << std::endl;
      //std::cout << velo[0] << ":" << velo[1] << ":" << velo[2] << std::endl;

      foo->SetTuple3(i, result[0], result[1], result[2]);
      foo->SetValue(i, vtkMath::Random(0.0,2.0));
      //foo->InsertTuple (vtkIdType dstTupleIdx, vtkIdType srcTupleIdx);
      //foo->SetComponent (vtkIdType tupleIdx, int compIdx, double value);
      //result[2];
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
  output->GetPointData()->SetScalars(foo);
}
