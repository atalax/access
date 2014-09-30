GCC=gcc

access: access.c
	$(CROSS)$(GCC) $< -o $@

clean:
	rm access

all: access
