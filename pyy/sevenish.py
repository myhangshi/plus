def get_7ish_number(n): 
    powers = [7**i for i in range(n)]
    totals = {0}

    for p in powers: 
        totals |= {x + p for x in totals}

    return totals 

def nth_7ish_numer(n): 
    sevenish_numbers = get_7ish_number(n)
    print(sevenish_numbers)

    i = 1
    count, last_sevenish_number = 0, 0 

    while count < n: 
        if i in sevenish_numbers: 
            count += 1
            last_sevenish_number = i 
        i += 1

    return last_sevenish_number

#for i in range(10): 
#    print(nth_7ish_numer(i))

#print(get_7ish_number(4))

def nth_number(n): 
    answer = 0 
    bit_place = 0
    seven = 1 

    while n: 
        
        if n % 2: 
            answer += seven

        n = n // 2 
        seven *= 7 

    return answer 

for i in range(5): 
    print(nth_number(i))


