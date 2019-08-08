//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   Kratos default license: kratos/license.txt
//
//  Main authors:    Thomas Oberbichler
//                   Tobias Teschemacher
//
//  Ported from the ANurbs library (https://github.com/oberbichler/ANurbs)
//

#if !defined(KRATOS_NURBS_SURFACE_GEOMETRY_H_INCLUDED )
#define  KRATOS_NURBS_SURFACE_GEOMETRY_H_INCLUDED

// System includes
#include <stdexcept>
#include <vector>

#include "includes/ublas_interface.h"

// External includes

// Project includes
#include "geometries/geometry.h"

#include "geometries/nurbs_shape_function_utilities/nurbs_surface_shape_functions.h"
#include "geometries/nurbs_shape_function_utilities/nurbs_interval.h"



namespace Kratos {

template <int TWorkingSpaceDimension, class TPointType>
class NurbsSurfaceGeometry : public Geometry<TPointType>
{
public:
    ///@name Type Definitions
    ///@{
    /// Geometry as base class.
    typedef Geometry<TPointType> BaseType;
    typedef NurbsSurfaceGeometry<TWorkingSpaceDimension, TPointType> GeometryType;

    typedef typename BaseType::IndexType IndexType;
    typedef typename BaseType::SizeType SizeType;

    /** Array of counted pointers to point. This type used to hold
        geometry's points.*/
    typedef  typename BaseType::PointsArrayType PointsArrayType;
    typedef  typename BaseType::CoordinatesArrayType CoordinatesArrayType;

    /// Counted pointer of NurbsSurfaceShapeFunction
    KRATOS_CLASS_INTRUSIVE_POINTER_DEFINITION(NurbsSurfaceGeometry);
    ///@}
    ///@name Life Cycle
    ///@{

    /* Conctructor for B-Spline surfaces. */
    NurbsSurfaceGeometry(
        const PointsArrayType& rThisPoints,
        const SizeType PolynomialDegreeU,
        const SizeType PolynomialDegreeV,
        const Vector& rKnotsU,
        const Vector& rKnotsV)
        : BaseType(PointsArrayType(), &msGeometryData)
        , mPolynomialDegreeU(PolynomialDegreeU)
        , mPolynomialDegreeV(PolynomialDegreeV)
        , mKnotsU(rKnotsU)
        , mKnotsV(rKnotsV)
        , mIsRational(false)
    {
        //KRATOS_DEBUG_ERROR_IF(rKnots.size() != NurbsUtilities::GetNumberOfKnots(PolynomialDegree, rThisPoints.size()))
        //    << "Number of knots and control points do not match!" << std::endl;
    }

    /* Conctructor for NURBS surfaces. */
    NurbsSurfaceGeometry(
        const PointsArrayType& rThisPoints,
        const SizeType PolynomialDegreeU,
        const SizeType PolynomialDegreeV,
        const Vector& rKnotsU,
        const Vector& rKnotsV,
        const Vector& rWeights)
        : BaseType(PointsArrayType(), &msGeometryData)
        , mPolynomialDegreeU(PolynomialDegreeU)
        , mPolynomialDegreeV(PolynomialDegreeV)
        , mKnotsU(rKnotsU)
        , mKnotsV(rKnotsV)
        , mWeights(rWeights)
        , mIsRational(false)
    {
        KRATOS_DEBUG_ERROR_IF(rKnots.size() != NurbsUtilities::GetNumberOfKnots(PolynomialDegree, rThisPoints.size()))
            << "Number of knots and control points do not match!" << std::endl;

        KRATOS_DEBUG_ERROR_IF(rWeights.size() != rThisPoints.size())
            << "Number of control points and weights do not match!" << std::endl;
    }

    explicit NurbsSurfaceGeometry(const PointsArrayType& ThisPoints)
        : BaseType(ThisPoints, &msGeometryData)
    {
    }

    /* Copy constructor.*/
    NurbsSurfaceGeometry(NurbsSurfaceGeometry const& rOther)
        : BaseType(rOther)
    {
    }

    /* Copy constructor from a geometry with different point type.*/
    template<class TOtherPointType> NurbsSurfaceGeometry(
        NurbsSurfaceGeometry<TWorkingSpaceDimension, TOtherPointType> const& rOther)
        : BaseType(rOther)
    {
    }

    /* Destructor.*/
    ~NurbsSurfaceGeometry() override {}

    GeometryData::KratosGeometryFamily GetGeometryFamily() const override
    {
        return GeometryData::Kratos_generic_family;
    }

