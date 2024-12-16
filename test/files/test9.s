    .text
    .globl main

mod:
    sw $fp, -4($sp)
    sw $ra, -8($sp)
    move $fp, $sp
    lw $t0, 0($fp)
    sw $t0, -8($fp)
    addi $sp, $sp, -4
loop0:
    lw $t1, -8($fp)
    lw $t2, 4($fp)
    sgt $t0, $t1, $t2
    xori $t0, $t0, 1
    bne $t0, 1, loop1
    lw $t1, -8($fp)
    lw $t2, 4($fp)
    sub $t1, $t1, $t2
    sw $t1, -8($fp)
    j loop0
loop1:
    addi $sp, $sp, 0
loop2:
    lw $t1, -8($fp)
    li $t2, 0
    slt $t0, $t1, $t2
    bne $t0, 1, loop3
    lw $t1, -8($fp)
    lw $t2, 4($fp)
    add $t1, $t1, $t2
    sw $t1, -8($fp)
    j loop2
loop3:
    addi $sp, $sp, 0
    lw $t0, -8($fp)
    move $v0, $t0
    move $sp, $fp
    lw $ra, -8($sp)
    lw $fp, -4($sp)
    jr $ra

gcd:
    sw $fp, -4($sp)
    sw $ra, -8($sp)
    move $fp, $sp
    lw $t0, 0($fp)
    sw $t0, -8($fp)
    addi $sp, $sp, -4
    lw $t0, 4($fp)
    sw $t0, -12($fp)
    addi $sp, $sp, -4
loop4:
    lw $t1, -12($fp)
    li $t2, 0
    sne $t0, $t1, $t2
    bne $t0, 1, loop5
    lw $t2, -8($fp)
    sw $t2, -8($sp)
    lw $t2, -12($fp)
    sw $t2, -4($sp)
    addi $sp, $sp, -8
    jal mod
    addi $sp, $sp, 8
    move $t1, $v0
    sw $t1, -16($fp)
    addi $sp, $sp, -4
    lw $t1, -12($fp)
    sw $t1, -8($fp)
    lw $t1, -16($fp)
    sw $t1, -12($fp)
    j loop4
loop5:
    addi $sp, $sp, 4
    lw $t0, -8($fp)
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
    li $v0, 5
    syscall
    move $t0, $v0
    sw $t0, -4($fp)
    addi $sp, $sp, -4
cond6:
    lw $t1, 0($fp)
    lw $t2, -4($fp)
    sgt $t0, $t1, $t2
    xori $t0, $t0, 1
    bne $t0, 1, cond7
    li $t4, 2
    lw $t5, 0($fp)
    mul $t2, $t4, $t5
    li $t4, 3
    lw $t5, -4($fp)
    mul $t3, $t4, $t5
    add $t1, $t2, $t3
    sw $t1, -8($sp)
    lw $t2, 0($fp)
    lw $t3, -4($fp)
    add $t1, $t2, $t3
    sw $t1, -4($sp)
    addi $sp, $sp, -8
    jal gcd
    addi $sp, $sp, 8
    move $a0, $v0
    li $v0, 1
    syscall
    addi $sp, $sp, 0
    j cond8
cond7:
    li $t3, 2
    lw $t4, 0($fp)
    mul $t1, $t3, $t4
    lw $t2, -4($fp)
    slt $t0, $t1, $t2
    xori $t0, $t0, 1
    bne $t0, 1, cond9
    li $t4, 5
    lw $t5, 0($fp)
    mul $t2, $t4, $t5
    li $t4, 4
    lw $t5, -4($fp)
    mul $t3, $t4, $t5
    add $t1, $t2, $t3
    sw $t1, -8($sp)
    li $t4, 2
    lw $t5, 0($fp)
    mul $t2, $t4, $t5
    lw $t3, -4($fp)
    add $t1, $t2, $t3
    sw $t1, -4($sp)
    addi $sp, $sp, -8
    jal gcd
    addi $sp, $sp, 8
    move $a0, $v0
    li $v0, 1
    syscall
    addi $sp, $sp, 0
    j cond8
cond9:
    lw $t0, 0($fp)
    sw $t0, -8($sp)
    lw $t0, -4($fp)
    sw $t0, -4($sp)
    addi $sp, $sp, -8
    jal gcd
    addi $sp, $sp, 8
    move $a0, $v0
    li $v0, 1
    syscall
    addi $sp, $sp, 0
    j cond8
cond8:
