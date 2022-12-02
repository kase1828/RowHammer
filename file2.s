        MRC p15, 1, R0, c0, c0, 1     ; Read CLIDR

        ANDS R3, R0, #&7000000

        MOV R3, R3, LSR #23           ; Cache level value (naturally aligned)        

        BEQ Finished

        MOV R10, #0

Loop1   ADD R2, R10, R10, LSR #1      ; Work out 3xcachelevel

        MOV R1, R0, LSR R2            ; bottom 3 bits are the Cache type for this level 

        AND R1, R1, #7                ; get those 3 bits alone

        CMP R1, #2

        BLT Skip                      ; no cache or only instruction cache at this level

        MCR p15, 2, R10, c0, c0, 0    ; write the Cache Size selection register

        ISB                           ; ISB to sync the change to the CacheSizeID reg

        MRC p15, 1, R1, c0, c0, 0     ; reads current Cache Size ID register

        AND R2, R1, #&7               ; extract the line length field

        ADD R2, R2, #4                ; add 4 for the line length offset (log2 16 bytes)

        LDR R4, =0x3FF

        ANDS R4, R4, R1, LSR #3       ; R4 is the max number on the way size (right aligned)

        CLZ R5, R4                    ; R5 is the bit position of the way size increment

        LDR R7, =0x00007FFF

        ANDS R7, R7, R1, LSR #13      ; R7 is the max number of the index size (right aligned)

Loop2   MOV R9, R4                    ; R9 working copy of the max way size (right aligned)

Loop3   ORR R11, R10, R9, LSL R5      ; factor in the way number and cache number into R11

        ORR R11, R11, R7, LSL R2      ; factor in the index number

        MCR p15, 0, R11, c7, c10, 2   ; clean by set/way

        SUBS R9, R9, #1               ; decrement the way number

        BGE Loop3    

        SUBS R7, R7, #1               ; decrement the index

        BGE Loop2

Skip    ADD R10, R10, #2              ; increment the cache number

        CMP R3, R10

        BGT Loop1
