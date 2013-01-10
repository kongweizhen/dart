#pragma once

#include <vector>
#include <Eigen/Core>

namespace dynamics { class SkeletonDynamics; }

namespace planning {

class Trajectory;

class Controller {
public:
    Controller(dynamics::SkeletonDynamics* _skel, const std::vector<int> &_actuatedDofs);
    virtual ~Controller() {};

    void setTrajectory(const Trajectory* _trajectory, double _startTime, const std::vector<int> &_dofs);

    // Returns zero torque for nonactuated DOFs
    Eigen::VectorXd getTorques(const Eigen::VectorXd& _dof, const Eigen::VectorXd& _dofVel, double _time);

protected: 
    
    dynamics::SkeletonDynamics* mSkel;
    std::vector<int> mTrajectoryDofs;
    Eigen::VectorXd mDesiredDofs;
    Eigen::MatrixXd mKp;
    Eigen::MatrixXd mKd;
    Eigen::MatrixXd mSelectionMatrix;
    Eigen::MatrixXd mIntegratedError;
    const Trajectory* mTrajectory;
    double mStartTime;
};

}