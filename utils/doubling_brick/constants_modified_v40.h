!=====================================================================
!
!          S p e c f e m 3 D  G l o b e  V e r s i o n  3 . 6
!          --------------------------------------------------
!
!                 Dimitri Komatitsch and Jeroen Tromp
!    Seismological Laboratory - California Institute of Technology
!        (c) California Institute of Technology July 2004
!
! This program is free software; you can redistribute it and/or modify
! it under the terms of the GNU General Public License as published by
! the Free Software Foundation; either version 3 of the License, or
! (at your option) any later version.
!
! This program is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY; without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
! GNU General Public License for more details.
!
! You should have received a copy of the GNU General Public License along
! with this program; if not, write to the Free Software Foundation, Inc.,
! 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
!
!=====================================================================

! constants.h.  Generated from constants.h.in by configure.

!
!--- user can modify parameters below
!

!!!!!!!!! DK DK UGLY temp
! logical, parameter :: ACTIVATE_SUPPRESS_TEMPOR = .true.
  logical, parameter :: ACTIVATE_SUPPRESS_TEMPOR = .false.

!! DK DK it seems optimal to implement the second doubling at this depth in the mantle
  double precision, parameter :: DEPTH_SECOND_DOUBLING_OPTIMAL = 1650000.d0

!! DK DK it seems optimal to implement the third doubling at this depth in the outer core
  double precision, parameter :: DEPTH_THIRD_DOUBLING_OPTIMAL = 3860000.d0

!! DK DK it seems optimal to implement the fourth doubling at this depth in the outer core
  logical, parameter :: IMPLEMENT_FOURTH_DOUBLING = .true.
  double precision, parameter :: DEPTH_FOURTH_DOUBLING_OPTIMAL = 5000000.d0

  integer, parameter :: NB_LAYERS_SAMPLING_STUDY = 11
! add three layers for the doublings in the mantle and outer core
  integer, parameter :: NUMBER_OF_MESH_LAYERS = NB_LAYERS_SAMPLING_STUDY + 3

! define number of spectral elements and points in basic symmetric mesh doubling superbrick
  integer, parameter :: NSPEC_DOUBLING_SUPERBRICK = 32
  integer, parameter :: NGLOB_DOUBLING_SUPERBRICK = 67
  integer, parameter :: NGNOD_DOUBLING_SUPERBRICK = 8

! PREM
  double precision, parameter :: RMIDDLE_CRUST = 6356000.d0
  double precision, parameter :: RMOHO = 6346600.d0
  double precision, parameter :: R80 = 6291000.d0
  double precision, parameter :: R220 = 6151000.d0
  double precision, parameter :: R400 = 5971000.d0
  double precision, parameter :: R600 = 5771000.d0
  double precision, parameter :: R670 = 5701000.d0
  double precision, parameter :: R771 = 5600000.d0
  double precision, parameter :: RTOPDDOUBLEPRIME = 3630000.d0
  double precision, parameter :: RCMB = 3480000.d0
  double precision, parameter :: RICB = 1221000.d0

!
! solver in single or double precision depending on the machine (4 or 8 bytes)
!
!  ALSO CHANGE FILE precision.h ACCORDINGLY
!
  integer, parameter :: SIZE_REAL = 4, SIZE_DOUBLE = 8

! set to SIZE_REAL to run in single precision
! set to SIZE_DOUBLE to run in double precision (increases memory size by 2)
  integer, parameter :: CUSTOM_REAL = SIZE_REAL

! if files on a local path on each node are also seen as global with same path
! set to .true. typically on a shared-memory machine with a common file system
! set to .false. typically on a cluster of nodes, e.g. on a Beowulf-type machine
! if running on a Beowulf-type machine, also customize global path to local
! files in create_serial_name_database.f90 ("20 format ...")
! Flag is used only when one checks the mesh with the serial codes
! ("xcheck_buffers_1D" etc.), ignore it if you do not plan to use them
  logical, parameter :: LOCAL_PATH_IS_ALSO_GLOBAL = .true.

! input, output and main MPI I/O files
  integer, parameter :: ISTANDARD_OUTPUT = 6
  integer, parameter :: IIN = 40,IOUT = 41
! local file unit for output of buffers
  integer, parameter :: IOUT_BUFFERS = 35
! uncomment this to write messages to a text file
  integer, parameter :: IMAIN = 42
! uncomment this to write messages to the screen (slows down the code)
! integer, parameter :: IMAIN = ISTANDARD_OUTPUT
! I/O unit for source and receiver vtk file
  integer, parameter :: IOUT_VTK = 98


