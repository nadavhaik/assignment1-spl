from tests_functions import *
conf_file = "test2.file.txt"
p = RunningProgram("test 2", conf_file)

try:
    p.assert_command_returns("order 0", "Trainer does not exist or is not open")
    p.assert_command_returns("open 3 nadav,mcl niv,chp yuval,fbd", "")
    p.assert_command_returns("order 3", """nadav Is Doing Yoga
nadav Is Doing Pilates
niv Is Doing Rope Jumps
yuval Is Doing Rope Jumps
yuval Is Doing CrossFit
yuval Is Doing Yoga""")
    p.assert_command_returns("backup", "")
    p.assert_command_returns("close 3", "Trainer 3 closed. Salary 570NIS")
    p.assert_command_returns("restore", "")
    p.assert_command_returns("status 3", """Trainer 3 status: open
Costumers:
0 nadav
1 niv
2 yuval
Orders:
Yoga 90NIS 0
Pilates 110NIS 0
Rope Jumps 70NIS 1
Rope Jumps 70NIS 2
CrossFit 140NIS 2
Yoga 90NIS 2
Current Trainer's Salary: 570NIS""")
    p.assert_command_returns("close 3", "Trainer 3 closed. Salary 570NIS")
    p.assert_command_returns("close 3", "Trainer does not exist or is not open")
    p.assert_command_returns("status 3", "Trainer 3 status: closed")
    p.assert_command_returns("restore", "")
    p.assert_command_returns("status 3", """Trainer 3 status: open
Costumers:
0 nadav
1 niv
2 yuval
Orders:
Yoga 90NIS 0
Pilates 110NIS 0
Rope Jumps 70NIS 1
Rope Jumps 70NIS 2
CrossFit 140NIS 2
Yoga 90NIS 2
Current Trainer's Salary: 570NIS""")

finally:
    p.end_test("Trainer 3 closed. Salary 570NIS")

