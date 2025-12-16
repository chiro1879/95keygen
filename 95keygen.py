import random

MAX_ARR_SIZE = 14282

def pad_number_with_zeros(num, desired_length):
    temp = str(num)
    zeros = desired_length - len(temp)
    return '0' * zeros + temp

def rnd(min_val, max_val):
    return random.randint(min_val, max_val - 1)

print("Calculating...")

arr = []
arr_count = 0

for i in range(100000):
    num_str = pad_number_with_zeros(i, 5)

    sum_digits = sum(int(digit) for digit in num_str)

    if sum_digits % 7 == 0:
        if arr_count < MAX_ARR_SIZE:
            arr.append(num_str)
            arr_count += 1

    if i % 1000 == 0:
        print(f"Calculating...\n {i * 100 // 100000}%")

random.seed()

one = pad_number_with_zeros(rnd(1, 366), 3)
two = pad_number_with_zeros(rnd(95, 99), 2)
three = arr[rnd(0, arr_count)]
four = arr[rnd(0, arr_count)]

key = f"{one}{two}-OEM-00{three}-{four}"
print(key)