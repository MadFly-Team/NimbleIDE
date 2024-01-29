let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
let VM_case_setting = ""
let VM_disable_syntax_in_imode =  0 
let VM_check_mappings =  1 
let VM_mouse_mappings =  0 
let VM_debug =  0 
let VM_default_mappings =  1 
let VM_persistent_registers =  0 
let VM_live_editing =  1 
let NetrwTopLvlMenu = "Netrw."
let VM_use_python =  0 
let VM_reselect_first =  0 
let VM_highlight_matches = "underline"
let NetrwMenuPriority =  80 
let VM_use_first_cursor_in_line =  0 
silent only
silent tabonly
cd D:/NewProjects/Utilities/NimbleIDE/Trunk
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +161 NimbleIDE/src/main.cpp
badd +19 NimbleLIB/inc/Modules/Curses/CursesColour.h
badd +85 NimbleLIB/inc/Modules/Curses/CursesKeyboard.h
badd +47 NimbleLIB/inc/Modules/Curses/CursesMenu.h
badd +74 NimbleLIB/inc/Modules/Curses/CursesWin.h
badd +10 NimbleLIB/inc/Modules/ErrorHandling/ErrorHandler.h
badd +107 NimbleLIB/inc/Modules/ErrorHandling/Errors.h
badd +8 NimbleLIB/inc/Modules/FileHandling/FileManager.h
badd +10 NimbleLIB/inc/Modules/Framework/CFrameworkObject.hpp
badd +30 NimbleLIB/inc/Modules/Global/Globals.h
badd +40 NimbleLIB/inc/Modules/IDE/IDEDialog.h
badd +47 NimbleLIB/inc/Modules/IDE/IDEEditBox.h
badd +10 NimbleLIB/inc/Modules/IDE/IDEEditline.h
badd +94 NimbleLIB/inc/Modules/IDE/IDEEditor.h
badd +72 NimbleLIB/inc/Modules/IDE/IDEFileHandler.h
badd +9 NimbleLIB/inc/Modules/Logging/Logger.h
badd +9 NimbleLIB/inc/Modules/Screen/ScreenBox.h
badd +9 NimbleLIB/inc/Modules/Screen/ScreenControl.h
badd +9 NimbleLIB/inc/Modules/Screen/ScreenInfo.h
badd +9 NimbleLIB/inc/Modules/Screen/ScreenPrint.h
badd +9 NimbleLIB/inc/Modules/Screen/ScreenWord.h
badd +57 NimbleLIB/inc/Modules/Utilities/StatusCtrl.h
badd +10 NimbleLIB/inc/Modules/Utilities/Tools.h
badd +40 NimbleLIB/inc/NimbleLib.h
badd +9 NimbleLIB/src/Modules/Curses/CursesColour.cpp
badd +208 NimbleLIB/src/Modules/Curses/CursesKeyboard.cpp
badd +295 NimbleLIB/src/Modules/Curses/CursesMenu.cpp
badd +320 NimbleLIB/src/Modules/Curses/CursesWin.cpp
badd +240 NimbleLIB/src/Modules/ErrorHandling/ErrorHandler.cpp
badd +21 NimbleLIB/src/Modules/FileHandling/FileManager.cpp
badd +36 NimbleLIB/src/Modules/Global/Globals.cpp
badd +218 NimbleLIB/src/Modules/IDE/IDEDialog.cpp
badd +216 NimbleLIB/src/Modules/IDE/IDEEditBox.cpp
badd +227 NimbleLIB/src/Modules/IDE/IDEEditline.cpp
badd +480 NimbleLIB/src/Modules/IDE/IDEEditor.cpp
badd +83 NimbleLIB/src/Modules/IDE/IDEFileHandler.cpp
badd +117 NimbleLIB/src/Modules/Logging/Logger.cpp
badd +169 NimbleLIB/src/Modules/Screen/ScreenBox.cpp
badd +139 NimbleLIB/src/Modules/Screen/ScreenControl.cpp
badd +132 NimbleLIB/src/Modules/Screen/ScreenInfo.cpp
badd +175 NimbleLIB/src/Modules/Screen/ScreenPrint.cpp
badd +2 NimbleLIB/src/Modules/Screen/ScreenWord.cpp
badd +265 NimbleLIB/src/Modules/Utilities/StatusCtrl.cpp
badd +90 NimbleLIB/src/Modules/Utilities/Tools.cpp
badd +1 NimbleUtils/NimbleCalc/src/main.cpp
badd +9 NimbleUtils/NimbleMenu/inc/Modules/MenuConfig.h
badd +1 NimbleUtils/NimbleMenu/src/Modules/MenuConfig.cpp
badd +28 NimbleUtils/NimbleMenu/src/main.cpp
badd +1 TestNimbleIDE/src/unitTests.cpp
badd +1 TestNimbleLIB/inc/unitTests_ErrorHandler.h
badd +1 TestNimbleLIB/inc/unitTests_IDEEdit.h
badd +23 TestNimbleLIB/inc/unitTests_Screen.h
badd +23 TestNimbleLIB/src/unitTests.cpp
badd +42 NimbleLIB/inc/Modules/IDE/IDEFileDialog.h
badd +27 NimbleLIB/src/Modules/IDE/IDEFileDialog.cpp
badd +9 CMakeLists.txt
badd +1 NimbleLIB/CMakeLists.txt
badd +2 NimbleIDE/CMakeLists.txt
badd +2 NimbleUtils/NimbleCalc/CMakeLists.txt
badd +2 NimbleUtils/NimbleMenu/CMakeLists.txt
badd +6 TestNimbleIDE/CMakeLists.txt
badd +8 TestNimbleLIB/CMakeLists.txt
badd +56 NimbleLIB/inc/Modules/IDE/IDEButton.h
badd +948 ExternalLibraries/PDCurses/curses.h
badd +1 NimbleLIB/src/Modules/Curses/CursesMouse.cpp
badd +82 NimbleLIB/inc/Modules/Curses/CursesMouse.h
badd +69 NimbleLIB/inc/Modules/IDE/IDEWindow.h
badd +12 NimbleLIB/src/Modules/IDE/IDEWindow.cpp
badd +81 NimbleLIB/inc/Modules/Editor/EditorStatusWin.h
badd +52 NimbleLIB/src/Modules/Editor/EditorStatusWin.cpp
badd +30 NimbleLIB/inc/Modules/Editor/EditorProjectWin.h
badd +21 NimbleLIB/src/Modules/Editor/EditorProjectWin.cpp
badd +114 NimbleLIB/src/Modules/Editor/EditorTitleWin.cpp
badd +65 NimbleLIB/inc/Modules/Editor/EditorTitleWin.h
badd +75 NimbleLIB/inc/Modules/Editor/EditorHexWin.h
badd +84 NimbleLIB/src/Modules/Editor/EditorHexWin.cpp
badd +1 NimbleLIB/src/Modules/Editor/EditorLineNumbersWin.cpp
badd +56 NimbleLIB/inc/Modules/Editor/EditorLineNumbersWin.h
badd +141 NimbleLIB/src/Modules/IDE/IDEButton.cpp
argglobal
%argdel
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit NimbleLIB/src/Modules/Curses/CursesMouse.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 69 + 37) / 74)
exe 'vert 1resize ' . ((&columns * 146 + 145) / 291)
exe '2resize ' . ((&lines * 69 + 37) / 74)
exe 'vert 2resize ' . ((&columns * 144 + 145) / 291)
argglobal
balt NimbleLIB/src/Modules/IDE/IDEEditor.cpp
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
73
normal! zo
77
normal! zo
98
normal! zo
let s:l = 104 - ((46 * winheight(0) + 34) / 69)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 104
normal! 027|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
argglobal
if bufexists(fnamemodify("D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/Curses/CursesMouse.h", ":p")) | buffer D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/Curses/CursesMouse.h | else | edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/Curses/CursesMouse.h | endif
if &buftype ==# 'terminal'
  silent file D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/Curses/CursesMouse.h
