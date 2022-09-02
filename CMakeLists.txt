

#
#   First, grab RooUnfold and build the shared library.
#   After doing that, reset the RooUnfold paths below to the correct path.
#
#   To build the unfolding executable, do this:
#
#     mkdir build
#     cd build
#     cmake ..
#     cmake --build .
#
#


cmake_minimum_required(VERSION 3.10)

project(h1-analysis)

find_package(ROOT CONFIG REQUIRED)
include("${ROOT_USE_FILE}")

separate_arguments(ROOT_EXE_LINKER_FLAGS)

find_package( RooUnfold REQUIRED )
include_directories("/Users/owen/work/eic/RooUnfold/src")



add_library( RooUnfold SHARED IMPORTED  )

set_target_properties( RooUnfold PROPERTIES IMPORTED_LOCATION /Users/owen/work/eic/RooUnfold/build/libRooUnfold.dylib )




#add_executable(boo boo.c)

#add_executable(simple_root_exec1a simple_root_exec1a.cxx)
#target_link_libraries(simple_root_exec1a PUBLIC ROOT::RIO ROOT::Hist)

add_executable(mytest2 mytest2.cxx)
target_link_libraries(mytest2 PUBLIC  ${ROOT_LIBRARIES} ${ROOT_EXE_LINKER_FLAGS} RooUnfold)


add_executable(mytest3_uniform_binning mytest3_uniform_binning.cxx)
target_link_libraries(mytest3_uniform_binning PUBLIC  ${ROOT_LIBRARIES} ${ROOT_EXE_LINKER_FLAGS} RooUnfold)


