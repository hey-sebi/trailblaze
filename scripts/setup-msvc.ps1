# Script to setup environment variables for working with Visual Studio Build Tools.
#
#  Usage: source the script like so
#  for Intel/AMD 64 bit arch:
#    . .\setup-msvc.ps1
#    . .\setup-msvc.ps1 -Arch x64
#  for Intel/AMD 32 bit arch:
#    . .\setup-msvc.ps1 -Arch x86
#  for ARM 64 bit arch:
#    . .\setup-msvc.ps1 -Arch arm64
param(
  [ValidateSet('x64','x86','arm64')] [string]$Arch = 'x64',
  [string]$VsWhere = "vswhere.exe"
  # [string]$VsWhere = "$env:ProgramFiles(x86)\Microsoft Visual Studio\Installer\vswhere.exe"
)

function Get-VSInstallPath {
  if (!(Get-Command $VsWhere)) { throw "vswhere not found in the PATH" }
  & $VsWhere -latest -products * `
    -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
    -property installationPath
}

$installPath = (Get-VSInstallPath).Trim()
if (-not $installPath) { throw "Could not locate VS Build Tools via vswhere." }

$vsDevCmd = Join-Path $installPath "Common7\Tools\VsDevCmd.bat"
if (!(Test-Path $vsDevCmd)) { throw "VsDevCmd.bat not found at: $vsDevCmd" }

# Run VsDevCmd and dump the environment with `set`
$envDump = & cmd.exe /s /c "`"$vsDevCmd`" -arch=$Arch -host_arch=$Arch && set"
if ($LASTEXITCODE -ne 0) { throw "VsDevCmd failed with exit code $LASTEXITCODE" }

# Import variables into current PS session
$envDump -split "`r?`n" | ForEach-Object {
  if ($_ -match "^(?<k>[^=]+)=(?<v>.*)$") {
    $k = $Matches['k']; $v = $Matches['v']
    # Skip read-only weirdness or cmd.exe internals
    if ($k -notin @('CMD_EXT_VERSION','CMDEXTVERSION','COMSPEC','PROMPT')) {
      # PowerShell will expand %FOO% lazily in some tools; keep raw text
      [Environment]::SetEnvironmentVariable($k, $v, "Process")
    }
  }
}

# Helpful extras for CMake/Ninja
$env:CC  = "cl.exe"
$env:CXX = "cl.exe"

Write-Host "MSVC environment set for $Arch (VS @ $installPath)."
Write-Host "Compiler version:" (& cl.exe 2>&1)[0]
