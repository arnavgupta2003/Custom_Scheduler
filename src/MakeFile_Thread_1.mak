all: cr clean
cr:
	@echo "For Question 1\n"
	@echo "Make sure to login as root\n"
	gcc -w -o r Thread_1.c
	./r
clean:
	@echo "**Removing Redundant Files** "
	rm -f r
	@echo "\n**Removed Redundant Files** \n"