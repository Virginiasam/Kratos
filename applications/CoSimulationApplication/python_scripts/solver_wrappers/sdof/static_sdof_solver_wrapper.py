from __future__ import print_function, absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7

# Importing the Kratos Library
import KratosMultiphysics as KM
import KratosMultiphysics.CoSimulationApplication as KMC

# Importing the base class
from KratosMultiphysics.CoSimulationApplication.base_classes.co_simulation_solver_wrapper import CoSimulationSolverWrapper

# Other imports
from .sdof_static_solver import SDoFStaticSolver
from .sdof_solver_wrapper import SdofSolverWrapper

def Create(settings, solver_name):
    return SdofStaticSolverWrapper(settings, solver_name)

class SdofStaticSolverWrapper(SdofSolverWrapper):
    """ This class implements a wrapper for an SDof solver to be used in CoSimulation
    """
    def __init__(self, settings, solver_name):
        CoSimulationSolverWrapper.__init__(self,settings, solver_name)

        input_file_name = self.settings["solver_wrapper_settings"]["input_file"].GetString()

        self.mp = self.model.CreateModelPart("Sdof_Static")
        self.mp.ProcessInfo[KM.DOMAIN_SIZE] = 1
        self._sdof_solver = SDoFStaticSolver(input_file_name)

    def SolveSolutionStep(self):
        self._sdof_solver.SetSolutionStepValue("ROOT_POINT_DISPLACEMENT", self.mp[KMC.SCALAR_ROOT_POINT_DISPLACEMENT], 0)
        self._sdof_solver.SetSolutionStepValue("LOAD",                    self.mp[KMC.SCALAR_FORCE], 0)

        self._sdof_solver.SolveSolutionStep()

        self.mp[KMC.SCALAR_DISPLACEMENT]        = self._sdof_solver.GetSolutionStepValue("DISPLACEMENT", 0)
        self.mp[KMC.SCALAR_REACTION]            = self._sdof_solver.GetSolutionStepValue("REACTION", 0)

    def Check(self):
        # making sure only a set of vaiables can be used
        admissible_variables = [
            "SCALAR_FORCE",
            "SCALAR_DISPLACEMENT",
            "SCALAR_REACTION",
        ]
        for data in self.data_dict.values():
            if data.variable.Name() not in admissible_variables:
                raise Exception('Variable "{}" of interface data "{}" of solver "{}" cannot be used for the SDof Solver!\nOnly the following variables are allowed: {}'.format(data.variable.Name(), data.name, data.solver_name, admissible_variables))
