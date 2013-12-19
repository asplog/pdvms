import math;
import pd;
class A:
	def __init__(self):
		self.x=10;
	def dump(self,b,c=20):
		print(self.x+b*c);
value=A();
def func():
	global a;
	a=10;
def test(w,*a):
	print(list(a));
def sump(a,b,c):	
	return sum([a,b,c]);
def bang():
	return "ok";
def number(a):
	return a*a;
def set(k,v):
	pd.set(k,v);
def get(k):
	return pd.get(k);
outlet=4;
