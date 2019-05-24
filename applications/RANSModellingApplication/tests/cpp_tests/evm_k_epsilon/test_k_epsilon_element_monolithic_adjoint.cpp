//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Suneth Warnakulasuriya
//
//

// System includes
#include <functional>
#include <vector>

// External includes

// Project includes
#include "containers/model.h"
#include "testing/testing.h"

// Application includes
#include "custom_elements/evm_k_epsilon/evm_k_epsilon_adjoint_utilities.h"
#include "custom_processes/y_plus_model_processes/rans_logarithmic_y_plus_model_process.h"
#include "custom_processes/y_plus_model_processes/rans_logarithmic_y_plus_model_sensitivities_process.h"
#include "custom_utilities/rans_calculation_utilities.h"
#include "test_k_epsilon_utilities.h"
#include "custom_utilities/test_utilities.h"

namespace Kratos
{
namespace Testing
{
KRATOS_TEST_CASE_IN_SUITE(RansEvmMonolithicKEpsilonVMSAdjointElementFirstDerivativesVMS,
                          RANSEvModelsKEpsilonElementResidualMatrices)
{
    Model primal_model;
    ModelPart& r_primal_model_part =
        primal_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_primal_model_part, "VMS2D3N");

    Model adjoint_model;
    ModelPart& r_adjoint_model_part =
        adjoint_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_adjoint_model_part, "RANSEVMMonolithicKEpsilonVMSAdjoint2D3N");

    Parameters empty_parameters = Parameters(R"({})");

    RansLogarithmicYPlusModelSensitivitiesProcess y_plus_sensitivities_process(
        r_adjoint_model_part, empty_parameters);
    RansLogarithmicYPlusModelProcess adjoint_y_plus_process(
        r_adjoint_model_part, empty_parameters);

    RansLogarithmicYPlusModelProcess primal_y_plus_process(r_primal_model_part, empty_parameters);

    auto perturb_variable_velocity = [](NodeType& rNode, const int Dim) -> double& {
        array_1d<double, 3>& r_velocity = rNode.FastGetSolutionStepValue(VELOCITY);
        return r_velocity[Dim];
    };

    auto perturb_variable_pressure = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(PRESSURE);
    };

    auto perturb_variable_tke = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_KINETIC_ENERGY);
    };

    auto perturb_variable_epsilon = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_ENERGY_DISSIPATION_RATE);
    };

    auto calculate_sensitivity_matrix = [](Matrix& rOutput, Element& rElement,
                                           ProcessInfo& rProcessInfo) {
        rElement.CalculateFirstDerivativesLHS(rOutput, rProcessInfo);
    };

    const double delta = 1e-5;
    const double tolerance = 1e-3;

    // adding monolithic formulation parameters : equation indices
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_KINETIC_ENERGY] = 3;
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_ENERGY_DISSIPATION_RATE] = 4;

    RansModellingApplicationTestUtilities::RunElementResidualVectorSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_velocity, delta, tolerance, 0, 0);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_pressure, delta, tolerance, 2, 0);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart,
        calculate_sensitivity_matrix, perturb_variable_tke, delta, tolerance, 3, 0);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_epsilon, delta, tolerance, 4, 0);
}

KRATOS_TEST_CASE_IN_SUITE(RansEvmMonolithicKEpsilonVMSAdjointElementFirstDerivativesK,
                          RANSEvModelsKEpsilonElementResidualMatrices)
{
    Model primal_model;
    ModelPart& r_primal_model_part =
        primal_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_primal_model_part, "RANSEVMK2D3N");

    Model adjoint_model;
    ModelPart& r_adjoint_model_part =
        adjoint_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_adjoint_model_part, "RANSEVMMonolithicKEpsilonVMSAdjoint2D3N");

    Parameters empty_parameters = Parameters(R"({})");

    RansLogarithmicYPlusModelSensitivitiesProcess y_plus_sensitivities_process(
        r_adjoint_model_part, empty_parameters);
    RansLogarithmicYPlusModelProcess adjoint_y_plus_process(
        r_adjoint_model_part, empty_parameters);

    RansLogarithmicYPlusModelProcess primal_y_plus_process(r_primal_model_part, empty_parameters);

    auto perturb_variable_velocity = [](NodeType& rNode, const int Dim) -> double& {
        array_1d<double, 3>& r_velocity = rNode.FastGetSolutionStepValue(VELOCITY);
        return r_velocity[Dim];
    };

    auto perturb_variable_pressure = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(PRESSURE);
    };

    auto perturb_variable_tke = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_KINETIC_ENERGY);
    };

    auto perturb_variable_epsilon = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_ENERGY_DISSIPATION_RATE);
    };

    auto calculate_sensitivity_matrix = [](Matrix& rOutput, Element& rElement,
                                           ProcessInfo& rProcessInfo) {
        rElement.CalculateFirstDerivativesLHS(rOutput, rProcessInfo);
    };

    const double delta = 1e-5;
    const double tolerance = 1e-3;

    // adding monolithic formulation parameters : equation indices
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_KINETIC_ENERGY] = 3;
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_ENERGY_DISSIPATION_RATE] = 4;

    RansModellingApplicationTestUtilities::RunElementResidualVectorSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_velocity, delta, tolerance, 0, 3);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_pressure, delta, tolerance, 2, 3);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart,
        calculate_sensitivity_matrix, perturb_variable_tke, delta, tolerance, 3, 3);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_epsilon, delta, tolerance, 4, 3);
}

