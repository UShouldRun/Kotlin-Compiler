    .text
    .globl main

main:
    move $fp, $sp
    li $v0, 5
    syscall
    move $t0, $v0
    sw $t0, -4($fp)
    addi $sp, $sp, -4
    li $v0, 5
    syscall
    move $t0, $v0
    sw $t0, -8($fp)
    addi $sp, $sp, -4
    lw $t1, -4($fp)
    lw $t2, -8($fp)
    add $t0, $t1, $t2
    sw $t0, -12($fp)
    addi $sp, $sp, -4
    lw $a0, -12($fp)
    li $v0, 1
    syscall
    li $v0, 10
    syscall
