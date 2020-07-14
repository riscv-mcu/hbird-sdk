function hsdk_build_directory() {
    local projroot=$1
    local target=${2:-"clean all"}
    local count=0
    local ignore_pattern=$FIND_IGNORE

    FIND_CMD="find $projroot -type f -name "Makefile" $ignore_pattern"
    echo $FIND_CMD
    local makefiles=($(eval $FIND_CMD))
    local totalcount=${#makefiles[@]}
    local failed_examples=""
    for makefile in ${makefiles[@]} ; do
        projdir=$(dirname $makefile)
        BUILD_CMD="hsdk_build \"$target\" $projdir $CORE $DOWNLOAD"
        echo "$BUILD_CMD"
        if eval "$BUILD_CMD" ; then
            testval=$((count++))
        else
            failed_examples="$failed_examples\r\n    $projdir"
        fi
    done

    echo ""
    echo "Successfully execute make target($target) for $count out of $totalcount applications in $projroot"
    if [ "$failed_examples" != "" ] ; then
        echo "=====Failed application(CORE=$CORE DOWNLOAD=$DOWNLOAD) list as below:====="
        echo -e "$failed_examples\r\n"
        return 1
    fi
}

