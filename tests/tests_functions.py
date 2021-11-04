import subprocess
import os
MAIN_FILE_LOCATION = "../main.cpp"
VALGRIND_LOG_FILE = './valgrind_log.txt'
END_COMMAND = "closeall"


def run_command(command: str):
    output = subprocess.run([command], stdout=subprocess.PIPE).stdout.decode('utf8').split('\n')
    if len(output) == 0:
        return
    elif len(output) == 1:
        return output[0]
    return output

def start_test(test_name: str, conf_file: str):
    print(f"running test: {test_name}")
    start_command = f"valgrind --leak-check=full --show-reachable=yes --log-file={VALGRIND_LOG_FILE} " \
                    f"g++ ../main.cpp {conf_file}"
    run_command(start_command)

def read_line_from_log(line_prefix: str, log: str):
    first_index = log.find(line_prefix)
    last_index = log.find('\n', first_index)
    return log[first_index:last_index]

def end_test():
    run_command(END_COMMAND)
    with open(VALGRIND_LOG_FILE, 'r', encoding='utf8') as log_file:
        valgrind_log = log_file.read()

    os.remove(VALGRIND_LOG_FILE)
    definitely_lost_line = read_line_from_log("definitely lost", valgrind_log)
    possibly_lost_line = read_line_from_log("possibly lost", valgrind_log)


    assert definitely_lost_line == "definitely lost: 0 bytes in 0 blocks"
    assert possibly_lost_line == "possibly lost: 0 bytes in 0 blocks"

    print("test passed!\n")

