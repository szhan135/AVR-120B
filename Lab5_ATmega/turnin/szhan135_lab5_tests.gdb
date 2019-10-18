# Test file for Lab5_ATmega


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

# Example test:

# Add tests below
test "PINA: 0x00=> PORTC: 0x00, state: INIT"
set state = INIT
setPINA 0xFF
continue 2
setPINA 0xFF
continue 2
setPINA 0xFF
continue 2
setPINA 0xFF
continue 2
expectPORTC 0xFF
expect state RESET
checkResult

test "PINA: 0x01, 0x01, 0x01, 0x01 => PORTC: 0x03, state: WAIT"
set state = INIT
setPINA 0xFD
continue 2
setPINA 0xFD
continue 2
setPINA 0xFD
continue 2
setPINA 0xFD
continue 2
expectPORTC 0x04
expect state WAIT
checkResult

test "PINA: 0x01, 0x02, 0x01, 0x02 => PORTC: 0x00, state: WAIT"
set state = INIT
setPINA 0xFE
continue 2
setPINA 0xFD
continue 2
setPINA 0xFE
continue 2
setPINA 0xFD
continue 2
expectPORTC 0x04
expect state WAIT
checkResult

test "PINA: 0x02, 0x02, 0x02, 0x02 => PORTC: 0x09, state: WAIT"
set state = INIT
setPINA 0xFD
continue 2
setPINA 0xFD
continue 2
setPINA 0xFD
continue 2
setPINA 0xFD
continue 2
expectPORTC 0x08
expect state WAIT
checkResult

test "PINA: 0x03, 0x03, 0x03, 0x03 => PORTC: 0x07, state: RESET"
set state = INIT
setPINA 0xFC
continue 2
setPINA 0xFC
continue 2
setPINA 0xFC
continue 2
setPINA 0xFC
continue 2
expectPORTC 0x00
expect state INIT
checkResult

test "PINA: 0x01, 0x02, 0x02, 0x03 => PORTC: 0x08, state: RESET"
set state = INIT
setPINA 0xFE
continue 2
setPINA 0xFD
continue 2
setPINA 0xFD
continue 2
setPINA 0xFC
continue 2
expectPORTC 0x00
expect state WAIT
checkResult
# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
