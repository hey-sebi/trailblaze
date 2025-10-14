#!/usr/bin/env bash
# Format or check all C/C++ sources in the tree.
# Usage:
#   ./format-all.sh                # format in place
#   ./format-all.sh --check        # just check (CI), nonzero exit on diff
#   ./format-all.sh path/to/dir    # limit to a subtree
#   ./format-all.sh --check path   # combination of above

# Uses clang-format which must be installed in order for the script to work.

set -euo pipefail

MODE="format"  # or "check"
ROOT="."
if [[ "${1:-}" == "--check" ]]; then
  MODE="check"
  shift || true
fi
if [[ "${1:-}" != "" ]]; then
  ROOT="$1"
fi

# Extensions to include
EXTS=(
  "*.h" "*.hh" "*.hpp" "*.hxx"
  "*.c" "*.cc" "*.cpp" "*.cxx"
  "*.ixx"  # C++ modules, if you use them
)

# Directories to exclude (add/remove to taste)
EXCLUDES=(
  ".git" "build" "build-*"
  "out" "dist" "node_modules"
  ".venv" "venv" ".cache"
  ".idea" ".vscode" "third_party"
)

# Build the 'find' expression
find_args=( "$ROOT" -type f )
# Add name patterns
name_expr=()
for p in "${EXTS[@]}"; do
  name_expr+=( -name "$p" -o )
done
# trim trailing -o
unset 'name_expr[${#name_expr[@]}-1]'
find_args+=( \( "${name_expr[@]}" \) )

# Add excludes
for ex in "${EXCLUDES[@]}"; do
  find_args+=( -not -path "*/$ex/*" )
done

# Find files (null-separated to handle spaces)
mapfile -d '' files < <(find "${find_args[@]}" -print0)

if [[ ${#files[@]} -eq 0 ]]; then
  echo "No source files found under '$ROOT'." >&2
  exit 0
fi

if ! command -v clang-format >/dev/null 2>&1; then
  echo "clang-format not found on PATH." >&2
  exit 127
fi

if [[ "$MODE" == "check" ]]; then
  echo "Checking formatting for ${#files[@]} files..."
  # -n: dry-run, -Werror: nonzero exit if changes would be made
  # Use xargs -0 to batch calls; clang-format supports multiple files.
  printf '%s\0' "${files[@]}" | xargs -0 clang-format -style=file -n -Werror
  echo "OK: formatting is clean."
else
  echo "Formatting ${#files[@]} files in place..."
  printf '%s\0' "${files[@]}" | xargs -0 clang-format -style=file -i
  echo "Done."
fi
