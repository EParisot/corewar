.name			"live-zjmp"
.comment		"live-zjmp"

live:		live %42
			sti  r1, %:live, %1
			add   r2, r2, r2
			zjmp %:live