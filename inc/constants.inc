; Bits - VPHB SINN
; V - NMI enable
; P - PPU master/slave
; H - Sprite height
; B - Background tile select
; S - Sprite tile select
; I - Increment mode
; NN - Nametable select
PPU_CTRL = $2000

; Bits - BGRs bMmG
; BGR - Color emphasis
; s - Sprite enable
; b - Background enable
; M - Sprite left column enable
; m - Background left column enable
; G - Greyscale
PPU_MASK = $2001

; Bits - VSO
; V - VBLANK
; S - Sprite 0 hit
; O - Sprite overflow
; Read resets write pair for $2005/$2006
PPU_STATUS = $2002

OAM_ADDR = $2003
OAM_DATA = $2004

PPU_SCROLL = $2005
PPU_ADDR = $2006
PPU_DATA = $2007

OAM_DMA = $4014

; APU - Audo
; Delta modulation channel
APU_DMC_FREQ = $4010

; Bits - MI
; M - Mode. 0 = 4-step, 1 = 5-step
; I = IRQ inhibit flag
APU_FRAME_COUNTER = $4017
