//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Suneth Warnakulasuriya (https://github.com/sunethwarna)
//

// System includes

// External includes

// Project includes
#include "rans_application.h"
#include "geometries/line_2d_2.h"
#include "geometries/tetrahedra_3d_4.h"
#include "geometries/triangle_2d_3.h"
#include "rans_application_variables.h"

namespace Kratos
{
KratosRANSApplication::KratosRANSApplication()
    :   KratosApplication("RANSApplication"),
        mSegregatedVMSVelocity2D3N(0,Element::GeometryType::Pointer(new Triangle2D3<Node<3> >(Element::GeometryType::PointsArrayType(3)))),
        mSegregatedVMSVelocity3D4N(0,Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3> >(Element::GeometryType::PointsArrayType(4)))),
        mSegregatedVMSPressure2D3N(0,Element::GeometryType::Pointer(new Triangle2D3<Node<3> >(Element::GeometryType::PointsArrayType(3)))),
        mSegregatedVMSPressure3D4N(0,Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3> >(Element::GeometryType::PointsArrayType(4)))),
        mSegregatedVMSWallVelocityCondition2D2N(0, Element::GeometryType::Pointer(new Line2D2<Node<3>>(Element::GeometryType::PointsArrayType(2)))),
        mSegregatedVMSWallVelocityCondition3D3N(0, Element::GeometryType::Pointer(new Triangle3D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mSegregatedVMSWallPressureCondition2D2N(0, Element::GeometryType::Pointer(new Line2D2<Node<3>>(Element::GeometryType::PointsArrayType(2)))),
        mSegregatedVMSWallPressureCondition3D3N(0, Element::GeometryType::Pointer(new Triangle3D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mFSHighReKWallCondition2D2N(0, Element::GeometryType::Pointer(new Line2D2<Node<3>>(Element::GeometryType::PointsArrayType(2)))),
        mFSHighReKWallCondition3D3N(0, Element::GeometryType::Pointer(new Triangle3D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mIncompressibleVelocityPotentialElement2D(0, Element::GeometryType::Pointer(new Triangle2D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mIncompressibleVelocityPotentialElement3D(0, Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3>>(Element::GeometryType::PointsArrayType(4)))),
        mPressurePotentialElement2D(0, Element::GeometryType::Pointer(new Triangle2D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mPressurePotentialElement3D(0, Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3>>(Element::GeometryType::PointsArrayType(4)))),
        mIncompressibleVelocityPotentialCondition2D2N(0, Element::GeometryType::Pointer(new Line2D2<Node<3>>(Element::GeometryType::PointsArrayType(2)))),
        mIncompressibleVelocityPotentialCondition3D3N(0, Element::GeometryType::Pointer(new Triangle3D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mIncompressiblePressureCondition2D2N(0, Element::GeometryType::Pointer(new Line2D2<Node<3>>(Element::GeometryType::PointsArrayType(2)))),
        mIncompressiblePressureCondition3D3N(0, Element::GeometryType::Pointer(new Triangle3D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmKEpsilonLowReK2D(0, Element::GeometryType::Pointer(new Triangle2D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmKEpsilonLowReK3D(0, Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3>>(Element::GeometryType::PointsArrayType(4)))),
        mRansEvmKEpsilonLowReEpsilon2D(0, Element::GeometryType::Pointer(new Triangle2D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmKEpsilonLowReEpsilon3D(0, Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3>>(Element::GeometryType::PointsArrayType(4)))),
        mRansEvmKEpsilonK2D(0, Element::GeometryType::Pointer(new Triangle2D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmKEpsilonK3D(0, Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3>>(Element::GeometryType::PointsArrayType(4)))),
        mRansEvmKEpsilonEpsilon2D(0, Element::GeometryType::Pointer(new Triangle2D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmKEpsilonEpsilon3D(0, Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3>>(Element::GeometryType::PointsArrayType(4)))),
        mRansEvmKEpsilonEpsilonWall2D2N(0, Element::GeometryType::Pointer(new Line2D2<Node<3>>(Element::GeometryType::PointsArrayType(2)))),
        mRansEvmKEpsilonEpsilonWall3D3N(0, Element::GeometryType::Pointer(new Triangle3D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmKEpsilonVmsMonolithicWall2D2N(0, Element::GeometryType::Pointer(new Line2D2<Node<3>>(Element::GeometryType::PointsArrayType(2)))),
        mRansEvmKEpsilonVmsMonolithicWall3D3N(0, Element::GeometryType::Pointer(new Triangle3D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmEpsilonAdjoint2D3N(0, Element::GeometryType::Pointer(new Triangle2D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmEpsilonAdjoint3D4N(0, Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3>>(Element::GeometryType::PointsArrayType(4)))),
        mRansEvmKAdjoint2D3N(0, Element::GeometryType::Pointer(new Triangle2D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmKAdjoint3D4N(0, Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3>>(Element::GeometryType::PointsArrayType(4)))),
        mRansEvmKEpsilonVMSAdjoint2D3N(0, Element::GeometryType::Pointer(new Triangle2D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmKEpsilonVMSAdjoint3D4N(0, Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3>>(Element::GeometryType::PointsArrayType(4)))),
        mRansEvmMonolithicKEpsilonVMSAdjoint2D(0, Element::GeometryType::Pointer(new Triangle2D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmMonolithicKEpsilonVMSAdjoint3D(0, Element::GeometryType::Pointer(new Tetrahedra3D4<Node<3>>(Element::GeometryType::PointsArrayType(4)))),
        mRansEvmEpsilonAdjointWallCondition2D2N(0, Element::GeometryType::Pointer(new Line2D2<Node<3>>(Element::GeometryType::PointsArrayType(2)))),
        mRansEvmEpsilonAdjointWallCondition3D3N(0, Element::GeometryType::Pointer(new Triangle3D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmVmsMonolithicAdjointWallCondition2D2N(0, Element::GeometryType::Pointer(new Line2D2<Node<3>>(Element::GeometryType::PointsArrayType(2)))),
        mRansEvmVmsMonolithicAdjointWallCondition3D3N(0, Element::GeometryType::Pointer(new Triangle3D3<Node<3>>(Element::GeometryType::PointsArrayType(3)))),
        mRansEvmMonolithicKEpsilonVMSAdjointWallCondition2D2N(0, Element::GeometryType::Pointer(new Line2D2<Node<3>>(Element::GeometryType::PointsArrayType(2)))),
        mRansEvmMonolithicKEpsilonVMSAdjointWallCondition3D3N(0, Element::GeometryType::Pointer(new Triangle3D3<Node<3>>(Element::GeometryType::PointsArrayType(3))))
{
}

void KratosRANSApplication::Register()
{
    // calling base class register to register Kratos components
    KratosApplication::Register();
    KRATOS_INFO("") << "Initializing KratosRANSApplication..." << std::endl;

    KRATOS_REGISTER_VARIABLE(TURBULENT_KINETIC_ENERGY)
    KRATOS_REGISTER_VARIABLE(TURBULENT_ENERGY_DISSIPATION_RATE)
    KRATOS_REGISTER_VARIABLE(TURBULENT_KINETIC_ENERGY_RATE)
    KRATOS_REGISTER_VARIABLE(TURBULENT_ENERGY_DISSIPATION_RATE_2)
    KRATOS_REGISTER_VARIABLE(IS_CO_SOLVING_PROCESS_ACTIVE)
    KRATOS_REGISTER_VARIABLE(RANS_Y_PLUS)
    KRATOS_REGISTER_VARIABLE(RANS_Y_PLUS_LIMIT)
    KRATOS_REGISTER_VARIABLE(RANS_AUXILIARY_VARIABLE_1)
    KRATOS_REGISTER_VARIABLE(RANS_AUXILIARY_VARIABLE_2)
    KRATOS_REGISTER_VARIABLE(WALL_SMOOTHNESS_BETA)
    KRATOS_REGISTER_VARIABLE(WALL_VON_KARMAN)
    KRATOS_REGISTER_VARIABLE(TURBULENCE_RANS_C_MU)
    KRATOS_REGISTER_VARIABLE(TURBULENCE_RANS_C1)
    KRATOS_REGISTER_VARIABLE(TURBULENCE_RANS_C2)
    KRATOS_REGISTER_VARIABLE(TURBULENT_KINETIC_ENERGY_SIGMA)
    KRATOS_REGISTER_VARIABLE(TURBULENT_ENERGY_DISSIPATION_RATE_SIGMA)
    KRATOS_REGISTER_VARIABLE(NUMBER_OF_NEIGHBOUR_CONDITIONS)
    KRATOS_REGISTER_VARIABLE(RANS_STABILIZATION_DISCRETE_UPWIND_OPERATOR_COEFFICIENT)
    KRATOS_REGISTER_VARIABLE(RANS_STABILIZATION_DIAGONAL_POSITIVITY_PRESERVING_COEFFICIENT)
    KRATOS_REGISTER_VARIABLE(FRICTION_VELOCITY)
    KRATOS_REGISTER_VARIABLE(VELOCITY_POTENTIAL)
    KRATOS_REGISTER_VARIABLE(PRESSURE_POTENTIAL)
    KRATOS_REGISTER_VARIABLE(PARENT_ELEMENT_POINTER)
    KRATOS_REGISTER_VARIABLE(PARENT_CONDITION_POINTER)
    KRATOS_REGISTER_VARIABLE(COUPLING_ITERATION)

    // Register adjoint variables
    KRATOS_REGISTER_VARIABLE(RANS_NUT_SCALAR_PARTIAL_DERIVATIVES)
    KRATOS_REGISTER_VARIABLE(RANS_Y_PLUS_VELOCITY_DERIVATIVES)
    KRATOS_REGISTER_VARIABLE(RANS_VELOCITY_PRESSURE_PARTIAL_DERIVATIVE)
    KRATOS_REGISTER_VARIABLE(RANS_PRESSURE_PARTIAL_DERIVATIVE)
    KRATOS_REGISTER_VARIABLE(RANS_TURBULENT_KINETIC_ENERGY_PARTIAL_DERIVATIVE)
    KRATOS_REGISTER_VARIABLE(RANS_TURBULENT_ENERGY_DISSIPATION_RATE_PARTIAL_DERIVATIVE)
    KRATOS_REGISTER_VARIABLE(RANS_ACCELERATION_PARTIAL_DERIVATIVE)
    KRATOS_REGISTER_VARIABLE(RANS_TURBULENT_KINETIC_ENERGY_RATE_PARTIAL_DERIVATIVE)
    KRATOS_REGISTER_VARIABLE(RANS_TURBULENT_ENERGY_DISSIPATION_RATE_2_PARTIAL_DERIVATIVE)

    KRATOS_REGISTER_VARIABLE(RANS_SCALAR_1_ADJOINT_1)
    KRATOS_REGISTER_VARIABLE(RANS_SCALAR_1_ADJOINT_2)
    KRATOS_REGISTER_VARIABLE(RANS_SCALAR_1_ADJOINT_3)
    KRATOS_REGISTER_VARIABLE(RANS_AUX_ADJOINT_SCALAR_1)

    KRATOS_REGISTER_VARIABLE(RANS_SCALAR_2_ADJOINT_1)
    KRATOS_REGISTER_VARIABLE(RANS_SCALAR_2_ADJOINT_2)
    KRATOS_REGISTER_VARIABLE(RANS_SCALAR_2_ADJOINT_3)
    KRATOS_REGISTER_VARIABLE(RANS_AUX_ADJOINT_SCALAR_2)

    // Register Elements
    // Segregated VMS elements
    KRATOS_REGISTER_ELEMENT("SegregatedVMSVelocity2D3N", mSegregatedVMSVelocity2D3N);
    KRATOS_REGISTER_ELEMENT("SegregatedVMSVelocity3D4N", mSegregatedVMSVelocity3D4N);
    KRATOS_REGISTER_ELEMENT("SegregatedVMSPressure2D3N", mSegregatedVMSPressure2D3N);
    KRATOS_REGISTER_ELEMENT("SegregatedVMSPressure3D4N", mSegregatedVMSPressure3D4N);

    // Segregated VMS conditions
    KRATOS_REGISTER_CONDITION("SegregatedVMSWallVelocity2D2N", mSegregatedVMSWallVelocityCondition2D2N);
    KRATOS_REGISTER_CONDITION("SegregatedVMSWallVelocity3D3N", mSegregatedVMSWallVelocityCondition3D3N);
    KRATOS_REGISTER_CONDITION("SegregatedVMSWallPressure2D2N", mSegregatedVMSWallPressureCondition2D2N);
    KRATOS_REGISTER_CONDITION("SegregatedVMSWallPressure3D3N", mSegregatedVMSWallPressureCondition3D3N);

    // Fractional step wall conditions
    KRATOS_REGISTER_CONDITION("FSHighReKWall2D2N", mFSHighReKWallCondition2D2N);
    KRATOS_REGISTER_CONDITION("FSHighReKWall3D3N", mFSHighReKWallCondition3D3N);

    KRATOS_REGISTER_ELEMENT("RansIncompressibleVelocityPotentialElement2D3N", mIncompressibleVelocityPotentialElement2D);
    KRATOS_REGISTER_ELEMENT("RansIncompressibleVelocityPotentialElement3D4N", mIncompressibleVelocityPotentialElement3D);
    KRATOS_REGISTER_ELEMENT("RansPressurePotentialElement2D3N", mPressurePotentialElement2D);
    KRATOS_REGISTER_ELEMENT("RansPressurePotentialElement3D4N", mPressurePotentialElement3D);

    KRATOS_REGISTER_ELEMENT("RansEvmKEpsilonLowReK2D3N", mRansEvmKEpsilonLowReK2D);
    KRATOS_REGISTER_ELEMENT("RansEvmKEpsilonLowReK3D4N", mRansEvmKEpsilonLowReK3D);
    KRATOS_REGISTER_ELEMENT("RansEvmKEpsilonLowReEpsilon2D3N", mRansEvmKEpsilonLowReEpsilon2D);
    KRATOS_REGISTER_ELEMENT("RansEvmKEpsilonLowReEpsilon3D4N", mRansEvmKEpsilonLowReEpsilon3D);

    KRATOS_REGISTER_ELEMENT("RansEvmKEpsilonK2D3N", mRansEvmKEpsilonK2D);
    KRATOS_REGISTER_ELEMENT("RansEvmKEpsilonK3D4N", mRansEvmKEpsilonK3D);
    KRATOS_REGISTER_ELEMENT("RansEvmKEpsilonEpsilon2D3N", mRansEvmKEpsilonEpsilon2D);
    KRATOS_REGISTER_ELEMENT("RansEvmKEpsilonEpsilon3D4N", mRansEvmKEpsilonEpsilon3D);

    // Register conditions
    KRATOS_REGISTER_CONDITION("RansIncompressibleVelocityPotentialCondition2D2N", mIncompressibleVelocityPotentialCondition2D2N);
    KRATOS_REGISTER_CONDITION("RansIncompressibleVelocityPotentialCondition3D3N", mIncompressibleVelocityPotentialCondition3D3N);
    KRATOS_REGISTER_CONDITION("RansIncompressiblePressureCondition2D2N", mIncompressiblePressureCondition2D2N);
    KRATOS_REGISTER_CONDITION("RansIncompressiblePressureCondition3D3N", mIncompressiblePressureCondition3D3N);

    KRATOS_REGISTER_CONDITION("RansEvmKEpsilonEpsilonWall2D2N", mRansEvmKEpsilonEpsilonWall2D2N);
    KRATOS_REGISTER_CONDITION("RansEvmKEpsilonEpsilonWall3D3N", mRansEvmKEpsilonEpsilonWall3D3N);

    KRATOS_REGISTER_CONDITION("RansEvmKEpsilonVmsMonolithicWall2D2N",
                              mRansEvmKEpsilonVmsMonolithicWall2D2N);
    KRATOS_REGISTER_CONDITION("RansEvmKEpsilonVmsMonolithicWall3D3N",
                              mRansEvmKEpsilonVmsMonolithicWall3D3N);

    // Registering adjoint elements
    KRATOS_REGISTER_ELEMENT("RansEvmEpsilonAdjoint2D3N", mRansEvmEpsilonAdjoint2D3N);
    KRATOS_REGISTER_ELEMENT("RansEvmEpsilonAdjoint3D4N", mRansEvmEpsilonAdjoint3D4N);

    KRATOS_REGISTER_ELEMENT("RansEvmKAdjoint2D3N", mRansEvmKAdjoint2D3N);
    KRATOS_REGISTER_ELEMENT("RansEvmKAdjoint3D4N", mRansEvmKAdjoint3D4N);

    KRATOS_REGISTER_ELEMENT("RansEvmKEpsilonVMSAdjoint2D3N", mRansEvmKEpsilonVMSAdjoint2D3N);
    KRATOS_REGISTER_ELEMENT("RansEvmKEpsilonVMSAdjoint3D4N", mRansEvmKEpsilonVMSAdjoint3D4N);

    KRATOS_REGISTER_ELEMENT("RansEvmMonolithicKEpsilonVMSAdjoint2D",
                            mRansEvmMonolithicKEpsilonVMSAdjoint2D);
    KRATOS_REGISTER_ELEMENT("RansEvmMonolithicKEpsilonVMSAdjoint3D",
                            mRansEvmMonolithicKEpsilonVMSAdjoint3D);

    // Registering adjoint conditions
    KRATOS_REGISTER_CONDITION("RansEvmEpsilonAdjointWallCondition2D2N",
                              mRansEvmEpsilonAdjointWallCondition2D2N);
    KRATOS_REGISTER_CONDITION("RansEvmEpsilonAdjointWallCondition3D3N",
                              mRansEvmEpsilonAdjointWallCondition3D3N);

    KRATOS_REGISTER_CONDITION("RansEvmVmsMonolithicAdjointWallCondition2D2N",
                              mRansEvmVmsMonolithicAdjointWallCondition2D2N);
    KRATOS_REGISTER_CONDITION("RansEvmVmsMonolithicAdjointWallCondition3D3N",
                              mRansEvmVmsMonolithicAdjointWallCondition3D3N);

    KRATOS_REGISTER_CONDITION(
        "RansEvmMonolithicKEpsilonVMSAdjointWallCondition2D2N",
        mRansEvmMonolithicKEpsilonVMSAdjointWallCondition2D2N);
    KRATOS_REGISTER_CONDITION(
        "RansEvmMonolithicKEpsilonVMSAdjointWallCondition3D3N",
        mRansEvmMonolithicKEpsilonVMSAdjointWallCondition3D3N);
}
} // namespace Kratos.
