_BSS SEGMENT
PUBLIC var_pos@0x27570a07060 ; var_pos
PUBLIC var_pos2@0x27570a07a80 ; var_pos2
PUBLIC var_tpos@0x27570a0b160 ; var_tpos
PUBLIC var_boss@0x27570a0a740 ; var_boss
PUBLIC s@0x27570a0a590 ; s
PUBLIC t@0x27570a0eac0 ; t
PUBLIC y@0x27570a0e910 ; y
PUBLIC bla@0x27570a0e0a0 ; bla
PUBLIC bg@0x27570a0f4e0 ; bg
PUBLIC g@0x27570a0f690 ; g
PUBLIC var_gra@0x27570a0f840 ; var_gra
PUBLIC a@0x27570a0e760 ; a
PUBLIC my_pos@0x27570a0def0 ; my_pos
PUBLIC func@0x27570a13150 ; func

var_pos@0x27570a07060 DB 011H DUP(?) ; var_pos
var_pos2@0x27570a07a80 DB 011H DUP(?) ; var_pos2
var_tpos@0x27570a0b160 DB 01H DUP(?) ; var_tpos
var_boss@0x27570a0a740 DB 011H DUP(?) ; var_boss
s@0x27570a0a590 DB 01H DUP(?) ; s
t@0x27570a0eac0 DB 01H DUP(?) ; t
y@0x27570a0e910 DB 01H DUP(?) ; y
bla@0x27570a0e0a0 DQ 01H DUP(?) ; bla
bg@0x27570a0f4e0 DQ 01H DUP(?) ; bg
g@0x27570a0f690 DQ 01H DUP(?) ; g
var_gra@0x27570a0f840 DB 01H DUP(?) ; var_gra
a@0x27570a0e760 DB 01H DUP(?) ; a


_TEXT SEGMENT
_xy$ = -24        ; size = 17
my_pos@0x27570a0def0 PROC
my_pos@0x27570a0def0 ENDP
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
func@0x27570a13150 PROC
mov eax, 2
add eax, 4
mov eax, 1
imul 7
sub eax, ebx
sub eax, 34
mov eax, [a@0x27570a0e760]
add eax, 5
mov eax, BYTE PTR _nas$[ebp - 64]
sub eax, 2
func@0x27570a13150 ENDP
_TEXT ENDS
