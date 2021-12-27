def subsetSumIncreasing(arr, val):
    assert arr == sorted(arr)
    result = []
    n = len(arr)
    if n  == 0:
        return result;
    idx = 0;
    hit = False;
    for i in range(n-1, -1, -1):
        if (arr[i] <= val):
            idx = i;
            hit = True;
            break
    if hit:
        result.extend(subsetSumIncreasing(arr[0:idx], val - arr[idx]))
        result.extend([idx])  #extend list  by appending elements from the iterable
    return result

def  subsetSumParition(arr, target):
    indices = subsetSumIncreasing(arr, target)
    print("indices = ", indices)
    result = [0] * len(indices)
    total = 0
    i = 0
    for index in indices:
        result[i] = arr[index]
        total += arr[index]
        i += 1
    assert total == target
    return result

knap = [5, 20, 10, 80, 40, 50, 30, 12, 8, 15, 32]
knap.sort();
print("knap = ", knap)
target = 90
print("target = ", target)
parition = subsetSumParition(knap, target)
print(parition)