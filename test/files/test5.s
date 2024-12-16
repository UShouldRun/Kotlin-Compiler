fibo:
    sw $fp -4($sp) 
    sw $ra -8($sp) 
    mv $fp $sp 
    lw $t3 12($fp) 
    li $t4 0 
    beq $t1 $t3 $t4
    lw $t3 12($fp) 
    li $t4 1 
    beq $t2 $t3 $t4
    or $t0 $t1 $t2
    bne $t0 1 cond0
    lw $t1 12($fp) 
    mv $v0 $t1 
    mv $sp $fp 
    lw $ra -8($sp) 
    lw $fp -4($sp) 
    jr $ra  
    addi $sp 0
    j cond1  
cond0:
cond1:
    lw $t4 12($fp) 
    li $t5 1 
    sub $t3 $t4 $t5
    sw $t3 -4($sp) 
    addi $sp -4
    jal fibo  
    addi $sp 4
    mv $t1 $v0 
    lw $t4 12($fp) 
    li $t5 2 
    sub $t3 $t4 $t5
    sw $t3 -4($sp) 
    addi $sp -4
    jal fibo  
    addi $sp 4
    mv $t2 $v0 
    add $t0 $t1 $t2
    mv $v0 $t0 
    mv $sp $fp 
    lw $ra -8($sp) 
    lw $fp -4($sp) 
    jr $ra  
main:
    sw $fp -4($sp) 
    sw $ra -8($sp) 
    mv $fp $sp 
    mv $v0 1 
    li $v0, 5
    syscall
    mv $t0 $v0 
    sw $t0 $fp 
    addi $sp -4
    lw $t1 $fp 
    sw $t1 -4($sp) 
    addi $sp -4
    jal fibo  
    addi $sp 4
    mv $t0 $v0 
    sw $t0 -4($fp) 
    addi $sp -4
    lw $a0 -4($fp) 
    mv $v0 1 
    li $v0, 1
    syscall
    mv $sp $fp 
    lw $ra -8($sp) 
    lw $fp -4($sp) 
    jr $ra  
