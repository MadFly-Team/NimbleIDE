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
badd +153 NimbleIDE/src/main.cpp
badd +19 NimbleLIB/inc/Modules/Curses/CursesColour.h
badd +69 NimbleLIB/inc/Modules/Curses/CursesKeyboard.h
badd +47 NimbleLIB/inc/Modules/Curses/CursesMenu.h
badd +44 NimbleLIB/inc/Modules/Curses/CursesWin.h
badd +10 NimbleLIB/inc/Modules/ErrorHandling/ErrorHandler.h
badd +39 NimbleLIB/inc/Modules/ErrorHandling/Errors.h
badd +36 NimbleLIB/inc/Modules/FileHandling/FileManager.h
badd +10 NimbleLIB/inc/Modules/Framework/CFrameworkObject.hpp
badd +30 NimbleLIB/inc/Modules/Global/Globals.h
badd +64 NimbleLIB/inc/Modules/IDE/IDEDialog.h
badd +39 NimbleLIB/inc/Modules/IDE/IDEEditBox.h
badd +42 NimbleLIB/inc/Modules/IDE/IDEEditline.h
badd +26 NimbleLIB/inc/Modules/IDE/IDEEditor.h
badd +53 NimbleLIB/inc/Modules/IDE/IDEFileHandler.h
badd +9 NimbleLIB/inc/Modules/Logging/Logger.h
badd +9 NimbleLIB/inc/Modules/Screen/ScreenBox.h
badd +9 NimbleLIB/inc/Modules/Screen/ScreenControl.h
badd +9 NimbleLIB/inc/Modules/Screen/ScreenInfo.h
badd +9 NimbleLIB/inc/Modules/Screen/ScreenPrint.h
badd +9 NimbleLIB/inc/Modules/Screen/ScreenWord.h
badd +57 NimbleLIB/inc/Modules/Utilities/StatusCtrl.h
badd +10 NimbleLIB/inc/Modules/Utilities/Tools.h
badd +37 NimbleLIB/inc/NimbleLib.h
badd +9 NimbleLIB/src/Modules/Curses/CursesColour.cpp
badd +154 NimbleLIB/src/Modules/Curses/CursesKeyboard.cpp
badd +295 NimbleLIB/src/Modules/Curses/CursesMenu.cpp
badd +419 NimbleLIB/src/Modules/Curses/CursesWin.cpp
badd +240 NimbleLIB/src/Modules/ErrorHandling/ErrorHandler.cpp
badd +21 NimbleLIB/src/Modules/FileHandling/FileManager.cpp
badd +36 NimbleLIB/src/Modules/Global/Globals.cpp
badd +210 NimbleLIB/src/Modules/IDE/IDEDialog.cpp
badd +216 NimbleLIB/src/Modules/IDE/IDEEditBox.cpp
badd +227 NimbleLIB/src/Modules/IDE/IDEEditline.cpp
badd +42 NimbleLIB/src/Modules/IDE/IDEEditor.cpp
badd +91 NimbleLIB/src/Modules/IDE/IDEFileHandler.cpp
badd +117 NimbleLIB/src/Modules/Logging/Logger.cpp
badd +169 NimbleLIB/src/Modules/Screen/ScreenBox.cpp
badd +139 NimbleLIB/src/Modules/Screen/ScreenControl.cpp
badd +132 NimbleLIB/src/Modules/Screen/ScreenInfo.cpp
badd +175 NimbleLIB/src/Modules/Screen/ScreenPrint.cpp
badd +2 NimbleLIB/src/Modules/Screen/ScreenWord.cpp
badd +265 NimbleLIB/src/Modules/Utilities/StatusCtrl.cpp
badd +90 NimbleLIB/src/Modules/Utilities/Tools.cpp
badd +86 NimbleUtils/NimbleCalc/src/main.cpp
badd +9 NimbleUtils/NimbleMenu/inc/Modules/MenuConfig.h
badd +1 NimbleUtils/NimbleMenu/src/Modules/MenuConfig.cpp
badd +111 NimbleUtils/NimbleMenu/src/main.cpp
badd +1 TestNimbleIDE/src/unitTests.cpp
badd +1 TestNimbleLIB/inc/unitTests_ErrorHandler.h
badd +1 TestNimbleLIB/inc/unitTests_IDEEdit.h
badd +23 TestNimbleLIB/inc/unitTests_Screen.h
badd +23 TestNimbleLIB/src/unitTests.cpp
badd +38 NimbleLIB/inc/Modules/IDE/IDEFileDialog.h
badd +165 NimbleLIB/src/Modules/IDE/IDEFileDialog.cpp
badd +9 CMakeLists.txt
badd +1 NimbleLIB/CMakeLists.txt
badd +2 NimbleIDE/CMakeLists.txt
badd +2 NimbleUtils/NimbleCalc/CMakeLists.txt
badd +2 NimbleUtils/NimbleMenu/CMakeLists.txt
badd +6 TestNimbleIDE/CMakeLists.txt
badd +8 TestNimbleLIB/CMakeLists.txt
badd +41 NimbleLIB/inc/Modules/IDE/IDEButton.h
badd +34 ExternalLibraries/PDCurses/curses.h
badd +76 NimbleLIB/src/Modules/Curses/CursesMouse.cpp
badd +41 NimbleLIB/inc/Modules/Curses/CursesMouse.h
badd +62 NimbleLIB/inc/Modules/IDE/IDEWindow.h
badd +12 NimbleLIB/src/Modules/IDE/IDEWindow.cpp
badd +71 NimbleLIB/inc/Modules/Editor/EditorStatusWin.h
badd +76 NimbleLIB/src/Modules/Editor/EditorStatusWin.cpp
badd +27 NimbleLIB/inc/Modules/Editor/EditorProjectWin.h
badd +33 NimbleLIB/src/Modules/Editor/EditorProjectWin.cpp
badd +72 NimbleLIB/src/Modules/Editor/EditorTitleWin.cpp
badd +65 NimbleLIB/inc/Modules/Editor/EditorTitleWin.h
badd +39 NimbleLIB/inc/Modules/Editor/EditorHexWin.h
badd +83 NimbleLIB/src/Modules/Editor/EditorHexWin.cpp
badd +1 NimbleLIB/src/Modules/Editor/EditorLineNumbersWin.cpp
badd +56 NimbleLIB/inc/Modules/Editor/EditorLineNumbersWin.h
badd +67 NimbleLIB/src/Modules/IDE/IDEButton.cpp
badd +2147 C:/Program\ Files/Microsoft\ Visual\ Studio/2022/Community/VC/Tools/MSVC/14.38.33130/include/functional
badd +96 NimbleLIB/inc/Modules/IDE/IDEManager.h
badd +109 NimbleLIB/src/Modules/IDE/IDEManager.cpp
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
exe '1resize ' . ((&lines * 71 + 38) / 76)
exe 'vert 1resize ' . ((&columns * 146 + 145) / 291)
exe '2resize ' . ((&lines * 71 + 38) / 76)
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
72
normal! zo
76
normal! zo
97
normal! zo
let s:l = 103 - ((45 * winheight(0) + 35) / 71)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 103
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
let s:l = 53 - ((33 * winheight(0) + 35) / 71)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 53
normal! 08|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
exe '1resize ' . ((&lines * 71 + 38) / 76)
exe 'vert 1resize ' . ((&columns * 146 + 145) / 291)
exe '2resize ' . ((&lines * 71 + 38) / 76)
exe 'vert 2resize ' . ((&columns * 144 + 145) / 291)
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
exe 'vert 1resize ' . ((&columns * 144 + 145) / 291)
exe 'vert 2resize ' . ((&columns * 146 + 145) / 291)
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
83
normal! zo
107
normal! zo
112
normal! zo
let s:l = 102 - ((63 * winheight(0) + 37) / 74)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 102
normal! 0
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
let s:l = 56 - ((35 * winheight(0) + 37) / 74)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 56
normal! 027|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 144 + 145) / 291)
exe 'vert 2resize ' . ((&columns * 146 + 145) / 291)
tabnext
edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleIDE/src/main.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
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
88
normal! zo
132
normal! zo
239
normal! zo
let s:l = 153 - ((22 * winheight(0) + 37) / 74)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 153
normal! 013|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
argglobal
if bufexists(fnamemodify("D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEManager.h", ":p")) | buffer D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEManager.h | else | edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEManager.h | endif
if &buftype ==# 'terminal'
  silent file D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEManager.h
