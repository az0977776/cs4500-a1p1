### Sor Adapter

* Our SoRer is written in CwC. 

* We have a parent Column class with four subclasses representing columns holding either String objects, floats, ints or booleans.

* When we infer, we look at the first 500 lines starting from the <from> byte and we stop when we reach 500 lines 
or when we have read <len> bytes. The number of columns we infer is the max number of columns of any row in the 
infer group of rows. The default Column is a ColumnBool. For each new element, we check the type of the element before
adding it to the row. We check in the order of: Boolean, Int, Float and String. We update the column inferences
as we iterate through the infer rows.

* Once the column types are inferred, it reads the specified rows and adds the values to the columns. We ignore rows
any of the field values do not match the column type. If fewer columns are given within a row, the rest of the columns
are filled with missing values. If more columns than inferred are given within a row, then the first n values from the
row are attempted to fit into their columns, where n is the number of columns inferred. NOTE: If the input file has
more data after parsing than can fit in memory of the computer it is up to the operating system to generate swap files
for the data. Only the data from the file will be stored in memory not the actual bytes in the file. 

* We have an enum representing the column types.
  * Strings are without spaces unless quoted
  * Floats can have a '-' or '+' at beginning, a single '.' and rest numbers
  * Ints can have a '-' or '+' at the beginning, and rest numbers
  * Bools can be 0 or 1

* The '<', '>', and '"' are special characters. The brackets cannot be by themselves unless they are quoted.
There is no way to put a '"' in a string, we do not support escape characters including new lines in strings.

* We only accept natural numbers for command line arguments.

* Our adapter accepts up to 4096 bytes in a line.

* For printing the column type, we return errors for out of bounds.

* For printing the col idx, we return empty string for missing values and out of bounds. For floating point numbers
the value that is printed is truncated 6 places after the decimal point. i.e. 0.000001123 is 0.000001 and 
0.000000011111 is 0.000000.

* For is missing, we return true for missing values and out of bounds.

* Disclaimer: Any fields without matching brackets on a line will lead to unspecified behavior.

* FLAGS:
```
-f  str     // path to SoR file to be read
-from uint  // starting position in the file (in bytes)
-len uint   // number of bytes to read
-print_col_type uint  // print the type of a column: BOOL, INT, FLOAT, STRING
-print_col_idx uint uint  // the first argument is the column, the second is the offset
-is_missing_idx uint uint // is there a missing in the specified column offset
```

`-f`, `-from`, `-len` are required
accepts one of: `-print_col_type`, `-print_col_idx`, `-is_missing_idx`

EXAMPLE: 
```bash
./sorer -f "data.sor" -from 0 -len 100 -print_col_type 0
```

* Also included:
generate.py is a python 3.7 script that will generate a random file of 1000000 lines. 
to run install python 3.7 and run shell command 
'python3.7 generate.py > filename.sor' 