    GeometryData::KratosGeometryType GetGeometryType() const override
    {
        return GeometryData::Kratos_generic_type;
    }

    ///@}
    ///@name Get and Set functions
    ///@{

    /* Checks if shape functions are rational or not.
    @return true if NURBS, false if B-Splines (all weights are considered as 1)
    */
    bool IsRational() const
    {
        return mWeights.size() != 0;
    }

    /* Get Knot vector in u-direction. This vector is defined to have
    a multiplicity of p at the beginning and end (NOT: p + 1).
    @return knot vector. */
    const Vector& KnotsU() const
    {
        return mKnotsU;
    }

    /* Get Knot vector in v-direction. This vector is defined to have
    a multiplicity of p at the beginning and end (NOT: p + 1).
    @return knot vector. */
    const Vector& KnotsV() const
    {
        return mKnotsV;
    }

    /* @return Gives the size of the knot vector in u-direction.
    */
    SizeType NumberOfKnotsU() const
    {
        return mKnotsU.size();
    }

    /* @return Gives the size of the knot vector in v-direction.
    */
    SizeType NumberOfKnotsV() const
    {
        return mKnotsV.size();
    }

    /* Get Weights vector. All values are 1.0 for B-Splines, for NURBS those can be unequal 1.0.
    @return weights vector.
    */
    const Vector& Weights() const
    {
        return mWeights;
    }

    /* Provides the natural boundaries of the NURBS/B-Spline curve.
    @return domain interval.
    */
    Interval DomainIntervalU() const
    {
        return Interval(
            mKnotsU[mPolynomialDegreeU - 1],
            mKnotsU[NumberOfKnotsU() - mPolynomialDegreeU]);
    }

    /* Provides the natural boundaries of the NURBS/B-Spline curve.
    @return domain interval.
    */
    Interval DomainIntervalV() const
    {
        return Interval(
            mKnotsV[mPolynomialDegreeV - 1],
            mKnotsV[NumberOfKnotsV() - mPolynomialDegreeV]);
    }

    /* Provides all knot span intervals of the surface in u-direction.
    @return vector of knot span intervals.
    */
    std::vector<Interval> KnotSpanIntervalsU() const
    {
        const SizeType first_span = mPolynomialDegreeU - 1;
        const SizeType last_span = NumberOfKnotsU() - mPolynomialDegreeU - 1;

        const SizeType number_of_spans = last_span - first_span + 1;

        std::vector<Interval> result(number_of_spans);

        for (int i = 0; i < number_of_spans; i++) {
            const double t0 = mKnotsU[first_span + i];
            const double t1 = mKnotsU[first_span + i + 1];

            result[i] = Interval(t0, t1);
        }

        return result;
    }

    /* Provides all knot span intervals of the surface in u-direction.
    @return vector of knot span intervals.
    */
    std::vector<Interval> KnotSpanIntervalsV() const
    {
        const SizeType first_span = mPolynomialDegreeV - 1;
        const SizeType last_span = NumberOfKnotsV() - mPolynomialDegreeV - 1;

        const SizeType number_of_spans = last_span - first_span + 1;

        std::vector<Interval> result(number_of_spans);

        for (int i = 0; i < number_of_spans; i++) {
            const double t0 = mKnotsV[first_span + i];
            const double t1 = mKnotsV[first_span + i + 1];

            result[i] = Interval(t0, t1);
        }

        return result;
    }

    ///@}
    ///@name Operations
    ///@{

    /** This method maps from local space to working space and computes the
    * number of derivatives at the local space parameter in the dimension of the object.
    * @param LocalCoordinates The local coordinates in dimension space
    * @param Derivative Number of computed derivatives
    * @return std::vector<array_1d<double, 3>> with the coordinates in working space
    * @see PointLocalCoordinates
    */
    //std::vector<CoordinatesArrayType> GlobalDerivatives(
    //    const CoordinatesArrayType& rCoordinates,
    //    const SizeType DerivativeOrder) const
    //{
    //    NurbsCurveShapeFunction shape_function_container(mPolynomialDegree, DerivativeOrder);

    //    if (IsRational()) {
    //        shape_function_container.ComputeNurbsShapeFunctionValues(mKnots, mWeights, rCoordinates[0]);
    //    }
    //    else {
    //        shape_function_container.ComputeBSplineShapeFunctionValues(mKnots, rCoordinates[0]);
    //    }

    //    std::vector<CoordinatesArrayType> derivatives(shape_function_container.NumberOfShapeFunctionRows());

