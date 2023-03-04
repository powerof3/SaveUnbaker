# Save Unbaker

Always load certain records from plugins instead of save, such as weight, opposite gender animations and persistent ref transforms
[SSE/AE](https://www.nexusmods.com/skyrimspecialedition/mods/85565)
[VR](https://www.nexusmods.com/skyrimspecialedition/mods/86265)

## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++
* [CommonLibSSE](https://github.com/powerof3/CommonLibSSE/tree/dev)
	* You need to build from the powerof3/dev branch
	* Add this as as an environment variable `CommonLibSSEPath`
* [CommonLibVR](https://github.com/alandtse/CommonLibVR/tree/vr)
	* Add this as as an environment variable `CommonLibVRPath` instead of /external

## User Requirements
* [Address Library for SKSE](https://www.nexusmods.com/skyrimspecialedition/mods/32444)
	* Needed for SSE/AE
* [VR Address Library for SKSEVR](https://www.nexusmods.com/skyrimspecialedition/mods/58101)
	* Needed for VR

## Register Visual Studio as a Generator
* Open `x64 Native Tools Command Prompt`
* Run `cmake`
* Close the cmd window

## Building
```
git clone https://github.com/powerof3/SaveUnbaker.git
cd SaveUnbaker
# pull commonlib /extern to override the path settings
git submodule init
# to update submodules to checked in build
git submodule update
```

### SSE
```
cmake --preset vs2022-windows-vcpkg-se
cmake --build build --config Release
```
### AE
```
cmake --preset vs2022-windows-vcpkg-ae
cmake --build buildae --config Release
```
### VR
```
cmake --preset vs2022-windows-vcpkg-vr
cmake --build buildvr --config Release
```
## License
[MIT](LICENSE)
