#!/usr/bin/env bash
#
# GPU native testing on a Cray EX (using none for CHPL_COMM)

UTIL_CRON_DIR=$(cd $(dirname ${BASH_SOURCE[0]}) ; pwd)
source $UTIL_CRON_DIR/common-native-gpu.bash
source $UTIL_CRON_DIR/common-hpe-cray-ex.bash
source $UTIL_CRON_DIR/common-gpu-nvidia-hpe-cray-ex.bash

module load cuda/12.4

export CHPL_LLVM=system
export CHPL_COMM=none
export CHPL_GPU=nvidia  # amd is also detected automatically

export CHPL_NIGHTLY_TEST_CONFIG_NAME="gpu-ex-cuda-12"
$UTIL_CRON_DIR/nightly -cron ${nightly_args}
