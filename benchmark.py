import subprocess
import time
import random
import string

def generate_random_string(length):
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

def run_benchmark(input_data):
    command = ['./hhvlm', input_data]

    start_time = time.time()
    process = subprocess.run(command, capture_output=True, text=True)
    end_time = time.time()

    time_taken = end_time - start_time

    output = process.stdout.strip()

    return output, time_taken

def benchmark_multiple_tests(input_data, num_tests=5):
    times = []

    for _ in range(num_tests):
        _, time_taken = run_benchmark(input_data)
        times.append(time_taken)

    average_time = sum(times) / num_tests

    return average_time

def main():
    num_tests = 1000

    input_lengths = [
        10,
        50,
        100,
        1000,
        10000,
        100000
    ]

    print("Benchmarking Hybrid Hashing Algorithm...")
    print("=" * 50)

    for length in input_lengths:
        input_data = generate_random_string(length)

        average_time = benchmark_multiple_tests(input_data, num_tests=num_tests)

        print(f"Input length: {length}")
        print(f"Average time taken over {num_tests} runs: {average_time:.6f} seconds")
        print("-" * 50)

if __name__ == "__main__":
    main()
