/*  Lattice Boltzmann sample, written in C++, using the OpenLB
 *  library
 *
 *  Copyright (C) 2011-2025 Christoph Gaul, Mathias J. Krause
 *  E-mail contact: info@openlb.net
 *  The most recent release of OpenLB can be downloaded at
 *  <http://www.openlb.net/>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 */

/* aneurysm
 * This example represents flow in an aneurysm.
 * The geometry is read from a STL file. Stress on the aneurysm wall can be visualized with the Mesh.pvd file.
 */

#include <olb.h>
#include <fstream>

using namespace olb;
using namespace olb::names;

using MyCase = Case<
  NavierStokes, Lattice<float, descriptors::D3Q19<>>
>;

Mesh<MyCase::value_t, MyCase::d> createMesh(MyCase::ParametersD& params)
{
  // Sentinel Security Check: Validate STL file existence
  // Prevents crash or undefined behavior when loading missing external files.
  std::string stlPath = params.get<parameters::STL_PATH>();
  std::ifstream f(stlPath);
  if (!f.good()) {
    throw std::runtime_error("Critical Error: STL file '" + stlPath + "' not found or not readable.");
  }
  f.close();

  return Mesh<MyCase::value_t,MyCase::d>::fromSTL(params);
}

void prepareGeometry(MyCase& myCase)
{
  using T        = MyCase::value_t;
  auto& params   = myCase.getParameters();
  auto& geometry = myCase.getGeometry();

  const T physDeltaX = params.get<parameters::PHYS_DELTA_X>();

  auto aneurysmI = myCase.getMesh().getSTL(params.get<parameters::STL_PATH>());
  IndicatorLayer3D<T> domain(*aneurysmI, params.get<parameters::MESH_PADDING>() * physDeltaX);

  geometry.rename(0, 2, domain);
  geometry.rename(2, 1, *aneurysmI);
  geometry.clean();

  std::vector<Vector<T, 3>> normals(5);
  normals[0] = {-0.026646, 0.963492, -0.266408};
  normals[1] = {0.906283, -0.171557, 0.386290};
  normals[2] = {-0.159757, 0.968927, -0.18883};
  normals[3] = {0.994170, -0.101600, -0.036091};
  normals[4] = {0.02343, 0.98639, -0.1627};

  std::vector<Vector<T, 3>> centerpoints(5);
  centerpoints[0] = {0.005072, 0.034537, -0.020140};
  centerpoints[1] = {0.032770, 0.018303, 0.014303};
  centerpoints[2] = {-0.0224, 0.0185, -0.02975};
  centerpoints[3] = {0.03653, 0.0152, -0.005};
  centerpoints[4] = {-0.017263, 0.0355, 0.0193};

  std::vector<T> radii(5);
  radii[0] = 0.001111;
  radii[1] = 0.001421;
  radii[2] = 0.002200;
  radii[3] = 0.001394;
  radii[4] = 0.002518;
  IndicatorCircle3D<T> inletCircle(centerpoints[0], normals[0], radii[0]);
  IndicatorCircle3D<T> inletCircle2(centerpoints[1], normals[1], radii[1]);
  IndicatorCircle3D<T> inletCircle3(centerpoints[2], normals[2], radii[2]);
  IndicatorCircle3D<T> outletCircle(centerpoints[3], normals[3], radii[3]);
  IndicatorCircle3D<T> outletCircle2(centerpoints[4], normals[4], radii[4]);

  IndicatorCylinder3D<T> inletCylinder(inletCircle, 2. * physDeltaX);
  IndicatorCylinder3D<T> inletCylinder2(inletCircle2, 2. * physDeltaX);
  IndicatorCylinder3D<T> inletCylinder3(inletCircle3, 2. * physDeltaX);
  IndicatorCylinder3D<T> outletCylinder(outletCircle, 2. * physDeltaX);
  IndicatorCylinder3D<T> outletCylinder2(outletCircle2, 2. * physDeltaX);

  geometry.rename(2, 4, 1, inletCylinder);
  geometry.rename(2, 4, 1, inletCylinder2);
  geometry.rename(2, 3, 1, inletCylinder3);
  geometry.rename(2, 4, 1, outletCylinder);
  geometry.rename(2, 4, 1, outletCylinder2);

  geometry.clean();
  geometry.checkForErrors();
  geometry.print();
}

