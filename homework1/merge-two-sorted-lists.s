.data
list1:
    .word 1, 0           # no started from 0
list2:
    .word 2, 0
list3:
    .word 4, 0
    
list4:
    .word 1, 0
list5:
    .word 3, 0
list6:
    .word 4, 0
    
strLink:
    .string " -> "
strNull:
    .string "NULL"


.text
setLinked:
    la    t0, list2
    sw    t0, -4(t0)
    addi  t0, t0, 8
    sw    t0, -4(t0)
    sw    x0,  4(t0)
    lw    s2,  0(t0)     # for checking
    lw    s3,  4(t0)     # for checking
    
    la    t1, list5
    sw    t1, -4(t1)
    addi  t1, t1, 8
    sw    t1, -4(t1)
    sw    x0,  4(t1)
    lw    s4,  0(t1)     # for checking
    lw    s5,  4(t1)     # for checking
    
    la    a0, list1     # a0 = &llist
    la    a1, list4     # a1 = &rlist
    li    a2, 6
    
    
mergeTwoSortedLists:
    addi  s0, sp, -4    # list, sorted, indir
    sw    x0, 0(s0)     # *list = NULL
    sw    s0, -4(s0)    # **sorted = &list
    sw    x0, -8(s0)    # **indir = NULL
    sw    a0, -12(s0)
    sw    a1, -16(s0)
    
loop:
    beq   a0, x0, out
    beq   a1, x0, out
    
    lw    s6, 0(a0)
    lw    s7, 0(a1)
    slt   t2, s7, s6    # 0: left is small or equ
    
    addi  s8, s0, -12
    sw    s8, -8(s0)    # indir = &llist
    beq   t2, x0, lSoE
    addi  s9, s0, -16
    sw    s9, -8(s0)    # indir = &rlist
    
lSoE:
    lw    s10, -8(s0)
    lw    s10, 0(s10)   # s10 = *indir
    lw    s11, -4(s0)   # s11 = sorted
    sw    s10, 0(s11)   # *sorted = *indir
    
    addi  t3, s10, 4
    sw    t3, -4(s0)    # sorted = &(*sorted)->next
    
    lw    t4, -8(s0)    # t4 = indir
    lw    t5, 0(t4)     # t4 = *indir
    lw    t5, 4(t5)
    sw    t5, 0(t4)
    
    lw    a0, -12(s0)
    lw    a1, -16(s0)

    j loop
    
out:
    lw    t6, -4(s0)
    or    s1, a0, a1
    sw    s1, 0(t6)
    
    lw    t0, 0(s0)
printResult:
    beq   a2, x0, end
    lw    a0, 0(t0)
    li    a7, 1
    ecall
    
    la    a0, strLink
    li    a7, 4
    ecall
    
    addi  a2, a2, -1
    lw    t0, 4(t0)
    j printResult

end:
    la    a0, strNull
    li    a7, 4
    ecall
    li    a7, 10
    ecall