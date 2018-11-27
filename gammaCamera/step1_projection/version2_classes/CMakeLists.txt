cmake_minimum_required( VERSION 2.8 )

project( alice )

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_BUILD_TYPE Release )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )

############### dependencies ######################
# OpenCV
find_package( OpenCV )
include_directories( ${OpenCV_INCLUDE_DIRS} )
# Eigen
include_directories( "/usr/include/eigen3" )
# Ceres Solver
find_package( Ceres REQUIRED)
include_directories( ${CERES_INCLUDE_DIRS} )

############### dependencies ######################

#----------------------------------------------------------------------------
# Setup include directory for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.C)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

#----------------------------------------------------------------------------
# Add the executable, and link it to libraries
#
add_executable( alice alice.C  ${sources} ${headers} )

# link OpenCV
target_link_libraries( alice ${OpenCV_LIBS} )
# link Ceresr Solver 
target_link_libraries( alice ${CERES_LIBRARIES} )

# copy files
set(cv_Scripts
	)

foreach(_script ${cv_Scripts})
	configure_file(
		${PROJECT_SOURCE_DIR}/${_script}
		${PROJECT_BINARY_DIR}/${_script}
		COPYONLY
		)
endforeach()
