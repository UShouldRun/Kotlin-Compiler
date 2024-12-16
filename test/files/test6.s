    .text
    .globl main

main:
    la $sp, 0x7FFFFFFC
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
    lw $t1, 0($fp)
    lw $t2, -4($fp)
    add $t0, $t1, $t2
    sw $t0, -8($fp)
    addi $sp, $sp, -4
    lw $a0, -8($fp)
    li $v0, 1
    syscall
