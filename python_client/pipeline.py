import subprocess

# Run the C++ program as a subprocess
process = subprocess.Popen(["../build/Client"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

while True:
    # Read data from the C++ program's stdout
    cplusplus_output = process.stdout.readline().strip()
    if not cplusplus_output:
        break  # Break the loop if there's no more data

    print(f"Received from C++ program: {cplusplus_output}")

# Close the subprocess
process.stdin.close()
process.stdout.close()
process.wait()  # Wait for the subprocess to finish
