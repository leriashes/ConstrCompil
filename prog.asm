_BSS SEGMENT
PUBLIC var_pos@0x1f6b0308fc0 ; var_pos
PUBLIC var_pos2@0x1f6b0308ab0 ; var_pos2
PUBLIC var_tpos@0x1f6b030c850 ; var_tpos
PUBLIC var_boss@0x1f6b030c4f0 ; var_boss
PUBLIC s@0x1f6b030c190 ; s
PUBLIC t@0x1f6b0310000 ; t
PUBLIC y@0x1f6b0310510 ; y
PUBLIC bla@0x1f6b0310f30 ; bla
PUBLIC bg@0x1f6b030fca0 ; bg
PUBLIC g@0x1f6b030f5e0 ; g
PUBLIC var_gra@0x1f6b0310a20 ; var_gra
PUBLIC a@0x1f6b0310360 ; a
PUBLIC my_pos@0x1f6b030faf0 ; my_pos
PUBLIC func@0x1f6b03115f0 ; func

var_pos@0x1f6b0308fc0 DB 011H DUP(?) ; var_pos
var_pos2@0x1f6b0308ab0 DB 011H DUP(?) ; var_pos2
var_tpos@0x1f6b030c850 DB 01H DUP(?) ; var_tpos
var_boss@0x1f6b030c4f0 DB 011H DUP(?) ; var_boss
s@0x1f6b030c190 DB 01H DUP(?) ; s
t@0x1f6b0310000 DB 01H DUP(?) ; t
y@0x1f6b0310510 DB 01H DUP(?) ; y
bla@0x1f6b0310f30 DQ 01H DUP(?) ; bla
bg@0x1f6b030fca0 DQ 01H DUP(?) ; bg
g@0x1f6b030f5e0 DQ 01H DUP(?) ; g
var_gra@0x1f6b0310a20 DB 01H DUP(?) ; var_gra
a@0x1f6b0310360 DB 01H DUP(?) ; a


_TEXT SEGMENT
my_pos@0x1f6b030faf0 PROC
my_pos@0x1f6b030faf0 ENDP
_TEXT ENDS

_TEXT SEGMENT
func@0x1f6b03115f0 PROC
func@0x1f6b03115f0 ENDP
_TEXT ENDS
