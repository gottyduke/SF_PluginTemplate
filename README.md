# 📑 SFSE Plugin Template
Native dll plugin for [starfield script extender](https://github.com/ianpatt/sfse).

[Create a new plugin project from this template](https://github.com/new?template_name=SF_PluginTemplate&template_owner=gottyduke) and wait for the first workflow action to finish, it will setup project automatically. **Make sure to include all branches**.  

## ⚙ Requirements

- [CMake 3.26+](https://cmake.org/)
  - Add this to your `PATH` during installtion/updating
- [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
- [Vcpkg](https://github.com/microsoft/vcpkg)
  - Set the `VCPKG_ROOT` environment variable to the path of the vcpkg folder
  - Make sure your local vcpkg port is up-to-date by pulling the latest and do `vcpkg integrate install`
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
  - Desktop development with C++
- [Starfield Steam Distribution](#-deployment)
  - Set the `SFPath` environment variable to the path of the game installation
  
## ⬇️ Get started

### 💻 Register Visual Studio as a Generator

- Open `x64 Native Tools Command Prompt`
- Run `cmake`
- Close the cmd window

### 📦 Dependencies

- [SFSE](https://github.com/ianpatt/sfse)
- [DKUtil](https://github.com/gottyduke/DKUtil)

These dependencies can be configured through the git submodule by running `update-submodule.bat`. Alternatively, the dependencies can also use a local git repository, by setting the `SFSEPath` and `DKUtilPath` environment variables to the path of the local git repository.

In order to enable local git repository lookup, existing folders within `extern` should be **removed**.

> To prevent duplicating submodules in each of the local projects, it's recommended to clone the SFSE and DKUtil repositories locally. Then, set the environment path accordingly, this ensures all projects share the same package.  
> Additionally, you can integrate a personal fork of SFSE; this setup makes testing modifications with a plugin project easily.

### 🔨 Building

```
.\make-sln-msvc.bat
cmake --build build --config Release
```
A Visual Studio solution will be generated inside `build` folder.

### ➕ Addon

This project bundles [DKUtil](https://github.com/gottyduke/DKUtil).  
This plugin template has auto deployment rules for easier build-and-test, build-and-package features, using simple json rules. [Read more here!](https://github.com/gottyduke/SF_PluginTemplate/wiki/Custom-deployment-rules)  
> Both enabled by default.

## 📖 License

[MIT](LICENSE)

## ❓ Credits

- [Ryan for his commonLibSSE code](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE) which was referenced in DKUtil.
- [ianpatt's starfield script extender](https://github.com/ianpatt/sfse).
- [Original plugin template](https://github.com/gottyduke/PluginTemplate).