void prepareLattice(MyCase& myCase)
{
  using T        = MyCase::value_t;
  auto& params   = myCase.getParameters();
  auto& geometry = myCase.getGeometry();
  auto& lattice  = myCase.getLattice(NavierStokes {});

  const T L   = 0.05 / params.get<parameters::RESOLUTION>();
  const T CFL = params.get<parameters::CFL>();
  const T Re  = params.get<parameters::REYNOLDS>();

  lattice.setUnitConverter(
      (T)L,               // physDeltaX: spacing between two lattice cells in [m]
      (T)CFL * L / 0.2,   // physDeltaT: time step in [s]
      (T)0.007,           // charPhysLength: reference length of simulation geometry in [m]
      (T)0.2,             // charPhysVelocity: highest expected velocity during simulation in [m/s]
      (T)0.2 * 0.05 / Re, // physViscosity: physical kinematic viscosity in [m^2/s] 3.7e-6
      (T)1080.0           // physDensity: physical density in [kg/m^3]
  );

  lattice.getUnitConverter().write();

  OstreamManager clout(std::cout, "prepareLattice");
  clout << "Prepare Lattice ..." << std::endl;

  // Material=1 -->bulk dynamics
  dynamics::set<BGKdynamics>(lattice, geometry, 1);

  // Material=2 -->bounce back
  boundary::set<boundary::BounceBack>(lattice, geometry, 2);

  // Material=3 -->fixed velocity
  // boundary::set<boundary::InterpolatedVelocity>(lattice, geometry, 3);

  // Material=4 -->fixed pressure
  // boundary::set<boundary::InterpolatedPressure>(lattice, geometry, 4);

  // Material=5 -->bounce back
  // boundary::set<boundary::BounceBack>(lattice, geometry, 5);
}

void setInitialValues(MyCase& myCase)
{
  auto& lattice  = myCase.getLattice(NavierStokes {});
  lattice.setParameter<descriptors::OMEGA>(lattice.getUnitConverter().getLatticeRelaxationFrequency());
  lattice.initialize();
}

void setTemporalValues(MyCase& myCase, int iT)
{
  using T         = MyCase::value_t;
  auto& params    = myCase.getParameters();
  auto& geometry  = myCase.getGeometry();
  auto& lattice   = myCase.getLattice(NavierStokes {});
  auto& converter = lattice.getUnitConverter();
  const T maxPhysT = params.get<parameters::MAX_PHYS_T>();

  // No of time steps for smooth start-up
  int iTmaxStart = converter.getLatticeTime(maxPhysT * 0.4);
  int iTupdate   = 30;

  if (iT % iTupdate == 0 && iT <= iTmaxStart) {
    PolynomialStartScale<T, int> StartScale(iTmaxStart, T(1));

    // Creates and sets the Poiseuille inflow profile using functors
    int iTvec[1] = {iT};
    T   frac[1]  = {};
    StartScale(frac, iTvec);
    std::vector<T> maxVelocity(3, 0);
    maxVelocity[0]                      = 2.25 * frac[0] * converter.getCharPhysVelocity();
    T                     distance2Wall = converter.getPhysDeltaX() / 2.;
    CirclePoiseuille3D<T> poiseuilleU(geometry, 3, maxVelocity[0], distance2Wall);
    momenta::setVelocity(lattice, geometry.getMaterialIndicator(3), poiseuilleU);

    // Update velocity on GPU
    lattice.setProcessingContext<Array<momenta::FixedVelocityMomentumGeneric::VELOCITY>>(
      ProcessingContext::Simulation);
  }
}

