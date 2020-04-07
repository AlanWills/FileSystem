set(INCLUDES 
    ${THIRD_PARTY_DIR}/dirent/include)

set(LIBS 
    Platform
    CelesteStl
    Assert)

build_library(NAME FileSystem FOLDER Celeste/Packages TYPE STATIC INCLUDES "${INCLUDES}" LIBS "${LIBS}")