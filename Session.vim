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
badd +184 NimbleIDE/src/main.cpp
badd +19 NimbleLIB/inc/Modules/Curses/CursesColour.h
badd +69 NimbleLIB/inc/Modules/Curses/CursesKeyboard.h
badd +47 NimbleLIB/inc/Modules/Curses/CursesMenu.h
badd +44 NimbleLIB/inc/Modules/Curses/CursesWin.h
badd +10 NimbleLIB/inc/Modules/ErrorHandling/ErrorHandler.h
badd +39 NimbleLIB/inc/Modules/ErrorHandling/Errors.h
badd +8 NimbleLIB/inc/Modules/FileHandling/FileManager.h
badd +10 NimbleLIB/inc/Modules/Framework/CFrameworkObject.hpp
badd +30 NimbleLIB/inc/Modules/Global/Globals.h
badd +82 NimbleLIB/inc/Modules/IDE/IDEDialog.h
badd +47 NimbleLIB/inc/Modules/IDE/IDEEditBox.h
badd +10 NimbleLIB/inc/Modules/IDE/IDEEditline.h
badd +26 NimbleLIB/inc/Modules/IDE/IDEEditor.h
badd +115 NimbleLIB/inc/Modules/IDE/IDEFileHandler.h
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
badd +154 NimbleLIB/src/Modules/Curses/CursesKeyboard.cpp
badd +295 NimbleLIB/src/Modules/Curses/CursesMenu.cpp
badd +419 NimbleLIB/src/Modules/Curses/CursesWin.cpp
badd +240 NimbleLIB/src/Modules/ErrorHandling/ErrorHandler.cpp
badd +21 NimbleLIB/src/Modules/FileHandling/FileManager.cpp
badd +36 NimbleLIB/src/Modules/Global/Globals.cpp
badd +165 NimbleLIB/src/Modules/IDE/IDEDialog.cpp
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
badd +1 NimbleUtils/NimbleCalc/src/main.cpp
badd +9 NimbleUtils/NimbleMenu/inc/Modules/MenuConfig.h
badd +1 NimbleUtils/NimbleMenu/src/Modules/MenuConfig.cpp
badd +28 NimbleUtils/NimbleMenu/src/main.cpp
badd +1 TestNimbleIDE/src/unitTests.cpp
badd +1 TestNimbleLIB/inc/unitTests_ErrorHandler.h
badd +1 TestNimbleLIB/inc/unitTests_IDEEdit.h
badd +23 TestNimbleLIB/inc/unitTests_Screen.h
badd +23 TestNimbleLIB/src/unitTests.cpp
badd +65 NimbleLIB/inc/Modules/IDE/IDEFileDialog.h
badd +212 NimbleLIB/src/Modules/IDE/IDEFileDialog.cpp
badd +9 CMakeLists.txt
badd +1 NimbleLIB/CMakeLists.txt
badd +2 NimbleIDE/CMakeLists.txt
badd +2 NimbleUtils/NimbleCalc/CMakeLists.txt
badd +2 NimbleUtils/NimbleMenu/CMakeLists.txt
badd +6 TestNimbleIDE/CMakeLists.txt
badd +8 TestNimbleLIB/CMakeLists.txt
badd +62 NimbleLIB/inc/Modules/IDE/IDEButton.h
badd +653 ExternalLibraries/PDCurses/curses.h
badd +1 NimbleLIB/src/Modules/Curses/CursesMouse.cpp
badd +41 NimbleLIB/inc/Modules/Curses/CursesMouse.h
badd +69 NimbleLIB/inc/Modules/IDE/IDEWindow.h
badd +12 NimbleLIB/src/Modules/IDE/IDEWindow.cpp
badd +71 NimbleLIB/inc/Modules/Editor/EditorStatusWin.h
badd +93 NimbleLIB/src/Modules/Editor/EditorStatusWin.cpp
badd +27 NimbleLIB/inc/Modules/Editor/EditorProjectWin.h
badd +33 NimbleLIB/src/Modules/Editor/EditorProjectWin.cpp
badd +72 NimbleLIB/src/Modules/Editor/EditorTitleWin.cpp
badd +65 NimbleLIB/inc/Modules/Editor/EditorTitleWin.h
badd +39 NimbleLIB/inc/Modules/Editor/EditorHexWin.h
badd +83 NimbleLIB/src/Modules/Editor/EditorHexWin.cpp
badd +1 NimbleLIB/src/Modules/Editor/EditorLineNumbersWin.cpp
badd +56 NimbleLIB/inc/Modules/Editor/EditorLineNumbersWin.h
badd +172 NimbleLIB/src/Modules/IDE/IDEButton.cpp
badd +2147 C:/Program\ Files/Microsoft\ Visual\ Studio/2022/Community/VC/Tools/MSVC/14.38.33130/include/functional
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
exe '1resize ' . ((&lines * 112 + 60) / 120)
exe 'vert 1resize ' . ((&columns * 213 + 211) / 423)
exe '2resize ' . ((&lines * 112 + 60) / 120)
exe 'vert 2resize ' . ((&columns * 209 + 211) / 423)
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
let s:l = 104 - ((74 * winheight(0) + 56) / 112)
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
let s:l = 53 - ((52 * winheight(0) + 56) / 112)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 53
normal! 08|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
exe '1resize ' . ((&lines * 112 + 60) / 120)
exe 'vert 1resize ' . ((&columns * 213 + 211) / 423)
exe '2resize ' . ((&lines * 112 + 60) / 120)
exe 'vert 2resize ' . ((&columns * 209 + 211) / 423)
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
exe 'vert 1resize ' . ((&columns * 210 + 211) / 423)
exe 'vert 2resize ' . ((&columns * 212 + 211) / 423)
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
let s:l = 102 - ((100 * winheight(0) + 59) / 118)
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
let s:l = 56 - ((55 * winheight(0) + 59) / 118)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 56
normal! 027|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 210 + 211) / 423)
exe 'vert 2resize ' . ((&columns * 212 + 211) / 423)
tabnext
edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEFileDialog.cpp
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
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/ExternalLibraries/PDCurses/curses.h
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
98
normal! zo
107
normal! zo
112
normal! zo
123
normal! zo
180
normal! zo
182
normal! zo
185
normal! zo
200
normal! zo
202
normal! zo
209
normal! zo
231
normal! zo
233
normal! zo
302
normal! zo
313
normal! zo
332
normal! zo
332
normal! zo
334
normal! zo
let s:l = 83 - ((60 * winheight(0) + 59) / 118)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 83
normal! 01|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
argglobal
if bufexists(fnamemodify("D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEDialog.cpp", ":p")) | buffer D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEDialog.cpp | else | edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEDialog.cpp | endif
if &buftype ==# 'terminal'
  silent file D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEDialog.cpp
endif
balt C:/Program\ Files/Microsoft\ Visual\ Studio/2022/Community/VC/Tools/MSVC/14.38.33130/include/functional
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
96
normal! zo
144
normal! zo
147
normal! zo
218
normal! zo
222
normal! zo
248
normal! zo
252
normal! zo
274
normal! zo
277
normal! zo
let s:l = 165 - ((38 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 165
normal! 05|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
argglobal
if bufexists(fnamemodify("D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEDialog.h", ":p")) | buffer D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEDialog.h | else | edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEDialog.h | endif
if &buftype ==# 'terminal'
  silent file D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEDialog.h
endif
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEDialog.cpp
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
45
normal! zo
let s:l = 82 - ((45 * winheight(0) + 29) / 59)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 82
normal! 0
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
argglobal
if bufexists(fnamemodify("D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEButton.h", ":p")) | buffer D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEButton.h | else | edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEButton.h | endif
if &buftype ==# 'terminal'
  silent file D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEButton.h
endif
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEDialog.h
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
41
normal! zo
let s:l = 36 - ((9 * winheight(0) + 29) / 59)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 36
normal! 044|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
2wincmd w
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