endif
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/FileHandling/FileManager.h
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
83
normal! zo
104
normal! zo
let s:l = 109 - ((4 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 109
normal! 0112|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
argglobal
if bufexists(fnamemodify("D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEDialog.cpp", ":p")) | buffer D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEDialog.cpp | else | edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEDialog.cpp | endif
if &buftype ==# 'terminal'
  silent file D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEDialog.cpp
endif
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEManager.cpp
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
147
normal! zo
let s:l = 328 - ((31 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 328
normal! 043|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
argglobal
if bufexists(fnamemodify("D:/NewProjects/Utilities/NimbleIDE/Trunk/ExternalLibraries/PDCurses/curses.h", ":p")) | buffer D:/NewProjects/Utilities/NimbleIDE/Trunk/ExternalLibraries/PDCurses/curses.h | else | edit D:/NewProjects/Utilities/NimbleIDE/Trunk/ExternalLibraries/PDCurses/curses.h | endif
if &buftype ==# 'terminal'
  silent file D:/NewProjects/Utilities/NimbleIDE/Trunk/ExternalLibraries/PDCurses/curses.h
endif
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/Curses/CursesMouse.cpp
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
148
normal! zo
let s:l = 34 - ((5 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 34
normal! 0
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
wincmd =
tabnext 3
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
