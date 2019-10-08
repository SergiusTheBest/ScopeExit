add_executable(Html Main.cpp)
target_link_libraries(Html ScopeExit::ScopeExit)
set_target_properties(Html PROPERTIES FOLDER Samples)