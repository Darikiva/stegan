from collections import Counter
import re


def get_prefixes(file_path):
    prefixes = []

    with open(file_path, 'r', encoding='utf-8') as file:
        for line in file:
            words = re.findall(r'\b\w+\b', line.lower())
            for word in words:
                # print(word)
                prefixes.extend(word[0:i] for i in range(1, min(4, len(word) + 1)))
                break

    return prefixes

def top_prefixes(prefixes, n=500):
    prefix_count = Counter(prefixes)
    return prefix_count.most_common(n)

file_path = 'C:/Users/darik/univer/stress.txt'

prefixes = get_prefixes(file_path)
# print(prefixes[0:500])

top_500_prefixes = top_prefixes(prefixes)

my_set = dict()

for prefix, count in top_500_prefixes:
    if len(my_set) > 64:
        break
    for i in range(1, len(prefix) + 1):
        if prefix[0:i] in my_set:
            del my_set[prefix[0:i]]
    my_set[prefix] = count


for word in my_set:
    print(word, my_set[word])

for prefix, count in top_500_prefixes:
    print(f'Prefix: {prefix}, Count: {count}')