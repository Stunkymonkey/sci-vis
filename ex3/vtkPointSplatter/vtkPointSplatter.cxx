#include "vtkObjectFactory.h" //for new() macro
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkSmartPointer.h"
#include "vtkPolyData.h"
#include "vtkFloatArray.h"
#include "vtkDoubleArray.h"
#include "vtkCellData.h"
#include "vtkPointData.h"

#include "vtkPointSplatter.h"

vtkStandardNewMacro(vtkPointSplatter);

vtkPointSplatter::vtkPointSplatter(void) {
    this->SetNumberOfInputPorts(1);
    this->SetNumberOfOutputPorts(1);
}

vtkPointSplatter::~vtkPointSplatter(void) {
}

int vtkPointSplatter::FillInputPortInformation(int port, vtkInformation* info) {
    if (!this->Superclass::FillInputPortInformation(port, info)) {
        return 0;
    }
    if (port == 0) {
        info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkPolyData");
        return 1;
    }
    return 0;
}

int vtkPointSplatter::RequestUpdateExtent(vtkInformation * vtkNotUsed(request), vtkInformationVector ** inputVector, vtkInformationVector * outputVector) {
    return 1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

int vtkPointSplatter::RequestData(vtkInformation * vtkNotUsed(request), vtkInformationVector ** inputVector, vtkInformationVector * outputVector) {

    // retrieve pointers to input and output data
    auto inInfo = inputVector[0]->GetInformationObject(0);
    auto input = vtkPolyData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));

    auto outInfo = outputVector->GetInformationObject(0);
    auto output = vtkRectilinearGrid::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

    // retrieve bounding box, order: (xmin, xmax, ymin, ymax, zmin, zmax)
    std::array<double, 6> boundingBox;
    input->GetBounds(boundingBox.data());

    // TODO Calculate the measurements of the grid cells for each dimension
    //-----------------------------------------------------------------
    std::array<double, 3> cellWidths;

    cellWidths[0] = (boundingBox[1] - boundingBox[0]) / GridResolution[0];
    cellWidths[1] = (boundingBox[3] - boundingBox[2]) / GridResolution[1];
    cellWidths[2] = (boundingBox[5] - boundingBox[4]) / GridResolution[2];

    //-----------------------------------------------------------------
    // END of todo section

    // set the extent of the output
    std::array<int, 6> extent = { 0, GridResolution[0], 0, GridResolution[1], 0, GridResolution[2] };
    output->SetExtent(extent.data());

    auto xCoords = vtkSmartPointer<vtkDoubleArray>::New();
    auto yCoords = vtkSmartPointer<vtkDoubleArray>::New();
    auto zCoords = vtkSmartPointer<vtkDoubleArray>::New();

    xCoords->SetNumberOfComponents(1);
    yCoords->SetNumberOfComponents(1);
    zCoords->SetNumberOfComponents(1);

    // this describes the amount of cell border vertices for each direction, so it always has to 
    // be GridResolution + 1
    xCoords->SetNumberOfTuples(GridResolution[0] + 1);
    yCoords->SetNumberOfTuples(GridResolution[1] + 1);
    zCoords->SetNumberOfTuples(GridResolution[2] + 1);

    // TODO set the coordinates of the points describing the cell border vertices for each dimension seperately
    // this can be done for each single value using the ->SetComponent(<index>, 0, <coordinate>) method of the three fields
    //-------------------------------------------------------------------------------------------
    for (int x = 0; x <= GridResolution[0]; ++x) {
        // TODO set x-coordinate for the x-th vertex in x-direction
    	xCoords->SetComponent(x, 0, boundingBox[1] - (x * cellWidths[0]));
    }
    for (int y = 0; y <= GridResolution[1]; ++y) {
        // TODO set y-coordinate for the y-th vertex in y-direction
    	yCoords->SetComponent(y, 0, boundingBox[3] - (y * cellWidths[1]));
    }
    for (int z = 0; z <= GridResolution[2]; ++z) {
        // TODO set z-coordinate for the z-th vertex in z-direction
    	zCoords->SetComponent(z, 0, boundingBox[5] - (z * cellWidths[2]));
    }
    //-------------------------------------------------------------------------------------------
    // END of todo section

    output->SetXCoordinates(xCoords);
    output->SetYCoordinates(yCoords);
    output->SetZCoordinates(zCoords);
 
    // allocate storage for the cell values
    vtkSmartPointer<vtkFloatArray> splattedData = vtkSmartPointer<vtkFloatArray>::New();
    splattedData->Initialize();
    splattedData->SetName("Density");
    splattedData->SetNumberOfComponents(1);
    splattedData->SetNumberOfValues(GridResolution[0] * GridResolution[1] * GridResolution[2]);
    splattedData->FillValue(0.0f); // initialize the result array with zeros.

    // This sanity check throws an error in ParaView if the option "Keep Arrays" 
    // is not activated in the "Table to Points" Filter
    auto arrNum = input->GetPointData()->GetNumberOfArrays();
    if (arrNum != 4) return 0;

    // iterate over all input particles
    for (vtkIdType i = 0; i < input->GetNumberOfPoints(); ++i) {
        // retrieve the array values
        auto xCoord = input->GetPointData()->GetArray("xcoord")->GetTuple1(i);
        auto yCoord = input->GetPointData()->GetArray("ycoord")->GetTuple1(i);
        auto zCoord = input->GetPointData()->GetArray("zcoord")->GetTuple1(i);

        vtkIdType cellIdx;

        // TODO calculate the index of the currently viewed cell.
        // First, calculate the index for each dimension seperately, then retrieve the global vertex index value (cellIdx) from the result.
        // Finally, increment the value of the found cell in the splattedData field by 1. Hint: The methods "SetValue" and "GetValue" might be useful
        //-----------------------------------------------------------------------------------------------------------
        int xIndex = GridResolution[0] - ((xCoord - boundingBox[0]) / cellWidths[0]);
        int yIndex = GridResolution[1] - ((yCoord - boundingBox[2]) / cellWidths[1]);
        int zIndex = GridResolution[2] - ((zCoord - boundingBox[4]) / cellWidths[2]);

        cellIdx = xIndex + (yIndex * GridResolution[0]) + (zIndex * GridResolution[1] * GridResolution[0]);

        splattedData->SetValue(cellIdx, splattedData->GetValue(cellIdx) + 1.0f);
        //-----------------------------------------------------------------------------------------------------------
        // END of todo section
    }

    output->GetCellData()->AddArray(splattedData);
    return 1;
}
