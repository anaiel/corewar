.name "zork_test"
.comment "HE IS KIND OF ALIIIIVE"


ld %-3, r2

l2:		sti r2, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
