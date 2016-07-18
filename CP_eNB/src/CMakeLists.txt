add_library (eNB SHARED Controller.cpp UeManager.cpp)
target_link_libraries (eNB messages)
