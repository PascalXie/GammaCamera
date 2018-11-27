#ifndef DATAOBSERVATION_H
#define DATAOBSERVATION_H 1

#include <iostream>
// Eigen
#include <Eigen/Dense>
// units
#include "units.h"

using namespace std;
using namespace Eigen;

class DataObservation
{
    public:
        DataObservation(int ID);
        ~DataObservation(); 
    public:
        void SetObservation(double x, double y);
        void SetCamera(double x, double y, double z, double focalLength);
        void SetLandMark(double x, double y, double z);
        void ShowObservation();
        void CalculateMatrices();
        void ShowLandMark();
        Matrix<double,3,4> GetCameraProjectionMatrix();
        Matrix<double,2,4> GetMatrixForTriangulation();

    private:
        void CalculateTransformationMatrix();
        void CalcuateIntrinsicMatrix();
        void CalculateTheMatrixForTriangulation();
    
    //private:
    public:
        int ID_;

        // observation
        double observationloc_[2]; // x,y

        // camera
        double cameraloc_[3]; // x,y,z

        // LandMark
        double landmarkloc_[3];  // x,y,z

        // Matrices
        // Camera External Parameters
        Matrix<double,3,4> Transformarion_;
        // Intrinsic Matrix
        Matrix3d K_inHomo_;
        // Camera Projection Matrix
        Matrix<double,3,4> Projection_;

        // Camera Intrinsic Parameters
        // information senror
        int pixelNumx_Int_;
        int pixelNumy_Int_;
        double pixelNumx_;
        double pixelNumy_;
        // information camera
        double pixelSizex_;
        double pixelSizey_;
        double cameraFocalLength_;
        double mx_;
        double my_;
        double px_;
        double py_;

        // For Triangulation
        Matrix<double,2,4> MatrixForTriangulation_;
};

#endif
