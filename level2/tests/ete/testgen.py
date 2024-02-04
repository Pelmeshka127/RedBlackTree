import random
import os

requests = []

req_set = set()

request_num = int(input("Enter number of requests: "))

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

    if j % 3 == 0 or size <= 0.2 * request_num:
        
        requests.append('k')
     
        num = random.randint(-request_num, request_num)
     
        requests.append(str(num))
     
        if not(num in req_set):
            size += 1
            req_set.add(num)
    
    if (j % 3 == 1) and (size > 0.2 * request_num):
        
        requests.append('m')
    
        num1 = str(random.randint(1, size))
    
        requests.append(num1)
    
    if (j % 3 == 2) and (size > 0.2 * request_num):
        
        requests.append('n')
    
        requests.append(str(random.randint(-1* int(1.1 * request_num), int(1.1 * request_num))))

with open(str(max_test_number + 1).zfill(3) + ".dat", "w") as f:
    f.write(" ".join(requests))