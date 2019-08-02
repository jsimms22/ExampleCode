program hooks_law

implicit none

integer :: n,i
real(8) :: k,dt,m
real(8), allocatable, dimension(:) :: x,v,a,TE,KE,PE
real(8) :: w,t

n = 10000

allocate(x(n),v(n),a(n),TE(n),KE(n),PE(n))

m = 5.0
dt = 0.01
k = .25

t = 0.0
x(1) = -3.0
v(1) = 0.0
a(1) = k/m * x(1)

KE(1) = 0.5 * m * v(1)**2.0
PE(1) = 0.5 * k * x(1)**2.0
TE(1) = KE(1) + PE(1)

open(unit = 100, file = 'springX.dat')
write(100,*) '#t		x)'
write(100,*) t,x(1)
open(unit = 110, file = 'springV.dat')
write(110,*) '#t		v)'
write(110,*) t,v(1)
open(unit = 120, file = 'springKE.dat')
write(120,*) '#t		KE)'
write(120,*) t,KE(1)
open(unit = 130, file = 'springPE.dat')
write(130,*) '#t		PE)'
write(130,*) t,PE(1)
open(unit = 140, file = 'springA.dat')
write(140,*) '#t		a)'
write(140,*) t,a(1)

do i = 1,n-1
  t = t + dt
  v(i+1) = v(i) - dt*(k/m)*x(i)
  x(i+1) = x(i) + dt*(v(i) + v(i+1))/2.0
  a(i+1) = (k / m) * x(i+1)
  KE(i+1) = 0.5 * m * v(i+1)**2.0
  PE(i+1) = 0.5 * k * x(i+1)**2.0
  TE(i+1) = KE(i+1) + PE(i+1)
  
  write(100,*) t,x(i+1)
  write(110,*) t,v(i+1)
  write(120,*) t,KE(i+1)
  write(130,*) t,PE(i+1)
  write(140,*) t,a(i+1)
end do

close(100)
close(110)
close(120)
close(130)

end program hooks_law
