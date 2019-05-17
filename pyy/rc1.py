def singleNumber(nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    result = [0] * 32
    for num in nums:
        for i in range(32):
            bit = num >> i & 1
            result[i] += bit

    print(result)
    my_result = 0
    for i, bit in enumerate(result):
        if bit % 3 != 0:
            my_result |= 1 << i
            print("result is ", bit, my_result )

    if my_result >= 2 ** 31:
            my_result -= 2 ** 32

    return int(my_result)




kk = [-2,-2,1,1,-3,1,-3,-3,-4,-2]
result = singleNumber(kk)
print(result)
print(bin(result))

