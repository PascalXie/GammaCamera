#include "dataObservation.h"

DataObservation::DataObservation(int ID)
:   ID_(ID),
    pixelNumx_Int_(256),
    pixelNumy_Int_(256),
    cameraFocalLength_(50*mm),
    pixelSizex_(55.*um),
    pixelSizey_(55.*um)
{
    // observation
    observationloc_[0] = 0;
    observationloc_[1] = 0;

    // camera
    cameraloc_[0] = 0;
    cameraloc_[1] = 0;
    cameraloc_[2] = 0;
    cameraFocalLength_ = 50.;  // default

    // LandMark
    landmarkloc_[0] = 0;
    landmarkloc_[1] = 0;
    landmarkloc_[2] = 0;

    // Transformation Matrix
    Transformarion_<<MatrixXd::Zero(3,4);
    //cout<<Transformarion_<<endl<<endl; // debug


    // Intrinsic Parameters
    pixelNumx_ = pixelNumx_Int_;
    pixelNumy_ = pixelNumy_Int_;
    // information camera
    mx_ = (1.*mm)/pixelSizex_;
    my_ = (1.*mm)/pixelSizey_;
    px_ = pixelNumx_/2.*pixelSizex_;
    py_ = pixelNumy_/2.*pixelSizey_;
}

DataObservation::~DataObservation()
{}

void DataObservation::SetObservation(double x, double y)
{
    observationloc_[0] = x;
    observationloc_[1] = y;
}

void DataObservation::SetCamera(double x, double y, double z, double focalLength)
{
    cameraloc_[0] = x;
    cameraloc_[1] = y;
    cameraloc_[2] = z;
    cameraFocalLength_ = focalLength;
}

void DataObservation::SetLandMark(double x, double y, double z)
{
    landmarkloc_[0] = x;
    landmarkloc_[1] = y;
    landmarkloc_[2] = z;
}

void DataObservation::ShowObservation()
{
    cout<<"Observation ID           :"<<ID_<<endl;
    cout<<"Observation: "<<observationloc_[0]<<","<<observationloc_[1]<<endl;
    cout<<"Transformarion Matrix:\n"<<Transformarion_<<endl;
    cout<<"Camera Intrinsic Matrix : \n"<<K_inHomo_<<endl;
    cout<<"Camera Projection Matrix:\n"<<Projection_<<endl;
    cout<<"MatrixForTriangulation: \n"<<MatrixForTriangulation_<<endl;
}

void DataObservation::ShowLandMark()
{
    cout<<"LandMark: "<<landmarkloc_[0]<<" "<<landmarkloc_[1]<<" "<<landmarkloc_[2]<<endl;
}

// Projection Matrix
Matrix<double,3,4> DataObservation::GetCameraProjectionMatrix()
{
    return Projection_;
}

// Triangulation
Matrix<double,2,4> DataObservation::GetMatrixForTriangulation()
{
    return MatrixForTriangulation_;
}

//
// Camera Matrices
//
void DataObservation::CalculateMatrices()
{
    // External Matrix
    CalculateTransformationMatrix();
    // Intrinsic Matrix
    CalcuateIntrinsicMatrix();
    // Projection Matrix
    Projection_ = K_inHomo_*Transformarion_;
    // For Triangulation
    CalculateTheMatrixForTriangulation();
}

void DataObservation::CalculateTransformationMatrix()
{
    Matrix<double,3,4> Transformarion;
    Transformarion<<MatrixXd::Zero(3,4);

    //cout<<MatrixXd::Identity(3,3)<<endl<<endl; // debug

    Transformarion<<    1,0,0,-1.*cameraloc_[0],
                        0,1,0,-1.*cameraloc_[1],
                        0,0,1,-1.*cameraloc_[2];

    //cout<<"Transformarion:\n"<<Transformarion<<endl<<endl;  // debug

    Transformarion_ = Transformarion;
}

void DataObservation::CalcuateIntrinsicMatrix()
{
    double ax = cameraFocalLength_*mx_;
    double ay = cameraFocalLength_*my_;
    double x0 = mx_*px_;
    double y0 = my_*py_;

    K_inHomo_
     << ax, 0, x0, 
        0,  ay, y0,
        0,  0,  1;
    //cout<<"Camera Intrinsic Matrix : \n"<<K_inHomo_<<endl;
}

// for triangulation
void DataObservation::CalculateTheMatrixForTriangulation()
{
    // get rows of Projection matrix
    Matrix<double,1,4> P1T, P2T, P3T;

    P1T<<Projection_(0,0),Projection_(0,1),Projection_(0,2),Projection_(0,3);
    P2T<<Projection_(1,0),Projection_(1,1),Projection_(1,2),Projection_(1,3);
    P3T<<Projection_(2,0),Projection_(2,1),Projection_(2,2),Projection_(2,3);
    /*
    // debug
    cout<<"Projection row 1: "<<P1T<<endl;
    cout<<"Projection row 2: "<<P2T<<endl;
    cout<<"Projection row 3: "<<P3T<<endl;
    */

    // get matrix for triangulation
    Matrix<double,1,4> Row1, Row2;
    double x = observationloc_[0];
    double y = observationloc_[1];
    Row1 = y*P3T - P2T;
    Row2 = x*P3T - P1T;
    Matrix<double,2,4> MatrixForTriangulation;
    MatrixForTriangulation.row(0) = Row1;
    MatrixForTriangulation.row(1) = Row2;

    MatrixForTriangulation_ = MatrixForTriangulation;

    /*
    // debug
    cout<<"Row1:"<<Row1<<endl;
    cout<<"Row2:"<<Row2<<endl;
    cout<<"MatrixForTriangulation: \n"<<MatrixForTriangulation<<endl;
    */
}
