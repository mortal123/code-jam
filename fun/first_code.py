# haa.py
import math
import functools
#dic = {'LWH' : 2}

def power(x):
	return x * x

def fact(n):
	result = 1
	for i in range(n):
		result = result * (i + 1)
	return result
#	return superPower(1, 1, n)

def superPower(product, count, maxN):
	if count > maxN:
		return product
	else:
		return superPower(product * count, count + 1, maxN)

def move(x, y, step, angle = 0) :
	return x + step * math.cos(angle), y - step * math.sin(angle)

print fact(5)

L = ['Hello', 'World', 18, 'Apple', None]
print [s.lower() if isinstance(s, str) else s for s in L]

for i, value in enumerate(['A', 'B', 'C']):
	print i, value

print move(100, 100, 60, math.pi / 6)
print power(5)

lists = [1, 2, 3, 4, 5, 6]
print reduce(lambda a, b : a + b, lists)

def log(arg):
	if not isinstance(arg, str):
		def wrapper(*args, **kw):
			print 'prob begin'
			result = arg(*args, **kw)
			print 'prob end'
			return result
		return wrapper
	else:
		def decorator(func):
			def wrapper(*args, **kw):
				print '%s' % arg
				return func
			return wrapper
		return decorator

@log('excute')
def time():
	print '2014-11-28'

time()
print time.__name__

def test(a, b, c, d):
	return d + c * 10 + b * 100 + a * 1000

print test(1, 2, 3, 4)

test1 = functools.partial(test, d = 1)
print test1(1, 2, 3)
test2 = functools.partial(test, d = 1, c = 2)
print test2(1, 9)