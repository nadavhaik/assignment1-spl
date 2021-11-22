import subprocess
import os
from time import sleep
MAIN_FILE_LOCATION = "../main.cpp"
VALGRIND_LOG_FILE = './valgrind_log.txt'
END_COMMAND = "closeall"
MAIN_CPP_FILE = "../../main.cpp"
CPP_OUTPUT = "../../main"
read, write = os.pipe()

def assert_equal(obj1, obj2):
    assert obj1 == obj2, f"expected: {obj2}, got: {obj1}"

def read_line_from_log(line_prefix: str, log: str):
    first_index = log.find(line_prefix)
    last_index = log.find('\n', first_index)
    return log[first_index:last_index]

def start_test(test_name: str, conf_file: str):
    compile_command = ["g++", MAIN_CPP_FILE, "-o", CPP_OUTPUT]
    subprocess.run(compile_command, stdout=subprocess.PIPE).stdout.decode('utf8').split('\n')
    print(f"Running: {test_name}")
    start_command = ["valgrind", "--leak-check=full", "--show-reachable=yes", f"--log-file={VALGRIND_LOG_FILE}",
                     CPP_OUTPUT, conf_file]
    p = subprocess.Popen(start_command, stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    assert_equal(p.stdout.readline().decode(), "Studio is now open!\n")
    return p


class RunningProgram:
    def __init__(self, test_name:str, conf_file: str):
        self.process = start_test(test_name, conf_file)

    def assert_command_returns(self, command: str, expected_output: str):
        expected_output_lines = 0 if expected_output == "" else expected_output.count("\n")+1
        output = self.run_command(command, expected_output_lines)
        if expected_output == "":
            assert_equal(output, "")
        else:
            assert_equal(output, expected_output+"\n")

    def run_command(self, command: str, expected_output_lines: int):
        self.process.stdin.write((command + "\n").encode())
        self.process.stdin.flush()
        output = ""
        for _ in range(expected_output_lines):
            output += self.process.stdout.readline().decode()
        return output


    def end_test(self, expected_output: str):
        out, err = self.process.communicate(END_COMMAND.encode())
        os.remove(CPP_OUTPUT)
        assert_equal(out.decode(), expected_output+"\n")
        sleep(2)
        with open(VALGRIND_LOG_FILE, 'r', encoding='utf8') as log_file:
            valgrind_log = log_file.read()

        definitely_lost_line = read_line_from_log("definitely lost", valgrind_log)
        possibly_lost_line = read_line_from_log("possibly lost", valgrind_log)

        if definitely_lost_line != "":
            assert_equal(definitely_lost_line, "definitely lost: 0 bytes in 0 blocks")
        if possibly_lost_line != "":
            assert_equal(possibly_lost_line, "possibly lost: 0 bytes in 0 blocks")

        if valgrind_log.find("All heap blocks were freed -- no leaks are possible") == -1:
            raise AssertionError("The good line wasn't found in valgrind's log!!!")


        os.remove(VALGRIND_LOG_FILE)
        print("Test passed!\n")

