set(INCLUDES 
    ${DIRENT_PROJECT_DIR}/include)

set(LIBS 
    Platform
    CelesteStl
    Assert)

build_library(NAME FileSystem FOLDER Celeste/Packages TYPE STATIC INCLUDES "${INCLUDES}" LIBS "${LIBS}")