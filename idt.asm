extern idtp
global load_idt
	lidt [idtp]
	ret
