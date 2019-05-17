def find_length(n): 
    n = bin(n)[2:]
    max_length = current_length = 0

    for digit in n: 
        if digit == '1':
            current_length += 1
            max_length = max(max_length, current_length)
        else: 
            current_length = 0 

    return max_length

def find_length2(n): 
    max_length = 0 

    while n: 
        max_length += 1 
        n = n & (n << 1) 

    return max_length 

kk = 156
result = find_length(kk)
print(result)
print(bin(result))

print("Second version") 

result = find_length(kk)
print(result)
print(bin(result))
