#include <qt_vision.h>
#include <vsn_last.h>
#include <action_solid.h>
#include <QDebug>
#include <vector>

using namespace VSN;
using namespace QtVision;
using namespace std;

c3d::SolidSPtr cylinder(int r, int z0, int z1) {

    vector<MbCartPoint3D> points;
    points.emplace_back(0, 0, z0);
    points.emplace_back(0, 0, z1);
    points.emplace_back(r, 0, z0);

    MbSNameMaker name;
    MbElementarySolidParams param(et_Cylinder, points, name);
    MbElementarySolidResults result;
    ElementarySolid(param, result);
    c3d::SolidSPtr ptr = result.GetResultSolid();

    return ptr;

}

c3d::SolidSPtr unification(c3d::SolidSPtr ptr1, c3d::SolidSPtr ptr2) {

    MbSNameMaker name;
    MbBooleanOperationParams params(bo_Union, 1, name);
    c3d::SolidSPtr result;
    BooleanResult(ptr1, cm_Same, ptr2, cm_Same, params, result);
    return result;

}

int main(int argc, char** argv)
{
    auto app = QtApplication::createApplication(argc, argv, "T2");
    if (!app)
        return 1;

    QtSdiMainWindow mainWindow;
    QtOpenGLSceneWidget* sceneWidget = mainWindow.sceneWidget();
    mainWindow.processManager()->createProcessesCameraControls();
    SceneSegment* pTopSegment = sceneWidget->sceneContent()->GetRootSegment();
    Q_ASSERT(pTopSegment != nullptr);

    int h = 45, R = 20, r = 15, t_top = 5, t_low = 1, d = 2;

    //corpus
    c3d::SolidSPtr ptr_foot = cylinder(r, 0, t_low);
    c3d::SolidSPtr ptr_leg = cylinder(d, t_low, h - t_top);
    c3d::SolidSPtr ptr_seat = cylinder(R, h - t_top, h);
    c3d::SolidSPtr ptr_footleg = unification(ptr_foot, ptr_leg);
    c3d::SolidSPtr ptr_corpus = unification(ptr_footleg, ptr_seat);

    MbSolid* pSolid = ptr_corpus.get();

    //view
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