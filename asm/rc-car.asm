  .org 0
    rjmp init
     .org 0x60
    init:
          ; --- Inizializza stack ---
          ldi r16, 0xFF
          out 0x3D, r16    ; SPL
          ldi r16, 0x08
          out 0x3E, r16    ; SPH
   loop:
    sbi 4,0
    rcall forward
    rjmp loop


    forward:
    ;forward W2 W2 W2 W2 (10) x W1
    ; 4 x w2 1.5ms
    rcall w2
    rcall w2
    rcall w2
    rcall w2
    ;10 x w1 .5ms
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    rcall w1
    ret

    w2:
    sbi 5,0
    ldi r17,31
    rcall pause
    cbi 5,0
    ldi r17,11
    rcall pause
    ret

    w1:
    sbi 5,0
    ldi r17,11
    rcall pause
    cbi 5,0
    ldi r17,11
    rcall pause
    ret

    pause:
    dec r16
    brne pause
    dec r17
    brne pause

    ret
