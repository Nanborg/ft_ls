#!/bin/sh

set -u

root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
cd "$root" || exit 1

if ! make -s; then
	echo "Build failed"
	exit 1
fi

tmpdir=$(mktemp -d) || exit 1
trap 'chmod -R u+rwx "$tmpdir" 2>/dev/null; rm -rf "$tmpdir"' EXIT HUP INT TERM
fixture="$tmpdir/fixture"
mkdir -p "$fixture/empty" "$fixture/tree/sub/deep" "$fixture/unreadable"

touch "$fixture/tree/.hidden" \
	"$fixture/tree/alpha" \
	"$fixture/tree/file with spaces" \
	"$fixture/tree/old-date" \
	"$fixture/tree/recent-date" \
	"$fixture/tree/same-date-a" \
	"$fixture/tree/same-date-b" \
	"$fixture/tree/setgid" \
	"$fixture/tree/setuid" \
	"$fixture/tree/sticky"
printf 'nested\n' > "$fixture/tree/sub/deep/child"
printf 'payload\n' > "$fixture/tree/alpha"
long_name=$(printf '%220s' '' | tr ' ' x)
touch "$fixture/tree/$long_name"
touch "$fixture/tree/old-date" "$fixture/tree/recent-date"
touch -d '2020-01-02 03:04:05' "$fixture/tree/old-date"
touch -d '2026-10-28 03:04:05' "$fixture/tree/recent-date"
touch -d '2024-06-07 08:09:10' \
	"$fixture/tree/same-date-a" "$fixture/tree/same-date-b"
chmod 4755 "$fixture/tree/setuid"
chmod 2750 "$fixture/tree/setgid"
chmod 1777 "$fixture/tree/sticky"
chmod 000 "$fixture/unreadable"
ln -s alpha "$fixture/tree/link-file"
ln -s sub "$fixture/tree/link-dir"
ln -s missing-target "$fixture/tree/broken-link"
ln -s .. "$fixture/tree/sub/deep/loop"

long_path="$tmpdir/long-path"
index=1
while [ "$index" -le 4 ]; do
	component=$(printf '%120s' '' | tr ' ' x)
	long_path="$long_path/$component"
	mkdir -p "$long_path"
	index=$((index + 1))
done
touch "$long_path/leaf"

index=1
while [ "$index" -le 25 ]; do
	name=$(printf 'entry-%02d' "$index")
	touch "$fixture/tree/$name"
	index=$((index + 1))
done

mkdir -p "$tmpdir/many"
index=1
while [ "$index" -le 30 ]; do
	name=$(printf 'file-%02d' "$index")
	touch "$tmpdir/many/$name"
	index=$((index + 1))
done

passed=0
failed=0
skipped=0

check_case()
{
	name=$1
	shift
	LC_ALL=C ./ft_ls "$@" >"$tmpdir/actual.out" 2>"$tmpdir/actual.err"
	actual_status=$?
	LC_ALL=C /bin/ls "$@" >"$tmpdir/expected.out" 2>"$tmpdir/expected.err"
	expected_status=$?
	sed 's#/bin/ls#ls#g' "$tmpdir/expected.err" >"$tmpdir/expected.norm.err"
	sed 's/^ft_ls:/ls:/' "$tmpdir/actual.err" >"$tmpdir/actual.norm.err"
	diff -u "$tmpdir/expected.out" "$tmpdir/actual.out" \
		>"$tmpdir/out.diff"
	out_status=$?
	diff -u "$tmpdir/expected.norm.err" "$tmpdir/actual.norm.err" \
		>"$tmpdir/err.diff"
	err_status=$?
	if [ "$out_status" -eq 0 ] && [ "$err_status" -eq 0 ] &&
		[ "$actual_status" -eq "$expected_status" ]; then
		echo "PASS: $name"
		passed=$((passed + 1))
		return
	fi
	echo "FAIL: $name (ft_ls=$actual_status, ls=$expected_status)"
	if [ -s "$tmpdir/out.diff" ]; then
		cat "$tmpdir/out.diff"
	fi
	if [ -s "$tmpdir/err.diff" ]; then
		cat "$tmpdir/err.diff"
	fi
	if [ "$actual_status" -ne "$expected_status" ]; then
		echo "Expected exit $expected_status, got $actual_status"
	fi
	failed=$((failed + 1))
}

skip_case()
{
	echo "SKIP: $1"
	skipped=$((skipped + 1))
}

check_case "no arguments (current directory)"
check_case "default directory listing" "$fixture/tree"
check_case "empty directory" "$fixture/empty"
check_case "one file argument" "$fixture/tree/alpha"
check_case "one directory argument" "$fixture/tree"
check_case "-a without argument"
check_case "-a with file argument" -a "$fixture/tree/alpha"
check_case "-a with directory argument" -a "$fixture/tree"
check_case "one long-format file argument" -l "$fixture/tree/alpha"
check_case "-l without argument" -l
check_case "-l with directory argument" -l "$fixture/tree"
check_case "-l displays symlinks" -l "$fixture/tree/link-file"
check_case "multiple file arguments" \
	"$fixture/tree/recent-date" "$fixture/tree/alpha"
check_case "multiple directory arguments" "$fixture/tree/sub" "$fixture/tree"
check_case "mixed files and directories" \
	"$fixture/tree/sub" "$fixture/tree/alpha" "$fixture/tree"
check_case "-r with file, directory, file" -r \
	"$fixture/tree/recent-date" "$fixture/tree" "$fixture/tree/alpha"
check_case "-t with file, directory, file" -t \
	"$fixture/tree/recent-date" "$fixture/tree" "$fixture/tree/alpha"
check_case "missing path" "$tmpdir/does-not-exist"
check_case "missing and valid paths" \
	"$tmpdir/does-not-exist" "$fixture/tree/alpha"
check_case "missing path followed by directory" \
	"$tmpdir/does-not-exist" "$fixture/tree"
check_case "broken symlink argument" -l "$fixture/tree/broken-link"
check_case "unknown option" -z

check_case "-a includes hidden files" -a "$fixture/tree"
check_case "-l long format" -l "$fixture/tree"
check_case "-l on an empty directory" -l "$fixture/empty"
check_case "-r reverse order" -r "$fixture/tree"
check_case "-t modification-time order" -t "$fixture/tree"
check_case "-tr reverse time order" -tr "$fixture/tree"
check_case "-a includes . and .." -a "$fixture/empty/.."
check_case "-la combined options" -la "$fixture/tree"
check_case "-lt combined options" -lt "$fixture/tree"
check_case "separate -l -t options" -l -t "$fixture/tree"
check_case "grouped -lt options" -lt "$fixture/tree"
check_case "-latr combined options" -latr "$fixture/tree"
check_case "-R nested directories" -R "$fixture/tree"
check_case "-R without argument" -R
check_case "-Ra hidden files recursively" -Ra "$fixture/tree"
check_case "-Rl recursive long format" -Rl "$fixture/tree"
check_case "-Rtr recursive reverse time order" -Rtr "$fixture/tree"
check_case "-R does not follow directory symlinks or loops" \
	-R "$fixture/tree"
check_case "many files" "$tmpdir/many"
check_case "long path argument" "$long_path"

if [ "$(id -u)" -eq 0 ]; then
	skip_case "unreadable directory (runner is root)"
else
	check_case "unreadable directory" "$fixture/unreadable"
fi

if [ -c /dev/null ]; then
	check_case "character device major/minor" -l /dev/null
else
	skip_case "character device major/minor (/dev/null unavailable)"
fi

echo "$passed passed, $failed failed, $skipped skipped"
test "$failed" -eq 0
