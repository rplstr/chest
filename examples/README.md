## Numeric Example

Demonstrates numeric comparisons: equality, less-than, and greater-than.

Build and run:
```sh
cc -std=c99 -Wall -I.. -o numeric numeric.c
./numeric
# Output:
# numeric assertions ... PASS
# ---
# 1/1 PASSED
# 0 FAILED
```

## Memory Example

Demonstrates memory equality for POD objects.

Build and run:
```sh
cc -std=c99 -Wall -I.. -o memory memory.c
./memory
# Output:
# memory assertions ... PASS
# ---
# 1/1 PASSED
# 0 FAILED
```

## Floating-point Example

Demonstrates approximate float comparison using a tolerance.

Build and run:
```sh
cc -std=c99 -Wall -I.. -o float float.c
./float
# Output:
# float assertions ... PASS
# ---
# 1/1 PASSED
# 0 FAILED
```

## String Example

Demonstrates C-string equality checks.

Build and run:
```sh
cc -std=c99 -Wall -I.. -o string string.c
./string
# Output:
# string assertions ... FAIL
#   'foo' and 'bar' are not EQUAL. (examples/string.c:5)
# ---
# 0/1 PASSED
# 1 FAILED
# string assertions
#   'foo' and 'bar' are not EQUAL. (examples/string.c:5)
```