KRATOS_TEST_CASE_IN_SUITE(RansEvmMonolithicKEpsilonVMSAdjointElementFirstDerivativesEpsilon,
                          RANSEvModelsKEpsilonElementResidualMatrices)
{
    Model primal_model;
    ModelPart& r_primal_model_part =
        primal_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_primal_model_part, "RANSEVMEPSILON2D3N");

    Model adjoint_model;
    ModelPart& r_adjoint_model_part =
        adjoint_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_adjoint_model_part, "RANSEVMMonolithicKEpsilonVMSAdjoint2D3N");

    Parameters empty_parameters = Parameters(R"({})");

    RansLogarithmicYPlusModelSensitivitiesProcess y_plus_sensitivities_process(
        r_adjoint_model_part, empty_parameters);
    RansLogarithmicYPlusModelProcess adjoint_y_plus_process(
        r_adjoint_model_part, empty_parameters);

    RansLogarithmicYPlusModelProcess primal_y_plus_process(r_primal_model_part, empty_parameters);

    auto perturb_variable_velocity = [](NodeType& rNode, const int Dim) -> double& {
        array_1d<double, 3>& r_velocity = rNode.FastGetSolutionStepValue(VELOCITY);
        return r_velocity[Dim];
    };

    auto perturb_variable_pressure = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(PRESSURE);
    };

    auto perturb_variable_tke = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_KINETIC_ENERGY);
    };

    auto perturb_variable_epsilon = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_ENERGY_DISSIPATION_RATE);
    };

    auto calculate_sensitivity_matrix = [](Matrix& rOutput, Element& rElement,
                                           ProcessInfo& rProcessInfo) {
        rElement.CalculateFirstDerivativesLHS(rOutput, rProcessInfo);
    };

    const double delta = 1e-5;
    const double tolerance = 1e-3;

    // adding monolithic formulation parameters : equation indices
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_KINETIC_ENERGY] = 3;
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_ENERGY_DISSIPATION_RATE] = 4;

    RansModellingApplicationTestUtilities::RunElementResidualVectorSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_velocity, delta, tolerance, 0, 4);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_pressure, delta, tolerance, 2, 4);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart,
        calculate_sensitivity_matrix, perturb_variable_tke, delta, tolerance, 3, 4);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_epsilon, delta, tolerance, 4, 4);
}

