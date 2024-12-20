    .text
    .globl main

main:
    move $fp, $sp
    li $v0, 5
    syscall
    move $t0, $v0
    sw $t0, 0($fp)
    addi $sp, $sp, -4
    lw $t0, 0($fp)
    sw $t0, -4($sp)
    addi $sp, $sp, -4
    jal factorial
    addi $sp, $sp, 4
    move $a0, $v0
    li $v0, 1
    syscall
    li $v0, 10
    syscall

factorial:
    sw $fp, -4($sp)
    sw $ra, -8($sp)
    move $fp, $sp
    addi $sp, $sp, -8
    li $t0, 1
    sw $t0, -12($fp)
    addi $sp, $sp, -4
    li $t1, 1
    sw $t1, -16($fp)
    addi $sp, $sp, -4
loop0:
    lw $t1, -16($fp)
    lw $t2, 0($fp)
    slt $t0, $t1, $t2
    seq $t3, $t1, $t2
    or $t0, $t0, $t3
    bne $t0, 1, loop1
    lw $t1, -12($fp)
    lw $t2, -16($fp)
    mul $t1, $t1, $t2
    sw $t1, -12($fp)
    lw $t1, -16($fp)
    addi $t1, $t1, 1
    sw $t1, -16($fp)
    j loop0
loop1:
    addi $sp, $sp, 4
    lw $t0, -12($fp)
    move $v0, $t0
    move $sp, $fp
    lw $ra, -8($sp)
    lw $fp, -4($sp)
    jr $ra
