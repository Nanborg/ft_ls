#!/bin/sh
# Run automated comparisons against /bin/ls.

set -eu

# Reproducible GNU/Linux comparisons, independent of the user's shell settings.
export LC_ALL=C TZ=UTC
unset BLOCK_SIZE BLOCKSIZE LS_BLOCK_SIZE TIME_STYLE QUOTING_STYLE POSIXLY_CORRECT
if ! command -v timeout >/dev/null 2>&1; then
	echo "GNU timeout is required (the tests target GNU/Linux)." >&2
	exit 1
fi

root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
cd "$root" || exit 1
ls_bin=${FT_LS_BIN:-"$root/ft_ls"}
case ${FT_LS_TIMEOUT:-15} in
	''|*[!0-9]*|0) echo "FT_LS_TIMEOUT must be a positive integer." >&2; exit 1 ;;
esac
if ! [ "${FT_LS_TIMEOUT:-15}" -gt 0 ] 2>/dev/null; then
	echo "FT_LS_TIMEOUT must be a positive integer." >&2
	exit 1
fi

if ! make -s; then
	echo "Build failed"
	exit 1
fi

tmpdir=$(mktemp -d) || exit 1
trap 'chmod -R u+rwx "$tmpdir" 2>/dev/null; rm -rf "$tmpdir"' EXIT
trap 'exit 129' HUP
trap 'exit 130' INT
trap 'exit 143' TERM
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
touch -d '1 hour ago' "$fixture/tree/recent-date"
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

# Additional fixtures: keep dates and names deliberately opposed for -t.
mkdir -p "$fixture/args/a_dir_old" "$fixture/args/z_dir_new" \
	"$fixture/tree/.hidden-dir" "$fixture/permissions" "$fixture/sizes" \
	"$fixture/dates" "$fixture/names" "$fixture/read-only" \
	"$fixture/no-read" "$fixture/recurse/accessible" \
	"$fixture/recurse/refused" "$tmpdir/failures"
touch "$fixture/tree/.hidden-dir/inside"
touch -t 202001010000 "$fixture/args/a_old" "$fixture/args/a_dir_old"
touch -t 202101010000 "$fixture/args/z_new" "$fixture/args/z_dir_new"
touch -t 202401010000 "$fixture/args/same-a" "$fixture/args/same-z"
ln "$fixture/tree/alpha" "$fixture/tree/hard-link"
ln -s link-file "$fixture/tree/link-chain"
ln -s self-link "$fixture/tree/self-link"
ln -s cycle-b "$fixture/tree/cycle-a"
ln -s cycle-a "$fixture/tree/cycle-b"
mkfifo "$fixture/tree/fifo"

for mode in 000 001 002 004 010 020 040 100 200 400 644 755 777 \
	4755 4644 2755 2644 1755 1644 7777; do
	touch "$fixture/permissions/mode-$mode"
	chmod "$mode" "$fixture/permissions/mode-$mode"
done
touch "$fixture/read-only/one" "$fixture/read-only/two" \
	"$fixture/no-read/inside" "$fixture/recurse/accessible/child" \
	"$fixture/recurse/refused/child"
chmod 400 "$fixture/read-only"
chmod 100 "$fixture/no-read"
chmod 000 "$fixture/recurse/refused"

touch "$fixture/sizes/zero"
printf x > "$fixture/sizes/one"
for size in 2147483647 2147483648 3221225472 5368709120; do
	truncate -s "$size" "$fixture/sizes/size-$size" || exit 1
done
for days in 179 180 181 184; do
	touch -d "$days days ago" "$fixture/dates/old-$days"
done
touch -d '1 hour ago' "$fixture/dates/recent"
touch -d '30 minutes' "$fixture/dates/future-30m"
touch -d '2 hours' "$fixture/dates/future-2h"
touch -t 197001020304 "$fixture/dates/ancient"

touch "$fixture/names/-" "$fixture/names/-a" "$fixture/names/--" \
	"$fixture/names/A" "$fixture/names/a" "$fixture/names/Z" \
	"$fixture/names/z" "$fixture/names/.hidden" \
	"$fixture/names/..not-parent" "$fixture/names/_under" \
	"$fixture/names/with spaces" "$fixture/names/ leading" \
	"$fixture/names/trailing " "$fixture/names/quote'file" \
	"$fixture/names/quote\"file"
tab_name=$(printf 'tab\tfile')
newline_name=$(printf 'line\nfile')
touch "$fixture/names/$tab_name" "$fixture/names/$newline_name"
max_name=$(printf '%0255d' 0)
touch "$fixture/names/$max_name" || exit 1