KRATOS_TEST_CASE_IN_SUITE(RansEvmMonolithicKEpsilonVMSAdjointElementSecondDerivativesVMS,
                          RANSEvModelsKEpsilonElementResidualMatrices)
{
    Model primal_model;
    ModelPart& r_primal_model_part =
        primal_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_primal_model_part, "VMS2D3N");

    Model adjoint_model;
    ModelPart& r_adjoint_model_part =
        adjoint_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_adjoint_model_part, "RANSEVMMonolithicKEpsilonVMSAdjoint2D3N");

    Parameters empty_parameters = Parameters(R"({})");

    RansLogarithmicYPlusModelSensitivitiesProcess y_plus_sensitivities_process(
        r_adjoint_model_part, empty_parameters);
    RansLogarithmicYPlusModelProcess adjoint_y_plus_process(
        r_adjoint_model_part, empty_parameters);

    RansLogarithmicYPlusModelProcess primal_y_plus_process(r_primal_model_part, empty_parameters);

    const double one_minus_bossak_alpha =
        1.0 - r_primal_model_part.GetProcessInfo()[BOSSAK_ALPHA];

    auto perturb_variable_velocity = [](NodeType& rNode, const int Dim) -> double& {
        array_1d<double, 3>& r_velocity = rNode.FastGetSolutionStepValue(ACCELERATION);
        return r_velocity[Dim];
    };

    auto perturb_variable_tke = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_KINETIC_ENERGY_RATE);
    };

    auto perturb_variable_epsilon = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_ENERGY_DISSIPATION_RATE_2);
    };

    auto calculate_sensitivity_matrix = [one_minus_bossak_alpha](
                                            Matrix& rOutput, Element& rElement,
                                            ProcessInfo& rProcessInfo) {
        rElement.CalculateSecondDerivativesLHS(rOutput, rProcessInfo);
        noalias(rOutput) = rOutput * one_minus_bossak_alpha;
    };

    const double delta = 1e-5;
    const double tolerance = 1e-3;

    // adding monolithic formulation parameters : equation indices
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_KINETIC_ENERGY] = 3;
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_ENERGY_DISSIPATION_RATE] = 4;

    RansModellingApplicationTestUtilities::RunElementResidualVectorSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_velocity, delta, tolerance, 0, 0);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart,
        calculate_sensitivity_matrix, perturb_variable_tke, delta, tolerance, 3, 0);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_epsilon, delta, tolerance, 4, 0);
}

KRATOS_TEST_CASE_IN_SUITE(RansEvmMonolithicKEpsilonVMSAdjointElementSecondDerivativesK,
                          RANSEvModelsKEpsilonElementResidualMatrices)
{
    Model primal_model;
    ModelPart& r_primal_model_part =
        primal_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_primal_model_part, "RANSEVMK2D3N");

    Model adjoint_model;
    ModelPart& r_adjoint_model_part =
        adjoint_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_adjoint_model_part, "RANSEVMMonolithicKEpsilonVMSAdjoint2D3N");

    Parameters empty_parameters = Parameters(R"({})");

    RansLogarithmicYPlusModelSensitivitiesProcess y_plus_sensitivities_process(
        r_adjoint_model_part, empty_parameters);
    RansLogarithmicYPlusModelProcess adjoint_y_plus_process(
        r_adjoint_model_part, empty_parameters);

    RansLogarithmicYPlusModelProcess primal_y_plus_process(r_primal_model_part, empty_parameters);

    const double one_minus_bossak_alpha =
        1.0 - r_primal_model_part.GetProcessInfo()[BOSSAK_ALPHA];

    auto perturb_variable_velocity = [](NodeType& rNode, const int Dim) -> double& {
        array_1d<double, 3>& r_velocity = rNode.FastGetSolutionStepValue(ACCELERATION);
        return r_velocity[Dim];
    };

    auto perturb_variable_tke = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_KINETIC_ENERGY_RATE);
    };

    auto perturb_variable_epsilon = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_ENERGY_DISSIPATION_RATE_2);
    };

    auto calculate_sensitivity_matrix = [one_minus_bossak_alpha](
                                            Matrix& rOutput, Element& rElement,
                                            ProcessInfo& rProcessInfo) {
        rElement.CalculateSecondDerivativesLHS(rOutput, rProcessInfo);
        noalias(rOutput) = rOutput * one_minus_bossak_alpha;
    };

    const double delta = 1e-5;
    const double tolerance = 1e-3;

    // adding monolithic formulation parameters : equation indices

    r_adjoint_model_part.GetProcessInfo()[TURBULENT_KINETIC_ENERGY] = 3;
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_ENERGY_DISSIPATION_RATE] = 4;

    RansModellingApplicationTestUtilities::RunElementResidualVectorSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_velocity, delta, tolerance, 0, 3);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart,
        calculate_sensitivity_matrix, perturb_variable_tke, delta, tolerance, 3, 3);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_epsilon, delta, tolerance, 4, 3);
}

