#include<graphics.h>
#include<iostream.h>
#include<conio.h>
#include<dos.h>
int main()
{
int gb=DETECT,gm;
initgraph(&gb, &gm,"C:\\TC\\BGI");
circle(50,5,5);
int co_x=50,co_y=5,co_xb,co_yb,j[5],idx_fire=-1,fire=0,up=0,down=0,ini=0,hit_count=0;
char a;
	while(1)
	{   
		for(int i=10;i<=200;i+=10)
		{

			circle(10,i,10);

			if(kbhit())

			{


			a=getch();
				if((a=='u') || (a=='U'))
				{
					up = 1;
				}

				else if((a=='d') || (a=='D'))
				{
					down=1;
				}


				else if(a=='F' ||a =='f')
				{
				 fire=1;
		     idx_fire++;
		     if(idx_fire<5)
			       {
			    j[idx_fire]=co_x-10;

			 }
		     else
			 {
			 idx_fire=0;
			 ini=0;
			//break;
			//closegraph(); //GAME OVER
			 }
				}


				else if(a=='E' ||a=='e')
				{
				closegraph();
				break;
				}
			}
		delay(500);
		cleardevice();

		if(up==1)
		{
			 if(co_y>5)
			 {

				co_y-=5;
				circle(co_x,co_y,5);
			 }

				 else
				 co_y=5;
		up=0;
		}

		if(down==1)
		{
			 if(co_y<100)
			 {
				co_y+=5;
				circle(co_x,co_y,5);
			 }

				 else
				 co_y=95;
		down=0;
		}
		else if(up==0 && down==0)
		{
			circle(co_x,co_y,5);
		}

		if(fire==1)
			{
		  for(int i1=ini;i1<=idx_fire;i1++)
		       {
			       if(j[i1]<0)
			      {

				j[i1]=0;
				ini=ini+1;

			      }
				   circle(j[i1],co_y,2);
				   j[i1]-=10;
				if((((j[i1]-10)*(j[i1]-10))+((co_y-i)*(co_y-i)))<=144)
			  hit_count++;
			  cout<<"hitcount ="<<hit_count;
		    }
		   }



		}

	}

return 0;
}
