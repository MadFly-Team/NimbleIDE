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
badd +80 NimbleLIB/inc/Modules/IDE/IDEEditline.h
badd +22 NimbleLIB/src/Modules/IDE/IDEEditline.cpp
badd +91 NimbleLIB/inc/Modules/ErrorHandling/Errors.h
badd +101 NimbleLIB/inc/Modules/ErrorHandling/ErrorHandler.h
badd +1 D:/NewProjects/Utilities/NimbleIDE/Trunk
badd +97 NimbleLIB/inc/Modules/IDE/IDEFileHandler.h
badd +185 NimbleLIB/src/Modules/IDE/IDEFileHandler.cpp
badd +135 NimbleLIB/src/Modules/IDE/IDEEditor.cpp
badd +71 NimbleLIB/inc/Modules/IDE/IDEEditor.h
badd +146 NimbleIDE/src/main.cpp
badd +36 NimbleLIB/inc/Modules/IDE/IDEEditBox.h
badd +1 NimbleLIB/src/Modules/IDE/IDEEditBox.cpp
badd +39 NimbleLIB/inc/NimbleLib.h
argglobal
%argdel
$argadd D:/NewProjects/Utilities/NimbleIDE/Trunk
edit NimbleLIB/src/Modules/IDE/IDEEditBox.cpp
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
balt NimbleLIB/inc/Modules/IDE/IDEEditBox.h
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal nofen
let s:l = 145 - ((54 * winheight(0) + 41) / 83)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 145
normal! 032|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
argglobal
if bufexists(fnamemodify("D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEEditor.h", ":p")) | buffer D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEEditor.h | else | edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEEditor.h | endif
if &buftype ==# 'terminal'
  silent file D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/Modules/IDE/IDEEditor.h
endif
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleIDE/src/main.cpp
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 71 - ((30 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 71
normal! 028|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
argglobal
if bufexists(fnamemodify("D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEEditor.cpp", ":p")) | buffer D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEEditor.cpp | else | edit D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEEditor.cpp | endif
if &buftype ==# 'terminal'
  silent file D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/src/Modules/IDE/IDEEditor.cpp
endif
balt D:/NewProjects/Utilities/NimbleIDE/Trunk/NimbleLIB/inc/NimbleLib.h
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=20
setlocal fen
68
normal! zo
97
normal! zo
104
normal! zo
122
normal! zo
145
normal! zo
148
normal! zo
150
normal! zo
152
normal! zo
161
normal! zo
151
normal! zo
153
normal! zo
155
normal! zo
157
normal! zo
166
normal! zo
let s:l = 135 - ((17 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 135
normal! 05|
lcd D:/NewProjects/Utilities/NimbleIDE/Trunk
wincmd w
3wincmd w
wincmd =
tabnext 1
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
