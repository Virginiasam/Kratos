//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Eduardo Soudah
//

#include "fluid_dynamics_biomedical_application_variables.h"

namespace Kratos
{

// Wall Shear Stress statistics (WSS)
KRATOS_CREATE_VARIABLE( double, TAWSS )  // Time Averaged WSS
KRATOS_CREATE_VARIABLE( double, TWSS )   // Time WSS
KRATOS_CREATE_VARIABLE( double, ECAP )   // Endothelial cell activation potential (OSI/TAWSS)
KRATOS_CREATE_VARIABLE( double, RRT )    // Relative Residence Time
KRATOS_CREATE_VARIABLE( double, OSI )    // Oscillatory Shear Index
KRATOS_CREATE_VARIABLE( double, WSS )    // Wall Shear Stress
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( WSS_TANGENTIAL_STRESS) //  Tangential Shear Stress
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( WSS_NORMAL_STRESS)     //  Normal Shear Stress
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( TEMPORAL_OSI )         // Temporal OSI

}
