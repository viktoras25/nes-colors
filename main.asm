.include "inc/init.inc"

.segment "CODE"

.PROC INIT
    LDA #$00
    STA bg_color

    LDA #$00
    STA counter

    RTS
.ENDPROC

.PROC MAIN
    JMP FOREVER
.ENDPROC

FOREVER:
    JMP FOREVER

.PROC UPDATE_BG_COLOR
    ; Only update color every 7 frames
    INC counter
    LDA counter
    CMP #$07
    BNE RETURN

    ; Choose on of 48 ($31) colors
    INC bg_color
    LDA bg_color
    CMP #$31
    BNE SET_COLOR

    ; Reset back to first color
    LDA #$00
    STA bg_color

    SET_COLOR:
    LDA #$3F
    STA PPU_ADDR
    LDA #$00
    STA PPU_ADDR

    LDX bg_color

    LDA COLORS, X
    STA PPU_DATA

    LDA #$00
    STA counter

    RETURN:
    RTS

    COLORS:
        .byte $31, $21, $11, $01, $02, $12, $22, $32
        .byte $33, $23, $13, $03, $04, $14, $24, $34
        .byte $35, $25, $15, $05, $06, $16, $26, $36
        .byte $37, $27, $17, $07, $08, $18, $28, $38
        .byte $39, $29, $19, $09, $0A, $1A, $2A, $3A
        .byte $3B, $2B, $1B, $0B, $0C, $1C, $2C, $3C
.ENDPROC

VBLANK:
    JSR UPDATE_BG_COLOR
    RTI