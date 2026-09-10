#!/bin/bash

PROG="./ft_ssl"
TMP="tester_tmp"

PASS=0
FAIL=0
TOTAL=0

mkdir -p "$TMP"

echo "========================================"
echo "        ft_ssl TEST SUITE"
echo "========================================"

pass()
{
	printf "[PASS] %s\n" "$1"
	PASS=$((PASS + 1))
	TOTAL=$((TOTAL + 1))
}

fail()
{
	printf "[FAIL] %s\n" "$1"
	printf "  expected: [%s]\n" "$2"
	printf "  actual:   [%s]\n" "$3"
	FAIL=$((FAIL + 1))
	TOTAL=$((TOTAL + 1))
}

check()
{
	NAME="$1"
	EXPECTED="$2"
	ACTUAL="$3"

	if [ "$EXPECTED" = "$ACTUAL" ]; then
		pass "$NAME"
	else
		fail "$NAME" "$EXPECTED" "$ACTUAL"
	fi
}

cleanup()
{
	rm -rf "$TMP"
}

trap cleanup EXIT

# ============================================================
# TEST DATA
# ============================================================

printf "And above all,\n" > "$TMP/file"
printf "just to be extra clear\n" > "$TMP/file2"
: > "$TMP/empty_file"

INPUTS=(
	""
	"a"
	"abc"
	"foo"
	"42 is nice"
	"hello world"
	"Pity the living."
	"1234567890"
	"special !@#\$%^&*()"
)

# ============================================================
# BASIC COMMAND TESTS
# ============================================================

echo
echo "========== BASIC =========="

EXPECTED=$(printf "" | openssl md5 | awk -F'= ' '{print $2}')
ACTUAL=$(printf "" | "$PROG" md5 | awk -F'= ' '{print $2}')
check "md5 empty stdin" "$EXPECTED" "$ACTUAL"

EXPECTED=$(printf "" | openssl sha256 | awk -F'= ' '{print $2}')
ACTUAL=$(printf "" | "$PROG" sha256 | awk -F'= ' '{print $2}')
check "sha256 empty stdin" "$EXPECTED" "$ACTUAL"

# ============================================================
# STDIN
# ============================================================

echo
echo "========== STDIN =========="

