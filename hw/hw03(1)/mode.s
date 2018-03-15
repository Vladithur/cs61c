	.data
# do not modify
LIST1:	
	.word 2 3 3 4 5 6 7 7 7 8
LIST2:	
	.word 1 3 4 4 5 6 6 9 9 9
LIST3:
	.word 35
received1:   
	.asciiz "LIST1: received "
received2:   
	.asciiz "LIST2: received "
received3:
	.asciiz "LIST3: received "
newline: 
	.asciiz "\n"
expected:
	.asciiz ", expected "
	
	.text

printLoop:
	# test case 1
	la $a0 LIST1 # get address of the array
	li $a1 10 # length of list
	jal mode
	move $s0, $v0
	la $a0 received1
	la $v0 4
	syscall # PRINT "LIST1: received "
	move $a0 $s0
	li $v0 1
	syscall # PRINT value returned from call to mode
	la $a0 expected
	li $v0 4
	syscall # PRINT ", expected "
	li $a0 7
	li $v0 1
	syscall # PRINT expected result
	la $a0 newline
	li $v0 4
	syscall # PRINT newline
	
	# test case 2
	la $a0 LIST2 # get address of the array
	li $a1 10 # length of list
	jal mode
	move $s0, $v0
	la $a0 received2
	la $v0 4
	syscall # PRINT "LIST2: received "
	move $a0 $s0
	li $v0 1
	syscall # PRINT value returned from call to mode
	la $a0 expected
	li $v0 4
	syscall # PRINT ", expected "
	li $a0 9
	li $v0 1
	syscall # PRINT expected result
	la $a0 newline
	li $v0 4
	syscall # PRINT newline

	# test case 3
	la $a0 LIST3 # get address of the array
	li $a1 1 # length of list
	jal mode
	move $s0, $v0
	la $a0 received3
	la $v0 4
	syscall # PRINT "LIST3: received "
	move $a0 $s0
	li $v0 1
	syscall # PRINT value returned from call to mode
	la $a0 expected
	li $v0 4
	syscall # PRINT ", expected "
	li $a0 35
	li $v0 1
	syscall # PRINT expected result

	li $v0 10
	syscall # EXIT
	
mode: # mode($a0,$a1)
	# ****** YOUR CODE STARTS HERE ******
	#
        # $a0 is the address of the list, and $a1 is the length.
        #
	# Try not to deviate too greatly (if at all) from the C version.
        #
	# DO NOT look up the values of the $s registers, LIST,
        # etc from above. You will receive no credit if you do.
        #
        # This problem can be solved using only the $a0-$a3,$t0-$t?,
        # $v0,$ra registers.

	lw $t1 0($a0) # currNum = arr[0]
        li $t2 1 # count = 1
        move $v0 $t1 # mode = currNum
        li $t3 0 # modeCount = 0
        li $t4 1 # initialize i to 1
        
        # Begin your code here, starting at the for loop in the C code.
        
loop:
	bge $t4, $a1, return # if (i >= len), return
	addiu $a0, $a0, 4 # *arr = *(arr + 1)
	lw $t5, 0($a0) # load arr[i]
	beq $t5, $t1, addcount # go to addcount if (arr[i] == currNum)
l:
	addiu $t6, $a1, -1 # set a temp value of len - 1
	beq $t4, $t6, mainif # jump to mainif if (i == len - 1)
	bne $t5, $t1, mainif # jump to mainif if (arr[i] != currNum)
l2:
	addiu $t4, $t4, 1 # i++
	j loop # loop
addcount:
	addiu $t2, $t2, 1 # count++
	j l # return back to loop
mainif:
	bgt $t2, $t3 newmode # jump to newmode if (count > modeCount)
m:
	move $t1, $t5 # currNum = arr[i]
	li $t2 1 # count = 1
	j l2 # got back to loop
newmode:
	move $t3, $t2 # modeCount = count
	move $v0, $t1 # mode = currNum
	j m # jump back to mainif
return:
	jr $ra # return
