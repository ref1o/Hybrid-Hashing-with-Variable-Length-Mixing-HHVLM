import subprocess
import multiprocessing
from multiprocessing import Manager

def generate_hash(input_data):
    # Runs the compiled hashing program and captures the output
    result = subprocess.run(['./hhvlm', input_data], stdout=subprocess.PIPE)
    hash_output = result.stdout.decode('utf-8').strip().split(' ')[1]
    return input_data, hash_output

def worker(start, end, return_dict, collisions_dict):
    local_hashes = {}
    collisions = 0

    for i in range(start, end + 1):
        input_data, hash_output = generate_hash(str(i))
        
        if hash_output in local_hashes:
            collisions += 1
            collisions_dict[hash_output] = (input_data, local_hashes[hash_output])
        else:
            local_hashes[hash_output] = input_data

        # Print progress every 1000 inputs within this worker
        if (i - start + 1) % 1000 == 0:
            print(f"Worker handling range {start}-{end}: Progress {i - start + 1} of {end - start + 1} inputs processed...")
    
    return_dict[(start, end)] = (local_hashes, collisions)

def test_collisions(n, num_processes=4):
    manager = Manager()
    return_dict = manager.dict()
    collisions_dict = manager.dict()

    chunk_size = n // num_processes
    processes = []

    for i in range(num_processes):
        start = i * chunk_size + 1
        end = (i + 1) * chunk_size if i != num_processes - 1 else n
        p = multiprocessing.Process(target=worker, args=(start, end, return_dict, collisions_dict))
        processes.append(p)
        p.start()

    for i, p in enumerate(processes):
        p.join()
        print(f"Process {i + 1}/{num_processes} completed.")

    # Combine results from all processes
    total_collisions = 0
    combined_hashes = {}

    for (start, end), (local_hashes, collisions) in return_dict.items():
        total_collisions += collisions
        for hash_output, input_data in local_hashes.items():
            if hash_output in combined_hashes:
                print(f"Collision detected: {combined_hashes[hash_output]} and {input_data} -> {hash_output}")
            else:
                combined_hashes[hash_output] = input_data

    print(f"Total collisions found: {total_collisions} out of {n} hashes")

if __name__ == "__main__":
    test_collisions(1000000, num_processes=4)
