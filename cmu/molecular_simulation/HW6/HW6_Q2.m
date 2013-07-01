
function kcalc = HW6_Q2(delta,beta,epsilon)

%Inputs
%delta=2.0; beta=0.01; epsilon=0.05; 
xi = -1.0; 
Ntot=500000;

numacc = 0; numreject = 0;
Ui = Q4b_energy(xi);
U=Ui; xold=xi;
xpos(1) = 0; Ulist(1)=0; xposacc(1)=0; Ulistacc(1)=0;

Ustar = 1.0; U0=0.0; xstar=0.0;

ind = 1;
N=0;

for i=1:Ntot

    %generate trial position and energy
    xtrial = xold + (rand()-0.5)*delta;
    Utrial = HW6_Q2_energy(xtrial);
 
    %check if new energy is lower or higher
    if xtrial > (xstar + epsilon/2)
        xpos(i)=xtrial;
        numreject = numreject+1;
    else
        randnum=rand();
        if Utrial<U
            xold=xtrial; xpos(i) = xtrial;
            U=Utrial; Ulist(i)=Utrial;
            numacc = numacc+1; N=N+1;
            if (xstar-epsilon/2)<=xtrial & xtrial<=(xstar+epsilon/2)
                xold=xtrial; xposacc(ind) = xtrial;
                U=Utrial; Ulistacc(ind)=Utrial;
                ind=ind+1;
            end
        elseif randnum<=exp(-beta*(Utrial-U))
            xold=xtrial; xpos(i) = xtrial;
            U=Utrial; Ulist(i)=Utrial;
            numacc = numacc+1; N=N+1;
            if (xstar-epsilon/2)<=xtrial & xtrial<=(xstar+epsilon/2)
                xold=xtrial; xposacc(ind) = xtrial;
                U=Utrial; Ulistacc(ind)=Utrial;
                ind=ind+1;
            end
        else
            numreject = numreject+1;
        end
    end
end



plot(xpos)
deltafn=(1/N)*(1/epsilon)*(length(xposacc));
kcalc = 0.5*sqrt(2/(pi*beta*1))*deltafn
kabexact = (sqrt(8)/(2*pi))*(exp(-beta*(Ustar-U0)))

numacc
numreject

% for i=1:length(Ulist)
%     Uavg(i) = mean(Ulist(1:i));
%     x2avg(i) = mean(xpos(1:i).*xpos(1:i));
% end