    //    for (IndexType order = 0; order < shape_function_container.NumberOfShapeFunctionRows(); order++) {
    //        IndexType index_0 = shape_function_container.GetFirstNonzeroControlPoint();
    //        derivatives[order] = (*this)[index_0] * shape_function_container(order, 0);

    //        for (IndexType i = 1; i < shape_function_container.NumberOfNonzeroControlPoints(); i++) {
    //            IndexType index = shape_function_container.GetFirstNonzeroControlPoint() + i;

    //            derivatives[order] += (*this)[index] * shape_function_container(order, i);
    //        }
    //    }

    //    return derivatives;
    //}

    /** This method maps from dimension space to working space.
    * @param rResult array_1d<double, 3> with the coordinates in working space
    * @param LocalCoordinates The local coordinates in dimension space
    * @return array_1d<double, 3> with the coordinates in working space
    * @see PointLocalCoordinates
    */
    //CoordinatesArrayType& GlobalCoordinates(
    //    CoordinatesArrayType& rResult,
    //    const CoordinatesArrayType& rLocalCoordinates
    //) const override
    //{
    //    NurbsSurfaceShapeFunction shape_function_container(mPolynomialDegreeU, mPolynomialDegreeV, 0);

    //    if (IsRational()) {
    //        shape_function_container.ComputeNurbsShapeFunctionValues(
    //            mKnotsU, mKnotsV, mWeights, rLocalCoordinates[0], rLocalCoordinates[1]);
    //    }
    //    else {
    //        shape_function_container.ComputeBSplineShapeFunctionValues(
    //            mKnotsU, mKnotsV, rLocalCoordinates[0], rLocalCoordinates[1]);
    //    }

    //    noalias(rResult) = ZeroVector(3);
    //    for (IndexType i = 0; i < shape_function_container.NumberOfNonzeroControlPoints(); i++) {
    //        const IndexType index = shape_function_container.GetFirstNonzeroControlPoint() + i;

    //        rResult += (*this)[index] * shape_function_container(0, i);
    //    }
    //    return rResult;
    //}

    ///@}
    ///@name Shape Function
    ///@{

    //Vector& ShapeFunctionsValues(
    //    Vector &rResult,
    //    const CoordinatesArrayType& rCoordinates) const override
    //{
    //    NurbsCurveShapeFunction shape_function_container(mPolynomialDegree, 0);

    //    if (IsRational()) {
    //        shape_function_container.ComputeNurbsShapeFunctionValues(mKnots, mWeights, rCoordinates[0]);
    //    }
    //    else {
    //        shape_function_container.ComputeBSplineShapeFunctionValues(mKnots, rCoordinates[0]);
    //    }

    //    if (rResult.size() != shape_function_container.NumberOfNonzeroControlPoints())
    //        rResult.resize(shape_function_container.NumberOfNonzeroControlPoints());

    //    for (int i = 0; i < shape_function_container.NumberOfNonzeroControlPoints(); i++) {
    //        rResult[i] = shape_function_container(0, i);
    //    }

    //    return rResult;
    //}

    //Matrix& ShapeFunctionsLocalGradients(
    //    Matrix& rResult,
    //    const CoordinatesArrayType& rCoordinates) const override
    //{
    //    NurbsCurveShapeFunction shape_function_container(mPolynomialDegree, 1);

    //    if (IsRational()) {
    //        shape_function_container.ComputeNurbsShapeFunctionValues(mKnots, mWeights, rCoordinates[0]);
    //    }
    //    else {
    //        shape_function_container.ComputeBSplineShapeFunctionValues(mKnots, rCoordinates[0]);
    //    }

    //    if (rResult.size1() != 1
    //        && rResult.size2() != shape_function_container.NumberOfNonzeroControlPoints())
    //        rResult.resize(1, shape_function_container.NumberOfNonzeroControlPoints());

    //    for (IndexType i = 0; i < shape_function_container.NumberOfNonzeroControlPoints(); i++) {
    //        rResult(0, i) = shape_function_container(1, i);
    //    }

    //    return rResult;
    //}

    //void ShapeFunctionDerivatives(
    //    GeometryData::IntegrationMethod ThisIntegrationMethod,
    //    IntegrationPointsArrayType& rIntegrationPoints,
    //    const int DerivativeOrder) const
    //{
    //    NurbsCurveShapeFunction shape_function_container(mPolynomialDegree, 0);

    //    int number_of_integration_points = rIntegrationPoints.size();

    //    Matrix shape_functions_values = ZeroMatrix(number_of_integration_points, shape_function_container.NumberOfNonzeroControlPoints());
    //    DenseVector<DenseVector<Matrix>> shape_function_derivatives_integration_points(number_of_integration_points);

