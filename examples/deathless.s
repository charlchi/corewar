.name "deathless"
.comment "I'M ALIIIIVE"

live:
		live %1

l1:
		sti r1, %:live, %1
		and r1, %0, r1
		live %1
		fork %:l2
		zjmp %:l1
l2:
		sti r1, %:live, %1
		and r1, %0, r1
		live %1
		fork %:l3
		zjmp %:l2
l3:
		sti r1, %:live, %1
		and r1, %0, r1
		live %1
		fork %:l4
		zjmp %:l3
l4:
		sti r1, %:live, %1
		and r1, %0, r1
		live %1
		fork %:l5
		zjmp %:l4
l5:
		sti r1, %:live, %1
		and r1, %0, r1
		live %1
		fork %:l6
		zjmp %:l5
l6:
		sti r1, %:live, %1
		and r1, %0, r1
		live %1
		fork %:l7
		zjmp %:l6
l7:
		sti r1, %:live, %1
		and r1, %0, r1
		live %1
		fork %:l8
		zjmp %:l7
l8:
		sti r1, %:live, %1
		and r1, %0, r1
		live %1
		fork %:l9
		zjmp %:l8
l9:
		sti r1, %:live, %1
		and r1, %0, r1
		live %1
		fork %:l10
		zjmp %:l9
l10:
		sti r1, %:live, %1
		and r1, %0, r1
		live %1
		fork %:l1
		zjmp %:live