! R_EARTH is the radius of the bottom of the oceans (radius of Earth in m)
  double precision, parameter :: R_EARTH = 6371000.d0
! uncomment line below for PREM with oceans
! double precision, parameter :: R_EARTH = 6368000.d0

! average density in the full Earth to normalize equation
  double precision, parameter :: RHOAV = 5514.3d0

! for topography/bathymetry model

!!--- ETOPO5 5-minute model, smoothed Harvard version
!! size of topography and bathymetry file
!  integer, parameter :: NX_BATHY = 4320,NY_BATHY = 2160
!! resolution of topography file in minutes
!  integer, parameter :: RESOLUTION_TOPO_FILE = 5
!! pathname of the topography file
!  character (len=*), parameter :: PATHNAME_TOPO_FILE = 'DATA/topo_bathy/topo_bathy_etopo5_smoothed_Harvard.dat'

!---  ETOPO4 4-minute model created by subsampling and smoothing etopo-2
! size of topography and bathymetry file
  integer, parameter :: NX_BATHY = 5400,NY_BATHY = 2700
! resolution of topography file in minutes
  integer, parameter :: RESOLUTION_TOPO_FILE = 4
! pathname of the topography file
  character (len=*), parameter :: PATHNAME_TOPO_FILE = 'DATA/topo_bathy/topo_bathy_etopo4_smoothed_window_7.dat'

!!--- ETOPO2 2-minute model, not implemented yet
!! size of topography and bathymetry file
!  integer, parameter :: NX_BATHY = 10800,NY_BATHY = 5400
!! resolution of topography file in minutes
!  integer, parameter :: RESOLUTION_TOPO_FILE = 2
!! pathname of the topography file
!  character (len=*), parameter :: PATHNAME_TOPO_FILE = 'DATA/topo_bathy/topo_bathy_etopo2_smoothed_window7.dat'

! maximum depth of the oceans in trenches and height of topo in mountains
! to avoid taking into account spurious oscillations in global model ETOPO
  logical, parameter :: USE_MAXIMUM_HEIGHT_TOPO = .false.
  integer, parameter :: MAXIMUM_HEIGHT_TOPO = +20000
  logical, parameter :: USE_MAXIMUM_DEPTH_OCEANS = .false.
  integer, parameter :: MAXIMUM_DEPTH_OCEANS = -20000

! minimum thickness in meters to include the effect of the oceans and topo
  double precision, parameter :: MINIMUM_THICKNESS_3D_OCEANS = 100.d0

! number of GLL points in each direction of an element (degree plus one)
  integer, parameter :: NGLLX = 5
  integer, parameter :: NGLLY = NGLLX
  integer, parameter :: NGLLZ = NGLLX

! flag to exclude elements that are too far from target in source detection
  logical, parameter :: USE_DISTANCE_CRITERION = .true.

! flag to display detailed information about location of stations
  logical, parameter :: DISPLAY_DETAILS_STATIONS = .false.

! maximum length of station and network name for receivers
  integer, parameter :: MAX_LENGTH_STATION_NAME = 32
  integer, parameter :: MAX_LENGTH_NETWORK_NAME = 8

! source decay rate
  double precision, parameter :: SOURCE_DECAY_RATE = 1.628d0

! number of sources to locate simultaneously
  integer, parameter :: NSOURCES_SUB = 1000

! distance threshold (in km) above which we consider that a receiver
! is located outside the mesh and therefore excluded from the station list
  double precision, parameter :: THRESHOLD_EXCLUDE_STATION = 50.d0

!! DK DK UGLY in the case of a very fine mesh, move the bottom of crustal
!! DK DK UGLY elements below the PREM Moho, otherwise the elements become
!! DK DK UGLY too distorted in the radial distribution of elements.
!! DK DK UGLY Not very clean, should write something more general one day
  double precision, parameter :: RMOHO_FICTITIOUS_2ELEMS = 6330000.d0
  double precision, parameter :: RMOHO_FICTITIOUS_4ELEMS = 6330000.d0

!
!--- debugging flags
!

! flags to actually assemble with MPI or not
! and to actually match fluid and solid regions of the Earth or not
! should always be set to true except when debugging code
  logical, parameter :: ACTUALLY_ASSEMBLE_MPI_SLICES = .true.
  logical, parameter :: ACTUALLY_ASSEMBLE_MPI_CHUNKS = .true.
  logical, parameter :: ACTUALLY_COUPLE_FLUID_CMB = .true.
  logical, parameter :: ACTUALLY_COUPLE_FLUID_ICB = .true.

