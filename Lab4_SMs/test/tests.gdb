# Test file for Lab4_SMs


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
test "PINA: 0x00, 0x02 => PORTB: 0x01, LT_state: INIT"
set LT_state = INIT
setPINA 0x00
continue 2
setPINA 0x02
continue 2
expectPORTB 0x01
expect LT_state INIT
checkResult

test "PINA: 0x01, 0x01 => PORTB: 0x02, LT_state: TURN_OFF"
set LT_state = INIT
setPINA 0x01
continue 2
setPINA 0x01
continue 2
expectPORTB 0x02
expect LT_state TURN_OFF
checkResult

test "PINA: 0x01, 0x00 => PORTB: 0x02, LT_state: WAIT_FIRST"
set LT_state = INIT
setPINA 0x01
continue 2
setPINA 0x00
continue 2
expectPORTB 0x02
expect LT_state WAIT_FIRST
checkResult

test "PINA: 0x01, 0x02, 0x01 => PORTB: 0x01, LT_state: TURN_ON"
set LT_state = INIT
setPINA 0x01
continue 2
setPINA 0x02
continue 2
setPINA 0x01
continue 2
expectPORTB 0x01
expect LT_state TURN_ON
checkResult

test "PINA: 0x01, 0x02, 0x01, 0x02 => PORTB: 0x01, LT_state: WAIT_SECOND"
set LT_state = INIT
setPINA 0x01
continue 2
setPINA 0x02
continue 2
setPINA 0x01
continue 2
setPINA 0x02
continue 2
expectPORTB 0x01
expect LT_state WAIT_SECOND
checkResult

test "PINA: 0x01, 0x02, 0x01, 0x02, 0x01, 0x01  => PORTB: 0x01, LT_state: TURN_OFF"
set LT_state = INIT
setPINA 0x01
continue 2
setPINA 0x02
continue 2
setPINA 0x01
continue 2
setPINA 0x02
continue 2
setPINA 0x01
continue 2
setPINA 0x01
continue 2
expectPORTB 0x02
expect LT_state TURN_OFF
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
