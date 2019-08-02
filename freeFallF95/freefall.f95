program freefall

implicit none
 
real(8) :: y,v,a,g,t,dt,c_d,drag

y = 57.0
v = -3.8
a = -9.8
t = 0.0
dt = .01

open(unit = 100, file = 'pos.dat')
write(100,*) '#t 	y'
write(100,*) t,y
open(unit = 110, file = 'vel.dat')
write(110,*) '#t 	v'
write(110,*) t,v
open(unit = 120, file = 'accel.dat')
write(120,*) '#t 	a'
write(120,*) t,a

do while(y >= 0.0)
  t = t + dt
  y = y + v*dt
  v = v + a*dt
  write(100,*) t,y
  write(110,*) t,v
  write(120,*) t,a
end do

close(100)
close(110)
close(120)

y = 57.0
v = -3.8
g = -9.8
t = 0.0

open(unit = 130, file = 'posdrag.dat')
write(130,*) '#t 	y'
write(130,*) t,y
open(unit = 140, file = 'veldrag.dat')
write(140,*) '#t 	v'
write(140,*) t,v
a = g + drag(v)
open(unit = 150, file = 'acceldrag.dat')
write(150,*) '#t 	a'
write(150,*) t,a

do while(y >= 0.0)
  t = t + dt
  y = y + v*dt
  v = v + a*dt
  a = g + drag(v)
  write(130,*) t,y
  write(140,*) t,v
  write(150,*) t,a
end do

close(130)
close(140)
close(150) 
end program freefall

real(8) function drag(v)
  real(8) v,cd,xa,s,m,p
  p = 1.225	!density of fluid
  m = .145	!mass of object
  cd = 0.37	!coefficient of drag for a baseball
		!sized sphere
  xa = 0.0043	!cross-sectional area
  s = ABS(v)	!magnitude of velocity
  drag = (-0.5 * cd * p * xa * s * v) / m
  return
end
