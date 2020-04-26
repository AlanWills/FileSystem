set(INCLUDES 
    ${THIRD_PARTY_DIR}/dirent/include)

set(LIBS 
    Platform
    CelesteStl
    Assert)

cbt_build_project(NAME FileSystem FOLDER Celeste TYPE STATIC INCLUDES "${INCLUDES}" LIBS "${LIBS}")