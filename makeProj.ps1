Set-ExecutionPolicy RemoteSigned

if (!(Test-Path -Path "Generated/AdventOfCode2025" -PathType Container)) {
	mkdir Generated/AdventOfCode2025
}
cd Generated/AdventOfCode2025
cmake -DCMAKE_TOOLCHAIN_FILE=C:/ProgramData/vcpkg/scripts/buildsystems/vcpkg.cmake ../.. -G "Visual Studio 17 2022" -A x64