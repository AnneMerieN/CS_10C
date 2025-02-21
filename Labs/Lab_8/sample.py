import random
with open('movieReviews.txt') as s:
    lines = s.read().split('\n')
    sample = random.sample(lines,10)
    with open('sample.txt','w') as out:
        for line in sample:
            print(line,file=out)
    
