PROGRAMS= main

# Un/comment the following two lines to use/disable sanitizers (UBSan, LSan & ASan):
#CFLAGS=-fno-omit-frame-pointer -fno-common -fsanitize=undefined,leak,address -fsanitize-recover=all
#LDLIBS=-lasan -lubsan

CC=clang
ASAN_STOP_ON_ERROR=halt_on_error=1:abort_on_error=1:print_legend=0
ASAN_CONT_ON_ERROR=halt_on_error=0:abort_on_error=0:print_legend=0
ASAN_RUNTIME=$(ASAN_CONT_ON_ERROR):detect_leaks=1:leak_check_at_exit=1:symbolize=1:exitcode=1
ASAN_GDB=

# My syntax checker wants access to my compilation flags too, so:
include Makefile.inc

CFLAGS_DBG=$(CFLAGS) -gdwarf-4 -ggdb3 -Werror -I./include
CFLAGS_PERF=$(CFLAGS) -O3 -I./include

LDLIBS+=-lm 

# https://stackoverflow.com/a/18258352
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

TESTS_REC_SRC=$(call rwildcard,test,*.c)
TESTS_REC=$(sort $(TESTS_REC_SRC:.c=))

TESTS_SRC=$(wildcard test/*.c)
TESTS=$(sort $(TESTS_SRC:.c=))


TESTS_ORACLE_REC_SRC=$(call rwildcard,tests_oracle,*.c)
TESTS_ORACLE_REC=$(sort $(TESTS_ORACLE_REC_SRC:.c=))

TESTS_ORACLE_SRC=$(wildcard tests_oracle/*.c)
TESTS_ORACLE=$(sort $(TESTS_ORACLE_SRC:.c=))


HEADERS=$(call rwildcard,include,*.h)

SRC=$(call rwildcard,src,*.c)
OBJ=$(SRC:.c=.o)
PERF_OBJ=$(SRC:.c=.perf)

all : $(addprefix programs/,$(PROGRAMS)) tests tests_oracle

programs/% : programs/%.perf $(PERF_OBJ) $(HEADERS) # Rebuild on header change, too
	$(CC) $(LDFLAGS) $(word 1, $^) $(PERF_OBJ) -o $@ $(LDLIBS)

%.o : %.c
	$(CC) $(CFLAGS_DBG) -c $< -o $@

%.perf : %.c
	$(CC) $(CFLAGS_PERF) -c $< -o $@

tests : $(TESTS_REC)

test/% : test/%.o $(OBJ) $(HEADERS)
	$(CC) $(LDFLAGS) $(word 1, $^) $(OBJ) -o $@ $(LDLIBS)

tests_oracle: $(TESTS_ORACLE_REC)

tests_oracle/% : tests_oracle/%.o $(OBJ) $(HEADERS)
	$(CC) $(LDFLAGS) $(word 1, $^) $(OBJ) -o $@ $(LDLIBS)

testDico1H: programs/main
	./programs/main ./dico_txt/dico1.txt -h

testVDico1H: programs/main
	valgrind ./programs/main ./dico_txt/dico1.txt -h


help :
	@echo ''
	@echo "  \e[3m\e[31m>> A Fast Workflow for C on GNU/Linux\e[m with \e[1m\e[34moptions\e[m, sanitizers,\n     and even some \e[2m\e[37mless useful functions\e[m."
	@echo ''
	@echo ''
	@echo "  Hint: VS Code will launch foo@debug executions below on (Ctrl-)F5."
	@echo "  Hint: VS Code will rightfully refuse to debug a src/*.c alone."
	@echo "  Hint: Add tests command line args for VS Code in .vscode/launch.json."
	@echo "  Hint: Add your global compilation options in Makefile.inc."
	@echo ''
	@echo '  Module foo of project bar = {src,test}/foo.c + include/bar/foo.h'
	@echo ''
	@echo ''
	@echo " \e[7m\e[32m Project management \e[m"
	@echo ''
	@echo "  \e[2m\e[37mmake                        Compile project and tests\e[m"
	@echo "  \e[2m\e[37mmake programs/bar           Compile programs/bar.c\e[m"
	@echo ''
	@echo ''
	@echo " \e[7m\e[32m Individual tests \e[m"
	@echo ''
	@echo "  \e[2m\e[37mmake test/foo                Compile test/foo.c\e[m"
	@echo '  make test/foo@check          Compile and run test/foo, check leaks'
	@echo " \e[1m\e[41m make test/foo@debug          Compile and run test/foo in debugger \e[m"
	@echo ''
	@echo ''
	@echo " \e[7m\e[32m All tests \e[m                     \e[21mDefault: Stop on first failed test\e[m"
	@echo ''
	@echo "  \e[2m\e[37mmake tests                  Compile all tests\e[m"
	@echo "  \e[1m\e[41m make tests@check            Compile and run all tests, check leaks \e[m"
	@echo "  \e[2m\e[37mmake tests@check-recursive  Recursive version (for regression)\e[m"
	@echo "  \e[2m\e[37mmake tests@debug            Compile and run all tests in debugger\e[m"
	@echo "  \e[2m\e[37mmake tests@debug-recursive  Recursive version (for regression)\e[m"
	@echo ''
	@echo "   \e[1m\e[34m Continue tests execution \e[m all=yes"
	@echo "   \e[1m\e[34m Command line arguments \e[m   args=\"argv[1] .. argv[argc-1]\""
	@echo ''

tests@check : $(TESTS)
	@for test in $^; do printf "\e[7m\e[36m** RUNNING $$test **\e[m\n"; make -s $$test@check args='$(args)'; if [ $$? -eq 0 ] ; then printf "\n\e[7m\e[32mSUCCESS\e[m\n" ; else printf "\n\e[6m\e[7m\e[31mFAILED\e[m\n" ; if [ -z $(all) ] ; then break ; fi ; fi ; done

tests@debug : $(TESTS)
	@for test in $^; do printf "\e[7m\e[33m** DEBUGGING $$test **\e[m\n"; make -s $$test@debug args='$(args)'; if [ $$? -eq 0 ] ; then printf "\e[7m\e[32mSUCCESS\e[m\n" ; else printf "\e[6m\e[7m\e[31mFAILED\e[m\n" ; if [ -z $(all) ] ; then break ; fi ; fi ; done

tests@check-recursive : $(TESTS_REC)
	@for test in $^; do printf "\e[7m\e[33m** RUNNING $$test **\e[m\n"; make -s $$test@check args='$(args)'; if [ $$? -eq 0 ] ; then printf "\e[7m\e[32mSUCCESS\e[m\n" ; else printf "\e[6m\e[7m\e[31mFAILED\e[m\n" ; if [ -z $(all) ] ; then break ; fi ; fi ; done

tests@debug-recursive : $(TESTS_REC)
	@for test in $^; do printf "\e[7m\e[33m** DEBUGGING $$test **\e[m\n"; make -s $$test@debug args='$(args)'; if [ $$? -eq 0 ] ; then printf "\e[7m\e[32mSUCCESS\e[m\n" ; else printf "\e[6m\e[7m\e[31mFAILED\e[m\n" ; if [ -z $(all) ] ; then break ; fi ; fi ; done


tests_oracle@check : $(TESTS_ORACLE)
	@printf "\e[7m\e[36m**Running script tests_oracle/check_oracles.sh\e[m\n"
	@tests_oracle/check_oracles.sh; if [ $$? -eq 0 ] ; then printf "\e[7m\e[36m**All tests ran by check_oracles.sh script passed successfully. Gratz.\e[m\n" ; else printf "\n\e[6m\e[7m\e[31mFAILED\e[m\n" ; fi ;




%@check : %
	@ASAN_OPTIONS=$(ASAN_RUNTIME) UBSAN_OPTIONS=$(ASAN_CONT_ON_ERROR) ./$< $(args)

%@debug : %
	@gdb -q --return-child-result -nh -x ~/.gdbinit -x test/env.gdb --args $< $(args) '-g' '-v'

clean :
	$(RM) $(addprefix programs/,$(PROGRAMS)) $(TESTS_REC) $(TESTS_ORACLE_REC)
	find . -name "*.o" -delete

deep-clean : clean
	$(RM) .projectile GTAGS GRTAGS GPATH
	find . -name "*~" -delete
	find . -name "._*" -delete
	$(RM) .gdb_history
		
