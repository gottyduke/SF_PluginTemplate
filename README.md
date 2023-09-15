# 📑 SFSE Plugin Template
Native dll plugin for [starfield script extender](https://github.com/ianpatt/sfse).

[Create a new plugin project from this template](https://github.com/new?template_name=SF_PluginTemplate&template_owner=gottyduke) and wait for the first workflow action to finish, it will setup project automatically.

## ⚙ Requirements

- [CMake 3.26+](https://cmake.org/)
  - Add this to your `PATH`
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

- [CommonLibSF](https://github.com/Starfield-Reverse-Engineering/CommonLibSF)
- [DKUtil](https://github.com/gottyduke/DKUtil)

These two dependencies can be setup either via git submodule (by executing `update-submodule.bat`) or through a local git repo (by specifying environment variable `CommonLibSFPath` and `DKUtilPath` pointing to local git repo path).

> If having multiple projects, to avoid having copies of CommonLibSF and DKUtil in each of them, it's suggested to use the local fork and environment path approach, so all projects share the same package.

```
.\make-sln-msvc.bat
cmake --build build
```

### 📦 Deployment

This plugin template has auto deployment rules for easier build-and-test, build-and-package features, using simple json rules. [Read more here!](https://github.com/gottyduke/SF_PluginTemplate/wiki/Custom-deployment-rules)

### ➕ DKUtil addon

This project bundles [DKUtil](https://github.com/gottyduke/DKUtil).

## 📖 License

[GPL-3.0-or-later](COPYING) WITH [Modding Exception AND GPL-3.0 Linking Exception (with Corresponding Source)](EXCEPTIONS). Specifically, the Modded Code is Starfield (and its variants) and Modding Libraries include [Starfield Script Extender](https://github.com/ianpatt/sfse) and [DKUtil](https://github.com/gottyduke/DKUtil/) (and variants).

## ❓ Credits

- [ianpatt's starfield script extender](https://github.com/ianpatt/sfse).
- [CommonLibSF, a collaborative effort project](https://github.com/Starfield-Reverse-Engineering/CommonLibSF)
