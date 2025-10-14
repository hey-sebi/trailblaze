<#
Format or check all C/C++ sources in the tree.
Usage:
  .\format-all.ps1                 # format in place
  .\format-all.ps1 -Check          # check only (CI)
  .\format-all.ps1 -Root path\to   # limit to subtree

   Uses clang-format which must be installed in order for the script to work.
#>

param(
  [string]$Root = ".",
  [switch]$Check
)

$exts = @("*.h","*.hh","*.hpp","*.hxx","*.c","*.cc","*.cpp","*.cxx","*.ixx")
$excludeDirs = @(".git","build","out","dist","node_modules",".venv","venv",".cache",".idea",".vscode","third_party")

# Resolve root
$rootPath = (Resolve-Path $Root).Path

# Gather files
$items = Get-ChildItem -Path $rootPath -Recurse -File -Include $exts -ErrorAction SilentlyContinue |
  Where-Object {
    $full = $_.FullName
    -not ($excludeDirs | ForEach-Object { $full -like "*\$_\*" } | Where-Object { $_ })
  }

if (-not $items -or $items.Count -eq 0) {
  Write-Host "No source files found under '$rootPath'."
  exit 0
}

# Ensure clang-format exists
$clang = Get-Command clang-format -ErrorAction SilentlyContinue
if (-not $clang) {
  Write-Error "clang-format not found on PATH."
  exit 127
}

if ($Check) {
  Write-Host "Checking formatting for $($items.Count) files..."
  $args = @("-style=file","-n","-Werror") + ($items | ForEach-Object { $_.FullName })
  & $clang @args
  if ($LASTEXITCODE -eq 0) { Write-Host "OK: formatting is clean." }
  exit $LASTEXITCODE
} else {
  Write-Host "Formatting $($items.Count) files in place..."
  # Batch the files to avoid very long command lines on Windows
  $batch = @()
  foreach ($f in $items) {
    $batch += $f.FullName
    if ($batch.Count -ge 200) {
      & $clang "-style=file","-i" @batch
      if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
      $batch = @()
    }
  }
  if ($batch.Count -gt 0) {
    & $clang "-style=file","-i" @batch
  }
  Write-Host "Done."
}
