function hsdk_build() {
    local TARGET=${1:-"clean all"}
    local PROGRAM=${2:-"application/baremetal/helloworld"}
    local CORE=${3:-"e203"}
    local DOWNLOAD=${4:-"ilm"}

    BUILD_CMD="make ${TARGET} PROGRAM=${PROGRAM} CORE=${CORE} DOWNLOAD=${DOWNLOAD} "
    echo "Help: hsdk_build [TARGET] [PROGRAM] [CORE] [DOWNLOAD]"
    echo "Execute HummingBird SDK build command in 1s: ${BUILD_CMD}"
    sleep 1
    eval $BUILD_CMD
}
