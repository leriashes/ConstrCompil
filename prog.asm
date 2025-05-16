_BSS SEGMENT
PUBLIC var_pos@0x1ce3f316ff0 ; var_pos
PUBLIC var_pos2@0x1ce3f317bc0 ; var_pos2
PUBLIC var_tpos@0x1ce3f31bcc0 ; var_tpos
PUBLIC var_boss@0x1ce3f31a880 ; var_boss
PUBLIC s@0x1ce3f31aa30 ; s
PUBLIC t@0x1ce3f31e1e0 ; t
PUBLIC y@0x1ce3f31f620 ; y
PUBLIC bla@0x1ce3f31e390 ; bla
PUBLIC bg@0x1ce3f31e030 ; bg
PUBLIC g@0x1ce3f31e540 ; g
PUBLIC var_gra@0x1ce3f31ea50 ; var_gra
PUBLIC a@0x1ce3f31f2c0 ; a
PUBLIC my_pos@0x1ce3f31ec00 ; my_pos
PUBLIC func@0x1ce3f322510 ; func

var_pos@0x1ce3f316ff0 DB 011H DUP(?) ; var_pos
var_pos2@0x1ce3f317bc0 DB 011H DUP(?) ; var_pos2
var_tpos@0x1ce3f31bcc0 DB 01H DUP(?) ; var_tpos
var_boss@0x1ce3f31a880 DB 011H DUP(?) ; var_boss
s@0x1ce3f31aa30 DB 01H DUP(?) ; s
t@0x1ce3f31e1e0 DB 01H DUP(?) ; t
y@0x1ce3f31f620 DB 01H DUP(?) ; y
bla@0x1ce3f31e390 DQ 01H DUP(?) ; bla
bg@0x1ce3f31e030 DQ 01H DUP(?) ; bg
g@0x1ce3f31e540 DQ 01H DUP(?) ; g
var_gra@0x1ce3f31ea50 DB 01H DUP(?) ; var_gra
a@0x1ce3f31f2c0 DB 01H DUP(?) ; a


_TEXT SEGMENT
_xy$ = -24        ; size = 17
my_pos@0x1ce3f31ec00 PROC
mov eax, 2
add eax, 4
mov eax, 1
imul 7
sub eax, ebx
sub eax, 34
my_pos@0x1ce3f31ec00 ENDP
_TEXT ENDS

_TEXT SEGMENT
_u$ = -80        ; size = 1
_nb$ = -72        ; size = 8
_nas$ = -64        ; size = 1
_tas$ = -63        ; size = 1
_a$ = -56        ; size = 8
_r$2 = -48        ; size = 1
_cl$2 = -40        ; size = 17
_rt$2 = -16        ; size = 8
_k$2 = -8        ; size = 1
func@0x1ce3f322510 PROC
mov eax, 2
add eax, 4
mov eax, 1
imul 7
sub eax, ebx
sub eax, 34
func@0x1ce3f322510 ENDP
_TEXT ENDS
