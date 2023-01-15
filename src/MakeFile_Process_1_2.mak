all: cr clean
cr:
	@echo "For Question 2\n"
	@echo "Make sure to login as root\n"
	gcc -w -o r Process_1_2.c
	./r
clean:
	@echo "**Removing Redundant Files** "
	rm -f r
	@echo "\n**Removed Redundant Files** \n"