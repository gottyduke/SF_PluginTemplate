Copy-Item C:/cmake_bin/* D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/ -Force -ErrorAction:SilentlyContinue
Copy-Item D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.dll C:/Starfield/Data/SFSE/Plugins/ -Force -ErrorAction:SilentlyContinue
if (Test-Path D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.pdb)
{ Copy-Item D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.pdb C:/Starfield/Data/SFSE/Plugins/ -Force -ErrorAction:SilentlyContinue }
if (Test-Path D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.ini)
{ Copy-Item D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.ini C:/Starfield/Data/SFSE/Plugins/ -Force -ErrorAction:SilentlyContinue }
if (Test-Path D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.toml)
{ Copy-Item D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.toml C:/Starfield/Data/SFSE/Plugins/ -Force -ErrorAction:SilentlyContinue }
if (Test-Path D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.json)
{ Copy-Item D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.json C:/Starfield/Data/SFSE/Plugins/ -Force -ErrorAction:SilentlyContinue }
Compress-Archive -Path D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.toml,D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.dll,D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/*.pdb -DestinationPath D:/WorkSpace/BG3Plugins/PluginTemplate/PluginTemplate/dist/ExampleMod.v1.0.1.zip -Force -ErrorAction:SilentlyContinue