!! DK DK UGLY added this in case we are running on MareNostrum in Barcelona
!! DK DK UGLY because we then need some calls to the system to use GPFS
  logical, parameter :: RUN_ON_MARENOSTRUM_BARCELONA = .false.

!------------------------------------------------------
!----------- do not modify anything below -------------
!------------------------------------------------------

! on some processors (e.g. Pentiums) it is necessary to suppress underflows
! by using a small initial field instead of zero
  logical, parameter :: FIX_UNDERFLOW_PROBLEM = .true.

! some useful constants
  double precision, parameter :: PI = 3.141592653589793d0
  double precision, parameter :: TWO_PI = 2.d0 * PI
  double precision, parameter :: PI_OVER_FOUR = PI / 4.d0

! to convert angles from degrees to radians
  double precision, parameter :: DEGREES_TO_RADIANS = PI / 180.d0

! 3-D simulation
  integer, parameter :: NDIM = 3

! dimension of the boundaries of the slices
  integer, parameter :: NDIM2D = 2

! number of nodes for 2D and 3D shape functions for hexahedra with 27 nodes
  integer, parameter :: NGNOD = 27, NGNOD2D = 9

! gravitational constant
  double precision, parameter :: GRAV = 6.6723d-11

! a few useful constants
  double precision, parameter :: ZERO = 0.d0,ONE = 1.d0,TWO = 2.d0,HALF = 0.5d0

  real(kind=CUSTOM_REAL), parameter :: &
    ONE_THIRD   = 1._CUSTOM_REAL/3._CUSTOM_REAL, &
    TWO_THIRDS  = 2._CUSTOM_REAL/3._CUSTOM_REAL, &
    FOUR_THIRDS = 4._CUSTOM_REAL/3._CUSTOM_REAL

! very large and very small values
  double precision, parameter :: HUGEVAL = 1.d+30,TINYVAL = 1.d-9

! very large real value declared independently of the machine
  real(kind=CUSTOM_REAL), parameter :: HUGEVAL_SNGL = 1.e+30_CUSTOM_REAL

! very large integer value
  integer, parameter :: HUGEINT = 100000000

! normalized radius of free surface
  double precision, parameter :: R_UNIT_SPHERE = ONE

! same radius in km
  double precision, parameter :: R_EARTH_KM = R_EARTH / 1000.d0

! fixed thickness of 3 km for PREM oceans
  double precision, parameter :: THICKNESS_OCEANS_PREM = 3000.d0 / R_EARTH

! shortest radius at which crust is implemented
  double precision, parameter :: R_DEEPEST_CRUST = (R_EARTH - 90000.d0) / R_EARTH

! maximum number of chunks (full sphere)
  integer, parameter :: NCHUNKS_MAX = 6

! define block type based upon chunk number (between 1 and 6)
! do not change this numbering, chunk AB must be number 1 for central cube
  integer, parameter :: CHUNK_AB = 1
  integer, parameter :: CHUNK_AC = 2
  integer, parameter :: CHUNK_BC = 3
  integer, parameter :: CHUNK_AC_ANTIPODE = 4
  integer, parameter :: CHUNK_BC_ANTIPODE = 5
  integer, parameter :: CHUNK_AB_ANTIPODE = 6

! maximum number of regions in the mesh
  integer, parameter :: MAX_NUM_REGIONS = 3

! define flag for regions of the global Earth mesh
  integer, parameter :: IREGION_CRUST_MANTLE = 1
  integer, parameter :: IREGION_OUTER_CORE = 2
  integer, parameter :: IREGION_INNER_CORE = 3

! define flag for elements
  integer, parameter :: IFLAG_CRUST = 1

  integer, parameter :: IFLAG_220_MOHO = 2
  integer, parameter :: IFLAG_670_220 = 3
  integer, parameter :: IFLAG_MANTLE_NORMAL = 4

  integer, parameter :: IFLAG_OUTER_CORE_NORMAL = 5

  integer, parameter :: IFLAG_INNER_CORE_NORMAL = 6

  integer, parameter :: IFLAG_IN_CENTRAL_CUBE = 7
  integer, parameter :: IFLAG_BOTTOM_CENTRAL_CUBE = 8
  integer, parameter :: IFLAG_TOP_CENTRAL_CUBE = 9
  integer, parameter :: IFLAG_IN_FICTITIOUS_CUBE = 10

! dummy flag used for mesh display purposes only
  integer, parameter :: IFLAG_DUMMY = 100

