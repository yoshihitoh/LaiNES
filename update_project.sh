#!/usr/bin/env bash

set -eo pipefail

premake5 gmake2
cmake -Bbuild .