endif
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEEditor.cpp
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 53 - ((36 * winheight(0) + 34) / 69)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 53
normal! 08|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
exe '1resize ' . ((&lines * 69 + 37) / 74)
exe 'vert 1resize ' . ((&columns * 146 + 145) / 291)
exe '2resize ' . ((&lines * 69 + 37) / 74)
exe 'vert 2resize ' . ((&columns * 144 + 145) / 291)
tabnext
edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEButton.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
wincmd =
argglobal
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/ExternalLibraries/PDCurses/curses.h
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
103
normal! zo
107
normal! zo
111
normal! zo
130
normal! zo
137
normal! zo
let s:l = 141 - ((55 * winheight(0) + 36) / 72)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 141
normal! 0
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
argglobal
if bufexists(fnamemodify("D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/ErrorHandling/Errors.h", ":p")) | buffer D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/ErrorHandling/Errors.h | else | edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/ErrorHandling/Errors.h | endif
if &buftype ==# 'terminal'
  silent file D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/ErrorHandling/Errors.h
endif
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEButton.h
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 105 - ((64 * winheight(0) + 36) / 72)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 105
normal! 02|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
wincmd =
tabnext
edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/Editor/EditorLineNumbersWin.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
wincmd =
argglobal
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/Editor/EditorStatusWin.cpp
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
61
normal! zo
78
normal! zo
107
normal! zo
let s:l = 102 - ((67 * winheight(0) + 36) / 72)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 102
normal! 054|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
argglobal
if bufexists(fnamemodify("D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/Editor/EditorLineNumbersWin.h", ":p")) | buffer D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/Editor/EditorLineNumbersWin.h | else | edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/Editor/EditorLineNumbersWin.h | endif
if &buftype ==# 'terminal'
  silent file D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/Editor/EditorLineNumbersWin.h
endif
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEEditBox.cpp
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 56 - ((53 * winheight(0) + 36) / 72)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 56
normal! 027|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
wincmd =
tabnext 2
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