! define flag for reference 1D Earth model
  integer, parameter :: REFERENCE_MODEL_PREM   = 1
  integer, parameter :: REFERENCE_MODEL_IASP91 = 2
  integer, parameter :: REFERENCE_MODEL_1066A  = 3
  integer, parameter :: REFERENCE_MODEL_AK135  = 4

! define flag for regions of the global Earth for attenuation
  integer, parameter :: NUM_REGIONS_ATTENUATION = 5

  integer, parameter :: IREGION_ATTENUATION_INNER_CORE = 1
  integer, parameter :: IREGION_ATTENUATION_CMB_670 = 2
  integer, parameter :: IREGION_ATTENUATION_670_220 = 3
  integer, parameter :: IREGION_ATTENUATION_220_80 = 4
  integer, parameter :: IREGION_ATTENUATION_80_SURFACE = 5

! number of standard linear solids for attenuation
  integer, parameter :: N_SLS = 3

! computation of standard linear solids in meshfem3D
! ATTENUATION_COMP_RESOLUTION: Number of Digits after decimal
! ATTENUATION_COMP_MAXIMUM:    Maximum Q Value
  integer, parameter :: ATTENUATION_COMP_RESOLUTION = 1
  integer, parameter :: ATTENUATION_COMP_MAXIMUM    = 5000

! for lookup table for attenuation every 100 m in radial direction of Earth model
  integer, parameter          :: NRAD_ATTENUATION  = 70000
  double precision, parameter :: TABLE_ATTENUATION = R_EARTH_KM * 10.0d0

! flag for the four edges of each slice and for the bottom edge
  integer, parameter :: XI_MIN  = 1
  integer, parameter :: XI_MAX  = 2
  integer, parameter :: ETA_MIN = 3
  integer, parameter :: ETA_MAX = 4
  integer, parameter :: BOTTOM  = 5

! flags to select the right corner in each slice
  integer, parameter :: ILOWERLOWER = 1
  integer, parameter :: ILOWERUPPER = 2
  integer, parameter :: IUPPERLOWER = 3
  integer, parameter :: IUPPERUPPER = 4

! number of points in each AVS or OpenDX quadrangular cell for movies
  integer, parameter :: NGNOD2D_AVS_DX = 4

! number of faces a given slice can share with other slices
! this is at most 2, except when there is only once slice per chunk
! in which case it is 4
  integer, parameter :: NUMFACES_SHARED = 4

! number of corners a given slice can share with other slices
! this is at most 1, except when there is only once slice per chunk
! in which case it is 4
  integer, parameter :: NUMCORNERS_SHARED = 4

! number of slaves per corner
  integer, parameter :: NUMSLAVES = 2

! number of layers in PREM
  integer, parameter :: NR = 640

! smallest real number on the Pentium and the SGI =  1.1754944E-38
! largest real number on the Pentium and the SGI  =  3.4028235E+38
! small negligible initial value to avoid very slow underflow trapping
! but not too small to avoid trapping on velocity and acceleration in Newmark
  real(kind=CUSTOM_REAL), parameter :: VERYSMALLVAL = 1.E-24_CUSTOM_REAL

! displacement threshold above which we consider that the code became unstable
  real(kind=CUSTOM_REAL), parameter :: STABILITY_THRESHOLD = 1.E+25_CUSTOM_REAL

! geometrical tolerance for boundary detection
  double precision, parameter :: SMALLVAL = 0.00001d0

! small tolerance for conversion from x y z to r theta phi
  double precision, parameter :: SMALL_VAL_ANGLE = 1.d-10

! geometry tolerance parameter to calculate number of independent grid points
! sensitive to actual size of model, assumes reference sphere of radius 1
! this is an absolute value for normalized coordinates in the Earth
  double precision, parameter :: SMALLVALTOL = 1.d-10

! do not use tags for MPI messages, use dummy tag instead
  integer, parameter :: itag = 0,itag2 = 0

! for the Gauss-Lobatto-Legendre points and weights
  double precision, parameter :: GAUSSALPHA = 0.d0,GAUSSBETA = 0.d0

! number of lines per source in CMTSOLUTION file
  integer, parameter :: NLINES_PER_CMTSOLUTION_SOURCE = 13

! number of iterations to solve the non linear system for xi and eta
  integer, parameter :: NUM_ITER = 4

! number of hours per day for rotation rate of the Earth
  double precision, parameter :: HOURS_PER_DAY = 24.d0

! for lookup table for gravity every 100 m in radial direction of Earth model
  integer, parameter :: NRAD_GRAVITY = 70000

