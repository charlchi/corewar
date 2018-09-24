.name		"Celebration Funebre v0.99pl42"
.comment	"Jour J"

# 02
90 0000 0000 03
09 0050 0900 00

code:
01    0000002a
0b 64 0f 0000 0e
09    ff38
01    0000002a
0b 64 0f 0000 0e
09    ff38
01 0000 002a 0b64
# 0f00 000e 09ff 3801 0000 002a
0b 64 0f00000e
09ff 38
0b 640f 0000 0e
09 ff38
0b64
# 0f00 000e
09ff 38

		ld   %0,r3		
label:		zjmp %:avantdebut
		zjmp %0				# pour eviter ecrasement
						# de l'instruction suivante
code:		live %42			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		live %42			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		live %42			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		live %42			# 5
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		sti  r15,%0,r14			# 6
		zjmp %-200			# 3
		sti  r15,%0,r14			# 6
		zjmp %-200


0b 68 01 ffb6 0001     sti   r1, %:code, %1 	1
0b 68 01 ffaf 000f     sti   r1, %:code, %15	
0b 68 01 ffa8 001d     sti   r1, %:code, %29	 
0b 68 01 ffa1 002b     sti   r1, %:code, %43	
0b 68 01 ff9a 0039     sti   r1, %:code, %57	 
0b 68 01 ff93 0047     sti   r1, %:code, %71	
	
02 90 00060000 04		ld   %393216, r4		 	#7	 
02 90 000e0000 0c		ld   %917504, r12		#7	
02 90 00000001 0b		ld   %1,      r11			#7 
02 90 00000006 0a		ld   %6,      r10			#7
01 0000002a

init:		ld   %393216,r4		 	#7	
		ld   %917504,r12		#7	
		ld   %1,r11			#7
		ld   %6,r10			#7
debut:		live %42			#5


0b 68 04 ff65 0001		sti  r4,%:label , %1		#7
04 54 04 0c 04			add  r4,r12,r4			#5	
05 54 0a 0b 0a  		sub  r10,r11,r10		#5
09 ffce 				zjmp %:init			#3
0c ffe7 				fork %:debut			
01 00000003 			live %3
0c 0028 				fork %:level10
01 00000004 			live %4
0c 0045 				fork %:level111
01 0000002a 			live %42
0a a4 0008 ff3f 0f 		ldi  %8, %:code, r15		#set des octets 9-12
02 90 ffffff46 0e 		ld   %-186, r14			#=$A-6-8
02 90 00000000 02		ld   %0,r2
09 ff24 				zjmp  %:label	
01 0000002a				live %42
0c 003d					fork %:level100
01 0000002a				live %42
0a a400 04ff 1a0f 0290 ffff ff42
# 0e02 9000 0000 0002 09fe ff01 0000 002a
# 0aa4 000c fefd 0f02 90ff ffff 4a0e 0290
# 0000 0000 0209 fee2 0100 0000 2a0a a400
# 00fe e00f 0290 ffff ff3e 0e02 9000 0000
# 0002 09fe c5



		
		
		
		
		
		
lev     
le      
		
lev     
		
		
		
		
level10:
		
level101
		ldi  %4, %:code, r15 		#set des octets 5-8
		ld   %-190, r14			#=$A-6-4
		ld   %0,r2
		zjmp %:label
		
level111:	live %42	
		ldi  %12, %:code, r15		#set des octets 13-16
		ld   %-182, r14			# $A -6 -12
		ld   %0,r2
		zjmp %:label
		
level100:	live %42
		ldi  %0, %:code, r15		#set des octets 1-4
		ld   %-194, r14			# $A -6 -0
		ld   %0,r2			#
		zjmp %:label			#
