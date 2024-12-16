factorial:
    sw fp -4(sp) 
    sw $ra -8(sp) 
    mv fp sp 
    li $t0 1 
    sw $t0 -4(fp) 
    addi sp -4
    li $t1 1 
    sw $t1 -8(fp) 
    addi sp -4
loop0:
    lw $t1 -8(fp) 
    lw $t2 12(fp) 
    ble $t0 $t1 $t2
    beq $t0 1 loop1
    lw $t1 -4(fp) 
    lw $t2 -8(fp) 
    mul $t1 $t1 $t2
    sw $t1 -4(fp) 
    lw $t1 -8(fp) 
    addi $t1 $t1 1
    sw $t1 -8(fp) 
    j loop0  
loop1:
    addi sp 4
    lw $t0 -4(fp) 
    mv $v0 $t0 
    mv sp fp 
    lw $ra -8(sp) 
    lw fp -4(sp) 
    jr $ra  
main:
    sw fp -4(sp) 
    sw $ra -8(sp) 
    mv fp sp 
    li $v0, 5
    syscall
    mv $t0 $v0 
    sw $t0 fp 
    addi sp -4
    lw $t1 fp 
    sw $t1 -4(sp) 
    addi sp -4
    jal factorial  
    addi sp 4
    mv $t0 $v0 
    mv $v0 $t0 
    li $v0, 1
    syscall
    mv sp fp 
    lw $ra -8(sp) 
    lw fp -4(sp) 
    jr $ra  
