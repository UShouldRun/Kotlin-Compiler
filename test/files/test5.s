    .text
    .globl main

fibo:
    sw $fp, -4($sp)
    sw $ra, -8($sp)
    move $fp, $sp
cond0:
    lw $t3, 0($fp)
    li $t4, 0
    seq $t1, $t3, $t4
    lw $t3, 0($fp)
    li $t4, 1
    seq $t2, $t3, $t4
    or $t0, $t1, $t2
    bne $t0, 1, cond1
    lw $t1, 0($fp)
    move $v0, $t1
    move $sp, $fp
    lw $ra, -8($sp)
    lw $fp, -4($sp)
    jr $ra
    addi $sp, $sp, 0
    j cond2
cond1:
cond2:
    lw $t4, 0($fp)
    li $t5, 1
    sub $t3, $t4, $t5
    sw $t3, -4($sp)
    addi $sp, $sp, -4
    jal fibo
    addi $sp, $sp, 4
    move $t1, $v0
    lw $t4, 0($fp)
    li $t5, 2
    sub $t3, $t4, $t5
    sw $t3, -4($sp)
    addi $sp, $sp, -4
    jal fibo
    addi $sp, $sp, 4
    move $t2, $v0
    add $t0, $t1, $t2
    move $v0, $t0
    move $sp, $fp
    lw $ra, -8($sp)
    lw $fp, -4($sp)
    jr $ra

main:
    la $sp, 0x7FFFFFFC
    move $fp, $sp
    li $v0, 5
    syscall
    move $t0, $v0
    sw $t0, 0($fp)
    addi $sp, $sp, -4
    lw $t1, 0($fp)
    sw $t1, -4($sp)
    addi $sp, $sp, -4
    jal fibo
    addi $sp, $sp, 4
    move $t0, $v0
    sw $t0, -4($fp)
    addi $sp, $sp, -4
    lw $a0, -4($fp)
    li $v0, 1
    syscall
