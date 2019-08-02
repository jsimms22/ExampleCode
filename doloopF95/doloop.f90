program do_loop

implicit none
integer(4) :: i,j
real(8) :: x,y

x = 56.0

open(unit=100,file='doloop.dat')

write(100,*) 'x = ', x

do i=1,10

  y=x
  x = x+10.0
  
  write(100,*) 'y = ',y

  write(100,*) 'x = ',x

end do

close(100)

end program do_loop