    //    for (IndexType ip_itr = 0; ip_itr < number_of_integration_points; ++ip_itr)
    //    {
    //        if (IsRational()) {
    //            shape_function_container.ComputeNurbsShapeFunctionValues(mKnots, mWeights, rIntegrationPoints[ip_itr][0]);
    //        }
    //        else {
    //            shape_function_container.ComputeBSplineShapeFunctionValues(mKnots, rIntegrationPoints[ip_itr][0]);
    //        }

    //        for (IndexType i = 0; i < shape_function_container.NumberOfNonzeroControlPoints(); i++) {
    //            shape_functions_values(ip_itr, i) = shape_function_container(ip_itr, i);
    //        }

    //        DenseVector<Matrix> shape_function_derivatives_array(DerivativeOrder);
    //        for (IndexType derivative_order_itr = 1; derivative_order_itr < DerivativeOrder; ++derivative_order_itr)
    //        {
    //            Matrix shape_function_derivatives_values = ZeroMatrix(1, shape_function_container.NumberOfNonzeroControlPoints());
    //            for (int i = 0; i < shape_function_container.NumberOfNonzeroControlPoints(); i++) {
    //                shape_function_derivatives_values(0, i) = shape_function_container(derivative_order_itr, i);
    //            }
    //            shape_function_derivatives_array[derivative_order_itr] = shape_function_derivatives_values;
    //        }
    //        shape_function_derivatives_integration_points[ip_itr] = shape_function_derivatives_array;
    //    }

    //    GeometryShapeFunctionContainer<GeometryData::IntegrationMethod>(
    //        ThisIntegrationMethod,
    //        rIntegrationPoints,
    //        shape_functions_values,
    //        shape_function_derivatives_integration_points);
    //}

    ///@}
    ///@name Information
    ///@{
    std::string Info() const override
    {
        return TWorkingSpaceDimension + " dimensional nurbs surface.";
    }

    void PrintInfo(std::ostream& rOStream) const override
    {
        rOStream << TWorkingSpaceDimension << " dimensional nurbs surface.";
    }

    void PrintData(std::ostream& rOStream) const override
    {
    }
    ///@}

protected:

private:
    ///@name Private Static Member Variables
    ///@{

    static const GeometryData msGeometryData;

    ///@}
    ///@name Private Member Variables
    ///@{

    SizeType mPolynomialDegreeU;
    SizeType mPolynomialDegreeV;
    Vector mKnotsU;
    Vector mKnotsV;
    bool mIsRational;
    Vector mWeights;

    ///@}
    ///@name Private Operations
    ///@{

    ///@}
    ///@name Private Serialization
    ///@{

    friend class Serializer;

    void save(Serializer& rSerializer) const override
    {
        KRATOS_SERIALIZE_SAVE_BASE_CLASS(rSerializer, BaseType);
        rSerializer.save("PolynomialDegreeU", mPolynomialDegreeU);
        rSerializer.save("PolynomialDegreeV", mPolynomialDegreeV);
        rSerializer.save("KnotsU", mKnotsU);
        rSerializer.save("KnotsV", mKnotsV);
        rSerializer.save("Weights", mWeights);
    }

    void load(Serializer& rSerializer) override
    {
        KRATOS_SERIALIZE_LOAD_BASE_CLASS(rSerializer, BaseType);
        rSerializer.load("PolynomialDegreeU", mPolynomialDegreeU);
        rSerializer.load("PolynomialDegreeV", mPolynomialDegreeV);
        rSerializer.load("KnotsU", mKnotsU);
        rSerializer.load("KnotsV", mKnotsV);
        rSerializer.load("Weights", mWeights);
    }

    NurbsSurfaceGeometry() : BaseType(PointsArrayType(), &msGeometryData) {};

    ///@}
    ///@name Private Friends
    ///@{

    template<int TWorkingSpaceDimension, class TOtherPointType> friend class NurbsSurfaceGeometry;

    ///@}
}; // class NurbsSurfaceGeometry

template<int TWorkingSpaceDimension, class TPointType>
const GeometryData NurbsSurfaceGeometry<TWorkingSpaceDimension, TPointType>::msGeometryData(
    2,
    TWorkingSpaceDimension,
    2,
    GeometryData::GI_GAUSS_1,
    {}, {}, {});

} // namespace Kratos

#endif // KRATOS_NURBS_SURFACE_GEOMETRY_H_INCLUDED defined