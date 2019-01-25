//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:     BSD License
//           Kratos default license: kratos/IGAStructuralMechanicsApplication/license.txt
//
//  Main authors:    Tobias Tescheamacher
//                   Thomas Oberbichler
//

// System includes

// External includes

// Project includes
#include "nurbs_brep_modeler.h"


namespace Kratos
{
    void NurbsBrepModeler::ImportGeometry(BrepJsonIO& rBrepJsonIO, Parameters& rNurbsBrepGeometryJson)
    {
        std::vector<BrepModel> brep_model_vector = rBrepJsonIO.ImportNurbsBrepGeometry(m_model_part, rNurbsBrepGeometryJson);
        for (auto brep_model = brep_model_vector.begin(); brep_model != brep_model_vector.end(); ++brep_model)
        {
            m_brep_model_vector.push_back(*brep_model);
        }
    }

    void NurbsBrepModeler::ImportModelPart(ModelPart& model_part, Parameters& rModelPartParameters)
    {
        for (int i = 0; i < rModelPartParameters["element_condition_list"].size(); ++i)
        {
            Parameters element_parameter = rModelPartParameters["element_condition_list"][i];

            std::string sub_model_part_name = element_parameter["iga_model_part"].GetString();
            ModelPart& sub_model_part = model_part.HasSubModelPart(sub_model_part_name)
                ? model_part.GetSubModelPart(sub_model_part_name)
                : model_part.CreateSubModelPart(sub_model_part_name);

            std::string geometry_type = element_parameter["geometry_type"].GetString();

            if (geometry_type == "Geometry3DStrong")
            {
                bool success = false;
                for (int j = 0; j < element_parameter["brep_ids"].size(); ++j)
                {
                    int brep_id = element_parameter["brep_ids"][j].GetInt();
                    KRATOS_INFO("Nurbs Brep Modeler") << "brep id: " << brep_id << std::endl;
                    Vector parameter = element_parameter["parameters"]["local_parameters"].GetVector();
                    success = m_brep_model_vector[0].GetNodesGeometry(
                        sub_model_part, brep_id, parameter);
                }
                continue;
            }
            else
            {
                std::string type = element_parameter["parameters"]["type"].GetString();
                std::string name = element_parameter["parameters"]["name"].GetString();

                int shape_function_derivatives_order = element_parameter["parameters"]["shape_function_derivatives_order"].GetInt();


                std::vector<std::string> variable_list;
                for (int j = 0; j < element_parameter["parameters"]["variables"].size(); ++j)
                {
                    variable_list.push_back(element_parameter["parameters"]["variables"][j].GetString());
                }

                if (element_parameter.Has("brep_ids"))
                {
                    for (int j = 0; j < element_parameter["brep_ids"].size(); ++j)
                    {
                        int brep_id = element_parameter["brep_ids"][j].GetInt();
                        KRATOS_INFO("Nurbs Brep Modeler") << "brep id: " << brep_id << std::endl;
                        if (geometry_type == "Geometry3D")
                        {
                            bool success = m_brep_model_vector[0].GetIntegrationDomainGeometry(
                                sub_model_part, brep_id, type, name,
                                shape_function_derivatives_order, variable_list);
                        }
                        if (geometry_type == "BrepCoupling")
                        {
                            bool success = m_brep_model_vector[0].GetIntegrationDomainBrepCoupling(
                                sub_model_part, brep_id, type, name,
                                shape_function_derivatives_order, variable_list);
                        }
                        if (geometry_type == "Brep")
                        {
                            bool success = m_brep_model_vector[0].GetIntegrationDomainBrep(
                                sub_model_part, brep_id, type, name,
                                shape_function_derivatives_order, variable_list);
                        }
                    }
                }
                else
                {
                    if (geometry_type == "BrepCoupling")
                        bool success = m_brep_model_vector[0].GetIntegrationDomainBrepCoupling(
                            sub_model_part, type, name,
                            shape_function_derivatives_order, variable_list);
                }
            }
        }
    }

    NurbsBrepModeler::NurbsBrepModeler(ModelPart& rModelPart)
        : m_model_part(rModelPart)
    {
    }
}  // namespace Kratos.


