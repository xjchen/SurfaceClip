/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

#ifndef __qSlicerSurfaceClipModuleWidget_h
#define __qSlicerSurfaceClipModuleWidget_h

//	SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"
#include <qSlicerApplication.h>
#include "qSlicerSurfaceClipModuleExport.h"

//	Qt includes
#include "QPlane.h"

//	vtk includes
#include <vtkClipPolyData.h>
#include <vtkImplicitBoolean.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPlane.h>
#include <vtkPlaneCollection.h>
#include "vtkPlaneExtend.h"
#include <vtkPlaneWidget.h>
#include "vtkPlaneWidgetSub.h"
#include <vtkPlaneSource.h>
#include <vtkPolyData.h>

#include <vtkPolyLine.h>

class qSlicerSurfaceClipModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_SURFACECLIP_EXPORT qSlicerSurfaceClipModuleWidget : 
	public qSlicerAbstractModuleWidget
{
	Q_OBJECT

public:
	typedef qSlicerAbstractModuleWidget Superclass;
	qSlicerSurfaceClipModuleWidget(QWidget *parent=0);
	virtual ~qSlicerSurfaceClipModuleWidget();

public slots:

protected:
	vtkRenderWindowInteractor* iren;
	vtkRenderWindow* renderWindow;
	vtkRenderer* renderer;
	vtkSmartPointer<vtkPlaneWidgetSub> planeWidget;
	vtkSmartPointer<vtkPlaneExtend> planeExtend;
  vtkSmartPointer<vtkPlaneWidget> depthPlane;

	vtkSmartPointer<vtkClipPolyData> clipper;
	vtkSmartPointer<vtkPolyData> sourcePD;

	QList<QPlane *> planeList;
	QList<vtkSmartPointer<vtkImplicitBoolean> > angleList;
	QList<vtkSmartPointer<vtkImplicitBoolean> > bodyList;
	QList<vtkSmartPointer<vtkPolyData> > resultList;
	QList<vtkSmartPointer<vtkPolyData> > clippedList;
	int numOfPlanes;
	int timeOfClip;
  bool isClipped;

	QScopedPointer<qSlicerSurfaceClipModuleWidgetPrivate> d_ptr;
	virtual void setup();

protected slots:
	void createPlane();
	void appendPlane();
	void removePlane();
	void hideSurface();
	void deleteSurface();
  void setDepth();
	void clip();

private:
	Q_DECLARE_PRIVATE(qSlicerSurfaceClipModuleWidget);
	Q_DISABLE_COPY(qSlicerSurfaceClipModuleWidget);

	double* getPoint3(int);
	double* makePoint2(int);
	double* lengthen(int);
	double dotProduct(int);
	double dotProduct(int, int);
	bool isInter(int);
  void clearBodyList();
  vtkSmartPointer<vtkImplicitBoolean> makeAngle(int);
  vtkSmartPointer<vtkImplicitBoolean> makeAngle(int, int);
	vtkSmartPointer<vtkImplicitBoolean> makeBody(int);
  vtkSmartPointer<vtkImplicitBoolean> makeBody(int, int);
  vtkSmartPointer<vtkImplicitBoolean> withDepth(vtkSmartPointer<vtkImplicitFunction>);
};

#endif
