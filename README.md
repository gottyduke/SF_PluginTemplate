# 📑 SFSE Plugin Template
Native dll plugin for [starfield script extender](https://github.com/ianpatt/sfse).

[Create a new plugin project from this template](https://github.com/new?template_name=SF_PluginTemplate&template_owner=gottyduke) 

## ⚙ Requirements

- [CMake 3.26+](https://cmake.org/)
  - Add this to your `PATH`
- [CommonLibSF](https://github.com/ianpatt/sfse)
  - Init & update with git submodule
- [DKUtil](https://github.com/gottyduke/DKUtil)
  - Init & update with git submodule
- [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
- [Vcpkg](https://github.com/microsoft/vcpkg)
  - Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
  - Make sure your local vcpkg port is up-to-date by pulling the latest and do `vcpkg integrate install`
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
  - Desktop development with C++
- [Starfield Steam Distribution](#-deployment)
  - Add the environment variable `SFPath` with the value as the path to the game installation
  
## Get started

### 💻 Register Visual Studio as a Generator

- Open `x64 Native Tools Command Prompt`
- Run `cmake`
- Close the cmd window

### 🔨 Building

```
.\update-submodule.bat
.\make-sln-msvc.bat
// or generate solution
.\build-msvc.bat
```

### 📦 Deployment

This plugin template comes with a simple custom deployer script to enable custom distribution rules fitting most use cases.  
To get started on adding custom deploy rules, check out the [default examples](Plugin/dist/rules).  
| action    | usage                                                        |
| --------- | ------------------------------------------------------------ |
| `base`    | set variable `params[0]` with value `params[1]`              |
| `copy`    | copy `params[0]` to `params[1]`                              |
| `copy_if` | do `copy` if file exists                                     |
| `package` | add `params[0..-1]` list of sources to zip file `params[-1]` |
| `remove`  | remove `params` list of sources                              |
| `script`  | execute raw powershell script                                |


The following base variables are provided by default:
```
cmake_output    // this is the binary output path
dist            // this is the dist folder path, also the working directory of deployer script
project_name    // project name same as CMakeLists
project_version // project version same as CMakeLists
```

Deploy actions can be enabled by build configuration(`debug`, `release`, `relwithdebinfo`, etc)

### ➕ DKUtil addon

This project bundles [DKUtil](https://github.com/gottyduke/DKUtil).

## 📖 License

[MIT](LICENSE)

## ❓ Credits

- [ianpatt's starfield script extender](https://github.com/ianpatt/sfse).
- [CommonLibSF, a collaborative effort project](https://github.com/Starfield-Reverse-Engineering/CommonLibSF)
