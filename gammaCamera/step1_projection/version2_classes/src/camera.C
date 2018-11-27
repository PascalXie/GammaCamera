#include "camera.h"
#include "units.h"

Camera::Camera()
:   pixelNumx_Int_(256),
    pixelNumy_Int_(256),
    f_(50*mm),
    pixelSizex_(55.*um),
    pixelSizey_(55.*um),
    camx_(0),
    camy_(0),
    camz_(-0.5)
{
    pixelNumx_ = pixelNumx_Int_;
    pixelNumy_ = pixelNumy_Int_;

    // information camera
    mx_ = (1.*mm)/pixelSizex_;
    my_ = (1.*mm)/pixelSizey_;
    px_ = pixelNumx_/2.*pixelSizex_;
    py_ = pixelNumy_/2.*pixelSizey_;

    double ax = f_*mx_;
    double ay = f_*my_;
    double x0 = mx_*px_;
    double y0 = my_*py_;

    K_inHomo_
     << ax, 0, x0, 
        0,  ay, y0,
        0,  0,  1;
    //cout<<"Camera Intrinsic Matrix : \n"<<K_inHomo_<<endl;

    Step1_Preparing();
    Step2_LocationTransformation();
}

Camera::~Camera()
{}

void Camera::Setlocation(double x, double y, double z)
{
    camx_ = x;
    camy_ = y;
    camz_ = z;
    Step2_LocationTransformation();
}

void Camera::Step1_Preparing()
{
    img_ei_.resize(pixelNumy_Int_, pixelNumx_Int_);
    img_ei_ << MatrixXd::Zero(pixelNumy_Int_, pixelNumx_Int_);

    img_ei_Exposured_.resize(pixelNumy_Int_, pixelNumx_Int_);
    img_ei_Exposured_ << MatrixXd::Zero(pixelNumy_Int_, pixelNumx_Int_);
}


void Camera::Step2_LocationTransformation()
{
    //
    // step 1 : transformation from world to camera 
    //
    // Be Aware : NO rotation happend between camera and world
    World_P_CamORG_inHomo_<<camx_,camy_,camz_;
    //cout<<World_P_CamORG_inHomo_.transpose()<<endl;
}

void Camera::Fill(double x, double y, double z, double &x_sensor, double &y_sensor)
{
    // step 0 : prepare coordinates of projeted point
    x_sensor = -1.;
    y_sensor = -1.;

    // step 1 : get 3D point relating to the World Coordinate system
    Vector3d World_P_inHomo(x,y,z);

    // step 2 : get 3D point relating to the Camera(Aperture) Coordinate system
    Vector3d Cam_P_inHomo = World_P_inHomo-World_P_CamORG_inHomo_;

    // step 3 : get 3D point relating to the Camera(Sensor) Coordinate system
    Vector3d Sensor_p_Homo = K_inHomo_ * Cam_P_inHomo;
    Vector2d Sensor_p_inHomo;
    Sensor_p_inHomo
        <<  int(Sensor_p_Homo(0,0)/Sensor_p_Homo(2,0)),
            int(Sensor_p_Homo(1,0)/Sensor_p_Homo(2,0));

    /*
    //
    // debug
    //
    cout<<"\nFunction : Fill "<<endl;
    cout<<"point relating to World : \n"<<World_P_inHomo.transpose()<<endl;
    cout<<"point relating to Camera : \n"<<Cam_P_inHomo.transpose()<<endl;
    cout<<"point relating to Seneor Homo: \n"<<Sensor_p_Homo.transpose()<<endl;
    cout<<"point relating to Seneor inHomo: \n"<<Sensor_p_inHomo.transpose()<<endl;
    */

    if(Sensor_p_inHomo(0,0)>=0&&Sensor_p_inHomo(0,0)<pixelNumy_Int_)
    if(Sensor_p_inHomo(1,0)>=0&&Sensor_p_inHomo(1,0)<pixelNumx_Int_) {
        img_ei_(Sensor_p_inHomo(0,0),Sensor_p_inHomo(1,0)) += 1.;
        x_sensor = Sensor_p_inHomo(0,0);
        y_sensor = Sensor_p_inHomo(1,0);
    }
}

void Camera::GetImage()
{
    //
    // Analysis
    //
    Step3_ImageAnalysis_Mode1();

    //
    // Make Image
    //
    Mat m(int(pixelNumy_),int(pixelNumx_),CV_8UC1, Scalar(0));

    for(int j=0; j<pixelNumy_Int_; j++)
    for(int i=0; i<pixelNumx_Int_; i++)
    {
        m.at<uchar>(j,i) = uchar(img_ei_Exposured_(j,i));
    }

    namedWindow("test", CV_WINDOW_AUTOSIZE);
	imshow("test", m);
    imwrite("result.png",m);
	waitKey(100);

}

void Camera::Step3_ImageAnalysis_Mode1()
{
    double K = -1.;
    double exposureResult = 0;

    for(int j=0; j<pixelNumy_Int_; j++)
    for(int i=0; i<pixelNumx_Int_; i++)
    {
        double value = img_ei_(i,j);
        double scaleFactor = log(150.+2.8)*20./log(150);
        if(value<150) exposureResult = log(value+2.8)*20;
        else {
            exposureResult = scaleFactor*log(value);
        }

        if(exposureResult>255) exposureResult=255;
        img_ei_Exposured_(j,i) = exposureResult;
        /*
        if(value>0)
            cout<<value<<"; "<<exposureResult<<endl;
        */
    }
}

void Camera::GetPoint_SensorCoorSysToApertureCoorSys(double xin, double yin, double &x, double &y)
{
    // (xin, yin) point represented in Sensor Coordinate System; pixel   
    // (x, y) point represented in Aperture Coordinate System; mm  
    x = xin*pixelSizex_ - 0.5*pixelSizex_*pixelNumx_;
    y = yin*pixelSizey_ - 0.5*pixelSizey_*pixelNumy_;
}

double Camera::GetFocalLength()
{
    return f_;
}
