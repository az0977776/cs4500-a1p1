from random import randint

rows = 1000 * 1000
num_spaces = 5
integer_range = 1000000
strings = ['Hello', 'world', 'foo', 'bar', 'baz', '"Hello World"', '1.333', '1', '1111', '"123 String"', '', '']

def get_start():
    return " " * randint(0, num_spaces) + "<" + " " * randint(0, num_spaces)

def get_end():
    return " " * randint(0, num_spaces) + ">" + " " * randint(0, num_spaces)




def get_boolean():
    rv = str(randint(0, 1))
    if randint(0, 1) == 0:
        rv = ''
    return get_start() + rv + get_end()

def get_int():
    rv = str(randint(-1 * integer_range, integer_range))
    if randint(0, 1) == 0:
        rv = ''
    return get_start() + rv + get_end()

def get_float():
    rv = str(randint(-1 * integer_range, integer_range) / randint(-1 * integer_range / 2, integer_range / 2))
    if randint(0, 1) == 0:
        rv = ''
    return get_start() + rv + get_end()

def get_string():
    return get_start() + strings[randint(0, len(strings) - 1)] + get_end()



def print_strings():
    for i in range(rows):
        print(get_boolean() + get_int() + get_float() + get_string())

print_strings()


