# 3D-spheres
A cpp application which shows 3D spheres created from an IFS (iterated function system) using Open GL libraries.

The IFS creating spheres is :
{h_0 , h_1} such that: h_0: R^3 --> R^3 , X --> C_0 and h_1 : R^3 --> R^3, X --> a A X
In the application the constants initialized as :
C_0: a sphere of radius 1 at (0,4,4) ,
a = 0.95 ,
A = [cos(t)  sin(t)  0
     sin(t)  cos(t)  0
     0       0      1]
and t = 2\PI / 11

In the program following shortcuts could help to get a better image:
N  ,  n --> increase , decrease number of displaying spheres
R  ,  r --> increase , decrease radius of first sphere
A  ,  a --> increase , decrease the constant "a" in h_1
T  ,  t --> increase , decrease the constant "t" in h_1
L  ,  l --> increase , decrease the legth of drawn axis for x , y, z
X  ,  x --> increase , decrease eye position on the window in x
Y  ,  y --> increase , decrease eye position on the window in y
Z  ,  z --> increase , decrease eye position on the window in z (you can also use mouse wheel to change z)

arrows up , down --> change center of view position in y
arrows right, left --> change center of view position in x

