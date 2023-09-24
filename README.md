# 📑 SFSE Plugin Template
Native dll plugin for [starfield script extender](https://github.com/ianpatt/sfse).

[Create a new plugin project from this template](https://github.com/new?template_name=SF_PluginTemplate&template_owner=gottyduke) and wait for the first workflow action to finish, it will setup project automatically.

## 📖 License

By using [this branch](https://github.com/gottyduke/SF_PluginTemplate/tree/main), you agree to comply with [CommonLibSF](https://github.com/Starfield-Reverse-Engineering/CommonLibSF) license, which is [GPL-3.0-or-later](COPYING) WITH [Modding Exception AND GPL-3.0 Linking Exception (with Corresponding Source)](EXCEPTIONS). Specifically, the Modded Code is Starfield (and its variants) and Modding Libraries include [Starfield Script Extender](https://github.com/ianpatt/sfse) and [DKUtil](https://github.com/gottyduke/DKUtil/) (and variants).  

To put it shortly: when you distribute a binary linked against CommonLibSF, you are obliged to provide access to the source code as well.  

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

- [CommonLibSF](https://github.com/Starfield-Reverse-Engineering/CommonLibSF)
- [DKUtil](https://github.com/gottyduke/DKUtil)

These dependencies can be configured through the git submodule by running `update-submodule.bat`. Alternatively, the dependencies can also use a local git repository, by setting the `CommonLibSFPath` and `DKUtilPath` environment variables to the path of the local git repository.

In order to enable local git repository lookup, existing folders within `extern` should be **removed**.

> To prevent duplicating submodules in multiple local projects, it's recommended to clone the CommonLibSF and DKUtil repositories locally. Then, set the environment path accordingly, this ensures all projects share the same package.  

> Additionally, you can use a personal fork of CommonLibSF; this setup makes testing modifications with a plugin project easily.

### 🔨 Building

```
.\make-sln-msvc.bat
cmake --build build --config Release
```
A Visual Studio solution will be generated inside `build` folder.

### ❓ Development FAQ.

Check out the [wiki page](https://github.com/gottyduke/SF_PluginTemplate/wiki/Common-FAQ.) and/or feel free to open an issue.  

### ➕ Addon

This project bundles [DKUtil](https://github.com/gottyduke/DKUtil).  
This project has auto deployment rules for easier build-and-test, build-and-package features, using simple json rules. [Read more here!](https://github.com/gottyduke/SF_PluginTemplate/wiki/Custom-deployment-rules)  

## 🏅 Credits

- [ianpatt's starfield script extender](https://github.com/ianpatt/sfse).
- [CommonLibSF, a collaborative effort project](https://github.com/Starfield-Reverse-Engineering/CommonLibSF)
