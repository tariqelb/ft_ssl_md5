#!/bin/bash

NAME="./ft_ssl"
TOTAL=0
FAIL=0

run_test()
{
    NAME_TEST="$1"
    COMMAND="$2"

    TOTAL=$((TOTAL + 1))

    echo "========================================"
    echo "TEST: $NAME_TEST"
    echo "========================================"

    eval "$COMMAND" > /tmp/ft_ssl_output 2> /tmp/valgrind_output

    if grep -q "All heap blocks were freed -- no leaks are possible" \
        /tmp/valgrind_output; then
        echo "[PASS] No leaks"
    else
        echo "[FAIL] Possible memory leak"
        FAIL=$((FAIL + 1))
        grep -A5 "HEAP SUMMARY" /tmp/valgrind_output
    fi
    echo
}

run_test "empty stdin" \
    "printf '' | valgrind --leak-check=full --show-leak-kinds=all $NAME md5"

run_test "simple stdin" \
    "printf 'hello' | valgrind --leak-check=full --show-leak-kinds=all $NAME md5"

run_test "stdin with newline" \
    "printf 'hello\n' | valgrind --leak-check=full --show-leak-kinds=all $NAME md5"

run_test "string argument" \
    "valgrind --leak-check=full --show-leak-kinds=all $NAME md5 -s 'hello'"

run_test "empty string argument" \
    "valgrind --leak-check=full --show-leak-kinds=all $NAME md5 -s ''"

echo "========================================"
echo "SUMMARY"
echo "========================================"
echo "TOTAL: $TOTAL"
echo "FAIL:  $FAIL"
echo "PASS:  $((TOTAL - FAIL))"

rm -f /tmp/ft_ssl_output /tmp/valgrind_output

if [ "$FAIL" -ne 0 ]; then
    exit 1
fi
