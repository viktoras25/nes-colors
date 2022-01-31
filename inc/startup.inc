.segment "STARTUP"

SPRITE_MEM = $0200

.PROC RESET
    SEI         ; Disable IRQs
    CLD         ; Disable decimal mode

    ; Disable APU frame IRQ
    LDX #$40    ; 0100_0000
    STX APU_FRAME_COUNTER
    LDX #$00
    STX APU_DMC_FREQ   ; Disable DMC IRQs

    ; Set up stack register
    LDX #$FF
    TXS

    ; Disable video
    LDX #$00
    STX PPU_CTRL    ; Disable NMI/VBLANK
    STX PPU_MASK    ; Disable rendering

    JSR WAIT_VBLANK
    JSR CLEAR_MEM
    RTI
.ENDPROC

.PROC WAIT_VBLANK
    BIT PPU_STATUS
    BPL WAIT_VBLANK
    RTS
.ENDPROC

.PROC CLEAR_MEM
    ; Reset RAM
    LDA #$00
    STA $0000, X
    STA $0100, X
    STA $0300, X
    STA $0400, X
    STA $0500, X
    STA $0600, X
    STA $0700, X

    ; Reset sprite memory
    LDA #$FF
    STA SPRITE_MEM, X

    ; Set sprite memory location ($0200) by setting most significat byte
    LDA .HIBYTE(SPRITE_MEM)
    STA OAM_DMA
    NOP ; Let PPU do it's job

    INX
    BNE CLEAR_MEM

    JSR WAIT_VBLANK

    ; Enable video again
    LDX #$00
    STX PPU_MASK
    LDX #$88
    STX PPU_CTRL

    RTS
.ENDPROC