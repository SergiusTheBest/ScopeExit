add_executable(Demo Main.cpp)
target_link_libraries(Demo ScopeExit::ScopeExit)
set_target_properties(Demo PROPERTIES FOLDER Samples)