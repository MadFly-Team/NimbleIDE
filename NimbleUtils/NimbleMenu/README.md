# NimbleMenu

##### Found in NimbleUtils directory

<img src="../Content/NimbleMenu1.png">

This utility allows quick selection of actions from a menu.
Setup to allow for easy integration into other applications.
The menu is a simple list of options, with a title and a prompt.
The options are numbered in a configuration file that is loaded from
the current directory where `NimbleMunu.exe` is ran.
Configuration file is called `NimbleMenu.cfg`
Items are numbered from 0 to 9, and are displayed in the order they are in the file.
Each item has a title and a command to run.
Please note 'cd' commands are supported, 'cd' is stripped and also the '\n' is stripped.
Each command is separated by either of the following:
* ` & ` - run the command and continue
* ` && ` - runs the next command if no errors are reported by the previous command

The following is a working example of the configuration file - called `NimbeMenu.cfg`.

```
// Nimble Menu Items -
Items = 9
1^Directory - NimbleIDE^cd D:\NewProjects\Utilities\NimbleIDE\Trunk
2^Directory - USBConsoleSuit^cd D:\NewProjects\Utilities\USBHIDConsoleSuite\Trunk
3^Clean-Build Project^cd build && rmdir -f . & cmake .. && cmake --build .
4^Build & Run NimbleIDE^ cmake --build build --target NimbleIDE && cd build\NimbleIDE\Debug\ && .\NimbleIDE.exe
5^Build & Run NimbleMenu^ cmake --build build --target NimbleMenu && cd build\NimbleUtils\NimbleMENU\Debug\ && .\NimbleMENU.exe
6^Build & Run TestNimbleLIB^ cmake --build build --target TestNimbleLIB && cd build\TestNimbleLIB\Debug\ && .\TestNimbleLIB.exe && timeout /t 10
7^Explorer at this location^explorer .
8^Far Manager at this location^"c:\Program Files\Far Manager\Far.exe" .
9^Lazygit at this location^lazygit.exe
```

