/*=========================================================================
$Author: bing.jian $
$Date: 2011-01-27 15:42:44 -0500 (Thu, 27 Jan 2011) $
$Revision: 135 $
=========================================================================*/

/**
 * \file gmmreg_api.cpp
 * \brief  The implementation of gmmreg_api interface
 */
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>


#ifdef WIN32
#include <windows.h>
#else
#include "port_ini.h"
#endif

#include "gmmreg_utils.h"
#include "gmmreg_api.h"
#include "gmmreg_cpd.h"
#include "gmmreg_tps.h"
#include "gmmreg_grbf.h"
#include "gmmreg_rigid.h"

typedef std::auto_ptr<gmmreg_cpd_tps> gmmreg_cpd_tps_Ptr;
typedef std::auto_ptr<gmmreg_cpd_grbf> gmmreg_cpd_grbf_Ptr;
typedef std::auto_ptr<gmmreg_tps_L2> gmmreg_tps_L2_Ptr;
typedef std::auto_ptr<gmmreg_tps_KC> gmmreg_tps_KC_Ptr;
typedef std::auto_ptr<gmmreg_grbf_L2> gmmreg_grbf_L2_Ptr;
typedef std::auto_ptr<gmmreg_grbf_KC> gmmreg_grbf_KC_Ptr;
typedef std::auto_ptr<gmmreg_rigid> gmmreg_rigid_Ptr;

#ifdef __cplusplus
extern "C"
#endif
void print_usage()
{
    std::cerr << "The following five methods are currently available:" << std::endl;
    std::cerr << " 'EM_TPS': Haili Chui and Anand Rangarajan,\
A new point matching algorithm for non-rigid registration, \
Computer Vision and Image Understanding, 2003, 89(2-3), pp. 114-141." << std::endl;
    std::cerr << " 'EM_GRBF': Andriy Myronenko, Xubo B. Song, Miguel A. Carreira-Perpinan,\
Non-rigid Point Set Registration: Coherent Point Drift,\
NIPS 2006, pp. 1009-1016." << std::endl;
    std::cerr << " 'TPS_L2, GRBF_L2': Bing Jian and Baba C. Vemuri,\
A Robust Algorithm for Point Set Registration Using Mixture of Gaussians,\
ICCV 2005, pp. 1246-1251." << std::endl;
    std::cerr << " 'TPS_KC, GRBF_KC': Yanghai Tsin and Takeo Kanade, \
A Correlation-Based Approach to Robust Point Set Registration, \
ECCV (3) 2004: 558-569. " << std::endl;
    std::cerr << " 'rigid':  rigid registration using Jian and Vemuri's algorithm." << std::endl;
}

#ifdef __cplusplus
extern "C"
#endif
int gmmreg_api(const char* input_config, const char* method)
{
    //std::cout << "Robust Point Set Registration Using Gaussian Mixture Models" << std::endl;
    //std::cout << "Compiled on " << __TIME__ << "," << __DATE__ << std::endl;
    //std::cout << "Copyright 2008 Bing Jian & Baba C. Vemuri " << std::endl;
    char f_config[BUFSIZE];
    get_config_fullpath(input_config,f_config);
    if (!strcmp(strupr((char*)method), "EM_TPS"))
    {
        gmmreg_cpd_tps_Ptr gmmreg(new gmmreg_cpd_tps);
        gmmreg->run(f_config);
    }
    else if (!strcmp(strupr((char*)method), "EM_GRBF"))
    {
        gmmreg_cpd_grbf_Ptr gmmreg(new gmmreg_cpd_grbf);
        gmmreg->run(f_config);
    }
    else if (!strcmp(strupr((char*)method), "TPS_L2"))
    {
        gmmreg_tps_L2_Ptr gmmreg(new gmmreg_tps_L2);
        gmmreg->run(f_config);
    }
    else if (!strcmp(strupr((char*)method), "TPS_KC"))
    {
        gmmreg_tps_KC_Ptr gmmreg(new gmmreg_tps_KC);
        gmmreg->run(f_config);
    }
    else if (!strcmp(strupr((char*)method), "GRBF_L2"))
    {
        gmmreg_grbf_L2_Ptr gmmreg(new gmmreg_grbf_L2);
        gmmreg->run(f_config);
    }
    else if (!strcmp(strupr((char*)method), "GRBF_KC"))
    {
        gmmreg_grbf_KC_Ptr gmmreg(new gmmreg_grbf_KC);
        gmmreg->run(f_config);
    }

    else if (!strcmp(strlwr((char*)method), "rigid"))
    {
        gmmreg_rigid_Ptr gmmreg(new gmmreg_rigid);
        gmmreg->run(f_config);
    }
    else
    {
        print_usage();
        return -1;
    }
    return 0;
}
