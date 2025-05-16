_BSS SEGMENT
PUBLIC var_pos@0x2747157d260 ; var_pos
PUBLIC var_pos2@0x2747157d410 ; var_pos2
PUBLIC var_tpos@0x27471581000 ; var_tpos
PUBLIC var_boss@0x2747157fa10 ; var_boss
PUBLIC s@0x27471581510 ; s
PUBLIC t@0x27471584600 ; t
PUBLIC y@0x274715847b0 ; y
PUBLIC bla@0x27471585380 ; bla
PUBLIC bg@0x274715840f0 ; bg
PUBLIC g@0x27471584960 ; g
PUBLIC var_gra@0x27471584cc0 ; var_gra
PUBLIC a@0x274715842a0 ; a
PUBLIC my_pos@0x27471585530 ; my_pos
PUBLIC func@0x27471587cc0 ; func

var_pos@0x2747157d260 DB 011H DUP(?) ; var_pos
var_pos2@0x2747157d410 DB 011H DUP(?) ; var_pos2
var_tpos@0x27471581000 DB 01H DUP(?) ; var_tpos
var_boss@0x2747157fa10 DB 011H DUP(?) ; var_boss
s@0x27471581510 DB 01H DUP(?) ; s
t@0x27471584600 DB 01H DUP(?) ; t
y@0x274715847b0 DB 01H DUP(?) ; y
bla@0x27471585380 DQ 01H DUP(?) ; bla
bg@0x274715840f0 DQ 01H DUP(?) ; bg
g@0x27471584960 DQ 01H DUP(?) ; g
var_gra@0x27471584cc0 DB 01H DUP(?) ; var_gra
a@0x274715842a0 DB 01H DUP(?) ; a


_TEXT SEGMENT
_xy$ = -24        ; size = 17
my_pos@0x27471585530 PROC
my_pos@0x27471585530 ENDP
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
func@0x27471587cc0 PROC
mov eax, 2
add eax, 4
mov ebx, 1
imul ebx, 7
sub eax, ebx
mov ebx, eax
cdq
mov eax, 34
idiv [a@0x274715842a0]
sub ebx, eax
mov eax, [a@0x274715842a0]
add eax, 5
mov ecx, BYTE PTR _nas$[ebp - 64]
sub ecx, 2
func@0x27471587cc0 ENDP
_TEXT ENDS
