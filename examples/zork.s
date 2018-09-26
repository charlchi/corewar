.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live1, %1
		and r1, %0, r1

live1:	zjmp %:live1
live4:	zjmp %:live1
live5:	zjmp %:live1
live6:	zjmp %:live1
live7:	zjmp %:live7
live8:	zjmp %:live8
live9:	zjmp %:live9
