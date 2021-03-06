/*=========================================================================
$Author: bingjian $
$Date: 2011-09-06 01:51:56 -0400 (Tue, 06 Sep 2011) $
$Revision: 141 $
=========================================================================*/

/**
 * \file gmmreg_rigid_func.cpp
 * \brief  The definition of the class gmmreg_rigid_func
 */

#include "gmmreg_utils.h"
#include "gmmreg_rigid_func.h"

double gmmreg_rigid_func::eval(double& f, vnl_matrix<double>& g) {
  /* L2 version and KC version are equivalent in the rigid case */
  g =  -g;
  return -f;
}

double gmmreg_rigid_func::f(const vnl_vector<double>& x) {
  // std::cout << "f begin" << std::endl;
  gmmreg->perform_transform(x);
  // std::cout << "transform done" << std::endl;
  double energy = GaussTransform(gmmreg->transformed_model,
      gmmreg->scene, scale, gradient);
  // std::cout << "gauss transform done" << std::endl;
  return eval(energy, gradient);
  // std::cout << "f end" << std::endl;
}

void gmmreg_rigid_func::gradf(const vnl_vector<double>& x,
    vnl_vector<double>& g) {
/*     case 'rigid2d'
 *         [f, grad] = rigid_costfunc(transformed_model, scene, scale);
 *         grad = grad';
 *         g(1) = sum(grad(1,:));
 *         g(2) = sum(grad(2,:));
 *         grad = grad*model;
 *         theta = param(3);
 *         r = [-sin(theta) -cos(theta);
 *              cos(theta)  -sin(theta)];
 *         g(3) = sum(sum(grad.*r));
 *
 */
  int i = 0;
  vnl_matrix<double> r;
  vnl_matrix<double> gm;
  if (d == 2) { //rigid2d
    g[0] = gradient.get_column(0).sum();
    g[1] = gradient.get_column(1).sum();
    r.set_size(2,2);
    double theta = x[2];
    r[0][0] = -sin(theta);
    r[0][1] = -cos(theta);
    r[1][0] = cos(theta);
    r[1][1] = -sin(theta);
    gm = gradient.transpose()*gmmreg->model;
    g[2] = 0;
    for (i=0;i<2;++i) {
      for (int j=0;j<2;++j) {
        g[2] += r[i][j]*gm[i][j];
      }
    }
  } else if (d == 3) { //rigid3d
/*
*     case 'rigid3d'
*        [f,grad] = rigid_costfunc(transformed_model, scene, scale);
*         [r,gq] = quaternion2rotation(param(1:4));
*         grad = grad';
*         gm = grad*model;
*         g(1) = sum(sum(gm.*gq{1}));
*         g(2) = sum(sum(gm.*gq{2}));
*         g(3) = sum(sum(gm.*gq{3}));
*         g(4) = sum(sum(gm.*gq{4}));
*         g(5) = sum(grad(1,:));
*         g(6) = sum(grad(2,:));
*         g(7) = sum(grad(3,:));
*/
    g[4] = gradient.get_column(0).sum();
    g[5] = gradient.get_column(1).sum();
    g[6] = gradient.get_column(2).sum();
    vnl_vector<double> q;
    q.set_size(4);
    for (i=0;i<4;++i) q[i] = x[i];
    r.set_size(3,3);
    vnl_matrix<double> g1,g2,g3,g4;
    g1.set_size(3,3);
    g2.set_size(3,3);
    g3.set_size(3,3);
    g4.set_size(3,3);
    quaternion2rotation(q,r,g1,g2,g3,g4);
    gm = gradient.transpose()*gmmreg->model;
    g[0] = 0;
    for (i=0;i<3;++i) {
      for (int j=0;j<3;++j) {
        g[0] += g1[i][j]*gm[i][j];
      }
    }
    g[1] = 0;
    for (i=0;i<3;++i) {
      for (int j=0;j<3;++j) {
        g[1] += g2[i][j]*gm[i][j];
      }
    }
    g[2] = 0;
    for (i=0;i<3;++i) {
      for (int j=0;j<3;++j) {
        g[2] += g3[i][j]*gm[i][j];
      }
    }
    g[3] = 0;
    for (i=0;i<3;++i) {
      for (int j=0;j<3;++j) {
        g[3] += g4[i][j]*gm[i][j];
      }
    }
  }
}
