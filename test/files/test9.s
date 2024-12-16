    .text
    .globl main

main:
    move $fp, $sp
    li $v0, 5
    syscall
    move $t0, $v0
    sw $t0, 0($fp)
    addi $sp, $sp, -4
    li $v0, 5
    syscall
    move $t0, $v0
    sw $t0, -4($fp)
    addi $sp, $sp, -4
cond0:
    lw $t1, 0($fp)
    lw $t2, -4($fp)
    sgt $t0, $t1, $t2
    xori $t0, $t0, 1
    bne $t0, 1, cond1
    lw $t1, 0($fp)
    lw $t2, -4($fp)
    add $a0, $t1, $t2
    li $v0, 1
    syscall
    addi $sp, $sp, 0
    j cond2
cond1:
    lw $t1, 0($fp)
    li $t3, 2
    lw $t4, -4($fp)
    mul $t2, $t3, $t4
    slt $t0, $t1, $t2
    seq $t3, $t1, $t2
    or $t0, $t0, $t3
    bne $t0, 1, cond3
    lw $t1, 0($fp)
    lw $t2, -4($fp)
    mul $a0, $t1, $t2
    li $v0, 1
    syscall
    addi $sp, $sp, 0
    j cond2
cond3:
    lw $t0, 0($fp)
    lw $t1, -4($fp)
    sub $a0, $t0, $t1
    li $v0, 1
    syscall
    addi $sp, $sp, 0
    j cond2
cond2:
    li $v0, 10
    syscall