void getResults(MyCase& myCase, util::Timer<MyCase::value_t>& timer, std::size_t iT,
                VTUsurfaceWriter<MyCase::value_t>& vtuWriter)
{
  using T          = MyCase::value_t;
  using DESCRIPTOR = MyCase::descriptor_t_of<NavierStokes>;
  auto& lattice    = myCase.getLattice(NavierStokes {});
  auto& converter  = lattice.getUnitConverter();
  auto& params     = myCase.getParameters();

  const T maxPhysT = params.get<parameters::MAX_PHYS_T>();
  const std::size_t vtkIter  = std::max<std::size_t>(1, converter.getLatticeTime(maxPhysT / 20.0));
  const std::size_t statIter = std::max<std::size_t>(1, converter.getLatticeTime(maxPhysT / 20.0));

  // Optimization: Early return to avoid expensive object creation (STL lookup, etc.)
  // when no output is needed for this time step.
  if (iT != 0 && iT % vtkIter != 0 && iT % statIter != 0) {
    return;
  }

  OstreamManager clout(std::cout, "getResults");

  SuperVTMwriter3D<T> vtmWriter("aneurysm");

  SuperLatticePhysVelocity3D<T, DESCRIPTOR> velocity(lattice, converter);
  SuperLatticePhysPressure3D<T, DESCRIPTOR> pressure(lattice, converter);
  SuperLatticeDensity3D                     densityF(lattice);
  AnalyticalFfromSuperF3D                   smoothDensityF(densityF);

  SuperLatticeStress3D    stressF(lattice);
  AnalyticalFfromSuperF3D smoothStressF(stressF);

  auto aneurysmI = myCase.getMesh().getSTL(params.get<parameters::STL_PATH>());
  PhysWallShearStressOnSurface3D<T, DESCRIPTOR> interpolatedWssF(
    converter, smoothDensityF, smoothStressF, *aneurysmI);
  vtmWriter.addFunctor(velocity);
  vtmWriter.addFunctor(pressure);
  interpolatedWssF.getName() = "WallShearStress";

  if (iT == 0) {
    vtmWriter.createMasterFile();
    vtuWriter.createMasterFile();
    vtuWriter.addFunctor(interpolatedWssF);
    vtuWriter.addFunctor(velocity);
    vtuWriter.addFunctor(pressure);
  }

  // Writes the vtu files
  if (iT % vtkIter == 0) {
    // Send values from GPU to CPU for evaluation
    lattice.setProcessingContext(ProcessingContext::Evaluation);
    vtuWriter.write(iT);
  }

  // Writes the vtk files
  if (iT % vtkIter == 0) {
    lattice.setProcessingContext(ProcessingContext::Evaluation);
    lattice.scheduleBackgroundOutputVTK([&, iT](auto task) {
      SuperVTMwriter3D<T>        vtmWriter("aneurysm");
      SuperLatticePhysVelocity3D velocity(lattice, converter);
      SuperLatticePhysPressure3D pressure(lattice, converter);
      vtmWriter.addFunctor(velocity);
      vtmWriter.addFunctor(pressure);
      task(vtmWriter, iT);
    });
  }

  // Writes output on the console
  if (iT % statIter == 0) {
    lattice.setProcessingContext(ProcessingContext::Evaluation);

    // Timer console output
    timer.update(iT);
    timer.printStep();
    lattice.getStatistics().print(iT, converter.getPhysTime(iT));
  }
}

