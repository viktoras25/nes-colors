.include "inc/init.inc"

.segment "CODE"

MAIN:
    LDA #$00
    STA flag

    LDA #$00
    STA counter

LOAD_PALETTE:
    ; Write $3F00 into PPU_ADDR - Universal background color
    LDA #$3F
    STA PPU_ADDR
    LDA #$00
    STA PPU_ADDR

    ; Write palette data
    LDA #$1A
    STA PPU_DATA

    LDA #$1E
    STA PPU_MASK

    ; Enable interrupts
    CLI

FOREVER:
    JMP FOREVER

UPDATE_COLORS:
    INC counter
    LDA counter
    CMP #$20
    BNE SkipColorChange
    ; INC flag
    ; LDA flag
    ; EOR #$80
    ; STA flag
    ;STA PPU_MASK

    LDA #$3F
    STA PPU_ADDR
    LDA #$00
    STA PPU_ADDR

    INC flag
    LDA flag
    STA PPU_DATA

    LDA #$00
    STA counter

SkipColorChange:
    RTS

VBLANK:
    JSR UPDATE_COLORS
    RTI
