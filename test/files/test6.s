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
    mv $v0 1 
    li $v0, 5
    syscall
    mv $t0 $v0 
    sw $t0 -4($fp) 
    addi $sp -4
    lw $t1 $fp 
    lw $t2 -4($fp) 
    add $t0 $t1 $t2
    sw $t0 -8($fp) 
    addi $sp -4
    lw $a0 -8($fp) 
    mv $v0 1 
    li $v0, 1
    syscall
    mv $sp $fp 
    lw $ra -8($sp) 
    lw $fp -4($sp) 
    jr $ra  
