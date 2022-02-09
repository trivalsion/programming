# Root Makefile Example
# Make Rules


## Variables
DEBUG = OFF# change to ON to turn on debugging mode
ADDITIONAL_CLI_ARGUMENTS =

ifeq ($(DEBUG), ON)
ADDITIONAL_CLI_ARGUMENTS += --debug
endif


## Run
run:
	@python -m farchat_src $(ADDITIONAL_CLI_ARGUMENTS)

clean:
	rm config.json


## Make config
.DEFAULT_GOAL = run
.PHONY: run clean