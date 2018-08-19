#include <fstream>
using namespace std;
ifstream f("agenda.in");
ofstream g("agenda.out");
char c,v[4];
bool gasit,zi1,luna1,zi2,luna2,h1,m1,h2,m2;
int frecv[525600]={0},nr,nrzile[13]={0,31,59,90,120,151,181,212,243,273,304,334,365};
long minutstart,minutfinal,maximactv,distanta,minutfinalmax,minutstartminim;
int cerinta,i;
int main()
{
    f>>cerinta;c=f.get();
     do
    {
       c=f.get();nr=0;
       if(c=='\n')
       {
        c=f.get();
        zi1=luna1=zi2=luna2=h1=m1=h2=m2=0;
         for(i=minutstart;i<=minutfinal;i++)
        {
        frecv[i]++;
        if(maximactv<frecv[i])
        maximactv=frecv[i];
        }
        distanta=distanta<(minutfinal-minutstart) ? (minutfinal-minutstart):distanta;
        minutfinalmax=minutfinal>minutfinalmax ? minutfinal:minutfinalmax;
       if(gasit==0)
       {minutstartminim=minutstart;gasit=1;}
       else
       minutstartminim=minutstartminim<minutstart ? minutstartminim:minutstart;
        minutstart=minutfinal=0;
       }
       if(h2==1&&m2==0&&c>='0'&&c<='9')
       {
           while(c>='0'&&c<='9')
            {nr=nr*10+c-'0';m2=1;c=f.get();}
            minutfinal+=nr;
       }
       else if(luna2==1&&h2==0&&c>='0'&&c<='9')
        {
            while(c!='.')
            {
            if(c>='0'&&c<='9')
            {nr=nr*10+c-'0';h2=1;}
            c=f.get();
            }
            minutfinal+=60*nr;
        }
       else if(zi2==1&&luna2==0&&((c<='z'&&c>='a')||(c<='Z'&&c>='A')))
       {
           v[1]=c;
          v[2]=f.get();
          v[3]=f.get();
       luna2=1;
    if((v[1]=='i'&&v[2]=='a'&&v[3]=='n')||(v[1]=='I'&&v[2]=='a'&&v[3]=='n'))
    {
        nr=1;
    }
   else if((v[1]=='f'&&v[2]=='e'&&v[3]=='b')||(v[1]=='F'&&v[2]=='e'&&v[3]=='b'))
    {
        nr=2;
    }
   else if((v[1]=='m'&&v[2]=='a'&&v[3]=='r')||(v[1]=='M'&&v[2]=='a'&&v[3]=='r'))
    {
        nr=3;
    }
   else if((v[1]=='a'&&v[2]=='p'&&v[3]=='r')||(v[1]=='A'&&v[2]=='p'&&v[3]=='r'))
    {
        nr=4;
    }
   else if((v[1]=='m'&&v[2]=='a'&&v[3]=='i')||(v[1]=='M'&&v[2]=='a'&&v[3]=='i'))
    {
        nr=5;
    }
   else if((v[1]=='i'&&v[2]=='u'&&v[3]=='n')||(v[1]=='I'&&v[2]=='u'&&v[3]=='n'))
    {
        nr=6;
    }
   else if((v[1]=='i'&&v[2]=='u'&&v[3]=='l')||(v[1]=='I'&&v[2]=='u'&&v[3]=='l'))
    {
       nr=7;
    }
   else if((v[1]=='a'&&v[2]=='u'&&v[3]=='g')||(v[1]=='A'&&v[2]=='u'&&v[3]=='g'))
    {
        nr=8;
    }
   else if((v[1]=='s'&&v[2]=='e'&&v[3]=='p')||(v[1]=='S'&&v[2]=='e'&&v[3]=='p'))
    {
        nr=9;
    }
    else if((v[1]=='o'&&v[2]=='c'&&v[3]=='t')||(v[1]=='O'&&v[2]=='c'&&v[3]=='t'))
    {
        nr=10;
    }
   else if((v[1]=='n'&&v[2]=='o'&&v[3]=='i')||(v[1]=='N'&&v[2]=='o'&&v[3]=='i'))
    {
        nr=11;
    }
  else  if((v[1]=='d'&&v[2]=='e'&&v[3]=='c')||(v[1]=='D'&&v[2]=='e'&&v[3]=='c'))
    {
        nr=12;
    }
    minutfinal+=nrzile[nr-1]*1440;
  }
  else if(zi2==0&&m1==1&&c>='0'&&c<='9')
  {
      zi2=1;
      while(c>='0'&&c<='9')
      {
          nr=nr*10+c-'0';c=f.get();
      }
      f.putback(c);
      minutfinal+=1440*(nr-1);
  }
  else if(m1==0&&h1==1&&c>='0'&&c<='9')
  {
      m1=1;
       while(c>='0'&&c<='9')
      {
          nr=nr*10+c-'0';c=f.get();
      }
      minutstart+=nr;
  }
  else if(h1==0&&luna1==1&&c>='0'&&c<='9')
  {
      h1=1;
       while(c!='.')
      {
          if(c<='9'&&c>='0')
          nr=nr*10+c-'0';c=f.get();
      }
      minutstart+=nr*60;
  }
  else if(zi1==1&&luna1==0&&c!=' ')
  {
      v[1]=c;
           v[2]=f.get();
          v[3]=f.get();
    luna1=1;
     if((v[1]=='i'&&v[2]=='a'&&v[3]=='n')||(v[1]=='I'&&v[2]=='a'&&v[3]=='n'))
    {
        nr=1;
    }
   else if((v[1]=='f'&&v[2]=='e'&&v[3]=='b')||(v[1]=='F'&&v[2]=='e'&&v[3]=='b'))
    {
        nr=2;
    }
   else if((v[1]=='m'&&v[2]=='a'&&v[3]=='r')||(v[1]=='M'&&v[2]=='a'&&v[3]=='r'))
    {
        nr=3;
    }
   else if((v[1]=='a'&&v[2]=='p'&&v[3]=='r')||(v[1]=='A'&&v[2]=='p'&&v[3]=='r'))
    {
        nr=4;
    }
   else if((v[1]=='m'&&v[2]=='a'&&v[3]=='i')||(v[1]=='M'&&v[2]=='a'&&v[3]=='i'))
    {
        nr=5;
    }
   else if((v[1]=='i'&&v[2]=='u'&&v[3]=='n')||(v[1]=='I'&&v[2]=='u'&&v[3]=='n'))
    {
        nr=6;
    }
   else if((v[1]=='i'&&v[2]=='u'&&v[3]=='l')||(v[1]=='I'&&v[2]=='u'&&v[3]=='l'))
    {
       nr=7;
    }
   else if((v[1]=='a'&&v[2]=='u'&&v[3]=='g')||(v[1]=='A'&&v[2]=='u'&&v[3]=='g'))
    {
        nr=8;
    }
   else if((v[1]=='s'&&v[2]=='e'&&v[3]=='p')||(v[1]=='S'&&v[2]=='e'&&v[3]=='p'))
    {
        nr=9;
    }
    else if((v[1]=='o'&&v[2]=='c'&&v[3]=='t')||(v[1]=='O'&&v[2]=='c'&&v[3]=='t'))
    {
        nr=10;
    }
   else if((v[1]=='n'&&v[2]=='o'&&v[3]=='i')||(v[1]=='N'&&v[2]=='o'&&v[3]=='i'))
    {
        nr=11;
    }
  else  if((v[1]=='d'&&v[2]=='e'&&v[3]=='c')||(v[1]=='D'&&v[2]=='e'&&v[3]=='c'))
    {
        nr=12;
    }
    minutstart+=nrzile[nr-1]*1440;
  }
  else if(zi1==0&&c>='0'&&c<='9')
  {
      zi1=1;
        while(c>='0'&&c<='9')
      {
          nr=nr*10+c-'0';c=f.get();
      }
      minutstart+=(nr-1)*1440;
      f.putback(c);
  }
  }
    while(c!=-1);
    if(cerinta==1)
    {
       int ore,zile;
       ore=distanta/60;
       distanta=distanta%60;
       zile=ore/24;
       ore=ore%24;
       g<<zile<<" "<<ore<<" "<<distanta;
    }
    else if(cerinta==2)
    g<<maximactv;
    else
    {
        int intervalmax=0,interval=0,ore,zile;
        for(i=minutstartminim;i<=minutfinalmax;i++)
        {
            if(frecv[i]==0)
            interval++;
            else
            {
                if(interval>intervalmax)
                intervalmax=interval;
                interval=0;
            }
        }
        ore=intervalmax/60;
        intervalmax=intervalmax%60;
        zile=ore/24;
        ore=ore%24;intervalmax++;
        if(intervalmax==60)
        {
            intervalmax=0;ore++;
            if(ore==24)
            zile++;
        }
        g<<zile<<" "<<ore<<" "<<intervalmax;
    }
    f.close();g.close();
    return 0;
}
