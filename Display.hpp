#pragma once

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <vector>

namespace dsp
{
    class dispxx
    {
    public:
        int maindisplay(Eigen::VectorXf* nodesx, Eigen::VectorXf* nodesy, int nodescount, int elementcount, Eigen::VectorXf* dispnodesx, Eigen::VectorXf* dispnodey, std::vector<int>* elids, std::vector<float> postp);
    };
};