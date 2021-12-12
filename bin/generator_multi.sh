#!/bin/bash

CNT=$1

set -eu
cd `dirname $0`/..

cd third_party/tools/in/
ls | xargs readlink -f