void simulate(MyCase& myCase)
{
  using T         = MyCase::value_t;
  auto& params    = myCase.getParameters();
  auto& geometry  = myCase.getGeometry();
  auto& lattice   = myCase.getLattice(NavierStokes {});
  auto& converter = lattice.getUnitConverter();

  const T maxPhysT = params.get<parameters::MAX_PHYS_T>();

  OstreamManager clout(std::cout, "simulate");

  clout << "========================================" << std::endl;
  clout << "      Aneurysm 3D Simulation Start      " << std::endl;
  clout << "========================================" << std::endl;
  clout << "Parameters:" << std::endl;
  clout << "  Reynolds number: " << params.get<parameters::REYNOLDS>() << std::endl;
  clout << "  Resolution:      " << params.get<parameters::RESOLUTION>() << std::endl;
  clout << "  Max Phys Time:   " << maxPhysT << " s" << std::endl;
  clout << "  Total Time Steps: " << converter.getLatticeTime(maxPhysT) << std::endl;
  clout << "Output Files:" << std::endl;
  clout << "  Flow data:       aneurysm.vtm (and .vts)" << std::endl;
  clout << "  Geometry:        Mesh.vtu" << std::endl;
  clout << "  Output Interval: " << (maxPhysT / 20.0) << " s" << " (" << converter.getLatticeTime(maxPhysT / 20.0) << " steps)" << std::endl;
  clout << "========================================" << std::endl;
  clout << "starting simulation..." << std::endl;

  auto aneurysmI = myCase.getMesh().getSTL(params.get<parameters::STL_PATH>());

  VTUsurfaceWriter<T> vtuWriter("Mesh", lattice.getCuboidDecomposition(), lattice.getLoadBalancer());
  vtuWriter.addSTL(*aneurysmI);

  util::Timer<T> timer(converter.getLatticeTime(maxPhysT), geometry.getStatistics().getNvoxel());
  timer.start();

  for (std::size_t iT = 0; iT < converter.getLatticeTime(maxPhysT); ++iT) {
    setTemporalValues(myCase, iT);

    lattice.collideAndStream();

    getResults(myCase, timer, iT, vtuWriter);
  }

  timer.stop();
  timer.printSummary();

  clout << "========================================" << std::endl;
  clout << "       Simulation Completed Successfully " << std::endl;
  clout << "========================================" << std::endl;
}

int main(int argc, char* argv[])
{
  initialize(&argc, &argv);

  MyCase::ParametersD myCaseParameters;
  {
    using namespace olb::parameters;
    using T = MyCase::value_t;

    myCaseParameters.set<STL_PATH>("aneurysm3d.stl");
    myCaseParameters.set<STL_SCALING>(1);
    myCaseParameters.set<STL_RAY_MODE>(RayMode::Robust);
    myCaseParameters.set<DECOMPOSITION_STRATEGY>("volume");
    myCaseParameters.set<MESH_PADDING>(2);
    myCaseParameters.set<DECOMPOSITION_MULTIPLIER>(4);

    myCaseParameters.set<RESOLUTION>(30);
    myCaseParameters.set<REYNOLDS>((T)100.);
    myCaseParameters.set<MAX_PHYS_T>((T)0.1);
    myCaseParameters.set<CFL>((T)0.02);
    myCaseParameters.set<PHYS_DELTA_X>([&]() {
      return 0.05 / myCaseParameters.get<parameters::RESOLUTION>();
    });
  }
  myCaseParameters.fromCLI(argc, argv);

  // Sentinel Security Check: Input Validation
  if (myCaseParameters.get<olb::parameters::RESOLUTION>() <= 0) {
    std::cerr << "Error: RESOLUTION must be positive to prevent division by zero." << std::endl;
    return 1;
  }
  if (myCaseParameters.get<olb::parameters::REYNOLDS>() <= 0) {
    std::cerr << "Error: REYNOLDS must be positive to prevent division by zero." << std::endl;
    return 1;
  }
  if (myCaseParameters.get<olb::parameters::MAX_PHYS_T>() <= 0) {
    std::cerr << "Error: MAX_PHYS_T must be positive to prevent infinite loops or invalid time steps." << std::endl;
    return 1;
  }
  if (myCaseParameters.get<olb::parameters::CFL>() <= 0) {
    std::cerr << "Error: CFL must be positive to ensure valid physical time steps." << std::endl;
    return 1;
  }

  Mesh mesh = createMesh(myCaseParameters);

  MyCase myCase(myCaseParameters, mesh);

  prepareGeometry(myCase);

  prepareLattice(myCase);

  setInitialValues(myCase);

  simulate(myCase);

  return 0;
}
