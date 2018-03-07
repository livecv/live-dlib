
# --- Version Check ---

# Some linux distributions have qt version 4 already installed. Sometimes this
# can lead to running the wrong qmake version. Notify the user:

!qtVersionCheck(5, 6)::error( \
    This project requires at least Qt version 5.6. \
    Make sure you have Qt 5.6 installed and running the correct qmake. \
)

# --- Project structure ---

TEMPLATE = subdirs
SUBDIRS += dlib

## --- Subdir configurations ---
dlib.subdir = dlib

exists($$PWD/livecv):equals(BUILD_DEPENDENCIES, true){
    SUBDIRS += livecv
    livecv.subdir = $$PWD/livecv
    dlib.depends = livecv
}

# --- Dependency configuration ---

# Include the global configuration files since otherwise they would never show
# up in your project
OTHER_FILES += \
    .qmake.conf \
    $$LIVECV_DEV_PATH/project/*.pri
