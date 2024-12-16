    .text
    .globl main

sumOfFirstN:
    sw $fp, -4($sp)
    sw $ra, -8($sp)
    move $fp, $sp
    li $t0, 0
    sw $t0, -4($fp)
    addi $sp, $sp, -4
    li $t0, 1
    sw $t0, -8($fp)
    addi $sp, $sp, -4
loop0:
    lw $t1, -8($fp)
    lw $t2, 0($fp)
    slt $t0, $t1, $t2
    xori $t0, $t0, 1
    bne $t0, 1, loop1
    lw $t1, -4($fp)
    lw $t2, -8($fp)
    add $t1, $t1, $t2
    sw $t1, -4($fp)
    lw $t1, -8($fp)
    addi $t1, $t1, 1
    sw $t1, -8($fp)
    j loop0
loop1:
    addi $sp, $sp, 0
    lw $t0, -4($fp)
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
    lw $t0, 0($fp)
    sw $t0, -4($sp)
    addi $sp, $sp, -4
    jal sumOfFirstN
    addi $sp, $sp, 4
    move $a0, $v0
    li $v0, 1
    syscall