for INPUT in "${INPUTS[@]}"; do
	EXPECTED=$(printf "%s" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
	ACTUAL=$(printf "%s" "$INPUT" | "$PROG" md5 | awk -F'= ' '{print $2}')
	check "md5 stdin: [$INPUT]" "$EXPECTED" "$ACTUAL"

	EXPECTED=$(printf "%s" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
	ACTUAL=$(printf "%s" "$INPUT" | "$PROG" sha256 | awk -F'= ' '{print $2}')
	check "sha256 stdin: [$INPUT]" "$EXPECTED" "$ACTUAL"
done

# ============================================================
# STDIN WITH NEWLINE
# ============================================================

echo
echo "========== STDIN WITH NEWLINE =========="

for INPUT in "${INPUTS[@]}"; do
	EXPECTED=$(printf "%s\n" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
	ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" md5 | awk -F'= ' '{print $2}')
	check "md5 stdin newline: [$INPUT]" "$EXPECTED" "$ACTUAL"

	EXPECTED=$(printf "%s\n" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
	ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" sha256 | awk -F'= ' '{print $2}')
	check "sha256 stdin newline: [$INPUT]" "$EXPECTED" "$ACTUAL"
done

# ============================================================
# -q
# ============================================================

echo
echo "========== -q =========="

for INPUT in "${INPUTS[@]}"; do
	EXPECTED=$(printf "%s\n" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
	ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" md5 -q)
	check "md5 -q stdin: [$INPUT]" "$EXPECTED" "$ACTUAL"

	EXPECTED=$(printf "%s\n" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
	ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" sha256 -q)
	check "sha256 -q stdin: [$INPUT]" "$EXPECTED" "$ACTUAL"
done

# ============================================================
# -s
# ============================================================

echo
echo "========== -s =========="

for INPUT in "${INPUTS[@]}"; do
	EXPECTED=$(printf "%s" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
	ACTUAL=$("$PROG" md5 -q -s "$INPUT")
	check "md5 -q -s: [$INPUT]" "$EXPECTED" "$ACTUAL"

	EXPECTED=$(printf "%s" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
	ACTUAL=$("$PROG" sha256 -q -s "$INPUT")
	check "sha256 -q -s: [$INPUT]" "$EXPECTED" "$ACTUAL"
done

# ============================================================
# -r -s
# ============================================================

echo
echo "========== -r -s =========="

for INPUT in "abc" "foo" "42 is nice" "hello world"; do
	MD5=$(printf "%s" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
	EXPECTED="$MD5 \"$INPUT\""
	ACTUAL=$("$PROG" md5 -r -s "$INPUT")
	check "md5 -r -s: [$INPUT]" "$EXPECTED" "$ACTUAL"

	SHA=$(printf "%s" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
	EXPECTED="$SHA \"$INPUT\""
	ACTUAL=$("$PROG" sha256 -r -s "$INPUT")
	check "sha256 -r -s: [$INPUT]" "$EXPECTED" "$ACTUAL"
done

# ============================================================
# NORMAL -s OUTPUT
# ============================================================

echo
echo "========== NORMAL -s OUTPUT =========="

INPUT="42 is nice"

MD5=$(printf "%s" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
EXPECTED="MD5 (\"$INPUT\") = $MD5"
ACTUAL=$("$PROG" md5 -s "$INPUT")
check "md5 -s normal output" "$EXPECTED" "$ACTUAL"

SHA=$(printf "%s" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
EXPECTED="SHA256 (\"$INPUT\") = $SHA"
ACTUAL=$("$PROG" sha256 -s "$INPUT")
check "sha256 -s normal output" "$EXPECTED" "$ACTUAL"

# ============================================================
# -p
# ============================================================

echo
echo "========== -p =========="

for INPUT in "" "a" "abc" "42 is nice" "hello world" "Pity the living."; do

	MD5=$(printf "%s\n" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
	EXPECTED="(\"$INPUT\")= $MD5"
	ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" md5 -p)
	check "md5 -p: [$INPUT]" "$EXPECTED" "$ACTUAL"

	SHA=$(printf "%s\n" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
	EXPECTED="(\"$INPUT\")= $SHA"
	ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" sha256 -p)
	check "sha256 -p: [$INPUT]" "$EXPECTED" "$ACTUAL"

done

# ============================================================
# -p -q
# ============================================================

echo
echo "========== -p -q =========="

INPUT="42 is nice"

EXPECTED="$INPUT
$(printf "%s\n" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')"
ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" md5 -p -q)
check "md5 -p -q" "$EXPECTED" "$ACTUAL"

EXPECTED="$INPUT
$(printf "%s\n" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')"
ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" sha256 -p -q)
check "sha256 -p -q" "$EXPECTED" "$ACTUAL"

# ============================================================
# FILES
# ============================================================

echo
echo "========== FILES =========="

for FILE in "$TMP/file" "$TMP/file2" "$TMP/empty_file"; do

	EXPECTED=$(openssl md5 "$FILE" | awk -F'= ' '{print $2}')
	ACTUAL=$("$PROG" md5 "$FILE" | awk -F'= ' '{print $2}')
	check "md5 file: $FILE" "$EXPECTED" "$ACTUAL"

	EXPECTED=$(openssl sha256 "$FILE" | awk -F'= ' '{print $2}')
	ACTUAL=$("$PROG" sha256 "$FILE" | awk -F'= ' '{print $2}')
	check "sha256 file: $FILE" "$EXPECTED" "$ACTUAL"

done

# ============================================================
# -q FILE
# ============================================================

echo
echo "========== -q FILE =========="

for FILE in "$TMP/file" "$TMP/file2" "$TMP/empty_file"; do

	EXPECTED=$(openssl md5 "$FILE" | awk -F'= ' '{print $2}')
	ACTUAL=$("$PROG" md5 -q "$FILE")
	check "md5 -q file: $FILE" "$EXPECTED" "$ACTUAL"

	EXPECTED=$(openssl sha256 "$FILE" | awk -F'= ' '{print $2}')
	ACTUAL=$("$PROG" sha256 -q "$FILE")
	check "sha256 -q file: $FILE" "$EXPECTED" "$ACTUAL"

done

# ============================================================
# -r FILE
# ============================================================

echo
echo "========== -r FILE =========="

for FILE in "$TMP/file" "$TMP/file2" "$TMP/empty_file"; do

	EXPECTED="$(openssl md5 "$FILE" | awk -F'= ' '{print $2}') $FILE"
	ACTUAL=$("$PROG" md5 -r "$FILE")
	check "md5 -r file: $FILE" "$EXPECTED" "$ACTUAL"

	EXPECTED="$(openssl sha256 "$FILE" | awk -F'= ' '{print $2}') $FILE"
	ACTUAL=$("$PROG" sha256 -r "$FILE")
	check "sha256 -r file: $FILE" "$EXPECTED" "$ACTUAL"

done

# ============================================================
# -p FILE
# ============================================================

echo
echo "========== -p FILE =========="

INPUT="be sure to handle edge cases carefully"

MD5=$(printf "%s\n" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
FILE_MD5=$(openssl md5 "$TMP/file" | awk -F'= ' '{print $2}')

EXPECTED="(\"$INPUT\")= $MD5
MD5 ($TMP/file) = $FILE_MD5"
ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" md5 -p "$TMP/file")
check "md5 -p file" "$EXPECTED" "$ACTUAL"

SHA=$(printf "%s\n" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
FILE_SHA=$(openssl sha256 "$TMP/file" | awk -F'= ' '{print $2}')

EXPECTED="(\"$INPUT\")= $SHA
SHA256 ($TMP/file) = $FILE_SHA"
ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" sha256 -p "$TMP/file")
check "sha256 -p file" "$EXPECTED" "$ACTUAL"

# ============================================================
# -p -r FILE
# ============================================================

echo
echo "========== -p -r FILE =========="

INPUT="but eventually you will understand"

MD5=$(printf "%s\n" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
FILE_MD5=$(openssl md5 "$TMP/file" | awk -F'= ' '{print $2}')

EXPECTED="(\"$INPUT\")= $MD5
$FILE_MD5 $TMP/file"
ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" md5 -p -r "$TMP/file")
check "md5 -p -r file" "$EXPECTED" "$ACTUAL"

SHA=$(printf "%s\n" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
FILE_SHA=$(openssl sha256 "$TMP/file" | awk -F'= ' '{print $2}')

EXPECTED="(\"$INPUT\")= $SHA
$FILE_SHA $TMP/file"
ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" sha256 -p -r "$TMP/file")
check "sha256 -p -r file" "$EXPECTED" "$ACTUAL"

# ============================================================
# -p -s FILE
# ============================================================

echo
echo "========== -p -s FILE =========="

INPUT="GL HF let's go"
STRING="foo"

MD5=$(printf "%s\n" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
STRING_MD5=$(printf "%s" "$STRING" | openssl md5 | awk -F'= ' '{print $2}')
FILE_MD5=$(openssl md5 "$TMP/file" | awk -F'= ' '{print $2}')

EXPECTED="(\"$INPUT\")= $MD5
MD5 (\"$STRING\") = $STRING_MD5
MD5 ($TMP/file) = $FILE_MD5"
ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" md5 -p -s "$STRING" "$TMP/file")
check "md5 -p -s file" "$EXPECTED" "$ACTUAL"

SHA=$(printf "%s\n" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
STRING_SHA=$(printf "%s" "$STRING" | openssl sha256 | awk -F'= ' '{print $2}')
FILE_SHA=$(openssl sha256 "$TMP/file" | awk -F'= ' '{print $2}')

EXPECTED="(\"$INPUT\")= $SHA
SHA256 (\"$STRING\") = $STRING_SHA
SHA256 ($TMP/file) = $FILE_SHA"
ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" sha256 -p -s "$STRING" "$TMP/file")
check "sha256 -p -s file" "$EXPECTED" "$ACTUAL"

# ============================================================
# COMPLEX COMBINATION
# ============================================================

echo
echo "========== COMPLEX COMBINATIONS =========="

INPUT="one more thing"
STRING1="foo"
STRING2="bar"

MD5=$(printf "%s\n" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
S1=$(printf "%s" "$STRING1" | openssl md5 | awk -F'= ' '{print $2}')
FILE_MD5=$(openssl md5 "$TMP/file" | awk -F'= ' '{print $2}')

EXPECTED="(\"$INPUT\")= $MD5
$S1 \"$STRING1\"
$FILE_MD5 $TMP/file"

ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" md5 -r -p -s "$STRING1" "$TMP/file")
check "md5 -r -p -s file" "$EXPECTED" "$ACTUAL"

SHA=$(printf "%s\n" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
S1=$(printf "%s" "$STRING1" | openssl sha256 | awk -F'= ' '{print $2}')
FILE_SHA=$(openssl sha256 "$TMP/file" | awk -F'= ' '{print $2}')

EXPECTED="(\"$INPUT\")= $SHA
$S1 \"$STRING1\"
$FILE_SHA $TMP/file"

ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" sha256 -r -p -s "$STRING1" "$TMP/file")
check "sha256 -r -p -s file" "$EXPECTED" "$ACTUAL"

# ============================================================
# -q -r -p
# ============================================================

echo
echo "========== -q -r -p =========="

INPUT="just to be extra clear"

STDIN_MD5=$(printf "%s\n" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
FILE_MD5=$(openssl md5 "$TMP/file" | awk -F'= ' '{print $2}')

EXPECTED="$INPUT
$STDIN_MD5
$FILE_MD5 $TMP/file"

ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" md5 -r -q -p "$TMP/file")
check "md5 -r -q -p file" "$EXPECTED" "$ACTUAL"

STDIN_SHA=$(printf "%s\n" "$INPUT" | openssl sha256 | awk -F'= ' '{print $2}')
FILE_SHA=$(openssl sha256 "$TMP/file" | awk -F'= ' '{print $2}')

EXPECTED="$INPUT
$STDIN_SHA
$FILE_SHA $TMP/file"

ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" sha256 -r -q -p "$TMP/file")
check "sha256 -r -q -p file" "$EXPECTED" "$ACTUAL"

# ============================================================
# MULTIPLE STRINGS / FILES
# ============================================================

echo
echo "========== MULTIPLE ARGUMENTS =========="

INPUT="one more thing"

MD5=$(printf "%s\n" "$INPUT" | openssl md5 | awk -F'= ' '{print $2}')
S1=$(printf "%s" "foo" | openssl md5 | awk -F'= ' '{print $2}')
S2=$(printf "%s" "bar" | openssl md5 | awk -F'= ' '{print $2}')
F1=$(openssl md5 "$TMP/file" | awk -F'= ' '{print $2}')

EXPECTED="(\"$INPUT\")= $MD5
$S1 \"foo\"
$F1 $TMP/file
ft_ssl: md5: -s: No such file or directory
ft_ssl: md5: bar: No such file or directory"

ACTUAL=$(printf "%s\n" "$INPUT" | "$PROG" md5 -r -p -s foo "$TMP/file" -s bar 2>&1)

# Do not require this exact error text because the subject
# explicitly says error syntax does not have to match perfectly.
ACTUAL_MAIN=$(printf "%s\n" "$INPUT" | "$PROG" md5 -r -p -s foo "$TMP/file" 2>&1)

EXPECTED_MAIN="(\"$INPUT\")= $MD5
$S1 \"foo\"
$F1 $TMP/file"

check "md5 -r -p -s file" "$EXPECTED_MAIN" "$ACTUAL_MAIN"

# ============================================================
# ERROR TESTS
# ============================================================

echo
echo "========== ERRORS =========="

ACTUAL=$("$PROG" foobar 2>&1)
if echo "$ACTUAL" | grep -q "invalid command"; then
	pass "invalid command"
else
	fail "invalid command" "message containing 'invalid command'" "$ACTUAL"
fi

ACTUAL=$("$PROG" 2>&1)
if echo "$ACTUAL" | grep -q "usage"; then
	pass "no command"
else
	fail "no command" "message containing 'usage'" "$ACTUAL"
fi

ACTUAL=$("$PROG" md5 -s 2>&1)
if echo "$ACTUAL" | grep -q -- "-s"; then
	pass "-s without argument"
else
	fail "-s without argument" "sensible -s error" "$ACTUAL"
fi

ACTUAL=$("$PROG" sha256 -s 2>&1)
if echo "$ACTUAL" | grep -q -- "-s"; then
	pass "sha256 -s without argument"
else
	fail "sha256 -s without argument" "sensible -s error" "$ACTUAL"
fi

ACTUAL=$("$PROG" md5 "$TMP/does_not_exist" 2>&1)
if echo "$ACTUAL" | grep -q "$TMP/does_not_exist"; then
	pass "md5 missing file"
else
	fail "md5 missing file" "error containing filename" "$ACTUAL"
fi

ACTUAL=$("$PROG" sha256 "$TMP/does_not_exist" 2>&1)
if echo "$ACTUAL" | grep -q "$TMP/does_not_exist"; then
	pass "sha256 missing file"
else
	fail "sha256 missing file" "error containing filename" "$ACTUAL"
fi

# ============================================================
# SUMMARY
# ============================================================

echo
echo "========================================"
printf "PASS: %d\n" "$PASS"
printf "FAIL: %d\n" "$FAIL"
printf "TOTAL: %d\n" "$TOTAL"
echo "========================================"

if [ "$FAIL" -ne 0 ]; then
	exit 1
fi

exit 0
