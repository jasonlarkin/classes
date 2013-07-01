   %  Matlab Program to Find Pi using Random Numbers
   %  Tom Huber,  June 15, 1996
   Nrand = input('How Many Random Numbers ');
   NInside = 0;
   for nloops=1:Nrand
      Xrand = rand;   % Generate Random XY Point
      Yrand = rand;
      Rrand = Xrand^2 + Yrand^2;  % Find its distance from origin
      if (Rrand <= 1)
          NInside = NInside + 1;
      end
   end
   disp(['Total Generated: ' num2str(Nrand) ' Inside Pts: ' ...
      num2str(NInside)]);
   piapprox = 4*NInside/Nrand;
   disp(['  Approximation to pi = ' num2str(piapprox)]);

