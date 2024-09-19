if !$_isvoid($_any_caller_matches)
	define hook-stop
		while $_thread && $_any_caller_matches("^__|abort|raise")
			up-silently
		end
	end
end

set environment ASAN_OPTIONS  halt_on_error=1:abort_on_error=1:print_legend=0:detect_leaks=0
set environment UBSAN_OPTIONS halt_on_error=1:abort_on_error=1:print_legend=0:print_stacktrace=1

set print pretty on

handle SIGALRM pass
set confirm off
dashboard -enabled off
run
dashboard -enabled on

if !$_isvoid ($_exitcode)
	quit
end
