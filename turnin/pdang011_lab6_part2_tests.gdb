# Test file for "Lab6_synchSMs"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

test "state: Start => PORTB: 0x01"
set state = Start
continue 5
expectPORTB 0x01
expect state LED_0
checkResult

test "state: Start, Wait 1 sec => PORTB: 0x02"
set state = Start
timeContinue
expectPORTB 0x02
expect state LED_1
checkResult

test "state: Start, Wait 2 sec => PORTB: 0x04"
set state = Start
timeContinue 2
expectPORTB 0x04
expect state LED_2
checkResult

test "state: Start, Wait 3 sec => PORTB: 0x02"
set state = Start
timeContinue 3
expectPORTB 0x01
expect state LED_0
checkResult

test "state: Start, Wait 3 sec, PINA: 0x00 => PORTB: 0x02"
set state = Start
timeContinue 3
setPINA 0x00
expectPORTB 0x02
expect state Pause_Wait
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
