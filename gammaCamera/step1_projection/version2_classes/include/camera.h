#ifndef CAMERA_H
#define CAMERA_H 1
#include <iostream>

// openCV
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

// Eigen
#include <Eigen/Dense>

// units
#include "units.h"


using namespace std;
using namespace cv;
using namespace Eigen;

class Camera
{
    public:
        Camera();
        ~Camera();
        void Step1_Preparing();
        void Step2_LocationTransformation();
        void Fill(double x, double y, double z, double &x_sensor, double &y_sensor);
        void GetImage();
        void Setlocation(double x, double y, double z);
        void GetPoint_SensorCoorSysToApertureCoorSys(double xin, double yin, double &x, double &y);
        double GetFocalLength();
    private:
        void Step3_ImageAnalysis_Mode1();

    public:
        // information senror
        int pixelNumx_Int_;
        int pixelNumy_Int_;
        double pixelNumx_;
        double pixelNumy_;

    private:
        MatrixXd img_ei_;
        MatrixXd img_ei_Exposured_;

        // information camera
        double pixelSizex_;
        double pixelSizey_;
        double f_; //focal length 
        double mx_;
        double my_;
        double px_;
        double py_;

        // information Camera location (Aperture)
        Vector3d World_P_CamORG_inHomo_;

        Matrix3d K_inHomo_;

        // information camera coordinate system
        double camx_;
        double camy_;
        double camz_;
};
#endif