KRATOS_TEST_CASE_IN_SUITE(RansEvmMonolithicKEpsilonVMSAdjointElementSecondDerivativesEpsilon,
                          RANSEvModelsKEpsilonElementResidualMatrices)
{
    Model primal_model;
    ModelPart& r_primal_model_part =
        primal_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_primal_model_part, "RANSEVMEPSILON2D3N");

    Model adjoint_model;
    ModelPart& r_adjoint_model_part =
        adjoint_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_adjoint_model_part, "RANSEVMMonolithicKEpsilonVMSAdjoint2D3N");

    Parameters empty_parameters = Parameters(R"({})");

    RansLogarithmicYPlusModelSensitivitiesProcess y_plus_sensitivities_process(
        r_adjoint_model_part, empty_parameters);
    RansLogarithmicYPlusModelProcess adjoint_y_plus_process(
        r_adjoint_model_part, empty_parameters);

    RansLogarithmicYPlusModelProcess primal_y_plus_process(r_primal_model_part, empty_parameters);

    const double one_minus_bossak_alpha =
        1.0 - r_primal_model_part.GetProcessInfo()[BOSSAK_ALPHA];

    auto perturb_variable_velocity = [](NodeType& rNode, const int Dim) -> double& {
        array_1d<double, 3>& r_velocity = rNode.FastGetSolutionStepValue(ACCELERATION);
        return r_velocity[Dim];
    };

    auto perturb_variable_tke = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_KINETIC_ENERGY_RATE);
    };

    auto perturb_variable_epsilon = [](NodeType& rNode) -> double& {
        return rNode.FastGetSolutionStepValue(TURBULENT_ENERGY_DISSIPATION_RATE_2);
    };

    auto calculate_sensitivity_matrix = [one_minus_bossak_alpha](
                                            Matrix& rOutput, Element& rElement,
                                            ProcessInfo& rProcessInfo) {
        rElement.CalculateSecondDerivativesLHS(rOutput, rProcessInfo);
        noalias(rOutput) = rOutput * one_minus_bossak_alpha;
    };

    const double delta = 1e-5;
    const double tolerance = 1e-3;

    // adding monolithic formulation parameters : equation indices

    r_adjoint_model_part.GetProcessInfo()[TURBULENT_KINETIC_ENERGY] = 3;
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_ENERGY_DISSIPATION_RATE] = 4;

    RansModellingApplicationTestUtilities::RunElementResidualVectorSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_velocity, delta, tolerance, 0, 4);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart,
        calculate_sensitivity_matrix, perturb_variable_tke, delta, tolerance, 3, 4);

    RansModellingApplicationTestUtilities::RunElementResidualScalarSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart, calculate_sensitivity_matrix,
        perturb_variable_epsilon, delta, tolerance, 4, 4);
}

KRATOS_TEST_CASE_IN_SUITE(RansEvmMonolithicKEpsilonVMSAdjointElementShapeSensitivityVMS,
                          RANSEvModelsKEpsilonElementResidualMatrices)
{
    Model primal_model;
    ModelPart& r_primal_model_part =
        primal_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_primal_model_part, "VMS2D3N");

    Model adjoint_model;
    ModelPart& r_adjoint_model_part =
        adjoint_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_adjoint_model_part, "RANSEVMMonolithicKEpsilonVMSAdjoint2D3N");

    Parameters empty_parameters = Parameters(R"({})");

    RansLogarithmicYPlusModelSensitivitiesProcess y_plus_sensitivities_process(
        r_adjoint_model_part, empty_parameters);
    RansLogarithmicYPlusModelProcess adjoint_y_plus_process(
        r_adjoint_model_part, empty_parameters);

    RansLogarithmicYPlusModelProcess primal_y_plus_process(r_primal_model_part, empty_parameters);

    auto perturb_variable = [](NodeType& rNode, const int Dim) -> double& {
        array_1d<double, 3>& r_coordinates = rNode.Coordinates();
        return r_coordinates[Dim];
    };

    auto calculate_sensitivity_matrix_velocity_pressure =
        [](Matrix& rOutput, Element& rElement, ProcessInfo& rProcessInfo) {
            rElement.CalculateSensitivityMatrix(SHAPE_SENSITIVITY, rOutput, rProcessInfo);
        };

    const double delta = 1e-5;
    const double tolerance = 1e-3;

    // adding monolithic formulation parameters : equation indices
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_KINETIC_ENERGY] = 3;
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_ENERGY_DISSIPATION_RATE] = 4;

    RansModellingApplicationTestUtilities::RunElementResidualVectorSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart,
        calculate_sensitivity_matrix_velocity_pressure, perturb_variable, delta,
        tolerance, 0, 0);
}

