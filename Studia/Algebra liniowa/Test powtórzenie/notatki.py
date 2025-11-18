#RÓWNANIA Z NIEWIADOMĄ X:
#a)
a=matrix([[-2,2,-1],[4,0,1]])
b=matrix([[0,1,-3],[2,1,0]])
x=(b+a)/2
print(x)

a=matrix([[0,6,3],[-1,-2,1]])
b=matrix([[6,0],[1,-2]])
x=a.solve_right(b)
print(x)

var('a b c d')
X = Matrix([[a, b], [c, d]])
A = Matrix([[1, 0], [1, 1]])
B = Matrix([[1, 0], [2, 1]])
rozw=solve([c==0 for c in (X*A-B*X).list()],[a,b,c,d])
rozw

#POSTAĆ SCHODKOWA I RZĄD MACIERZY:
#a
A=matrix([[2,-1,1,-1],[1,1,1,1],[2,0,2,2]])
wyn=A.echelon_form()
b=A.rank()
print(b)
wyn

DEFINICJA I OPERACJE ELEMENTARNE
#c
p,q,r,s,t,w,u,x,z=var('p,q,r,s,t,w,u,x,z')
A=matrix([[1,0,2],[2,1,1],[2,1,0]])
X=matrix([[p,q,r],[s,t,w],[u,x,z]])
# z definicji
I=identity_matrix(3)
roz=solve([c==0 for c in(A*X-I).list()],[p,q,r,s,t,w,u,x,z])
roz2=X.subs(roz)
roz2

#operacje elementarne
A=matrix([[1,0,2],[2,1,1],[2,1,0]])
u=A.augment(I,subdivide=True).echelon_form()
X=A.solve_right(I)
X

POSTAĆ BAZOWA:
#a
A=matrix([[1,-1,2],[-2,3,1],[5,-7,-4]])
roz=A.rref()
rzad=roz.rank()
print(rzad)
roz

#ROZWIĄZYWANIE METODY KOLUMN JEDNOSTRKOWYCH:
A=matrix([[2,-1,1],[-4,-12,1],[3,3,1]])
B=vector([1,2,3])
x,y,z,t=var('x,y,z,t')
X=vector([x,y,z,t])
U=A.augment(B,subdivide=True).rref()
solve([c==0 for c in(A*X-B).list()],[x,y,z,t])

SZUKANIE ELEMENTU e W PERMUTACJACH:
s = PermutationGroupElement([2,3,1,5,4,8,10,9,7,6])
lcm([c.order() for c in s.cycles()])
s.order()

PERMUTACJE:
s=PermutationGroupElement([2,5,3,1,4])
t=PermutationGroupElement([4,5,2,1,3])
print(Permutation(t*s))
print(Permutation(s*t))
print(Permutation(s^4))
print(Permutation(t^(-1)))
print(Permutation(t^2021))

PERMUTACJA TA CO BYŁA U RAJMUNDA:
a=PermutationGroupElement([9,1,4,2,6,5,3,8,7])
s=PermutationGroupElement([4,7,6,5,1,9,2,3,8])
t=Permutation((s^(-1))*a*(s^(26)))
t

CIAŁA:
cialo=GF(29)
print(cialo(27*5-19))
print(cialo(12^(-1)))
print(cialo(4*21^(-3)+3^4*5-2^(-6)))