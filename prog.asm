_BSS SEGMENT
PUBLIC var_pos@0x1d9c9b5ee00 ; var_pos
PUBLIC var_pos2@0x1d9c9b5e230 ; var_pos2
PUBLIC var_tpos@0x1d9c9b61c70 ; var_tpos
PUBLIC var_boss@0x1d9c9b61e20 ; var_boss
PUBLIC s@0x1d9c9b62840 ; s
PUBLIC t@0x1d9c9b65ae0 ; t
PUBLIC y@0x1d9c9b65c90 ; y
PUBLIC bla@0x1d9c9b65e40 ; bla
PUBLIC bg@0x1d9c9b65ff0 ; bg
PUBLIC g@0x1d9c9b66a10 ; g
PUBLIC var_gra@0x1d9c9b65420 ; var_gra
PUBLIC a@0x1d9c9b650c0 ; a
PUBLIC my_pos@0x1d9c9b65780 ; my_pos
PUBLIC func@0x1d9c9b6ab90 ; func

var_pos@0x1d9c9b5ee00 DB 011H DUP(?) ; var_pos
var_pos2@0x1d9c9b5e230 DB 011H DUP(?) ; var_pos2
var_tpos@0x1d9c9b61c70 DB 01H DUP(?) ; var_tpos
var_boss@0x1d9c9b61e20 DB 011H DUP(?) ; var_boss
s@0x1d9c9b62840 DB 01H DUP(?) ; s
t@0x1d9c9b65ae0 DB 01H DUP(?) ; t
y@0x1d9c9b65c90 DB 01H DUP(?) ; y
bla@0x1d9c9b65e40 DQ 01H DUP(?) ; bla
bg@0x1d9c9b65ff0 DQ 01H DUP(?) ; bg
g@0x1d9c9b66a10 DQ 01H DUP(?) ; g
var_gra@0x1d9c9b65420 DB 01H DUP(?) ; var_gra
a@0x1d9c9b650c0 DB 01H DUP(?) ; a


_TEXT SEGMENT
xy@0x1d9c9b65270 = -24        ; size = 17
my_pos@0x1d9c9b65780 PROC
my_pos@0x1d9c9b65780 ENDP
_TEXT ENDS

_TEXT SEGMENT
u@0x1d9c9b69750 = -80        ; size = 1
nb@0x1d9c9b6a680 = -72        ; size = 8
nas@0x1d9c9b69c60 = -64        ; size = 1
tas@0x1d9c9b6a9e0 = -63        ; size = 1
a@0x1d9c9b6ad40 = -56        ; size = 8
r@0x1d9c9b6a830 = -48        ; size = 1
cl@0x1d9c9b69240 = -40        ; size = 17
rt@0x1d9c9b6d7d0 = -16        ; size = 8
k@0x1d9c9b6e700 = -8        ; size = 1
func@0x1d9c9b6ab90 PROC
func@0x1d9c9b6ab90 ENDP
_TEXT ENDS
