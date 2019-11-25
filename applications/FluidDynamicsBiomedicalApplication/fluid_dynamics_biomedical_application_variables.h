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


#if !defined(KRATOS_FLUID_DYNAMICS_BIOMEDICAL_APPLICATION_VARIABLES_H_INCLUDED )
#define  KRATOS_FLUID_DYNAMICS_BIOMEDICAL_APPLICATION_VARIABLES_H_INCLUDED

// System includes

// External includes

// Project includes
#include "includes/define.h"
#include "includes/kratos_application.h"
#include "includes/variables.h"

namespace Kratos
{

// Wall Shear Stress statistics
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_BIOMEDICAL_APPLICATION, double, TAWSS )  // Time Averaged WSS
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_BIOMEDICAL_APPLICATION, double, TWSS )   // Time WSS
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_BIOMEDICAL_APPLICATION, double, ECAP )   // Endothelial cell activation potential (OSI/TAWSS)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_BIOMEDICAL_APPLICATION, double, RRT )    // Relative Residence Time
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_BIOMEDICAL_APPLICATION, double, OSI )    // Oscillatory Shear Index
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_BIOMEDICAL_APPLICATION, double, WSS )    // Wall Shear Stress
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_BIOMEDICAL_APPLICATION, WSS_TANGENTIAL_STRESS) //  Tangential Shear Stress
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_BIOMEDICAL_APPLICATION, WSS_NORMAL_STRESS)     //  Normal Shear Stress
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_BIOMEDICAL_APPLICATION, TEMPORAL_OSI )         // Temporal OSI

}

#endif	/* KRATOS_FLUID_DYNAMICS_BIOMEDICAL_APPLICATION_VARIABLES_H_INCLUDED */
