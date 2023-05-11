
# Base
set (
    BASE_SOURCE
    MMD/Base/File.cpp
    MMD/Base/Log.cpp
    MMD/Base/Path.cpp
    MMD/Base/Singleton.cpp
    MMD/Base/Time.cpp
    MMD/Base/UnicodeUtil.cpp
)
set (
    BASE_HEADER
    MMD/Base/File.h
    MMD/Base/Log.h
    MMD/Base/Path.h
    MMD/Base/Singleton.h
    MMD/Base/Time.h
    MMD/Base/UnicodeUtil.h
)

# OBJ Model
set (
    MODEL_OBJ_SOURCE
    MMD/Model/OBJ/OBJModel.cpp
    MMD/Model/OBJ/tinyobjloader.cpp
)
set (
    MODEL_OBJ_HEADER
    MMD/Model/OBJ/OBJModel.h
)

# MMD Model
set (
    MODEL_MMD_SOURCE
    MMD/Model/MMD/MMDIkSolver.cpp
    MMD/Model/MMD/MMDMaterial.cpp
    MMD/Model/MMD/MMDModel.cpp
    MMD/Model/MMD/MMDMorph.cpp
    MMD/Model/MMD/MMDNode.cpp
    MMD/Model/MMD/MMDPhysics.cpp
    MMD/Model/MMD/MMDCamera.cpp
    MMD/Model/MMD/PMDFile.cpp
    MMD/Model/MMD/PMDModel.cpp
    MMD/Model/MMD/PMXFile.cpp
    MMD/Model/MMD/PMXModel.cpp
    MMD/Model/MMD/SjisToUnicode.cpp
    MMD/Model/MMD/VMDAnimation.cpp
    MMD/Model/MMD/VMDCameraAnimation.cpp
    MMD/Model/MMD/VMDFile.cpp
    MMD/Model/MMD/VPDFile.cpp
)
set (
    MODEL_MMD_HEADER
    MMD/Model/MMD/MMDFileString.h
    MMD/Model/MMD/MMDIkSolver.h
    MMD/Model/MMD/MMDMaterial.h
    MMD/Model/MMD/MMDModel.h
    MMD/Model/MMD/MMDMorph.h
    MMD/Model/MMD/MMDNode.h
    MMD/Model/MMD/MMDPhysics.h
    MMD/Model/MMD/MMDCamera.h
    MMD/Model/MMD/PMDFile.h
    MMD/Model/MMD/PMDModel.h
    MMD/Model/MMD/PMXFile.h
    MMD/Model/MMD/PMXModel.h
    MMD/Model/MMD/SjisToUnicode.h
    MMD/Model/MMD/VMDAnimation.h
    MMD/Model/MMD/VMDCameraAnimation.h
    MMD/Model/MMD/VMDAnimationCommon.h
    MMD/Model/MMD/VMDFile.h
    MMD/Model/MMD/VPDFile.h
)

add_library(
    MMD
    ${BASE_SOURCE}
    ${BASE_HEADER}
    ${MODEL_OBJ_SOURCE}
    ${MODEL_OBJ_HEADER}
    ${MODEL_XFILE_SOURCE}
    ${MODEL_XFILE_HEADER}
    ${MODEL_MMD_SOURCE}
    ${MODEL_MMD_HEADER}
)

set (MMD_LIBRARIES ${BULLET_LIBRARIES})
if (UNIX)
    find_package(Threads REQUIRED)
    list (APPEND MMD_LIBRARIES ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
    target_link_libraries(MMD PRIVATE ${BULLET_LIBRARIES} ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
endif ()
target_link_libraries(MMD PRIVATE ${MMD_LIBRARIES})

SOURCE_GROUP(Base FILES ${BASE_SOURCE} ${BASE_HEADER})
SOURCE_GROUP(Model\\OBJ FILES ${MODEL_OBJ_SOURCE} ${MODEL_OBJ_HEADER})
SOURCE_GROUP(Model\\XFile FILES ${MODEL_XFILE_SOURCE} ${MODEL_XFILE_HEADER})
SOURCE_GROUP(Model\\MMD FILES ${MODEL_MMD_SOURCE} ${MODEL_MMD_HEADER})

# install
if (MMD_INSTALL)
    install (TARGETS MMD DESTINATION lib)
endif()
