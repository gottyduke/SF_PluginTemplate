# 📑 PluginTemplate
Generic native dll plugin template for various games.

## ⚙ Requirements

- [CMake](https://cmake.org/)
  - Add this to your `PATH`
- [DKUtil](https://github.com/gottyduke/DKUtil)
  - Init & update with git submodule
- [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
- [Vcpkg](https://github.com/microsoft/vcpkg)
  - Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
  - Desktop development with C++
- [Deploy target](#📦-deployment)
  - Set custom deploy rules accordingly
  
## 📦 Deployment

This plugin template comes with a simple custom deployer script to enable custom distribution rules fitting most use cases.  
To get started on adding custom deploy rules, check out the [default examples](PluginTemplate/dist/rules).  
| action    | usage                                                        |
| --------- | ------------------------------------------------------------ |
| `base`    | set `params[0]` to `params[1]`                               |
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

## 💻 Register Visual Studio as a Generator

- Open `x64 Native Tools Command Prompt`
- Run `cmake`
- Close the cmd window

## 🔨 Building

[Create a new github repo from this template](https://github.com/new?template_name=PluginTemplate&template_owner=gottyduke) or: 

```
git clone https://github.com/gottyduke/PluginTemplate.git
cd PluginTemplate
git submodule init
git submodule update --remote
.\build-release.ps1
```

## 📖 License

[MIT](LICENSE)

## ❓ Credits

- [Ryan for his commonLibSSE code](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE) which was referenced in DKUtil.
