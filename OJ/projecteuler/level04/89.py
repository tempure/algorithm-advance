# 文件中的数字是一行一行的，不是拼接起来的
# 所以不涉及祖玛问题那种替换后可能会出现新的替换方案
# 只需要暴力替换即可
# ans = 743

import re

def main():
    with open('../data/p089_roman.txt') as f:
        romans = f.read()
    new = re.sub("DCCCC|LXXXX|VIIII|CCCC|XXXX|IIII", '**',romans)
    savings = len(romans) - len(new)
    print(savings)

main()