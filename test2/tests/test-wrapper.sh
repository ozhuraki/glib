#!/usr/bin/env bash

set -euo pipefail

TEST_INPUT=$1

TEST_NAME=$(basename $TEST_INPUT)

case "$TEST_NAME" in
    scanner*)
	TEST_PROG=./scanner;;
    parser*)
	TEST_PROG=./parser;;
esac

$TEST_PROG < $TEST_INPUT
exit $?
