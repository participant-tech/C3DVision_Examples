#include <qt_vision.h>
#include <vsn_last.h>
#include <action_solid.h>
#include <vector>

using namespace VSN;
using namespace QtVision;
using namespace std;

int main(int argc, char** argv)
{
    auto app = QtApplication::createApplication(argc, argv, "T1");
    if (!app)
        return 1;

    QtSdiMainWindow mainWindow;
    QtOpenGLSceneWidget* sceneWidget = mainWindow.sceneWidget();
    mainWindow.processManager()->createProcessesCameraControls();
    SceneSegment* pTopSegment = sceneWidget->sceneContent()->GetRootSegment();
    Q_ASSERT(pTopSegment != nullptr);

    vector<MbCartPoint3D> points;
    points.emplace_back(0, 0, 0);
    points.emplace_back(0, 0, 10);
    points.emplace_back(5, 0, 0);

    MbSNameMaker name;
    MbElementarySolidParams param(et_Cylinder, points, name);
    MbElementarySolidResults result;
    ElementarySolid(param, result);
    
    MbSolid* pSolid = result.DetachSolid();

    MathRepresentation* geometry = new MathRepresentation();
    geometry->SetBuildType(CommandType::Synchronous);
    geometry->SetMathItem(pSolid);

    SceneSegment* pSegment = new SceneSegment(geometry);
    pTopSegment->AddSegment(pSegment);
   
    mainWindow.show();
    // re-initialize all modes
    GlobalFlags::SetFaceCulling(CullFaces::None);
    sceneWidget->mainLight()->SetType(Light::PointLight);
    sceneWidget->mainLight()->SetDoubleSided(true);
    sceneWidget->viewport()->GetCamera()->SetViewOrientation(Orientation::Front);
    sceneWidget->viewport()->ZoomToFit(sceneWidget->sceneContent()->GetBoundingBox());

    return app->exec();
}