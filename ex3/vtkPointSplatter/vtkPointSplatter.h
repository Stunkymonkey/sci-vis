#ifndef __vtkPointSplatter_h
#define __vtkPointSplatter_h

#include "vtkInformation.h"
#include "vtkRectilinearGridAlgorithm.h"
#include <array>

class vtkPointSplatter : public vtkRectilinearGridAlgorithm
{
public:
  static vtkPointSplatter *New();
  vtkTypeMacro(vtkPointSplatter, vtkRectilinearGridAlgorithm);
  vtkGetVector3Macro(GridResolution, int);
  vtkSetVector3Macro(GridResolution, int);

protected:
    vtkPointSplatter(void);
    virtual ~vtkPointSplatter(void);
  
    int FillInputPortInformation(int, vtkInformation*);

    int RequestUpdateExtent(vtkInformation*, vtkInformationVector **, vtkInformationVector*);

    int RequestData(vtkInformation*, vtkInformationVector **, vtkInformationVector*);
private:
    vtkPointSplatter(const vtkPointSplatter&);
    void operator=(const vtkPointSplatter&);

    int GridResolution[3];
};
#endif
