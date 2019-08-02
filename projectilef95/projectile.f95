program projectile

implicit none

real(8), parameter :: g = -9.81			!accel due to gravity
real(8), parameter :: m = .145			!mass of projectile
real(8), parameter :: dt = 0.01			!time step
real(8), parameter :: xa = 0.0043		!cross-sectional area of a
						!ball with radius ____
real(8), parameter :: cd = 0.37			!coef of drag
real(8), parameter :: p = 1.225			!density of medium
real(8), parameter :: kappa = (-0.5*cd*p*xa)/m 	!math for drag equation
integer(4), parameter :: n = 500		!array size/step limit

integer(4) :: i					!iterator
real(8) :: t,mx,mh,vmag				!time,max x,max h,v magnitude
real(8), allocatable, dimension(:) :: x,y,z	!position arrays
real(8), allocatable, dimension(:) :: vx,vy,vz	!velocity arrays
real(8), allocatable, dimension(:) :: ax,ay,az	!acceleration arrays

allocate(x(n),y(n),z(n))
allocate(vx(n),vy(n),vz(n))
allocate(ax(n),ay(n),az(n))

!----------------------------------------------------------------------------
!------------------------------Initial Values--------------------------------
!----------------------------------------------------------------------------
x(1) = 0.0
y(1) = 0.0
z(1) = 1.0
vx(1) = 20.0*cos(0.872665) + 0.0                !roughly 50 degrees in radians
vy(1) = 0.0
vz(1) = 20.0*sin(0.872665) + 0.0
ax(1) = 0.0
ay(1) = 0.0
az(1) = g

!----------------------------------------------------------------------------
!--------------------------Midpoint Method DO Loop---------------------------
!----------------------------------------------------------------------------
do i = 2,n
  vmag = sqrt(vx(i-1)**2.0 + vy(i-1)**2.0 + vz(i-1)**2.0)
  t = t + dt
  
  vx(i) = vx(i-1) + ax(i-1)*dt
  vy(i) = vy(i-1) + ay(i-1)*dt
  vz(i) = vz(i-1) + az(i-1)*dt

  x(i) = x(i-1) + ((vx(i)+vx(i-1))/2.0)*dt
  y(i) = y(i-1) + ((vy(i)+vy(i-1))/2.0)*dt
  z(i) = z(i-1) + ((vz(i)+vz(i-1))/2.0)*dt
  
  ax(i) = 0.0, ay(i) = 0.0, az(i) = g
  ax(i) = ax(i) + kappa * vmag * vx(i)
  ay(i) = ay(i) + kappa * vmag * vy(i)
  az(i) = az(i) + kappa * vmag * vz(i)
  
  if (z(i) <= 0.0d0) exit			!exit if below ground
enddo 

!----------------------------------------------------------------------------
!---------------------------------Write Data---------------------------------
!----------------------------------------------------------------------------
open(unit=100,file = 'pos3d.dat')
write(100,*) '#x				y				z'
open(unit=110,file = 'vel3d.dat')
write(110,*) '#vx				vy				vz'
open(unit=120,file = 'accel3d.dat')
write(120,*) '#ax				ay				az'

do i = 1,n
  write(100,*) x(i),y(i),z(i)
  write(110,*) vx(i),vy(i),vz(i)
  write(120,*) ax(i),ay(i),az(i)
enddo

temp = 0.0
mx = 0.0
do i = 1,n
  if (z(i) > temp) temp = z(i)
  if (x(i) >= 0.0000000000001) mx = x(i) 
enddo

print*, 'time of flight = ',(t+t-dt)/2.0d0
print*, 'maximum height = ',temp
print*, 'maximum distance traveled = ',mx

close(100)
close(110)
close(120)

deallocate(x,y,z,vx,vy,vz,ax,ay,az)

end program projectile
