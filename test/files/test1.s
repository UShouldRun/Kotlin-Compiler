    .text
    .globl main

main:
    move $fp, $sp
    li $t0, -1
    sw $t0, 0($fp)
    addi $sp, $sp, -4
    li $t0, 1
    sw $t0, -4($fp)
    addi $sp, $sp, -4
    lw $t0, 0($fp)
    lw $t1, -4($fp)
    add $a0, $t0, $t1
    li $v0, 1
    syscall
    li $v0, 10
    syscall
