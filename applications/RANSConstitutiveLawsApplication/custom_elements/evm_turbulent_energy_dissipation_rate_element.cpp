//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    , KratosAppGenerator
//

// System includes


// External includes


// Include Base h
#include "custom_elements/evm_turbulent_energy_dissipation_rate_element.h"


namespace Kratos
{

///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

///@}
///@name  Enum's
///@{

///@}
///@name  Functions
///@{

///@}
///@name Kratos Classes
///@{

/**
 * Constructor.
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::EvmTurbulentEnergyDissipationRateElement(IndexType NewId)
    : RANSConstitutiveElement<TDim, TNumNodes>(NewId)
{
}

/**
 * Constructor using an array of nodes
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::EvmTurbulentEnergyDissipationRateElement(IndexType NewId, const NodesArrayType& ThisNodes)
    : RANSConstitutiveElement<TDim, TNumNodes>(NewId, ThisNodes)
{
}

/**
 * Constructor using Geometry
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::EvmTurbulentEnergyDissipationRateElement(IndexType NewId, GeometryType::Pointer pGeometry)
    : RANSConstitutiveElement<TDim, TNumNodes>(NewId, pGeometry)
{
}

/**
 * Constructor using Properties
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::EvmTurbulentEnergyDissipationRateElement(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties)
    : RANSConstitutiveElement<TDim, TNumNodes>(NewId, pGeometry, pProperties)
{
}

/**
 * Copy Constructor
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::EvmTurbulentEnergyDissipationRateElement(EvmTurbulentEnergyDissipationRateElement const& rOther)
    : RANSConstitutiveElement<TDim, TNumNodes>(rOther)
{
}

/**
 * Destructor
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::~EvmTurbulentEnergyDissipationRateElement()
{
}

///@}
///@name Operators
///@{

/// Assignment operator.
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes> & EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::operator=(EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes> const& rOther)
{
    BaseType::operator=(rOther);
    Flags::operator =(rOther);
    // mpProperties = rOther.mpProperties;
    return *this;
}

///@}
///@name Operations
///@{

/**
 * ELEMENTS inherited from this class have to implement next
 * Create and Clone methods: MANDATORY
 */

/**
 * creates a new element pointer
 * @param NewId: the ID of the new element
 * @param ThisNodes: the nodes of the new element
 * @param pProperties: the properties assigned to the new element
 * @return a Pointer to the new element
 */
template<unsigned int TDim, unsigned int TNumNodes>
Element::Pointer EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::Create(
    IndexType NewId,
    NodesArrayType const& ThisNodes,
    PropertiesType::Pointer pProperties) const
{
    KRATOS_TRY
    return Kratos::make_shared<EvmTurbulentEnergyDissipationRateElement>(NewId, Element::GetGeometry().Create(ThisNodes), pProperties);
    KRATOS_CATCH("");
}

/**
 * creates a new element pointer
 * @param NewId: the ID of the new element
 * @param pGeom: the geometry to be employed
 * @param pProperties: the properties assigned to the new element
 * @return a Pointer to the new element
 */
template<unsigned int TDim, unsigned int TNumNodes>
Element::Pointer EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::Create(
    IndexType NewId,
    GeometryType::Pointer pGeom,
    PropertiesType::Pointer pProperties) const
{
    KRATOS_TRY
    return Kratos::make_shared<EvmTurbulentEnergyDissipationRateElement>(NewId, pGeom, pProperties);
    KRATOS_CATCH("");
}

/**
 * creates a new element pointer and clones the previous element data
 * @param NewId: the ID of the new element
 * @param ThisNodes: the nodes of the new element
 * @param pProperties: the properties assigned to the new element
 * @return a Pointer to the new element
 */
template<unsigned int TDim, unsigned int TNumNodes>
Element::Pointer EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::Clone(IndexType NewId, NodesArrayType const& ThisNodes) const
{
    KRATOS_TRY
    return Kratos::make_shared<EvmTurbulentEnergyDissipationRateElement>(NewId, Element::GetGeometry().Create(ThisNodes), Element::pGetProperties());
    KRATOS_CATCH("");
}

/**
 * this determines the elemental equation ID vector for all elemental
 * DOFs
 * @param rResult: the elemental equation ID vector
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::EquationIdVector(EquationIdVectorType& rResult, ProcessInfo& CurrentProcessInfo)
{
    unsigned int number_of_nodes = Element::GetGeometry().PointsNumber();
    if (rResult.size() != number_of_nodes)
        rResult.resize(number_of_nodes, false);

      for (unsigned int i = 0; i < number_of_nodes; i++)
    rResult[i] = Element::GetGeometry()[i].GetDof(TURBULENT_ENERGY_DISSIPATION_RATE).EquationId();


}

/**
 * determines the elemental list of DOFs
 * @param ElementalDofList: the list of DOFs
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::GetDofList(DofsVectorType& rElementalDofList, ProcessInfo& CurrentProcessInfo)
{
    unsigned int number_of_nodes = Element::GetGeometry().PointsNumber();
    if (rElementalDofList.size() != number_of_nodes)
        rElementalDofList.resize(number_of_nodes);

      for (unsigned int i = 0; i < number_of_nodes; i++)
    rElementalDofList[i] = Element::GetGeometry()[i].pGetDof(TURBULENT_ENERGY_DISSIPATION_RATE);


}

/**
 * ELEMENTS inherited from this class have to implement next
 * CalculateLocalSystem, CalculateLeftHandSide and CalculateRightHandSide methods
 * they can be managed internally with a private method to do the same calculations
 * only once: MANDATORY
 */

/**
 * this is called during the assembling process in order
 * to calculate all elemental contributions to the global system
 * matrix and the right hand side
 * @param rLeftHandSideMatrix: the elemental left hand side matrix
 * @param rRightHandSideVector: the elemental right hand side
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::CalculateLocalSystem(
    MatrixType& rLeftHandSideMatrix,
    VectorType& rRightHandSideVector,
    ProcessInfo& rCurrentProcessInfo)
{
}

/**
 * this is called during the assembling process in order
 * to calculate the elemental left hand side matrix only
 * @param rLeftHandSideMatrix: the elemental left hand side matrix
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::CalculateLeftHandSide(MatrixType& rLeftHandSideMatrix, ProcessInfo& rCurrentProcessInfo)
{
}

/**
 * this is called during the assembling process in order
 * to calculate the elemental right hand side vector only
 * @param rRightHandSideVector: the elemental right hand side vector
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::CalculateRightHandSide(VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo)
{
    KRATOS_TRY

    BaseType::CalculateRightHandSide(rRightHandSideVector, rCurrentProcessInfo);

    // Get Shape function data
    Vector GaussWeights;
    Matrix ShapeFunctions;
    ShapeFunctionDerivativesArrayType ShapeDerivatives;
    this->CalculateGeometryData(GaussWeights, ShapeFunctions, ShapeDerivatives);
    const unsigned int num_gauss_points = GaussWeights.size();

    const GeometryType rGeom = this->GetGeometry();

    const double beta = rCurrentProcessInfo[WALL_SMOOTHNESS_BETA];
    const double von_karman = rCurrentProcessInfo[WALL_VON_KARMAN];
    const double C_mu = rCurrentProcessInfo[TURBULENCE_RANS_C_MU];
    const double C1 = rCurrentProcessInfo[TURBULENCE_RANS_C1];
    const double C2 = rCurrentProcessInfo[TURBULENCE_RANS_C2];
    const double tke_sigma = rCurrentProcessInfo[TURBULENT_KINETIC_ENERGY_SIGMA];

    for (unsigned int g = 0; g < num_gauss_points; g++)
    {
        const auto& r_shape_derivatives = ShapeDerivatives[g];

        double velocity_divergence = 0.0;
        double epsilon = 0.0;
        double tke = 0.0;
        double wall_distance = 0.0;
        double nu = 0.0;
        array_1d<double, 3> velocity  = ZeroVector(3);

        for (unsigned int c = 0; c < TNumNodes; c++)
        {
            const array_1d<double,3>& r_velocity = rGeom[c].FastGetSolutionStepValue(VELOCITY);
            for (unsigned int k = 0; k < TDim; k++)
            {
                velocity_divergence += r_shape_derivatives(c,k) * r_velocity[k];
            }

            epsilon += ShapeFunctions(g, c) * rGeom[c].FastGetSolutionStepValue(TURBULENT_ENERGY_DISSIPATION_RATE);
            tke += ShapeFunctions(g, c) * rGeom[c].FastGetSolutionStepValue(TURBULENT_KINETIC_ENERGY);
            wall_distance += ShapeFunctions(g, c) * rGeom[c].GetValue(WALL_DISTANCE);
            nu += ShapeFunctions(g, c) * rGeom[c].FastGetSolutionStepValue(VISCOSITY);
            velocity += ShapeFunctions(g, c) * r_velocity;
        }

        const double velocity_magnitude = norm_2(velocity);
        auto log_law_wall_function = [velocity_magnitude, von_karman, wall_distance, nu, beta](double u_tau)
        {
            return u_tau - velocity_magnitude / ((1.0/von_karman) * std::log(u_tau * wall_distance / nu) + beta);
        };

        const double iterTol = 1e-5;
        const double maxIter = 10;
        const double u_tau = BrentIteration::FindRoot(log_law_wall_function, 1e-6, 300.0 * nu / wall_distance, iterTol, maxIter);
        double y_plus = u_tau * wall_distance / nu;

        if (y_plus < 11.06)
            y_plus = velocity_magnitude / u_tau;

        const double f_mu = 1 - std::exp(-0.0115 * y_plus);
        const double nu_t = C_mu * f_mu * std::pow(tke, 2.0) / epsilon;

        BoundedMatrix<double, TDim, TDim> velocity_gradient_matrix;
        velocity_gradient_matrix.clear();
        for (unsigned int c = 0; c < TNumNodes; c++)
        {
            const array_1d<double,3>& r_velocity = rGeom[c].FastGetSolutionStepValue(VELOCITY);
            for (unsigned int i = 0; i < TDim; i++)
            {
                for (unsigned int j = 0; j < TDim; j++)
                {
                    velocity_gradient_matrix(i,j) += r_shape_derivatives(c, j) * r_velocity[i];
                }
            }
        }

        BoundedMatrix<double, TDim, TDim> temp;
        noalias(temp) = velocity_gradient_matrix + trans(velocity_gradient_matrix);
        const double norm_f = std::pow(norm_frobenius(temp), 2.0);
        const double gamma = epsilon / tke;

        for (unsigned int a = 0; a < TNumNodes; a++)
        {
            rRightHandSideVector[a] += GaussWeights[g] * ShapeFunctions(g, a) * gamma * C1 * 0.5 * nu_t * norm_f;
        }
    }

    KRATOS_CATCH("");
}

/**
 * this is called during the assembling process in order
 * to calculate the first derivatives contributions for the LHS and RHS
 * @param rLeftHandSideMatrix: the elemental left hand side matrix
 * @param rRightHandSideVector: the elemental right hand side
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::CalculateFirstDerivativesContributions(
    MatrixType& rLeftHandSideMatrix,
    VectorType& rRightHandSideVector,
    ProcessInfo& rCurrentProcessInfo)
{
    if (rLeftHandSideMatrix.size1() != 0)
        rLeftHandSideMatrix.resize(0, 0, false);
    if (rRightHandSideVector.size() != 0)
        rRightHandSideVector.resize(0, false);
}

/**
 * this is called during the assembling process in order
 * to calculate the elemental left hand side matrix for the first derivatives constributions
 * @param rLeftHandSideMatrix: the elemental left hand side matrix
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::CalculateFirstDerivativesLHS(MatrixType& rLeftHandSideMatrix, ProcessInfo& rCurrentProcessInfo)
{
    if (rLeftHandSideMatrix.size1() != 0)
        rLeftHandSideMatrix.resize(0, 0, false);
}

/**
 * this is called during the assembling process in order
 * to calculate the elemental right hand side vector for the first derivatives constributions
 * @param rRightHandSideVector: the elemental right hand side vector
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::CalculateFirstDerivativesRHS(VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo)
{
    if (rRightHandSideVector.size() != 0)
        rRightHandSideVector.resize(0, false);
}

/**
 * ELEMENTS inherited from this class must implement this methods
 * if they need to add dynamic element contributions
 * note: second derivatives means the accelerations if the displacements are the dof of the analysis
 * note: time integration parameters must be set in the rCurrentProcessInfo before calling these methods
 * CalculateSecondDerivativesContributions,
 * CalculateSecondDerivativesLHS, CalculateSecondDerivativesRHS methods are : OPTIONAL
 */


/**
 * this is called during the assembling process in order
 * to calculate the second derivative contributions for the LHS and RHS
 * @param rLeftHandSideMatrix: the elemental left hand side matrix
 * @param rRightHandSideVector: the elemental right hand side
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::CalculateSecondDerivativesContributions(
    MatrixType& rLeftHandSideMatrix,
    VectorType& rRightHandSideVector,
    ProcessInfo& rCurrentProcessInfo)
{
    if (rLeftHandSideMatrix.size1() != 0)
        rLeftHandSideMatrix.resize(0, 0, false);
    if (rRightHandSideVector.size() != 0)
        rRightHandSideVector.resize(0, false);
}

/**
 * this is called during the assembling process in order
 * to calculate the elemental left hand side matrix for the second derivatives constributions
 * @param rLeftHandSideMatrix: the elemental left hand side matrix
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::CalculateSecondDerivativesLHS(
    MatrixType& rLeftHandSideMatrix,
    ProcessInfo& rCurrentProcessInfo)
{
    if (rLeftHandSideMatrix.size1() != 0)
        rLeftHandSideMatrix.resize(0, 0, false);
}

/**
 * this is called during the assembling process in order
 * to calculate the elemental right hand side vector for the second derivatives constributions
 * @param rRightHandSideVector: the elemental right hand side vector
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::CalculateSecondDerivativesRHS(
    VectorType& rRightHandSideVector,
    ProcessInfo& rCurrentProcessInfo)
{
    if (rRightHandSideVector.size() != 0)
        rRightHandSideVector.resize(0, false);
}

/**
 * this is called during the assembling process in order
 * to calculate the elemental mass matrix
 * @param rMassMatrix: the elemental mass matrix
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::CalculateMassMatrix(MatrixType& rMassMatrix, ProcessInfo& rCurrentProcessInfo)
{
    KRATOS_TRY

    BaseType::CalculateMassMatrix(rMassMatrix, rCurrentProcessInfo);

    // Get Shape function data
    Vector GaussWeights;
    Matrix ShapeFunctions;
    ShapeFunctionDerivativesArrayType ShapeDerivatives;
    this->CalculateGeometryData(GaussWeights, ShapeFunctions, ShapeDerivatives);
    const unsigned int num_gauss_points = GaussWeights.size();


    for (unsigned int a = 0; a < TNumNodes; a++)
    {
        for (unsigned int b = 0; b < TNumNodes; b++)
        {
            for (unsigned int g = 0; g < num_gauss_points; g++)
                rMassMatrix(a,b) += GaussWeights[g] * ShapeFunctions(g, a) * ShapeFunctions(g, b);
        }
    }

    KRATOS_CATCH("");
}

/**
 * this is called during the assembling process in order
 * to calculate the elemental damping matrix
 * @param rDampingMatrix: the elemental damping matrix
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::CalculateDampingMatrix(MatrixType& rDampingMatrix, ProcessInfo& rCurrentProcessInfo)
{
    KRATOS_TRY

    BaseType::CalculateDampingMatrix(rDampingMatrix, rCurrentProcessInfo);

    // Get Shape function data
    Vector GaussWeights;
    Matrix ShapeFunctions;
    ShapeFunctionDerivativesArrayType ShapeDerivatives;
    this->CalculateGeometryData(GaussWeights, ShapeFunctions, ShapeDerivatives);
    const unsigned int num_gauss_points = GaussWeights.size();

    const GeometryType rGeom = this->GetGeometry();

    const double beta = rCurrentProcessInfo[WALL_SMOOTHNESS_BETA];
    const double von_karman = rCurrentProcessInfo[WALL_VON_KARMAN];
    const double C_mu = rCurrentProcessInfo[TURBULENCE_RANS_C_MU];
    const double C1 = rCurrentProcessInfo[TURBULENCE_RANS_C1];
    const double C2 = rCurrentProcessInfo[TURBULENCE_RANS_C2];
    const double tke_sigma = rCurrentProcessInfo[TURBULENT_KINETIC_ENERGY_SIGMA];

    for (unsigned int g = 0; g < num_gauss_points; g++)
    {
        const auto& r_shape_derivatives = ShapeDerivatives[g];

        double velocity_divergence = 0.0;
        double epsilon = 0.0;
        double tke = 0.0;
        double wall_distance = 0.0;
        double nu = 0.0;
        array_1d<double, 3> velocity  = ZeroVector(3);

        for (unsigned int c = 0; c < TNumNodes; c++)
        {
            const array_1d<double,3>& r_velocity = rGeom[c].FastGetSolutionStepValue(VELOCITY);
            for (unsigned int k = 0; k < TDim; k++)
            {
                velocity_divergence += r_shape_derivatives(c,k) * r_velocity[k];
            }

            epsilon += ShapeFunctions(g, c) * rGeom[c].FastGetSolutionStepValue(TURBULENT_ENERGY_DISSIPATION_RATE);
            tke += ShapeFunctions(g, c) * rGeom[c].FastGetSolutionStepValue(TURBULENT_KINETIC_ENERGY);
            wall_distance += ShapeFunctions(g, c) * rGeom[c].GetValue(WALL_DISTANCE);
            nu += ShapeFunctions(g, c) * rGeom[c].FastGetSolutionStepValue(VISCOSITY);
            velocity += ShapeFunctions(g, c) * r_velocity;
        }

        const double velocity_magnitude = norm_2(velocity);
        auto log_law_wall_function = [velocity_magnitude, von_karman, wall_distance, nu, beta](double u_tau)
        {
            return u_tau - velocity_magnitude / ((1.0/von_karman) * std::log(u_tau * wall_distance / nu) + beta);
        };

        const double iterTol = 1e-5;
        const double maxIter = 10;
        const double u_tau = BrentIteration::FindRoot(log_law_wall_function, 1e-6, 300.0 * nu / wall_distance, iterTol, maxIter);
        double y_plus = u_tau * wall_distance / nu;

        if (y_plus < 11.06)
            y_plus = velocity_magnitude / u_tau;

        const double f_mu = 1 - std::exp(-0.0115 * y_plus);
        const double f2 = 1 - 0.22 * std::exp(std::pow(tke, 2) / (6.0 * nu * epsilon));
        const double nu_t = C_mu * f_mu * std::pow(tke, 2.0) / epsilon;
        const double gamma = epsilon / tke;

        for (unsigned int a = 0; a < TNumNodes; a++)
        {
            for (unsigned int b = 0; b < TNumNodes; b++)
            {
                double value = 0.0;

                value += velocity_divergence;
                value += C2 * f2 * gamma;
                value += 2.0 * nu / std::pow(wall_distance, 2.0) * std::exp(-0.5 * y_plus);
                value *= ShapeFunctions(g, a) * ShapeFunctions(g, b);

                for (unsigned int i = 0; i < TDim; i++)
                    value += (nu_t / tke_sigma) * r_shape_derivatives(a, i) * r_shape_derivatives(b, i);

                rDampingMatrix(a,b) += GaussWeights[g] * value;
            }
        }
    }

    KRATOS_CATCH("");
}

/**
 * This method provides the place to perform checks on the completeness of the input
 * and the compatibility with the problem options as well as the contitutive laws selected
 * It is designed to be called only once (or anyway, not often) typically at the beginning
 * of the calculations, so to verify that nothing is missing from the input
 * or that no common error is found.
 * @param rCurrentProcessInfo
 * this method is: MANDATORY
 */
template<unsigned int TDim, unsigned int TNumNodes>
int EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::Check(const ProcessInfo& rCurrentProcessInfo)
{
    KRATOS_TRY

    KRATOS_ERROR_IF(this->Id() < 1) <<"EvmTurbulentEnergyDissipationRateElement found with Id 0 or negative" << std::endl;

    KRATOS_ERROR_IF(this->GetGeometry().Area() <= 0) << "On EvmTurbulentEnergyDissipationRateElement -> "
        << this->Id() <<  "; Area cannot be less than or equal to 0" << std::endl;

    return 0;

    KRATOS_CATCH("");
}

///@}
///@name Access
///@{


///@}
///@name Inquiry
///@{


///@}
///@name Input and output
///@{

/// Turn back information as a string.

template<unsigned int TDim, unsigned int TNumNodes>
std::string EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::Info() const {
    std::stringstream buffer;
    buffer << "EvmTurbulentEnergyDissipationRateElement #" << Element::Id();
    return buffer.str();
}

/// Print information about this object.

template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::PrintInfo(std::ostream& rOStream) const {
    rOStream << "EvmTurbulentEnergyDissipationRateElement #" << Element::Id();
}

/// Print object's data.

template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::PrintData(std::ostream& rOStream) const {
    Element::pGetGeometry()->PrintData(rOStream);
}

///@}
///@name Friends
///@{

///@}

///@name Protected static Member Variables
///@{

///@}
///@name Protected member Variables
///@{

///@}
///@name Protected Operators
///@{

///@}
///@name Protected Operations
///@{

///@}
///@name Protected  Access
///@{

///@}
///@name Protected Inquiry
///@{

///@}
///@name Protected LifeCycle
///@{

///@}

///@name Static Member Variables
///@{

///@}
///@name Member Variables
///@{

///@}
///@name Private Operators
///@{

///@}
///@name Private Operations
///@{

///@}
///@name Serialization
///@{

template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::save(Serializer& rSerializer) const
{
    KRATOS_SERIALIZE_SAVE_BASE_CLASS(rSerializer, Element );

    // List
    // To be completed with the class member list
}

template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>::load(Serializer& rSerializer)
{
    KRATOS_SERIALIZE_LOAD_BASE_CLASS(rSerializer, Element );

    // List
    // To be completed with the class member list
}

///@}
///@name Private  Access
///@{

///@}
///@name Private Inquiry
///@{

///@}
///@name Un accessible methods
///@{

///@}
///@name Type Definitions
///@{

///@}
///@name Input and output
///@{

/// input stream function
template<unsigned int TDim, unsigned int TNumNodes>
inline std::istream & operator >> (std::istream& rIStream, EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>& rThis);

/// output stream function
template<unsigned int TDim, unsigned int TNumNodes>
inline std::ostream & operator << (std::ostream& rOStream, const EvmTurbulentEnergyDissipationRateElement<TDim, TNumNodes>& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << " : " << std::endl;
    rThis.PrintData(rOStream);
    return rOStream;
}

// Class template instantiation

template class EvmTurbulentEnergyDissipationRateElement<2, 3>;
template class EvmTurbulentEnergyDissipationRateElement<3, 4>;
template class EvmTurbulentEnergyDissipationRateElement<2, 4>;
template class EvmTurbulentEnergyDissipationRateElement<3, 8>;


} // namespace Kratos.
