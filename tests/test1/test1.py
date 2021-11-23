from tests_functions import *
conf_file = "./test1.file.txt"
p = RunningProgram("test 1", conf_file)

try:
    p.assert_command_returns("order 0", "Trainer does not exist or is not open")
    p.assert_command_returns("open 3 nadav,mcl niv,chp", "")
    p.assert_command_returns("order 3", """nadav Is Doing Yoga
nadav Is Doing Pilates
niv Is Doing Rope Jumps""")
    p.assert_command_returns("backup", "")
    p.assert_command_returns("close 3", "Trainer 3 closed. Salary 270NIS")
    p.assert_command_returns("restore", "")

finally:
    p.end_test("Trainer 3 closed. Salary 270NIS")

