# Usage:
#
#   Pipeline:
#     TODO: SynSource needs pipeline description
#
#   Parameters:
#     TODO: SynSource needs parameter description
#
#   Contribution :
#     TODO: SynSource needs contributor mention
#
#   Author:
#     TODO: SynSource needs author mention



#--------------------------------------------------
cmake_minimum_required(VERSION 2.8)

IF (ParaView_SOURCE_DIR)
  INCLUDE_DIRECTORIES(
    ${VTK_INCLUDE_DIRS}
  )
ELSE (ParaView_SOURCE_DIR)
  FIND_PACKAGE(ParaView REQUIRED)
  INCLUDE(${PARAVIEW_USE_FILE})
ENDIF (ParaView_SOURCE_DIR)

ADD_PARAVIEW_PLUGIN(PointSplatter "0.1"
  SERVER_MANAGER_XML PointSplatter.xml
  SERVER_MANAGER_SOURCES vtkPointSplatter.cxx
)