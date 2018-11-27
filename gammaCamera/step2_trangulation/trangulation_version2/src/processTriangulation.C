#include "processTriangulation.h"

ProcessTriangulation::ProcessTriangulation(int ID)
:   ID_(ID)
{}

ProcessTriangulation::~ProcessTriangulation()
{}

void ProcessTriangulation::AddObservation(DataObservation observation)
{
    Observations_.push_back(observation);
}

void ProcessTriangulation::DoTriangulate()
{
    //
    // step 1 : 
    //

    /*
    // debug
    Observations_[0].ShowObservation();
    Matrix<double,2,4> MatrixForTriangulation = Observations_[0].GetMatrixForTriangulation();
    //cout<<"MatrixForTriangulation:\n"<<MatrixForTriangulation<<endl<<endl; // debug
    */

    int Num_rows = 2*Observations_.size();
    int Num_cols = 4;
    MatrixXd AllMatrices(Num_rows,Num_cols);
    AllMatrices<<MatrixXd::Zero(Num_rows,Num_cols);

    for(int i=0;i<Observations_.size();i++)
    {
        Matrix<double,2,4> MatrixForTriangulation_temp = Observations_[i].GetMatrixForTriangulation();
        AllMatrices.row(i*2)    = MatrixForTriangulation_temp.row(0);
        AllMatrices.row(i*2+1)  = MatrixForTriangulation_temp.row(1);
    }

    // step 2 : Least mean squares
    MatrixXd ATA(4,4);
    ATA = AllMatrices.transpose()*AllMatrices;
    SelfAdjointEigenSolver<Matrix<double,4,4>> eigen_solver(ATA);

    MatrixXd loc(4,1);
    loc.col(0) = eigen_solver.eigenvectors().col(0);
    loc = loc/loc(3,0);

    /*
    // debug
    Observations_[0].ShowLandMark();
    cout<<eigen_solver.eigenvalues()<<endl;
    cout<<eigen_solver.eigenvectors()<<endl;
    cout<<"Triangulation ID: "<<ID_<<", loc: "<<loc.transpose()<<endl;
    */

    // step 3 : save it 
    LandMarkEstimated_<<loc(0,0),loc(1,0),loc(2,0);
    cout<<"Triangulation ID: "<<ID_<<", loc: "<<LandMarkEstimated_.transpose()<<endl;
}

void ProcessTriangulation::ShowProcessTriangulation()
{
    cout<<"ID: "<<ID_<<"; Size of DataObservation: "<<Observations_.size()<<endl;
}