KRATOS_TEST_CASE_IN_SUITE(RansEvmMonolithicKEpsilonVMSAdjointElementShapeSensitivityK,
                          RANSEvModelsKEpsilonElementResidualMatrices)
{
    Model primal_model;
    ModelPart& r_primal_model_part =
        primal_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_primal_model_part, "RANSEVMK2D3N");

    Model adjoint_model;
    ModelPart& r_adjoint_model_part =
        adjoint_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_adjoint_model_part, "RANSEVMMonolithicKEpsilonVMSAdjoint2D3N");

    Parameters empty_parameters = Parameters(R"({})");

    RansLogarithmicYPlusModelSensitivitiesProcess y_plus_sensitivities_process(
        r_adjoint_model_part, empty_parameters);
    RansLogarithmicYPlusModelProcess adjoint_y_plus_process(
        r_adjoint_model_part, empty_parameters);

    RansLogarithmicYPlusModelProcess primal_y_plus_process(r_primal_model_part, empty_parameters);

    auto perturb_variable = [](NodeType& rNode, const int Dim) -> double& {
        array_1d<double, 3>& r_coordinates = rNode.Coordinates();
        return r_coordinates[Dim];
    };

    auto calculate_sensitivity_matrix_tke = [](Matrix& rOutput, Element& rElement,
                                               ProcessInfo& rProcessInfo) {
        rElement.CalculateSensitivityMatrix(SHAPE_SENSITIVITY, rOutput, rProcessInfo);
    };

    const double delta = 1e-5;
    const double tolerance = 1e-3;

    // adding monolithic formulation parameters : equation indices
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_KINETIC_ENERGY] = 3;
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_ENERGY_DISSIPATION_RATE] = 4;

    RansModellingApplicationTestUtilities::RunElementResidualVectorSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart,
        calculate_sensitivity_matrix_tke, perturb_variable, delta, tolerance, 0, 3);
}

KRATOS_TEST_CASE_IN_SUITE(RansEvmMonolithicKEpsilonVMSAdjointElementShapeSensitivityEpsilon,
                          RANSEvModelsKEpsilonElementResidualMatrices)
{
    Model primal_model;
    ModelPart& r_primal_model_part =
        primal_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_primal_model_part, "RANSEVMEPSILON2D3N");

    Model adjoint_model;
    ModelPart& r_adjoint_model_part =
        adjoint_model.CreateModelPart("RansEvmKElementSensitivityMatrix");
    RansEvmKEpsilonModel::GenerateRansEvmKEpsilonTestModelPart(
        r_adjoint_model_part, "RANSEVMMonolithicKEpsilonVMSAdjoint2D3N");

    Parameters empty_parameters = Parameters(R"({})");

    RansLogarithmicYPlusModelSensitivitiesProcess y_plus_sensitivities_process(
        r_adjoint_model_part, empty_parameters);
    RansLogarithmicYPlusModelProcess adjoint_y_plus_process(
        r_adjoint_model_part, empty_parameters);

    RansLogarithmicYPlusModelProcess primal_y_plus_process(r_primal_model_part, empty_parameters);

    auto perturb_variable = [](NodeType& rNode, const int Dim) -> double& {
        array_1d<double, 3>& r_coordinates = rNode.Coordinates();
        return r_coordinates[Dim];
    };

    auto calculate_sensitivity_matrix_epsilon = [](Matrix& rOutput, Element& rElement,
                                                   ProcessInfo& rProcessInfo) {
        rElement.CalculateSensitivityMatrix(SHAPE_SENSITIVITY, rOutput, rProcessInfo);
    };

    const double delta = 1e-5;
    const double tolerance = 1e-3;

    // adding monolithic formulation parameters : equation indices
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_KINETIC_ENERGY] = 3;
    r_adjoint_model_part.GetProcessInfo()[TURBULENT_ENERGY_DISSIPATION_RATE] = 4;

    RansModellingApplicationTestUtilities::RunElementResidualVectorSensitivityTest(
        r_primal_model_part, r_adjoint_model_part, primal_y_plus_process,
        adjoint_y_plus_process, y_plus_sensitivities_process,
        RansEvmKEpsilonModel::UpdateVariablesInModelPart,
        calculate_sensitivity_matrix_epsilon, perturb_variable, delta, tolerance, 0, 4);
}

} // namespace Testing
} // namespace Kratos