#pragma once

#include <Eigen/Dense>
#include <PoseLib/types.h>
#include <vector>

namespace pose_lib {

struct ProblemInstance {
public:
  // Ground truth camera pose
  CameraPose pose_gt;

  // Point-to-point correspondences
  std::vector<Eigen::Vector3d> x_point_;
  std::vector<Eigen::Vector3d> X_point_;

  // Point-to-line correspondences
  std::vector<Eigen::Vector3d> x_line_;
  std::vector<Eigen::Vector3d> X_line_;
  std::vector<Eigen::Vector3d> V_line_;

  // Line-to-point correspondences
  std::vector<Eigen::Vector3d> l_line_point_;
  std::vector<Eigen::Vector3d> X_line_point_;

  // Line-to-line correspondences
  std::vector<Eigen::Vector3d> l_line_line_;
  std::vector<Eigen::Vector3d> X_line_line_;
  std::vector<Eigen::Vector3d> V_line_line_;

  // For generalized cameras we have an offset in the camera coordinate system
  std::vector<Eigen::Vector3d> p_point_;
  std::vector<Eigen::Vector3d> p_line_;
  std::vector<Eigen::Vector3d> p_line_point_;
  std::vector<Eigen::Vector3d> p_line_line_;
};

struct CalibPoseValidator {
  // Computes the distance to the ground truth pose
  static double compute_pose_error(const ProblemInstance &instance, const CameraPose &pose);
  // Checks if the solution is valid (i.e. is rotation matrix and satisfies projection constraints)
  static bool is_valid(const ProblemInstance &instance, const CameraPose &pose, double tol);
};

struct UnknownFocalValidator {
  // Computes the distance to the ground truth pose
  static double compute_pose_error(const ProblemInstance &instance, const CameraPose &pose);
  // Checks if the solution is valid (i.e. is rotation matrix and satisfies projection constraints)
  static bool is_valid(const ProblemInstance &instance, const CameraPose &pose, double tol);
};


struct RadialPoseValidator {
  // Computes the distance to the ground truth pose
  static double compute_pose_error(const ProblemInstance &instance, const CameraPose &pose);
  // Checks if the solution is valid (i.e. is rotation matrix and satisfies projection constraints)
  static bool is_valid(const ProblemInstance &instance, const CameraPose &pose, double tol);
};

struct ProblemOptions {
  double min_depth_ = 0.1;
  double max_depth_ = 10.0;
  double camera_fov_ = 70.0;
  int n_point_point_ = 0;
  int n_point_line_ = 0;
  int n_line_point_ = 0;
  int n_line_line_ = 0;
  bool upright_ = false;
  bool generalized_ = false;
  bool unknown_scale_ = false;
  bool unknown_focal_ = false;
  bool radial_lines_ = false;
  double min_scale_ = 0.1;
  double max_scale_ = 10.0;
  double min_focal_ = 100.0;
  double max_focal_ = 1000.0;
};

void set_random_pose(CameraPose &pose, bool upright);

void generate_problems(int n_problems, std::vector<ProblemInstance> *problem_instances, const ProblemOptions &options);

}; // namespace pose_lib