# Fixture setup must succeed; comparison failures must not stop the suite.
set +e
passed=0
failed=0
skipped=0

check_case()
{
	name=$1
	shift
	timeout -k 2 "${FT_LS_TIMEOUT:-15}" "$ls_bin" "$@" \
		>"$tmpdir/actual.out" 2>"$tmpdir/actual.err"
	actual_status=$?
	LC_ALL=C /bin/ls "$@" >"$tmpdir/expected.out" 2>"$tmpdir/expected.err"
	expected_status=$?
	# readdir order may change the order of independent diagnostics.
	sed 's#/bin/ls#ls#g' "$tmpdir/expected.err" | sort >"$tmpdir/expected.norm.err"
	sed 's#/bin/ls#ls#g; s/^ft_ls:/ls:/' "$tmpdir/actual.err" \
		| sort >"$tmpdir/actual.norm.err"
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
	case_dir="$tmpdir/failures/$failed"
	mkdir -p "$case_dir"
	cp "$tmpdir/actual.out" "$tmpdir/actual.err" \
		"$tmpdir/expected.out" "$tmpdir/expected.err" \
		"$tmpdir/out.diff" "$tmpdir/err.diff" "$case_dir/"
	{
		printf '%s\n' "$name"
		printf 'cwd: %s\n' "$PWD"
		printf 'argument: <%s>\n' "$@"
		printf 'status: ft_ls=%s ls=%s\n' "$actual_status" "$expected_status"
	} >"$case_dir/case.txt"
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
check_case "-a without argument" -a
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

# Every subset of l/R/a/r/t, with file arguments and directory arguments too.
for opt in '' l R a r t lR la lr lt Ra Rr Rt ar at rt \
	lRa lRr lRt lar lat lrt Rar Rat Rrt art lRar lRat lRrt lart Rart lRart; do
	if [ -z "$opt" ]; then
		set --
	else
		set -- "-$opt"
	fi
	check_case "matrix [$opt]: populated directory" "$@" "$fixture/tree"
	check_case "matrix [$opt]: empty directory" "$@" "$fixture/empty"
	check_case "matrix [$opt]: file arguments" "$@" \
		"$fixture/args/a_old" "$fixture/args/z_new"
	check_case "matrix [$opt]: directory arguments" "$@" \
		"$fixture/args/a_dir_old" "$fixture/args/z_dir_new"
	check_case "matrix [$opt]: mixed arguments" "$@" \
		"$fixture/args/z_dir_new" "$fixture/args/a_old" \
		"$fixture/args/a_dir_old" "$fixture/args/z_new"
done

check_case "-r without argument" -r
check_case "-t without argument" -t
check_case "all options separately" -l -R -a -r -t "$fixture/tree"
check_case "all options in another order" -tarlR "$fixture/tree"
check_case "repeated options" -llaaRRrrtt "$fixture/tree"
check_case "end of options" -- "$fixture/tree"
check_case "-l then end of options" -l -- "$fixture/tree"
check_case "end of options without operand" --
check_case "invalid option in a group" -laz
check_case "invalid option with missing operand" -z "$tmpdir/absent"
check_case "empty operand" ''
check_case "several missing operands" "$tmpdir/z-absent" "$tmpdir/a-absent"
check_case "file used as parent directory" "$fixture/tree/alpha/child"
check_case "trailing slash on a file" "$fixture/tree/alpha/"
check_case "trailing slash and relative components" \
	"$fixture/tree/" "$fixture/tree/sub/../sub"
check_case "repeated directory operands" "$fixture/tree" "$fixture/tree"
check_case "repeated file operands" "$fixture/tree/alpha" "$fixture/tree/alpha"
check_case "GNU option after an operand" "$fixture/tree" -a
check_case "GNU options after an operand" "$fixture/tree" -l -t

# Keep the current shell so the counters survive tests from another cwd.
cd "$fixture/names" || exit 1
check_case "dash names after --" -- - -a --
check_case "dash name in long format" -l -- -a
check_case "dash name with ./ prefix" ./-a
cd "$root" || exit 1

for opt in '' l R lR; do
	if [ -z "$opt" ]; then set --; else set -- "-$opt"; fi
	for link in link-file link-dir broken-link link-chain self-link cycle-a; do
		check_case "link [$opt]: $link" "$@" "$fixture/tree/$link"
	done
done
check_case "directory symlink with trailing slash" -l "$fixture/tree/link-dir/"
check_case "mixed symlinks and directory" -l "$fixture/tree/link-file" \
	"$fixture/tree/link-dir" "$fixture/tree/sub"
check_case "hard links and link count" -l "$fixture/tree/alpha" "$fixture/tree/hard-link"
check_case "all ordinary and special permission bits" -l "$fixture/permissions"
if [ "$(id -u)" -eq 0 ]; then
	skip_case "permission distinctions and recursive errors (runner is root)"
else
	check_case "read permission without search permission" "$fixture/read-only"
	check_case "read without search permission in -l" -l "$fixture/read-only"
	check_case "search permission without read permission" "$fixture/no-read"
	check_case "known child with search permission only" "$fixture/no-read/inside"
	check_case "unreadable directory in -l" -l "$fixture/unreadable"
	check_case "child behind a forbidden directory" "$fixture/recurse/refused/child"
	check_case "forbidden and valid operands" "$fixture/unreadable" \
		"$fixture/tree/alpha" "$fixture/tree"
	check_case "recursive permission error" -R "$fixture/recurse"
	check_case "recursive permission error in -la" -laR "$fixture/recurse"
fi

check_case "large sparse files and total blocks" -l "$fixture/sizes"
for size in 2147483647 2147483648 3221225472 5368709120; do
	check_case "file size $size" -l "$fixture/sizes/size-$size"
done
check_case "shared long-format widths for file operands" -l \
	"$fixture/sizes/zero" "$fixture/sizes/size-5368709120"
check_case "FIFO file type" -l "$fixture/tree/fifo"
if [ -c /dev/null ] && [ -c /dev/zero ]; then
	check_case "several character devices" -l /dev/null /dev/zero
else
	skip_case "several character devices unavailable"
fi
check_case "recent, future and old dates" -l "$fixture/dates"
check_case "dates sorted by time" -lt "$fixture/dates"
check_case "dates sorted by reverse time" -ltr "$fixture/dates"
for date_case in future-30m future-2h old-179 old-180 old-181 old-184 ancient; do
	check_case "date boundary: $date_case" -l "$fixture/dates/$date_case"
done
check_case "equal argument times: name tie-break" -t \
	"$fixture/args/same-z" "$fixture/args/same-a"
check_case "equal argument times: reverse tie-break" -tr \
	"$fixture/args/same-z" "$fixture/args/same-a"
check_case "special names in byte order" "$fixture/names"
check_case "special names in long format" -la "$fixture/names"
check_case "special names in reverse order" -r "$fixture/names"
check_case "..not-parent remains visible in recursion" -laR "$fixture/names"
check_case "leading and trailing spaces in operands" -l \
	"$fixture/names/with spaces" "$fixture/names/ leading" "$fixture/names/trailing "
check_case "maximum filename length" -l "$fixture/names/$max_name"
check_case "long path in recursion" -R "$tmpdir/long-path"

if command -v python3 >/dev/null 2>&1; then
	if python3 - "$fixture/socket" <<'PY'
import socket, sys
try:
    with socket.socket(socket.AF_UNIX) as sock:
        sock.bind(sys.argv[1])
except OSError as error:
    print(f"Socket fixture unavailable: {error}", file=sys.stderr)
    sys.exit(1)
PY
	then
		check_case "Unix socket file type" -l "$fixture/socket"
	else
		skip_case "Unix socket creation unavailable"
	fi
	mkdir -p "$fixture/nano"
	if python3 - "$fixture/nano" <<'PY'
import os, pathlib, sys
root = pathlib.Path(sys.argv[1])
for name, atime, mtime in (
    ('a_old', 1700000000900000000, 1700000000100000000),
    ('z_new', 1700000000100000000, 1700000000900000000),
):
    path = root / name
    path.touch()
    os.utime(path, ns=(atime, mtime))
    if path.stat().st_mtime_ns != mtime:
        sys.exit(1)
PY
	then
		check_case "nanosecond time ordering" -t "$fixture/nano"
		check_case "reverse nanosecond ordering" -tr "$fixture/nano"
		check_case "nanosecond ordering of operands" -t \
			"$fixture/nano/a_old" "$fixture/nano/z_new"
	else
		skip_case "filesystem does not preserve the requested nanoseconds"
	fi
else
	skip_case "socket and nanosecond fixtures require Python 3"
fi

if [ "$failed" -gt 0 ]; then
	report_dir=$(mktemp -d "${TMPDIR:-/tmp}/ft_ls-failures.XXXXXX") || exit 1
	cp -R "$tmpdir/failures/." "$report_dir/"
	echo "Failure details saved in: $report_dir"
fi
echo "$passed passed, $failed failed, $skipped skipped"
test "$failed" -eq 0
