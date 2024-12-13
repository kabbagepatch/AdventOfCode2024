DAY=$(shell date +%d)

update-tasks:
	@./update.sh ${DAY}

create:
	@mkdir day${DAY}
	@touch day${DAY}/testinput
	@touch day${DAY}/input
	@touch day${DAY}/notes.md
	@mkdir day${DAY}/part1
	@mkdir day${DAY}/part2
ifeq ($(TITLE),)
	@cp template.cpp day${DAY}/part1/
else
	@cp template.cpp day${DAY}/part1/${TITLE}.cpp
endif

2:
	@cp day${DAY}/part1/*.cpp day${DAY}/part2/

push:
	@git pull
	@git add .
ifeq ($(PART),)
	@git commit -am "Completed day ${DAY}"
else
	@git commit -am "Completed day ${DAY} part $(PART)"
endif
	@git push
