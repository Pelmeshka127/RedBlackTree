import random
import os

requests = []

request_set = set()

request_num = int(input("Enter the number of requests: "))

size = 0

all_files = os.listdir()

max_test_number = 0

for file in all_files:

    if file.endswith('.dat'):

        test_number = int(file[:-4])

        if (test_number > max_test_number):
            max_test_number = test_number

for i in range(request_num):

    j = random.randint(-request_num, request_num)

    if (j % 2 == 0) or (size <= 0.1 * request_num):

        requests.append('k')

        num = random.randint(-request_num, request_num)

        requests.append(str(num))

        if not(num in request_set):

            size += 1
            
            request_set.add(num)

    if (j % 2 == 1) and (size > 0.1 * request_num):

        requests.append('q')

        num1 = str(random.randint(-request_num, request_num))

        num2 = str(random.randint(-request_num, request_num))

        requests.append(num1)

        requests.append(num2)


with open(str(max_test_number + 1).zfill(3) + ".dat", "w") as f:
    f.write(" ".join(requests))